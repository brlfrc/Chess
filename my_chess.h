#ifndef my_chess_h
#define my_chess_h

#include "my_board.h"

//----------------------------------------------------------------
//Game Function. Obv not really of the library, but useful
//----------------------------------------------------------------

void StartGame(){
	board * currentgame= new board();

	delete currentgame;
}

#endif