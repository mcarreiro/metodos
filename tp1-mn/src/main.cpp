#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<double> rvector; 
typedef vector<rvector> rmatrix;

enum statusPoint {VACIO,SANGUIJUELA,FRIO};

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
    Windshield(){};
	Windshield(int x, int y, float ah, int ar, float temp, vector< vector<double > > posSanguijuelas);
	vector<vector<double> > bandMatrix();
	void resolveBandMatrix(vector<vector<double> > bandMatrix);
	void showMatriz();
	void putSanguijuela(vector< vector<double > > posSanguijuelas);
	double distance(Position p1, Position p2);
	vector<Point> sanguijuelaPoints(Position sanguijuela);
	vector<double> gaussianElimination();
private:

	vector< vector< double > > prepareSystemOfEquations();
	vector< double > resolveByGaussianElimination(rmatrix& A, rvector& b);
	void calculateForAdjacent(int x, int y, vector< vector< double > > systemOfEquations, int pos);
	rvector backSubstitution(const rmatrix& A, const rvector& b);
	bool doGaussianElimination(rmatrix& A, rvector& b);
	int find_max(const rmatrix& A, int k);

	int a;
    int b;
    float h;
    int r;
	float ts;
    int m;
    int n;

	vector< vector<Point *> > matrix;
	vector< double > bVector;
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
				if(matrix[i-1][j]->status != VACIO) bandMatrix[pos][res] -= matrix[i-1][j]->temp;
				else bandMatrix[pos][ancho-1] = 1;
				if(matrix[i+1][j]->status != VACIO) bandMatrix[pos][res] -= matrix[i+1][j]->temp;
				else bandMatrix[pos][ancho+1] = 1;
				if(matrix[i][j-1]->status != VACIO) bandMatrix[pos][res] -= matrix[i][j-1]->temp;
				else 
					bandMatrix[pos][0] = 1;
				if(matrix[i][j+1]->status != VACIO) bandMatrix[pos][res] -= matrix[i][j+1]->temp;
				else bandMatrix[pos][ancho*2] = 1;
				break;
			}
        }
	}
	return bandMatrix;
}

void Windshield::resolveBandMatrix(vector<vector<double> > bandMatrix){
	int ancho = n*2+1;
	int fila, columna;
	for(int i = 0; i < n*m -1; i++){
		fila = i / n;
		columna = i % n;
        if(matrix[fila][columna]->status != VACIO)  continue; // SI NO ES VACIO SE QUE ABAJO HAY TODO CERO
        for( int h = 1; h <= n; h++){ // COMO ES BANDA ME FIJO SI EN LA DIAGONAL IZQ INF HAY DISTINTO DE 0 PARA PIVOTEAR
            if(i+h >= n*m || n-h < 0) break;
            double centro = bandMatrix[i][n];
			
            double actual = bandMatrix[i+h][n-h];
            double multiplicador = actual / centro;
			if(multiplicador == 0) continue;         
                for(int j = 0; j < n; j++){
					double pivote = bandMatrix[i][n+j];
					double antes = bandMatrix[i+h][n-h+j];
                    bandMatrix[i+h][n-h+j] -= bandMatrix[i][n+j] * multiplicador;
					double desp = bandMatrix[i+h][n-h+j];
					int sdasd = 2;
                }
                bandMatrix[i+h][ancho] -= bandMatrix[i][ancho] * multiplicador;            
        }



	}
	int b = 2;
}

vector<double> Windshield::gaussianElimination(){
	vector<vector<double > > systemOfEquations = prepareSystemOfEquations(); // N X N

	vector<double> solution = resolveByGaussianElimination(systemOfEquations,bVector); //Gaussian Elimination resolver

	for (int i = 0 ; i < solution.size() ; i++){
		cout << solution[i] << " ";
	}

	return solution;
}

vector< vector<double > > Windshield::prepareSystemOfEquations(){
	vector< vector<double > > systemOfEquations = vector< vector <double > >(m*n, vector<double >(m*n));
	bVector = vector<double>(m*n);
	int pos,otherPos,i,j;

	for(i=0; i< m*n;i++){
		bVector[i] = 0;
		for (j=0; j < m*n ; j++){
			systemOfEquations[i][j] = 0;
		}
	}

	for (int i = 0 ; i < m ; ++i){
		for (int j = 0 ; j < n ; ++j){
			pos = j + (i * n);
			switch(matrix[i][j]->status){
				case SANGUIJUELA:
					systemOfEquations[pos][pos] = 1;
					bVector[pos] = ts;
				case FRIO:
					systemOfEquations[pos][pos] = 1;
					bVector[pos] = -100;
				case VACIO:
					systemOfEquations[pos][pos] = -4;
					bVector[pos] = 0;
					calculateForAdjacent(i-1,j,systemOfEquations,pos);
					calculateForAdjacent(i+1,j,systemOfEquations,pos);
					calculateForAdjacent(i,j+1,systemOfEquations,pos);
					calculateForAdjacent(i,j-1,systemOfEquations,pos);
			}
		}
	}

	return systemOfEquations;
}

void Windshield::calculateForAdjacent(int x, int y, vector< vector< double > > systemOfEquations, int pos){
	if(matrix[x][y]->status != VACIO){ 
		bVector[pos] -= matrix[x][y]->temp;
	}else{ 
		int otherPos = y + (x * n);
		systemOfEquations[pos][otherPos] = 1;
	}
}

rvector Windshield::backSubstitution(const rmatrix& A, const rvector& b) { 
	int n = A.size();

	rvector x(n); // Creates the vector for the solution
	  // Calculates x from x[n-1] to x[0]
	for (int i = n - 1; i >= 0; --i) {
		// The values x[i+1..n-1] have already been calculated 
		double s = 0;
		for (int j = i + 1; j < n; ++j) s = s + A[i][j] * x[j];
		
		x[i] = (b[i] - s)/A[i][i];
	}
	return x; 
}

bool Windshield::doGaussianElimination(rmatrix& A, rvector& b) {
  	int n = A.size();
  	// Reduce rows 0..n-1
	for (int k = 0; k < n; ++k) {
		// Rows 0..k have already been reduced
		int imax = find_max(A, k); // finds the max pivot
		if (A[imax][k] == 0) return true; // Singular matrix
	    swap(A[k], A[imax]); swap(b[k], b[imax]); // Swap rows k and imax
	    // Force 0’s in column A[k+1..n-1][k]
		for (int i = k + 1; i < n; ++i) {
			double c = A[i][k]/A[k][k]; // coefficient to scale row A[i][k] = 0;
			for (int j = k + 1; j < n; ++j) A[i][j] = A[i][j] - c * A[k][j]; 
			b[i] = b[i] - c * b[k];
		} 
	}
  	return false; // We have a non-singular matrix
}

int Windshield::find_max(const rmatrix& A, int k) {
  	int n = A.size();
	double imax = k; // index of the row with max pivot 
	double max_pivot = abs(A[k][k]);
	for (int i = k + 1; i < n; ++i) { 
		double a = abs(A[i][k]);
		if (a > max_pivot) {
	        max_pivot = a;
			imax = i; 
		}
	}
    return imax;
}


rvector Windshield::resolveByGaussianElimination(rmatrix& A, rvector& b) { 
	bool singular = doGaussianElimination(A, b);
	if (singular) return rvector(0);
	// A is in row echelon form
	return backSubstitution(A, b); 
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


