#include <iostream>
#include <conio.h> // for live input
#include <ctime> // random seeds
#include <cstdlib> // rand/srand
#include "Maps.h"

using namespace std;

// Maze variables

int Map[10][20]; // main map variable
int keypresses = 1;
char PlayerInputMaze = '\0';

// Tic tac toe variables

char IsSinglePlayer = ' ';

int TicTacToeBoard[3][3]
{
    {0,0,0},
    {0,0,0},
    {0,0,0}
};

int PlayerMove = 0; // 1-9
int winner = 0; // 0 = no winner, 1 = player 1, 2 = player 2, 3 = draw

// Game state variables

bool PlayingMazeGame = false;
bool PlayingTicTacToe = false;
int GameSelectionIndex = 0;


// Maze functions

void printMatrix(const int matrix[][20], int rows, int cols) {
    cout << "Press keys (press 'q' to quit):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {

            switch (matrix[i][j])
            {
            case 0: cout << ' '; break; // Empty
            case 1: cout << '#'; break; // Square Wall
            case 2: cout << '|'; break; // Vertical Wall
            case 3: cout << 'X'; break; // End
            case 4: cout << 'O'; break; // Player
            default: cout << '?'; break; // unknown value 
            }
        }
        cout << endl;
    }
}

char UpdatePlayerInput()
{
    char c = '\0'; // default no input


    // get key if pressed

    if (_kbhit()) 
    {
        c = _getch();
    }

    return c;
}

bool MovePlayer(int matrix[][20], int rows, int cols, char input)
{
    int px = -1, py = -1;

    // Find player position (4 in the array)
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (matrix[i][j] == 4) { px = i; py = j; }

	if (px == -1) return false; // returns false if player not found

    int nx = px, ny = py;

    switch (toupper(input))
    {
    case 'W': nx = px - 1; break;
    case 'S': nx = px + 1; break;
    case 'A': ny = py - 1; break;
    case 'D': ny = py + 1; break;
    default: return false;
    }

    if (matrix[nx][ny] == 1 || matrix[nx][ny] == 2)
        return false;

    bool reachedEnd = (matrix[nx][ny] == 3);

    matrix[px][py] = 0;
    matrix[nx][ny] = 4;

    return reachedEnd;
}

void PickRandomMaze()
{
    srand(time(nullptr));

    int choice = rand() % 4;

    const int (*Selected)[20] = nullptr;

    switch (choice)
    {
    case 0: Selected = Map1; break;
    case 1: Selected = Map2; break;
    case 2: Selected = Map3; break;
    case 3: Selected = Map4; break;
    }

    // Copy the selected map into main Map[][]
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 20; j++)
            Map[i][j] = Selected[i][j];
}

// Main menu function

void MainMenu()
{
    cout << "\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "  /$$$$$$                                                 /$$$$$$                                                                           " << endl;
    cout << " /$$__  $$                                               /$$__  $$                                                                          " << endl;
    cout << "| $$  \\__/ /$$   /$$  /$$$$$$   /$$$$$$   /$$$$$$       | $$  \\ $$ /$$  /$$  /$$  /$$$$$$   /$$$$$$$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$    " << endl;
    cout << "|  $$$$$$ | $$  | $$ /$$__  $$ /$$__  $$ /$$__  $$      | $$$$$$$$| $$ | $$ | $$ /$$__  $$ /$$_____/ /$$__  $$| $$_  $$_  $$ /$$__  $$      " << endl;
    cout << " \\____  $$| $$  | $$| $$  \\ $$| $$$$$$$$| $$  \\__/      | $$__  $$| $$ | $$ | $$| $$$$$$$$|  $$$$$$ | $$  \\ $$| $$ \\ $$ \\ $$| $$$$$$$$      " << endl;
    cout << " /$$  \\ $$| $$  | $$| $$  | $$| $$_____/| $$            | $$  | $$| $$ | $$ | $$| $$_____/ \\____  $$| $$  | $$| $$ | $$ | $$| $$_____/      " << endl;
    cout << "|  $$$$$$/|  $$$$$$/| $$$$$$$/|  $$$$$$$| $$            | $$  | $$|  $$$$$/$$$$/|  $$$$$$$ /$$$$$$$/|  $$$$$$/| $$ | $$ | $$|  $$$$$$$      " << endl;
    cout << " \\______/  \\______/ | $$____/  \\_______/|__/            |__/  |__/ \\_____/\\___/  \\_______/|_______/  \\______/ |__/ |__/ |__/ \\_______/      " << endl;
    cout << "                    | $$                                                                                                                    " << endl;
    cout << "                    | $$                                                                                                                    " << endl;
    cout << "                    |__/                                                                                                                    " << endl;
    cout << " /$$    /$$ /$$       /$$                            /$$$$$$                                                                                " << endl;
    cout << "| $$   | $$|__/      | $$                           /$$__  $$                                                                               " << endl;
    cout << "| $$   | $$ /$$  /$$$$$$$  /$$$$$$   /$$$$$$       | $$  \\__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$                                              " << endl;
    cout << "|  $$ / $$/| $$ /$$__  $$ /$$__  $$ /$$__  $$      | $$ /$$$$ |____  $$| $$_  $$_  $$ /$$__  $$                                             " << endl;
    cout << " \\  $$ $$/ | $$| $$  | $$| $$$$$$$$| $$  \\ $$      | $$|_  $$  /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$                                             " << endl;
    cout << "  \\  $$$/  | $$| $$  | $$| $$_____/| $$  | $$      | $$  \\ $$ /$$__  $$| $$ | $$ | $$| $$_____/                                             " << endl;
    cout << "   \\  $/   | $$|  $$$$$$$|  $$$$$$$|  $$$$$$/      |  $$$$$$/|  $$$$$$$| $$ | $$ | $$|  $$$$$$$                                             " << endl;
    cout << "    \\_/    |__/ \\_______/ \\_______/ \\______/        \\______/  \\_______/|__/ |__/ |__/ \\_______/                                             " << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "1. Maze Game\n";
    cout << "2. Tic Tac Toe\n";
	cout << "3. Exit\n";
    cin >> GameSelectionIndex;
}

// tic tac toe functions

void PrintTicTacToeBoard(int board[3][3])
{
	system("cls");

    auto symbol = [&](int r, int c) {
        if (board[r][c] == 1) return 'X';
        if (board[r][c] == 2) return 'O';
        return ' ';
        };

    cout << " " << symbol(0, 0) << " | " << symbol(0, 1) << " | " << symbol(0, 2) << " \n";
    cout << "---+---+---\n";
    cout << " " << symbol(1, 0) << " | " << symbol(1, 1) << " | " << symbol(1, 2) << " \n";
    cout << "---+---+---\n";
    cout << " " << symbol(2, 0) << " | " << symbol(2, 1) << " | " << symbol(2, 2) << " \n";
}

int CheckWinOrDraw(int board[3][3])
{
    // Check rows
    for (int r = 0; r < 3; r++)
    {
        if (board[r][0] != 0 &&
            board[r][0] == board[r][1] &&
            board[r][1] == board[r][2])
        {
            return board[r][0]; // 1 or 2
        }
    }

    // Check columns
    for (int c = 0; c < 3; c++)
    {
        if (board[0][c] != 0 &&
            board[0][c] == board[1][c] &&
            board[1][c] == board[2][c])
        {
            return board[0][c]; // 1 or 2
        }
    }

    // Check diags
    if (board[0][0] != 0 &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        return board[0][0];
    }

    if (board[0][2] != 0 &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        return board[0][2];
    }

    // Check for draw 
    bool boardFull = true;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (board[r][c] == 0)
            {
                boardFull = false;
                break;
            }
        }
        if (!boardFull) break;
    }

    if (boardFull)
        return 3; // Draw

    return 0; // No winner yet, game continues
}

void OutputWinMessage(int winner)
{
    switch (winner)
    {
    case 1:
        cout << "Player 1 (X) wins!\n";
        system("pause");
		break;
    case 2:
	    cout << "Player 2 (O) wins!\n";
        system("pause");
    case 3:
        cout << "It's a draw!\n";
		system("pause");
		break;
    default:
        break;
    }
}

bool RobotMoveO(int board[3][3])
{
    // check for an empty space
    bool hasEmpty = false;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (board[r][c] == 0)
            {
                hasEmpty = true;
                break;
            }
        }
        if (hasEmpty) break;
    }

    if (!hasEmpty)
        return false; // board full, nothing to place

    // try random cells until it finds a 0
    while (true)
    {
        int r = rand() % 3;
        int c = rand() % 3;

        if (board[r][c] == 0)
        {
            board[r][c] = 2;
            return true;
        }
    }
}

bool PlayerMoveX(int board[3][3], int input)
{
    int row = -1, col = -1;

    switch (input)
    {
    case 1: row = 2; col = 0; break;
    case 2: row = 2; col = 1; break;
    case 3: row = 2; col = 2; break;
    case 4: row = 1; col = 0; break;
    case 5: row = 1; col = 1; break;
    case 6: row = 1; col = 2; break;
    case 7: row = 0; col = 0; break;
    case 8: row = 0; col = 1; break;
    case 9: row = 0; col = 2; break;
    default:
        return false; // invalid input
    }

    // If the cell is empty (0), place X (1)
    if (board[row][col] == 0)
    {
        board[row][col] = 1;
        return true;
    }

    return false; // Cell taken
}

bool PlayerMoveO(int board[3][3], int input)
{
    int row = -1, col = -1;

    switch (input)
    {
    case 1: row = 2; col = 0; break;
    case 2: row = 2; col = 1; break;
    case 3: row = 2; col = 2; break;
    case 4: row = 1; col = 0; break;
    case 5: row = 1; col = 1; break;
    case 6: row = 1; col = 2; break;
    case 7: row = 0; col = 0; break;
    case 8: row = 0; col = 1; break;
    case 9: row = 0; col = 2; break;
    default:
        return false; // invalid input
    }

    // If the cell is empty (0), place O (2)
    if (board[row][col] == 0)
    {
        board[row][col] = 2;
        return true;
    }

    return false; // Cell is not empty
}

int main()
{

main_menu:

    MainMenu();
    system("cls");

    switch (GameSelectionIndex)
    {
    case 1: PlayingMazeGame = true;
        break;
    case 2: PlayingTicTacToe = true;
        break;
    case 3: cout << "Exiting.\n";
		return 0;
    default: cout << "Invalid selection. Exiting.\n";
        return 0;
    }

    // Maze Game Loop

    if (PlayingMazeGame == true)
    {

        PickRandomMaze();

        printMatrix(Map, 10, 20);

        // Start timer
        time_t startTime = time(nullptr);

        while (true)
        {

            // main input and frame updates
            PlayerInputMaze = UpdatePlayerInput();

            if (PlayerInputMaze != '\0')
            {
                if (PlayerInputMaze == 'q') break;

                bool finished = MovePlayer(Map, 10, 20, PlayerInputMaze);

                if (finished)
                {
                    system("cls");
                    printMatrix(Map, 10, 20);
                    time_t finalTime = time(nullptr);
                    cout << "\nYou reached the end!\n";
                    cout << "Your time: " << (finalTime - startTime) << " seconds\n";
                    cout << "Total keypresses: " << keypresses << "\n";
                    break;
                }
                else
                {
                    keypresses++;
                }

                // print new frame
                system("cls");
                printMatrix(Map, 10, 20);

                // update timer
                time_t currentTime = time(nullptr);
                cout << "Time: " << (currentTime - startTime) << "s\n";
            }

            PlayerInputMaze = '\0';
        }
        system("pause");
        system("cls");
        PlayingMazeGame = false;
        goto main_menu;
    }

    if (PlayingTicTacToe == true)
    {
        // reset board
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                TicTacToeBoard[r][c] = 0;

		// choose single or multiplayer
        cout << "Single Player (y/n)? ";
        cin >> IsSinglePlayer;
        system("cls");

		PrintTicTacToeBoard(TicTacToeBoard);

        if (IsSinglePlayer == 'y')
        {

            while (true)
            {
            
				PrintTicTacToeBoard(TicTacToeBoard);
				cin >> PlayerMove;
				PlayerMoveX(TicTacToeBoard, PlayerMove);
                PrintTicTacToeBoard(TicTacToeBoard);

                if ( CheckWinOrDraw(TicTacToeBoard) == !0 )
                {
                    winner = CheckWinOrDraw(TicTacToeBoard);
                    PrintTicTacToeBoard(TicTacToeBoard);
                    OutputWinMessage(winner);
					system("cls");
					goto main_menu;
				}
                
				RobotMoveO(TicTacToeBoard);
                PrintTicTacToeBoard(TicTacToeBoard);

                if (CheckWinOrDraw(TicTacToeBoard) == !0)
                {
                    winner = CheckWinOrDraw(TicTacToeBoard);
                    PrintTicTacToeBoard(TicTacToeBoard);
                    OutputWinMessage(winner);
                    system("cls");
                    goto main_menu;
                }
            
            }

		}
        else
        {
            while (true)
            {

                PrintTicTacToeBoard(TicTacToeBoard);
                cin >> PlayerMove;
                PlayerMoveX(TicTacToeBoard, PlayerMove);
                PrintTicTacToeBoard(TicTacToeBoard);

                if (CheckWinOrDraw(TicTacToeBoard) == !0)
                {
                    winner = CheckWinOrDraw(TicTacToeBoard);
                    PrintTicTacToeBoard(TicTacToeBoard);
                    OutputWinMessage(winner);
                    system("cls");
                    goto main_menu;
                }

                PrintTicTacToeBoard(TicTacToeBoard);
                cin >> PlayerMove;
                PlayerMoveO(TicTacToeBoard, PlayerMove);
                PrintTicTacToeBoard(TicTacToeBoard);

                if (CheckWinOrDraw(TicTacToeBoard) == !0)
                {
                    winner = CheckWinOrDraw(TicTacToeBoard);
                    PrintTicTacToeBoard(TicTacToeBoard);
                    OutputWinMessage(winner);
                    system("cls");
                    goto main_menu;
                }

            }
        }
    }
    return 0;
}