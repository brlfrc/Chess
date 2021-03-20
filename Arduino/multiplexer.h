#ifndef multiplexer_h
#define multiplexer_h

#include "Arduino.h"
//Multiplexer is a chip that works in this way: there are four pin (SPin) to select a channel, using binary code (HIGH or LOW); then you can read channel using 
//SIG pin and eventually there En pin that can interrupt in each moment comunication (setting it on HIGH).

//Binary combinatio for each channel Y (0= LOW, 1=HIGH)
const int STable[16][4] = {
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

class Multiplexer{
	private:

		int SPin[4];								
		int EPin;					
		int SIG;

		int YBoard [4][4]; //match each channel with the right position on the 4*4 board 

	public:
		Multiplexer(){};
		Multiplexer(int epin, int* sPin, int sig, int type){ EPin=epin ; SPin[0]=sPin[0]; SPin[1]=sPin[1]; SPin[2]=sPin[2]; SPin[3]=sPin[3]; SIG=sig; this->Configure(type);};

    Multiplexer& operator= (const Multiplexer& original);


    void Set_SIG(int sig){SIG=sig;};
    void Set_EPin(int epin){EPin=epin;};
    void Set_YBoard(int i, int j, int a){YBoard[i][j]=a;};

    int Get_SIG(){return SIG;};
    int Get_EPin(){return EPin;};
    int Get_YBoard(int i, int j){return YBoard[i][j];};
    
		//Select Channel, setting SPin
		void YSelect(int Y){
		  	digitalWrite(SPin[0], STable[Y][0]);
		  	digitalWrite(SPin[1], STable[Y][1]);
		  	digitalWrite(SPin[2], STable[Y][2]);
		  	digitalWrite(SPin[3], STable[Y][3]);
		}

		//Configure YBoard (I have connected incorrectly in different way multiplexer to board) 
		void Configure(int type);

   
};
//----------------operator = --------------------------
Multiplexer& Multiplexer::operator=(const Multiplexer& original){
  for(int i=0; i<4; i++)
    SPin[i]=original.SPin[i];
    
  EPin=original.EPin;
  SIG=original.SIG;
  
  for (int i =0; i<4; i++){
    for (int j=0; j<4; j++){
      YBoard [i][j]=original.YBoard[i][j];
    }
  }
}

//---------------------------------------------------

// As you can see below i connected multiplexer in different way, so position [0][0] in two configurations is matched with 3 while in last one with 0.
// Configurations are three because two boards are connected in the same way.

void Multiplexer::Configure(int type){
	if (type==1){

		YBoard [0][0]=3;
		YBoard [0][1]=2;
		YBoard [0][2]=1;
		YBoard [0][3]=0;
		YBoard [1][0]=7;
		YBoard [1][1]=6;
		YBoard [1][2]=5;
		YBoard [1][3]=4;
		YBoard [2][0]=11;
		YBoard [2][1]=10;
		YBoard [2][2]=9;
		YBoard [2][3]=8;
		YBoard [3][0]=15;
		YBoard [3][1]=14;
		YBoard [3][2]=13;
		YBoard [3][3]=12;

	}
  if (type==2){

    YBoard [0][0]=3;
    YBoard [0][1]=2;
    YBoard [0][2]=1;
    YBoard [0][3]=0;
    YBoard [1][0]=5;
    YBoard [1][1]=8;
    YBoard [1][2]=6;
    YBoard [1][3]=4;
    YBoard [2][0]=11;
    YBoard [2][1]=10;
    YBoard [2][2]=9;
    YBoard [2][3]=7;
    YBoard [3][0]=15;
    YBoard [3][1]=14;
    YBoard [3][2]=13;
    YBoard [3][3]=12;
    
   }
    if (type==3){

    YBoard [0][0]=0;
    YBoard [0][1]=1;
    YBoard [0][2]=2;
    YBoard [0][3]=3;
    YBoard [1][0]=4;
    YBoard [1][1]=5;
    YBoard [1][2]=6;
    YBoard [1][3]=7;
    YBoard [2][0]=11;
    YBoard [2][1]=9;
    YBoard [2][2]=10;
    YBoard [2][3]=8;
    YBoard [3][0]=15;
    YBoard [3][1]=14;
    YBoard [3][2]=13;
    YBoard [3][3]=12;
    
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
    void Print_scan(); 

};

//-----------------------------------------------------
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

//-----------------------------------------------------

//If box is free analogread is 0.
 
void Scanner::Make_scan(){
  last=new Scanner(this);
  
  for (int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      
      quarter_board[0].YSelect(quarter_board[0].Get_YBoard(i,j));
      
      if (analogRead(quarter_board[0].Get_SIG()) != 0) 
              scan [i][j] = 1;
      else
              scan [i][j] = 0;
      
      }
  }

  for (int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      quarter_board[1].YSelect(quarter_board[1].Get_YBoard(i,j));
      
      if (analogRead(quarter_board[1].Get_SIG()) != 0) 
              scan [i][j+4] = 1;
      else
              scan [i][j+4] = 0;
      
      }
  }

  for (int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      
      quarter_board[2].YSelect(quarter_board[2].Get_YBoard(i,j));
      
      if (analogRead(quarter_board[2].Get_SIG()) != 0) 
              scan [i+4][j] = 1;
      else
              scan [i+4][j] = 0;
      
      }
  }

  for (int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      quarter_board[3].YSelect(quarter_board[3].Get_YBoard(i,j));
      
      if (analogRead(quarter_board[3].Get_SIG()) != 0) 
              scan [i+4][j+4] = 1;
      else
              scan [i+4][j+4] = 0;
      
      }
  }

}

//------------------------------------------------------------
void Scanner::Print_scan(){
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
        Serial.print(this->Get_scan(i,j));
        if (j==7) Serial.println();
        else Serial.print("\t");
    }
  }
}

#endif
