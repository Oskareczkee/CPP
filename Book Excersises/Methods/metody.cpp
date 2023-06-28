#include <iostream>
using namespace std;


struct tictactoe
{
    enum sign { circle = 1, cross = 10 };
    enum player { pone = 1, ptwo = 2 };//pone is circle, ptwo is cross 
    int board[3][3];
    int x;
    int y;
    sign s=circle;
    player p=pone;
    void start_game(int board[][3]);//funtion to give initialize board array fields to 0
    void display_board(int board[][3]); //const to not change table by accident
    void change_player(player& p, sign& s);
    int check_win(player &p,int board[][3]);//check above
    int move(player &p, sign &s , int x, int y, int board[][3]);
};

void tictactoe::change_player(player& p, sign& s)
{
    if (p == pone)
    {
        p = ptwo;
        s = cross;
    }
    else
    {
        p = pone;
        s = circle;
    }
}

void tictactoe::display_board(int board[][3])
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            switch (board[x][y])
            {
            case 0:
            {
                cout << "  0  ";
                break;
            }
            case 1:
            {
                cout << "  O  ";
                break;
            }
            case 10:
            {
                cout << "  X  ";
                break;
            }
            default:
            {
                cout << "Error !";
                break;
            }
            }
        }
        cout << "\n";
    }
}

void tictactoe::start_game(int board[][3])
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            board[x][y] = 0;
        }
    }
}

int tictactoe::move(player &p, sign &s, int x, int y, int board[][3])
{
    if (board[x][y] != 0)
    {
        cout << "This field is already taken\n";
        return 0;
    }
    board[x][y] = s;
    return 1;
}


//top 10 żydowskich metod na sprawdzenie wygranej w kolko i krzyzyk
int tictactoe::check_win(player& p, int board[][3])
{
    int count = 0;
    int array[9];
    int shit = 0;
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            array[count] = board[x][y];
            count++;
        }
    }
    for (int x = 0; x < 9; x++)
    {
        if (array[x] == 0)
        {
            break;
        }
        shit++;
    }
    if (shit == 9)
    {
        cout << "Game ended with tie !\nNo one wins :(\n";
        return 2;
    }
    if (((array[0] + array[1] + array[2]) == 30) || ((array[0] + array[1] + array[2]) == 3))
    {
        cout << "Player " << p << " won !";
        return 1;
    }
    if (((array[3] + array[4] + array[5]) == 30) || ((array[3] + array[4] + array[5]) == 3))
    {
        cout << "Player " << p << " won !";
        return 1;
    }
    if (((array[6] + array[7] + array[8]) == 30) || ((array[6] + array[7] + array[8]) == 3))
    {
        cout << "Player " << p << " won !";
        return 1;
    }
    if (((array[0] + array[3] + array[6]) == 30) || ((array[0] + array[3] + array[6]) == 3))
    {
        cout << "Player " << p << " won !";
        return 1;
    }
    if (((array[1] + array[4] + array[7]) == 30) || ((array[1] + array[4] + array[7]) == 3))
    {
        cout << "Player " << p << " won !";
        return 1;
    }
    if (((array[2] + array[5] + array[8]) == 30) || ((array[2] + array[5] + array[8]) == 3))
    {
        cout << "Player " << p << " won !";
        return 1;
    }
    if (((array[0] + array[4] + array[8]) == 30) || ((array[0] + array[4] + array[8]) == 3))
    {
        cout << "Player " << p << " won !";
        return 1;
    }
    if (((array[2] + array[4] + array[6]) == 30) || ((array[2] + array[4] + array[6]) == 3))
    {
        cout << "Player " << p << " won !";
        return 1;
    }
    return 0;
}


int main()
{
    tictactoe game;
    cout << "Gdybym kiedys to odpalil, ten program to tylko prototyp, nie ma on na celu działania w pełni, mial on za zadanie nauczenie mnie pisania metod, prawdopodobnie ten sam program, tylko"
        << "Napisany w klasie tez gdzies sie znajduje, i mial mnie zaznajomic z klasami :/\n\n";
    game.start_game(game.board);
        game.display_board(game.board);
        do
        {
            cout << "Type x and y coordinate: \n";
            cin >> game.x >> game.y;
            game.move(game.p, game.s, game.x, game.y, game.board);
            if (game.check_win(game.p, game.board))
            {
                break;
            }
            game.display_board(game.board);
            game.change_player(game.p, game.s);
        } while (1);
}