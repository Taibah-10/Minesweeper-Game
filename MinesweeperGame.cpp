
#include <bits/stdc++.h>
using namespace std;

#define MAXSIDE 25

int n, m;

void Chooselevel(){
    int level;
    cout << "LEVELS:=" << endl;
    cout << "Beginner - 0" << endl;
    cout << "Intermediate - 1" << endl;
    cout << "Advanced - 2" << endl;
    cout << "Choose difficulty level(0,1,2): ";
    cin >> level;
    
    if(level==0){
        n=9;
        m=10;
    }
    else if(level==1){
        n=16;
        m=40;
    }
    else if(level==2){
        n=24;
        m=99;
    }
    else{
        cout << "INVALID CHOICE!!Choose out of the following three levels:";
        Chooselevel();
    }
}

void initialiseBoards(char realboard[][MAXSIDE], char board[][MAXSIDE]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            board[i][j]='-';
            realboard[i][j]='-';
        }
    }

    srand(time(0));
    for(int i=0; i<m;){
        int row=(rand()%n);
        int col=(rand()%n);
        if(realboard[row][col]=='-'){
            realboard[row][col]='*';
            i++;
        }
        else{
            continue;
        }
    }
}

void printBoard(char board[][MAXSIDE]){
    cout << "Minesweeper board" << endl;
    cout << " ";
    for(int i=0; i<n; i++){
        if(i<10){
            cout << "  " << i;
        }
        else{
            cout << " " << i;
        }
    }
    cout << endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(j==0 && i<10){
                cout << i << "  " << board[i][j];
            }
            else if(j==0 && i>=10){
                cout << i << " " << board[i][j];
            }
            else{
                cout << "  " << board[i][j];
            }
        }
        cout << endl;
    }
}

int checkAdjacent(char realboard[][MAXSIDE], int r, int c){
    int cnt=0;
    if(r!=0 && realboard[r-1][c]=='*'){
        cnt++;
    }
    if(r!=n-1 && realboard[r+1][c]=='*'){
        cnt++;
    }
    if(c!=0 && realboard[r][c-1]=='*'){
        cnt++;
    }
    if(c!=n-1 && realboard[r][c+1]=='*'){
        cnt++;
    }
    if(r!=0 && c!=0 && realboard[r-1][c-1]=='*'){
        cnt++;
    }
    if(r!=n-1 && c!=n-1 && realboard[r+1][c+1]=='*'){
        cnt++;
    }
    if(r!=0 && c!=n-1 && realboard[r-1][c+1]=='*'){
        cnt++;
    }
    if(r!=n-1 && c!=0 && realboard[r+1][c-1]=='*'){
        cnt++;
    }
    return cnt;
}

bool Checkfields(char board[][MAXSIDE], char realboard[][MAXSIDE], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(board[i][j]=='-' && realboard[i][j]!='*'){
                return false;
            }
        }
    }
    return true;
}

void playminesweeper(){
    Chooselevel();
    char realboard[n][MAXSIDE];
    char board[n][MAXSIDE];

    initialiseBoards(realboard, board);
    printBoard(board);
    //printBoard(realboard);

    int r,c;
    while (true)
    {
        bool win = Checkfields(board, realboard, n);
        if(win==true){
            cout << "Congratulations!!!You won the game." << endl;
            break;
        }
        cout << "Enter cell: " << endl;
        cout << "row = ";
        cin >> r;
        cout << "column = ";
        cin >> c;
        if(r>=n || c>=n || r<0 || c<0){
            cout << "Invalid! Enter correct row and column" << endl;
            continue;
        }
        if(realboard[r][c]=='-' && board[r][c]=='-'){
            int cnt=0;
            cnt=checkAdjacent(realboard, r, c);
            //cout << cnt;
            board[r][c]=cnt + '0';
            realboard[r][c]=cnt + '0';
            printBoard(board);
            continue;
        }
        else if(realboard[r][c]=='*'){
            printBoard(realboard);
            cout << "You Lost!! You hit a mine!" << endl;
            break;
        }
        else{
            cout << "Cell already filled!" << endl;
            continue;
        }
    }
    
}

int main(){
    char play='Y';
    while(play=='Y' || play=='y'){
        playminesweeper();
        cout << "Want to play another game?(y/n): ";
        cin >> play;
    }
    return 0;
}