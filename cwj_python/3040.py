import sys

def solve():
    grid_data = [
        [2, 4, 6, 8, 9, 7, 5, 3],
        [3, 4, 6, 7, 8, 4, 3, 2],
        [5, 8, 4, 9, 0, 4, 3, 2],
        [4, 3, 2, 1, 6, 7, 8, 9],
        [4, 5, 6, 7, 8, 9, 0, 7],
        [2, 3, 4, 6, 7, 8, 9, 6],
        [1, 2, 3, 4, 5, 6, 7, 8],
        [0, 9, 8, 7, 6, 5, 4, 3]
    ]

    def get_value(r, c):
        grid_row_index = 8 - r
        grid_col_index = c - 1
        if 0 <= grid_row_index < 8 and 0 <= grid_col_index < 8:
            return grid_data[grid_row_index][grid_col_index]
        else:
            print(f"Error: Invalid coordinates ({r}, {c}) accessed.", file=sys.stderr)
            return 0

    n = int(sys.stdin.readline())

    vertices = []
    for _ in range(n):
        r, c = map(int, sys.stdin.readline().split())
        vertices.append((r, c))

    if n == 0:
        print(0)
        return
        
    if n == 1:
        r1, c1 = vertices[0]
        print(get_value(r1, c1))
        return
        
    total_sum = 0

    for i in range(n - 1):
        r_start, c_start = vertices[i]
        r_end, c_end = vertices[i+1]

        if r_start == r_end:
            r = r_start
            if c_start < c_end:
                for c in range(c_start, c_end):
                    total_sum += get_value(r, c)
            elif c_start > c_end:
                for c in range(c_start, c_end, -1):
                    total_sum += get_value(r, c)

        elif c_start == c_end:
            c = c_start
            if r_start < r_end:
                for r in range(r_start, r_end):
                    total_sum += get_value(r, c)
            elif r_start > r_end:
                for r in range(r_start, r_end, -1):
                    total_sum += get_value(r, c)

    r_last, c_last = vertices[n-1]
    total_sum += get_value(r_last, c_last)

    print(total_sum)

solve()
