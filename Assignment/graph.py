from matplotlib import pyplot

def plotGraph(x, y):
	pyplot.figure(1)
	pyplot.plot(x,y,'ro-',label='Robot motion path')
	pyplot.grid(axis='both')
	pyplot.xlabel('x coordinate')
	pyplot.ylabel('y coordinate')
	pyplot.axis([0, 1, 0, 1])
	pyplot.title('Plot of Robot Motion')
	pyplot.legend(loc=2)
	pyplot.show()
	#save("1", ext="png", close=False, verbose=True)
	
def main():
	x = []
	y = []
	with open("input.txt") as f:
		for line in f:
			coord = line.split(" ")
			x.append(float(coord[0]))
			y.append(float(coord[1]))
	plotGraph(x, y)

if __name__ == '__main__':
	main()


