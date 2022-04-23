def change_to_int(lst):
    for i in range(len(lst)):
        lst[i] = int(lst[i])
    return lst

def add_func(data1, data2):
    i = 0
    j = 0
    data3 = []
    while (i < len(data1) and j < len(data2)):
        if data1[i + 1] == data2[j + 1]:
            data3.append(data1[i] + data2[j])
            data3.append(data1[i + 1])
            i += 2
            j += 2
        elif data1[i + 1] > data2[j + 1]:
            data3.append(data1[i])
            data3.append(data1[i + 1])
            i += 2
        else:
            data3.append(data2[j])
            data3.append(data2[j + 1])
            j += 2
    if i > len(data1) and j > len(data2):
        return data3
    elif i > len(data1):
        while j < len(data2):
            data3.append(data1[j])
            data3.append(data1[j + 1])
            j += 2
    else:
        while i < len(data1):
            data3.append(data1[i])
            data3.append(data1[i + 1])
            i += 2
    return data3

def check_degree(lst, degree):
    for i in range(1, len(lst), 2):
        if lst[i] == degree:
            return i - 1
    return 0

def sort_data(lst):
    new_lst = []
    for i in range(0, len(lst), 2):
        tup = (lst[i],lst[i + 1])
        new_lst.append(tup)
    new_lst = sorted(new_lst, key = lambda x : x[1], reverse=True)
    j = 0
    for i in range(len(new_lst)):
        lst[j] = new_lst[i][0]
        lst[j + 1] = new_lst[i][1]
        j += 2
    return lst

def mul_func(data1, data2):
    i = 0
    data4 = []
    while (i < len(data1)):
        j = 0
        while (j < len(data2)):
            index = check_degree(data4, data1[i+1] + data2[j+1])
            if (index != 0):
                data4[index] += data1[i]*data2[j]
            else:
                data4.append(data1[i]*data2[j])
                data4.append(data1[i+1] + data2[j+1])
            j+=2
        i+=2
    return sort_data(data4)

data1 = input("수식 1을 입력하세요 : ").split(' ')
data2 = input("수식 2을 입력하세요 : ").split(' ')
data1 = change_to_int(data1)
data2 = change_to_int(data2)

data3 = add_func(data1, data2)
data4 = mul_func(data1, data2)
print("수식 1 + 2 는 ", end = "")
for i in data3:
    print(i, end = " ")
print("\n수식 1 * 2 는 ",end ="")
for i in data4:
    print(i, end = " ")
print("")
num = input("수식에 값을 넣으세요 ").split(' ')
result = 0
if num[0] == '1':
    for i in range(0, len(data1), 2):
        result += int(num[1]) ** data1[i+1] * data1[i]
elif num[0] == '2':
    for i in range(0, len(data2), 2):
        result += int(num[1]) ** data2[i+1] * data2[i]
elif num[0] == '3':
    for i in range(0, len(data3), 2):
        result += int(num[1]) ** data3[i+1] * data3[i]
elif num[0] == '4':
    for i in range(0, len(data4), 2):
        result += int(num[1]) ** data4[i+1] * data4[i]
else:
    print("입력값이 잘못되었습니다.")

print("결과값은",result)
