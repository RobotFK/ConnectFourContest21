/*
To make accounting for the size easier comments will be in Blocks
In the Field F the topleft Field is 0:0 with the one to the right being 1:0 and the one under it 0:1
The value in each Field (F) has a meaning:
0 is empty
1 is The Current player
2 is the passive player

The function participating is to Evaluate the field and return the column (0-6) to enter a chip in

*/
#include <iostream>
using namespace std;

int F[7][6];
string winner = "0";

void Drawfield(){
    int draw;
    cout << "1 to draw field:";
    cin >> draw;
    cout << endl;
    if(draw == 1){
    for(int y = 0;y <= 5;y++){
        for(int x = 0;x <= 6;x++){
            cout << F[x][y];
        }
        cout << endl;
    }}
}

void switchsides(){
    for(int y = 0;y <= 5;y++){
        for(int x = 0;x <= 6;x++){
            F[x][y] = F[x][y] != 0 ? (F[x][y]%2)+1 : 0;
        }
    }
}

string Placemarker(int x, string name){
bool victory = false;
bool placed = false;

for(int i = 5;placed == false and i >= 0;i--){
    cout << "Testing" << x <<":" << i << endl;
    if (F[x][i] == 0){
        cout << "Inserting" << endl;
        F[x][i] = 1;
        placed = true;
    }
    if(i == 0 and F[x][i] != 0){
    cout << "Error, Column appears to be full" << endl;
    winner = "not " + name;
    }
}
//Evaluating victorynext
if (F[0][0] != 0 && F[1][0] != 0 && F[2][0] != 0 && F[3][0] != 0 && F[4][0] != 0 && F[5][0] != 0 && F[6][0] != 0 )


if(victory){
    return name;
}else{
    return winner;
    }
}

int placerand(){
return 3; // OH YEAH !
}

int main(){
    cout << "Initalising:" << endl;
    while(winner == "0"){
        winner = Placemarker(placerand(),"placerand");
        Drawfield();
        switchsides();
        winner = Placemarker(placerand(),"placerand2");
        Drawfield();
        switchsides();
        if(F[0][0] != 0 && F[1][0] != 0 && F[2][0] != 0 && F[3][0] != 0 && F[4][0] != 0 && F[5][0] != 0 && F[6][0] != 0 ){
            winner = "Null";
        }
        //cin >> winner;
    }
    cout << endl << "Winner is " << winner;
    return 0;
}
