#ifndef my_piece_h
#define my_piece_h


enum type_piece {Null, R, N, B, Q, p, K};
enum color_piece {white, black};

class AbstractPiece{
	protected:
		int raw;										//raw of piece
		int col;										//col of piece
		color_piece color;										//color of piece
		type_piece type;										//type of piece
		bool alive;										//is this piece alive?

	public:
		AbstractPiece(){throw " (file my piece.h line 20) AbstractPiece provide an abstract builder. This is not intended to be used in the base class and needs to be overridden in child classes";};										


		int GetRaw(){return raw;};									//retun raw
		int GetCol(){return col;};									//retun col
		bool GetAlive(){return alive;};								//retun alive status							
		color_piece GetColor(){return color;};								//retun color
		type_piece GetType(){return type;};									//retun # for type

		bool SetAlive(bool a){alive = a;};							//set alive status
		void ChangePos(int n_raw, int n_col){raw = n_raw;col = n_col;};			//change both raw and col

		
};

class Nullpiece : public AbstractPiece{
	public:
		Nullpiece(int riga, int colonna){raw = riga; col = colonna;	type = Null; alive = false;};
};

class Rook : public AbstractPiece{
	public:
		Rook(color_piece colore, int riga, int colonna){raw = riga;	col = colonna;	color = colore;	type = R; alive = true;};
};

class Knight : public AbstractPiece{
	public:
		Knight(color_piece colore, int riga, int colonna) {raw = riga; col = colonna; color = colore; type = N; alive = true;};
};

class Bishop : public AbstractPiece{
	public:
		Bishop(color_piece colore, int riga, int colonna){raw = riga; col = colonna; color = colore; type = B; alive = true;};
};

class Queen : public AbstractPiece{
	public:
		Queen(color_piece colore, int riga, int colonna){raw = riga; col = colonna; color = colore; type = Q; alive = true;};
};

class Pawn : public AbstractPiece{
	public:
		Pawn(color_piece colore, int riga, int colonna){raw = riga; col = colonna; color = colore; type = p; alive = true;};
};

class King : public AbstractPiece{
	public:
		King(color_piece colore, int riga, int colonna){raw = riga; col = colonna; color = colore; type = K; alive = true;};
};

#endif