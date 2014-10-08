#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "pagerank.cpp"
#include "hits.cpp"
#include "indeg.cpp"
#include "readFile.cpp"


using namespace std;

int main(int argc, char *argv[]) {

    string input = argv[1];
    string output = argv[2];

    ifstream input_file (input.c_str());
    string path;
	int alg, tipoInstancia;	
    double c, tolerancia;
    input_file >> alg >> c >> tipoInstancia >> path >> tolerancia;
    //cout  << alg << c << tipoInstancia << path << tolerancia;


    vector<vector<int> > links;
    if(tipoInstancia==0)
		links = leerInstancia0(path);
	else
		links = leerInstancia1(path);


	if(alg==0) {
		PageRank pr(c, tolerancia, links.size(), links);
		pr.ranking(100);
			//for(int j = 0;  j < links.size(); j++)
				//cout << "POS:" << j << " VALOR: "<< pr.v[j] << "\n";
	}

	if(alg==1){
		Hits h(links);
		h.hubsYautoridades(tolerancia);
		for(int j = 0;  j < links.size(); j++)
					cout << "POS:" << j << " VALOR X: "<< h.x[j] << "\n";
		for(int j = 0;  j < links.size(); j++)
					cout << "POS:" << j << " VALOR Y: "<< h.y[j] << "\n";
	}
	
	if(alg==2){
		Indeg indeg (links);
		indeg.print();
	}







    return 0;
}
