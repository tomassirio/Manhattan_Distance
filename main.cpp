#include <iostream>
#include <vector>
using namespace std;

void printMatrix(vector<vector<pair<int, bool> > > matrix){
    for(int i = 0; i < matrix.size() ; i++){
        for (int j = 0; j < matrix[i].size() ; j++){
            cout << matrix[i][j].first  << '\t';
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0; i < matrix.size() ; i++){
        for (int j = 0; j < matrix[i].size() ; j++){
            cout << matrix[i][j].second << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

void printVector(vector<uint32_t> vector) {
    for(int i = 0; i < vector.size(); i++){
        cout << vector[i] << ", ";
    }

}

bool checkIfZero(vector<vector<pair<int, bool> > >  matrix, int row, int col){
    return matrix[row][col].first == 0;
}

bool checkIfNeighbourIsPOI(vector<vector<pair<int, bool> > > matrix, int row, int col){
    return matrix[row][col].second;
}

vector<vector<pair<int, bool> > > incrementNeighbours(vector<vector<pair<int, bool> > > matrix, int row, int col){
    //Checks for out of bounds and Points of interest before incrementing
    if(row-1 >= 0){
        if(checkIfZero(matrix, row-1, col) && !checkIfNeighbourIsPOI(matrix, row-1, col))
        matrix[row-1][col].first = matrix[row][col].first + 1;
    }
    if(row+1 < matrix.size()){
        if(checkIfZero(matrix, row+1, col) && !checkIfNeighbourIsPOI(matrix, row+1, col))
            matrix[row+1][col].first = matrix[row][col].first + 1;
    }
    if(col-1 >= 0){
        if(checkIfZero(matrix, row, col-1) && !checkIfNeighbourIsPOI(matrix, row, col-1))
            matrix[row][col-1].first = matrix[row][col].first + 1;
    }
    if(col+1 < matrix[row].size()){
        if(checkIfZero(matrix, row, col+1) && !checkIfNeighbourIsPOI(matrix, row, col+1))
            matrix[row][col+1].first = matrix[row][col].first + 1;
    }
    return matrix;
}


std::vector<uint32_t> ComputarEnemigos(uint32_t M, uint32_t N, const std::vector<std::pair<uint32_t, uint32_t>>& iP){
    vector<vector<pair<int, bool> > > matrix(M, vector<pair<int, bool>>(N));

    //Initialize my matrix with (0, false)
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            matrix[i][j].first = 0;
            matrix[i][j].second = false;
        }
    }
    //Set the values of point of interest as (0, true) in the matrix
    for(int i = 0; i < iP.size(); i++){
        matrix[iP[i].first][iP[i].second].first = 0;
        matrix[iP[i].first][iP[i].second].second = true;
    }

    //Increases only first neighbours
    for(int i = 0; i < iP.size(); i++){
        matrix = incrementNeighbours(matrix, iP[i].first,  iP[i].second);
    }

    int checkIncrements;
    int level = 1;
    do{
        checkIncrements = 0;
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[i].size(); j++){
                if (matrix[i][j].first == level){
                    matrix = incrementNeighbours(matrix, i, j);
                    checkIncrements++;
                }
            }
        }
        level++;
    }while(checkIncrements !=0);

    printMatrix(matrix);

    vector<uint32_t > vec;

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            vec.push_back(matrix[i][j].first);
        }
    }

    printVector(vec);

    return vec;
}
int main() {
    pair<uint32_t , uint32_t > firstPair (4,3);
    pair<uint32_t , uint32_t > secondPair (2,3);
    pair<uint32_t , uint32_t > thirdPair (7,9);


    vector<pair<uint32_t, uint32_t> > poiVector;

    poiVector.push_back(firstPair);
    poiVector.push_back(secondPair);
    poiVector.push_back(thirdPair);

    ComputarEnemigos(21, 19, poiVector);
    return 0;
}

