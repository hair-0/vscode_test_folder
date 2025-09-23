# 该文件使用的编码方式为 utf-8
# 导入模块部分
import sys
import pygame
# 此代码基于pygame库进行开发
import math
import random
# 多个位置分数相同时随机选一个（ai部分贪心算法会用到）
import time
import tkinter as tk
from tkinter import messagebox
#用于创建消息对话框
import os
#与操作系统交互

os.environ['SDL_VIDEO_CENTERED'] = '1'

'''
经上网查询，设置环境变量 'SDL_VIDEO_CENTERED' 的值为 '1'，
这个设置会告诉 SDL（Pygame底层使用的库） 在启动窗口时尝试将其放置在屏幕中央。
'''

#---------------------------------------------------------------------------------------

# 此程序大部分的常量和变量命名规律采用cwj老师课上提到的匈牙利命名法 

# --- 常量定义 ---

n_rows = 6
n_cols = 7
n_win_length = 4  # 胜利条件
player_1 = 0
player_2 = 1
piece_empty = 0  # 表示棋盘格子里为空的状态(0)
piece_player_1 = 1
piece_player_2 = 2

squaresize = 100  # 棋盘上每个正方形格子的边长（100像素）
width = n_cols * squaresize
menu_bar_height = 200 # 菜单顶部标题高度
top_bar_height = 100 # 游戏界面的顶部操作栏高度
height = n_rows * squaresize + top_bar_height 
size = (width, height)
radius = int(squaresize / 2 - 10) # 棋子半径的设置，略小于格子边长的一半
# 颜色常量
color_blue = (0, 0, 255)
color_black = (0, 0, 0)
color_red = (255, 0, 0)
color_yellow = (255, 255, 0)
color_white = (255, 255, 255)
color_gray = (180, 180, 180)
color_piece_text = color_black
#游戏模式定义
mode_select = 0 # 模式选择界面
mode_h_vs_h = 1
mode_h_vs_ai = 2
mode_timed_h_vs_h = 3
mode_select_starter = -2 # 选择 玩家 vs AI 的先手

f_time_limit_seconds = 300.0 
f_auto_return_delay = 10.0   # 游戏结束后10s自动返回菜单延迟


# --- 全局变量 ---
ngamemode = mode_select 
fturnstarttime = 0.0 # 回合开始时间戳
fplayer1totaltime = 0.0
fplayer2totaltime = 0.0
fgameendtime = None # 游戏结束时间戳，结束时赋值
owinnertextrect = None # 用于存储游戏结束时显示的胜利/平局消息文本表面的矩形对象 (pygame.Rect)。
swinnermessage = "" # 存储游戏结束时显示的胜利/平局消息字符串。初始化为空字符串。
nturn = player_1 

#--------------------------------------------------------------------------------------------------------------

pygame.init()

# 字体初始化，使用默认字体
font_file_path_msg = None
font_file_path_large = None
font_file_path_piece = None

# 鲁棒性。默认失败就尝试加载备选字体。
try:
    ofont_menu_title = pygame.font.Font(font_file_path_msg, 24) if font_file_path_msg else pygame.font.SysFont("SimHei", 24)
    # 菜单标题的字体
    ofont_msg = pygame.font.Font(font_file_path_msg, 28) if font_file_path_msg else pygame.font.SysFont("SimHei", 28)
    # 普通消息和菜单选项的字体
    ofont_piece = pygame.font.Font(font_file_path_piece, 50) if font_file_path_piece else pygame.font.SysFont("Arial Bold", 50)
    # 棋子上的文字（'X', 'O'）
    ofont_large = pygame.font.Font(font_file_path_large, 70) if font_file_path_large else pygame.font.SysFont("SimHei", 70)
    # 游戏结束消息的字体    
    ofont_hint = pygame.font.Font(font_file_path_msg, 20) if font_file_path_msg else pygame.font.SysFont("SimHei", 20)
    # 游戏界面提示文本的字体

# 如果文件找不到，也回退到使用 Pygame 默认字体。同上
except FileNotFoundError as e:
     print(f"警告：找不到指定的字体文件 ({e})，尝试使用默认字体，中文可能显示为方框。")
     ofont_menu_title = pygame.font.SysFont(None, 28)
     ofont_msg = pygame.font.SysFont(None, 28)
     ofont_piece = pygame.font.SysFont(None, 60)
     ofont_large = pygame.font.SysFont(None, 75)
     ofont_hint = pygame.font.SysFont(None, 20)

#--------------------------------------------------------------------------------------------------------

# --- Tkinter Pop-up 弹窗函数 ---
def show_message_popup(title, message):
    """
    用于显示一个通用的 Tkinter 消息弹窗。
    """
    try:
        popup_root = tk.Tk() 
        popup_root.withdraw() # 隐藏根窗口
        popup = tk.Toplevel(popup_root) 
        popup.title(title) # 设置弹窗的标题
        popup.attributes('-topmost', True) # 设置弹窗属性，使其始终显示在最顶层。

        win_width = 650
        win_height = 200
        screen_width = popup.winfo_screenwidth()
        screen_height = popup.winfo_screenheight()

        # 计算弹窗居中显示时的左上角坐标。
        x = (screen_width / 2) - (win_width / 2)
        y = (screen_height / 2) - (win_height / 2)
        # 设置弹窗的大小和位置 (格式为 "宽x高+x+y")。
        popup.geometry('%dx%d+%d+%d' % (win_width, win_height, x, y))
        try:
       # 尝试使用自定义字体创建标签。
            custom_font = ("SimHei", 24)
            message_label = tk.Label(popup, text=message, font=custom_font, pady=40)
            # 创建一个 Label 组件显示消息文本，设置字体和垂直内边距。
        except tk.TclError:
             message_label = tk.Label(popup, text=message, pady=20)
        message_label.pack()
        ok_button = tk.Button(popup, text="确定", command=lambda: [popup.destroy(), popup_root.destroy()])
        # 创建一个 Button (确认按钮)。command 参数指定点击按钮时执行的动作
        # 使用 lambda 匿名函数，调用 popup.destroy() 关闭弹窗，然后调用 popup_root.destroy() 关闭隐藏的根窗口。
        ok_button.pack(pady=5) # 使用 pack 布局管理器将 Button 放置到弹窗中，并设置垂直内边距。
        popup.wait_window(popup) # 使程序暂停，直到弹窗被关闭。这是确保弹窗显示并等待用户交互的关键。
        try: popup_root.destroy()
        except: pass
        # 在弹窗关闭后，再次尝试销毁根窗口，以防 lambda 命令未能完全清理。使用 try 避免在 popup_root 已经销毁时报错。
    except Exception as e:
        print(f"Tkinter 弹窗出错: {e}")
        print(f"{title}: {message}")

def show_exit_popup():
    """
    显示退出信息弹窗
    """
    show_message_popup("游戏结束", "感谢cwj老师体验四子棋游戏,\n求求老师捞一捞分数!!! orz")


#-------------------------------------------------------------------------------------------------------------------------------

# --- 游戏逻辑函数 (游戏核心逻辑函数) ---

def create_board():
    a_a_nboard = [[piece_empty for _ in range(n_cols)] for _ in range(n_rows)]
     # 二维列表 (a_a_nboard)中的每个元素都初始化为 piece_empty (0)，代表空位。
    return a_a_nboard
def is_valid_location(a_a_nboard, ncol_param):# 检查给定列 ncol_param 是否是有效的落子位置。
    if 0 <= ncol_param < n_cols: # 首先检查列号 ncol_param 是否在有效范围内 (0 到 n_cols-1)。
        bisvalid = a_a_nboard[0][ncol_param] == piece_empty
        # 如果列号有效，检查该列的最顶层 (索引为 0 的行) 是否为空。只要最上面有空位，下面就一定有空位。
        return bisvalid
    return False
def get_next_open_row(a_a_nboard, ncol_param):
    for nrow_param in range(n_rows - 1, -1, -1):
        if a_a_nboard[nrow_param][ncol_param] == piece_empty:
            return nrow_param
    return -1 # 若遍历完所有行都没有找到空位（即该列已满），返回 -1。
def drop_piece(a_a_nboard, nrow_param, ncol_param, npiece_param):
    if 0 <= nrow_param < n_rows and 0 <= ncol_param < n_cols:
        a_a_nboard[nrow_param][ncol_param] = npiece_param

# 检查胜利条件
def check_win(a_a_nboard, npiece_param):
    # 水平方向
    for nrow_local in range(n_rows):
        for ncol_local in range(n_cols - (n_win_length - 1)):
            if all(a_a_nboard[nrow_local][ncol_local + i] == npiece_param for i in range(n_win_length)):
                return True
    # 垂直方向
    for ncol_local in range(n_cols):
        for nrow_local in range(n_rows - (n_win_length - 1)):
            if all(a_a_nboard[nrow_local + i][ncol_local] == npiece_param for i in range(n_win_length)):
                return True
    # 主对角线
    for nrow_local in range(n_rows - (n_win_length - 1)):
        for ncol_local in range(n_cols - (n_win_length - 1)):
            if all(a_a_nboard[nrow_local + i][ncol_local + i] == npiece_param for i in range(n_win_length)):
                return True
    # 副对角线
    for nrow_local in range(n_win_length - 1, n_rows):
        for ncol_local in range(n_cols - (n_win_length - 1)):
            if all(a_a_nboard[nrow_local - i][ncol_local + i] == npiece_param for i in range(n_win_length)):
                return True
    return False

# 检查棋盘是否已满（平局）
def is_board_full(a_a_nboard):
    for ncol_local in range(n_cols):
        if a_a_nboard[0][ncol_local] == piece_empty:
            return False
    return True



#--- AI 相关函数 ---
# 贪心算法
def evaluate_window(awindow_param, npiece_param):
    nscore_local = 0
    nopponentpiece_local = piece_player_1 if npiece_param == piece_player_2 else piece_player_2
    ncountpiece_local = awindow_param.count(npiece_param)
    ncountempty_local = awindow_param.count(piece_empty)
    ncountopponent_local = awindow_param.count(nopponentpiece_local)

    # 根据不同数量的棋子和空位组合，给予不同的分数。
    if ncountpiece_local == 4: nscore_local += 1000
    # 如果己方有 4 个连子，是胜利条件，给予非常高的分数。
    elif ncountpiece_local == 3 and ncountempty_local == 1: nscore_local += 10
     # 如果己方有 3 个连子和一个空位，给予较高的分数。
    elif ncountpiece_local == 2 and ncountempty_local == 2: nscore_local += 3
    # 如果己方有 2 个连子和两个空位，给予较低的分数。
    if ncountopponent_local == 3 and ncountempty_local == 1: nscore_local -= 80
    # 如果对手有 3 个连子和一个空位，给予非常低的（负的）分数
    elif ncountopponent_local == 4: nscore_local -= 5000
     # 如果对手已经有 4 个连子，即回合失败，给予极低的（负的）分数。
    return nscore_local

# 评估整个棋盘 a_a_nboard 对于给定棋子 npiece_param 的总分数。
def score_position(a_a_nboard, npiece_param):
    nscore_local = 0
    # 偏爱中心列：在四子棋中，中心列更容易形成连接，因此优先占据中心列。
    acenterarray_local = [a_a_nboard[i][n_cols // 2] for i in range(n_rows)]
    ncentercount_local = acenterarray_local.count(npiece_param)
    nscore_local += ncentercount_local * 6 # 将中心列己方棋子的数量乘以一个权重 (6) 加到总分中。

    # 评估水平方向的所有窗口
    for r_local in range(n_rows):
        arowarray_local = [a_a_nboard[r_local][c_local] for c_local in range(n_cols)]
        for c_local in range(n_cols - (n_win_length - 1)):
            awindow_local = arowarray_local[c_local:c_local + n_win_length]
            nscore_local += evaluate_window(awindow_local, npiece_param)
    # 评估垂直方向的所有窗口
    for c_local in range(n_cols):
        acolarray_local = [a_a_nboard[r_local][c_local] for r_local in range(n_rows)]
        for r_local in range(n_rows - (n_win_length - 1)):
            awindow_local = acolarray_local[r_local:r_local + n_win_length]
            nscore_local += evaluate_window(awindow_local, npiece_param)
    # 评估主对角线方向的所有窗口
    for r_local in range(n_rows - (n_win_length - 1)):
        for c_local in range(n_cols - (n_win_length - 1)):
            awindow_local = [a_a_nboard[r_local + i][c_local + i] for i in range(n_win_length)]
            nscore_local += evaluate_window(awindow_local, npiece_param)
    # 评估副对角线方向的所有窗口
    for r_local in range(n_win_length - 1, n_rows):
        for c_local in range(n_cols - (n_win_length - 1)):
            awindow_local = [a_a_nboard[r_local - i][c_local + i] for i in range(n_win_length)]
            nscore_local += evaluate_window(awindow_local, npiece_param)
    return nscore_local

# 获取棋盘上所有可以合法落子的列的列表。
def get_valid_locations(a_a_nboard):
    avalidlocations_local = []
    for ncol_local in range(n_cols):
        if is_valid_location(a_a_nboard, ncol_local):
            avalidlocations_local.append(ncol_local)
    return avalidlocations_local

# 这是 AI 的主要决策函数，根据当前棋盘状态为给定棋子 npiece_param 选择最佳的落子列。
def pick_best_move(a_a_nboard, npiece_param):
    avalidlocations_local = get_valid_locations(a_a_nboard)
    nbestscore_local = -10000
    if not avalidlocations_local: return -1
    nbestcol_local = random.choice(avalidlocations_local)
     # 初始化最佳落子列为有效列中的一个随机选择。
     # 这可以增加 AI 的一些变化性，避免每次在相同分数时总是选择同一列。
    for ncol_local in avalidlocations_local:
        nrow_local = get_next_open_row(a_a_nboard, ncol_local)
        atempboard_local = [row[:] for row in a_a_nboard]
        drop_piece(atempboard_local, nrow_local, ncol_local, npiece_param)
        nscore_local = score_position(atempboard_local, npiece_param)
        if nscore_local > nbestscore_local:
            nbestscore_local = nscore_local
            nbestcol_local = ncol_local
    return nbestcol_local
 # 返回找到的最佳落子列号。


# ---- Pygame 绘图函数 ----

def draw_board(oscreen_param, a_a_nboard):
    nyoffset_local = top_bar_height
    for c_local in range(n_cols):
        for r_local in range(n_rows):
            pygame.draw.rect(oscreen_param, color_gray, (c_local * squaresize, nyoffset_local + r_local * squaresize, squaresize, squaresize))
            pygame.draw.circle(oscreen_param, color_black, (int(c_local * squaresize + squaresize / 2), int(nyoffset_local + r_local * squaresize + squaresize / 2)), radius)
    for c_local in range(n_cols):
        for r_local in range(n_rows):
            ncenterx_local = int(c_local * squaresize + squaresize / 2)
            ncentery_local = int(nyoffset_local + r_local * squaresize + squaresize / 2)
            spiecechar_local = ""
            cpiececolor_local = None
            if a_a_nboard[r_local][c_local] == piece_player_1:
                cpiececolor_local = color_red
                spiecechar_local = "X"
            elif a_a_nboard[r_local][c_local] == piece_player_2:
                 cpiececolor_local = color_yellow
                 spiecechar_local = "O"
            if cpiececolor_local:
                pygame.draw.circle(oscreen_param, cpiececolor_local, (ncenterx_local, ncentery_local), radius)
                opiecesurflocal = ofont_piece.render(spiecechar_local, 1, color_piece_text)
                otextrect_local = opiecesurflocal.get_rect(center=(ncenterx_local, ncentery_local))
                oscreen_param.blit(opiecesurflocal, otextrect_local)
    pygame.display.update(0, top_bar_height, width, n_rows * squaresize)

def format_time(fseconds_param):
    if fseconds_param < 0: fseconds_param = 0
    nmins_local = int(fseconds_param // 60)
    nsecs_local = int(fseconds_param % 60)
    return f"{nmins_local:02d}:{nsecs_local:02d}"

def draw_top_bar(oscreen_param, nturn_param, nmousex_param, bgameover_param, owinnertextrect_param):
    pygame.draw.rect(oscreen_param, color_black, (0, 0, width, top_bar_height))
    nleftmargin_local = 15
    nrightmargin_local = 15
    ntoppadding_local = 10
    nlinespacing_local = 5
    ncurrenty_local = ntoppadding_local
    if not bgameover_param:
        cpiececolor_local = color_red if nturn_param == player_1 else color_yellow
        shoverchar_local = "X" if nturn_param == player_1 else "O"
        ncircley_local = top_bar_height - int(squaresize/2) + 5
        if nmousex_param is not None and 0 <= nmousex_param < width:
            pygame.draw.circle(oscreen_param, cpiececolor_local, (nmousex_param, ncircley_local), radius - 5)
            ohoversurf_local = ofont_piece.render(shoverchar_local, 1, color_piece_text)
            ohoverrect_local = ohoversurf_local.get_rect(center=(nmousex_param, ncircley_local))
            oscreen_param.blit(ohoversurf_local, ohoverrect_local)

        fp1displaytime_local = fplayer1totaltime
        fp2displaytime_local = fplayer2totaltime
        if fturnstarttime > 0: # Accessing global fturnstarttime
             if nturn_param == player_1: fp1displaytime_local += (time.time() - fturnstarttime)
             elif nturn_param == player_2: fp2displaytime_local += (time.time() - fturnstarttime)

        stimetextp1_local = f"玩家1时间: {format_time(fp1displaytime_local)}"
        stimetextp2_local = f"玩家2时间: {format_time(fp2displaytime_local)}"
        if ngamemode == mode_timed_h_vs_h: # Accessing global ngamemode
             stimetextp1_local = f"玩家1剩余: {format_time(f_time_limit_seconds - fp1displaytime_local)}"
             stimetextp2_local = f"玩家2剩余: {format_time(f_time_limit_seconds - fp2displaytime_local)}"

        otimelabelp1_local = ofont_msg.render(stimetextp1_local, 1, color_white)
        otimelabelp2_local = ofont_msg.render(stimetextp2_local, 1, color_white)
        oscreen_param.blit(otimelabelp1_local, (nleftmargin_local, ncurrenty_local))
        ncurrenty_local += otimelabelp1_local.get_height() + nlinespacing_local
        oscreen_param.blit(otimelabelp2_local, (nleftmargin_local, ncurrenty_local))

        sturntext_local = f"当前回合: {'玩家1 (红 X)' if nturn_param == player_1 else ('玩家2 (黄 O)' if ngamemode != mode_h_vs_ai else 'AI (黄 O)')}"
        oturnlabel_local = ofont_msg.render(sturntext_local, 1, color_white)
        oturnrect_local = oturnlabel_local.get_rect(topright=(width - nrightmargin_local, ntoppadding_local))
        oscreen_param.blit(oturnlabel_local, oturnrect_local)

        shintsuf_local = "按 空格键 返回主菜单"
        ohintlabel_local = ofont_hint.render(shintsuf_local, 1, color_gray)
        ohintrect_local = ohintlabel_local.get_rect(bottomright=(width - nrightmargin_local, top_bar_height - 5))
        oscreen_param.blit(ohintlabel_local, ohintrect_local)
    else:
        if owinnertextrect_param:
            olabelsurf_local = ofont_large.render(swinnermessage, 1, color_white) # Accessing global swinnermessage
            oscreen_param.blit(olabelsurf_local, owinnertextrect_param)
            fremainingtime_local = max(0, f_auto_return_delay - (time.time() - fgameendtime)) # Accessing global fgameendtime
            sreturnhintsuf_local = f"{int(fremainingtime_local)}s后自动返回菜单,也可按 空格键 直接返回菜单"
            oreturnhintlabel_local = ofont_msg.render(sreturnhintsuf_local, 1, color_gray)
            oreturnhintrect_local = oreturnhintlabel_local.get_rect(center=(width/2, top_bar_height - 20))
            oscreen_param.blit(oreturnhintlabel_local, oreturnhintrect_local)
    pygame.display.update(0, 0, width, top_bar_height)


# 模式选择界面 (包括 H vs AI 先手选择)
def mode_selection_screen(oscreen_param):
    global ngamemode, nturn
    nverticalmargin_local = 20
    nhorizontalmargin_local = 20
    noptionlineheight_local = ofont_msg.get_linesize() + 10
    noptionsheight_local = 4 * noptionlineheight_local # 主菜单选项高度
    nstarteroptionsheight_local = 4 * noptionlineheight_local # 先手选择选项高度
    nmenuheight_local = menu_bar_height + max(noptionsheight_local, nstarteroptionsheight_local) + nverticalmargin_local # 取最大值

    # 调整窗口大小以适应菜单内容
    oscreen_param = pygame.display.set_mode((width, nmenuheight_local))
    pygame.display.set_caption("四子棋 - 模式选择 (按 空格键 退出)")

    current_selection_mode = mode_select

    while current_selection_mode in [mode_select, mode_select_starter]:
        oscreen_param.fill(color_black)
        ncurrenty_local = nverticalmargin_local

        # 1:选择游戏模式
        if current_selection_mode == mode_select:
            # 绘制标题信息
            aheadertext_local = [
                "欢迎来到四子棋游戏!",
                "学生姓名：",
                "学号：",
                "----------------------------------------------",
                "感谢老师体验游戏，求求捞一捞分数！！！ orz",
                "----------------------------------------------"
            ]
            for slinetext_local in aheadertext_local:
                olinesurf_local = ofont_menu_title.render(slinetext_local, 1, color_white)
                olinerect_local = olinesurf_local.get_rect(topleft=(nhorizontalmargin_local, ncurrenty_local))
                oscreen_param.blit(olinesurf_local, olinerect_local)
                ncurrenty_local += olinesurf_local.get_height() + 5
            ncurrenty_local += nverticalmargin_local

            # 绘制模式选项
            aoptiontext_local = [
                ("按 1: 人类 vs 人类", mode_h_vs_h),
                ("按 2: 人类 vs AI", mode_select_starter),
                ("按 3: 限时对战 (人类vs人类, 5分钟/人)", mode_timed_h_vs_h),
                ("按 空格键: 退出游戏", -1)
            ]
            for stext_local, nmodevalue_local in aoptiontext_local:
                ooptionsurf_local = ofont_msg.render(stext_local, 1, color_white)
                ooptionrect_local = ooptionsurf_local.get_rect(topleft=(nhorizontalmargin_local, ncurrenty_local))
                oscreen_param.blit(ooptionsurf_local, ooptionrect_local)
                ncurrenty_local += ooptionsurf_local.get_height() + 10

        # 2:选择 H vs AI 先手
        elif current_selection_mode == mode_select_starter:
            # 绘制先手选择标题
            otitlesurf_local = ofont_msg.render("人类 vs AI - 选择先手:", 1, color_white)
            otitlerect_local = otitlesurf_local.get_rect(topleft=(nhorizontalmargin_local, ncurrenty_local))
            oscreen_param.blit(otitlesurf_local, otitlerect_local)
            ncurrenty_local += otitlesurf_local.get_height() + nverticalmargin_local * 2 # 较大间距

            # 绘制先手选项
            astarteroptiontext_local = [
                ("按 1: 玩家先手 (红 X)", player_1),
                ("按 2: AI 先手 (黄 O)", player_2),

            ]
            for stext_local, nstartervalue_local in astarteroptiontext_local:
                 ooptionsurf_local = ofont_msg.render(stext_local, 1, color_white)
                 ooptionrect_local = ooptionsurf_local.get_rect(topleft=(nhorizontalmargin_local, ncurrenty_local))
                 oscreen_param.blit(ooptionsurf_local, ooptionrect_local)
                 ncurrenty_local += ooptionsurf_local.get_height() + 10

        pygame.display.update()

        # 事件处理
        for event_local in pygame.event.get():
            if event_local.type == pygame.QUIT:
                show_exit_popup()
                pygame.quit()
                sys.exit()

            if event_local.type == pygame.KEYDOWN:
                # 处理模式选择输入
                if current_selection_mode == mode_select:
                    if event_local.key == pygame.K_1:
                        ngamemode = mode_h_vs_h
                        nturn = player_1 # 人人对战总是 P1 先手
                        current_selection_mode = ngamemode # 跳出循环
                    elif event_local.key == pygame.K_2:
                        current_selection_mode = mode_select_starter # 进入先手选择状态
                    elif event_local.key == pygame.K_3:
                        ngamemode = mode_timed_h_vs_h
                        nturn = player_1 # 限时对战总是 P1 先手
                        current_selection_mode = ngamemode # 跳出循环
                    elif event_local.key == pygame.K_SPACE: # 使用空格键退出
                        show_exit_popup()
                        pygame.quit()
                        sys.exit()

                # 处理先手选择输入
                elif current_selection_mode == mode_select_starter:
                    if event_local.key == pygame.K_1:
                        nturn = player_1
                        ngamemode = mode_h_vs_ai
                        current_selection_mode = ngamemode # 跳出循环
                    elif event_local.key == pygame.K_2:
                        nturn = player_2
                        ngamemode = mode_h_vs_ai
                        current_selection_mode = ngamemode # 跳出循环
                    elif event_local.key == pygame.K_r: # 'r' was not in the original options, keeping it for consistency if it was intended
                        nturn = random.choice([player_1, player_2])
                        ngamemode = mode_h_vs_ai
                        current_selection_mode = ngamemode # 跳出循环

        # 如果已经选择了有效的游戏模式 (不再是 SELECT 或 SELECT_STARTER)
        if current_selection_mode not in [mode_select, mode_select_starter]:
            # 重新设置窗口大小为游戏所需的大小
            oscreen_param = pygame.display.set_mode(size)
            pygame.display.set_caption("四子棋 - 按 空格键 返回主菜单")
            break # 退出模式选择循环


# --- 主游戏函数 ---
def main():
    global ngamemode, fturnstarttime, fplayer1totaltime, fplayer2totaltime, fgameendtime, swinnermessage, owinnertextrect, nturn
    # 声明函数内需要修改的全局变量

    oscreen_local = pygame.display.set_mode(size) # Pygame显示窗口，初始设置为游戏大小
    pygame.display.set_caption("四子棋 - 按 空格键 返回主菜单") # 设置窗口标题
    oclock_local = pygame.time.Clock() # 创建Clock 对象，用于控制游戏的帧率

    while True: 
        ngamemode = mode_select 
        mode_selection_screen(oscreen_local)

        # 游戏状态初始化
        a_a_nboard_local = create_board()
        bgameover_local = False
        nmousex_local = None
        swinnermessage = ""
        fplayer1totaltime = 0.0 # 重置计时
        fplayer2totaltime = 0.0
        fturnstarttime = time.time() # 开始第一个回合的计时
        fgameendtime = None # 重置游戏结束时间为 None
        owinnertextrect = None

        # 绘制初始空棋盘（包括顶部区域）
        oscreen_local.fill(color_black) # 清空整个屏幕
        draw_board(oscreen_local, a_a_nboard_local) # 绘制棋盘部分 (Y偏移 top_bar_height)

        # 单局游戏循环
        bgamerunning_local = True
        while bgamerunning_local:
        # 进入内层循环，执行一局游戏，直到 bgamerunning_local 变为 False。
            oclock_local.tick(60) # 控制帧率

            # 在绘制顶部栏之前先更新计时，确保实时性
            draw_top_bar(oscreen_local, nturn, nmousex_local, bgameover_local, owinnertextrect) # 持续更新顶部
            draw_board(oscreen_local, a_a_nboard_local)

            # 处理自动返回菜单
            if bgameover_local and fgameendtime is not None:
                if time.time() - fgameendtime >= f_auto_return_delay:
                    # 达到延迟，结束本局循环，返回主菜单
                    bgamerunning_local = False
                    continue # 跳过本帧剩余逻辑 (重要!)

            # 事件处理
            for event_local in pygame.event.get():
                if event_local.type == pygame.QUIT:
                    # 在退出前累加当前回合时间 (如果计时已开始)
                    if fturnstarttime > 0 and not bgameover_local:
                         fturnduration_local = time.time() - fturnstarttime
                         if nturn == player_1: fplayer1totaltime += fturnduration_local
                         else: fplayer2totaltime += fturnduration_local
                    show_exit_popup() # 退出前显示弹窗
                    pygame.quit()
                    sys.exit()

                if event_local.type == pygame.MOUSEMOTION and not bgameover_local:
                    nmousex_local = event_local.pos[0] # 获取鼠标在顶部的 X 坐标用于悬停显示

                if event_local.type == pygame.MOUSEBUTTONDOWN and not bgameover_local:
                    nmousex_local = event_local.pos[0] # 点击时获取 X 坐标

                    ncol_local = nmousex_local // squaresize # 直接根据X坐标计算列

                    if 0 <= ncol_local < n_cols: # 确保计算出的列在有效范围内
                        # 现在，只要计算出的列有效，就继续处理落子
                        bisplayerturn_local = (ngamemode != mode_h_vs_ai) or \
                                        (ngamemode == mode_h_vs_ai and nturn == player_1)

                        if bisplayerturn_local: # 仅当是人类玩家回合时处理落子点击
                            if is_valid_location(a_a_nboard_local, ncol_local):
                                # 累加回合时间
                                if fturnstarttime > 0:
                                     fturnduration_local = time.time() - fturnstarttime
                                     if nturn == player_1:
                                         fplayer1totaltime += fturnduration_local
                                     else:
                                         fplayer2totaltime += fturnduration_local
                                fturnstarttime = 0

                                # 落子
                                nrow_local = get_next_open_row(a_a_nboard_local, ncol_local)
                                npiece_local = piece_player_1 # 默认P1
                                if ngamemode == mode_h_vs_h or ngamemode == mode_timed_h_vs_h:
                                     npiece_local = piece_player_1 if nturn == player_1 else piece_player_2
                                elif ngamemode == mode_h_vs_ai:
                                     npiece_local = piece_player_1 # H vs AI 点击总是 P1

                                drop_piece(a_a_nboard_local, nrow_local, ncol_local, npiece_local)
                                draw_board(oscreen_local, a_a_nboard_local) # 重绘棋盘部分

                                # 检查胜利/平局/超时
                                if check_win(a_a_nboard_local, npiece_local):
                                    swinnermessage = f"{'玩家1 (红 X)' if npiece_local == piece_player_1 else '玩家2 (黄 O)'} 获胜!"
                                    bgameover_local = True
                                elif is_board_full(a_a_nboard_local):
                                    swinnermessage = "平局!"
                                    bgameover_local = True
                                if ngamemode == mode_timed_h_vs_h and not bgameover_local:
                                    if fplayer1totaltime >= f_time_limit_seconds:
                                        swinnermessage = "玩家 1 超时, 玩家 2 (黄 O) 获胜!"
                                        bgameover_local = True
                                    elif fplayer2totaltime >= f_time_limit_seconds:
                                        swinnermessage = "玩家 2 超时, 玩家 1 (红 X) 获胜!"
                                        bgameover_local = True


                                # 切换回合 (如果游戏未结束)
                                if not bgameover_local:
                                    if ngamemode == mode_h_vs_h or ngamemode == mode_timed_h_vs_h:
                                         nturn = (nturn + 1) % 2
                                    elif ngamemode == mode_h_vs_ai:
                                         nturn = player_2
                                    fturnstarttime = time.time()
                            else:
                                # 列满弹窗提示 (使用列字母 A-G)
                                scolletter_local = chr(ord('A') + ncol_local)
                                show_message_popup("提示", f"选择的列 ({scolletter_local}) 已满，请选择其他列。")
                if event_local.type == pygame.KEYDOWN:
                    if event_local.key == pygame.K_SPACE:
                        # 在返回前累加当前回合剩余时间 (如果计时已开始)
                        if fturnstarttime > 0 and not bgameover_local:
                             fturnduration_local = time.time() - fturnstarttime
                             if nturn == player_1: fplayer1totaltime += fturnduration_local
                             else: fplayer2totaltime += fturnduration_local

                        bgamerunning_local = False # 退出当前局，返回外层循环重选模式

            # AI 回合
            if ngamemode == mode_h_vs_ai and nturn == player_2 and not bgameover_local:
                 # AI 逻辑
                 if fturnstarttime > 0:
                     fplayer2totaltime += (time.time() - fturnstarttime)
                 fturnstarttime = 0
                 pygame.time.wait(500) # AI思考延时
                 ncol_ai_move = pick_best_move(a_a_nboard_local, piece_player_2)
                 if ncol_ai_move != -1 and is_valid_location(a_a_nboard_local, ncol_ai_move):
                    nrow_ai_move = get_next_open_row(a_a_nboard_local, ncol_ai_move)
                    drop_piece(a_a_nboard_local, nrow_ai_move, ncol_ai_move, piece_player_2)
                    draw_board(oscreen_local, a_a_nboard_local)
                    if check_win(a_a_nboard_local, piece_player_2):
                        swinnermessage = "AI (黄 O) 获胜!"
                        bgameover_local = True
                    elif is_board_full(a_a_nboard_local):
                        swinnermessage = "平局!"
                        bgameover_local = True
                    if not bgameover_local:
                        nturn = player_1
                        fturnstarttime = time.time()

            # 游戏结束状态首次进入处理
            if bgameover_local and fgameendtime is None:
                fgameendtime = time.time() # 记录结束时间
                fturnstarttime = 0 # 停止计时
                olabelsurf_local = ofont_large.render(swinnermessage, 1, color_white)
                owinnertextrect = olabelsurf_local.get_rect(center=(width / 2, top_bar_height / 2 - 15))
                draw_top_bar(oscreen_local, nturn, nmousex_local, bgameover_local, owinnertextrect) 


if __name__ == '__main__':
    main()
    pygame.quit()
    sys.exit()