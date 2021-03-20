#ifndef my_board_h
#define my_board_h

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

#include "my_piece.h"

class board{
	private:
		board * last;												//stores the board before a move 
		AbstractPiece * thisboard [8][8];							//the board, with all the pieces

		int currentmove;											//can be 0 -> white or 1 -> black

	public:
		board();													//constructor for a new board with pieces
		board(board * oldBoard);									//copy constructor
		~board();													//destructor (delete all pieces etc.)

		AbstractPiece * GetPiece(int raw, int col){return thisboard[raw][col];};
		bool Occupied(int n_raw, int n_col){return (thisboard[n_raw][n_col] != NULL);};

		void Print();												
		std::string Unicode(type_piece type, color_piece color); 		//converts type+color in unicode char

		int GetCurrentMoveInt(){return currentmove;};				//returns 0 || 1 for white & black
		void SetCurrentMoveInt(int a){currentmove = a;};
		
		void InvertCurrentMoveInt(){if (currentmove==0)	currentmove=1; else	currentmove=0;};

		bool Castling(bool scan [8][8]);

		//Double can the board and compare two boards and find the move, if box occupied scan =true, else false
		bool Move(bool scan [8][8], bool scan2 [8][8]);				
};



board::board(){

	thisboard[0][0] = new Rook(white,0,0);
	thisboard[0][1] = new Knight(white,0,1);	
	thisboard[0][2] = new Bishop(white,0,2);
	thisboard[0][3] = new Queen(white,0,3);
	thisboard[0][4] = new King(white,0,4);
	thisboard[0][5] = new Bishop(white,0,5);
	thisboard[0][6] = new Knight(white,0,6);
	thisboard[0][7] = new Rook(white,0,7);

	thisboard[7][0] = new Rook(black,7,0);
	thisboard[7][1] = new Knight(black,7,1);
	thisboard[7][2] = new Bishop(black,7,2);
	thisboard[7][3] = new Queen(black,7,3);
	thisboard[7][4] = new King(black,7,4);
	thisboard[7][5] = new Bishop(black,7,5);
	thisboard[7][6] = new Knight(black,7,6);
	thisboard[7][7] = new Rook(black,7,7);

	for(int i = 0; i < 8; i++){
		thisboard[1][i] = new Pawn(white,1,i);
		thisboard[6][i] = new Pawn(black,6,i);		
	}

	for(int i = 0; i < 8; i++){
		for(int j = 2; j < 6; j++){
			thisboard[j][i] = NULL;
		}
	}

	currentmove = 0;
}

board::~board(){
	delete last;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++)
			delete thisboard[i][j];
	}
}
//-------------------------------------------------------

void board::Print(){
	for(int i = 7; i >= 0; i--){
		for(int j = 0; j < 8; j++){
			if(j == 0) std::cout << "|__";
			if (thisboard[i][j] != NULL){
				type_piece type = thisboard[i][j] -> GetType();
				color_piece color = thisboard[i][j] -> GetColor();
				std::cout << this -> Unicode(type,color);
			}
			else std::cout << "  ";
			if(j != 7) std::cout << "__|__";
			else std::cout << "__|\t" << i+1;
		}
		std::cout << "\n" << std::endl;
	}
	std::cout << "   a     b     c     d     e     f     g     h" << std::endl;
}

std::string board::Unicode(type_piece type, color_piece color){

	if(type == rook){	
		if(color == black) return "Tb";
		if(color == white) return "Tw";
	}
	if(type == knight){	
		if(color == black) return "Nb";
		if(color == white) return "Nw";
	}
	if(type == bishop){	
		if(color == black) return "Bb";
		if(color == white) return "Bw";
	}
	if(type == queen){	
		if(color == black) return "Qb";
		if(color == white) return "Qw";
	}
	if(type == pawn){	
		if(color == black) return "pb";
		if(color == white) return "pw";
	}
	if(type == king){	
		if(color == black) return "Kb";
		if(color == white) return "Kw";
	}
	return "  ";
}

//------------------------------------------------

bool board::Castling(bool scan [8][8]){				
	if (scan[0][5]==true && scan[0][6]==true && this->GetCurrentMoveInt()==0){					//WHITE
		thisboard[0][6] = this->GetPiece(0,4);									//king
	    thisboard[0][6]->ChangePos(0,6);
	  	thisboard[0][4] =NULL;

	  	thisboard[0][5] = this->GetPiece(0,7);									//rook
	    thisboard[0][5]->ChangePos(0,5);
	  	thisboard[0][7] = NULL;

	  	return true;
	}

	if (scan[0][2]==true && scan[0][3]==true && this->GetCurrentMoveInt()==0){
		thisboard[0][2] = this->GetPiece(0,4);									//king
	    thisboard[0][2]->ChangePos(0,2);
	  	thisboard[0][4] = NULL;

	  	thisboard[0][3] = this->GetPiece(0,4);									//rook
	    thisboard[0][3]->ChangePos(0,3);
	  	thisboard[0][4] = NULL;

	  	return true;
	}

	if (scan[7][5]==true && scan[7][6]==true && this->GetCurrentMoveInt()==1){					//BLACK
		thisboard[7][6] = this->GetPiece(7,4);									//king
	    thisboard[7][6]->ChangePos(7,6);
	  	thisboard[7][4] = NULL;

	  	thisboard[7][5] = this->GetPiece(7,7);									//rook
	    thisboard[7][5]->ChangePos(7,5);
	  	thisboard[7][7] = NULL;

	  	return true;
	}

	if (scan[7][2]==true && scan[7][3]==true && this->GetCurrentMoveInt()==1){
		thisboard[7][2] = this->GetPiece(7,4);									//king
	    thisboard[7][2]->ChangePos(7,2);
	  	thisboard[7][4] = NULL;

	  	thisboard[7][3] = this->GetPiece(7,4);									//rook
	    thisboard[7][3]->ChangePos(7,3);
	  	thisboard[7][4] = NULL;

	  	return true;
	}

	return false;
}
//----------------Easy function to compare two matrix----
bool areSame(bool scan [8][8], bool scan2 [8][8]){
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (scan[i][j] != scan2[i][j])
                return false;
    return true;
}
//-------------------------------------------------------
//two type of move: shift a piece (1), take a piece
bool board::Move(bool scan [8][8], bool scan2 [8][8]){ 					

	//I need two scan when a piece is taking, else one is enough. In this case I put scan=scan2
	bool notaken = areSame (scan, scan2);

	int i_old, j_old, i_new, j_new;
	int count=0; 								

	for(int i =0; i<8; i++){
		for(int j=0; j<8; j++){
			if (this->Occupied(i,j)!=scan[i][j] && this->Occupied(i,j)== true && this->GetPiece(i,j)->GetColor()==this->GetCurrentMoveInt()){
				i_old= i;
				j_old= j;
				count++;
			}
			if (this->Occupied(i,j)!=scan[i][j] && this->Occupied(i,j)== false){
				i_new= i;
				j_new= j;
				count++;
			}
			if (this->Occupied(i,j)!=scan[i][j] && this->Occupied(i,j)== true && notaken==false){ 
				i_new= i;
				j_new= j;
				count++;
			}
		}
	}

	if (count==4)
		return Castling(scan);
	
	if(count ==2){                           			// shift a piece
	    thisboard[i_new][j_new] = this->GetPiece(i_old,j_old);
	    thisboard[i_new][j_new]->ChangePos(i_new,j_new);
	  	thisboard[i_old][j_old] = NULL;

	  	this->InvertCurrentMoveInt();
	  	return true;
	}

	// Take an other piece: that's critic. I can't find an easy way to understand which piece is taken
	// So i suppose two scan, in the first the enemy's piece dissapears and in the second one i'll put the piece
	if (count ==1 && this->GetPiece(i_new,j_new)->GetColor()!=this->GetCurrentMoveInt()){				
		thisboard[i_new][j_new]->SetAlive(false);										
		
		for(int i =0; i<8; i++){
			for(int j=0; j<8; j++)
				if (this->Occupied(i,j)!=scan2[i][j] && this->Occupied(i,j)== true && this->GetPiece(i,j)->GetColor()==this->GetCurrentMoveInt()){
					i_old= i;
					j_old= j;
					count++;
				}
		}
		thisboard[i_new][j_new] = this->GetPiece(i_old,j_old);
	    thisboard[i_new][j_new]->ChangePos(i_new,j_new);
	  	thisboard[i_old][j_old] = NULL;

	  	this->InvertCurrentMoveInt();
	  	return true;
	}

	std::cout<<"\n *****\nError e count "<<count<<"\n ******\n "<<std::endl;
	return false;									//scan failed
}

#endif