#ifndef image_h
#define image_h

#include "GLinclude.h"
#include <iostream>

void LoadTextureFromFile(unsigned int &texture_id, const char* path, bool one)
{
	int width, height, nr_channels;
	unsigned char *data = stbi_load(path, &width, &height, &nr_channels, 0);
	if (data)
	{
		if (one) {
			glGenTextures(2, &texture_id);
		}
		glBindTexture(GL_TEXTURE_2D, texture_id);   /* 2d texture (x and y size)*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* ��ͼ���������ʱ��������*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* ��ͼ��С������ʱ��������*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	}
	else
	{
		std::cout << "��������ʧ��" << std::endl;
	}
	stbi_image_free(data);
}
#endif
