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

class Field {       // The class
  public:             // Access specifier
    int F[7][6];;        //Main Attribute
    string myString;  // Attribute (string variable)

    void Fill() {
        int draw = 1;//Change to disable
        if (draw == 1) {
            for (int y = 0; y <= 5; y++) {
                for (int x = 0; x <= 6; x++) {
                    F[x][y] = 0;
                }
            }
        }
        cout <<"Field Filled" << endl;
    }

    void switchsides() {
        for (int y = 0; y <= 5; y++) {
            for (int x = 0; x <= 6; x++) {
                F[x][y] = F[x][y] != 0 ? (F[x][y] % 2) + 1 : 0;
            }
        }
    }

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

};

int main()
{
    Field F;
    F.Fill();
    F.Drawfield();
    F.F[0][5] = 1;
    F.Drawfield();
    F.switchsides();
    F.Drawfield();
    return 0;
}
