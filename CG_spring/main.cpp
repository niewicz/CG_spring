#include <GL/glut.h>

#define W_HEIGHT 800
#define W_WIDTH 800
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
}

void RenderScene()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
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