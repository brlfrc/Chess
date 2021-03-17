#include "multiplexer.h"
#include "my_chess.h"

int EPin_Q[4]={7, 7, 7, 7}; //Q0 Q1 Q2 Q3
int SPin_Q[4][4]={
  {5,4,3,2},  //Q0
  {5,4,3,2},  //Q1
  {5,4,3,2},  //Q2
  {5,4,3,2}   //Q3
};
//----------- Q_0----------
int SIG_Q1 = A0;
Multiplexer Q1= Multiplexer (EPin_Q[0], SPin_Q[0], SIG_Q1);

//----------- Q_1----------
int SIG_Q2 = A0;
Multiplexer Q2= Multiplexer (EPin_Q[1], SPin_Q[1], SIG_Q2);

//----------- Q_2----------
int SIG_Q3 = A0;
Multiplexer Q3= Multiplexer (EPin_Q[2], SPin_Q[2], SIG_Q3);


//----------- Q_3----------
int SIG_Q4 = A0;
Multiplexer Q4= Multiplexer (EPin_Q[3], SPin_Q[3], SIG_Q4);

Scanner SCANNER= Scanner(Q1, Q2, Q3, Q4);

void setup() {
  Serial.begin (9600);

  for (int i=0;i<4;i++){
    pinMode(EPin_Q[i], OUTPUT);
    digitalWrite(EPin_Q[i], LOW);
  }

  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      pinMode(SPin_Q[i][j], OUTPUT); // Inizializza tutti gli Spin come OUTPUT
      digitalWrite(SPin_Q[i][j], LOW); // Setta tutti gli Spin LOW
    }
  }

}

void loop() {
  
}
