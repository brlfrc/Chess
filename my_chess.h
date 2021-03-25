#ifndef my_chess_h
#define my_chess_h

#include "my_board.h"
#include <cmath>

//----------------------------------------------------------------
//Game Function. Obv not really of the library, but useful
//----------------------------------------------------------------
class Game{

	protected:
		board * currentgame= new board();

		bool whitechecked;
		bool blackchecked;

		bool possiblemoves [8][8];

	public:
		Game(){};

		//Possible moves of piece in the position row, col
		//N.B: in this possible moves i don't consider any checks, i'll consider it during the move
		bool Getpossiblemoves(int i, int j){return possiblemoves[i][j];};
		void Studypossiblemoves(AbstractPiece* piece);                    
		void Resetpossiblemoves(){for(int i =0; i<8;i++) {for(int j=0; j<8;j++) possiblemoves[i][j]=false;} };
		bool CanMove(AbstractPiece* piece, int row, int col);   //make possiblemove and return it
		bool ValidMove(AbstractPiece* piece, int row_f, int col_f);   //Considering checks a move is valid?
		
		//check
		bool GetCheck(color_piece color){if (color==white) return whitechecked; else return blackchecked;}
		void ResetChecks(color_piece color){if (color==white) whitechecked=false; else blackchecked=false;}
		
		AbstractPiece* FindKing(color_piece color);
		bool BoxCheck(color_piece color,int row, int col);
		bool CheckChecks(color_piece color);
		AbstractPiece* FindCheckPiece(color_piece color);
		bool BoxAttack(color_piece color,int row, int col);   //There is a piece that can go in (row, col)
		void LineAttack(AbstractPiece* K, AbstractPiece* Attackpiece, int* size, int* line);  //give the line attack
		bool CheckMated(color_piece color);        //missing

		//Castling
		bool Castling(color_piece color, int i); //castling move code 8 8 8 0 (short) 8 8 8 1 (long)
		void CastlingMove(color_piece color, int i);

		//Capture Enpassant
		bool Enpassant(AbstractPiece* piece, int row_f, int col_f);
		void EnpassantMove(AbstractPiece* piece, int row_f, int col_f);
		void EnpassantReset(color_piece color);

		//moving
		bool Turn(color_piece color, int row_i, int col_i, int row_f, int col_f);
		void Match();
};

//----------------------------------------------------------------

void Game::Studypossiblemoves(AbstractPiece* piece){
	this->Resetpossiblemoves();

	if (piece== NULL){
		std::cout<<"(line 63, my_chess.h) Error, there is no piece in this position"<<std::endl;
		return;
	}

	color_piece color= piece->GetColor();
	int row = piece->GetRow();
	int col = piece->GetCol();

	switch (piece->GetType()){

		case rook:{
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
			break;
		}

		case knight:{

			if(row+1<8 && col+2<8){
				if (currentgame -> Occupied(row+1,col+2) == false)
					possiblemoves[row+1][col+2] = true;
				else if (currentgame -> GetPiece(row+1,col+2) -> GetColor() != color)
					possiblemoves[row+1][col+2] = true;
			}

			if(row-1>=0 && col+2<8){
				if (currentgame -> Occupied(row-1,col+2) == false)
					possiblemoves[row-1][col+2] = true;
				else if (currentgame -> GetPiece(row-1,col+2) -> GetColor() != color)
					possiblemoves[row-1][col+2] = true;
			}

			if(row+1<8 && col-2>=0){
				if (currentgame -> Occupied(row+1,col-2) == false)
					possiblemoves[row+1][col-2] = true;
				else if (currentgame -> GetPiece(row+1,col-2) -> GetColor() != color)
					possiblemoves[row+1][col-2] = true;
			}

			if(row-1>=0 && col-2>=0){
				if (currentgame -> Occupied(row-1,col-2) == false)
					possiblemoves[row-1][col-2] = true;
				else if (currentgame -> GetPiece(row-1,col-2) -> GetColor() != color)
					possiblemoves[row-1][col-2] = true;
			}

			if(row+2<8 && col+1<8){
				if (currentgame -> Occupied(row+2,col+1) == false)
					possiblemoves[row+2][col+1] = true;
				else if (currentgame -> GetPiece(row+2,col+1) -> GetColor() != color)
					possiblemoves[row+2][col+1] = true;
			}

			if(row-2>=0 && col+1<8){
				if (currentgame -> Occupied(row-2,col+1) == false)
					possiblemoves[row-2][col+1] = true;
				else if (currentgame -> GetPiece(row-2,col+1) -> GetColor() != color)
					possiblemoves[row-2][col+1] = true;
			}

			if(row+2<8 && col-1>=0){
				if (currentgame -> Occupied(row+2,col-1) == false)
					possiblemoves[row+2][col-1] = true;
				else if (currentgame -> GetPiece(row+2,col-1) -> GetColor() != color)
					possiblemoves[row+2][col-1] = true;
			}


			if(row-2>=0 && col-1>=0){
				if (currentgame -> Occupied(row-2,col-1) == false)
					possiblemoves[row-2][col-1] = true;
				else if (currentgame -> GetPiece(row-2,col-1) -> GetColor() != color)
					possiblemoves[row-2][col-1] = true;
			}

			break;
		}
		

		case bishop:{
			int a = 1;
			while(row+a<8 && col+a<8){
				if(currentgame -> Occupied(row+a,col+a) == false)
					possiblemoves[row+a][col+a] = true;
				else{
					if(currentgame->GetPiece(row+a,col+a)->GetColor() != color){
						possiblemoves[row+a][col+a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(row+a<8 && col-a>=0){
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
			while(row-a>=0 && col+a<8){
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
			while(row-a>=0 && col-a>=0){
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
			break;
		}

		case queen:{

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
			while(row+a<8 && col+a<8){
				if(currentgame -> Occupied(row+a,col+a) == false)
					possiblemoves[row+a][col+a] = true;
				else{
					if(currentgame->GetPiece(row+a,col+a)->GetColor() != color){
						possiblemoves[row+a][col+a] = true;
						break;
					}
					else break;
				}
				a++;
			}

			a = 1;
			while(row+a<8 && col-a>=0){
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
			while(row-a>=0 && col+a<8){
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
			while(row-a>=0 && col-a>=0){
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
			break;
		}

		case king:{
			for(int a = -1; a < 2; a++){
				for(int b = -1; b < 2; b++){
					bool rowbool = row+a >= 0 && row+a < 8;
					bool colbool = col+b >= 0 && col+b < 8;
					if(rowbool && colbool){
						if(currentgame -> GetPiece(row+a,col+b) == NULL)
							possiblemoves[row+a][col+b] = true;
						else if(currentgame -> GetPiece(row+a,col+b) -> GetColor() != color)
							possiblemoves[row+a][col+b] = true;
					} 	
				}
			}
			break;
		}

		case pawn :{

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
					if(currentgame -> Occupied(row+1,col+1)==true)
						if(currentgame -> GetPiece(row+1,col+1) -> GetColor() != color)
							possiblemoves[row+1][col+1] = true;
				}
				if(row + 1 < 8 && col - 1 >= 0){
					if(currentgame -> Occupied(row+1,col-1)==true)
						if(currentgame -> GetPiece(row+1,col-1) -> GetColor() != color)
							possiblemoves[row+1][col-1] = true;
				}
			}

			if (color == black){
				
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
					if(currentgame -> Occupied(row-1,col+1)==true)
						if(currentgame -> GetPiece(row-1,col+1) -> GetColor() != color)
							possiblemoves[row-1][col+1] = true;
				}

				if(row - 1 >= 0 && col - 1 >= 0){
					if(currentgame -> Occupied(row-1,col-1)==true)
						if(currentgame -> GetPiece(row-1,col-1) -> GetColor() != color)
							possiblemoves[row-1][col-1] = true;
				}
			}
			break;
		}
	}
	return;
}


bool Game::CanMove(AbstractPiece* piece, int row, int col){
	this->Studypossiblemoves(piece);
	return  possiblemoves[row][col];
}

// A move is valid if a piece can go in the final position and if that's not open to some enemy checks.
// I need two function (CanMove and ValidMove), so CheckChecks can work without circoular call.
bool Game::ValidMove(AbstractPiece* piece, int row_f, int col_f){
	currentgame->Remember();

	if (this->CanMove(piece,row_f, col_f)== true){

		currentgame->Move(piece, row_f, col_f);

		if (this->CheckChecks(piece->GetColor())==false){
			currentgame->Restore();

			if (piece->GetType()==king){
				if (abs(this->FindKing(white)->GetRow()-this->FindKing(black)->GetRow())>1 && abs(this->FindKing(white)->GetCol()-this->FindKing(black)->GetCol()))
					return true;
			}
			else
				return true;
		}
		else{
			if (piece->GetType()!=king)
				std::cout<<"(line 477, my_chess.h) there is or open check"<<std::endl;
		}
	}
	currentgame->Restore();
	return false;
}

//----------------------------------------------------------------
AbstractPiece* Game::FindKing(color_piece color){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if (currentgame->GetPiece(i,j)!=NULL){
				if (currentgame->GetPiece(i,j)->GetType()==king && currentgame->GetPiece(i,j)->GetColor()==color){
					return currentgame->GetPiece(i,j);
				}

			}
		}
	}
}

bool Game::BoxCheck(color_piece color,int row, int col){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if (currentgame->GetPiece(i,j)!=NULL){
				if (currentgame->GetPiece(i,j)->GetColor()!=color){
					if (CanMove(currentgame->GetPiece(i,j), row, col)==true){
						return true;
					}
				}

			}
		}
	}
	return false;
}

bool Game::CheckChecks(color_piece color){
	AbstractPiece* K=this->FindKing(color);  //that's doesn't work
	K->GetRow();
	if (BoxCheck(color, K->GetRow(), K->GetCol())==true){
		if (color==white) whitechecked==true;
		if (color==black) blackchecked==true;
		return true;
	}
	return false;
}

AbstractPiece* Game::FindCheckPiece(color_piece color){
	this->ResetChecks(color);
	AbstractPiece* Attackpiece;

	AbstractPiece* K=this->FindKing(color);
	int index=0;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if (currentgame->GetPiece(i,j)!=NULL){
				if (currentgame->GetPiece(i,j)->GetColor()!=color){
					if (CanMove(currentgame->GetPiece(i,j), K->GetRow(), K->GetCol())==true){
						Attackpiece=currentgame->GetPiece(i,j);
						index=index+1;				
					}
				}
			}
		}
	}
	if (index > 1) return NULL;
	else return Attackpiece;
}

bool Game::BoxAttack(color_piece color,int row, int col){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if (currentgame->GetPiece(i,j)!=NULL){
				if (currentgame->GetPiece(i,j)->GetColor()==color && currentgame->GetPiece(i,j)->GetType()!=king){
					if (ValidMove(currentgame->GetPiece(i,j), row, col)==true){
						return true;
					}
				}

			}
		}
	}
	return false;
}
 
void Game::LineAttack(AbstractPiece* K, AbstractPiece* Attackpiece, int* size, int* line){
	//Return the point in this way. line[1,3,5]=row_1,2,3 while line[2,4,6]=col_1,2,3 
	//N.B return also the position of Attackpiece 
	int index=0;

	if (Attackpiece->GetType()==rook || Attackpiece->GetType()==queen){
		if (K->GetCol()==Attackpiece->GetCol()){
			if (K->GetRow()>Attackpiece->GetRow()){
				for (int i = Attackpiece->GetRow(); i<K->GetRow(); i++){
					line[index]= i;
					line[index+1]=K->GetCol();
					index=index+2;
				}
				size[0]= index-1;
				return;
			}
			else {
				for (int i = K->GetRow(); i<Attackpiece->GetRow()+1; i++){
					line[index]= i;
					line[index+1]=K->GetCol();
					index=index+2;
				}
				size[0]= index-1;
				return;
			}
		}
		if (K->GetRow()==Attackpiece->GetRow()){
			if (K->GetCol()>Attackpiece->GetCol()){
				for (int i = Attackpiece->GetCol(); i<K->GetCol(); i++){
					line[index]= K->GetRow(); 
					line[index+1]=i;
					index=index+2;
				}
				size[0]= index-1;
				return;
			}
			else {
				for (int i = K->GetCol(); i<Attackpiece->GetCol()+1; i++){
					line[index]= K->GetRow();
					line[index+1]= i;
					index=index+2;
				}
				size[0]= index-1;
				return;
			}
		}

	}

	if (Attackpiece->GetType()==bishop || Attackpiece->GetType()==queen){
		if (K->GetCol()>Attackpiece->GetCol()){
			if (K->GetRow()>Attackpiece->GetRow()){
				for (int i = 0; i < (K->GetRow()-Attackpiece->GetRow()); i++){
					line[index]= Attackpiece->GetRow() + i;
					line[index+1]= Attackpiece->GetCol() + i;
					index=index+2;
				}
				size[0]= index-1;
				return;
			}
			else {
				for (int i = 0; i < (Attackpiece->GetRow()-K->GetRow()); i++){
					line[index]= Attackpiece->GetRow() - i;
					line[index+1]= Attackpiece->GetCol() + i;
					index=index+2;
				}
				size[0]= index-1;
				return;
			}
		}
	
		else{

			if (K->GetRow()>Attackpiece->GetRow()){
				for (int i = 0; i < (K->GetRow()-Attackpiece->GetRow()); i++){ 
					line[index]= Attackpiece->GetRow() + i;
					line[index+1]= Attackpiece->GetCol() - i;
					index=index+2;
				}
				size[0]= index-1;
				return;
			}
			else {
				for (int i = 0; i < (Attackpiece->GetRow()-K->GetRow()); i++){
					line[index]= Attackpiece->GetRow() - i;
					line[index+1]= Attackpiece->GetCol() - i;
					index=index+2;
				}
				size[0]= index-1;
				return;
			}
		}
	}
}

bool Game::CheckMated(color_piece color){
	this->ResetChecks(color);

	if (CheckChecks(color)==false)
		return false;

	AbstractPiece* K=this->FindKing(color);

	int row= K->GetRow();
	int col= K->GetCol();
	
	for(int a = -1; a < 2; a++){
		for(int b = -1; b < 2; b++){
			bool rowbool = row+a >= 0 && row+a < 8;
			bool colbool = col+b >= 0 && col+b < 8;
			if(rowbool && colbool){
				if (this->ValidMove(K,row+a, col+b)== true){
					return false;
				}
			} 	
		}
	}

	AbstractPiece* Attackpiece=FindCheckPiece(color);
	//A double or more attack, after checking that the king can't move, it's mated
	//Findcheckpiece  return Null for multiple attack

	if (Attackpiece==NULL) return true;
	//Singular piece check

	//pawn or knight attack
	if (Attackpiece->GetType()==pawn || Attackpiece->GetType()==knight){
		if (BoxAttack(color,Attackpiece->GetRow(), Attackpiece->GetCol())==true) return false;
		else return true;
	}

	//rook attack
	if (Attackpiece->GetType()==rook){
		int size[1];
		int line[16];
		this->LineAttack(K, Attackpiece, size, line);
		for (int i=0; i<size[0]; i=i+2){
			if (BoxAttack(color,line[i], line[i+1])==true) return false;
		}
		return true;
	}

	//bishop attack
	if (Attackpiece->GetType()==bishop){
		int size[1];
		int line[16];
		this->LineAttack(K, Attackpiece, size, line);
		for (int i=0; i<size[0]; i=i+2){
			if (BoxAttack(color,line[i], line[i+1])==true) return false;
		}
		return true;
	}

	//queen attack
	if (Attackpiece->GetType()==queen){
		int size[1];
		int line[16];
		this->LineAttack(K, Attackpiece, size, line);

		for (int i=0; i<size[0]; i=i+2){
			if (BoxAttack(color,line[i], line[i+1])==true) return false;
		}
		return true;
	}
}

//-------------  Castling  ---------------------------------

bool Game::Castling(color_piece color, int i){	// i = 0 short castling i=1 long one
	if (color==white){
		if (i==0){
			if(currentgame->GetPiece(0,5)==NULL && currentgame->GetPiece(0,6)==NULL){
				if (CheckChecks(color)==false && this->BoxCheck(color,0,5)==false && this->BoxCheck(color,0,6)==false && currentgame->GetPiece(0,4)->GetMoved()==false && currentgame->GetPiece(0,7)->GetMoved()==false)
					return true;
			}
			else
				return false;
		}
		else{
			if(currentgame->GetPiece(0,2)==NULL && currentgame->GetPiece(0,3)==NULL && currentgame->GetPiece(0,1)==NULL){
				if (this->CheckChecks(color)==false && this->BoxCheck(color,0,2)==false && this->BoxCheck(color,0,3)==false && currentgame->GetPiece(0,4)->GetMoved()==false && currentgame->GetPiece(0,0)->GetMoved()==false)
					return true;
			}
			else
				return false;
		}
	}
	else{
		if (i==0){
			if(currentgame->GetPiece(7,5)==NULL && currentgame->GetPiece(7,6)==NULL){
				if (CheckChecks(color)==false && this->BoxCheck(color,7,5)==false && this->BoxCheck(color,7,6)==false && currentgame->GetPiece(7,4)->GetMoved()==false && currentgame->GetPiece(7,7)->GetMoved()==false)
					return true;
			}
			else
				return false;
		}
		else{
			if(currentgame->GetPiece(7,2)==NULL && currentgame->GetPiece(7,3)==NULL && currentgame->GetPiece(7,1)==NULL){
				if (CheckChecks(color)==false && this->BoxCheck(color,7,2)==false && this->BoxCheck(color,7,3)==false && currentgame->GetPiece(7,4)->GetMoved()==false && currentgame->GetPiece(7,0)->GetMoved()==false)
					return true;
			}
			else
				return false;
		}
	}
}

void Game::CastlingMove(color_piece color, int i){
	if (color==white){
		if (i==0){
			currentgame->Move(currentgame->GetPiece(0,4), 0, 6);
			currentgame->Move(currentgame->GetPiece(0,7), 0, 5);
		}
		else{
			currentgame->Move(currentgame->GetPiece(0,4), 0, 2);
			currentgame->Move(currentgame->GetPiece(0,0), 0, 3);
		}
	}
	else{
		if (i==0){
			currentgame->Move(currentgame->GetPiece(7,4), 7, 6);
			currentgame->Move(currentgame->GetPiece(7,7), 7, 5);
		}
		else{
			currentgame->Move(currentgame->GetPiece(7,4), 7, 2);
			currentgame->Move(currentgame->GetPiece(7,0), 7, 3);
		}
	}
}

//-------------  Enpassant  ---------------------------------

bool Game::Enpassant(AbstractPiece* piece, int row_f, int col_f){
	if (piece->GetType()==pawn){
		if(piece->GetColor()==white){
			if (currentgame->Occupied(row_f-1,col_f)==true){
				if(currentgame->GetPiece(row_f-1,col_f)->GetType()==pawn && currentgame->GetPiece(row_f-1,col_f)->GetColor() != piece->GetColor()){
					if(currentgame->GetPiece(row_f-1,col_f)->GetEnpassant()==true)
						return true;
				}
			}
		}
		if(piece->GetColor()==black){
			if (currentgame->Occupied(row_f+1,col_f)==true){
				if(currentgame->GetPiece(row_f+1,col_f)->GetType()==pawn && currentgame->GetPiece(row_f+1,col_f)->GetColor() != piece->GetColor()){
					if(currentgame->GetPiece(row_f+1,col_f)->GetEnpassant()==true)
						return true;
				}
			}
		}
	}
	return false;
}

void Game::EnpassantMove(AbstractPiece* piece, int row_f, int col_f){
	if(piece->GetColor()==white){
		currentgame->Move(piece, row_f, col_f);
		currentgame->GetPiece(row_f-1,col_f)->SetAlive(false);
		currentgame->SetPiece(NULL,row_f-1,col_f);
	}
	if(piece->GetColor()==black){
		currentgame->Move(piece, row_f, col_f);
		currentgame->GetPiece(row_f+1,col_f)->SetAlive(false);
		currentgame->SetPiece(NULL,row_f+1,col_f);
	}	
}

void Game::EnpassantReset(color_piece color){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if (currentgame->GetPiece(i,j)!=NULL){
				if (currentgame->GetPiece(i,j)->GetColor()==color && currentgame->GetPiece(i,j)->GetType()==pawn)
					currentgame->GetPiece(i,j)->SetEnpassant(false);
			}
		}
	}
}

//----------------------------------------------------------------

bool Game::Turn(color_piece color, int row_i, int col_i, int row_f, int col_f){  //castling move code 8 8 8 0 (short) 8 8 8 1 (long)
	//Castling
	if (row_i==8 && col_i==8 && row_f==8){
		if (col_f==0 && this->Castling(color, 0)){
			this->CastlingMove(color, 0);
			return true;
		}
		else if (col_f==1 && this->Castling(color, 1)){
			this->CastlingMove(color, 1);
			return true;
		}
		std::cout<<"(line 855, my_chess.h) Castling not possible"<<std::endl;
		return false;
	}


	if (currentgame->GetPiece(row_i, col_i)==NULL){
		std::cout<<"(line 861, my_chess.h) no piece here"<<std::endl;
		return false;;
	}
	else if (this->Enpassant(currentgame->GetPiece(row_i, col_i), row_f, col_f) == true)
				this->EnpassantMove(currentgame->GetPiece(row_i, col_i), row_f, col_f);
	else{
		if (this->ValidMove(currentgame->GetPiece(row_i, col_i), row_f, col_f)==false){
			std::cout<<"(line 868, my_chess.h) move not valid"<<std::endl;
			return false;
		}
		else{
			currentgame->Move(currentgame->GetPiece(row_i, col_i), row_f, col_f);

			if (currentgame->GetPiece(row_f, col_f)->GetType() ==pawn && abs(row_i-row_f)==2) currentgame->GetPiece(row_f, col_f)->SetEnpassant(true);
			if (currentgame->GetPiece(row_f, col_f)->GetColor()==white)  this->EnpassantReset(black); else this->EnpassantReset(white);
			return true;
		}
	}
}

void Game::Match(){
	//Game--->Input (), in this case using terminal
	int row_i, col_i, row_f, col_f;
	
	while(true){

		currentgame->Print();

		if (this->CheckMated(currentgame->GetTurn())==true)
			break;

		if (whitechecked==true)
			std::cout<<"White checked"<<std::endl;
		if(blackchecked==true)
			std::cout<<"Black checked"<<std::endl;

		if (currentgame->GetTurn()==white)
			std::cout<<"Play White:"<<std::endl;
		else 
			std::cout<<"Play Black:"<<std::endl;


		std::cout<<"Play move (row_i, col_i, row_f, col_f)"<<std::endl;
		std::cout<<"row_i "; std::cin >> row_i; std::cout<<std::endl;
		std::cout<<"col_i "; std::cin >> col_i; std::cout<<std::endl;
		std::cout<<"row_f "; std::cin >> row_f; std::cout<<std::endl;
		std::cout<<"col_f "; std::cin >> col_f; std::cout<<std::endl;

		if (this->Turn(currentgame->GetTurn(), row_i, col_i, row_f, col_f)==true)
			currentgame->ChangeTurn();
	}
}

#endif