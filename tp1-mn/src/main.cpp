#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

enum statusPoint {VACIO,SANGUIJUELA,FRIO};

struct Point {
    int x;
    int y;
	float temp;
	statusPoint status;
	float coeficiente;

	Point() {
        temp = NULL;
        status = VACIO;
	};

	Point(int xa, int ya, float tempa, statusPoint statusa) : x(xa), y(ya), temp(tempa), status(statusa) {};
};

class Windshield {
public:
    Windshield(){
    	cout << "3" << "\n";
        vector<vector<Point *> > matrix(0, vector<Point *>(0));
    };
	Windshield(int x, int y, float ah, int ar, float temp);
	void initialize();
	void initializeEmptyMatrix();
	void bandMatrix();
private:
	int a;
    int b;
    float h;
    int r;
	float ts;
    int m;
    int n;

	vector< vector<Point *> > matrix;
};

Windshield::Windshield(int x, int y, float ah, int ar, float temp) {
	a = x;
	b = y;
	h = ah;
	r = ar;
	ts = temp;

	m = (a/h) + 1;
	n = (b/h) + 1;

    matrix = vector<vector<Point *> >(m, vector<Point *>(n));

    cout << matrix.size() << "\n";

    int i,j;
	for(i=0; i< m;i++){
		cout << "I: " << i << "\n";
		cout << "SIZE[I]: "<< matrix[i].size() << "\n";
		for (j=0; j<n;j++){
			cout << "J: " << j << "\n";
            matrix[i][j] = new Point(i,j,0.00f,VACIO);
			if (j == 0 || i == 0 || j== n-1 || i==m-1){
               matrix[i][j]->temp = -100;
               matrix[i][j]->status = FRIO;
            }
        }
	}

	this->initialize();
}

void Windshield::initialize(){
	this->initializeEmptyMatrix();
}

void Windshield::initializeEmptyMatrix(){

}

void Windshield::bandMatrix(){
	int ancho = 2;
	  vector<vector<int> > bandMatrix  = vector<vector<int> >(ancho*2+2, vector<int>(n*m));
	int i,j, pos, res = ancho*2+1;
	for(i=0; i< m;i++){
		for (j=0; j<n;j++){
			pos = j + i * m;
			switch(matrix[i][j]->status){
			case SANGUIJUELA:
				bandMatrix[ancho][pos] = 1;
				bandMatrix[res][pos] = ts;
				break;
			case FRIO:
				bandMatrix[ancho][pos] = 1;
				bandMatrix[res][pos] = -100;
				break;
			case VACIO:
				bandMatrix[ancho][pos] = -4;
				bandMatrix[res][pos] = 0;
				if(matrix[i-1][j]->status != VACIO) bandMatrix[res][pos] -= matrix[i-1][j]->temp;
				else bandMatrix[ancho-1][pos] = 1;
				if(matrix[i+1][j]->status != VACIO) bandMatrix[res][pos] -= matrix[i+1][j]->temp;
				else bandMatrix[ancho+1][pos] = 1;
				if(matrix[i][j-1]->status != VACIO) bandMatrix[res][pos] -= matrix[i][j-1]->temp;
				else bandMatrix[0][pos] = 1;
				if(matrix[i][j+1]->status != VACIO) bandMatrix[res][pos] -= matrix[i][j+1]->temp;
				else bandMatrix[ancho*2][pos] = 1;
				break;
			}
        }
	}

}

int main(int a,int b,float h,int r) {
    float h;
	int a,b,r;
	cout << "Ingrese con enters en el medio, a, b, h, r, Ts y las sanguijuelas" << "\n";
    int CantSanguijuleas;
    int Ts;

	cin >> a >> b >> h >> r >> Ts >> CantSanguijuleas;

    vector< vector<double > > posSanguijuelas;
	posSanguijuelas = vector<vector<double > >(CantSanguijuleas, vector<double >(2));
	double rowS;
    double colS;
    int i;
	for (i=0; i<CantSanguijuleas;i++){
        cin >> rowS;
        posSanguijuelas[i].push_back(rowS);
        cin >> colS;
        posSanguijuelas[i].push_back(colS);

    }


    Windshield *windshield = new Windshield(a,b,h,r, 500);
	windshield->bandMatrix();

    return 0;
}

