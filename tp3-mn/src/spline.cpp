#ifndef Spline_H
#define Spline_H

#include "bilineal.cpp"
#include <cmath>

using namespace std;

class Spline {
public:
    Spline(){}

    int getByDirection(int i, int j, vector<vector<Pixel > >& imagen, int direccion){
    	if (direccion == 0){
			return imagen[i][j].verde;
    	}else{
			return imagen[j][i].verde;
    	}
    }

    void resolverDireccion(int j, int from, int to, vector<vector<Pixel > >& imagen, int direccion){ //0 es horizontal, 1 es vertical
    	int width = imagen.size();
    		
		vector<int> alphas = vector<int>(width);
		vector<int> ls = vector<int>(width);
		vector<int> us = vector<int>(width);
		vector<int> zs = vector<int>(width);

		vector<int> cs = vector<int>(width);
		vector<int> bs = vector<int>(width);
		vector<int> ds = vector<int>(width);

		ls[0] = 1;
		us[0] = 0;
		zs[0] = 0;

		for (int i = to ; i <= from ; i+=2){ //Por cada azul sin incluir el primero
			int alpha_i = (3/2)*(getByDirection(i+1,j,imagen,direccion) - getByDirection(i-1,j,imagen,direccion)); //Depende del verde de la izquierda y el de la derecha
			alphas[i] = alpha_i;

			int ls_i = 4 - 2*us[i-2];
			ls[i] = ls_i;
			us[i] = 2/ls_i;
			zs[i] = (alpha_i - 2*zs[i-2]);
		}

		ls[to] = 1;
		zs[to] = 0;
		cs[to] = 0;

		for (int k = to-2 ; k >= from ; k-=2){ //k==i pero al reves
			cs[k] = zs[k] - us[k]*cs[k+2];
			bs[k] = (getByDirection(k+1,j,imagen,direccion) - getByDirection(k-1,j,imagen,direccion))/2 - 2*(cs[k+2] + 2*cs[k])/3;
			ds[k] = (cs[k+2] - cs[k])/6;

			if (direccion == 0)
				coeficientes[k][j][direccion] = getByDirection(k-1,j,imagen,direccion) + bs[k] + cs[k] + ds[k];
			else
				coeficientes[j][k][direccion] = getByDirection(k-1,j,imagen,direccion) + bs[k] + cs[k] + ds[k];
			//coeficientes[k][j][0] = getByDirection(k-1,j,imagen,direccion);
			//coeficientes[k][j][2] = zs[k] - us[k]cs[k+2];
			//coeficientes[k][j][1] = (imagen[k+1][j].verde - imagen[k-1][j].verde)/2 - 2*(cs[k+2] + 2cs[k])/3;
			//coeficientes[k][j][3] = cs[k+2] - cs[k])/6;
		}
    }

    void plantearYResolverHorizontal(int j, vector<vector<Pixel > >& imagen, color colorAArmar){
    	int from,to;
    	if (colorAArmar == AZUL){
    		int width = imagen.size();

    		from = 2;
    		to = width -2;
    	}else if (colorAArmar == ROJO){
    		int width = imagen.size();

    		from = 1;
    		to = width -3;
		}
		resolverDireccion(j,from,to,imagen,0);
    }

    void plantearYResolverVertical(int j, vector<vector<Pixel > >& imagen, color colorAArmar){
    	int from,to;
    	if (colorAArmar == AZUL){
    		int height = imagen[0].size();

    		from = 2;
    		to = height -2;
    	}else if (colorAArmar == ROJO){
    		int height = imagen[0].size();

    		from = 1;
    		to = height -3;
    	}
		resolverDireccion(j,from,to,imagen,1);
	}

    void hacer(vector<vector<Pixel > >& imagen){
    	

		Bilineal b = Bilineal();
		b.hacer(imagen);//TODO: ver si hay que obviar los verdes

    	int width = imagen.size();
        int height = imagen[0].size();

        coeficientes.resize(width);
        for(int i=0; i< width; i++) {
        	coeficientes[i].resize(height);
        	for (int j = 0; j < height; j++) {
        		coeficientes[i][j].resize(2); 
        	}
        }

        for(int j=1; j< height-2; j++) {
        	if (j % 2 == 0)
				plantearYResolverHorizontal(j,imagen,AZUL);
			else
   				plantearYResolverHorizontal(j,imagen,ROJO);
    	}	

    	for(int i=1; i< width-2; i++) {
    		if (i % 2 == 0)
				plantearYResolverVertical(i,imagen,AZUL);
			else
   				plantearYResolverVertical(i,imagen,ROJO);
    	}	

    	for(int a=1; a< width-1; a++) {
            for(int b=1; b< height-1; b++) {
        		if (a%2 != b%2) continue; //Solo quiero los azules y rojos

        		float derivadaX = fabs(imagen[a+1][b].verde - imagen[a-1][b].verde);
        		float derivadaY = fabs(imagen[a][b+1].verde - imagen[a][b-1].verde);

        		if (derivadaX > derivadaY){
    				imagen[a][b].verde = 0.3 * coeficientes[a][b][0] + 0.7 * coeficientes[a][b][1];
        		} else {
        			imagen[a][b].verde = 0.7 * coeficientes[a][b][0] + 0.3 * coeficientes[a][b][1];
        		}

				//if (fabs(imagen[a][b].verde - coeficientes[a][b][0]) < fabs(imagen[a][b].verde - coeficientes[a][b][1])){
					//imagen[a][b].verde = percentageY * coeficientes[a][b][0] + percentageX * coeficientes[a][b][1];
				//} else {
					//imagen[a][b].verde = coeficientes[a][b][1];
				//}

        	}
        }
	}

	vector<vector<vector<int > > > coeficientes;
};



#endif