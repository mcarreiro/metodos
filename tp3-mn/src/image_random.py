import math, operator
from PIL import Image
import random

def random_img(width_x, height_x, output):

    width = int(width_x)
    height = int(height_x)
    newImg = Image.new( 'RGB', (width,height))
    newPixels = newImg.load()
   

    for i in xrange(width):
        for j in xrange(height):
            newPixels[i,j] = (random.randint(0,255),random.randint(0,255),random.randint(0,255))
    newImg.save(output+".bmp","bmp")

    

if __name__=='__main__':
    import sys
    width, height, output = sys.argv[1:]
    random_img(width, height,output)