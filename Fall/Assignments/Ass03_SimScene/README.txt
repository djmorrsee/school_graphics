To Build: 'make simscene'

The scene is inspired by the "render test" scenes you see for some 3d rendering packages. 

Use the arrow keys to adjust the angle of view.

Each face is properly culled. 

The room is built by hand, the three boxes are built with a helper function.

Twice the boxes are placed using the helper function, with the third being placed at the origin and moved via glTranslate. 

The assignment took around 3 hours

**RESUBMISSION NOTES**

I reworked a lot of how the scene was drawn; Namely introducing my own vertex struct and a drawVert routine to generically handle drawing all meshes.

I want to eventually use drawArrays() or drawElements()

Added a cylindrical primitive to the scene. The pole will act as a lamp once we get to lighting. The number of vertices around the circumference of the cylinder can be adjusted:

	+ or = increases the amount of vertices in the pole
	
	- decreases the amount of vertices in the pole


The cylinder is created by 2 function calls to a custom drawCricle method, and then connected via a custom drawBody method.

The cylinder is created at origin and moved via glTranslate in the drawCylinder function.
