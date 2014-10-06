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
#include "pagerank.cpp"

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

    PageRank pr(0.15, 0.0000001, 4, links);
    pr.ranking(100); //

    //CON MISMA PROBA
    links = * new vector<vector<int> >(4);
    links[0] = * new vector<int>(3);
    i = 0;
    links[0][i++] = 1;
    links[0][i++] = 2;
    links[0][i++] = 3;
    links[1] = * new vector<int>(3);
    i = 0;
    links[1][i++] = 0;
    links[1][i++] = 2;
    links[1][i++] = 3;
    links[2] = * new vector<int>(3);
    i=0;
    links[2][i++] = 0;
    links[2][i++] = 1;
    links[2][i++] = 3;
    links[3] = * new vector<int>(3);
    i=0;
    links[3][i++] = 0;
    links[3][i++] = 1;
    links[3][i++] = 2;

    //PageRank pr2(0.15, 4, links);
    //pr2.iterar(50); //

    links = * new vector<vector<int> >(5);
    links[0] = * new vector<int>(1);
    i = 0;
    links[0][i++] = 1;
    links[1] = * new vector<int>(1);
    i = 0;
    links[1][i++] = 0;
    links[2] = * new vector<int>(1);
    i=0;
    links[2][i++] = 3;
    links[3] = * new vector<int>(1);
    i=0;
    links[3][i++] = 2;
    links[4] = * new vector<int>(2);
    i=0;
    links[4][i++] = 3;
    links[4][i++] = 2;

    //PageRank pr3(0.15, links.size() ,links);
    //pr3.iterar(10); //
    for(int j = 0;  j < 4; j++)
        cout << "POS:" << j << " VALOR: "<< pr.v[j] << "\n";

    return 0;
}
