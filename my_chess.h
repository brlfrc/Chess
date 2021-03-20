#ifndef my_chess_h
#define my_chess_h

#include "my_board.h"

//----------------------------------------------------------------
//Game Function. Obv not really of the library, but useful
//----------------------------------------------------------------
class Game{

	protected:
		board * currentgame= new board();

		bool whitechecked;
		bool whitemated;

		bool blackchecked;
		bool blackmated;

		bool possiblemoves [8][8];

	public:
		Game();

		//Possible moves of piece in the position row, col
		bool Getpossiblemoves(int i, int j){return possiblemoves[i][j];};
		void Studypossiblemoves(AbstractPiece* piece);                    
		void Resetpossiblemoves(){for(int i =0; i<8;i++) {for(int j=0; j<8;j++) possiblemoves[i][j]=false;} };
		bool CanMove(AbstractPiece* piece, int row_f, int col_f);   //piece ---move?---->(row_f,col_f)

		//checked
		bool GetCheck(color_piece color){if (color==white) return whitechecked; else return blackchecked;}
		bool GetMated(color_piece color){if (color==white) return whitemated; else return blackmated;}
		void ResetChecks(color_piece color){if (color==white) whitechecked=false; else blackchecked=false;}
		int* FindKing(color_piece color);
		void CheckChecks(color_piece color);
		void CheckMated(color_piece color);        //missing

		//moving

};

//----------------------------------------------------------------

void Game::Studypossiblemoves(AbstractPiece* piece){
	this->Resetpossiblemoves();

	if (currentgame->GetCurrentMoveInt()==0 && whitechecked==true){

	}
	if (currentgame->GetCurrentMoveInt()==0 && blackchecked==true){

	}
	if (piece== NULL){
		std::cout<<"(line 52, my_chess.h) Error, there is no piece in this position"<<std::endl;
		return;
	}

	color_piece color= piece->GetColor();
	int row = piece->GetRow();
	int col = piece->GetCol();

	switch (piece->GetType()){

		case (rook):{
			
			int a = 1;
			while(col+a<8){
				if(currentgame -> Occupied(row,col+a) == false)
					possiblemoves[row][col+a] = true;
				else{
					if(currentgame->GetPiece(row,col+a)->GetColor() != color){
						possiblemoves[row][col+a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(col-a>=0){
				if(currentgame -> Occupied(row,col-a) == false)
					possiblemoves[row][col-a] = true;
				else{
					if(currentgame->GetPiece(row,col-a)->GetColor() != color){
						possiblemoves[row][col-a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(row+a<8){
				if(currentgame -> Occupied(row+a,col) == false)
					possiblemoves[row+a][col] = true;
				else{
					if(currentgame -> GetPiece(row+a,col) -> GetColor() != color){
						possiblemoves[row+a][col] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(row-a>=0){
				if(currentgame -> Occupied(row-a,col) == false)
					possiblemoves[row-a][col] = true;
				else{
					if(currentgame -> GetPiece(row-a,col) -> GetColor() != color){
						possiblemoves[row-a][col] = true;
						break;
					}
					else break;
				}
				a++;
			}
		}

		case (knight):{

			if(row+1<8 && col+2<8){
				if (currentgame -> Occupied(row+1,col+2) == false)
					possiblemoves[row+1][col+2] = true;
				else if (currentgame -> GetPiece(row+1,col+2) -> GetColor() != color)
					possiblemoves[row+1][col+2] = true;
			}

			if(row-1<8 && col+2<8){
				if (currentgame -> Occupied(row-1,col+2) == false)
					possiblemoves[row-1][col+2] = true;
				else if (currentgame -> GetPiece(row-1,col+2) -> GetColor() != color)
					possiblemoves[row-1][col+2] = true;
			}

			if(row+1<8 && col-2<8){
				if (currentgame -> Occupied(row+1,col-2) == false)
					possiblemoves[row+1][col-2] = true;
				else if (currentgame -> GetPiece(row+1,col+2) -> GetColor() != color)
					possiblemoves[row+1][col-2] = true;
			}

			if(row-1<8 && col-2<8){
				if (currentgame -> Occupied(row-1,col-2) == false)
					possiblemoves[row-1][col-2] = true;
				else if (currentgame -> GetPiece(row+1,col+2) -> GetColor() != color)
					possiblemoves[row-1][col-2] = true;
			}

			if(row+2<8 && col+1<8){
				if (currentgame -> Occupied(row+2,col+1) == false)
					possiblemoves[row+2][col+1] = true;
				else if (currentgame -> GetPiece(row+2,col+1) -> GetColor() != color)
					possiblemoves[row+2][col+1] = true;
			}

			if(row-2<8 && col+1<8){
				if (currentgame -> Occupied(row-2,col+1) == false)
					possiblemoves[row-2][col+1] = true;
				else if (currentgame -> GetPiece(row-1,col+1) -> GetColor() != color)
					possiblemoves[row-2][col+1] = true;
			}

			if(row+2<8 && col-1<8){
				if (currentgame -> Occupied(row+2,col-1) == false)
					possiblemoves[row+2][col-1] = true;
				else if (currentgame -> GetPiece(row+1,col+2) -> GetColor() != color)
					possiblemoves[row+2][col-1] = true;
			}

			if(row-2<8 && col-1<8){
				if (currentgame -> Occupied(row-2,col-1) == false)
					possiblemoves[row-2][col-1] = true;
				else if (currentgame -> GetPiece(row+1,col+2) -> GetColor() != color)
					possiblemoves[row-2][col-1] = true;
			}
		}

		case(bishop):{

			int a = 1;
			while(col+a<8 && col+a<8){
				if(currentgame -> Occupied(row,col+a) == false)
					possiblemoves[row+a][col+a] = true;
				else{
					if(currentgame->GetPiece(row,col+a)->GetColor() != color){
						possiblemoves[row+a][col+a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(col+a<8 && col-a>=0){
				if(currentgame -> Occupied(row+a,col-a) == false)
					possiblemoves[row+a][col-a] = true;
				else{
					if(currentgame->GetPiece(row+a,col-a)->GetColor() != color){
						possiblemoves[row+a][col-a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(col-a>=8 && col+a<0){
				if(currentgame -> Occupied(row-a,col+a) == false)
					possiblemoves[row-a][col+a] = true;
				else{
					if(currentgame->GetPiece(row-a,col+a)->GetColor() != color){
						possiblemoves[row-a][col+a] = true;
						break;
					}
					else break;
				}
				a++;
			}


			a = 1;
			while(col-a>=8 && col-a>=8){
				if(currentgame -> Occupied(row-a,col-a) == false)
					possiblemoves[row-a][col-a] = true;
				else{
					if(currentgame->GetPiece(row-a,col-a)->GetColor() != color){
						possiblemoves[row-a][col-a] = true;
						break;
					}
					else break;
				}
				a++;
			}
		}

		case(queen):{

			int a = 1;
			while(col+a<8){
				if(currentgame -> Occupied(row,col+a) == false)
					possiblemoves[row][col+a] = true;
				else{
					if(currentgame->GetPiece(row,col+a)->GetColor() != color){
						possiblemoves[row][col+a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(col-a>=0){
				if(currentgame -> Occupied(row,col-a) == false)
					possiblemoves[row][col-a] = true;
				else{
					if(currentgame->GetPiece(row,col-a)->GetColor() != color){
						possiblemoves[row][col-a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(row+a<8){
				if(currentgame -> Occupied(row+a,col) == false)
					possiblemoves[row+a][col] = true;
				else{
					if(currentgame -> GetPiece(row+a,col) -> GetColor() != color){
						possiblemoves[row+a][col] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(row-a>=0){
				if(currentgame -> Occupied(row-a,col) == false)
					possiblemoves[row-a][col] = true;
				else{
					if(currentgame -> GetPiece(row-a,col) -> GetColor() != color){
						possiblemoves[row-a][col] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(col+a<8 && col+a<8){
				if(currentgame -> Occupied(row,col+a) == false)
					possiblemoves[row+a][col+a] = true;
				else{
					if(currentgame->GetPiece(row,col+a)->GetColor() != color){
						possiblemoves[row+a][col+a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(col+a<8 && col-a>=0){
				if(currentgame -> Occupied(row+a,col-a) == false)
					possiblemoves[row+a][col-a] = true;
				else{
					if(currentgame->GetPiece(row+a,col-a)->GetColor() != color){
						possiblemoves[row+a][col-a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(col-a>=8 && col+a<0){
				if(currentgame -> Occupied(row-a,col+a) == false)
					possiblemoves[row-a][col+a] = true;
				else{
					if(currentgame->GetPiece(row-a,col+a)->GetColor() != color){
						possiblemoves[row-a][col+a] = true;
						break;
					}
					else break;
				}
				a++;
			}


			a = 1;
			while(col-a>=8 && col-a>=8){
				if(currentgame -> Occupied(row-a,col-a) == false)
					possiblemoves[row-a][col-a] = true;
				else{
					if(currentgame->GetPiece(row-a,col-a)->GetColor() != color){
						possiblemoves[row-a][col-a] = true;
						break;
					}
					else break;
				}
				a++;
			}
		}

		case(king):{
			for(int a = -1; a < 2; a++){
				for(int b = -1; b < 2; b++){
					bool rowbool = row+a >= 0 && row+a < 8;
					bool colbool = col+b >= 0 && col+b < 8;
					if(rowbool && colbool) 
						if(currentgame -> GetPiece(row+a,col+b) -> GetColor() != color)
							possiblemoves[row+a][col+b] = true;
				}
			}
		}

		case(pawn):{
			if(color == white){
				if(currentgame->GetPiece(row,col)->GetMoved()==false){
					if(currentgame -> Occupied(row+1, col) == false){
						possiblemoves[row+1][col] = true;
						if(currentgame -> Occupied(row+2, col) == false){
							possiblemoves[row+2][col] = true;
						}
					}
				}
				else{
					if(row+1 < 8){
						if(currentgame -> Occupied(row+1, col) == false) possiblemoves[row+1][col] = true;
					}
				}
				if(row + 1 < 8 && col + 1 < 8){
					if(currentgame -> GetPiece(row+1,col+1) -> GetColor() != color && currentgame -> Occupied(row+1,col+1))
						possiblemoves[row+1][col+1] = true;
				}
				if(row + 1 < 8 && col - 1 >= 0){
					if(currentgame -> GetPiece(row+1,col-1) -> GetColor() != color && currentgame -> Occupied(row+1,col-1))
						possiblemoves[row+1][col-1] = true;
				}
			}
			if(color == black){
				if(currentgame->GetPiece(row,col)->GetMoved()==false){
					if(currentgame -> Occupied(row-1, col) == false){
						possiblemoves[row-1][col] = true;
						if(currentgame -> Occupied(row-2, col) == false){
							possiblemoves[row-2][col] = true;
						}
					}
				}
				else{
					if(row-1 >= 0){
						if(currentgame -> Occupied(row-1, col) == false) possiblemoves[row-1][col] = true;
					} 
				}
				if(row - 1 >= 0 && col + 1 < 8){
					if(currentgame -> GetPiece(row-1,col+1) -> GetColor() != color && currentgame -> Occupied(row-1,col+1))
						possiblemoves[row-1][col+1] = true;
				}
				if(row - 1 >= 0 && col - 1 >= 0){
					if(currentgame -> GetPiece(row-1,col-1) -> GetColor() != color && currentgame -> Occupied(row-1,col-1))
						possiblemoves[row-1][col-1] = true;
				}
			}
		}
	}
	return;
}

bool Game::CanMove(AbstractPiece* piece, int row_f, int col_f){
	this->Studypossiblemoves(piece);
	return this->Getpossiblemoves(row_f, col_f);
}
//----------------------------------------------------------------
int* Game::FindKing(color_piece color){
	int* pos;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if (currentgame->GetPiece(i,j)!=NULL){
				if (currentgame->GetPiece(i,j)->GetType()==king && currentgame->GetPiece(i,j)->GetColor()==color){
					pos[0]=i;
					pos[1]=j;
					return pos;
				}

			}
		}
	}
}

void Game::CheckChecks(color_piece color){
	this->ResetChecks(color);

	int* pos=this->FindKing(color);

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if (currentgame->GetPiece(i,j)!=NULL){
				if (currentgame->GetPiece(i,j)->GetColor()!=color){
					if (CanMove(currentgame->GetPiece(i,j), pos[0], pos[1])==true){
						if (color==white) whitechecked==true;
						if (color==black) blackchecked==true;
					}
				}

			}
		}
	}
}

void Game::CheckMated(color_piece color){
	//Controlla le case vicine al re
	//Cerca chi da lo scacco e lungo che direzioni e controlla che ogni pezzo non possa interporsi o mangiare
	//NB poni attenzione agli scacchi multipli
}
//----------------------------------------------------------------


#endif