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

		//moving
		bool Turn(color_piece color, int row_i, int col_i, int row_f, int col_f);
		void Match();
};

//----------------------------------------------------------------

void Game::Studypossiblemoves(AbstractPiece* piece){
	this->Resetpossiblemoves();

	if (piece== NULL){
		std::cout<<"(line 54, my_chess.h) Error, there is no piece in this position"<<std::endl;
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
			return true;
		}
		else{
			if (piece->GetType()!=king)
				std::cout<<"(line 455, my_chess.h) there is or open check"<<std::endl;
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

//----------------------------------------------------------------

bool Game::Turn(color_piece color, int row_i, int col_i, int row_f, int col_f){

	if (currentgame->GetPiece(row_i, col_i)==NULL){
		std::cout<<"(line 704, my_chess.h) no piece here"<<std::endl;
		return false;;
	}
	else{
		if (this->ValidMove(currentgame->GetPiece(row_i, col_i), row_f, col_f)==false){
			std::cout<<"(line 710, my_chess.h) move not valid"<<std::endl;
			return false;
		}
		else{
			currentgame->Move(currentgame->GetPiece(row_i, col_i), row_f, col_f);
			return true;
		}
	}
}

void Game::Match(){
	//Game--->Input (), in this case using terminal
	int row_i, col_i, row_f, col_f;
	/*int row_i[]={1,6,0};
	int col_i[]={4,5,3};
	int row_f[]={2,5,4};
	int col_f[]={4,5,7};*/

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