N, K = map(int, input().split())
dp = [[0] * 100001 for _ in range(101)]
W = [0] * 101
V= [0] * 101

for i in range(1, N+1):
  w, v = map(int, input().split())
  W[i], V[i] = w, v
  

for i in range(1,N+1):
  for j in range(0,K+1):
    if j - W[i] >= 0:
      dp[i][j] = max(dp[i-1][j], dp[i][j-W[i]]+V[i])
    else : 
      dp[i][j] = dp[i-1][j]

print(dp[N][K])