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
    inputFile >> width >> height;

    cout << "C++ ancho: " << width << " altura: " << height << flush << endl;

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

    Vecino metodo1 = Vecino();
//    metodo1.hacer(imagen);

    Bilineal metodo2 = Bilineal();
    metodo2.hacer(imagen);

    return 0;
}