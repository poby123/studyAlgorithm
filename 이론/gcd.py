# 큰 수에서 작은 수를 빼나가는 방법
def gcd_sub(a, b):
    while(a != 0 and b != 0):
        gcd_sub.counter += 1

        if(a > b):
            a = a - b
        else :
            b = b - a
    return a + b
gcd_sub.counter = 0

# 큰 수를 작은 수로 나눴을 때 나머지를 이용하는 방법
def gcd_remainder(a, b):
    while(a != 0 and b != 0):
        gcd_remainder.counter += 1
        if(a > b):
            a = a % b
        else :
            b = b % a
    return a + b
gcd_remainder.counter = 0

# 큰 수를 작은 수로 나누는 방법인데 재귀함수 버전
def gcd_recursive(a, b):
    gcd_recursive.counter += 1
    if(a == 0 or b == 0):
       return a + b
    elif(a > b):
        return gcd_recursive(a % b, b)
    else:
        return gcd_recursive(a, b % a)
gcd_recursive.counter = 0

# 메인 함수
if __name__ == "__main__":
    res = gcd_sub(256,1000)
    print(res, ' ', gcd_sub.counter)

    res = gcd_remainder(256, 1000)
    print(res, ' ', gcd_remainder.counter)

    res = gcd_recursive(256, 1000)
    print(res, ' ', gcd_recursive.counter)