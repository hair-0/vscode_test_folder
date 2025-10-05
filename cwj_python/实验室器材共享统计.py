def main():
    n = int(input().strip())
    groups = []
    for _ in range(n):
        instruments = input().strip().split()
        groups.append(set(instruments))
    common = sorted(set.intersection(*groups)) if groups else []
    freq = {}
    for group in groups:
        for instrument in group:
            freq[instrument] = freq.get(instrument, 0) + 1
    unique = sorted([instrument for instrument, count in freq.items() if count == 1])
    print(" ".join(common) if common else "None")
    print(" ".join(unique) if unique else "None")

if __name__ == '__main__':
    main()
