import random
import os
import time
from subprocess import call
from time import sleep
from random import seed
from random import randint
N = 5
M = 4
count_score = [0,0]
n_players = 2
n_elements = 20
marks = ['X', 'O']
grid = [['.']*(M) for _ in range(N)]
elements = ['A','A','B','B','C','C','D','D','E','E','F','F','G','G','Q','Q','K','K','L','L']
chosen_elements = ['.'] * (n_elements //2)
def check_full():
    for i in range(N):
        for j in range(M):
            if grid[i][j] == '.':
                return False
    return True
def set_elements():
    x, j, i = 0, 0, 0
    while not check_full():
         i = random.randint(0, 4)
         j = random.randint(0, 3)
         if grid[i][j] == '.':
             grid[i][j] = elements[x]
             x+=1
def clear_grid():
    for i in range(N):
        for j in range(M):
            grid[i][j] = '.'
    count_score[0] = 0
    count_score[1] = 0
    for i in range(n_elements // 2):
        chosen_elements[i] = '.'

def print_1stTime():
    clear_grid()
    set_elements()
    print("Player 1: %c  vs  Player 2: %c" % (marks[0], marks[1]))
    print('--' + '---' * (N + 2) + '--')
    for i in range(N):
        for j in range(M):
            print(end='|  ')
            print(grid[i][j], end='  ')
        print(end='|')
        print()
        print('--' + '---' * (N+2) + '--')
    time.sleep(4)
def print_grid():
    flag = False
    print("Player 1: %c  vs  Player 2: %c" % (marks[0], marks[1]))
    print('--' + '---' * (N+2) + '--')
    for i in range(N):
        for j in range(M):
            print(end='|  ')
            for h in range(n_elements // 2):
                if grid[i][j] == chosen_elements[h]:
                    flag = True
            if(flag):
                print(grid[i][j], end='  ')
            else:
                print("??", end=' ')
            flag = False
        print(end='|')
        print()
        print('--' + '---' * (N + 2)+ '--')
    print("Player Y Score : %d" %count_score[0])
    print("Player H Score : %d" %count_score[1])

def print_wrong(i1,j1,i2,j2):
    print('WRONG!!')
    flag = False
    print("Player 1: %c  vs  Player 2: %c" % (marks[0], marks[1]))
    print('--' + '---' * (N + 2)  + '--')
    for i in range(N):
        for j in range(M):
            print(end='|  ')
            if(i == i1 and j == j1):
                print(grid[i][j], end = '  ')
            elif(i == i2 and j == j2):
                print(grid[i][j], end = '  ')
            else:
                for h in range(n_elements // 2):
                    if grid[i][j] == chosen_elements[h]:
                        flag = True
                        break
                if(flag):
                    print(grid[i][j], end ='  ')
                else:
                    print("??", end = ' ')
                flag = False
        print(end='|')
        print()
        print('--' + '---' * (N + 2)+ '--')
    time.sleep(3)
def check_full_elements():
    for i in range(n_elements // 2):
        if(chosen_elements[i] == '.'):
            return False
    return True

def check_chosen(i1,j1,i2,j2,player):
    if grid[i1][j1] == grid[i2][j2]:
        for i in range(n_elements // 2):
            if chosen_elements[i] == '.':
                chosen_elements[i] = grid[i1][j1]
                break
        count_score[player]+= 1
    else:
        print_wrong(i1,j1,i2,j2)

def valid_position(i1,j1,i2,j2):
    if(i1 >= 0 and i1 < N) and (i2 >= 0 and i2 < N ) and (j1 >= 0 and j1 < M) and (j2 >= 0 and j2 < M):
        return True
    return False

def valid_element(i1,j1,i2,j2):
    for h in range(n_elements // 2):
        if (grid[i1][j1] == chosen_elements[h]) or (grid[i2][j2] == chosen_elements[h]):
            return False
    return True
def check_winner():
    if count_score[0] > count_score[1]:
        print("The winner is %c"% marks[0])
    elif(count_score[0] < count_score[1]):
        print("Winner winner chicken dinner %c"% marks[1])
    else:
       print("TIE!!")
def read_input(i1, j1, i2, j2):
    i1, j1, i2, j2 = map(int, input("Enter the two points of the cards: ").split())
    while (not valid_position(i1, j1,i2,j2) or not valid_element(i1,j1,i2,j2)):
      i1,j1,i2,j2 = map(int, input("Enter a valid two points of the cards: ").split())
    return i1,j1,i2,j2
def play():
    print("Memory Cards Game!\n")
    player = 0
    while True:
        print_grid()
        print("Player %c is playing now\n"% marks[player])
        i1, j1, i2, j2 = 0, 0, 0, 0
        i1,j1,i2,j2 = read_input(i1, j1, i2, j2)
        check_chosen(i1, j1, i2, j2,player)
        player = (player + 1) % n_players
        if check_full_elements():
            print_grid()
            check_winner()
            break
print_1stTime()
while True:
    play()
    print("Play Again [Y/N] ")
    c = input();
    if not c == 'y' and not c == 'Y':
        break
    else:
        print_1stTime()
