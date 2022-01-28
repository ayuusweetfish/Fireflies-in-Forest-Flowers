def fact(n):
  ans = 1
  for i in range(2, n + 1): ans *= i
  return ans

def bi(n, m):
  return fact(n) // (fact(m) * fact(n - m))

n = 28
m = 6

c = [bi(n, i) for i in range(n // 2, n // 2 + m)]
s = float(c[0] + 2 * sum(c[1:]))

for i in range(m):
  factor = c[i] / s
  if i == 0:
    print('blurA += %.8f * (premul(samplePosition[%d]));' % (factor, m - 1))
  else:
    print('blurA += %.8f * (premul(samplePosition[%d]) + premul(samplePosition[%d]));'
      % (factor, m - 1 - i, m - 1 + i))
