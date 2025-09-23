import sys

memo = {}

def solve_stair_climbing(n):
    if n < 0:
        return 0
    if n == 0:
        return 1

    if n in memo:
        return memo[n]

    result = solve_stair_climbing(n - 1) + solve_stair_climbing(n - 2) + solve_stair_climbing(n - 3)

    memo[n] = result
    return result

try:
    N = int(sys.stdin.readline().strip())

    result = solve_stair_climbing(N)

    print(result)

except ValueError:
    pass
