#pragma once

#include <GL/glew.h>


class Shader;

class Renderer
{
public:

	static GLuint lineVAO;
	static GLuint lineVBO;
	static GLuint staticSize;

	static GLuint boxVAO;
	static GLuint boxVBO;
	static GLuint boxEBO;

	static Shader* gridShader;
	static Shader* boxShader;

	static void vertex_line_init();
	static void vertex_box_init();

public:

	static void initialize();
	static void terminate();
	static void fillStaticBuffer(GLuint size, GLfloat* vertices);
	static void renderLines();
	static void renderBoxes(GLuint count, GLfloat* vertices, GLuint* indices);

};

