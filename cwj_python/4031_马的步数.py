# 这里我用的是递归+深度优先搜索（DFS）

def main():
    n = int(input().strip())
    start = list(map(int, input().split()))
    target = list(map(int, input().split()))
    if start == target:
        print(0)
        return
    moves = [(1, 2), (1, -2), (-1, 2), (-1, -2),
             (2, 1), (2, -1), (-2, 1), (-2, -1)]
    
    def dfs(x, y, depth, limit, visited):
        if [x, y] == target:
            return True
        if depth == limit:
            return False
        for dx, dy in moves:
            nx, ny = x + dx, y + dy
            if 1 <= nx <= n and 1 <= ny <= n and not visited[nx][ny]:
                visited[nx][ny] = True
                if dfs(nx, ny, depth + 1, limit, visited):
                    return True
                visited[nx][ny] = False
        return False

    for limit in range(n * n + 1):
        visited = [[False] * (n + 1) for _ in range(n + 1)]
        visited[start[0]][start[1]] = True
        if dfs(start[0], start[1], 0, limit, visited):
            print(limit)
            return
    print(-1)

if __name__ == "__main__":
    main()
