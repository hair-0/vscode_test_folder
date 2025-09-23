money=int(input())
ts=money-3500
tax50=ts-60000
tax30=ts-40000
tax25=ts-20000
tax20=ts-5000
tax15=ts-2000
tax10=ts-500
tax5=ts
if money<=3500:
    print(0.0)
elif ts<=500:
    tax=tax5*0.05
    print(round(tax,1))
elif ts>=500 and ts<=2000:
    tax=500*0.05+tax10*0.1
    print(round(tax,1))
elif ts>2000 and ts<=5000:
    tax=500*0.05+1500*0.1+tax15*0.15
    print(round(tax,1))
elif ts>5000 and ts <=20000:
    tax=500*0.05+1500*0.1+3000*0.15+tax20*0.2
    print(round(tax,1))
elif ts>20000 and ts<=40000:
    tax=(500*0.05+1500*0.1+3000*0.15+15000*0.2)+tax25*0.25
    print(round(tax,1))
elif ts>40000 and ts<=60000:
    tax=(500*0.05+1500*0.1+3000*0.15+15000*0.2+20000*0.25)+tax30*0.3
    print(round(tax,1))
elif ts>60000 :
    tax=(500*0.05+1500*0.1+3000*0.15+15000*0.2+20000*0.25+20000*0.3)+tax50*0.5
    print(round(tax,1))


'''
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
    tax = 0.0
    remaining = taxable
    for amount, rate in brackets:
        if remaining <= 0:
            break
        current = min(amount, remaining)
        tax += current * rate
        remaining -= current
print(f"{tax:.1f}")
'''