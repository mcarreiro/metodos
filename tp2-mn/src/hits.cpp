#include "hits.h"
#include <utility>
#include <iostream>
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

    x = vector<double>(matriz.dim, 1);
    y =  vector<double>(matriz.dim, 1);
}


void Hits::hubsYautoridades(){
    int k = 10;
     DOK* matriz_transpuesta = matriz.transponer();
    for( int i = 0; i < k; i++){
        x = *matriz_transpuesta->porVector(y);
        y = *matriz_transpuesta->porVector(x);
        x = this->normalizarVector(x);
        y = this->normalizarVector(y);
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


