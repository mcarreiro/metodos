#include "pixel.cpp"
#include <vector>

typedef unsigned int nat;

using namespace std;

class HighQuality{

public:
    HighQuality(){};

    void hacer(vector<vector<Pixel > >& imagen){

        Bilineal bilineal();
        bilineal.hacer(imagen);
        
        double correccion;

        int width = imagen.size();
        int height = imagen[0].size();
        for(int i=2; i< height-2; i++) {
            for(int j=2; j< width-2; j++) {
                correccion = 0;
                if (i %2 == 0 && j % 2 == 0){ //ACA HAY AZUL
                    
                    correccion += imagen[i][j-2].azul;
                    correccion += imagen[i-2][j].azul;
                    correccion += imagen[i][j+2].azul;
                    correccion += imagen[i+2][j].azul;
                    correccion = imagen[i][j].azul - correccion/4;
                    imagen[i][j].verde += 0.75 * correccion;
                    imagen[i][j].rojo += 0.75 * correccion;
                
                }else if (i %2 == 1 && j % 2 == 1){ //ACA HAY ROJO
                    
                    correccion += imagen[i][j-2].rojo;
                    correccion += imagen[i-2][j].rojo;
                    correccion += imagen[i][j+2].rojo;
                    correccion += imagen[i+2][j].rojo;
                    correccion = imagen[i][j].rojo - correccion/4;
                    imagen[i][j].verde += 0.5 * correccion;
                    imagen[i][j].azul += 0.5 * correccion;


                } else { //ACA HAY VERDE

                    correccion += imagen[i][j-2].verde;
                    correccion += imagen[i-2][j].verde;
                    correccion += imagen[i][j+2].verde;
                    correccion += imagen[i+2][j].verde;

                    correccion += imagen[i+1][j+1].verde;
                    correccion += imagen[i-1][j+1].verde;                    
                    correccion += imagen[i-1][j-1].verde;
                    correccion += imagen[i+1][j-1].verde;

                    correccion = imagen[i][j].verde - correccion/4;
                    imagen[i][j].verde += correccion * 5/8;
                    imagen[i][j].rojo += correccion * 5/8;
                    
                } 
            }
        }

    };

};