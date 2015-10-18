__author__ = 'gauth_000'

scores=sorted([int(input()) for i in range(10)])[::-1]
team_a=scores[::2]
scores.insert(0, 0)
team_b=scores[::2][1:]
team_a=sum(team_a[:3])
team_b=sum(team_b[:3])
print(team_a) if team_a>team_b else print(team_b)