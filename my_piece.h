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
		bool moved;

	public:
		AbstractPiece(type_piece Type, color_piece Color, int Row, int Col){
			row = Row; col = Col; color = Color; type = Type; alive = true;
		};

		int GetRow(){return row;};
		int GetCol(){return col;};
		bool GetAlive(){return alive;};
		bool GetMoved(){return moved;};

		color_piece GetColor(){return color;};	
		const char GetNameColor(){return name_color[color];};		

		type_piece GetType(){return type;};	
		const char GetNamePiece(){return name_piece[type];};

		void SetAlive(bool a){alive = a;};
		void SetMoved(bool a){moved = a;};

		void ChangePos(int n_row, int n_col){row = n_row; col = n_col; this->SetMoved(true);};

};

class Rook : public AbstractPiece{
	public:
		Rook(color_piece color, int row, int col) : AbstractPiece(rook, color, row, col){};
};

class Knight : public AbstractPiece{
	public:
		Knight(color_piece color, int row, int col) : AbstractPiece(knight, color, row, col){};
};

class Bishop : public AbstractPiece{
	public:
		Bishop(color_piece color, int row, int col) : AbstractPiece(bishop, color, row, col){};
};

class Queen : public AbstractPiece{
	public:
		Queen(color_piece color, int row, int col) : AbstractPiece(queen, color, row, col){};
};

class Pawn : public AbstractPiece{
	public:
		Pawn(color_piece color, int row, int col) : AbstractPiece(pawn, color, row, col){};
};

class King : public AbstractPiece{
	public:
		King(color_piece color, int row, int col) : AbstractPiece(king, color, row, col){};
};

#endif