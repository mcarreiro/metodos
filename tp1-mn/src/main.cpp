#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

enum status = {VACIO,SANGUIJUELA,FRIO};

struct Point {
    int x;
    int y;
	float temp;
	status status;

	Point(int x, int y, float temp, status status) : x(x), y(y), temp(temp), status(status) {};

};

class Windshield {
public:
    Windshield(){};
	Windshield(int x, int y, float ah, int ar);
	void initialize();

private:
	int a;
    int b;
    float h;
    int r;

    int m;
    int n;
	
	Punto matrix;
};

Windshield::Windshield(int x, int y, float ah, int ar) {
    a = x;
    b = y;
	h = ah;
	r = ar;	
	
	initialize();
}

void Windshield::initialize(){
	m = (a/h) + 1;
	n = (a/h) + 1;

	initializeEmptyMatrix();



	
}

void Windshield::initializeEmptyMatrix(){
	Punto matrix[m][n];

	for(i=0; i< m;i++){
		for (j=0; j<n;j++){
			if (j == 0 || i == 0){
				matrix[i][j] = new Punto()
			}
		}		
	}


}

int main() {
	int a,b,h,r;
	cout << "Ingrese con enters en el medio, a, b, h y r" << "\n";
	cin >> a >> b >> h >> r;
    Windshield *Windshield = new Windshield(a,b,h,r);	

    return 0;
}

