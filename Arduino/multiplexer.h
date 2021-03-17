#ifndef multiplexer_h
#define multiplexer_h

#include "Arduino.h"


class Multiplexer{
	private:

		int SPin[4];								
		int EPin;					
		int SIG;

		//Binary Table for calling channel Y
		int STable[16][4] = {
		  	{0,  0,  0,  0}, // Y0
		  	{1,  0,  0,  0}, // Y1
		  	{0,  1,  0,  0}, // Y2
		  	{1,  1,  0,  0}, // Y3
		  	{0,  0,  1,  0}, // Y4
		  	{1,  0,  1,  0}, // Y5
		  	{0,  1,  1,  0}, // Y6
		  	{1,  1,  1,  0}, // Y7
		  	{0,  0,  0,  1}, // Y8
		  	{1,  0,  0,  1}, // Y9
		  	{0,  1,  0,  1}, // Y10
		  	{1,  1,  0,  1}, // Y11
		  	{0,  0,  1,  1}, // Y12
		  	{1,  0,  1,  1}, // Y13
		  	{0,  1,  1,  1}, // Y14
		  	{1,  1,  1,  1}  // Y15
		};

		int YBoard [4][4];

	public:
		Multiplexer(){};
		Multiplexer(int EPin_, int* sPin, int SIG_){ EPin=EPin_ ; SPin[0]=sPin[0]; SPin[1]=sPin[1]; SPin[2]=sPin[2]; SPin[3]=sPin[3]; SIG=SIG_;};

    Multiplexer& operator= (const Multiplexer& original);


    void Set_SIG(int sig){SIG=sig;};
    void Set_EPin(int epin){EPin=epin;};
    void Set_STable(int i, int j, int a){STable[i][j] = a;};
    void Set_YBoard(int i, int j, int a){YBoard[i][j]=a;};

    int Get_SIG(){return SIG;};
    int Get_EPin(){return EPin;};
    int Get_STable(int i, int j){return STable[i][j];};
    int Get_YBoard(int i, int j){return YBoard[i][j];};
    
		//Select Channel
		void YSelect(int Y){
		  	digitalWrite(SPin[0], STable[Y][0]);
		  	digitalWrite(SPin[1], STable[Y][1]);
		  	digitalWrite(SPin[2], STable[Y][2]);
		  	digitalWrite(SPin[3], STable[Y][3]);
		}

		//Match channel with a board 4*4 (I connected in different way multiplexer to board, it was an error) 
		void Configure(int type);

   
};
//----------------operator = --------------------------
Multiplexer& Multiplexer::operator=(const Multiplexer& original){
  for(int i=0; i<4; i++)
    SPin[i]=original.SPin[i];
    
  EPin=original.EPin;
  SIG=original.SIG;
  
  for (int i =0; i<16; i++){
    for (int j=0; j<4; j++){
      STable [i][j]=original.STable[i][j];
    }
  }

  for (int i =0; i<4; i++){
    for (int j=0; j<4; j++){
      YBoard [i][j]=original.YBoard[i][j];
    }
  }
}

//---------------------------------------------------

void Multiplexer::Configure(int type){
	if (type==1){

		YBoard [0][0]=15;
		YBoard [0][1]=14;
		YBoard [0][2]=13;
		YBoard [0][3]=12;
		YBoard [1][0]=11;
		YBoard [1][1]=10;
		YBoard [1][2]=9;
		YBoard [1][3]=8;
		YBoard [2][0]=7;
		YBoard [2][1]=6;
		YBoard [2][2]=5;
		YBoard [2][3]=4;
		YBoard [3][0]=3;
		YBoard [3][1]=2;
		YBoard [3][2]=1;
		YBoard [3][3]=0;

	}
	if (type==2){

		YBoard [0][0]=12;
		YBoard [0][1]=13;
		YBoard [0][2]=14;
		YBoard [0][3]=15;
		YBoard [1][0]=8;
		YBoard [1][1]=9;
		YBoard [1][2]=10;
		YBoard [1][3]=11;
		YBoard [2][0]=4;
		YBoard [2][1]=5;
		YBoard [2][2]=6;
		YBoard [2][3]=7;
		YBoard [3][0]=3;
		YBoard [3][1]=2;
		YBoard [3][2]=1;
		YBoard [3][3]=0;
		
	}
	else {
		Serial.print("type error");
	}
}

//------------Function to understand color of box----

bool isblue(int i, int j){
	if (i ==0 || i==2){
		if (j==0 || j==2)
			return true;
		else 
			return false;
	}
	if (i ==1 || i==3){
		if (j==1 || j==3)
			return true;
		else 
			return false;
	}

}
		
//------------- SCANNER Object ----------------------
/*
				| Q1  Q2 |
	Scanner = 	|        |
				| Q3  Q4 |
*/

class Scanner{

	protected:
		Multiplexer quarter_board [4];

		int scan [8][8];
		
		Scanner* last;

	public:
		Scanner(){};

		Scanner(Multiplexer Q1, Multiplexer Q2, Multiplexer Q3, Multiplexer Q4){quarter_board[0]=Q1; quarter_board[1]=Q2; quarter_board[2]=Q3; quarter_board[3]=Q4;};
		Scanner(Scanner* old_scan);
   
		Multiplexer Get_quarter_board(int i){return quarter_board[i];};
		int Get_scan (int i, int j){return scan[i][j];}

		void Make_scan();

};

Scanner::Scanner(Scanner* old_scan){
	last=old_scan;
	for(int i=0; i<4; i++)
		quarter_board[i]=old_scan->Get_quarter_board(i);

	for (int i =0; i<8; i++){
		for (int j=0; j<8; j++){
			scan [i][j]=old_scan->Get_scan(i,j);
		}
	}
}

void Scanner::Make_scan(){
	int index=0;

	for (int b=0; b<2; b++){
		for (int a=0; a<2; a++){
			if (b==0)
				index=a;
			else
				index=a+2;

			for (int i=0+4*b; i<4+4*b; i++){
				for(int j=0+4*a; j<4+4*a; j++){

					quarter_board[index].YSelect(quarter_board[index].Get_YBoard(i,j));

					if (isblue(i,j)==true){
						if (analogRead(quarter_board[index].Get_SIG()) > 600) 
							scan [i][j] = 1;
						else
							scan [i][j] = 0;
					}
					else{
					 	if (analogRead(quarter_board[index].Get_SIG()) > 400) 
							scan [i][j] = 1;
						else
							scan [i][j] = 0;
					}
				}
			}
		}
	}
}


#endif
