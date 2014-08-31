#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

enum statusPoint {VACIO,SANGUIJUELA,FRIO};

bool esIgual(double a, double b, double error= 0.00001){
	return abs(a-b) < error;
}

void imprimirMatriz(vector<vector<double> > matriz, int filas, int columnas){
	for(int i=0; i< filas; i++){
		for(int j=0; j< columnas; j++)
			cout << matriz[i][j] << ";";
	cout << "\n";
	}
	
}
struct Point {
    int x;
    int y;
	float temp;
	statusPoint status;
	float coeficiente;

	Point() {
        temp = 0;
        status = VACIO;
	};
    Point(int j, int i) : x(j), y(i) {};
	Point(int xa, int ya, float tempa, statusPoint statusa) : x(xa), y(ya), temp(tempa), status(statusa) {};
};

struct Position {
    double x;
    double y;
    Position(double x, double y) : x(x), y(y) {};
};


class Windshield {
public:
    Windshield(){
    	cout << "3" << "\n";
        vector<vector<Point *> > matrix(0, vector<Point *>(0));
    };
	Windshield(int x, int y, float ah, int ar, float temp, vector< vector<double > > posSanguijuelas);
	void initialize();
	void initializeEmptyMatrix();
	vector<vector<double> > bandMatrix();
	void resolveBandMatrix(vector<vector<double> > bandMatrix);
	void showMatriz();
	void putSanguijuela(vector< vector<double > > posSanguijuelas);
	double distance(Position p1, Position p2);
	vector<Point> sanguijuelaPoints(Position sanguijuela);
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





Windshield::Windshield(int x, int y, float ah, int ar, float temp, vector< vector<double > > posSanguijuelas) {
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

		for (j=0; j<n;j++){
            matrix[i][j] = new Point(i,j,0.00f,VACIO);
			if (j == 0 || i == 0 || j== n-1 || i==m-1){
               matrix[i][j]->temp = -100;
               matrix[i][j]->status = FRIO;
            }
        }
	}

	this->putSanguijuela(posSanguijuelas);
	this->bandMatrix();
	this->showMatriz();
}

void Windshield::putSanguijuela(vector< vector<double > > posSanguijuelas){
    int i,posX, posY;

	for(i=0; i< posSanguijuelas.size();i++){
        vector<Point> cubiertos = this->sanguijuelaPoints(Position(posSanguijuelas[i][0],posSanguijuelas[i][1]));
        for (int i = 0; i < cubiertos.size(); i++) {
            Point p = cubiertos[i];
            matrix[p.x][p.y]->status = SANGUIJUELA;
            matrix[p.x][p.y]->temp = ts;
        }

	}
}

double Windshield::distance(Position p1, Position p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return dx*dx + dy*dy;
}

vector<Point> Windshield::sanguijuelaPoints(Position sanguijuela) {
    vector<Point> v;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            Position p(j*h , i*h);
            if (this->distance(sanguijuela, p) <= r*r) {
                v.push_back(Point(i, j));
            }
        }
    }
    return v;
}


void Windshield::showMatriz(){
    int i,j;
    for(i=0; i< m;i++){
		for (j=0; j<n;j++){
            cout << i << " " << j << " " <<  matrix[i][j]->temp << "\n";
        }
	}
}

void Windshield::initialize(){
	this->initializeEmptyMatrix();
}

void Windshield::initializeEmptyMatrix(){

}

vector<vector<double> > Windshield::bandMatrix(){
	int ancho = n;
	  vector<vector<double> > bandMatrix  = vector<vector<double> >(n*m, vector<double>(ancho*2+2));
	int i,j, pos, res = ancho*2+1;
	for(i=0; i< m*n;i++){
		for (j=0; j<ancho*2+2;j++){
			bandMatrix[i][j] = 0;
		}
	}
	for(i=0; i< m;i++){
		for (j=0; j<n;j++){
			pos = j + i * n;
			switch(matrix[i][j]->status){
			case SANGUIJUELA:
				bandMatrix[pos][ancho] = 1;
				bandMatrix[pos][res] = ts;
				break;
			case FRIO:
				bandMatrix[pos][ancho] = 1;
				bandMatrix[pos][res] = -100;
				break;
			case VACIO:
				bandMatrix[pos][ancho] = -4;
				bandMatrix[pos][res] = 0;
				if(matrix[i][j-1]->status != VACIO) bandMatrix[pos][res] -= matrix[i][j-1]->temp;
				else bandMatrix[pos][ancho-1] = 1;
				if(matrix[i][j+1]->status != VACIO) bandMatrix[pos][res] -= matrix[i][j+1]->temp;
				else bandMatrix[pos][ancho+1] = 1;
				if(matrix[i-1][j]->status != VACIO) bandMatrix[pos][res] -= matrix[i-1][j]->temp;
				else bandMatrix[pos][0] = 1;
				if(matrix[i+1][j]->status != VACIO) bandMatrix[pos][res] -= matrix[i+1][j]->temp;
				else bandMatrix[pos][ancho*2] = 1;
				break;
			}
        }
	}
	//imprimirMatriz(bandMatrix, n*m, ancho*2+2);
	return bandMatrix;
}

void Windshield::resolveBandMatrix(vector<vector<double> > bandMatrix){
	cout << "RESOLVER" << "\n";
	int ancho = n*2+1;
	int fila, columna;
	//PRIMERO LA HAGO TRIANGULAR SUPERIOR
	for(int i = 0; i < n*m -1; i++){
		fila = i / n;
		columna = i % n;
        if(matrix[fila][columna]->status != VACIO)  continue; // SI NO ES VACIO SE QUE ABAJO HAY TODO CERO
        for( int h = 1; h <= n; h++){ // COMO ES BANDA ME FIJO SI EN LA DIAGONAL IZQ INF HAY DISTINTO DE 0 PARA PIVOTEAR
            if(i+h >= n*m || n-h < 0) break;
            double centro = bandMatrix[i][n];			
            double actual = bandMatrix[i+h][n-h];
            double multiplicador = actual / centro;
			if(esIgual(multiplicador,0)) continue;         
                for(int j = 0; j < n; j++){
                    bandMatrix[i+h][n-h+j] -= bandMatrix[i][n+j] * multiplicador;
					if(esIgual(bandMatrix[i+h][n-h+j], 0)) bandMatrix[i+h][n-h+j] = 0;					
                }
                bandMatrix[i+h][ancho] -= bandMatrix[i][ancho] * multiplicador;  				
        }
	}
	
	//AHORA RESUELVO :)
	
	for(int i = n*m-1; i >0; i--){
		fila = i / n;
		columna = i % n;
        for( int h = 1; h <= n; h++){ // COMO ES BANDA ME FIJO SI EN LA DIAGONAL IZQ INF HAY DISTINTO DE 0 PARA PIVOTEAR
            if(n+h >= ancho*2+1 || i-h < 0) break;
            double centro = bandMatrix[i][n];			
            double actual = bandMatrix[i-h][n+h];
            double multiplicador = actual / centro;
			if(esIgual(multiplicador,0)) continue;         
                for(int j = 0; j < n; j++){
                    bandMatrix[i-h][n+h+j] -= bandMatrix[i][n+j] * multiplicador;
					if(esIgual(bandMatrix[i-h][n+h+j], 0)) bandMatrix[i-h][n+h+j] = 0;					
                }
                bandMatrix[i-h][ancho] -= bandMatrix[i][ancho] * multiplicador;  				
        }
	}
	
	imprimirMatriz(bandMatrix, n*m, ancho+1);
}

int main() {
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
        cin >> rowS >> colS;
        posSanguijuelas[i][0] = rowS;
        posSanguijuelas[i][1] = colS;
    }


    Windshield *windshield = new Windshield(a, b, h, r, Ts, posSanguijuelas);
	vector<vector<double> > bandMatrix = windshield->bandMatrix();
	windshield->resolveBandMatrix(bandMatrix);

    return 0;
}


