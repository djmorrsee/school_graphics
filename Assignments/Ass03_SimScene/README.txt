Use make simscene to build

Use the arrow keys to adjust the angle of view.

Each face is properly culled. 

The room is built by hand, the three boxes are built with a helper function.

Twice the boxes are placed using the helper function, with the third being placed at the origin and moved via glTranslate. 

The assignment took around 3 hours

RESUBMISSION NOTES

Added a cylindrical primitive to the scene. The pole will act as a lamp once we get to lighting. The number of vertices around the circumference of the cylinder can be adjusted:

	+ or = increases the amount of vertices in the pole
	
	- decreases the amount of vertices in the pole

