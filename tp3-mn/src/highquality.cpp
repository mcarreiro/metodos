#include "pixel.cpp"
#include <vector>

typedef unsigned int nat;

using namespace std;

class HighQuality{

public:
    HighQuality(){};

    void hacer(vector<vector<Pixel > >& imagen){

        Bilineal bilineal = Bilineal();
        bilineal.hacer(imagen);
        
        double correccion, correccionRojo, correccionAzul, correccionVerde;

        int width = imagen.size();
        int height = imagen[0].size();
        for(int i=2; i< width-2; i++) {
            for(int j=2; j< height-2; j++) {
                //i COLUMNA
                //j FILA
                correccion = correccionRojo = correccionVerde = correccionAzul =  0;
                if (i %2 == 0 && j % 2 == 0){ //ACA HAY AZUL
                  
                    correccion -= imagen[i][j-2].azul;
                    correccion -= imagen[i-2][j].azul;
                    correccion -= imagen[i][j+2].azul;
                    correccion -= imagen[i+2][j].azul;
                    correccion = imagen[i][j].azul + correccion/4;
                    imagen[i][j].verde += 0.25 * correccion;
                    //imagen[i][j].rojo += 0.75 * correccion;
                
                }else if (i %2 == 1 && j % 2 == 1){ //ACA HAY ROJO
                
                    correccion -= imagen[i][j-2].rojo;
                    correccion -= imagen[i-2][j].rojo;
                    correccion -= imagen[i][j+2].rojo;
                    correccion -= imagen[i+2][j].rojo;
                    correccion = imagen[i][j].rojo + correccion/4;
                    imagen[i][j].verde += 0.5 * correccion;
                    //imagen[i][j].azul += 0.5 * correccion;


                } else { //ACA HAY VERDE
                    correccion -= imagen[i+1][j+1].verde;
                    correccion -= imagen[i-1][j+1].verde;                    
                    correccion -= imagen[i-1][j-1].verde;
                    correccion -= imagen[i+1][j-1].verde;

                    correccionRojo = correccionAzul = correccion;
                    
                    correccionRojo += imagen[i][j-2].verde/2;
                    correccionRojo -= imagen[i-2][j].verde;
                    correccionRojo += imagen[i][j+2].verde/2;
                    correccionRojo -= imagen[i+2][j].verde;

                    correccionAzul -= imagen[i][j-2].verde;
                    correccionAzul += imagen[i-2][j].verde/2;
                    correccionAzul -= imagen[i][j+2].verde;
                    correccionAzul += imagen[i+2][j].verde/2;

                    if(j %2 ==0){
                        correccionAzul += correccionRojo;
                        correccionRojo = correccionAzul - correccionRojo;
                        correccionAzul -= correccionRojo;
                    }

                    //imagen[i][j].rojo += (imagen[i][j].verde + correccionRojo/8) * 5/8;
                    //imagen[i][j].azul += (imagen[i][j].verde + correccionAzul/8) * 5/8;
                    
                } 
                //cout << "VERDE: " << imagen[i][j].verde << endl;
                //cout << "ROJO: " << imagen[i][j].rojo << endl;
                //cout << "AZUL: " << imagen[i][j].azul << endl;

                
                if(imagen[i][j].verde > 255) imagen[i][j].verde = 255;
                if(imagen[i][j].rojo > 255) imagen[i][j].rojo = 255;
                if(imagen[i][j].azul > 255) imagen[i][j].azul = 255;


                if(imagen[i][j].verde== 255 && imagen[i][j].rojo < 70 && imagen[i][j].azul < 70)
                    imagen[i][j].verde = 0;
            }
        }

    };

};