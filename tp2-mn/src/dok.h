

#include <map>
#include <vector>
#include <utility>      // std::pair
#include <iostream>     // std::cout
using namespace std;
class DOK
{
public:
    DOK() {};
    DOK(int dim);
    void definir(int, int, double);
    double obtener(int f, int c);
    DOK* multiplicar(DOK&);
    vector<double>* porVector(vector<double>&);
    DOK* transponer();
    double cantColNoCero(int);
    int dim;
    map<pair<int,int>, double> dicc;
private:


};
