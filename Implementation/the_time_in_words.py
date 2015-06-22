__author__ = 'gauth_000'

translate_num = {0: 'o\' clock',
                 1: 'one', 2: 'two', 3: 'three', 4: 'four', 5: 'five',
                 6: 'six', 7: 'seven', 8: 'eight', 9: 'nine', 10: 'ten',
                 11: 'eleven', 12: 'twelve', 13: 'thirteen', 14: 'fourteen', 15: 'quarter',
                 16: 'sixteen', 17: 'seventeen', 18: 'eighteen', 19: 'nineteen', 20: 'twenty',
                 21: 'twenty one', 22: 'twenty two', 23: 'twenty three', 24: 'twenty four', 25: 'twenty five',
                 26: 'twenty six', 27: 'twenty seven', 28: 'twenty eight', 29: 'twenty nine', 30: 'half'}
hours = int(input())
minutes = int(input())

if minutes == 0:
    print(translate_num[hours], translate_num[minutes])
elif minutes < 30:
    if minutes == 1:
        print(translate_num[minutes], 'minute past', translate_num[hours])
    elif minutes == 15:
        print(translate_num[minutes], 'past', translate_num[hours])
    else:
        print(translate_num[minutes], 'minutes past', translate_num[hours])
elif minutes > 30:
    minutes = 60 - minutes
    if minutes == 1:
        print(translate_num[minutes], 'minute to', translate_num[hours + 1])
    elif minutes == 15:
        print(translate_num[minutes], 'to', translate_num[hours + 1])
    else:
        print(translate_num[minutes], 'minutes to', translate_num[hours + 1])
else:
    print(translate_num[minutes], 'past', translate_num[hours])
