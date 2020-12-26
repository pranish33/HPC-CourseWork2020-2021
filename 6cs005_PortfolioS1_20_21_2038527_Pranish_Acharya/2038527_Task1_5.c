#include <stdio.h>

int main(){

	int A = 1;
	int B = 2;
	int C = 3;
	int D = 4;
	
	int P1;
	int P2;
	
	//removing Dependency by introducing variables P1 and P2
	
	B = A+C;
	P1 = C+D;
	P2 = C+2*D;
	
	return 0;


}
