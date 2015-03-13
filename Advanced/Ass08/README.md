Homework 8: Texture Buffers
============================

## Daniel Morrissey

The purpose of this assignment was to explore the process of saving, using
and modifying texture buffers in an opengl context.

For my submission, I've created a **very** simple 'Paint' program.
Use the cursor and left mouse button to draw a picture!

Only uses current cursor position every frame, I don't do any smoothing.	

## To Build/Run

	make all
	./main

## Controls

	- Click Mouse and Drag to Draw
	- 'c' to change mouse color from R, G and B
	- 'r' resets the picture
	
## Notes

Total Time: 5 or 6 hours. I fought a bug for the longest time, where the 
display buffer would clear, despite the texture being saved. If I don't 
first draw and empty frame and save that, strange things happen with the
saved texture.
