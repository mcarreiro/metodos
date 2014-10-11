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
    //cout << flush;

    vector<vector<int> > links;

    if(tipoInstancia==0)
		links = leerInstancia0(path);
	else if(tipoInstancia==1)
		links = leerInstancia1(path);
	else if(tipoInstancia==3)
		links = vector<vector<int> >(150000, vector<int>(1,1));
    else 
        links = leerInstancia2(path);
 	
 	ofstream myfile (output.c_str());
	  cout << output;

	if(alg==0) {
        if(tipoInstancia != 2){
		  PageRank pr(c, tolerancia, links.size(), links);
          pr.ranking(1000);

          		for(int j = 0;  j < links.size(); j++){
          	myfile << fixed;
          	myfile << setprecision(5) << pr.v[j] << "\n";
          }
        }else{
            double cc = atoi(argv[3])/(double)10;
            //cout << "ATOI:" << cc;
          PageRank pr(cc, tolerancia , links.size(), links);
          pr.ranking(1000);

          		for(int j = 0;  j < links.size(); j++){
          	myfile << fixed;
          	myfile << setprecision(5) << pr.v[j] << "\n";
          }
          
      }


			//for(int j = 0;  j < links.size(); j++)
				//cout << "POS:" << j << " VALOR: "<< pr.v[j] << "\n";
	}

	if(alg==1){
		Hits h(links);
		h.hubsYautoridades(tolerancia);


		for(int j = 0;  j < links.size(); j++){
			myfile << fixed;
			myfile << setprecision(5) << h.x[j] << "\n";

		}
				
					
		for(int j = 0;  j < links.size(); j++){
			myfile << fixed;
			myfile << setprecision(5) << h.y[j] << "\n";
		}
					

	}
	
	if(alg==2){
		Indeg indeg (links);
		//indeg.print();

		myfile << fixed;
		 for(int i=0;i<indeg.values.size();i++){
        myfile << indeg.valuesQuality[i] << endl;
    }

	}

	myfile.close();






    return 0;
}
