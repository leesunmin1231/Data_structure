def get_wall(line):
    # '+' ' ' = a, '+' '-' = b, '|' ' ' = c
    lst=[]
    i = 1
    while(i < len(line)-2):
        if (line[i] == '-' and line[i]==line[i-1]):
            if (i>1 and line[i-1]==line[i-2]):
                lst[-1] = str(int(lst[-1])+1)
            else:
                lst.pop()
                lst.append("2")
        elif (line[i] == '+' and line[i+1] == ' '):
            lst.append("a")
            i+=1
        elif (line[i] == '+' and line[i+1] == '-' and line[i+2] != '-'):
            lst.append("b")
            i+=1
        elif (line[i] == '|' and line[i+1] == ' '):
            lst.append('c')
            i+=1
        else:
            lst.append(line[i])
        i+=1
    return(lst)

def get_road(line):
    lst=[]
    for i in range(1, len(line)-2):
        if (line[i] == '|'):
            lst.append(i)
    return(lst)

def draw_updown(maze, index, width):
    print("+", end="")
    for i in range(1, width-1):
        if(i in maze[index]):
            print("+", end="")
        else:
            print("-", end="")
    print("+")

def draw_wall(line):
    if (line[0].isdigit() or line[0]== '-'):
            print("+", end="")
    else:
        print("|", end="")
    for i in range(len(line)):
        if (line[i].isdigit()):
            for j in range(int(line[i])):
                print('-', end="")
        elif (line[i] == 'a'):
            print("+ ",end ="")
        elif (line[i] == 'b'):
            print("+-", end="")
        elif (line[i] == 'c'):
            print("| ", end ="")
        else:
            print(line[i], end="")
    if (line[-1].isdigit() or line[-1]== '-'):
        print("+")
    else:
        print("|")

def draw_road(line, width):
    print("|",end="")
    for i in range(1, width-1):
        if i in line:
            print("|", end="")
        else:
            print(" ", end="")
    print("|")

def draw_maze(maze, width):
    draw_updown(maze, 0, width)
    row = 0
    for line in maze:
        if (row % 2 == 1):
            draw_wall(line)
        else:
            draw_road(line, width)
        row+=1
    draw_updown(maze, -1, width)

f = open("maze2.txt", 'r')
line = f.readline()
nums = line.split()
count=0
row=0
maze=[]
print("{} {}".format(nums[0],nums[1]))
line = f.readline()
while True:
    line = f.readline()
    if (not line or row == (int(nums[1])*2-1)): 
        break
    if (row % 2 == 1):
        data_list = get_wall(line)
    else:
        data_list = get_road(line)
    maze.append(data_list)
    count+=len(data_list)
    row+=1
f.close()
draw_maze(maze,int(nums[0])*2+1)
print(count)