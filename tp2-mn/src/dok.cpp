#include "dok.h"
#include <utility>      // std::pair
#include <iostream>     // std::cout
DOK::DOK(int dim) : dim(dim) {}

void DOK::definir(int f, int c, double val)
{
    cout << "DEFINIR:" << val << " POS: (" << f << " , " << c << ")\n";
   pair<int,int> pos = make_pair(f,c);
    if(val != 0){ // Lo tengo que agregar o modificar valor.
        dicc[pos] = val;
    }else{ // Lo tengo que borrar
        if(dicc.count(pos) > 0)
        {
            dicc.erase(pos);
        }
    }
}
double DOK::obtener(int f, int c){
    pair<int,int> pos = make_pair(f,c);
    return (dicc.count(pos) > 0) ? dicc[pos] : 0;
}

double DOK::cantColNoCero(int c){
    int cant = 0;
    for(map<pair<int, int>, double>::iterator iterador = dicc.begin();
        iterador != dicc.end();
        iterador++)
    {
        if(iterador->first.second == c)
            cant++;
    }
    return cant;
}

DOK* DOK::multiplicar(DOK& otra)
{

    DOK *result  = new DOK();
    for(map<pair<int, int>, double>::iterator itIZQ = dicc.begin();
        itIZQ != dicc.end();
        itIZQ++)
    {

        for(map<pair<int, int>, double>::iterator itDER = otra.dicc.begin();
        itDER != otra.dicc.end();
        itDER++)
        {
            // (A,B) * (C,D) con B=C y la sumo en (A,D)
            if(itIZQ->first.second == itDER->first.first){
                pair<int, int> pos = make_pair(itIZQ->first.first, itDER->first.second);
                result->dicc[pos] += dicc[itIZQ->first] * otra.dicc[itDER->first];
                if(result->dicc[pos] == 0) // SI SE VUELVE CERO LO TENGO QUE BORRAR
                     result->dicc.erase(pos);
            }
        }
    }
    return result;
}

vector<double>* DOK::porVector(vector<double>& v){
    vector<double>* result = new vector<double>(v.size());
    for(unsigned int i = 0; i < v.size(); i++)
        result->at(i) = 0.00;
   for(map<pair<int, int>, double>::iterator iterador = dicc.begin();
        iterador != dicc.end();
        iterador++)
    {
        // POS <A,B> por la posicion B del vector y lo sumo a la posicion A
        pair<int, int> pos = iterador->first;
        //cout << "( "<<pos.first << " , " << pos.second << ")\n";

        //cout << "EL VALOR:" << result->at(pos.first) << "\n";

        result->at(pos.first) += dicc[pos] * v[pos.second];

    }
        for(unsigned int i = 0; i < v.size(); i++)
        cout << "VECTOR POS:" << i << " VALOR: "<< result->at(i) << "\n";
    return result;
}

DOK* DOK::transponer()
{
    DOK *result  = new DOK();
    for(map<pair<int, int>, double>::iterator iterador = dicc.begin();
        iterador != dicc.end();
        iterador++)
    {
        int f = iterador->first.first;
        int c = iterador->first.second;
        double valor = iterador->second;
        result->definir(c, f, valor);
    }
    return result;
}
