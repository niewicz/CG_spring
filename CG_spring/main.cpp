#include <GL/glut.h>
#include <math.h>
#include "Image.h"

#define W_HEIGHT 800
#define W_WIDTH 800

#define N_SLICES (GLint)50
#define N_STACKS (GLint)50
#define N_SPIRALS 4
#define M_PI 3.141592653589793238463

#define RADIUS_SPRING (GLfloat)0.01
#define RADIUS_BALL (GLfloat)0.1

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
	GLfloat x;
	GLfloat z;
	GLfloat i;

	for(i = 1.0f; i >= 0.95f; i -= RADIUS_SPRING)
		DrawSphere(0.0f, i, 0.1f, textureSteel, quad, RADIUS_SPRING, N_SLICES, N_STACKS);

	GLfloat y = 0.94f;
	for (float ii = 0.0f; ii <= 2.0f * M_PI * N_SPIRALS; ii += 3*RADIUS_SPRING)
	{
		x = (GLfloat)sin(ii) / 10;
		z = (GLfloat)cos(ii) / 10;
		DrawSphere(x, y, z, textureSteel, quad, RADIUS_SPRING, N_SLICES, N_STACKS);
		y -= RADIUS_SPRING/10;
	}

	for (i = 0.1f; i >= 0.0f; i -= RADIUS_SPRING)
		DrawSphere(x, y - i, z, textureSteel, quad, RADIUS_SPRING, N_SLICES, N_STACKS);

	DrawSphere(x, y - i - 2 * RADIUS_BALL , z, textureGlass, quad, RADIUS_BALL, N_SLICES, N_STACKS);
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