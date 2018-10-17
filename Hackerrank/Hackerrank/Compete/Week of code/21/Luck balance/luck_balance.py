n, k = map(int, input().strip().split())
lt = [tuple(map(int, input().strip().split())) for i in range(n)]
imp = [i[0] for i in sorted(filter(lambda m: m[1], lt), key=lambda x: x[0], reverse=True)]
nImp = [i[0] for i in filter(lambda r: not r[1], lt)]
luck = sum(nImp)
if k < len(imp):
    luck += sum(imp[:k])
    luck -= sum(imp[k:])
else:
    luck += sum(imp)
print(luck)
