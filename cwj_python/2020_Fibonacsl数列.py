def main():
    F1, F2, a, b, n = map(int, input().split())
    if n == 1:
        print(F1)
        return
    if n == 2:
        print(F2)
        return
    seq = [0] * (n + 1)
    seq[1], seq[2] = F1, F2
    for i in range(3, n + 1):
        seq[i] = a * seq[i - 2] + b * seq[i - 1]
    print(seq[n])

if __name__ == "__main__":
    main()

