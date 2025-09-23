n = int(input())

intervals = []
for _ in range(n):
    start, end = map(int, input().split())
    intervals.append([start, end])

intervals.sort()

merged_intervals = []

if intervals:
    merged_intervals.append(intervals[0])

    for current_interval in intervals[1:]:
        last_merged_interval = merged_intervals[-1]

        if current_interval[0] <= last_merged_interval[1]:
            last_merged_interval[1] = max(last_merged_interval[1], current_interval[1])
        else:
            merged_intervals.append(current_interval)

for interval in merged_intervals:
    print(interval[0], interval[1])
    