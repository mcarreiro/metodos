

#include <map>
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
    DOK* transponer();
    int dim;
    map<pair<int,int>, double> dicc;
private:


};
