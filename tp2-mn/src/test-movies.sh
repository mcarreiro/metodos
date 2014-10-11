#!/bin/bash
g++ main.cpp

echo Test Movies 0.1
time ./a.out tests/movies-10.in a > tests/normas/movies-10
echo Test Movies 0.2
time ./a.out tests/movies-20.in a > tests/normas/movies-20
echo Test Movies 0.3
time ./a.out tests/movies-30.in a > tests/normas/movies-30
echo Test Movies 0.4
time ./a.out tests/movies-40.in a > tests/normas/movies-40
echo Test Movies 0.5
time ./a.out tests/movies-50.in a > tests/normas/movies-50
echo Test Movies 0.6
time ./a.out tests/movies-60.in a > tests/normas/movies-60
echo Test Movies 0.7
time ./a.out tests/movies-70.in a > tests/normas/movies-70
echo Test Movies 0.8
time ./a.out tests/movies-80.in a > tests/normas/movies-80
echo Test Movies 0.9
time ./a.out tests/movies-90.in a > tests/normas/movies-90
