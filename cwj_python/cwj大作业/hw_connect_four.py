# -*- coding: utf-8 -*-  采用utf-8字符编码而非gbk，后者不支持汉字
import sys 
import pygame  
import math
import random
# 导入 random 模块，用于生成伪随机数
# 在 AI 逻辑中用于选择最佳落子位置之一（如果多个位置分数相同）
import time
import tkinter as tk
from tkinter import messagebox
import os 
os.environ['SDL_VIDEO_CENTERED'] = '1'

#---------------------------------------------------------------------------------------

'''
--- 此程序大部分的常量和变量命名规律采用cwj老师课上提到的匈牙利命名法 ---
'''

# --- 常量定义 ---

N_ROWS = 6
N_COLS = 7

N_WIN_LENGTH = 4 
PLAYER_1 = 0
PLAYER_2 = 1
PIECE_EMPTY = 0  # 表示棋盘格子里为空的状态，设置为 0
PIECE_PLAYER_1 = 1
PIECE_PLAYER_2 = 2

SQUARESIZE = 100  # 表示棋盘上每个格子（正方形）的边长（100像素）

WIDTH = N_COLS * SQUARESIZE
MENU_BAR_HEIGHT = 200 # 菜单顶部标题高度
TOP_BAR_HEIGHT = 100 # 游戏界面的顶部操作栏高度
HEIGHT = N_ROWS * SQUARESIZE + TOP_BAR_HEIGHT # 游戏窗口高度
SIZE = (WIDTH, HEIGHT) # 这里我用元组表示游戏窗口的尺寸（宽度，高度）
RADIUS = int(SQUARESIZE / 2 - 5) # 计算棋子圆形的半径，略小于格子宽度的一半，留一点边距
# 颜色常量的定义
COLOR_BLUE = (0, 0, 255)
COLOR_BLACK = (0, 0, 0)
COLOR_RED = (255, 0, 0)
COLOR_YELLOW = (255, 255, 0)
COLOR_WHITE = (255, 255, 255)
COLOR_GRAY = (180, 180, 180)
COLOR_PIECE_TEXT = COLOR_BLACK
#游戏模式定义
MODE_SELECT = 0 # 模式选择界面
MODE_H_VS_H = 1 
MODE_H_VS_AI = 2
MODE_TIMED_H_VS_H = 3
MODE_SELECT_STARTER = -2 # 选择 玩家 vs AI 的先手

F_TIME_LIMIT_SECONDS = 300.0 # 限时模式时间上限 (秒)
F_AUTO_RETURN_DELAY = 10.0   # 游戏结束后自动返回菜单延迟 (单位：秒)


# --- 全局变量 ---
nGameMode = MODE_SELECT 
fTurnStartTime = 0.0 # 计算回合持续时间
fPlayer1TotalTime = 0.0 
fPlayer2TotalTime = 0.0
fGameEndTime = None # 游戏结束时间戳 ，初始化为 None
oWinnerTextRect = None # 用于存储游戏结束时显示的胜利/平局消息文本表面的矩形对象 (pygame.Rect)
sWinnerMessage = "" # 存储游戏结束时显示的胜利/平局消息字符串
nTurn = PLAYER_1 

pygame.init()

# --------------------------------------------------------------------------------

# --- Pygame 字体初始化 ---
FONT_FILE_PATH_MSG = None 
FONT_FILE_PATH_LARGE = None 
FONT_FILE_PATH_PIECE = None
# 默认为 None，使用系统字体

'''
尝试加载字体。使用 try...except 块是为了在加载字体失败时提供备选方案，避免程序崩溃
'''
try:
    OFONT_MENU_TITLE = pygame.font.Font(FONT_FILE_PATH_MSG, 24) if FONT_FILE_PATH_MSG else pygame.font.SysFont("SimHei", 24)
    OFONT_MSG = pygame.font.Font(FONT_FILE_PATH_MSG, 28) if FONT_FILE_PATH_MSG else pygame.font.SysFont("SimHei", 28)
    # 普通消息和菜单选项的字体对象。
    OFONT_PIECE = pygame.font.Font(FONT_FILE_PATH_PIECE, 50) if FONT_FILE_PATH_PIECE else pygame.font.SysFont("Arial Bold", 50)
    # 棋子上的文字（'X', 'O'）的字体对象
    OFONT_LARGE = pygame.font.Font(FONT_FILE_PATH_LARGE, 70) if FONT_FILE_PATH_LARGE else pygame.font.SysFont("SimHei", 70)
    # 游戏结束消息的字体对象
    OFONT_HINT = pygame.font.Font(FONT_FILE_PATH_MSG, 20) if FONT_FILE_PATH_MSG else pygame.font.SysFont("SimHei", 20) 
    # 游戏界面提示文本的字体对象

# -- Pygame 在加载字体时可能发生的错误 (例如字体文件损坏) --
except pygame.error as e:
    print(f"警告：字体加载失败 ({e})，尝试使用默认字体，中文可能显示为方框。")
    OFONT_MENU_TITLE = pygame.font.SysFont(None, 28)
    OFONT_MSG = pygame.font.SysFont(None, 28)
    OFONT_PIECE = pygame.font.SysFont(None, 60)
    OFONT_LARGE = pygame.font.SysFont(None, 75)
    OFONT_HINT = pygame.font.SysFont(None, 20)
# 如果加载失败，则回退到使用 Pygame 默认字体 (SysFont(None, ...))。这可能导致中文字符无法显示

# -- 捕获字体文件找不到的错误 --
except FileNotFoundError as e:
     print(f"警告：找不到指定的字体文件 ({e})，尝试使用默认字体，中文可能显示为方框。")
     OFONT_MENU_TITLE = pygame.font.SysFont(None, 28)
     OFONT_MSG = pygame.font.SysFont(None, 28)
     OFONT_PIECE = pygame.font.SysFont(None, 60)
     OFONT_LARGE = pygame.font.SysFont(None, 75)
     OFONT_HINT = pygame.font.SysFont(None, 20)
# 如果文件找不到，也回退到使用 Pygame 默认字体。同上

#--------------------------------------------------------------------------------------------------------

# --- Tkinter Pop-up 弹窗函数 ---
def show_message_popup(title, message): 
    """
    --- 通用消息弹窗 ---
    用于显示一个通用的 Tkinter 消息弹窗。接收标题和消息内容作为参数
    """
    # 使用 try...except 块来处理 Tkinter 初始化或创建弹窗时可能发生的错误
    try: 
        popup_root = tk.Tk() 
        popup_root.withdraw() 
        popup = tk.Toplevel(popup_root) # 创建一个 Toplevel 窗口，作为实际的弹窗。将其父窗口设置为 popup_root
        popup.title(title) 
        popup.attributes('-topmost', True) # 设置弹窗属性，使其始终显示在最顶层
        
        win_width = 450
        win_height = 150
        screen_width = popup.winfo_screenwidth()
        screen_height = popup.winfo_screenheight()
        
        # 计算弹窗居中显示时的左上角坐标。
        x = (screen_width / 2) - (win_width / 2)
        y = (screen_height / 2) - (win_height / 2)
        # 设置弹窗的大小和位置 (格式为 "宽x高+x+y")
        popup.geometry('%dx%d+%d+%d' % (win_width, win_height, x, y))
        try:
            custom_font = ("Helvetica", 16, "bold")
            message_label = tk.Label(popup, text=message, font=custom_font, pady=15)
            # 创建一个 Label 组件显示消息文本，设置字体和垂直内边距
        except tk.TclError:
             message_label = tk.Label(popup, text=message, pady=15)
        message_label.pack()
      # 使用 pack 布局管理器将 Label 放置到弹窗中
        ok_button = tk.Button(popup, text="确定", command=lambda: [popup.destroy(), popup_root.destroy()])
        # 创建一个 Button (确定按钮)
        # 使用 lambda 匿名函数，调用 popup.destroy() 关闭弹窗，然后调用 popup_root.destroy() 关闭隐藏的根窗口
        ok_button.pack(pady=5) # 使用 pack 布局管理器将 Button 放置到弹窗中，并设置垂直内边距
        popup.wait_window(popup) # 使程序暂停，直到弹窗被关闭，等待用户交互
        try: popup_root.destroy()
        except: pass
        # 在弹窗关闭后，再次尝试销毁根窗口，以防 lambda 命令未能完全清理。使用 try 避免在 popup_root 已经销毁时报错。
    except Exception as e: # 捕获其他任何异常
        print(f"Tkinter 弹窗出错: {e}")
        print(f"{title}: {message}")

def show_exit_popup():
    """
    显示退出信息弹窗
    """
    show_message_popup("游戏结束", "感谢cwj老师体验四子棋游戏,\n求求老师捞一捞分数!!! orz")


#-------------------------------------------------------------------------------------------------------------------------------

# --- 游戏逻辑函数 (游戏核心逻辑函数) ---

# 定义函数 create_board，用于创建一个新的空棋盘。
def create_board():
    a_a_nBoard = [[PIECE_EMPTY for _ in range(N_COLS)] for _ in range(N_ROWS)]
     # 使用列表推导式创建一个 N_ROWS 行、N_COLS 列的二维列表 (a_a_nBoard)
     # 列表中的每个元素都初始化为 PIECE_EMPTY (0)，代表空位
    return a_a_nBoard
def is_valid_location(a_a_nBoard, nCol):# 检查给定列 nCol 是否是有效的落子位置
    if 0 <= nCol < N_COLS: # 首先检查列号 nCol 是否在有效范围内 (0 到 N_COLS-1)
        bIsValid = a_a_nBoard[0][nCol] == PIECE_EMPTY
        # 如果列号有效，检查该列的最顶层 (索引为 0 的行) 是否为空。只要最上面有空位，下面就一定有空位
        return bIsValid
    return False
def get_next_open_row(a_a_nBoard, nCol):
    for nRow in range(N_ROWS - 1, -1, -1):
        if a_a_nBoard[nRow][nCol] == PIECE_EMPTY:
            return nRow
    return -1 # 如果遍历完所有行都没有找到空位（即该列已满），返回 -1
def drop_piece(a_a_nBoard, nRow, nCol, nPiece):
    if 0 <= nRow < N_ROWS and 0 <= nCol < N_COLS:
        a_a_nBoard[nRow][nCol] = nPiece

# 检查胜利条件
def check_win(a_a_nBoard, nPiece):
    # 水平方向的胜利
    for nRow in range(N_ROWS):
        for nCol in range(N_COLS - (N_WIN_LENGTH - 1)):
            if all(a_a_nBoard[nRow][nCol + i] == nPiece for i in range(N_WIN_LENGTH)):
                return True
    # 垂直方向的胜利
    for nCol in range(N_COLS):
        for nRow in range(N_ROWS - (N_WIN_LENGTH - 1)):
            if all(a_a_nBoard[nRow + i][nCol] == nPiece for i in range(N_WIN_LENGTH)):
                return True
    # 主对角线的胜利
    for nRow in range(N_ROWS - (N_WIN_LENGTH - 1)):
        for nCol in range(N_COLS - (N_WIN_LENGTH - 1)):
            if all(a_a_nBoard[nRow + i][nCol + i] == nPiece for i in range(N_WIN_LENGTH)):
                return True
    # 副对角线的胜利
    for nRow in range(N_WIN_LENGTH - 1, N_ROWS):
        for nCol in range(N_COLS - (N_WIN_LENGTH - 1)):
            if all(a_a_nBoard[nRow - i][nCol + i] == nPiece for i in range(N_WIN_LENGTH)):
                return True
    return False

# 检查棋盘是否已满（平局）
def is_board_full(a_a_nBoard):
    for nCol in range(N_COLS):
        if a_a_nBoard[0][nCol] == PIECE_EMPTY:
            return False
    return True

#--- AI 相关函数 ---

def evaluate_window(aWindow, nPiece):
    nScore = 0
    nOpponentPiece = PIECE_PLAYER_1 if nPiece == PIECE_PLAYER_2 else PIECE_PLAYER_2
    nCountPiece = aWindow.count(nPiece)
    nCountEmpty = aWindow.count(PIECE_EMPTY)
    nCountOpponent = aWindow.count(nOpponentPiece)

    # 根据不同数量的棋子和空位组合，给予不同的分数
    if nCountPiece == 4: nScore += 1000
    # 如果己方有 4 个连子，给予非常高的分数
    elif nCountPiece == 3 and nCountEmpty == 1: nScore += 10
     # 如果己方有 3 个连子和一个空位，给予较高的分数
    elif nCountPiece == 2 and nCountEmpty == 2: nScore += 3
    # 如果己方有 2 个连子和两个空位，给予较低的分数
    if nCountOpponent == 3 and nCountEmpty == 1: nScore -= 80
    # 如果对手有 3 个连子和一个空位，给予非常低的（负的）分数，AI 需要阻止这种情况
    elif nCountOpponent == 4: nScore -= 5000
     # 如果对手已经有 4 个连子，给予极低的（负的）分数
    return nScore

# 评估整个棋盘 a_a_nBoard 对于给定棋子 nPiece 的总分数
def score_position(a_a_nBoard, nPiece):
    nScore = 0
    # 偏爱中心列：在四子棋中，中心列更容易形成连接，因此优先占据中心列
    aCenterArray = [a_a_nBoard[i][N_COLS // 2] for i in range(N_ROWS)]
    nCenterCount = aCenterArray.count(nPiece)
    nScore += nCenterCount * 6 # 将中心列己方棋子的数量乘以一个权重 (6) 加到总分中
     
    # 评估水平方向的所有窗口
    for r in range(N_ROWS):
        aRowArray = [a_a_nBoard[r][c] for c in range(N_COLS)]
        for c in range(N_COLS - (N_WIN_LENGTH - 1)):
            aWindow = aRowArray[c:c + N_WIN_LENGTH]
            nScore += evaluate_window(aWindow, nPiece)
    # 评估垂直方向的所有窗口
    for c in range(N_COLS):
        aColArray = [a_a_nBoard[r][c] for r in range(N_ROWS)]
        for r in range(N_ROWS - (N_WIN_LENGTH - 1)):
            aWindow = aColArray[r:r + N_WIN_LENGTH]
            nScore += evaluate_window(aWindow, nPiece)
    # 评估主对角线方向的所有窗口
    for r in range(N_ROWS - (N_WIN_LENGTH - 1)):
        for c in range(N_COLS - (N_WIN_LENGTH - 1)):
            aWindow = [a_a_nBoard[r + i][c + i] for i in range(N_WIN_LENGTH)]
            nScore += evaluate_window(aWindow, nPiece)
    # 评估副对角线方向的所有窗口
    for r in range(N_WIN_LENGTH - 1, N_ROWS):
        for c in range(N_COLS - (N_WIN_LENGTH - 1)):
            aWindow = [a_a_nBoard[r - i][c + i] for i in range(N_WIN_LENGTH)]
            nScore += evaluate_window(aWindow, nPiece)
    return nScore

# 获取棋盘上所有可以合法落子的列的列表
def get_valid_locations(a_a_nBoard):
    aValidLocations = []
    for nCol in range(N_COLS):
        if is_valid_location(a_a_nBoard, nCol):
            aValidLocations.append(nCol)
    return aValidLocations

# 这是 AI 的主要决策函数，根据当前棋盘状态为给定棋子 nPiece 选择最佳的落子列
def pick_best_move(a_a_nBoard, nPiece):
    aValidLocations = get_valid_locations(a_a_nBoard)
    nBestScore = -10000
    if not aValidLocations: return -1
    nBestCol = random.choice(aValidLocations)
     # 初始化最佳落子列为有效列中的一个随机选择
     # 这可以增加 AI 的一些变化性，避免每次在相同分数时总是选择同一列
    for nCol in aValidLocations:
        nRow = get_next_open_row(a_a_nBoard, nCol)
        aTempBoard = [row[:] for row in a_a_nBoard]
        drop_piece(aTempBoard, nRow, nCol, nPiece)
        nScore = score_position(aTempBoard, nPiece)
        if nScore > nBestScore:
            nBestScore = nScore
            nBestCol = nCol
    return nBestCol
 # 返回找到的最佳落子列号(贪心算法)


# ---- Pygame 绘图函数 ----

def draw_board(oScreen, a_a_nBoard):
    nYOffset = TOP_BAR_HEIGHT
    for c in range(N_COLS):
        for r in range(N_ROWS):
            pygame.draw.rect(oScreen, COLOR_BLUE, (c * SQUARESIZE, nYOffset + r * SQUARESIZE, SQUARESIZE, SQUARESIZE))
            pygame.draw.circle(oScreen, COLOR_BLACK, (int(c * SQUARESIZE + SQUARESIZE / 2), int(nYOffset + r * SQUARESIZE + SQUARESIZE / 2)), RADIUS)
    for c in range(N_COLS):
        for r in range(N_ROWS):
            nCenterX = int(c * SQUARESIZE + SQUARESIZE / 2)
            nCenterY = int(nYOffset + r * SQUARESIZE + SQUARESIZE / 2)
            sPieceChar = ""
            cPieceColor = None
            if a_a_nBoard[r][c] == PIECE_PLAYER_1:
                cPieceColor = COLOR_RED
                sPieceChar = "X"
            elif a_a_nBoard[r][c] == PIECE_PLAYER_2:
                 cPieceColor = COLOR_YELLOW
                 sPieceChar = "O"
            if cPieceColor:
                pygame.draw.circle(oScreen, cPieceColor, (nCenterX, nCenterY), RADIUS)
                oPieceText = OFONT_PIECE.render(sPieceChar, 1, COLOR_PIECE_TEXT)
                oTextRect = oPieceText.get_rect(center=(nCenterX, nCenterY))
                oScreen.blit(oPieceText, oTextRect)
    pygame.display.update(0, TOP_BAR_HEIGHT, WIDTH, N_ROWS * SQUARESIZE)

def format_time(fSeconds):
    if fSeconds < 0: fSeconds = 0
    nMins = int(fSeconds // 60)
    nSecs = int(fSeconds % 60)
    return f"{nMins:02d}:{nSecs:02d}"

def draw_top_bar(oScreen, nTurn, nMouseX, bGameOver, oWinnerTextRect):
    pygame.draw.rect(oScreen, COLOR_BLACK, (0, 0, WIDTH, TOP_BAR_HEIGHT))
    nLeftMargin = 15
    nRightMargin = 15
    nTopPadding = 10
    nLineSpacing = 5
    nCurrentY = nTopPadding
    if not bGameOver:
        cPieceColor = COLOR_RED if nTurn == PLAYER_1 else COLOR_YELLOW
        sHoverChar = "X" if nTurn == PLAYER_1 else "O"
        nCircleY = TOP_BAR_HEIGHT - int(SQUARESIZE/2) + 5
        if nMouseX is not None and 0 <= nMouseX < WIDTH:
            pygame.draw.circle(oScreen, cPieceColor, (nMouseX, nCircleY), RADIUS - 5)
            oHoverText = OFONT_PIECE.render(sHoverChar, 1, COLOR_PIECE_TEXT)
            oHoverRect = oHoverText.get_rect(center=(nMouseX, nCircleY))
            oScreen.blit(oHoverText, oHoverRect)

        fP1DisplayTime = fPlayer1TotalTime
        fP2DisplayTime = fPlayer2TotalTime
        if fTurnStartTime > 0:
             if nTurn == PLAYER_1: fP1DisplayTime += (time.time() - fTurnStartTime)
             elif nTurn == PLAYER_2: fP2DisplayTime += (time.time() - fTurnStartTime)

        sTimeTextP1 = f"玩家1时间: {format_time(fP1DisplayTime)}"
        sTimeTextP2 = f"玩家2时间: {format_time(fP2DisplayTime)}"
        if nGameMode == MODE_TIMED_H_VS_H:
             sTimeTextP1 = f"玩家1剩余: {format_time(F_TIME_LIMIT_SECONDS - fP1DisplayTime)}"
             sTimeTextP2 = f"玩家2剩余: {format_time(F_TIME_LIMIT_SECONDS - fP2DisplayTime)}"

        oTimeLabelP1 = OFONT_MSG.render(sTimeTextP1, 1, COLOR_WHITE)
        oTimeLabelP2 = OFONT_MSG.render(sTimeTextP2, 1, COLOR_WHITE)
        oScreen.blit(oTimeLabelP1, (nLeftMargin, nCurrentY))
        nCurrentY += oTimeLabelP1.get_height() + nLineSpacing
        oScreen.blit(oTimeLabelP2, (nLeftMargin, nCurrentY))

        sTurnText = f"当前回合: {'玩家1 (红 X)' if nTurn == PLAYER_1 else ('玩家2 (黄 O)' if nGameMode != MODE_H_VS_AI else 'AI (黄 O)')}"
        oTurnLabel = OFONT_MSG.render(sTurnText, 1, COLOR_WHITE)
        oTurnRect = oTurnLabel.get_rect(topright=(WIDTH - nRightMargin, nTopPadding))
        oScreen.blit(oTurnLabel, oTurnRect)

        sHintText = "按 空格键 返回主菜单"
        oHintLabel = OFONT_HINT.render(sHintText, 1, COLOR_GRAY)
        oHintRect = oHintLabel.get_rect(bottomright=(WIDTH - nRightMargin, TOP_BAR_HEIGHT - 5))
        oScreen.blit(oHintLabel, oHintRect)
    else:
        if oWinnerTextRect:
            oLabel = OFONT_LARGE.render(sWinnerMessage, 1, COLOR_WHITE)
            oScreen.blit(oLabel, oWinnerTextRect)
            fRemainingTime = max(0, F_AUTO_RETURN_DELAY - (time.time() - fGameEndTime))
            sReturnHint = f"{int(fRemainingTime)}s后自动返回菜单,也可按 空格键 直接返回菜单"
            oReturnHintLabel = OFONT_MSG.render(sReturnHint, 1, COLOR_GRAY)
            oReturnHintRect = oReturnHintLabel.get_rect(center=(WIDTH/2, TOP_BAR_HEIGHT - 20))
            oScreen.blit(oReturnHintLabel, oReturnHintRect)
    pygame.display.update(0, 0, WIDTH, TOP_BAR_HEIGHT)


# 模式选择界面 (包括 H vs AI 先手选择)
def mode_selection_screen(oScreen):
    global nGameMode, nTurn 
    nVerticalMargin = 20
    nHorizontalMargin = 20
    nOptionLineHeight = OFONT_MSG.get_linesize() + 10
    nOptionsHeight = 4 * nOptionLineHeight # 主菜单选项高度
    nStarterOptionsHeight = 4 * nOptionLineHeight # 先手选择选项高度
    nMenuHeight = MENU_BAR_HEIGHT + max(nOptionsHeight, nStarterOptionsHeight) + nVerticalMargin # 取最大值

    # 调整窗口大小以适应菜单内容
    oScreen = pygame.display.set_mode((WIDTH, nMenuHeight))
    pygame.display.set_caption("四子棋 - 模式选择 (按 空格键 退出)")

    current_selection_mode = MODE_SELECT # 初始状态是选择模式

    while current_selection_mode in [MODE_SELECT, MODE_SELECT_STARTER]:
        oScreen.fill(COLOR_BLACK)
        nCurrentY = nVerticalMargin

        # State 1: 选择游戏模式
        if current_selection_mode == MODE_SELECT:
            # 绘制标题信息 
            aHeaderText = [
                "欢迎来到四子棋游戏!",
                "学生姓名：任晗", 
                "学号：2024010209",   
                "----------------------------------------------",
                "感谢老师体验游戏，求求捞一捞分数！！！ orz",
                "----------------------------------------------"
            ]
            for sLine in aHeaderText:
                oLineSurf = OFONT_MENU_TITLE.render(sLine, 1, COLOR_WHITE)
                oLineRect = oLineSurf.get_rect(topleft=(nHorizontalMargin, nCurrentY))
                oScreen.blit(oLineSurf, oLineRect)
                nCurrentY += oLineSurf.get_height() + 5
            nCurrentY += nVerticalMargin

            # 绘制模式选项 
            aOptionText = [
                ("按 1: 人类 vs 人类", MODE_H_VS_H),
                ("按 2: 人类 vs AI", MODE_SELECT_STARTER), # 按2进入先手选择
                ("按 3: 限时对战 (人类vs人类, 5分钟/人)", MODE_TIMED_H_VS_H),
                ("按 空格键: 退出游戏", -1)
            ]
            for sText, nModeValue in aOptionText:
                oOptionSurf = OFONT_MSG.render(sText, 1, COLOR_WHITE)
                oOptionRect = oOptionSurf.get_rect(topleft=(nHorizontalMargin, nCurrentY))
                oScreen.blit(oOptionSurf, oOptionRect)
                nCurrentY += oOptionSurf.get_height() + 10

        # State 2: 选择 H vs AI 先手 
        elif current_selection_mode == MODE_SELECT_STARTER:
            # 绘制先手选择标题
            oTitleSurf = OFONT_MSG.render("人类 vs AI - 选择先手:", 1, COLOR_WHITE)
            oTitleRect = oTitleSurf.get_rect(topleft=(nHorizontalMargin, nCurrentY))
            oScreen.blit(oTitleSurf, oTitleRect)
            nCurrentY += oTitleSurf.get_height() + nVerticalMargin * 2 # 较大间距

            # 绘制先手选项
            aStarterOptionText = [
                ("按 1: 玩家先手 (红 X)", PLAYER_1),
                ("按 2: AI 先手 (黄 O)", PLAYER_2),

            ]
            for sText, nStarterValue in aStarterOptionText:
                 oOptionSurf = OFONT_MSG.render(sText, 1, COLOR_WHITE)
                 oOptionRect = oOptionSurf.get_rect(topleft=(nHorizontalMargin, nCurrentY))
                 oScreen.blit(oOptionSurf, oOptionRect)
                 nCurrentY += oOptionSurf.get_height() + 10

        pygame.display.update()

        # 事件处理
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                show_exit_popup()
                pygame.quit()
                sys.exit()

            if event.type == pygame.KEYDOWN:
                # 处理模式选择输入
                if current_selection_mode == MODE_SELECT:
                    if event.key == pygame.K_1:
                        nGameMode = MODE_H_VS_H
                        nTurn = PLAYER_1 # 人人对战总是 P1 先手
                        current_selection_mode = nGameMode # 跳出循环
                    elif event.key == pygame.K_2:
                        current_selection_mode = MODE_SELECT_STARTER # 进入先手选择状态
                    elif event.key == pygame.K_3:
                        nGameMode = MODE_TIMED_H_VS_H
                        nTurn = PLAYER_1 # 限时对战总是 P1 先手
                        current_selection_mode = nGameMode # 跳出循环
                    elif event.key == pygame.K_SPACE: # 使用空格键退出
                        show_exit_popup()
                        pygame.quit()
                        sys.exit()

                # 处理先手选择输入
                elif current_selection_mode == MODE_SELECT_STARTER:
                    if event.key == pygame.K_1:
                        nTurn = PLAYER_1
                        nGameMode = MODE_H_VS_AI
                        current_selection_mode = nGameMode # 跳出循环
                    elif event.key == pygame.K_2:
                        nTurn = PLAYER_2
                        nGameMode = MODE_H_VS_AI
                        current_selection_mode = nGameMode # 跳出循环
                    elif event.key == pygame.K_r:
                        nTurn = random.choice([PLAYER_1, PLAYER_2])
                        nGameMode = MODE_H_VS_AI
                        current_selection_mode = nGameMode # 跳出循环

        # 如果已经选择了有效的游戏模式 (不再是 SELECT 或 SELECT_STARTER)
        if current_selection_mode not in [MODE_SELECT, MODE_SELECT_STARTER]:
            # 重新设置窗口大小为游戏所需的大小
            oScreen = pygame.display.set_mode(SIZE)
            pygame.display.set_caption("四子棋 - 按 空格键 返回主菜单")
            break # 退出模式选择循环


# --- 主游戏函数 ---
def main():
    global nGameMode, fTurnStartTime, fPlayer1TotalTime, fPlayer2TotalTime, fGameEndTime, sWinnerMessage, oWinnerTextRect, nTurn # nTurn 现在是全局的
    # 声明函数内需要修改的全局变量

    oScreen = pygame.display.set_mode(SIZE) # Pygame显示窗口，初始设置为游戏大小
    pygame.display.set_caption("四子棋 - 按 空格键 返回主菜单") # 设置窗口标题
    oClock = pygame.time.Clock() # 创建一个 Clock 对象，用于控制游戏的帧率

    while True: # 主程序循环
        nGameMode = MODE_SELECT 
        # mode_selection_screen 会设置全局的 nGameMode 和 nTurn
        mode_selection_screen(oScreen)

        # 游戏状态初始化 
        a_a_nBoard = create_board()
        bGameOver = False
        # nTurn 已经在 mode_selection_screen 中设置好了

        nMouseX = None
        sWinnerMessage = ""
        fPlayer1TotalTime = 0.0 # 重置计时
        fPlayer2TotalTime = 0.0
        fTurnStartTime = time.time() # 开始第一个回合的计时
        fGameEndTime = None # 重置游戏结束时间为 None
        oWinnerTextRect = None

        # 绘制初始空棋盘（包括顶部区域）
        oScreen.fill(COLOR_BLACK) # 清空整个屏幕
        draw_board(oScreen, a_a_nBoard) # 绘制棋盘部分 (Y偏移 TOP_BAR_HEIGHT)


        # 单局游戏循环
        bGameRunning = True

        while bGameRunning:
        # 进入内层循环，执行一局游戏，直到 bGameRunning 变为 False。
            oClock.tick(60) # 控制帧率

            # 在绘制顶部栏之前先更新计时，确保实时性
            draw_top_bar(oScreen, nTurn, nMouseX, bGameOver, oWinnerTextRect) # 持续更新顶部
            draw_board(oScreen,a_a_nBoard)
            
            # 处理自动返回菜单
            if bGameOver and fGameEndTime is not None:
                if time.time() - fGameEndTime >= F_AUTO_RETURN_DELAY:
                    # 达到延迟，结束本局循环，返回主菜单
                    bGameRunning = False
                    continue 

            # 事件处理 
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    # 在退出前累加当前回合时间 (如果计时已开始)
                    if fTurnStartTime > 0 and not bGameOver:
                         fTurnDuration = time.time() - fTurnStartTime
                         if nTurn == PLAYER_1: fPlayer1TotalTime += fTurnDuration
                         else: fPlayer2TotalTime += fTurnDuration
                    show_exit_popup() # 退出前显示弹窗
                    pygame.quit()
                    sys.exit()

                if event.type == pygame.MOUSEMOTION and not bGameOver:
                    nMouseX = event.pos[0] # 获取鼠标在顶部的 X 坐标用于悬停显示

                if event.type == pygame.MOUSEBUTTONDOWN and not bGameOver:
                    nMouseX = event.pos[0] # 点击时获取 X 坐标

                    nCol = nMouseX // SQUARESIZE # 直接根据X坐标计算列

                    if 0 <= nCol < N_COLS: # 确保计算出的列在有效范围内
                        bIsPlayerTurn = (nGameMode != MODE_H_VS_AI) or \
                                        (nGameMode == MODE_H_VS_AI and nTurn == PLAYER_1)

                        if bIsPlayerTurn: # 仅当是人类玩家回合时处理落子点击
                            if is_valid_location(a_a_nBoard, nCol):
                                # 累加回合时间
                                if fTurnStartTime > 0:
                                     fTurnDuration = time.time() - fTurnStartTime
                                     if nTurn == PLAYER_1:
                                         fPlayer1TotalTime += fTurnDuration
                                     else:
                                         fPlayer2TotalTime += fTurnDuration
                                fTurnStartTime = 0

                                # 落子 
                                nRow = get_next_open_row(a_a_nBoard, nCol)
                                nPiece = PIECE_PLAYER_1 # 默认P1
                                if nGameMode == MODE_H_VS_H or nGameMode == MODE_TIMED_H_VS_H:
                                     nPiece = PIECE_PLAYER_1 if nTurn == PLAYER_1 else PIECE_PLAYER_2
                                elif nGameMode == MODE_H_VS_AI:
                                     nPiece = PIECE_PLAYER_1 # H vs AI 点击总是 P1

                                drop_piece(a_a_nBoard, nRow, nCol, nPiece)
                                draw_board(oScreen, a_a_nBoard) # 重绘棋盘部分

                                # 检查胜利/平局/超时 
                                if check_win(a_a_nBoard, nPiece):
                                    sWinnerMessage = f"{'玩家1 (红 X)' if nPiece == PIECE_PLAYER_1 else '玩家2 (黄 O)'} 获胜!"
                                    bGameOver = True
                                elif is_board_full(a_a_nBoard):
                                    sWinnerMessage = "平局!"
                                    bGameOver = True
                                if nGameMode == MODE_TIMED_H_VS_H and not bGameOver:
                                    if fPlayer1TotalTime >= F_TIME_LIMIT_SECONDS:
                                        sWinnerMessage = "玩家 1 超时, 玩家 2 (黄 O) 获胜!"
                                        bGameOver = True
                                    elif fPlayer2TotalTime >= F_TIME_LIMIT_SECONDS:
                                        sWinnerMessage = "玩家 2 超时, 玩家 1 (红 X) 获胜!"
                                        bGameOver = True

                                # 切换回合 (如果游戏未结束)
                                if not bGameOver:
                                    if nGameMode == MODE_H_VS_H or nGameMode == MODE_TIMED_H_VS_H:
                                         nTurn = (nTurn + 1) % 2
                                    elif nGameMode == MODE_H_VS_AI:
                                         nTurn = PLAYER_2
                                    fTurnStartTime = time.time()

                            else:
                                # 列满弹窗提示 (使用列字母 A-G)
                                sColLetter = chr(ord('A') + nCol)
                                show_message_popup("提示", f"选择的列 ({sColLetter}) 已满，请选择其他列。")
                        # else: 非人类玩家回合，点击无效
                    # else: 计算出的列超出范围 (0-6)，点击无效

                # 处理 空格键 返回主菜单
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_SPACE:
                        # 在返回前累加当前回合剩余时间 (如果计时已开始)
                        if fTurnStartTime > 0 and not bGameOver:
                             fTurnDuration = time.time() - fTurnStartTime
                             if nTurn == PLAYER_1: fPlayer1TotalTime += fTurnDuration
                             else: fPlayer2TotalTime += fTurnDuration
                        bGameRunning = False # 退出当前局，返回外层循环重选模式

            # AI 回合 
            if nGameMode == MODE_H_VS_AI and nTurn == PLAYER_2 and not bGameOver:
                 # AI 逻辑
                 if fTurnStartTime > 0:
                     fPlayer2TotalTime += (time.time() - fTurnStartTime)
                 fTurnStartTime = 0
                 pygame.time.wait(500)
                 nCol = pick_best_move(a_a_nBoard, PIECE_PLAYER_2)
                 if nCol != -1 and is_valid_location(a_a_nBoard, nCol):
                    nRow = get_next_open_row(a_a_nBoard, nCol)
                    drop_piece(a_a_nBoard, nRow, nCol, PIECE_PLAYER_2)
                    draw_board(oScreen, a_a_nBoard)
                    if check_win(a_a_nBoard, PIECE_PLAYER_2):
                        sWinnerMessage = "AI (黄 O) 获胜!"
                        bGameOver = True
                    elif is_board_full(a_a_nBoard):
                        sWinnerMessage = "平局!"
                        bGameOver = True
                    if not bGameOver:
                        nTurn = PLAYER_1
                        fTurnStartTime = time.time()


            # 游戏结束状态
            if bGameOver and fGameEndTime is None:
                fGameEndTime = time.time() # 记录结束时间
                fTurnStartTime = 0 # 游戏结束，停止计时
                oLabel = OFONT_LARGE.render(sWinnerMessage, 1, COLOR_WHITE)
                oWinnerTextRect = oLabel.get_rect(center=(WIDTH / 2, TOP_BAR_HEIGHT / 2 - 15))
                draw_top_bar(oScreen, nTurn, nMouseX, bGameOver, oWinnerTextRect)


if __name__ == '__main__':
    main() 
    pygame.quit() 
    sys.exit()
