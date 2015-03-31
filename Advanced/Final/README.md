CSCI 4239 Final Project
=======================
## Daniel Morrissey

### Overview

The goal of my project was to create a game and rendering engine in the 
style of the video game Minecraft.

### The World

### Interacting With the World

### Rendering Details

The majority of the work on this project came from creating the rendering engine,
as well as engineering how to format and pass data to and from the engines.

#### Geometry

**Research Here**

If we could only pass the block coordinate to the shaders, and build our 
geo in a shader, things would be gravy.

#### Shaders

I am choosing to target opengl 3.x+ style shaders. Object buffers ftw.

Create a variable number of shaders for viewing the world.
	- Phong, Ray-traced, etc.
	- "Special" Shaders for showing details about the world
		- "Depth" Shader
		- "Height" Shader
		- "Distance Shader
		
