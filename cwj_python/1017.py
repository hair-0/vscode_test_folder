year=int(input())
a=year%4
b=year%100
c=year%400
if c==0:
    print("Y")
elif b==0 and c!=0:
    print('N')
elif a==0:
    print('Y')
else :
    print('N')
    

'''
year = int(input())
if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
    print("Y")
else:
    print("N")
'''