#include <vector>
#include <cmath>
#include "dok.cpp"

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
