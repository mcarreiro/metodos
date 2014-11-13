#!/bin/bash

for (( i=100; i<=2500; i=i+100 ))
do
	#python image_random.py $i $i ../images/test_$i
	T="$(($(date +'%s')))"
	python image.py test_$i quality
	T="$(($(date +'%s')-T))"
	echo "$i ${T}"
done
