import math, operator
from PIL import Image

def compare(file1, file2, error):
    image1 = Image.open(file1)
    image2 = Image.open(file2)
    pix1 = image1.load()
    pix2 = image2.load()
    width, height = image1.size

    aciertos = 0
    errores = 0
    distancia = 0


    for i in xrange(2,width-2):
        for j in xrange(2,height-2):
            verde1  = int(pix1[i,j][1])
            verde2  = int(pix2[i,j][1])
            dis = abs(verde1 - verde2)
            if dis <= int(error):
                aciertos+=1
                dis = 0
            else:
                errores+=1

            distancia += dis

    print ("Comparacion entre las dos imagenes para el color verde con tolerancia " + str(error))
    print ("DISTANCIA:" + str(distancia))
    print ("ACIERTOS:" + str(aciertos) )
    print ("CANTIDAD:" + str(width*height))
    print ("PORCENTAJE ACIERTOS: %.10f" % (aciertos/float(width*height)))
    print ("PROMEDIO DISTANCIA: %.10f" % (distancia/float(width*height)))
    if errores > 0:
        print ("PROMEDIO DISTANCIA DE ERRORES: %.10f" % (distancia/float(errores)))


if __name__=='__main__':
    import sys
    file1, file2, error = sys.argv[1:]
    compare(file1, file2, error)