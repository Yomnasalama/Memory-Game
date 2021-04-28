#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
const int N = 5;
const int M = 4;
int count_score[2]= {0,0};
const int n_players = 2;
const int n_elements = 20;
char marks[n_players] = {'Y', 'H'};
char grid[N][M];
char elements[n_elements] = {'A','A','B','B','C','C','D','D','E','E','F','F','G','G','Q','Q','K','K','L','L'};
vector <char>chosen_elements;

bool check_full()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(grid[i][j] == '.')
                return false;
        }
    }
    return true;
}
void set_elements()
{
    char temp[n_elements] = {'.'};
    int x = 0, j = 0, i = 0;
    srand(time(0));
    while(!check_full())
    {
         i = rand() % 6;
         j = rand() % 5;
         if(grid[i][j] == '.')
         {
             grid[i][j] = elements[x];
             x++;
         }
    }
}
void clear_grid()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            grid[i][j] = '.';
        }
    }
    count_score[0] = 0;
    count_score[1] = 0;
    chosen_elements.clear();
}
void print_1stTime()
{
    clear_grid();
    set_elements();
    bool flag = false;
    cout << "Player 1: " << marks[0] << "  vs  Player 2: " << marks[1] << "\n";
    cout << "--";
    for (int i = 0; i <= N+1; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
        {
            cout << "|  ";
            cout << grid[i][j] << "  ";
        }
        cout << "|\n";
        cout << "--";
        for (int i = 0; i <= N+1; cout << "---", i++);
        cout << "--\n";
    }
    sleep(4);
    system ("CLS");
}
void print_grid() {
    bool flag = false;
    cout << "Player 1: " << marks[0] << "  vs  Player 2: " << marks[1] << "\n";
    cout << "--";
    for (int i = 0; i <= N+1; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
        {
            cout << "|  ";
            if(chosen_elements.size() != 0)
            {
                for(int h = 0; h < n_elements / 2; h++)
                {
                    if(grid[i][j] == chosen_elements[h])
                    {
                        flag = true;
                        break;
                    }
                }
            }
            if(flag)
                cout << grid[i][j] << "  ";
            else
                cout<<"??"<<" ";
            flag = false;
        }
        cout << "|\n";
        cout << "--";
        for (int i = 0; i <= N+1; cout << "---", i++);
        cout << "--\n";
    }
    cout<<"Player"<<" "<<"Y"<<" "<<"Score"<<" "<<':'<<" "<<count_score[0]<<endl;
    cout<<"Player"<<" "<<"H"<<" "<<"Score"<<" "<<':'<<" "<<count_score[1]<<endl;
}
void print_wrong(int i1,int j1,int i2,int j2)
{
    cout<<"WRONG!!"<<endl;
    bool flag = false;
    cout << "Player 1: " << marks[0] << "  vs  Player 2: " << marks[1] << "\n";
    cout << "--";
    for (int i = 0; i <= N+1; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
        {
            cout << "|  ";
            if(i == i1 && j == j1)
                cout << grid[i][j] << "  ";
            else if(i == i2 && j == j2)
                cout << grid[i][j] << "  ";
            else{
            for(int h = 0; h < chosen_elements.size(); h++)
            {
                if(grid[i][j] == chosen_elements[h])
                    flag = true;
            }
            if(flag)
                cout<<grid[i][j]<<"  ";
            else
                cout<<"??"<<" ";
            flag = false;
            }
        }
        cout << "|\n";
        cout << "--";
        for (int i = 0; i <= N+1; cout << "---", i++);
        cout << "--\n";
    }
    sleep(4);
    system ("CLS");
}
bool check_full_elements()
{
    if(chosen_elements.size() == n_elements/2)
        return true;
    return false;
}
void check_chosen(int i1, int j1, int i2, int j2, int player)
{
    if(grid[i1][j1] == grid[i2][j2])
    {
        chosen_elements.push_back(grid[i1][j1]);
        count_score[player]++;
    }
    else
        print_wrong(i1,j1,i2,j2);
}
bool valid_position(int i1, int j1, int i2, int j2)
{
    if((i1 >= 0 && i1 < N) && (i2 >= 0 && i2 < N )&& (j1 >= 0 && j1 < M) && (j2 >= 0 && j2 < M))
        return true;
    return false;
}
bool valid_element(int i1, int j1, int i2, int j2)
{
    if(chosen_elements.size() == 0)
        return true;
    for(int h = 0; h < n_elements/2; h++ )
    {
        if(grid[i1][j1] == chosen_elements[h] || grid[i2][j2] == chosen_elements[h])
            return false;
    }
    return true;
}
void check_winner()
{
    if(count_score[0] > count_score[1])
        cout<<marks[0]<<" "<<"Winner winner chicken dinner"<<endl;
    else if(count_score[0] < count_score[1])
        cout<<marks[1]<<" " <<"Winner winner chicken dinner"<<endl;
    else
        cout<<"TIE!!"<<endl;
}
int read_input(int &i1, int &j1, int &i2, int &j2)
{   cout << "Enter the two points of the cards: ";
    cin >> i1 >> j1 >> i2 >> j2;
    while (!valid_position(i1, j1,i2,j2) || !valid_element(i1,j1,i2,j2)) {
		cout << "Enter a valid two points of the cards: ";
		cin >> i1 >> j1 >> i2 >> j2;
	}
}
void play()
{
    cout << "Memory Cards Game!\n";
    int player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input from the player
        cout << "Player " << marks[player] << " is playing now\n";
        int i1, j1, i2, j2;
		read_input(i1, j1, i2, j2);
		check_chosen(i1, j1, i2, j2,player);
        player = (player + 1) % n_players;
        if (check_full_elements()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            check_winner();
            break;
        }
    }
}
int main()
{
    print_1stTime();
    while(true)
    {
        play();
        char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
        else
            print_1stTime();
    }
}
