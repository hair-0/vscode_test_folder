import datetime

def blackfridays(year):
    count = 0
    for month in range(1, 13):
        if datetime.date(year, month, 13).weekday() == 4:  
            count += 1
    return count

year = int(input())
print(blackfridays(year))