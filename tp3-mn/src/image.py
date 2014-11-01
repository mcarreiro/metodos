from __future__ import print_function
import os,sys
from PIL import Image
from subprocess import call

print ("Nombre de archivo sin extension")

imageName = raw_input()
imageType = "bmp"
jpgfile = Image.open("../images/"+imageName+"."+imageType)
pix = jpgfile.load()
height, width = jpgfile.size

f = open(imageName+".txt",'w')
print (str(height)+" "+str(width), file=f)

print ("PYTHON: altura: "+str(height)+ " ancho: "+str(width))

for i in xrange(height):
	for j in xrange(width):
		acutalTuple = pix[i,j]
		newTuple = ()
		if i % 2 == 0: # AZUL-VERDE-AZUL
			if j % 2 == 0: #AZUL
				newTuple = (0,0,acutalTuple[2])
				print (acutalTuple[2], file=f)
			else: #VERDE
				newTuple = (0,acutalTuple[1],0)
				print (acutalTuple[1], file=f)
		else: # VERDE-ROJO-VERDE
			if j % 2 == 0: #VERDE
				newTuple = (0,acutalTuple[1],0)
				print (acutalTuple[1], file=f)
			else: #ROJO
				newTuple = (acutalTuple[0],0,0)
				print (acutalTuple[0], file=f)
		pix[i,j] = newTuple

#jpgfile.show()
jpgfile.save(imageName+"_bayer."+imageType,imageType)
f.close()

#call(["g++", "main.cpp -std=gnu++11"])
call(["./metodos", imageName+".txt"])