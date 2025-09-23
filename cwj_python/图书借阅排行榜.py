def main():
    n = int(input().strip())
    category_durations = {}
    for _ in range(n):
        line = input().strip()
        if not line:
            continue
        parts = line.split()
        category = parts[0]
        duration = int(parts[1])
        category_durations[category] = category_durations.get(category, 0) + duration
    sorted_categories = sorted(category_durations.items(), key=lambda x: (-x[1], x[0]))
    for i in range(min(3, len(sorted_categories))):
        category, total_duration = sorted_categories[i]
        print(category, total_duration)

if __name__ == '__main__':
    main()
