with open('primes.txt', 'r') as data_file:
    num = data_file.read()
    num = num.split(',')
    c = 0
    with open('prime_106.txt', 'w') as op_file:
        for n in num[:100005]:
            op_file.write(n.replace('\n', '') + ',')
