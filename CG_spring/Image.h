#define _CRT_SECURE_NO_DEPRECATE // for fopem
#include <fstream>
#include <iostream>
#include <GL/glut.h>

class Image
{
public:
	Image(int w, int h, unsigned char *data);
	~Image();

	int width;
	int height;
	unsigned char *data;
};

Image* LoadBMP(const char *path);
GLuint LoadTexture(Image *image);
