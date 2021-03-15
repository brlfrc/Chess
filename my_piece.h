#ifndef my_piece_h
#define my_piece_h


enum type_piece {rook=0, knight, bishop, queen, pawn, king};
const char name_piece[]= {'R', 'N', 'B', 'Q', 'p', 'K'};

enum color_piece {white=0, black};
const char name_color[]= {'W', 'B'};

class AbstractPiece{
	protected:
		int row;								
		int col;					
		color_piece color;							
		type_piece type;						
		bool alive;	

	public:
		AbstractPiece(){};

		int GetRow(){return row;};									
		int GetCol(){return col;};									
		bool GetAlive(){return alive;};			

		color_piece GetColor(){return color;};	
		const char GetNameColor(){return name_color[color];};		

		type_piece GetType(){return type;};	
		const char GetNamePiece(){return name_piece[type];};

		bool SetAlive(bool a){alive = a;};							
		void ChangePos(int n_row, int n_col){row = n_row;col = n_col;};	
		
};

class Rook : public AbstractPiece{
	public:
		Rook(color_piece colore, int rowa, int colu){row = rowa; col = colu; color = colore; type = rook; alive = true;};
};

class Knight : public AbstractPiece{
	public:
		Knight(color_piece colore, int rowa, int colu) {row = rowa; col = colu; color = colore; type = knight; alive = true;};
};

class Bishop : public AbstractPiece{
	public:
		Bishop(color_piece colore, int rowa, int colu){row = rowa; col = colu; color = colore; type = bishop; alive = true;};
};

class Queen : public AbstractPiece{
	public:
		Queen(color_piece colore, int rowa, int colu){row = rowa; col = colu; color = colore; type = queen; alive = true;};
};

class Pawn : public AbstractPiece{
	public:
		Pawn(color_piece colore, int rowa, int colu){row = rowa; col = colu; color = colore; type = pawn; alive = true;};
};

class King : public AbstractPiece{
	public:
		King(color_piece colore, int riga, int colonna){row = riga; col = colonna; color = colore; type = king; alive = true;};
};

#endif