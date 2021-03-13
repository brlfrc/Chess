//---------------------------------------------------------
//all constructors
//---------------------------------------------------------

nullpiece::nullpiece(int riga, int colonna){
	raw = riga;
	col = colonna;
	color = -1;
	type = 0;
	alive = false;
}

rook::rook(int colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 1;
	alive = true;
}

knight::knight(int colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 2;
	alive = true;
}

bishop::bishop(int colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 3;
	alive = true;
}

queen::queen(int colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 4;
	alive = true;
}

pawn::pawn(int colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 5;
	alive = true;
}

king::king(int colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 6;
	alive = true;
}

//---------------------------------------------------------

int piece::GetRaw(){
	return raw;
}

int piece::GetCol(){
	return col;
}

bool piece::GetAlive(){
	return alive;
}



int piece::GetColor(){
	return color;
}

int piece::GetType(){
	return type;
}

//---------------------------------------------------------

bool piece::SetAlive(bool a){
	alive = a;
}

void piece::ChangePos(int n_raw, int n_col){
	raw = n_raw;
	col = n_col;
}