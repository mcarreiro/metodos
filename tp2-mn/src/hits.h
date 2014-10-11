#include <vector>
#include <cmath>
using namespace std;
class Hits
{
public:
    Hits( vector<vector<int> >&);
    void hubsYautoridades(double tolerancia);
    vector<double> x;
    vector<double> y;

private:
    DOK matriz;
    vector<double> normalizarVector(vector<double>);
    double manhattan(vector<double>&, vector<double>&);
};
