def solve():
    scores_str = input().split()
    scores = [int(s) for s in scores_str]

    scores.sort()

    valid_scores = scores[1:-1]

    average = sum(valid_scores) / len(valid_scores)

    rounded_average = int(average + 0.5)

    print(rounded_average)

solve()