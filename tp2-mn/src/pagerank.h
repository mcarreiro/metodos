#include <vector>
#include <cmath>
#include "dok.h"

class PageRank
{
public:
    PageRank(){};
    PageRank(double,int, vector<vector<int> >&);
    void iterar(int);
    double manhattan();
    double c; //Probabilidad navegante aleatorio
    vector<double> v;
    DOK matriz;
private:
    
};
