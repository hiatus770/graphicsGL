import random
import math

"""
Example row in GLfloat vertices[] = { ... }:
//     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f,
"""

import math
import random

# Generate vertices, normals, texture coordinates, indices, and colors for a sphere
def vertindigen():
	radius = 10.0
	rings = 500
	sectors = 500

	R = 1.0 / (rings - 1)
	S = 1.0 / (sectors - 1)

	vertices = []
	normals = []
	texcoords = []
	indices = []
	colors = []

	for r in range(rings):
		for s in range(sectors):
			y = math.sin(-math.pi / 2 + math.pi * r * R)
			x = math.cos(2 * math.pi * s * S) * math.sin(math.pi * r * R)
			z = math.sin(2 * math.pi * s * S) * math.sin(math.pi * r * R)

			vertices.append(x * radius)
			vertices.append(y * radius)
			vertices.append(z * radius)

			normals.append(x)
			normals.append(y)
			normals.append(z)

			# Texture coordinate are normalized, so that (0,0) is top-left corner of the texture image and (1,1) is bottom-right corner, i want each face of the sphere to have a the texture loaded on it, so i need to map the texture coordinates to the vertices
			u = s * (S+1)
			v = r * (R+1)
			texcoords.append(u)
			texcoords.append(v)
			texcoords.append(0)


			# Generate random color values for each vertex and round them
			colors.append(random.randint(0, 255))
			colors.append(random.randint(0, 255))
			colors.append(random.randint(0, 255))
			

			if r < rings - 1 and s < sectors - 1:
				indices.append(r * sectors + s)
				indices.append((r + 1) * sectors + s)
				indices.append((r + 1) * sectors + (s + 1))

				indices.append(r * sectors + s)
				indices.append((r + 1) * sectors + (s + 1))
				indices.append(r * sectors + (s + 1))

	# Return vertices, normals, texture coordinates, indices, and colors
	return vertices, normals, texcoords, indices, colors

def main():
	# Generate vertices, normals, texture coordinates, indices, and colors
	vertices, normals, texcoords, indices, colors = vertindigen()

	# Print vertices
	print("GLfloat vertices[] = {")
	for i in range(len(vertices) - 2):
		if i % 3 == 0:
			x = vertices[i]
			y = vertices[i + 1]
			z = vertices[i + 2]
			r = round(colors[i] / 255.0, 2)
			g = round(colors[i + 1] / 255.0, 2)
			b = round(colors[i + 2] / 255.0, 2)
			u = texcoords[i]
			v = texcoords[i + 1]
			nx = normals[i]
			ny = normals[i + 1]
			nz = normals[i + 2]
			# aadd .0 to color if missing
			if r == 0:
				r = "0.0"
			if g == 0:
				g = "0.0"
			if b == 0:
				b = "0.0"
			if u == 0:
				u = "0.0"
			if v == 0:
				v = "0.0"
			# round normals
			nx = round(nx, 2)
			ny = round(ny, 2)
			nz = round(nz, 2)
			# round vertices to 5 decimal places
			x = round(x, 5)
			y = round(y, 5)
			z = round(z, 5)
			print("\t{}f, {}f, {}f, {}f, {}f, {}f, {}f, {}f, {}f, {}f, {}f,".format(x, y, z, r, g, b, u, v, nx, ny, nz))

	print("};")

	# Print indices
	print("GLuint indices[] = {")
	for i in range(len(indices)):
		if i % 3 == 0:
			print("\t" + str(indices[i]) + ", " + str(indices[i + 1]) + ", " + str(indices[i + 2]) + ",")
	# before finishing, add 2 more triangles for the ground
	print("};")

# Call main function
main()
