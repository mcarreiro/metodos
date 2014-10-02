#include "pagerank.h"
#include <utility>      // std::pair
#include <iostream>     // std::cout
#include <iomanip>

//links: en la pos "i" tiene un vector con sus links "j" de salida
PageRank::PageRank(double c, int dim, vector<vector<int> >& links) : c(c){

	v = * new vector<double>(dim);

	for(int i = 0; i < dim; i++){
		v.at(i) = 1/(double)dim;
	}


	matriz = * new DOK(dim);
	for(unsigned int i = 0; i < links.size(); i++){

		vector<int> salidas = links[i];
		int cantSalidas = salidas.size();

		if(cantSalidas != 0){
			for(int j = 0; j < cantSalidas; j++){
				int s = salidas[j];

				matriz.definir(s, i, 1.0/cantSalidas); // En la columna i se define a los s que sale.
			}
		}else{
			for(int j = 0; j < dim; j++)
			{
				if(j != 1)
					matriz.definir(j, i, 1.0/(dim-1));
			}
		}
	}

}

double PageRank::manhattan(){
	double res = 0;
	for(unsigned int i = 0; i < v.size(); i++){
		res += v[i];
	}
	return res;
}

void PageRank::iterar(int iteraciones = 1){
	for(int i = 0; i < iteraciones; i++){
		this->v = *matriz.porVector(v);
		cout << "IT: " << i << "NORMA: "<< this->manhattan() << "\n";
	}
}
