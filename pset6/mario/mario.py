from cs50 import get_int

def main():

    #Get pyramid's dimentions
	pyramidH = get_int("Pyrammid Height: ")


	x = 0
	y = pyramidH

    #Display Pyramid
	while True:
		spacer(y + 1)
		printer(x)
		print(" ", end="")
		printer(x)
		x += 1
		y -= 1
		print("")
		if x > pyramidH + 1:
		    break

#Print a set amount of ' '
def spacer(n):
	for x in range(n):
		print(" ", end="")

#Print a set amount of '#'
def printer(n):
	for x in range(n):
		print("#", end="")

main()
