# Minecraft Graphics Project Update

## Daniel Morrissey

**To Build**

	./scons/scons.py
	
I have adopted the use of the SCONS build tool. It is python based, with no other dependencies, and included with the project.
It invokes g++ with all of the flags required for the class, and should handle all of the building and linking, as per the SConstruct and SConscript files.

If this tool is a problem, I can build a makefile system for the final submission. 
I found myself spending more time constructing the makefiles than writing graphics code, so I found a tool to alleviate that problem.

**To Run**

	./build/src/main
	
**Controls**

Click and drag, or use WSAD to rotate the cube.

## Explanation

I am building a "Minecraft" world. Currently, a 3D grid of cubes is drawn by a geometry shader.
The program sends the GPU a 3D array of vertices, 1 per block in the world.
The geometry shader then builds a cube around the point and passes the new mesh to the fragment shader.

Even in its primitive state, the shader can handle drawing **32 thousand cubes, or 1 million verts** while still maintaining 30fps on my semi-decent machine.
I feel that after implementing some face culling, that limit will go up.

## Next Steps

- Implement a "map" of sorts for determining cube types.
	- This will either be a Texture3D uniform or a simple int[] uniform
	- This will allow me to choose cube type (color,  texture, etc.), as well as skip drawing blocks
	- This will allow face culling (don't draw face if its neighbor has been drawn).
	
- Lighting and Textures
	- Simple directional lighting for the world. Normals, texture and color will be determined in the geo shader (most likely)
	- Texturing will be done with an atlas
	- The vertices passed to the vertex shader will contain the texture info.

- Motion
	- Simple fps style movment
	
- CPU Comparison
	- If time permits, I would like to implement the same algorithms for mesh building that I used in the geo shader in straight c++, and then compare the two.
	
- Chunks
	- If time permits, I would like to implement a "chunk" system, which would allow dynamically loading the world.
