#include "pagerank.h"
#include <utility>      // std::pair
#include <iostream>     // std::cout
#include <iomanip>

//links: en la pos "i" tiene un vector con sus links "j" de salida
PageRank::PageRank(double c, double tolerancia, int dim, vector<vector<int> >& links) : c(c), tolerancia(tolerancia){

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

double PageRank::manhattan(vector<double>& x, vector<double>&y){
	double res = 0;
	for(unsigned int i = 0; i < x.size(); i++){
		res += abs(x[i] - y[i]);
	}
	return res;
}

void PageRank::ranking(int max){

	//M = (1-c)*A + c * B con B = 1/n * matriz de unos
	//Mv = (1-c) * Av + c*Bv 

    int tam = v.size();
    int it = 0;
    double norma;
	while(it == 0 || (norma > tolerancia && it < max)  ){


        vector<double> w = v;
        v = *matriz.porVector(v);
        for (int i = 0; i < tam; i++){
            v[i] = (1-c)*v[i]+(c/(double)tam);
			//cout << v[i] << ";";
		}
		norma = this->manhattan(v,w);
		cout << "IT: " << it << "NORMA: "<< norma << "\n";
		it++;
	}
}
