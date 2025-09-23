import math 

x, y = map(int, input().split())
max_divisors = math.gcd(x, y)

def common_divisors(n):
    divisors = set()
    for i in range(1, int(n**0.5) + 1):  
        if n % i == 0:  
            divisors.add(i)
            divisors.add(n // i)  
    return divisors 

print(sum(common_divisors(max_divisors)))
