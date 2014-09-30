#include "dok.h"
#include <utility>      // std::pair
#include <iostream>     // std::cout
DOK::DOK(int dim) : dim(dim) {}

void DOK::definir(int f, int c, double val)
{
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
                result->dicc[make_pair(itIZQ->first.first, itDER->first.second)] += dicc[itIZQ->first] * otra.dicc[itDER->first];
                if(  result->dicc[make_pair(itIZQ->first.first, itDER->first.second)] == 0) // SI SE VUELVE CERO LO TENGO QUE BORRAR
                     result->dicc.erase(make_pair(itIZQ->first.first, itDER->first.second));
            }
        }
    }
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
        result->definir(f, c, valor);
    }
    return result;
}
