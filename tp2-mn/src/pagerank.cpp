#include "pagerank.h"
#include <utility>      // std::pair
#include <iostream>     // std::cout
#include <iomanip>

//links: en la pos "i" tiene un vector con sus links "j" de salida
PageRank::PageRank(double c, int dim, vector<vector<int> >& links) : c(c){

	v = * new vector<double>(dim);

	for(int i = 0; i < dim; i++){
		v.at(i) = 1.00/(double)dim;
	}


	matriz = * new DOK(dim);
	for(unsigned int i = 0; i < links.size(); i++){

		vector<int> salidas = links[i];
		int cantSalidas = salidas.size();

		if(cantSalidas != 0){
			for(int j = 0; j < cantSalidas; j++){
				int s = salidas[j];

				matriz.definir(s, i, 1.00/cantSalidas ); // En la columna i se define a los s que sale.
			}
		}else{
			/*for(int j = 0; j < dim; j++)
			{
				//if(j != 1)
					matriz.definir(j, i, 1.0/(dim));
			}*/
		}
	}

}

double PageRank::manhattan(){
	double res = 0;
	for(unsigned int i = 0; i < v.size(); i++){
		res += abs(v[i]);
	}
	return res;
}

void PageRank::iterar(int iteraciones = 1){

	//M = (1-c)*A + c * B con B = 1/n * matriz de unos
	//Mv = (1-c) * Av + c*Bv 

    int tam = v.size();
	for(int it = 0; it < iteraciones; it++){
		/*
        double normaX = manhattan();
        v = *matriz.porVector(v);
        for (int i = 0; i < tam; i++)
            v[i] = c*v[i];
        double normaY = manhattan();
        double w = normaX - normaY;
        for (int i = 0; i < tam; i++)
            v[i] = v[i]+w*(1.0/tam);
       */

        vector<double> w = *matriz.porVector(v);
        for (int i = 0; i < tam; i++){
            v[i] = (1-c)*w[i]+(c/(double)tam);
			//cout << v[i] << ";";
		}
		cout << "IT: " << it << "NORMA: "<< this->manhattan() << "\n";
	}
}
