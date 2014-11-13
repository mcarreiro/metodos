from __future__ import print_function
import os,sys
from PIL import Image
#print ("MAS ANCHO QUE ALTO")
#print ("REAL ancho 768 altura 512")
#print ("Nombre de archivo sin extension")
imageName, metodo = sys.argv[1:]
metodos = {'vecino':1,'quality':3,'bilineal':2,'spline':4}

#imageName = raw_input()
imageType = "bmp"
jpgfile = Image.open("../images/"+imageName+"."+imageType)
pix = jpgfile.load()
width, height = jpgfile.size

#print ("Nombre del metodo (opciones: "+str(metodos.keys())+") si no pones nada corre todos")
#metodo = raw_input()

f = open(imageName+".txt",'w')
print (str(height)+" "+str(width), file=f)

#print ("PYTHON: altura: "+str(height)+ " ancho: "+str(width))

for i in xrange(width):
	for j in xrange(height):
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

os.system("g++ -o metodos main.cpp -std=gnu++0x")
os.system("g++ -o metodos main.cpp -std=gnu++0x")
os.system("g++ -o metodos main.cpp -std=gnu++0x")

def dibujar(i,key_method):
	print (" ")
	os.system("./metodos "+imageName+".txt "+imageName+"_out.txt "+str(i))

	newFile = open(imageName+"_out.txt",'r')

	newImg = Image.new( 'RGB', (width,height))
	newPixels = newImg.load() # create the pixel map

	for line in newFile:
		pixelArray = line.rstrip().split(" ")
		newPixels[int(pixelArray[0]),int(pixelArray[1])] = (int(pixelArray[2]),int(pixelArray[3]),int(pixelArray[4]))
		
	#newImg.show()
	newImg.save(imageName+"_demosicing_"+key_method+"."+imageType,imageType)


if metodo == 't':
	for key in metodos:
		dibujar(metodos[key],key)
else:
	dibujar(metodos[metodo],metodo)













