def reverse_num(n):
    return int(str(n)[::-1])  

def invert_num(a, b):
    reverse_a = reverse_num(a)
    reverse_b = reverse_num(b)
    sum_reverse = reverse_a + reverse_b
    
    reverse_sum = reverse_num(sum_reverse)
    
    return reverse_sum

a, b = map(int, input().split())
result = invert_num(a, b)
print(result)
