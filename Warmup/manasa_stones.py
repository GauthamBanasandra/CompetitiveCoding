for test_cases in range(int(input())):
    last_stone=[]
    stones=int(input())-1
    a=int(input())
    b=int(input())
    #print('stones: ', stones, ' a: ', a, ' b: ', b)
    for stone in range(stones):
        outcome_1=a*stone+b*(stones-stone)
        outcome_2=a*(stones-stone)+b*stone
        if outcome_1 not in last_stone:
            #print('stone: ', stone, ' stones: ', stones, ' a: ', a, ' b: ', b, ' outcome_1: ', outcome_1)
            last_stone.append(outcome_1)
        if outcome_2 not in last_stone:
            #print('stone: ', stone, ' stones: ', stones, ' a: ', a, ' b: ', b, ' outcome_2: ', outcome_2)
            last_stone.append(outcome_2)
    print(' '.join(map(str, sorted(last_stone))))#Converts a list of int into a list of strings.