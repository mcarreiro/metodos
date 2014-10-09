#!/bin/bash
g++ main.cpp

echo Test google 0.1
./a.out tests/web-Google-c.in a 1 >> tests/normas/web-Google-c10
echo Test google 0.2
./a.out tests/web-Google-c.in a 2 >> tests/normas/web-Google-c20
echo Test google 0.3
./a.out tests/web-Google-c.in a 3 >> tests/normas/web-Google-c30
echo Test google 0.4
./a.out tests/web-Google-c.in a 4 >> tests/normas/web-Google-c40
echo Test google 0.5
./a.out tests/web-Google-c.in a 5 >> tests/normas/web-Google-c50
echo Test google 0.6
./a.out tests/web-Google-c.in a 6 >> tests/normas/web-Google-c60
echo Test google 0.7
./a.out tests/web-Google-c.in a 7 >> tests/normas/web-Google-c70
echo Test google 0.8
./a.out tests/web-Google-c.in a 8 >> tests/normas/web-Google-c80
echo Test google 0.9
./a.out tests/web-Google-c.in a 9 >> tests/normas/web-Google-c90
