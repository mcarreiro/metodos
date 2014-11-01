#ifndef Pixel_H
#define Pixel_H

typedef unsigned int nat;

enum color {ROJO,VERDE,AZUL};

class Pixel {
public:
    Pixel():rojo(0),azul(0),verde(0){}

    nat rojo;
    nat azul;
    nat verde;
};

#endif