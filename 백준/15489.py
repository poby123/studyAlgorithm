r, c, w = map(int, input().split())
ans = 0
dp = [[0] * 32 for _ in range(32) ]

dp[1][1] = dp[2][1] = dp[2][2] = 1

for i in range(2, 32):
  for j in range(1, i + 1):
    dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
    # print(dp[i][j], end = ' ')
  # print()


for i in range(w):
  for j in range(i+1):
    # print(dp[r + i][c + j])
    ans += dp[r + i][c + j]

print(ans)