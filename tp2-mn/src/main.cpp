#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "pagerank.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<vector<int> > links = * new vector<vector<int> >(4);
    links[0] = * new vector<int>(3);
    int i = 0;
    links[0][i++] = 1;
    links[0][i++] = 2;
    links[0][i++] = 3;
    links[1] = * new vector<int>(2);
    i = 0;
    links[1][i++] = 2;
    links[1][i++] = 3;
    links[2] = * new vector<int>(1);
    i=0;
    links[2][i++] = 0;
    links[3] = * new vector<int>(2);
    i=0;
    links[3][i++] = 0;
    links[3][i++] = 2;

    PageRank pr(0.15, 4, links);
    pr.iterar(20); //

    return 0;
}
