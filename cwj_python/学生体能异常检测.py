def main():
    import math
    n = int(input().strip())
    records_by_day = []
    for _ in range(n):
        line = input().strip().split()
        m = int(line[0])
        daily_records = {}
        for i in range(m):
            name = line[1 + i * 2]
            temperature = float(line[2 + i * 2])
            if name in daily_records:
                daily_records[name] = max(daily_records[name], temperature)
            else:
                daily_records[name] = temperature
        records_by_day.append(daily_records)
    student_records = {}
    for day, daily_records in enumerate(records_by_day):
        for name, temperature in daily_records.items():
            if name not in student_records:
                student_records[name] = {}
            student_records[name][day] = temperature
    eligible_students = []
    for name, days in student_records.items():
        sorted_days = sorted(days.keys())
        for i in range(len(sorted_days) - 1):
            if sorted_days[i + 1] - sorted_days[i] == 1:
                eligible_students.append(name)
                break
    eligible_students = sorted(eligible_students)
    max_temperature = -math.inf
    for name in eligible_students:
        for temp in student_records[name].values():
            max_temperature = max(max_temperature, temp)
    print(" ".join(eligible_students))
    print(f"{max_temperature:.1f}")

if __name__ == '__main__':
    main()
