#include "pixel.cpp"
#include <vector>

typedef unsigned int nat;

using namespace std;

class Vecino{

public:
    Vecino(){};

    void hacer(vector<vector<Pixel > >& imagen){
        int width = imagen.size();
        int height = imagen[0].size();
        //cout << "Vecino altura " << height << " ancho " << width << flush << endl;
        for(int i=0; i< width; i++) {
            for(int j=0; j< height; j++) {
                if (i %2 == 0 && j % 2 == 0){ //ACA HAY AZUL
                    nat verde = imagen[i][j+1].verde;
                    nat rojo = imagen[i+1][j+1].rojo;
                    imagen[i][j].verde = verde;
                    imagen[i][j].rojo = rojo;
                }else if (i %2 == 1 && j % 2 == 1){ //ACA HAY ROJO
                    nat verde = imagen[i][j-1].verde;
                    nat azul = imagen[i-1][j-1].azul;
                    imagen[i][j].verde = verde;
                    imagen[i][j].azul = azul;
                } else if ( j%2 == 0){ //ACA HAY VERDE EN FILA PAR
                    nat rojo = imagen[i][j+1].rojo;
                    nat azul = imagen[i-1][j].azul;
                    imagen[i][j].rojo = rojo;
                    imagen[i][j].azul = azul;
                } else { //ACA HAY VERDE EN FILA IMPAR
                    nat rojo = imagen[i+1][j].rojo;
                    nat azul = imagen[i][j-1].azul;
                    imagen[i][j].rojo = rojo;
                    imagen[i][j].azul = azul;
                }
            }
        }
    };

};