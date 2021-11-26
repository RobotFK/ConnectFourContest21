/*
To make accounting for the size easier comments will be in Blocks
In the Field F the topleft Field is 0:0 with the one to the right being 1:0 and the one under it 0:1

0123456
1  M  X
2  M  X
3  M  X
4  M  X
5XXMXXX

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

void Drawfield() {
    int draw = 1;//Change to disable
    if (draw == 1) {
        for (int y = 0; y <= 5; y++) {
            for (int x = 0; x <= 6; x++) {
                cout << F[x][y];
            }
            cout << endl;
        }
    }
    cout << endl;
}

void switchsides() {
    for (int y = 0; y <= 5; y++) {
        for (int x = 0; x <= 6; x++) {
            F[x][y] = F[x][y] != 0 ? (F[x][y] % 2) + 1 : 0;
        }
    }
}

string Placemarker(int x, string name) {
    bool victory = false;
    bool placed = false;
    int y;

    for (int i = 5; placed == false and i >= 0; i--) {
        cout << "Testing" << x << ":" << i << endl;
        if (F[x][i] == 0) {
            cout << "Inserting" << endl;
            F[x][i] = 1;
            placed = true;
            y = i;
        } //If else instead here maybe ?
        if (i == 0 and F[x][i] != 0) {
            cout << "Error, Column appears to be full" << endl;
            winner = "not " + name;
        }
    }
    //Evaluating victorynext

    if (F[0][0] != 0 && F[1][0] != 0 && F[2][0] != 0 && F[3][0] != 0 && F[4][0] != 0 && F[5][0] != 0 && F[6][0] != 0) {
        return "a Tie";
    }

    // Procedural Checking in 4 steps: Up, Side diagonal NE and diagonal NW
    // The splitting in subchecks is simmilar to solving unknown Nongramms
    //cout <<"Pre VicCheck"<< endl;

    //up
    if(F[x][2] == 1 and F[x][3] == 1){//Base check to reduce calculation
        if (F[x][4] == 1 and (F[x][5] == 1 or F[x][1] == 1)) {
            return name;
        }
        else if (F[x][1] == 1 and (F[x][4] == 1 or F[x][0] == 1)) {
            return name;
        }
    }

    //Side
    if (F[3][y] == 1) {// 0001000
        if (F[x][2] == 1) {// 0011000
            if (F[x][1] == 1) {// 0111000
                if (F[x][0] == 1 or F[x][4]) {
                    return name;
                }
            }else if (F[x][4] == 1) { // 0211100
                if  (F[x][5] == 1) {
                    return name;
                }
            }
        }else if (F[x][4] == 1 and F[x][5] == 1 and F[x][6] == 1) {// 0021111
                return name;
        }
    }

    //Diagonals prep
    //Could we not just check for a winstate procedurally in the first while loop ?
    int midyn = y;//going up(North) diagonally to the Middle
    int midys = y;//going down(South) diagonally to the Middle
    int midx = x;
    bool mid = false;
    while (not(mid)) {
        if (midx < 3) { // Spot is West of the middle
            midyn = midyn - 1 >= 0 ? midyn-- : midyn = -1;//If there is a legit space NE we move up, else we Disable
            midys = midys + 1 <= 5 ? midyn++ : midyn = -1;//If there is a legit space SE...
            midx++;
        }else if (midx > 3) { // Spot is East of the middle
            midyn = midyn - 1 >= 0 ? midyn-- : midyn = -1;//If there is a legit space Nw we move up, else we Disable
            midys = midys + 1 <= 5 ? midyn++ : midyn = -1;//If there is a legit space SW...
            midx--;
        }
        if (midx = 3) { // Spot is in the middle
        mid = true;
        }
        //cout <<"midx at the end is "<< midx<< endl;
    }

    //Diagonalls NE
    if (midyn != -1 ){//Is a Split into two to avoid errors even needed ?
        if(F[3][midyn] == 1 ){
        switch(midyn - y){//How far appart is the new one is placed from the center
        case 0://Placed in Mid, max wiggle - This is Code taken from Side evaluation and Altered
            if (F[2][y-1] == 1) {// 0011000
                if (F[1][y-2] == 1) {// 0111000
                    if (F[0][y-3] == 1 or F[4][y+1]) {
                        return name;
                    }
                }else if (F[4][y+1] == 1) { // 0211100
                    if  (F[5][y+2] == 1) {
                        return name;
                    }
                }
            }else if (F[4][y+1] == 1 and F[5][y+2] == 1 and F[6][y+3] == 1) {// 0021111
                return name;//This will be super super rare :)
            }
            break;
        case 1://Placed 1 of Mid, wiggle of 2
            if (x == 2) {
                if (F[1][y-1] == 1) {// 0111000
                    if (F[0][y-2] == 1 or F[4][y+2]) {
                        return name;
                    }
                }else{//0211000
                    if (F[4][y+2] == 1 and F[5][y+3]) {
                        return name;
                    }
                }
            }else{ // x is 4
                if  (F[5][y+1] == 1) { // 0001110
                    if (F[6][y+2] == 1 or F[2][y-2]) {
                        return name;
                    }
                }else{//0001120
                    if (F[2][y-2] == 1 and F[1][y-3]) {
                        return name;
                    }
                }
            }
            break;
        case 2://Placed 2 of Mid, wiggle of 1
            if(x == 2){// 0101000
                if(F[2][y+1] == 1 and (F[0][y-1] == 1 or F[4][y+3] == 1)){
                    return name;
                }
            }else {//x is 5
                if(F[4][y+1] == 1 and (F[6][y+1] == 1 or F[2][y-3] == 1)){
                    return name;
                }
            }
            break;
        case 3://Placed 3 of Mid, at max distance
            if(x == 0){
                if(F[1][y+1] == 1 and F[2][y+2] == 1){
                    return name;
                }
            }else {//x is 6 (I really hope)
                if(F[5][y-1] == 1 and F[4][y-2] == 1){
                    return name;
                }
            }
            break;
        default:
        cout << "Error in Diagonal Distance calc North" << endl;
        }
        }else{cout << "Northern mid for Diagonall Rates as Not owned" << endl;}
    }else{
        cout << "Northern mid for Diagonall Rates as Oob" << endl;}

    //Diagonalls NW , copied from The NE version
    if (midys != -1 ){
        if(F[3][midys] == 1 ){
        switch(y - midys){//How far appart is the new one is placed from the center
        case 0://Placed in Mid, max wiggle
            if (F[2][y+1] == 1) {// 0011000
                if (F[1][y+2] == 1) {// 0111000
                    if (F[0][y+3] == 1 or F[4][y-1]) {
                        return name;
                    }
                }else if (F[4][y-1] == 1) { // 0211100
                    if  (F[5][y-2] == 1) {
                        return name;
                    }
                }
            }else if (F[4][y-1] == 1 and F[5][y-2] == 1 and F[6][y-3] == 1) {// 0021111
                return name;//This will be not as rare as the first one but still rare I hope:)
            }
            break;
        case 1://Placed 1 of Mid, wiggle of 2
            if (x == 2) {
                if (F[1][y+1] == 1) {// 0111000
                    if (F[0][y+2] == 1 or F[4][y-2]) {
                        return name;
                    }
                }else{//0211000
                    if (F[4][y-2] == 1 and F[5][y-3]) {
                        return name;
                    }
                }
            }else{ // x is 4
                if  (F[5][y-1] == 1) { // 0001110
                    if (F[6][y-2] == 1 or F[2][y+2]) {
                        return name;
                    }
                }else{//0001120
                    if (F[2][y+2] == 1 and F[1][y+3]) {
                        return name;
                    }
                }
            }
            break;
        case 2://Placed 2 of Mid, wiggle of 1
            if(x == 2){// 0101000
                if(F[3][y-1] == 1 and (F[1][y+1] == 1 or F[4][y-2] == 1)){
                    return name;
                }
            }else {//x is 5
                if(F[4][y+1] == 1 and (F[6][y-1] == 1 or F[2][y+3] == 1)){
                    return name;
                }
            }
            break;
        case 3://Placed 3 of Mid, at max distance
            if(x == 0){
                if(F[1][y-1] == 1 and F[2][y-2] == 1){
                    return name;
                }
            }else {//x is 6 (I really hope)
                if(F[5][y+1] == 1 and F[4][y+2] == 1){
                    return name;
                }
            }
            break;
        default:
        cout << "Error in Diagonal Distance calc south" << endl;
        }
        }else{cout << "Southern mid for Diagonall Rates as Not owned" << endl;}
    }else{
        cout << "Southern mid for Diagonall Rates as Oob" << endl;}

    return winner; // If we have triggerd nothing so far, this placement was not winning

}

int placerand() {
    return 3; // OH YEAH ! an XKCD/221/ reference
}

int placebyhand() {
    int input;
    Drawfield();
    cout << "Input:";
    cin >> input;
    cout << endl;
    return input; // Using a Humans to give input for testing
}

int main() {
    cout << "Initalising:" << endl;
    while (winner == "0") {
        winner = Placemarker(placerand(), "placerand");
        //Drawfield();
        switchsides();
        winner = Placemarker(placebyhand(), "a Debugging user");
        //Drawfield();
        switchsides();
        if (F[0][0] != 0 && F[1][0] != 0 && F[2][0] != 0 && F[3][0] != 0 && F[4][0] != 0 && F[5][0] != 0 && F[6][0] != 0) {
            winner = "Null";
        }
        //cin >> winner;
    }
    cout << endl << "Winner is " << winner;
    return 0;
}
