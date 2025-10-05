def alpha_product(x):  
    while x >= 10:  
        product = 1  
        temp = x  
        while temp:  
            digit = temp % 10  
            if digit != 0:  
                product *= digit  
            temp //= 10  
        x = product  
    return x  

if __name__ == '__main__':  
    n = int(input().strip())  
    print(alpha_product(n))  