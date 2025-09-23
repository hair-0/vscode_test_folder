def count(s):
    if not s:
        return 0
    '''1.空字符串处理: 添加显式的空字符串检查，
        如果输入字符串为空，则直接返回 0，因为空字符串中不存在升序片段。
       2.max_num 初始化: 对于非空字符串，最少也会有一个长度为 1 的升序片段
       （即单个字符本身）。因此，将 max_num 初始化为 1 更符合逻辑。
    '''
    now_num = 1
    max_num = 1

    for i in range(1, len(s)):
        if s[i-1]<=s[i]:
            now_num+=1
        else:
            max_num=max(max_num,now_num)
            now_num=1
    max_num=max(max_num,now_num)
    return max_num

s=input()
print(count(s))