#include <GL/glut.h>
#include "Image.h"

#define W_HEIGHT 800
#define W_WIDTH 800

GLUquadric *quad;
GLuint textureSteel, textureGlass;

void Timer(int value)
{

}

void InitializeScene()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)W_WIDTH / W_HEIGHT, 0.001f, 4.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);

	quad = gluNewQuadric();

	Image *imageSteel = LoadBMP("steel.bmp");
	textureSteel = LoadTexture(imageSteel);
	delete imageSteel;

	Image *imageGlass = LoadBMP("glass.bmp");
	textureGlass = LoadTexture(imageGlass);
	delete imageGlass;
}

void DrawSphere(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z, GLuint texture, GLUquadric *quad, GLfloat radius, GLint slices, GLint stacks)
{
	glTranslatef(pos_x, pos_y, pos_z);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, texture);
		gluQuadricTexture(quad, 1);
		gluSphere(quad, radius, slices, stacks);
	glTranslatef(-pos_x, -pos_y, -pos_z);
}

void RenderScene()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	DrawSphere(0.0f, 0.0f , 0.0f, textureGlass, quad, 1.0f, 50, 50);
	glFlush();

	glutSwapBuffers();
}

void RenderOnMotion(int x, int y)
{

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Spring");

	InitializeScene();

	glutDisplayFunc(RenderScene);
	glutMotionFunc(RenderOnMotion);
	Timer(0);
	glutMainLoop();

	return 0;
}