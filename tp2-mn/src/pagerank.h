#include <vector>
#include <cmath>
#include "dok.cpp"
using namespace std;
class PageRank
{
public:
    PageRank(){};
    PageRank(double, double,int, vector<vector<int> >&);
    void ranking(int);
    double manhattan(vector<double>&, vector<double>&);
    double c; //Probabilidad navegante aleatorio
    double tolerancia; //Criterio de parada
    vector<double> v;
    vector<int> desconectados;
    DOK matriz;
private:
    
};
