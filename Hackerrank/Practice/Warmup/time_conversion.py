__author__ = 'gauth_000'

time=input()
print(str(int(time[:2])+12)+time[2:-2] if 1<=int(time[:2])<12 and time[-2:]=='PM' else '00'+time[2:-2] if time[:2]=='12'and time[-2:]=='AM' else time[:-2])