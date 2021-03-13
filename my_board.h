board::board(){

	thisboard[0][0] = new rook(0,0,0);
	thisboard[0][1] = new knight(0,0,1);
	thisboard[0][2] = new bishop(0,0,2);
	thisboard[0][3] = new queen(0,0,3);
	thisboard[0][4] = new king(0,0,4);
	thisboard[0][5] = new bishop(0,0,5);
	thisboard[0][6] = new knight(0,0,6);
	thisboard[0][7] = new rook(0,0,7);

	thisboard[7][0] = new rook(1,7,0);
	thisboard[7][1] = new knight(1,7,1);
	thisboard[7][2] = new bishop(1,7,2);
	thisboard[7][3] = new queen(1,7,3);
	thisboard[7][4] = new king(1,7,4);
	thisboard[7][5] = new bishop(1,7,5);
	thisboard[7][6] = new knight(1,7,6);
	thisboard[7][7] = new rook(1,7,7);

	for(int i = 0; i < 8; i++){
		thisboard[1][i] = new pawn(0,1,i);
		thisboard[6][i] = new pawn(1,6,i);		
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
	if(thisboard[n_raw][n_col] -> GetType() != 0) return true;
	else return false;
}

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

//-------------------------------------------------------
bool board::Move(bool scan [8][8], bool scan2 [8][8]){ 					//two type of move: shift a piece (1), take a piece
	
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
		}
	}

	if (count==4){
		if (Castling(scan)==true){
			this->InvertCurrentMoveInt();
			return true;
		}
	}
	
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

	return false;									//scan failed
}

//-------------------------------------------------------
