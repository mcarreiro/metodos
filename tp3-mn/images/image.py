import os,sys
from PIL import Image

imageName = raw_input()
imageType = "bmp"
jpgfile = Image.open(imageName+"."+imageType)
pix = jpgfile.load()
height, width = jpgfile.size

print height,width

for i in xrange(height):
	for j in xrange(width):
		acutalTuple = pix[i,j]
		newTuple = ()
		if i % 2 == 0: # AZUL-VERDE-AZUL
			if j % 2 == 0: #AZUL
				newTuple = (0,0,acutalTuple[2])
				print acutalTuple[2]
			else: #VERDE
				newTuple = (0,acutalTuple[1],0)
				print acutalTuple[1]
		else: # VERDE-ROJO-VERDE
			if j % 2 == 0: #VERDE
				newTuple = (0,acutalTuple[1],0)
				print acutalTuple[1]
			else: #ROJO
				newTuple = (acutalTuple[0],0,0)
				print acutalTuple[0]
		pix[i,j] = newTuple

#jpgfile.show()
jpgfile.save(imageName+"_bayer."+imageType,imageType)