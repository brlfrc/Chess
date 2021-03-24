//c++ -o main main.cpp

#include "my_chess.h"

using namespace std;

int main(){
	
	Game* gioco= new (Game);

	gioco->Match();
	cout<<"finish"<<endl;
}