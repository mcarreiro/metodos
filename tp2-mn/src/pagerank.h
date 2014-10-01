#include <vector>
#include <cmath>
#include "dok.h"

class PageRank
{
public:
    PageRank(double, vector<vector<int> >&);    
    void iterar(int);
    double manhattan();
private:
    double c; //Probabilidad navegante aleatorio
    vector<double> v;
    DOK matriz;
};