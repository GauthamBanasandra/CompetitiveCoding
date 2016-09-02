import threading as t


def count_factors(start, stop):
    count = 0
    for f in range(start, stop):
        if nsq % f == 0 and n % f != 0:
            count += 1
    counts.append(count)


n = int(input())
counts = []
nsq = n ** 2
t1 = t.Thread(target=count_factors, args=(2, n // 2))
t2 = t.Thread(target=count_factors, args=(n // 2, n))
t1.start()
t2.start()
t1.join()
t2.join()
print(sum(counts))
