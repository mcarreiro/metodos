#ifndef Bilineal_H
#define Bilineal_H
#include "pixel.cpp"

class Bilineal{
public:
    Bilineal(){};

    int enRango(vector<int> punto,vector<vector<Pixel> >& imagen){
        int width = imagen.size();
        int height = imagen[0].size();
        return punto[0] >= 0 && punto[1] >= 0 && punto[1] < height && punto[0] < width;
    }

    int funcionLineal(int i, int j, vector<vector<int> > puntos, vector<vector<Pixel> >& imagen, color colorACalcular){
        int cantPuntos = 0;
        int resultado = 0;

        for (int f = 0 ; f<puntos.size() ; f++ ){
            vector<int> punto = puntos[f];
            if (enRango(punto,imagen)){
                if (colorACalcular == ROJO){
                    resultado += imagen[punto[0]][punto[1]].rojo;
                }else if (colorACalcular == VERDE){
                    resultado += imagen[punto[0]][punto[1]].verde;
                } else {
                    resultado += imagen[punto[0]][punto[1]].azul;
                }
                cantPuntos++;
            }
        }
        return resultado/cantPuntos;
    }

    void hacerAzul(int i,int j,vector<vector<Pixel> >& imagen){
        imagen[i][j].rojo = funcionLineal(i,j,{{i-1,j+1},{i-1,j-1},{i+1,j-1},{i+1,j+1}},imagen,ROJO);
        imagen[i][j].verde = funcionLineal(i,j,{{i,j+1},{i-1,j},{i,j-1},{i+1,j}},imagen,VERDE);
    }

    void hacerRojo(int i,int j,vector<vector<Pixel> >& imagen){
        imagen[i][j].azul = funcionLineal(i,j,{{i+1,j-1},{i-1,j-1},{i-1,j+1},{i+1,j+1}},imagen,AZUL);
        imagen[i][j].verde = funcionLineal(i,j,{{i,j+1},{i-1,j},{i,j-1},{i+1,j}},imagen,VERDE);
    }

    void hacerVerdePar(int i,int j,vector<vector<Pixel> >& imagen){
        imagen[i][j].rojo = funcionLineal(i,j,{{i,j-1},{i,j+1}},imagen,ROJO);
        imagen[i][j].azul = funcionLineal(i,j,{{i-1,j},{i+1,j}},imagen,AZUL);
    }

    void hacerVerdeImpar(int i,int j,vector<vector<Pixel> >& imagen){
        imagen[i][j].azul = funcionLineal(i,j,{{i,j-1},{i,j+1}},imagen,AZUL);
        imagen[i][j].rojo = funcionLineal(i,j,{{i-1,j},{i+1,j}},imagen,ROJO);
    }


    void hacer(vector<vector<Pixel> >& imagen){
        int width = imagen.size();
        int height = imagen[0].size();
        //cout << "Bilineal altura " << height << " ancho " << width << flush << endl;
        for(int i=0; i< width; i++) {
            for(int j=0; j< height; j++) {
                if (i %2 == 0 && j % 2 == 0){ //ACA HAY AZUL
                    hacerAzul(i,j,imagen);
                }else if (i %2 == 1 && j % 2 == 1){ //ACA HAY ROJO
                    hacerRojo(i,j,imagen);
                } else if ( j%2 == 0){ //ACA HAY VERDE EN FILA PAR
                    hacerVerdePar(i,j,imagen);
                } else { //ACA HAY VERDE EN FILA IMPAR
                    hacerVerdeImpar(i,j,imagen);
                }
            }
        }

    };
};

#endif