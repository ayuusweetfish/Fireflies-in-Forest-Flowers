codes = []
for s in input().split():
  a = list(map(lambda w: int(w, 16), s.split('-')))
  if len(a) == 2:
    codes += list(range(a[0], a[1] + 1))
  else:
    codes.append(a[0])
print(','.join(map(str, codes)))
