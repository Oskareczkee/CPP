#include "HexBoardLoader.h"

int HexBoardLoader::get_size()
{
    //ignore first line
    stream.ignore(INT_MAX, '\n');
    int out_size = 0;

    //load till we do not encounter single < character
    char c;
    while (true) {
        stream.get(c);
        //ignore all whitespaces
        while (isspace(c))
            stream.get(c);

        if (c == '<') {
            out_size++;
            break;
        }

        out_size++;
        stream.ignore(INT_MAX, '\n'); //ignore this line
    }

    stream.seekg(0,stream.beg);//set stream to the beginning for further loading
    return out_size;
}

HexBoard* HexBoardLoader::load_board()
{
    HexBoard* out = new HexBoard();

    //create square board
    out->_size = get_size();
    out->_board = new HexTile*[out->_size];
    for (int x = 0; x < out->_size; x++)
        out->_board[x] = new HexTile[out->_size];

    //ignore first line
    stream.ignore(INT_MAX, '\n');
    char c;

    //load first half
    for (int x = 0; x < out->_size; x++)
    {
        for (int y = 0; y <= x ; y++)
        {
            stream.ignore(INT_MAX, (char)HexBoardTiles::TILE_BEGIN); //read till tile begin
            stream >> c; //read character
            if (c == (char)HexBoardTiles::TILE_END) //if chatacter was tile end, then all spaces were skipped, and there was empty tile
                out->_board[x-y][y].pawn_type = PawnType::NONE;
            else if (c == (char)PawnType::RED)
            {
                out->_board[x-y][y].pawn_type = PawnType::RED;
                out->red_pawns++;
            }
            else
            {
                out->_board[x-y][y].pawn_type = PawnType::BLUE;
                out->blue_pawns++;
            }
        }

        stream.ignore(INT_MAX, '\n'); //load another line
    }


    
    //i literally don't know how to do this better -> look into docs -> reading data from input
    int d = 1;
    int a = out->_size-1;
    //load second half
    for (int x = out->_size-2; x >=0 ; x--)
    {
        for (int y = d; y < out->_size; y++)
        {
            stream.ignore(INT_MAX, (char)HexBoardTiles::TILE_BEGIN);
            stream >> c;
            if (c == (char)HexBoardTiles::TILE_END)
                out->_board[a--][y].pawn_type = PawnType::NONE;
            else if (c == (char)PawnType::RED)
            {
                out->_board[a--][y].pawn_type = PawnType::RED;
                out->red_pawns++;
            }
            else
            {
                out->_board[a--][y].pawn_type = PawnType::BLUE;
                out->blue_pawns++;
            }
        }
        stream.ignore(INT_MAX, '\n'); //load another line
        d++;
        a = out->_size-1;
    }

    //reverse the columns for proper coordinate usage
    std::reverse(out->_board, out->_board+out->_size);
    
    return out;
}
