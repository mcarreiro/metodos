#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include "dok.cpp"
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
    string tipoInstancia, path;
	int alg;	
    double c, tolerancia;
    input_file >> alg >> c >> tipoInstancia >> path >> tolerancia;
    cout  << alg << c << tipoInstancia << path << tolerancia;


    vector<vector<int> > links = readFile(path);
	

	if(alg==0) { 
		PageRank pr(c, tolerancia, links.size(), links);
		pr.ranking(100);
			for(int j = 0;  j < links.size(); j++)
				cout << "POS:" << j << " VALOR: "<< pr.v[j] << "\n";
	}

	if(alg==1){
		Hits h(links);
		h.hubsYautoridades();
		for(int j = 0;  j < links.size(); j++)
					cout << "POS:" << j << " VALOR X: "<< h.x[j] << "\n";
		for(int j = 0;  j < links.size(); j++)
					cout << "POS:" << j << " VALOR Y: "<< h.y[j] << "\n";
	}

	
	


 

    return 0;
}
