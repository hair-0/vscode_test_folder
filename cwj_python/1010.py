scores = input().split()
score1 = int(scores[0])
score2 = int(scores[1])
score3 = int(scores[2])

average_score = (score1 + score2 + score3) / 3
rounded_average = round(average_score)

print(rounded_average)
