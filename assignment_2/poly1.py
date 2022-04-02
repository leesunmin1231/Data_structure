def add_func(data1, data2):
    data3 = []
    for i in range(len(data1)):
        data1[i] = int(data1[i])
        data3.append(data1[i])
    for i in range(len(data2)):
        data2[i] = int(data2[i])
        data3[i] += data2[i]
    return (data3)

def mul_func(data1, data2):
    data4 = []
    for i in range(len(data1) + len(data2) - 1):
        data4.append(0)
    for i in range(len(data1)):
        for j in range(len(data2)):
            data4[i+j] += data1[i] * data2[j]
    return(data4)

data1 = input("수식 1을 입력하세요 : ").split(' ')
data2 = input("수식 2를 입력하세요 : ").split(' ')
data1.reverse()
data2.reverse()

if len(data1) > len(data2):
    data3 = add_func(data1, data2)
else:
    data3 = add_func(data2, data1)
data4 = mul_func(data1, data2)

print("수식 1 + 2 는 ",end = "")
for i in (list(reversed(data3))):
    print(i, end = ' ')
print("\n수식 1 * 2 는 ", end = "")
for i in (list(reversed(data4))):
    print(i, end = " ")
print("")

num = input("수식에 값을 넣으세요: ").split(' ')
result = 0
if num[0] == '1':
    for i in range(len(data1)):
        result += int(num[1]) ** i * data1[i]
elif num[0] == '2':
    for i in range(len(data2)):
        result += int(num[1]) ** i * data2[i]
elif num[0] == '3':
    for i in range(len(data3)):
        result += int(num[1]) ** i * data3[i]
elif num[0] == '4':
    for i in range(len(data4)):
        result += int(num[1]) ** i * data4[i]
else:
    print("입력값이 잘못되었습니다.")

print("결과값은",result)
