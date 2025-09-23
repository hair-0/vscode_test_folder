def whetherprime(n):
    if n<=1:
        return False
    if n==2:
        return True
    for i in range(3, int(n**0.5) + 1, 2):
        if n%i==0:
            return False
    return True

n = int(input())
primes = []
first = 2
while len(primes) < n:
    if whetherprime(first):
        primes.append(first)
    if first == 2:
        first +=1
    else:
        first += 2

print(sum(primes))