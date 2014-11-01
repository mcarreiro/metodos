#include <iostream>
#include <fstream>
#include <vector>
#include "pixel.cpp"
#include "vecino.cpp"
#include "bilineal.cpp"

using namespace std;

typedef unsigned int nat;

int main(int argc, char* argv[]) {
    std::ifstream inputFile(argv[1]);

    int height, width;
    nat color;
    inputFile >> height >> width;

    cout << "C++ altura: " << height << " ancho: " << width << flush << endl;

    vector<vector<Pixel> > imagen;

    imagen.resize(width);

    //Load data
    for(int i=0; i< width; i++) {
        imagen[i].resize(height);
        for (int j = 0; j < height; j++) {
            imagen[i][j] = Pixel();

            inputFile >> color;
            if(i%2 == 0) {
                if(j%2 == 0) {
                    imagen[i][j].azul = color;
                } else {
                    imagen[i][j].verde = color;
                }
            } else {
                if(j%2 == 0) {
                    imagen[i][j].verde = color;
                } else {
                    imagen[i][j].rojo = color;
                }
            }
        }
    }

    cout << "Imprimiendo archivo!"<< flush << endl;

    Vecino metodo1 = Vecino();
//    metodo1.hacer(imagen);

    Bilineal metodo2 = Bilineal();
    metodo2.hacer(imagen);

    string output = argv[2];
    ofstream myfile (output);

    cout << "Imprimiendo archivo2!"<< flush << endl;

    for(int a=0; a< width; a++) {
        for (int b = 0; b < height; b++) {
            myfile << imagen[a][b].rojo << " " << imagen[a][b].verde << " " << imagen[a][b].azul << flush << endl;
        }
    }

    return 0;
}