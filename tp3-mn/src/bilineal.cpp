#include "pixel.cpp"

class Bilineal{
public:
    Bilineal(){};

    int enRango(vector<int> punto){
        return punto[0] >= 0 && punto[1] >= 0;
    }

    int funcionLineal(int i, int j, vector<vector<int> > puntos, vector<vector<Pixel> > imagen, color colorACalcular){
        int cantPuntos = 0;
        int resultado = 0;

        for (int i = 0 ; i<puntos.size() ; i++ ){
            vector<int> punto = puntos[i];
            if (enRango(punto)){
                if (colorACalcular == ROJO){
                    resultado += imagen[punto[0]][punto[1]].rojo;
                }else if (colorACalcular == VERDE){
                    resultado += imagen[punto[0]][punto[1]].verde;
                } else {
                    resultado += imagen[punto[0]][punto[1]].azul;
                }
                cantPuntos ++;
            }
        }
        return resultado/cantPuntos;
    }

    void hacerAzul(int i,int j,vector<vector<Pixel> > imagen, color colorACalcular){
        if (colorACalcular == ROJO){
            imagen[i][j].rojo = funcionLineal(i,j,{{i+1,j-1},{i-1,j-1},{i-1,j+1},{i+1,j+1}},imagen,ROJO);
        }else{ //Es verde el color a calcular
            imagen[i][j].verde = funcionLineal(i,j,{{i+1,j},{i,j-1},{i-1,j},{i,j+1}},imagen,VERDE);
        }
    }

    void hacerRojo(int i,int j,vector<vector<Pixel> > imagen, color colorACalcular){
        if (colorACalcular == AZUL){
            imagen[i][j].azul = funcionLineal(i,j,{{i+1,j-1},{i-1,j-1},{i-1,j+1},{i+1,j+1}},imagen,AZUL);
        }else{ //Es verde el color a calcular
            imagen[i][j].verde = funcionLineal(i,j,{{i+1,j},{i,j-1},{i-1,j},{i,j+1}},imagen,VERDE);
        }
    }

    void hacerVerdePar(int i,int j,vector<vector<Pixel> > imagen, color colorACalcular){
        if (colorACalcular == ROJO){
            imagen[i][j].azul = funcionLineal(i,j,{{i-1,j},{i+1,j}},imagen,ROJO);
        }else{ //Es AZUL el color a calcular
            imagen[i][j].verde = funcionLineal(i,j,{{i,j-1},{i,j+1}},imagen,AZUL);
        }
    }

    void hacerVerdeImpar(int i,int j,vector<vector<Pixel> > imagen, color colorACalcular){
        if (colorACalcular == AZUL){
            imagen[i][j].azul = funcionLineal(i,j,{{i-1,j},{i+1,j}},imagen,AZUL);
        }else{ //Es AZUL el color a calcular
            imagen[i][j].verde = funcionLineal(i,j,{{i,j-1},{i,j+1}},imagen,ROJO);
        }
    }


    void hacer(vector<vector<Pixel> > imagen){
        int width = imagen.size();
        int height = imagen[0].size();
        cout << "Bilineal altura " << height << " ancho " << width << flush << endl;
        for(int i=0; i< height; i++) {
            for(int j=0; j< width; j++) {
                cout << i << " " << j << flush << endl;
                if (i %2 == 0 && j % 2 == 0){ //ACA HAY AZUL
                    hacerAzul(i,j,imagen,ROJO);
                    hacerAzul(i,j,imagen,VERDE);
                }else if (i %2 == 1 && j % 2 == 1){ //ACA HAY ROJO
                    hacerRojo(i,j,imagen,AZUL);
                    hacerRojo(i,j,imagen,VERDE);
                } else if ( i%2 == 0){ //ACA HAY VERDE EN FILA PAR
                    hacerVerdePar(i,j,imagen,ROJO);
                    hacerVerdePar(i,j,imagen,AZUL);
                } else { //ACA HAY VERDE EN FILA IMPAR
                    hacerVerdeImpar(i,j,imagen,ROJO);
                    hacerVerdeImpar(i,j,imagen,AZUL);
                }
            }
        }

    };
};