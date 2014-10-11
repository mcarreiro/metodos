#include "hits.h"
#include <utility>
#include <iostream>
#include <vector>
using namespace std;
Hits::Hits(vector<vector<int> >& links)  {
    matriz = * new DOK(links.size());
    for(unsigned int i = 0; i < links.size(); i++){
		vector<int> salidas = links[i];
		unsigned int cantSalidas = salidas.size();
        for(unsigned int j = 0; j < cantSalidas; j++){
			int s = salidas[j];
			matriz.definir(i, s, 1); // En la columna s pongo 1 porque sale a ella
        }
    }
    //Inicializo vectores de hubs y autoridades como dice el paper
    x = vector<double>(matriz.dim, 1);
    y =  vector<double>(matriz.dim, 1);
    x = this->normalizarVector(x);
    y = this->normalizarVector(y);
}


void Hits::hubsYautoridades(double tolerancia){
    int k = 100;
    DOK* matriz_transpuesta = matriz.transponer();
    vector<double> xPrevio;
    vector<double> yPrevio;
    double toleranciaX;
    double toleranciaY;
    for( int i = 0; i < k; i++){
        xPrevio = x;
        x = *matriz_transpuesta->porVector(y);
        x = this->normalizarVector(x);
        toleranciaX = this->manhattan(x,xPrevio);


        yPrevio = y;
        y = *matriz.porVector(x);
        y = this->normalizarVector(y);
        toleranciaY = this->manhattan(y,yPrevio);
        if(toleranciaY < tolerancia || toleranciaX < tolerancia){
            break;
        }
    }
}

vector<double> Hits::normalizarVector(vector<double> v){
    double suma = 0;
    for(unsigned int i = 0; i < v.size(); i++){
        suma += v[i]*v[i];
    }
    double norma2 = sqrt(suma);

    for(unsigned int i = 0; i < v.size(); i++){
        v[i] = v[i] / norma2;
    }
    return v;
}

double Hits::manhattan(vector<double>& x, vector<double>&y){
    double res = 0, parcial = 0;
    for(unsigned int i = 0; i < x.size(); i++){
        parcial = abs(x[i] - y[i]);
        if(parcial < 0.00000000000000001) parcial = 0;
        res += parcial;
    }
    return res;
}


