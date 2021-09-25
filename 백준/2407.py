n, r = map(int, input().split())
dp = [[0] * 101 for _ in range(101)]

for i in range(101):
  dp[i][1] = i
  dp[i][i] = 1

def comb(n, r):
  if(dp[n][r] != 0):
    return dp[n][r]

  dp[n][r] = comb(n-1, r-1) + comb(n-1, r)
  return dp[n][r]

print(comb(n, r))