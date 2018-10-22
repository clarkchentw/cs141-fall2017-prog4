/*
    Overall score = 53 + 42.5 = 95.5

Grading comments in the code below are marked with //-!-
Not following the naming convention results in 5 pt. Deduction as stated above

 Program execution (55 points total)
 A. 5: Display the graphical board         				|
 B. 10: Move all of the pieces around(without error check)     	|
        (A and B above must work for the rest to be graded)	|
 C: 10: The initial configuration for the board should be read	|
 from a file called board.txt							|
 D.  check conditions.
3:valid color or action items. Please retry.			|
      4:move a piece in the wrong direction.  Please retry.		|
	4:move a piece on top of another piece.  Please retry.	|
	4:move a piece off the edge of the board.  Please retry.	|  //-!-   -2 some cars treat it as moving on top of another piece
 E.  5: Input of ‘x’ or ‘X’ exits the game                   	|
 G.  10: Reset the board. The subsequent board must be playable	|

 Program Style (45 points total):
 A.  5: Followed program naming conventions     |  //-!- -2.5 & is not a program naming convention
 B. 10: Meaningful identifier names             |
 C. 10: Comments                                |
 D.  5: Functional Decomposition                |
 E. 10: Appropriate data and control structures |
 F.  5: Code Layout                             |
*/

/* --------------------------------------------------------
 * Graphical Traffic
 *     Graphical version of the game RushHour, where the
 *     object is to move the vehicles such that the small
 *     car can exit the right of the board.
 *
 * Class: Program #4 for CS 141, Fall 2017.
 * Lab: Tues 9am
 * TA: Moumita Samanta
 * System: Qt Creator
 * Author: Clark Chen, Ishita Chopra
 */
#include <iostream>
#include <fstream> // Read File
#include <unistd.h> // For sleep()
#include "gobjects.h"  // for all graphics objects
using namespace std;

// Global variables and constants
int numOfMoves = 0;
char pointData[37]; // Primary Storage
char lastPointData[37]; // Backup Storage, use when found invalid move during process

//--------------------------------------------------------------------
// Display ID info
void displayIDInfo()
{
    cout << "Author:  Clark Chen, Ishita Chopra" << endl;
    cout << "Lab:     Tues 9am" << endl;
    cout << "TA:      Moumita Samanta" << endl;
    cout << "Program: #4, Graphical" << endl;
}//end displayIDInfo()


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "Welcome to the traffic game!                          " << endl
         << "                                                      " << endl
         << "Move the vehicles so that the Red car can exit   " << endl
         << "the board to the right. Each move should be of the    " << endl
         << "of the form:   CDN   where:                           " << endl
         << "   C  is the first letter of color of the vehicle to be moved" << endl
         << "   D  is the direction (u=up, d=down, l=left or r=right)" << endl
         << "   N  is the number of squares to move it             " << endl
         << "For example GR2  means move the G vehicle to the right" << endl
         << "2 squares.  Lower-case input such as   gr2  is also   " << endl
         << "accepted.  Enter 'reset' to reset board, or 'exit' to exit.  " << endl;
}//end displayInstructions()


//--------------------------------------------------------------------
// Take a snapshot of the current board
void snapshotBoard()
{
    for (int i = 0; i <= 36; i++)
    {
        lastPointData[i] = pointData[i];
    }
}//end snapshotBoard()


//--------------------------------------------------------------------
// Restore from the previous snapshot
void restoreFromSnapshot()
{
    for (int i = 0; i <= 36; i++)
    {
        pointData[i] = lastPointData[i];
    }
}//end restoreFromSnapshot()


//--------------------------------------------------------------------
// Moving Action
// function for moving the piece.
// "origin" is it's original point, and "dest" is the destination point
void startMove(int origin, int dest)
{
    pointData[dest] = pointData[origin];
    pointData[origin] = '.';
}//end startMove(int origin, int dest)


//--------------------------------------------------------------------
// Validate Moving Action
// Make sure they are not moving out of bound or moving onto another
// piece.
bool validateMove(int origin, int dest)
{
    // exception rule to prevent attempt to move to pointData[0]
    if (dest == 0)
    {
        cout << "Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
        restoreFromSnapshot();
        return false;
    }
    if (pointData[dest] != '.')
    {
        cout << "Attempt is made to move a piece on top of another piece.  Please retry." << endl;
        restoreFromSnapshot();
        numOfMoves--;
        return false;
    }

    // validation for horizontal move
    if (abs(origin-dest) == 1 && ((origin / 6) == (dest / 6) || (dest % 6 == 0 && (origin / 6) == (dest / 6)-1) || (origin % 6 == 0 && (origin / 6)-1 == (dest / 6))))
    {
        startMove(origin, dest);
        return true;
    }
    // validation for vertical move
    else if (abs(origin-dest) == 6 && ((origin % 6) == (dest % 6)))
    {
        startMove(origin, dest);
        return true;
    }
    else
    {
        cout << "Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
        restoreFromSnapshot();
        numOfMoves--;
        return false;
    }
}//end validateMove(int origin, int dest)


//--------------------------------------------------------------------
// Move the selected vehicle vertically
// Parameter C  is the vehicle to be moved,
// D  is the direction (u=up, d=down)
// N  is the number of squares to move it
bool moveV(char C, char D)
{
    // tempx are for temp location info of the car
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;
    // Search for the position of the car
    for (int i = 36; i >= 1; i--)
    {
        if (pointData[i] == C)
        {
            if (temp1 == 0)
            {
                temp1 = i;
            }
            else if (temp2 == 0)
            {
                temp2 = i;
            }
            else if (temp3 == 0)
            {
                temp3 = i;
            }
        }
    }
    // check to make sure the car can move vertically
    if (abs(temp1-temp2) == 1)
    {
        cout << "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
        numOfMoves--;
        return false;
    }
    if (D == 'U')
    {
        if (temp3 != 0)
        {
            if (!validateMove(temp3, temp3-6))
            {
                return false;
            }
        }
        if (!validateMove(temp2, temp2-6))
        {
            return false;
        }
        if (!validateMove(temp1, temp1-6))
        {
            return false;
        }
    }
    else if (D == 'D')
    {
        if (!validateMove(temp1, temp1+6))
        {
            return false;
        }
        if (!validateMove(temp2, temp2+6))
        {
            return false;
        }
        if (temp3 != 0)
        {
            if (!validateMove(temp3, temp3+6))
            {
                return false;
            }
        }
    }
    return true;
}//end moveV(char C, char D)


//--------------------------------------------------------------------
// Move the selected vehicle horizontally
// Parameter C  is the vehicle to be moved,
// D  is the direction (l=left or r=right)
// N  is the number of squares to move it
bool moveH(char C, char D)
{
    // tempx are for temp location info of the car
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;

    // Search for the position of the car
    for (int i = 36; i >= 1; i--)
    {
        if (pointData[i] == C)
        {
            if (temp1 == 0)
            {
                temp1 = i;
            }
            else if (temp2 == 0)
            {
                temp2 = i;
            }
            else if (temp3 == 0)
            {
                temp3 = i;
            }
        }
    }

    // check to make sure the car can move horizontally
    if (abs(temp1-temp2) == 6)
    {
        cout << "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
        numOfMoves--;
        return false;
    }

    if (D == 'L')
    {
        if (temp3 != 0)
        {
            if (!validateMove(temp3, temp3-1))
            {
                return false;
            }
        }
        if (!validateMove(temp2, temp2-1))
        {
            return false;
        }
        if (!validateMove(temp1, temp1-1))
        {
            return false;
        }
    }
    else if (D == 'R'){
        if (!validateMove(temp1, temp1+1))
        {
            return false;
        }
        if (!validateMove(temp2, temp2+1))
        {
            return false;
        }
        if (temp3 != 0){
            if (!validateMove(temp3, temp3+1))
            {
                return false;
            }
        }
    }
    return true;
}//end moveH(char C, char D)


//--------------------------------------------------------------------
// Coordinate to Array index Translator
int coorToArray(int x, int y, bool ischar=false)
{
    // char to int convertor
    if (ischar)
    {
        x = x-'0';
        y = y-'0';
    }

    int arrayID = (x-1)*6+(y);
    return arrayID;
}//end coorToArray(int x, int y, bool ischar=false)


//--------------------------------------------------------------------
// Reset the board
void resetBoard()
{
    numOfMoves = 0;
    // Set the board values
    int num_of_cars; //
    char userInput[8][5];

    cout<<"Enter the number of cars: ";
    cin>>num_of_cars;

    for(int i=1;i<=num_of_cars;i++)
    {
        cout<<"Enter the information of Car "<<i<<" : "<<endl;
        cout<<"Car color (first letter): ";
        cin >> userInput[i-1][0];
        cout<<"Car direction (V for vertical, H for Horizontal): ";
        cin >> userInput[i-1][1];
        cout<<"Car's X postion: ";
        cin >> userInput[i-1][2];
        cout<<"Car's Y postion: ";
        cin >> userInput[i-1][3];
        cout<<"Car length: ";
        cin >> userInput[i-1][4];
    }

    // Reset Database
    for (int i = 1; i <= 36; i++)
    {
        pointData[i] = '.';
    }

	// Process the import data, and save to array
    for (int i = 0; i < num_of_cars; i++)
    {
        char carColor = toupper(userInput[i][0]);
        char carDirection = userInput[i][1];
        char carX = userInput[i][2];
        char carY = userInput[i][3];
        int carLength = userInput[i][4]-'0';
        int carPosition = coorToArray(carX, carY, true);

        for (int i = 0; i < carLength; i++)
        {
            pointData[carPosition] = carColor;

            if (toupper(carDirection) == 'H')
            {
                carPosition = carPosition + 1;
            }
            else if (toupper(carDirection) == 'V')
            {
                carPosition = carPosition + 6;
            }
            else
            {
                cout << "Invalid Input for car direction" << endl;
                break;
            }
        }
    }

    // Check if the board is successfully created (Not blank)
    bool boardNotBlank = false;
    for (int i = 1; i <= 36; i++)
    {
        if (pointData[i] != '.'){
            boardNotBlank = true;
            break;
        }
    }
    // If the board is blank, then restore to the previous one
    if (!boardNotBlank){
        restoreFromSnapshot();
    }

    cin.ignore(10000, '\n'); //Clean any additional input before return back to main
} // end resetBoard();


//--------------------------------------------------------------------
// exit the game
void exitGame(GWindow graphicsWindow)
{
    cout << endl;
    cout << "Thank you for playing.  Exiting..." << endl;
    sleep(2);
    // Close the windows, first the graphics window, then the console window.
    graphicsWindow.requestFocus();
    graphicsWindow.close();
    exitGraphics();
    exit(0);
}//end exitGame(GWindow graphicsWindow)

//--------------------------------------------------------------------
// Input Check: check for special function key, and make sure user
// input a valid command length
bool inputCheck(char userInput[5], GWindow graphicsWindow)
{
    bool goToOther = false;
    if (userInput[0] == 'e' && userInput[1] == 'x' && userInput[2] == 'i' && userInput[3] == 't')
    {
        exitGame(graphicsWindow);
        goToOther = true;
    }
    else if (userInput[0] == 'r' && userInput[1] == 'e' && userInput[2] == 's' && userInput[3] == 'e' && userInput[4] == 't')
    {
        resetBoard();
        goToOther = true;
    }
    return goToOther;
}//end inputCheck(char userInput[5], GWindow graphicsWindow)


//--------------------------------------------------------------------
// Process user command
void controlUnit(GWindow graphicsWindow)
{
    char C;
    char D;
    int N;
    char userInput[5];

    // Prompt for enter command
    cout << numOfMoves << ". Your move -> ";
    cin.getline (userInput, 6);
    cin.clear(); // Clear any additional input
    if (inputCheck(userInput, graphicsWindow))
    {
        return;
    }

    // Set userInput to proper variable
    C = toupper(userInput[0]);
    D = toupper(userInput[1]);
    N = userInput[2]-'0';


    // Loop through the board to check if the car(C) exist
    bool validCar = false;
    for(int i = 1; i <= 36; i++)
    {
        if (pointData[i] == C)
        {
            validCar = true;
            break;
        }
    }

    if (!validCar)
    {
        cout << "User input is not one of the valid color or action items.  Please retry." << endl << endl;
    }
    else if(!(0 < N && N < 10))
    {
        cout << "User input is not one of the valid color or action items.  Please retry." << endl << endl;
    }
    else
    {
        // Increase move count by 1
        numOfMoves += 1;
        if (D == 'L' || D == 'R')
        {
            for (int i=N;i>0;i--)
            {
                if (!moveH(C, D))
                {
                    break;
                }
            }
            cout << endl;
        }
        else if (D == 'U' || D == 'D')
        {
            for (int i=N;i>0;i--)
            {
                if (!moveV(C, D))
                {
                    break;
                }
            }
            cout << endl;
        }
        else
        {
            cout << "User input is not one of the valid color or action items.  Please retry." << endl << endl;
            numOfMoves--;
        }
    }
} // end controlUnit()


//--------------------------------------------------------------------
// win the game
void winGame(GWindow graphicsWindow)
{
    cout << "*** Congratulations, you did it! ***" << endl;
    exitGame(graphicsWindow);
}//winGame(GWindow graphicsWindow)


//--------------------------------------------------------------------
// Array index to Coordinate Translator
// For X
int arrayToCoorX(int arrayID)
{
    int x = arrayID % 6;
    if (x == 0)
    {
        x = 6;
    }
    return x;
}//end arrayToCoorX(int arrayID)
// For Y
int arrayToCoorY(int arrayID)
{
    int y;
    if (arrayID % 6 == 0)
    {
        y = arrayID / 6;
    }
    else{
        y = arrayID / 6;
        y++;
    }
    return y;
}//end arrayToCoorY(int arrayID)


//--------------------------------------------------------------------
// Convertor for coordinate X to graphic X
int coorXToGraphicX(int x)
{   // x is the number of the boxes to be moved along horizontally
    int graphic_x=30;
    graphic_x += (x-1)*40;
    return graphic_x;
}//end coorXToGraphicX(int x)

//--------------------------------------------------------------------
// Convertor for coordinate X to graphic X
int coorYToGraphicY(int y)
{
    // y is the number of the boxes to be moved along veritcally
    int graphic_y=30;
    graphic_y += (y-1) * 40;
    return graphic_y;
}//end coorYToGraphicY(int y)


//--------------------------------------------------------------------
// Convert length and direction to graphic length
// For X
int toGraphicXLength(int length, char direction)
{
    int graphic_length_x=30;
    if(toupper(direction) == 'H')
    {
        graphic_length_x += (length-1)*40;
    }
    return graphic_length_x;
}//end toGraphicXLength(int length, char direction)
// For Y
int toGraphicYLength(int length, char direction)
{
    int graphic_length_y=30;
    if(toupper(direction) == 'V')
    {
        graphic_length_y += (length-1)*40;
    }
    return graphic_length_y;
}//end toGraphicXLength(int length, char direction)


//--------------------------------------------------------------------
// Update Database from File
void updateDBFromFile()
{
    // Process for import file data to variable
    ifstream boardFile;
    boardFile.open("board.txt");
    char numOfCar, carColor, carDirection, carX, carY, carLength;

    // Extract number of car from file
    boardFile >> numOfCar;

    // Reset Database
    for (int i = 1; i <= 36; i++)
    {
        pointData[i] = '.';
    }

    // Import data from File
    while (boardFile >> carColor >> carDirection >> carX >> carY >> carLength)
    {
        int carPosition = coorToArray(carX, carY, true);
        for (int i = 0; i < carLength-'0'; i++)
        {
            pointData[carPosition] = carColor;


            if (toupper(carDirection) == 'H')
            {
                carPosition = carPosition + 1;
            }
            else if (toupper(carDirection) == 'V')
            {
                carPosition = carPosition + 6;
            }
            else
            {
                cout << "Invalid Input for car direction" << endl;
                break;
            }
        }
    }
}//end updateDBFromFile()


//--------------------------------------------------------------------
// determine the direction of the car
char arrayToGUI_find_direction(int target[3])
{
    char result = 'x';
    if (target[1] - target[0] == 1)
    {
        result = 'h';
    }
    else if (target[1] - target[0] == 6)
    {
        result = 'v';
    }
    else {
        result = 'x';
    }
    return result;
}//end arrayToGUI_find_direction(int target[3])


//--------------------------------------------------------------------
// convert from array to GUI
void arrayToGUI(GRect *gCar, GRect *yCar, GRect *mCar, GRect *rCar, GRect *bCar, GRect *oCar, GRect *cCar, GRect *pCar)
{
    // pos for record each car's position, counter is the amount of car, direction used to temperary store direction info
    int gPos[3] = { 0 }; int gCounter = 0; char gDirection = 'x';
    int yPos[3] = { 0 }; int yCounter = 0; char yDirection = 'x';
    int mPos[3] = { 0 }; int mCounter = 0; char mDirection = 'x';
    int rPos[3] = { 0 }; int rCounter = 0; char rDirection = 'x';
    int bPos[3] = { 0 }; int bCounter = 0; char bDirection = 'x';
    int oPos[3] = { 0 }; int oCounter = 0; char oDirection = 'x';
    int cPos[3] = { 0 }; int cCounter = 0; char cDirection = 'x';
    int pPos[3] = { 0 }; int pCounter = 0; char pDirection = 'x';

    // Search the position of the car
    for (int i = 1; i <= 36; i++)
    {
        switch (pointData[i])
        {
            case 'G': gPos[gCounter] = i; gCounter++; break;
            case 'Y': yPos[yCounter] = i; yCounter++; break;
            case 'M': mPos[mCounter] = i; mCounter++; break;
            case 'R': rPos[rCounter] = i; rCounter++; break;
            case 'B': bPos[bCounter] = i; bCounter++; break;
            case 'O': oPos[oCounter] = i; oCounter++; break;
            case 'C': cPos[cCounter] = i; cCounter++; break;
            case 'P': pPos[pCounter] = i; pCounter++; break;
        }
    }

    // Determine car's direction
    gDirection = arrayToGUI_find_direction(gPos);
    yDirection = arrayToGUI_find_direction(yPos);
    mDirection = arrayToGUI_find_direction(mPos);
    rDirection = arrayToGUI_find_direction(rPos);
    bDirection = arrayToGUI_find_direction(bPos);
    oDirection = arrayToGUI_find_direction(oPos);
    cDirection = arrayToGUI_find_direction(cPos);
    pDirection = arrayToGUI_find_direction(pPos);

    // If the car exist on the board, process it, if not hide it.
    if (gPos[0] != 0)
    {
        gCar->setBounds(coorXToGraphicX(arrayToCoorX(gPos[0])), coorYToGraphicY(arrayToCoorY(gPos[0])), toGraphicXLength(gCounter, gDirection), toGraphicYLength(gCounter, gDirection));
        gCar->setVisible(true);
    }
    else
    {
        gCar->setVisible(false);
    }
    if (yPos[0] != 0)
    {
        yCar->setBounds(coorXToGraphicX(arrayToCoorX(yPos[0])), coorYToGraphicY(arrayToCoorY(yPos[0])), toGraphicXLength(yCounter, yDirection), toGraphicYLength(yCounter, yDirection));
        yCar->setVisible(true);

    }
    else
    {
        yCar->setVisible(false);
    }
    if (mPos[0] != 0)
    {
        mCar->setBounds(coorXToGraphicX(arrayToCoorX(mPos[0])), coorYToGraphicY(arrayToCoorY(mPos[0])), toGraphicXLength(mCounter, mDirection), toGraphicYLength(mCounter, mDirection));
        mCar->setVisible(true);
    }
    else
    {
        mCar->setVisible(false);
    }
    if (rPos[0] != 0)
    {
        rCar->setBounds(coorXToGraphicX(arrayToCoorX(rPos[0])), coorYToGraphicY(arrayToCoorY(rPos[0])), toGraphicXLength(rCounter, rDirection), toGraphicYLength(rCounter, rDirection));
        rCar->setVisible(true);
    }
    else
    {
        rCar->setVisible(false);
    }
    if (bPos[0] != 0)
    {
        bCar->setBounds(coorXToGraphicX(arrayToCoorX(bPos[0])), coorYToGraphicY(arrayToCoorY(bPos[0])), toGraphicXLength(bCounter, bDirection), toGraphicYLength(bCounter, bDirection));
        bCar->setVisible(true);
    }
    else
    {
        bCar->setVisible(false);
    }
    if (oPos[0] != 0)
    {
        oCar->setBounds(coorXToGraphicX(arrayToCoorX(oPos[0])), coorYToGraphicY(arrayToCoorY(oPos[0])), toGraphicXLength(oCounter, oDirection), toGraphicYLength(oCounter, oDirection));
        oCar->setVisible(true);
    }
    else
    {
        oCar->setVisible(false);
    }
    if (cPos[0] != 0)
    {
        cCar->setBounds(coorXToGraphicX(arrayToCoorX(cPos[0])), coorYToGraphicY(arrayToCoorY(cPos[0])), toGraphicXLength(cCounter, cDirection), toGraphicYLength(cCounter, cDirection));
        cCar->setVisible(true);
    }
    else
    {
        cCar->setVisible(false);
    }
    if (pPos[0] != 0)
    {
        pCar->setBounds(coorXToGraphicX(arrayToCoorX(pPos[0])), coorYToGraphicY(arrayToCoorY(pPos[0])), toGraphicXLength(pCounter, pDirection), toGraphicYLength(pCounter, pDirection));
        pCar->setVisible(true);
    }
    else
    {
        pCar->setVisible(false);
    }
}//end arrayToGUI(GRect *gCar, GRect *yCar, GRect *mCar, GRect *rCar, GRect *bCar, GRect *oCar, GRect *cCar, GRect *pCar)


int main()
{
    displayIDInfo();        // Display ID info
    displayInstructions();  // Display game instructions
    // Initialize the board data from the file.
    updateDBFromFile();

    // Create a graphics window
    GWindow graphicsWindow(300, 300);   // Set the size
    graphicsWindow.setWindowTitle("Graphical Traffic");

    // Board outline
    GRect *boardOutline = new GRect(10, 10, 270, 270);
    boardOutline->setFilled(true);
    boardOutline->setColor("darkGray");
    graphicsWindow.add(boardOutline);

    // Inner playing surface
    GRect *innerPlayingSurface = new GRect(20, 20, 250, 250);
    innerPlayingSurface->setFilled(true);
    innerPlayingSurface->setColor("Gray");
    graphicsWindow.add(innerPlayingSurface);

    // Exit opening in the border: 270,100,10,50, "lightGray"
    GRect *exitOpening = new GRect(270, 100, 10, 50);
    exitOpening->setFilled(true);
    exitOpening->setColor("lightGray");
    graphicsWindow.add(exitOpening);

    /*         Grid         */
    // Vertical lines (vLineN)
    GRect *vLine1 = new GRect(20, 20, 10, 250);
    vLine1->setFilled(true);
    vLine1->setColor("lightGray");
    graphicsWindow.add(vLine1);
    GRect *vLine2 = new GRect(60, 20, 10, 250);
    vLine2->setFilled(true);
    vLine2->setColor("lightGray");
    graphicsWindow.add(vLine2);
    GRect *vLine3 = new GRect(100, 20, 10, 250);
    vLine3->setFilled(true);
    vLine3->setColor("lightGray");
    graphicsWindow.add(vLine3);
    GRect *vLine4 = new GRect(140, 20, 10, 250);
    vLine4->setFilled(true);
    vLine4->setColor("lightGray");
    graphicsWindow.add(vLine4);
    GRect *vLine5 = new GRect(180, 20, 10, 250);
    vLine5->setFilled(true);
    vLine5->setColor("lightGray");
    graphicsWindow.add(vLine5);
    GRect *vLine6 = new GRect(220, 20, 10, 250);
    vLine6->setFilled(true);
    vLine6->setColor("lightGray");
    graphicsWindow.add(vLine6);
    GRect *vLine7 = new GRect(260, 20, 10, 250);
    vLine7->setFilled(true);
    vLine7->setColor("lightGray");
    graphicsWindow.add(vLine7);

    // Horizontal lines (hLineN)
    GRect *hLine1 = new GRect(20, 20, 250, 10);
    hLine1->setFilled(true);
    hLine1->setColor("lightGray");
    graphicsWindow.add(hLine1);
    GRect *hLine2 = new GRect(20, 60, 250, 10);
    hLine2->setFilled(true);
    hLine2->setColor("lightGray");
    graphicsWindow.add(hLine2);
    GRect *hLine3 = new GRect(20, 100, 250, 10);
    hLine3->setFilled(true);
    hLine3->setColor("lightGray");
    graphicsWindow.add(hLine3);
    GRect *hLine4 = new GRect(20, 140, 250, 10);
    hLine4->setFilled(true);
    hLine4->setColor("lightGray");
    graphicsWindow.add(hLine4);
    GRect *hLine5 = new GRect(20, 180, 250, 10);
    hLine5->setFilled(true);
    hLine5->setColor("lightGray");
    graphicsWindow.add(hLine5);
    GRect *hLine6 = new GRect(20, 220, 250, 10);
    hLine6->setFilled(true);
    hLine6->setColor("lightGray");
    graphicsWindow.add(hLine6);
    GRect *hLine7 = new GRect(20, 260, 250, 10);
    hLine7->setFilled(true);
    hLine7->setColor("lightGray");
    graphicsWindow.add(hLine7);

    // Create Car Object
    GRect *gCar = new GRect(0, 0, 0, 0);
    gCar->setColor("green");
    gCar->setFilled(true);
    graphicsWindow.add(gCar);
    gCar->setVisible(false);
    GRect *yCar = new GRect(0, 0, 0, 0);
    yCar->setColor("yellow");
    yCar->setFilled(true);
    graphicsWindow.add(yCar);
    yCar->setVisible(false);
    GRect *mCar = new GRect(0, 0, 0, 0);
    mCar->setColor("magenta");
    mCar->setFilled(true);
    graphicsWindow.add(mCar);
    mCar->setVisible(false);
    GRect *rCar = new GRect(0, 0, 0, 0);
    rCar->setColor("red");
    rCar->setFilled(true);
    graphicsWindow.add(rCar);
    rCar->setVisible(false);
    GRect *bCar = new GRect(0, 0, 0, 0);
    bCar->setColor("blue");
    bCar->setFilled(true);
    graphicsWindow.add(bCar);
    bCar->setVisible(false);
    GRect *oCar = new GRect(0, 0, 0, 0);
    oCar->setColor("orange");
    oCar->setFilled(true);
    graphicsWindow.add(oCar);
    oCar->setVisible(false);
    GRect *cCar = new GRect(0, 0, 0, 0);
    cCar->setColor("cyan");
    cCar->setFilled(true);
    graphicsWindow.add(cCar);
    cCar->setVisible(false);
    GRect *pCar = new GRect(0, 0, 0, 0);
    pCar->setColor("pink");
    pCar->setFilled(true);
    graphicsWindow.add(pCar);
    pCar->setVisible(false);


    // Make it the current window, but only for one second
    graphicsWindow.requestFocus();
    pause(1000);   // time in milliseconds

	//--------------------------------------------------------------------
	// Main Running Part of the program
    arrayToGUI(gCar, yCar, mCar, rCar, bCar, oCar, cCar, pCar);
    while(true)
    {
        controlUnit(graphicsWindow); // Load the input control and operation system
        arrayToGUI(gCar, yCar, mCar, rCar, bCar, oCar, cCar, pCar); // Convert the array to GUI

		//Check for game end
        if (pointData[18] == 'R')
        {
            rCar->move(40, 0); // Red Car step out to the gate when win.
            winGame(graphicsWindow);
        }

		// Snapshot the current board
        snapshotBoard();
    }


    return 0;
}
