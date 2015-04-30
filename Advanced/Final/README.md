# Mini Minecraft: Advanced Graphics Final Project

## Daniel Morrissey

I use the scons build tool for this project. It is included in this directory.

	To Build: python ./scons/scons.py
	To Run: ./build/src/main
	
**Controls**
	
	Arrow Keys or WSAD or Mouse Click/Drag: Rotates the viewport
	c/C: Cycles the scene which is drawn

## Abstract

The purpose of my project was to explore efficient drawing of a large number of primitives. The inspiration for this project is the game 'Minecraft' which, at the core, puts the player in a world full of only cubes. The cool thing about Minecraft is that at any given time, millions of cubes could be drawn at a time (machine response not included).

My aim was to use a geometry shader to handle the construction of my meshes. The goal was to pass as little data to the GPU as possible to still get the world drawn. This desire comes from my background in video game programming, where data storage and handling is usually done very differently than in GL programs. I hoped to gain a deeper understanding of some pieces of game programming that are typically abstrated away at the level I program at.

## How Its Done

I use the concept of "chunks" which is just a 8x8x4 array of positions in space (vec3's, 1 per block).

These vec3's are what is passed to the shaders. The vertex shader simply passes it through.

The geometry shader is where most of the work is done. It takes the single vert in space and draws 6 faces around it, to make a cube. A culling process is also done, so that a cube wont draw a face if it would be facing its neighbor.

The geometry shader also takes in a uniform array of integer IDs. This is where my implementation could either be called clever or hacky.

The vec3's in which the geometry shader draws the cubes consist of only whole numbers. These xyz components are then used to index the uniform array of IDs in order to determine which texture each individual cube should draw. This requires chunks to have a fixed size, as the algorithm to do all of this is as follows:

	this_block_id = IDs[x + y * CHUNK_DIM + z * CHUNK_DIM * CHUNK_DIM]
	
With this, I can access my uniform and determine all the info I need to draw a textured cube.

## Since the Progress Report...

The major thing I implemented since the progress report was the block_id map discussed above. This allowed me to draw textured cubes instead of just hard coded colors.

### Details

#### The Scene

The scene consists of a single chunk, which can be cycled with the 'c' key. The drawn scenes are:
- Random:
	- Randomly generated blocks all along the 8x8x4 grid
- House:
	- A hollow, wooden house, with a stone floor
- Pyramid
	- A stone pyramid

#### Texture

The texture is a simple atlas, for which all the cube types sample.

#### Vert and Frag shaders

The vert and frag shaders are as minimal as they get, assigning only to gl_Position and FragColor respectively.

## What I Wish I Had More Time For

More Chunks
	
- My implementation for getting block ids meant I had to have a fixed size chunk. In order to hand draw structures, I kept this size small. In reality the geo shader can draw quite a few hundred thousand cubes before slowing down.

Motion

- Due to how the cubes are drawn in the geo shader (and potentially due to a bug I can't find) any type of motion introduces major skewing of results. As such, the stretch goal of moving around the world beyond rotation could not be met with the time constraints.

World Interaction

- Time constraints made the stretch goal of adding or removing blocks to the world unreachable.

More Blocks

- If you take a look at the atlas texture, you can see I have quite a few more blocks available than I draw in my program. Time constraits restricted me from being able to calculate the texture coordinates for all the possible types.
	
Fancy Lighting

- It wasn't the focus of this project, but I would have liked to have implemented directional lighting as well.
