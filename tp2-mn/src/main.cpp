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
    string metodoAEjecutar, tipoInstancia, path;
    double c, tolerancia;
    input_file >> metodoAEjecutar >> c >> tipoInstancia >> path >> tolerancia;
    cout  << metodoAEjecutar << c << tipoInstancia << path << tolerancia;


    vector<vector<int> > links = readFile(path);



    PageRank pr(c, tolerancia, links.size(), links);
    pr.ranking(100);

    for(int j = 0;  j < links.size(); j++)
        cout << "POS:" << j << " VALOR: "<< pr.v[j] << "\n";

    return 0;
}
