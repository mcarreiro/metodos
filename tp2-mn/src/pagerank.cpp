#include "pagerank.h"
#include <utility>      // std::pair
#include <iostream>     // std::cout

 PageRank::PageRank(double c, vector<vector<int> >& links) : c(c) {
 	// aca crear el dok
 	int dim = links.size();
 	v = new vector<double>(dim);
 	for(int = 0; i < dim; i++)
 		v[i] = 1/dim;
 }    

double PageRank::manhattan(){
	double res = 0;
	for(int i = 0; i < v.size(); i++){
		res += v[i];
	}
	return res;
}

void PageRank::iterar(int iteraciones = 1){
	for(int i = 0; i < iteraciones; i++){
		v = matriz.porVector(v);		
	}
}