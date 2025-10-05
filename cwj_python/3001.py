def main():
    n=int(input())
    nums=[]
    for _ in range(n):
        nums.append(int(input()))
    count_time={}
    for num in nums:
        count_time[num]=count_time.get(num,0)+1
    max_count=-1
    result=float('inf')
    for num,count in count_time.items():
        if count > max_count or (count==max_count and num< result):
            max_count=count
            result=num


    print (result)
if __name__=="__main__":
    main()