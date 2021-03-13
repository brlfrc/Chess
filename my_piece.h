#ifndef my_piece_h
#define my_piece_h


enum type_piece {Nullpiece, Rook, Knight, Bishop, Queen, Pawn, King};
enum color_piece {white, black};

class piece{
	protected:
		int raw;										//raw of piece
		int col;										//col of piece
		color_piece color;										//color of piece
															// white    -> 0
															// black  	-> 1
		type_piece type;										//type of piece 
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
		color_piece GetColor();								//retun color
		type_piece GetType();									//retun # for type

		bool SetAlive(bool a);							//set alive status
		void ChangePos(int n_raw, int n_col);			//change both raw and col

		
};

class nullpiece : public piece{
	public:
		nullpiece(int riga, int colonna);
};

nullpiece::nullpiece(int riga, int colonna){
	raw = riga;
	col = colonna;
	type = Nullpiece;
	alive = false;
}

class rook : public piece{
	public:
		rook(color_piece colore, int riga, int colonna);
};

rook::rook(color_piece colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = Rook;
	alive = true;
}

class knight : public piece{
	public:
		knight(color_piece colore, int riga, int colonna);
};

knight::knight(color_piece colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = Knight;
	alive = true;
}

class bishop : public piece{
	public:
		bishop(color_piece colore, int riga, int colonna);
};

bishop::bishop(color_piece colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = Bishop;
	alive = true;
}

class queen : public piece{
	public:
		queen(color_piece colore, int riga, int colonna);
};

queen::queen(color_piece colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = Queen;
	alive = true;
}

class pawn : public piece{
	public:
		pawn(color_piece colore, int riga, int colonna);
};

pawn::pawn(color_piece colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = Pawn;
	alive = true;
}

class king : public piece{
	public:
		king(color_piece colore, int riga, int colonna);
};

king::king(color_piece colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = King;
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

color_piece piece::GetColor(){
	return color;
}

type_piece piece::GetType(){
	return type;
}

bool piece::SetAlive(bool a){
	alive = a;
}

void piece::ChangePos(int n_raw, int n_col){
	raw = n_raw;
	col = n_col;
}

#endif