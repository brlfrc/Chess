#ifndef my_chess_h
#define my_chess_h

#include <string>
#include <vector>
#include <iostream>

class game;
class board;
class piece;
class nullpiece;
class rook;
class knight;
class bishop;
class queen;
class pawn;
class king;

//------------------------------------------------------

class board{
	private:
		board * last;									//stores the board before a move 
		piece * thisboard [8][8];						//the board, with all the pieces

		int currentmove;								//can be 0 -> white or 1 -> black

	public:
		board();										//constructor for a new board with pieces
		board(board * oldBoard);						//copy constructor
		~board();										//destructor (delete all pieces etc.)

		piece * GetPiece(int raw, int col);				//returns piece from raw and column
		
		bool Occupied(int n_raw, int n_col);			//is a position occupied?

		int GetCurrentMoveInt();						//returns 0 || 1 for white & black
		int GetMove();									//returns move # (1,2,3,4...)
		void SetCurrentMoveInt(int a);					//set currentmove
		void InvertCurrentMoveInt();				//Invert 0.1 currentmove

		bool Castling(bool scan [8][8]);
		bool Move(bool scan [8][8], bool scan2 [8][8]);	//Double can the board and compare two boards and find the move
														//if box occupied scan =true, else false
};

class piece{
	protected:
		int raw;										//raw of piece
		int col;										//col of piece
		int color;										//color of piece
															// white    -> 0
															// black  	-> 1
		int type;										//type of piece 
															//rook 		-> 1
															//kinght	-> 2
															//bishop 	-> 3
															//queen 	-> 4
															//pawn		-> 5
															//king 		-> 6
		bool alive;										//is this piece alive?

	public:
		piece(){};										//default constructor (not used)

		int GetRaw();									//retun raw
		int GetCol();									//retun col
		bool GetAlive();								//retun alive status							
		int GetColor();								//retun color
		int GetType();									//retun # for type

		bool SetAlive(bool a);							//set alive status
		void ChangePos(int n_raw, int n_col);			//change both raw and col

		
};

class nullpiece : public piece{
	public:
		nullpiece(int riga, int colonna);
		void update(board * myBoard);
};

class rook : public piece{
	public:
		rook(int colore, int riga, int colonna);
		void update(board * myBoard);
};

class knight : public piece{
	public:
		knight(int colore, int riga, int colonna);
		void update(board * myBoard);
};

class bishop : public piece{
	public:
		bishop(int colore, int riga, int colonna);
		void update(board * myBoard);
};

class queen : public piece{
	public:
		queen(int colore, int riga, int colonna);
		void update(board * myBoard);
};

class pawn : public piece{
	public:
		pawn(int colore, int riga, int colonna);
		void update(board * myBoard);
};

class king : public piece{
	public:
		king(int colore, int riga, int colonna);
		void update(board * myBoard);
};

//----------------------------------------------------------------
//Game Function. Obv not really of the library, but useful
//----------------------------------------------------------------

void StartGame(){
	board * currentgame= new board();

	delete currentgame;
}


#include "my_board.h"
#include "my_piece.h"

#endif