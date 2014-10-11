#include "indeg.h"
#include <utility>      // std::pair
#include <iostream>     // std::cout
#include <vector>

//links: en la pos "i" tiene un vector con sus links "j" de salida
Indeg::Indeg(vector<vector<int> > links){

	int totalAmountOfDomains = links.size();

	values = vector<int>(totalAmountOfDomains);
	valuesQuality = vector<int>(totalAmountOfDomains);

	for(int i = 0 ; i < values.size() ; i++){
		values[i] = 0;
		valuesQuality[i] = 0;
	}

	for(int i = 0; i < links.size(); i++){
		vector<int> salidas = links[i];
		int cantSalidas = salidas.size();
		if(cantSalidas != 0){
			for(int j = 0; j < cantSalidas; j++){
				int s = salidas[j]; //Page I goes to S
				values[s] = values[s] + 1;
				valuesQuality[s] = valuesQuality[s] + 1/totalAmountOfDomains;
			}
		}
	}
}

void Indeg::print(){
	cout << "PAGINA I LO APUNTAN X PAGINAS";
    for(int i=0;i<values.size();i++){
        //cout << i << values[i] << endl;
    }

    cout << "PAGINA I TIENE PUNTAJE REFERENCIAL";
    for(int i=0;i<values.size();i++){
        cout << i << valuesQuality[i] << endl;
    }
}