//SUDOKU GENERATOR AND SOLVER

#include <bits/stdc++.h>
using namespace std;

#define N 9
#define empty 0


bool  isValid(int row, int col, vector<vector<int>> & grid, int val){
    for(int i=0; i<N; i++){
        //check in row
        if(grid[row][i] == val){
            return false;
        }

        //check in column
        if(grid[i][col] == val){
            return false;
        }

        //check in 3*3 submatrix
        if(grid[3*(row/3) + i/3][3*(col/3) + i%3] == val){
            return false;
        }
    }

    return true;
}

bool solver(vector<vector<int>> &grid){

    for(int row=0 ; row<N; row++){
        for(int col=0; col<N; col++){

           //check if the cell is empty
           if(grid[row][col]==empty){

            //insert value
            for(int val=1; val<=9; val++){
                if(isValid(row,col,grid,val)){
                    grid[row][col] = val;

                    //recursive call
                    bool isSolutionPossible = solver(grid);
                    if(isSolutionPossible){
                        return true;
                    }
                    else{
                        //backtrack
                        grid[row][col]=0;
                    }

                }
            }
            return false;
           } 
        }
    }

    return true;
}

void generator(vector<vector<int>> &grid){
    cout<<"Enter the number of clues you want to solve with:"<<endl;
    int clues;
    cin>>clues;

    solver(grid);

    int emptyCells = N*N - clues;

    while(emptyCells){
        int row = rand()%N;
        int col = rand()%N;

        if(grid[row][col]!=empty){
            grid[row][col]=0;
            emptyCells--;
        }
    }
}

void print(vector<vector<int>> &grid){
    cout<<" === === === === === === === === ==="<<endl;
    for(int row=0; row<N; row++){
        cout<<"|";
        for(int col=0; col<N; col++){
            cout<<" "<<grid[row][col]<<" |";
        }
        cout<<endl;
        cout<<" === === === === === === === === ==="<<endl;
    }
}

int main(){
    vector<vector<int>> grid(N,vector<int>(N,0));

    //generate sudoku
    generator(grid);

    print(grid);

    cout<<"Press 1 to solve the sudoku"<<endl;
    int solve;
    cin>>solve;

    if(solve==1){
        if(solver(grid)){
            cout<<"Solved Sudoku:"<<endl;
            print(grid);
        }
        else{
            cout<<"The Soduku can't be solved"<<endl;    
        }
    }

return 0;
}