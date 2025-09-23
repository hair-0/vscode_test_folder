income = int(input())
taxable = income - 3500
if taxable <= 0:
    tax = 0.0
else:
    brackets = [
        (500, 0.05),
        (1500, 0.1),
        (3000, 0.15),
        (15000, 0.2),
        (20000, 0.25),
        (20000, 0.3),
        (float('inf'), 0.5)
    ]
    # float('inf')表示正无穷大，float('-inf')表示负无穷大
    tax = 0.0
    remaining = taxable
    for amount, rate in brackets:
        if remaining <= 0:
            break
        current = min(amount, remaining)
        tax += current * rate
        remaining -= current
print(f"{tax:.1f}")