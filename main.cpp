#include <iostream>
using namespace std;
struct board
{
    bool square, circle, empty;
    int pos;
    char data;
    board* next;
};

bool equal3(char x, char y, char z , char w) {
    if (x == y && x == z && x == w && x != ' ') {
        return true;
    }
    return false;
}
board* findNode(board* fullBoard, int new_data) {
    board* temp = fullBoard;
    while (temp->pos != new_data) {
        temp = temp->next;
    }
    return temp;
}

int checkWinner(board* fullBoard) {
    board* temp = fullBoard;
    // for rows
    for (int j = 0; j <= 35; j = j + 7 ) {
        for (int i = 0; i <4; i++) {
            if (equal3(findNode(fullBoard, temp->pos - i - j )->data, findNode(fullBoard, temp->pos - i - j - 1)->data, findNode(fullBoard, temp->pos - i - j - 2)->data, findNode(fullBoard, temp->pos - i - j - 3)->data))
            {
                return findNode(fullBoard, temp->pos - i)->data == 'X' ? 2 : -2;
            }
        }
    }

    // for columns
    for (int i = 0; i < 7; i++) {
        for (int j = 0;j<21;j = j + 7 ) {
            if (equal3(findNode(fullBoard, temp->pos-j - i)->data, findNode(fullBoard, temp->pos - i - j-7)->data, findNode(fullBoard, temp->pos - i-j - 14)->data, findNode(fullBoard, temp->pos - i -j - 21)->data)) {
                return findNode(fullBoard, temp->pos - i)->data == 'X' ? 2 : -2;

            }

        }
    }
    // for diameter 1
    for(int j = 0 ; j <21 ; j= j+7){
        for (int i = 0; i < 4; i++) {

            if (equal3(findNode(fullBoard, temp->pos - i - j)->data, findNode(fullBoard, temp->pos - 8 - i - j )->data, findNode(fullBoard, temp->pos - 16 - i - j )->data, findNode(fullBoard, temp->pos - 24 - i - j)->data)) {
                return findNode(fullBoard, temp->pos - i - j)->data == 'X' ? 2 : -2;
            }

        }
    }

    // for diameter 2
    for (int j = 0; j < 21; j = j + 7) {
        for (int i = 7; i >3; i--) {

            if (equal3(findNode(fullBoard, temp->pos - i - j)->data, findNode(fullBoard, temp->pos - 8 - i - j)->data, findNode(fullBoard, temp->pos - 16 - i - j)->data, findNode(fullBoard, temp->pos - 24 - i - j)->data)) {
                return findNode(fullBoard, temp->pos - i - j)->data == 'X' ? 2 : -2;
            }

        }
    }
    // for tie case
    bool tie = true;
    for (int i = 0; i < 42; i++) {

        if (temp->data == ' ') {
            tie = false;
        }
        temp = temp->next;
    }
    if (tie) return 0;

    return 1;

}
int minimax(board* fullBoard, int depth, bool isMaximizing, bool firstTime = true) {
    board* temp = fullBoard;
    int result = checkWinner(fullBoard);
    if (result != 1) {
        return result;
    }
    if (isMaximizing) {
        int finalScore = -100;
        for (int i = 0; i < 42; i++) {
            if (temp->data == ' ') {
                board* current = temp;
                current = findNode(fullBoard, temp->pos + 7);
                if (current->empty == true) {
                    continue;
                }
                temp->data = 'X';
                int score = minimax(fullBoard, depth - 1, false, false);
                temp->data = ' ';
                if (score > finalScore) {
                    finalScore = score;
                }
                if (firstTime) {
                    cout << "score," << temp->pos << score << "\n";
                }
            }
            temp = temp->next;
        }
        return finalScore;

    }

    else
    {
        int finalScore = 100;
        int finalPos;
        for (int i = 0;i < 42;i++)
        {
            if (temp->data == ' ')
            {
                board* current = temp;
                current = findNode(fullBoard, temp->pos + 7);
                if (current->empty == true ) {
                    continue;
                }

                    temp->data = 'O';
                    int score = minimax(fullBoard, depth - 1, true, false);
                    temp->data = ' ';
                    if (score < finalScore)
                    {
                        finalScore = score;
                        finalPos = temp->pos;
                    }
                    if (firstTime)
                    {
                        cout << "score," << temp->pos << score << endl;
                    }

            }
            temp = temp->next;
        }
        if (firstTime)
        {
            findNode(fullBoard, finalPos)->empty = false;
            findNode(fullBoard, finalPos)->circle = true;
        }

        return finalScore;
    }
}

void startGame(int first, board* fullBoard);
board* getBoard(board* fullBoard);

int main()
{
    int dice, first;

    board* fullBoard = NULL;
    cout << "Welcome to Tic-tac-toe DOS Game. (2 Player version)\n\n";
    cout << "X is Player 1 and O is Player 2.\nI will decide who is starting in the first match...\n ";

    dice = 1;//rand() % 6 + 1;
    cout << dice;
    if (dice <= 3)
    {
        first = 1;
        cout << " Player 1 is the first!\n";
    }
    else
    {
        first = 2;
        cout << " Player 2 is the first!\n\n";
    }
    system("pause");
    system("cls");
    startGame(first, fullBoard);

}

void startGame(int first, board* fullBoard)
{
    int choice;
    bool isPlaying;
    for (int i = 1; i <= 42; i++)
        fullBoard = getBoard(fullBoard);

    bool has_winner = false;
    while (!has_winner)
    {
        board* current = fullBoard;
        while (current != NULL)
        {
            cout << "|";
            if (current->empty == true) {

                cout << "   " << "*";

            }
            else if (current->circle == true) {

                cout << "   " << 'O';

            }
            else {

                cout << "   " << 'X';

            }
            if (current->pos == 36 || current->pos == 29 || current->pos == 22 || current->pos == 15 || current->pos == 8)
            {
                cout << " |";
                cout << "\n";
                cout << "-------------------------------------------------------------\n";
            }
            else if (current->pos == 1) {
                cout << " |";
                cout << "\n";
            }
            else
                cout << "   |";

            current = current->next;
        }



        if (first == 1)
        {
            isPlaying = true;
            while (isPlaying == true)
            {
                cout << "Player 1, please put the number corresponding to the area you want to fill: ";
                cin >> choice;
                while (choice < 1 || choice > 7)
                {
                    cout << "Invalid choice. Please choose a valid option: ";
                    cin >> choice;
                }
                current = fullBoard;
                while (current != NULL && current->pos != choice)
                    current = current->next;

            for (int i = 7;i <= 42; i = i +7 ) {
                if (current->empty == true)
                {
                    current->empty = false;
                    current->square = true;
                    isPlaying = false;
                    first = 2;
                    break;

                }
                else {
                    current = findNode(fullBoard,current->pos +i);
                }
            }
            }

        }
        else
        {
            int result = minimax(fullBoard, 100, false);
            cout << "result: " << result << "\n";
            first = 1;
        }
        current = fullBoard;
        while (current != NULL)
        {
            if (current->empty == true) {


                current->data = ' ';
            }
            else if (current->circle == true) {


                current->data = 'O';
            }
            else {


                current->data = 'X';
            }

            current = current->next;
        }


        has_winner = checkWinner(fullBoard) != 1;
        system("pause");
        system("cls");

    }

    int result = checkWinner(fullBoard);
    if (result == 0)
    {
        cout << "tie " << endl;
    }
    else
    {
        cout << ((result == 2) ? 'X' : 'O') << " is the winner " << endl;
    }
}

board* getBoard(board* fullBoard)
{
    board* newBoard = new board;
    newBoard->empty = true;
    newBoard->circle = false;
    newBoard->square = false;
    newBoard->next = fullBoard;
    if (newBoard->next != NULL)
        newBoard->pos = newBoard->next->pos + 1;
    else
        newBoard->pos = 1;
    return newBoard;
}
