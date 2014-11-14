import math, operator
from PIL import Image

def compare(file1, file2):
	image1 = Image.open(file1)
	image2 = Image.open(file2)
	pix1 = image1.load()
	pix2 = image2.load()
	width, height = image1.size

	total = 0
	for i in xrange(2,width-2):
		for j in xrange(2,height-2):
			verde1  = int(pix1[i,j][1])
			verde2  = int(pix2[i,j][1])
			value = (verde1 - verde2) ** 2

			total += value
	mse = total/((width-4)*(height-4))

	result = 20 * math.log10(255) - 10 * math.log10(mse)

	print (file2+ ' ' + str(result))

if __name__=='__main__':
	import sys
	file1, file2 = sys.argv[1:]
	compare(file1, file2)
