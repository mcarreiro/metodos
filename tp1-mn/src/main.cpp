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

	Point() {
        temp = NULL;
        status = VACIO;
	};

	Point(int xa, int ya, float tempa, statusPoint statusa) : x(xa), y(ya), temp(tempa), status(statusa) {};
};

class Windshield {
public:
    Windshield(){
        vector<vector<Point *> > matrix(0, vector<Point *>(0));
    };
	Windshield(int x, int y, float ah, int ar);
	void initialize();
	void initializeEmptyMatrix();

private:
	int a;
    int b;
    float h;
    int r;

    int m;
    int n;

	vector< vector<Point *> > matrix;
};

Windshield::Windshield(int x, int y, float ah, int ar) {
    a = x;
    b = y;
	h = ah;
	r = ar;

	m = (a/h) + 1;
	n = (b/h) + 1;

	cout << "ants";

    //1matrix = vector<vector<Point *> >(m, vector<Point *>(n));

    cout << matrix.size();

	this->initialize();
}

void Windshield::initialize(){
	this->initializeEmptyMatrix();
}

void Windshield::initializeEmptyMatrix(){
    int i,j;
	for(i=0; i< m;i++){
		for (j=0; j<n;j++){
            matrix[i][j]->y = j;
			if (j == 0 || i == 0){
//                matrix.at(i).at(j).temp = -100;
//                matrix.at(i).at(j).status = FRIO;
            }
        }
	}
}

int main() {
	int a,b,h,r;
	cout << "Ingrese con enters en el medio, a, b, h y r" << "\n";
//	cin >> a >> b >> h >> r;
	a = 2;
	b = 2;
	h = 1;
	r = 1;
	cout << "ants";
    Windshield *windshield = new Windshield(a,b,h,r);

    return 0;
}

