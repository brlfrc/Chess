//c++ -o main main.cpp

#include "my_chess.h"

using namespace std;

int main(){

	board* Scacchiera= new (board);

	cout<<"Move 0"<<endl;
	Scacchiera->Print();						//unicode chars doesn't work, i don't know why


	//two easy moves
	bool prima_mossa [8][8]={false};
	for (int i = 0; i<8; i++){
		prima_mossa[0][i]=true;
		prima_mossa[1][i]=true;
		prima_mossa[6][i]=true;
		prima_mossa[7][i]=true;
	}
	prima_mossa[1][5]=false;
	prima_mossa[2][5]=true;

	Scacchiera->Move(prima_mossa, prima_mossa);

	cout<<"\n\nMove 1"<<endl;
	Scacchiera->Print();

	bool seconda_mossa [8][8];

	for (int i =0; i<8;i++){
		for (int j=0; j<8; j++)
			seconda_mossa[i][j] = prima_mossa[i][j];
	}

	seconda_mossa[6][5]=false;
	seconda_mossa[3][5]=true;

	cout<<"\nasjias"<<endl;

	Scacchiera->Move(seconda_mossa, seconda_mossa);

	cout<<"\n\nMove 2"<<endl;
	Scacchiera->Print();

	//Take enemy's piece
	bool terza_mossa_pt1 [8][8];
	bool terza_mossa_pt2 [8][8];

	for (int i =0; i<8;i++){
		for (int j=0; j<8; j++){
			terza_mossa_pt1[i][j] = seconda_mossa[i][j];
			terza_mossa_pt2[i][j] = seconda_mossa[i][j];
		}
	}

	terza_mossa_pt1[3][5]=false;

	terza_mossa_pt2[2][5]=false;

	Scacchiera->Move(terza_mossa_pt1, terza_mossa_pt2);

	cout<<"\n\nMove 3"<<endl;
	Scacchiera->Print();

	//Invalid move. That's doesn't work. I could improve something to understand when i try to move a piece when it's not my turn and return error, now return (core dumped)
	
/*	bool mossa_falsa [8][8];

	for (int i =0; i<8;i++){
		for (int j=0; j<8; j++){
			mossa_falsa[i][j] = terza_mossa_pt2[i][j];
		}
	}

	mossa_falsa[0][1]=false;
	mossa_falsa[2][2]=true;

	Scacchiera->Move(mossa_falsa, mossa_falsa);

	cout<<"\n\nMossa Falsa"<<endl;
	Scacchiera->Print();
*/


	//Castling  Works
	terza_mossa_pt2[7][5]= false;
	terza_mossa_pt2[6][5]= true; 
	Scacchiera->Move(terza_mossa_pt2, terza_mossa_pt2);

	terza_mossa_pt2[1][3]= false;
	terza_mossa_pt2[2][4]= true;
	Scacchiera->Move(terza_mossa_pt2, terza_mossa_pt2);

	terza_mossa_pt2[7][6]= false;
	terza_mossa_pt2[5][5]= true;
	Scacchiera->Move(terza_mossa_pt2, terza_mossa_pt2);

	terza_mossa_pt2[1][1]= false;
	terza_mossa_pt2[2][2]= true;
	Scacchiera->Move(terza_mossa_pt2, terza_mossa_pt2);

	cout<<"\n\nCastling -1 Move"<<endl;
	Scacchiera->Print();

	terza_mossa_pt2[7][4]= false;
	terza_mossa_pt2[7][6]= true;
	terza_mossa_pt2[7][7]= false;
	terza_mossa_pt2[7][5]= true;

	Scacchiera->Move(terza_mossa_pt2, terza_mossa_pt2);

	cout<<"\n\nCastling Move"<<endl;
	Scacchiera->Print();
}