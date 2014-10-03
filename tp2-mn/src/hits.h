#include <vector>
#include <cmath>
#include "dok.h"
class Hits
{
public:
    Hits( vector<vector<int> >&);
    void hubsYautoridades();
    vector<double> x;
    vector<double> y;
private:
    DOK matriz;
    vector<double> normalizarVector(vector<double>);
};
