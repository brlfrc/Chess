#ifndef my_board_h
#define my_board_h

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

		void Print();									//prints the board
		string Unicode(type_piece type, color_piece color); //converts type+color in unicode char

		int GetCurrentMoveInt();						//returns 0 || 1 for white & black
		int GetMove();									//returns move # (1,2,3,4...)
		void SetCurrentMoveInt(int a);					//set currentmove
		void InvertCurrentMoveInt();				//Invert 0.1 currentmove

		bool Castling(bool scan [8][8]);
		bool Move(bool scan [8][8], bool scan2 [8][8]);	//Double can the board and compare two boards and find the move
														//if box occupied scan =true, else false
};



board::board(){

	thisboard[0][0] = new rook(white,0,0);
	thisboard[0][1] = new knight(white,0,1);
	thisboard[0][2] = new bishop(white,0,2);
	thisboard[0][3] = new queen(white,0,3);
	thisboard[0][4] = new king(white,0,4);
	thisboard[0][5] = new bishop(white,0,5);
	thisboard[0][6] = new knight(white,0,6);
	thisboard[0][7] = new rook(white,0,7);

	thisboard[7][0] = new rook(black,7,0);
	thisboard[7][1] = new knight(black,7,1);
	thisboard[7][2] = new bishop(black,7,2);
	thisboard[7][3] = new queen(black,7,3);
	thisboard[7][4] = new king(black,7,4);
	thisboard[7][5] = new bishop(black,7,5);
	thisboard[7][6] = new knight(black,7,6);
	thisboard[7][7] = new rook(black,7,7);

	for(int i = 0; i < 8; i++){
		thisboard[1][i] = new pawn(white,1,i);
		thisboard[6][i] = new pawn(black,6,i);		
	}

	for(int i = 0; i < 8; i++){
		for(int j = 2; j < 6; j++){
			thisboard[j][i] = new nullpiece(j,i);
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

//------------------------------------------------------

piece * board::GetPiece(int raw, int col){
	return thisboard[raw][col];
}

bool board::Occupied(int n_raw, int n_col){
	return (thisboard[n_raw][n_col] -> GetType() != 0);
}

//-------------------------------------------------------

void board::Print(){
	for(int i = 7; i >= 0; i--){
		for(int j = 0; j < 8; j++){
			type_piece type = thisboard[i][j] -> GetType();
			color_piece color = thisboard[i][j] -> GetColor();
			if(j == 0) cout << "|__";
			cout << this -> Unicode(type,color);
			if(j != 7) cout << "__|__";
			else cout << "__|\t" << i+1;
		}
		cout << "\n" << endl;
	}
	cout << "   a     b     c     d     e     f     g     h" << endl;
}

string board::Unicode(type_piece type, color_piece color){

	if(type == Nullpiece) return " ";
	if(type == Rook){	
		if(color == black) return "T";//"\u2656";
		if(color == white) return "\u265C";
	}
	if(type == Knight){	
		if(color == black) return "\u2658";
		if(color == white) return "\u265E";
	}
	if(type == Bishop){	
		if(color == black) return "\u2657";
		if(color == white) return "\u265D";
	}
	if(type == Queen){	
		if(color == black) return "\u2655";
		if(color == white) return "\u265B";
	}
	if(type == Pawn){	
		if(color == black) return "\u2659";
		if(color == white) return "P";//"\u265F";
	}
	if(type == King){	
		if(color == black) return "K";//"\u2654";
		if(color == white) return "\u265A";
	}
}

//-------------------------------------------------------

//-------------------------------------------------------

int board::GetCurrentMoveInt(){
	return currentmove;
}

void board::SetCurrentMoveInt(int a){
	currentmove = a;
}

void board::InvertCurrentMoveInt(){
	if (currentmove==0)
		currentmove=1;
	else
		currentmove=0;
}
//------------------------------------------------

bool board::Castling(bool scan [8][8]){				
	if (scan[0][5]==true && scan[0][6]==true && this->GetCurrentMoveInt()==0){					//WHITE
		thisboard[0][6] = this->GetPiece(0,4);									//king
	    thisboard[0][6]->ChangePos(0,6);
	  	thisboard[0][4] = new nullpiece(0,4);

	  	thisboard[0][5] = this->GetPiece(0,7);									//rook
	    thisboard[0][5]->ChangePos(0,5);
	  	thisboard[0][7] = new nullpiece(0,7);

	  	return true;
	}

	if (scan[0][2]==true && scan[0][3]==true && this->GetCurrentMoveInt()==0){
		thisboard[0][2] = this->GetPiece(0,4);									//king
	    thisboard[0][2]->ChangePos(0,2);
	  	thisboard[0][4] = new nullpiece(0,4);

	  	thisboard[0][3] = this->GetPiece(0,4);									//rook
	    thisboard[0][3]->ChangePos(0,3);
	  	thisboard[0][4] = new nullpiece(0,4);

	  	return true;
	}

	if (scan[7][5]==true && scan[7][6]==true && this->GetCurrentMoveInt()==1){					//BLACK
		thisboard[7][6] = this->GetPiece(7,4);									//king
	    thisboard[7][6]->ChangePos(7,6);
	  	thisboard[7][4] = new nullpiece(7,4);

	  	thisboard[7][5] = this->GetPiece(7,7);									//rook
	    thisboard[7][5]->ChangePos(7,5);
	  	thisboard[7][7] = new nullpiece(7,7);

	  	return true;
	}

	if (scan[7][2]==true && scan[7][3]==true && this->GetCurrentMoveInt()==1){
		thisboard[7][2] = this->GetPiece(7,4);									//king
	    thisboard[7][2]->ChangePos(7,2);
	  	thisboard[7][4] = new nullpiece(7,4);

	  	thisboard[7][3] = this->GetPiece(7,4);									//rook
	    thisboard[7][3]->ChangePos(7,3);
	  	thisboard[7][4] = new nullpiece(7,4);

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
bool board::Move(bool scan [8][8], bool scan2 [8][8]){ 					//two type of move: shift a piece (1), take a piece
	
	bool notaken = areSame (scan, scan2);	 	//I nedd two scan when a piece is taking, else one is enough. In this case I put scan=scan2

	int i_old, j_old, i_new, j_new;
	int count=0; 								//need for the debug (if something get wrong during the scan of the board)

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
			if (this->Occupied(i,j)!=scan[i][j] && this->Occupied(i,j)== true && notaken==false){  //for taken move
				i_new= i;
				j_new= j;
				count++;
			}
		}
	}
	cout<<count<<endl;
	if (count==4)
		return Castling(scan);
	
	if(count ==2){                           			// shift a piece
	    thisboard[i_new][j_new] = this->GetPiece(i_old,j_old);
	    thisboard[i_new][j_new]->ChangePos(i_new,j_new);
	  	thisboard[i_old][j_old] = new nullpiece(i_old,j_old);

	  	this->InvertCurrentMoveInt();
	  	return true;
	}

	if (count ==1 && this->GetPiece(i_new,j_new)->GetColor()!=this->GetCurrentMoveInt()){				// take an other piece: that's critic. I can't find an easy way to understand which piece is taken
		thisboard[i_new][j_new]->SetAlive(false);										// So i suppose two scan, in the first the enemy's piece dissapears and in the second one i'll put the piece
		
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
	  	thisboard[i_old][j_old] = new nullpiece(i_old,j_old);

	  	this->InvertCurrentMoveInt();
	  	return true;
	}

	cout<<"\n *****\nError e count "<<count<<"\n ******\n "<<endl;
	return false;									//scan failed
}

#endif