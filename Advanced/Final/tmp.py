dim = 8
height = 4
def IndexFromXYZ(x, y, z):
	return z * dim * dim + y * dim + x
	
def XYZFromIndex(i):
	x = 0
	y = 0
	z = 0
	z = i / (dim * dim)
	y = (i - z * dim * dim) / dim
	x = (i - z * dim * dim - y * dim) % dim
	return (x, y, z)
	
print IndexFromXYZ(0, 0, 1);
print XYZFromIndex(64)
