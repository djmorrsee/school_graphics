#include "djgraphics.h"

void drawPoint(vert v) 
{
		// Assumes inside of a glBegin(GL_TRIANGLES)
		glTexCoord2f(v.tx, v.ty);
		glVertex3f(v.x, v.y, v.z);
}

void drawFaces(face *f, int c) 
{

	int i;
	face fa;
		
	glBegin(GL_TRIANGLES);
	for(i = 0; i < c; ++i) 
	{
		fa = f[i];
		glNormal3f(fa.nx, fa.ny, fa.nz);
		
		drawPoint(fa.a);
		drawPoint(fa.b);
		drawPoint(fa.c);
	}
	
	glEnd();
}

void drawFace(face f)
{
	glBegin(GL_TRIANGLES);
	glNormal3f(f.nx, f.ny, f.nz);
	
	drawPoint(f.a);
	drawPoint(f.b);
	drawPoint(f.c);
	
	glEnd();
}

void drawTexturedSquare(unsigned int texID, float xa, float ya)
{
	const float p = 0.5;
	vert verts[4];
	verts[0] = newVert(-p, -p, 0,	0, 0);
	verts[1] = newVert(p, p, 0, 	xa, ya);
	verts[2] = newVert(-p, p, 0, 	0, ya);
	verts[3] = newVert(p, -p, 0, 	xa, 0);
	
	face faces[2];
	faces[0] = newFace(verts[0], verts[1], verts[2]);
	faces[1] = newFace(verts[0], verts[3], verts[1]);
	
	glBindTexture(GL_TEXTURE_2D, texID);
	drawFaces(faces, 2);
}

void drawTexturedCircle(unsigned int texID, int res) 
{
	int i;
	int v0, v1, v2;	

	vert verts[res + 1];
	face faces[res];
	
	float angle, x, y, tx, ty;
	float slice = 2 * M_PI / (float)res;

	
	verts[0] = newVert(0, 0, 0, 0.5, 0.5);
	for (i = 1; i <= res; ++i) 
	{
		angle = slice * i;
		x = cos(angle);
		y = sin(angle);
		tx = x / 2 + 0.5;
		ty = y / 2 + 0.5;
		
		verts[i] = newVert(x, y, 0, tx, ty);
	}
	
	for(i = 0; i < res; ++i) 
	{
		v0 = 0;
		v1 = i + 1;
		v2 = i + 2 > res ? 1 : i + 2;
		faces[i] = newFace(verts[v0], verts[v1], verts[v2]);
	}
	
	glBindTexture(GL_TEXTURE_2D, texID);
	drawFaces(faces, res);
	
}

void drawTexturedBox(unsigned int texID, float w, float h, float l) 
{
	glPushMatrix();
	glTranslatef(0, 0, l / 2);
	glScalef(w, h, 1);
	drawTexturedSquare(texID, w, h);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, -l / 2);
	glRotatef(180, 0, 1, 0);
	glScalef(w, h, 1);
	drawTexturedSquare(texID, w, h);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(w / 2, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(l, h, 1);
	drawTexturedSquare(texID, l, h);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-w / 2, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(l, h, 1);
	drawTexturedSquare(texID, l, h);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -h / 2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(w, l, 1);
	drawTexturedSquare(texID, w, l);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, h / 2, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(w, l, 1);
	drawTexturedSquare(texID, w, l);
	glPopMatrix();
	
}

void drawTexturedRoof(unsigned int texID, float w, float h, float l) 
{
	float fh = sqrt((l/2.0) * (l/2.0) + (h * h));
	float angle = atan(2 * h / l);
	float dl = sin(angle) * fh / 2;
	
	glPushMatrix();
	glTranslatef(0, 0, dl);
	glRotatef(angle*180/M_PI, -1, 0, 0);
	glScalef(w, fh, 1);
	drawTexturedSquare(texID, w, fh);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, -dl);
	glRotatef(180-angle*180/M_PI, -1, 0, 0);
	glScalef(w, fh, 1);
	drawTexturedSquare(texID, w, fh);
	glPopMatrix();
	

	glPushMatrix();
	
	glPopMatrix();

}

//void drawBox(float w, float h, float l)
//{
	//glPushMatrix();
	//glTranslatef(0, 0, -l / 2);
	//glScalef(w, h, 1);
	//drawSquare();
	//glPopMatrix();
	
	//glPushMatrix();
	//glTranslatef(0, 0, l / 2);
	//glRotatef(180, 0, 1, 0);
	//glScalef(w, h, 1);
	//drawSquare();
	//glPopMatrix();
	
	//glPushMatrix();
	//glTranslatef(-w / 2, 0, 0);
	//glRotatef(90, 0, 1, 0);
	//glScalef(l, h, 1);
	//drawSquare();
	//glPopMatrix();
	
	//glPushMatrix();
	//glTranslatef(w / 2, 0, 0);
	//glRotatef(-90, 0, 1, 0);
	//glScalef(l, h, 1);
	//drawSquare();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0, h / 2, 0);
	//glRotatef(90, 1, 0, 0);
	//glScalef(w, l, 1);
	//drawSquare();
	//glPopMatrix();
	
	//glPushMatrix();
	//glTranslatef(0, -h / 2, 0);
	//glRotatef(-90, 1, 0, 0);
	//glScalef(w, l, 1);
	//drawSquare();
	//glPopMatrix();

//}

//void drawRoom(float w, float h, float l)
//{
	//glPushMatrix();
	//glTranslatef(0, 0, l / 2);
	//glScalef(w, h, 1);
	//drawSquare();
	//glPopMatrix();
	
	//glPushMatrix();
	//glTranslatef(0, 0, -l / 2);
	//glRotatef(180, 0, 1, 0);
	//glScalef(w, h, 1);
	//drawSquare();
	//glPopMatrix();
	
	//glPushMatrix();
	//glTranslatef(w / 2, 0, 0);
	//glRotatef(90, 0, 1, 0);
	//glScalef(l, h, 1);
	//drawSquare();
	//glPopMatrix();
	
	//glPushMatrix();
	//glTranslatef(-w / 2, 0, 0);
	//glRotatef(90, 0, -1, 0);
	//glScalef(l, h, 1);
	//drawSquare();
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0, -h / 2, 0);
	//glRotatef(90, 1, 0, 0);
	//glScalef(w, l, 1);
	//drawSquare();
	//glPopMatrix();
	
	//glPushMatrix();
	//glTranslatef(0, h / 2, 0);
	//glRotatef(90, -1, 0, 0);
	//glScalef(w, l, 1);
	//drawSquare();
	//glPopMatrix();

//}

//void drawCircle(float r, int v)
//{
	//vert verts[v + 1];
	//face faces[v];
	
	//int i;
	//float x, y, angle;
	//float slice = 2 * M_PI / (float)v;
	
	//replaceVert(&verts[0], 0, 0, 0);
	//for(i = 1; i <= v; ++i) {
		//angle = slice * i;
		//x = cos(angle) * r;
		//y = sin(angle) * r;
		
		//replaceVert(&verts[i], x, y, 0);
	//}
	
	
	//for(i = 0; i < v; ++i) 
	//{
		//int v0, v1, v2;
		//v0 = 0;
		//v1 = i + 1;
		//v2 = i + 2 > v ? 1 : i + 2;
		//replaceFace(&faces[i], verts[v0], verts[v1], verts[v2]);
	//}
	
	//drawFaces(faces, v);
	
//}

//void drawCylinderBody(float r, float h, int v)
//{
	//vert verts[v * 2];
	//face faces[v * 2];
	
	//int i;
	//float x, y, z, angle;
	//float slice = 2 * M_PI / (float)v;
	
	//for (i = 0; i < v; ++i) {
		//angle = slice * i;
		//x = cos(angle) * r;
		//y = h / 2;
		//z = sin(angle) * r;
		//replaceVert(&verts[2 * i], x, y, z);
		//replaceVert(&verts[2 * i + 1], x, -y, z);

	//}
	
	//for (i = 0; i < v; ++i) {
		//// 0, 1, 2
		//// 1, 3, 2
		
		//// 2, 3, 4
		//// 3, 5, 4
		//int idx0 = i * 2;
		//int idx1 = (idx0 + 1) % (v * 2);
		//int idx2 = (idx0 + 2) % (v * 2);
		//int idx3 = (idx0 + 3) % (v * 2);
		
		//replaceFace(&faces[i * 2], verts[idx2], verts[idx1], verts[idx0]);
		//replaceFace(&faces[i * 2 + 1], verts[idx2], verts[idx3], verts[idx1]);
	//}
	
	//drawFaces(faces, v * 2);

//}

//void drawCylinder(float r, float h, int v)
//{
	//glPushMatrix();
	//glTranslatef(0, h / 2, 0);
	//glRotatef(90, -1, 0, 0);
	//drawCircle(r, v);
	//glPopMatrix();
	
	//glPushMatrix();
	//glTranslatef(0, -h / 2, 0);
	//glRotatef(90, 1, 0, 0);
	//drawCircle(r, v);
	//glPopMatrix();
	
	//drawCylinderBody(r, h, v);
//}
//vert getMidIcoPoint(vert a, vert b) 
//{
	//vert v;
	//float midx = (a.x + b.x) / 2.0;
	//float midy = (a.y + b.y) / 2.0;
	//float midz = (a.z + b.z) / 2.0;
	//replaceVert(&v, midx, midy, midz);
	//return v;
//}

//face* refineIcoFaces(face *faces, int count, int num) 
//{
	
	//face *reFaced = malloc(sizeof(face) * 4 * count);
	
	//face f;
	//vert v0, v1, v2;

	//int i, idx;
	//for (i = 0; i < count; ++i) 
	//{
		//idx = i * 4;
		//f = faces[i];
		
		//v0 = f.a;
		//v1 = f.b;
		//v2 = f.c;
		
		
		//vert a = getMidIcoPoint(v0, v1);
		//vert b = getMidIcoPoint(v1, v2);
		//vert c = getMidIcoPoint(v2, v0);
		
		//// Make Points Unit Length
		//normalize(&a);
		//normalize(&b);
		//normalize(&c);
		//normalize(&v0);
		//normalize(&v1);
		//normalize(&v2);

		//replaceFace(&reFaced[idx], v0, a, c);
		//replaceFace(&reFaced[idx + 1], v1, b, a);
		//replaceFace(&reFaced[idx + 2], v2, c, b);
		//replaceFace(&reFaced[idx + 3], a, b, c);
		
	//}
	//if(num > 1) {
		//return refineIcoFaces(reFaced, 4 * count, num-1);
	//}
	//return reFaced;
//}

//void drawIcosphere (int dim) 
//{
	//int i, idx;
	//float t = (1.0 + sqrt(5.0)) / 2.0;
	//vert verts[12];
	//face faces[20];
	
	//replaceVert(&verts[0], -1, t, 0);
	//replaceVert(&verts[1], 1, t, 0);
	//replaceVert(&verts[2], -1, -t, 0);
	//replaceVert(&verts[3], 1, -t, 0);
	
	//replaceVert(&verts[4], 0, -1, t);
	//replaceVert(&verts[5], 0, 1, t);
	//replaceVert(&verts[6], 0, -1, -t);
	//replaceVert(&verts[7], 0, 1, -t);
	
	//replaceVert(&verts[8], t, 0, -1);
	//replaceVert(&verts[9], t, 0, 1);
	//replaceVert(&verts[10], -t, 0, -1);
	//replaceVert(&verts[11], -t, 0, 1);
	
	//for (i = 0; i < 12; ++i) {
		//normalize(&verts[i]);
	//}
	
	//// Faces
	//replaceFace(&faces[0], verts[0], verts[11], verts[5]);
	//replaceFace(&faces[1], verts[0], verts[5], verts[1]);
	//replaceFace(&faces[2], verts[0], verts[1], verts[7]);
	//replaceFace(&faces[3], verts[0], verts[7], verts[10]);
	//replaceFace(&faces[4], verts[0], verts[10], verts[11]);
	
	//replaceFace(&faces[5], verts[1], verts[5], verts[9]);
	//replaceFace(&faces[6], verts[5], verts[11], verts[4]);
	//replaceFace(&faces[7], verts[11], verts[10], verts[2]);
	//replaceFace(&faces[8], verts[10], verts[7], verts[6]);
	//replaceFace(&faces[9], verts[7], verts[1], verts[8]);
	
	//replaceFace(&faces[10], verts[3], verts[9], verts[4]);
	//replaceFace(&faces[11], verts[3], verts[4], verts[2]);
	//replaceFace(&faces[12], verts[3], verts[2], verts[6]);
	//replaceFace(&faces[13], verts[3], verts[6], verts[8]);
	//replaceFace(&faces[14], verts[3], verts[8], verts[9]);
	
	//replaceFace(&faces[15], verts[4], verts[9], verts[5]);
	//replaceFace(&faces[16], verts[2], verts[4], verts[11]);
	//replaceFace(&faces[17], verts[6], verts[2], verts[10]);
	//replaceFace(&faces[18], verts[8], verts[6], verts[7]);
	//replaceFace(&faces[19], verts[9], verts[8], verts[1]);
		
	//if(dim > 0) {	
	
		//face *refFaces = refineIcoFaces(faces, 20, dim);

		//drawFaces(refFaces, 20 * pow(4, dim));
	//} else {
		//drawFaces(faces, 20);
	//}

//}
