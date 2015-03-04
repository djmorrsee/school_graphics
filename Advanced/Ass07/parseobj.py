import sys, os, ntpath

def path_leaf(path):
	head, tail = ntpath.split(path)
	return tail or ntpath.basename(head)

def parse_obj(filename):
	f = open(filename, 'r')

	name = os.path.splitext(filename)[0]

	if not os.path.exists(name + '/'):
		os.makedirs(name + '/')
	
	xyz_file = open(name + '/' + 'xyz', 'w')
	rgb_file = open(name + '/' +  'rgb', 'w')
	tc_file = open(name + '/' + 'tc', 'w')
	norm_file = open(name + '/'  + 'norm', 'w')

	xyz_file.write('const float ' + path_leaf(name) + '_xyz[] = {')
	rgb_file.write('const float ' + path_leaf(name) + '_rgb[] = {')
	tc_file.write('const float ' + path_leaf(name) + '_tc[] = {')
	norm_file.write('const float ' + path_leaf(name) + '_norm[] = {')

	txyz = []
	trgb = []
	ttc = []
	tnorm = []

	acc = 0
	for line in f:
		if line[:2] == 'v ':
			vals = line.split(' ')
			txyz.append((float(vals[1]), float(vals[2]), float(vals[3])))
		elif line[:3] == 'vt ':
			vals = line.split(' ')
			ttc.append((float(vals[1]), float(vals[2])))
		elif line[:3] == 'vn ':
			vals = line.split(' ')
			tnorm.append((float(vals[1]), float(vals[2]), float(vals[3])))
		elif line[:2] == 'f ':
			vals = line.split(' ')
			for i in vals[1:]:
				acc += 1

				idxs = i.split('/')
				
				x = txyz[int(idxs[0])-1][0]
				y = txyz[int(idxs[0])-1][1]
				z = txyz[int(idxs[0])-1][2]

				r = 1.0
				g = 1.0
				b = 1.0
				
				u = ttc[int(idxs[1])-1][0]
				v = ttc[int(idxs[1])-1][1]
			
				nx = tnorm[int(idxs[2])-1][0]
				ny = tnorm[int(idxs[2])-1][1]
				nz = tnorm[int(idxs[2])-1][2]

				xyz_file.write(str(x) + ', ' + str(y) + ', ' + str(z) + ', 1.0, ')
				rgb_file.write(str(r) + ', ' + str(g) + ', ' + str(b) + ', ')
				tc_file.write(str(u) + ', ' + str(v) + ', ')
				norm_file.write(str(nx) + ', ' + str(ny) + ', ' + str(nz) + ', ')
	
	xyz_file.seek(-2, 1)
	rgb_file.seek(-2, 1)
	tc_file.seek(-2, 1)
	norm_file.seek(-2, 1)
	
	xyz_file.write('};')
	rgb_file.write('};')
	tc_file.write('};')
	norm_file.write('};')
		
	xyz_file.close()
	rgb_file.close()
	tc_file.close()
	norm_file.close()
	
	return acc


def main():
	f = sys.argv[1]
	print parse_obj(f)


if __name__ == '__main__':
	main()
