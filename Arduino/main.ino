#include "multiplexer.h"
#include "my_chess.h"

int EPin_Q[4]={7, 4, 2, 1}; //Q0 Q1 Q2 Q3
int SPin_Q[4][4]={
  {5,4,3,2},  //Q0
  {10,11,12,13},  //Q1
  {15,16,17,18},  //Q2
  {20,21,22,23}   //Q3
};
//----------- Q_0----------
int SIG_Q1 = A0;
Multiplexer Q1= Multiplexer (EPin_Q[0], SPin_Q[0], SIG_Q1,1);

//----------- Q_1----------
int SIG_Q2 = A0;
Multiplexer Q2= Multiplexer (EPin_Q[1], SPin_Q[1], SIG_Q2,2);

//----------- Q_2----------
int SIG_Q3 = A0;
Multiplexer Q3= Multiplexer (EPin_Q[2], SPin_Q[2], SIG_Q3,1);

//----------- Q_3----------
int SIG_Q4 = A0;
Multiplexer Q4= Multiplexer (EPin_Q[3], SPin_Q[3], SIG_Q4,3);

Scanner SCANNER= Scanner(Q1, Q2, Q3, Q4);

void setup() {
  Serial.begin (9600);

  for (int i=0;i<4;i++){
    pinMode(EPin_Q[i], OUTPUT);
    digitalWrite(EPin_Q[i], LOW);
  }

  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      pinMode(SPin_Q[i][j], OUTPUT);
      digitalWrite(SPin_Q[i][j], LOW);
    }
  }

}

void loop() {
  
  SCANNER.Make_scan();
  SCANNER.Print_scan();

  Serial.println();
  delay(1000 );
}
