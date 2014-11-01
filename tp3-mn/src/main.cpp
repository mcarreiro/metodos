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
    for(int i=0; i< height; i++) {
        imagen[i].resize(height);
        for (int j = 0; j < width; j++) {
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
    ofstream myfile (output.c_str());

    for(int i=0; i< height; i++) {
        for (int j = 0; j < width; j++) {
            myfile << imagen[i][j].rojo << " " << imagen[i][j].verde << " " << imagen[i][j].azul << endl;
        }
    }

    return 0;
}