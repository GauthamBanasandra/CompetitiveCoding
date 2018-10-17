__author__ = 'gauth_000'
actual_date=list(map(int, input().strip().split()))
expected_date=list(map(int, input().strip().split()))
late_period=(actual_date[0]-expected_date[0], actual_date[1]-expected_date[1], actual_date[2]-expected_date[2])
fine=0
if late_period[2]>0:
    fine=10000
elif late_period[1]>0:
    fine=late_period[1]*500
elif late_period[0]>0:
    fine=late_period[0]*15
print(fine)