import tkinter as tk
from tkinter import ttk  # 用于更美观的主题化控件
from tkinter import messagebox
from tkinter import scrolledtext # 用于可滚动的历史记录区域
import random
import time

class GuessNumberGame:
    # 难度级别字典，键是显示文本，值是 (最小值, 最大值) 元组
    DIFFICULTY_LEVELS = {
        "简单 (1-50)": (1, 50),
        "中等 (1-100)": (1, 100),
        "困难 (1-200)": (1, 200)
    }

    def __init__(self, master):
        """
        初始化游戏窗口并设置游戏状态。
        """
        self.master = master
        master.title("PA10: 猜数字游戏")
        master.geometry("450x550") # 增加窗口大小以容纳新元素
        master.resizable(False, False) # 禁止改变窗口大小
        master.configure(bg='#f0f0f0') # 浅灰色背景

        # --- 样式 ---
        style = ttk.Style()
        style.theme_use('clam') 
        style.configure('TLabel', background='#f0f0f0') # 使 Label 背景匹配窗口背景
        style.configure('TFrame', background='#f0f0f0') # 使 Frame 背景匹配窗口背景
        style.configure('TRadiobutton', background='#f0f0f0') # 使 Radiobutton 背景匹配窗口背景

        # --- 游戏状态变量 ---
        self.difficulty_var = tk.StringVar(value="中等 (1-100)") # 默认难度
        self.min_range, self.max_range = self.DIFFICULTY_LEVELS[self.difficulty_var.get()]
        self.secret_number = self.generate_secret_number() # 生成秘密数字
        self.guess_count = 0 # 猜测次数计数
        self.start_time = time.time() # 记录游戏开始时间
        self.guess_history_list = [] # 存储猜测历史的列表

        # --- GUI 元素 ---

        # 标题标签
        self.title_label = ttk.Label(master, text="猜数字游戏!", font=(None, 18, "bold"))
        self.title_label.pack(pady=(10, 5))

        # --- 难度选择框架 ---
        self.difficulty_frame = ttk.Frame(master, padding=5)
        self.difficulty_frame.pack(pady=5)
        ttk.Label(self.difficulty_frame, text="难度:").grid(row=0, column=0, padx=(0, 5), sticky='w')

        col = 1
        # 为每个难度级别创建单选按钮
        for level_text in self.DIFFICULTY_LEVELS.keys():
            rb = ttk.Radiobutton(
                self.difficulty_frame,
                text=level_text,
                variable=self.difficulty_var,
                value=level_text,
                command=self.change_difficulty # 改变难度时调用重启游戏方法
            )
            rb.grid(row=0, column=col, padx=3, sticky='w')
            col += 1

        # 指导说明标签
        self.instructions_text = f"猜一个 {self.min_range} ~ {self.max_range}的数字"
        self.instructions_label = ttk.Label(master, text=self.instructions_text, wraplength=400, font=(None, 11)) # wraplength 控制文本换行宽度
        self.instructions_label.pack(pady=5)

        # --- 输入框架 ---
        self.input_frame = ttk.Frame(master)
        self.input_frame.pack(pady=10)

        # 猜测数字输入框
        self.guess_entry = ttk.Entry(self.input_frame, width=10, font=(None, 12))
        self.guess_entry.grid(row=0, column=0, padx=5)
        self.guess_entry.bind("<Return>", self.check_guess_event) # 绑定回车键事件，按下回车也提交猜测

        # 提交猜测按钮
        self.guess_button = ttk.Button(self.input_frame, text="提交猜测", command=self.check_guess)
        self.guess_button.grid(row=0, column=1, padx=5)

        # 结果显示区域
        self.result_label = ttk.Label(master, text="请输入您猜测的数字", font=(None, 12), foreground="blue") # 初始提示信息
        self.result_label.pack(pady=10)

        # --- 信息框架 (次数和计时器) ---
        self.info_frame = ttk.Frame(master)
        self.info_frame.pack(pady=5, fill='x', padx=20) # fill='x' 使框架填充水平空间

        # 猜测次数显示标签
        self.count_label = ttk.Label(self.info_frame, text="Guesses: 0", font=("Arial", 10))
        self.count_label.pack(side=tk.LEFT, padx=10) # 靠左排列

        # 计时器显示标签
        self.timer_label = ttk.Label(self.info_frame, text="Time: 0.0s", font=("Arial", 10))
        self.timer_label.pack(side=tk.RIGHT, padx=10) # 靠右排列
        self._update_timer() # 启动计时器显示更新循环

        # --- 历史记录框架 ---
        self.history_frame = ttk.LabelFrame(master, text="猜测历史", padding=10) # 带标题的框架
        self.history_frame.pack(pady=10, padx=20, fill=tk.BOTH, expand=True) # fill 和 expand 使其随窗口（如果可调整大小的话）填充并扩展

        # 可滚动的历史记录文本区域
        self.history_text = scrolledtext.ScrolledText(
            self.history_frame,
            wrap=tk.WORD, # 按单词换行
            width=40, # 宽度（字符数）
            height=6, # 高度（行数）
            font=("Consolas", 10), # 使用等宽字体便于查看对齐
            state=tk.DISABLED # 初始设置为只读
        )
        self.history_text.pack(fill=tk.BOTH, expand=True) # 填充并扩展在框架内

        # --- 重新开始按钮 ---
        self.restart_button = ttk.Button(master, text="重新开始", command=self.restart_game) # 绑定重新开始方法
        self.restart_button.pack(pady=15)

        # 初始时将焦点设置到输入框
        self.guess_entry.focus_set()
        # 打印初始秘密数字（用于调试）
        print(f"Secret number (for debugging): {self.secret_number}")


    def _update_timer(self):
        """内部方法，用于周期性更新计时器标签。"""
        if self.guess_button['state'] == tk.NORMAL: # 只在游戏进行中更新计时器
             elapsed_time = time.time() - self.start_time
             self.timer_label.config(text=f"时间: {elapsed_time:.1f}秒") # 更新时间显示
             # 安排下一次更新
             self.master.after(100, self._update_timer) # 每100毫秒（0.1秒）更新一次

    def generate_secret_number(self):
        """在当前设定的范围内生成一个新的随机秘密数字。"""
        # print(f"Generating number between {self.min_range} and {self.max_range}") # Debug print
        return random.randint(self.min_range, self.max_range)

    def change_difficulty(self):
        """处理难度改变事件并重新开始游戏。"""
        messagebox.showinfo("难度已改变", f"难度已设置为 {self.difficulty_var.get()}。游戏即将重新开始。")
        self.restart_game() # 调用重新开始方法

    def update_history(self, guess, feedback):
        """将猜测数字和反馈信息添加到历史记录列表并更新显示区域。"""
        # 将当前猜测信息格式化后添加到历史记录列表
        self.guess_history_list.append(f"猜测 {self.guess_count} 次: {guess} -> {feedback}")

        # 更新 ScrolledText 控件显示
        self.history_text.config(state=tk.NORMAL) # 启用写入
        self.history_text.delete('1.0', tk.END) # 清空之前的内容
        self.history_text.insert(tk.END, "\n".join(self.guess_history_list)) # 将历史记录列表内容插入，用换行符分隔
        self.history_text.see(tk.END) # 滚动到底部
        self.history_text.config(state=tk.DISABLED) # 再次设置为只读

    def check_guess_event(self, event):
        """处理在输入框中按下回车键的事件。"""
        self.check_guess() # 调用实际检查猜测的方法

    def check_guess(self):
        """
        验证猜测，提供反馈，更新猜测次数和历史记录。
        """
        try:
            guess = int(self.guess_entry.get()) # 获取输入框中的文本并尝试转换为整数
        except ValueError:
            # 处理非整数输入的情况
            self.result_label.config(text="输入无效。请输入一个数字。", foreground="red") # 显示错误信息
            self.guess_entry.delete(0, tk.END) # 清空输入框
            return # 结束方法执行

        # 清空输入框以便下次输入
        self.guess_entry.delete(0, tk.END)

        # 增加猜测次数计数
        self.guess_count += 1
        self.count_label.config(text=f"Guesses: {self.guess_count}") # 更新计数显示

        feedback = "" # 初始化反馈信息字符串
        # 将猜测数字与秘密数字进行比较
        if guess < self.min_range or guess > self.max_range:
             feedback = f"超出范围 ({self.min_range}-{self.max_range})!"
             self.result_label.config(text=f"超出范围，请在 {self.min_range} ~ {self.max_range}之间猜测!", foreground="orange") # 超出范围提示
        elif guess < self.secret_number:
            feedback = "猜小了!"
            self.result_label.config(text="猜小了，请再猜一次！", foreground="blue") 
        elif guess > self.secret_number:
            feedback = "猜大了!"
            self.result_label.config(text="猜大了，请再猜一次！", foreground="purple") 
        else:
            # 猜测正确
            feedback = "猜对了!"
            elapsed_time = time.time() - self.start_time # 计算总耗时
            self.result_label.config(text=f"恭喜你猜对了！ 你一共猜了 {self.guess_count} 次!", foreground="green") # 猜对提示
            self.timer_label.config(text=f"时间: {elapsed_time:.1f}秒") # 显示最终耗时

            # 猜对后禁用猜测按钮和输入框
            self.guess_button.config(state=tk.DISABLED)
            self.guess_entry.config(state=tk.DISABLED)

            # 显示一个成功的消息框
           
            messagebox.showinfo("你赢了！", f"正确答案是 {self.secret_number}。你猜了{self.guess_count} 次， 共用时 {elapsed_time:.1f} 秒。")
            # 猜对后，计时器更新循环会因为按钮状态改变而停止调度

        # 在确定反馈信息后更新历史记录
        self.update_history(guess, feedback)


    def restart_game(self):
        """根据选择的难度重置游戏状态以开始新一轮。"""
        # 根据选定的难度更新数字范围
        self.min_range, self.max_range = self.DIFFICULTY_LEVELS[self.difficulty_var.get()]
        # 更新指导说明文本
        self.instructions_text = f"猜一个 {self.min_range} ~ {self.max_range}的数字"
        self.instructions_label.config(text=self.instructions_text)

        # 生成新的秘密数字并重置状态变量
        self.secret_number = self.generate_secret_number()
        self.guess_count = 0
        self.guess_history_list.clear() # 清空历史记录列表
        self.start_time = time.time() # 重置计时器开始时间

        # 重置 GUI 元素显示
        self.result_label.config(text="新游戏已开始！请输入您猜测的数字。", foreground="navy") # 重置结果提示
        self.count_label.config(text="Guesses: 0") # 重置猜测次数显示
        self.timer_label.config(text="Time: 0.0s") # 重置计时器显示
        self.guess_entry.delete(0, tk.END) # 清空输入框

        # 清空历史记录显示区域
        self.history_text.config(state=tk.NORMAL) # 暂时启用写入
        self.history_text.delete('1.0', tk.END) # 清空内容
        self.history_text.config(state=tk.DISABLED) # 再次设置为只读

        # 重新启用猜测按钮和输入框
        self.guess_button.config(state=tk.NORMAL)
        self.guess_entry.config(state=tk.NORMAL)

        # 将焦点重新设置到输入框
        self.guess_entry.focus_set()
        # 重新启动计时器更新（如果在猜对时停止了）
        self._update_timer()
        # 打印新的秘密数字（用于调试）
        print(f"New secret number generated (for debugging): {self.secret_number}")


# --- 主程序执行入口 ---
if __name__ == "__main__":
    root = tk.Tk() # 创建 Tkinter 根窗口
    game_app = GuessNumberGame(root) # 创建游戏应用实例
    # root.mainloop() 启动 Tkinter 事件循环，使窗口保持显示和响应
    root.mainloop()
    