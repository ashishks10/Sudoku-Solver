#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;

#define N 9
int grid[N][N];
bool rowTag[N][N], colTag[N][N], boxTag[N][N];
bool solvable=true,check_solved=false;


void initializeTags()
{
    for(int i=0;i<N;i++)
        {
        for(int j=0;j<N;j++)
        {
            grid[i][j]=0;
            rowTag[i][j]=false;
            colTag[i][j]=false;
            boxTag[i][j]=false;
        }
    }
}


void setTags(int row,int col,int num,bool value)
{
    int X_box=row/3;
    int Y_box=col/3;
    int boxNo=X_box*3 + Y_box;

    if(rowTag[row][num-1]==value || colTag[col][num-1]==value || boxTag[boxNo][num-1]==value)
        solvable=false;

    rowTag[row][num-1]=value;
    colTag[col][num-1]=value;
    boxTag[boxNo][num-1]=value;
}


void setTagsForInput()
{
    int num;
    for(int i=0;i<N;i++)
        {
        for(int j=0;j<N;j++)
        {
            num=grid[i][j];
            if(num>0){
                setTags(i,j,num,true);
            }
        }
    }
    cout<<endl;
}


void goto_XY(pair<int, int> pos)
{
    COORD coord;
    coord.X = pos.first * 4 + 42;
    coord.Y = pos.second * 2 + 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void move_up(pair<int, int>& pos)
{
    if (pos.second != 0)
        --pos.second;
    else
        pos.second = 8;
}


void move_down(pair<int, int>& pos)
{
    if (pos.second != 8)
        ++pos.second;
    else
        pos.second = 0;
}


void move_left(pair<int, int>& pos)
{
    if (pos.first != 0)
        --pos.first;
    else
        pos.first = 8;
}


void move_right(pair<int, int>& pos)
{
    if (pos.first != 8)
        ++pos.first;
    else
        pos.first = 0;
}


void move_pos(char c, pair<int, int>& pos)
{
    if(toupper(c) == 'W')
        move_up(pos);
    if(toupper(c) == 'A')
        move_left(pos);
    if(toupper(c) == 'S')
        move_down(pos);
    if(toupper(c) == 'D')
        move_right(pos);
    goto_XY(pos);
}


void clearscreen()
{
    HANDLE hConsole;
    COORD Position;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hConsole, Position);
}


void printGrid()
{
    system("color F1");

    if(check_solved){
        goto_XY(make_pair(0,13));
        cout<<"\nTHE SOLVED SUDOKU IS:  "<<endl;
    }
    cout << "\n\n";
    for (int i=0;i<N;i++) {
        cout << "\t\t\t\t\t|";
        if ((i) % 3)
            cout << "-----------|-----------|-----------|\n\t\t\t\t\t||";
        else
            cout << "===========|===========|===========|\n\t\t\t\t\t||";
        for (int j=0;j<N;j++)
        {
            if (j % 3 == 0)
                cout << "\b\b| ";
            if (grid[i][j]) {
                cout << grid[i][j];
            }
            else
                cout << " ";
            cout << " | ";
            if (j == N - 1)
                cout << "\b\b| ";
        }
        cout << "\b\n";
    }
    cout << "\t\t\t\t\t|===========|===========|===========|";
    if(!check_solved)
        cout << "\n\n\tINSTRUCTIONS FOR ENTERING THE SUDOKU: \n\t1 . USE W A S D  TO MOVE.\n\t2 . USE DIGITS 1 - 9 TO FILL VALUES.\n\t3 . PRESS 0 TO EMPTY CELL\n\t4 . PRESS Y TO SOLVE\n\t";
    else cout<<endl;
}


void getInput()
{
    pair <int, int> pos=make_pair(0,0);
    while (!check_solved)
    {
        clearscreen();
        printGrid();
        goto_XY(pos);
        char c;
        c = _getch();
        if (c >= '0' && c <= '9')
        {
            grid[pos.second][pos.first] = c - '0';
        }
        else if (c == 'a' || c == 'w' || c == 's' || c == 'd' || c == 'A' || c == 'W' || c == 'S' || c == 'D')
        {
            move_pos(c, pos);
        }
        else if(c == 'y' || c == 'Y'){
            check_solved=true;
            return;
        }
    }
    char c = getchar();
        return;
}


bool isSafe(int row,int col,int num)
{
    int X_box=row/3;
    int Y_box=col/3;
    int boxNo=X_box*3 + Y_box;

    bool row_check=rowTag[row][num-1];
    bool col_check=colTag[col][num-1];
    bool box_check=boxTag[boxNo][num-1];

    return !(row_check || col_check || box_check);
}


bool getEmpty(int &row,int &col)
{
    for(row=0;row<N;row++)
        {
        for(col=0;col<N;col++)
        {
            if(grid[row][col]==0)
                return true;
        }
    }
    return false;
}


bool solve()
{
    int row,col;

    if(getEmpty(row,col))
        {
        for(int num=1;num<=N;num++)
        {
            if(isSafe(row,col,num))
            {
                grid[row][col]=num;
                setTags(row,col,num,true);
                if(solve())
                    return true;
                else {
                    grid[row][col]=0;
                    setTags(row,col,num,false);
                }
            }
        }
    }
    else
        return true;
    return false;
}


int main() {
    initializeTags();
    getInput();
    setTagsForInput();
	if(solvable && solve()){
	    printGrid();
	}
	else{
        goto_XY(make_pair(0,13));
        system("color F4");
        cout<<"\n This SUDOKU CANNOT BE SOLVED.\n\n\n"<<endl;
	}
	system("pause");
	return 0;
}
