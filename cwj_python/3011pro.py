def birthnum(year, month, day):
    def sum_of_digits(num):
        return sum(int(digit) for digit in str(num))
    total_sum = sum_of_digits(year) + sum_of_digits(month) + sum_of_digits(day)
    while total_sum > 9:
        total_sum = sum_of_digits(total_sum)
    return total_sum
year, month, day = map(int, input().split())
result = birthnum(year, month, day)
print(result)
