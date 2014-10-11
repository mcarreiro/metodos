#!/bin/bash
g++ main.cpp

echo Test google 0.1
time ./a.out tests/web-Google-c.in a 1 > tests/normas/web-Google-c1
echo Test google 0.2
time ./a.out tests/web-Google-c.in a 2 > tests/normas/web-Google-c2
echo Test google 0.3
time ./a.out tests/web-Google-c.in a 3 > tests/normas/web-Google-c3
echo Test google 0.4
time ./a.out tests/web-Google-c.in a 4 > tests/normas/web-Google-c4
echo Test google 0.5
time ./a.out tests/web-Google-c.in a 5 > tests/normas/web-Google-c5
echo Test google 0.6
time ./a.out tests/web-Google-c.in a 6 > tests/normas/web-Google-c6
echo Test google 0.7
time ./a.out tests/web-Google-c.in a 7 > tests/normas/web-Google-c7
echo Test google 0.8
time ./a.out tests/web-Google-c.in a 8 > tests/normas/web-Google-c8
echo Test google 0.9
time ./a.out tests/web-Google-c.in a 9 > tests/normas/web-Google-c9
