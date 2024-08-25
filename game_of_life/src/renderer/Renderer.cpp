#include "Renderer.h"

#include "../graphics/Shader.h"
#include "../graphics/loaders/shader_loader.h"

GLuint Renderer::lineVAO = 0;
GLuint Renderer::lineVBO = 0;
GLuint Renderer::staticSize = 0;

GLuint Renderer::boxVAO = 0;
GLuint Renderer::boxVBO = 0;
GLuint Renderer::boxEBO = 0;

Shader* Renderer::gridShader = nullptr;
Shader* Renderer::boxShader = nullptr;

void Renderer::vertex_line_init()
{
	glBindVertexArray(lineVAO);
		glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::vertex_box_init()
{
	glBindVertexArray(boxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxEBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void Renderer::initialize()
{
	gridShader = load_shader("res/shaders/v_grid_shader.glsl", "res/shaders/f_shader.glsl");
	if (gridShader == nullptr) {
		throw "Failed to load grid shader";
	}
	boxShader = load_shader("res/shaders/v_box_shader.glsl", "res/shaders/f_shader.glsl");
	if (boxShader == nullptr) {
		throw "Failed to load box shader";
	}

	glGenVertexArrays(1, &lineVAO);
	glGenBuffers(1, &lineVBO);

	glGenVertexArrays(1, &boxVAO);
	glGenBuffers(1, &boxVBO);
	glGenBuffers(1, &boxEBO);

	vertex_line_init();
	vertex_box_init();
}

void Renderer::terminate()
{
	glDeleteVertexArrays(1, &lineVAO);
	glDeleteBuffers(1, &lineVBO);

	glDeleteVertexArrays(1, &boxVAO);
	glDeleteBuffers(1, &boxVBO);
	glDeleteBuffers(1, &boxEBO);
}

void Renderer::fillStaticBuffer(GLuint size, GLfloat* vertices)
{
	glBindVertexArray(lineVAO);
		glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	staticSize = size;
}

void Renderer::renderLines()
{
	gridShader->use();
	glBindVertexArray(lineVAO);
		glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_LINES, 0, staticSize);
	glBindVertexArray(0);
}

void Renderer::renderBoxes(GLuint count, GLfloat* vertices, GLuint* indices)
{
	boxShader->use();
	glBindVertexArray(boxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
		glBufferData(GL_ARRAY_BUFFER, (static_cast<GLsizeiptr>(count) * 8 * sizeof(GLfloat)), vertices, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (static_cast<GLsizeiptr>(count) * 6 * sizeof(GLuint)), indices, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, (count * 6), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
