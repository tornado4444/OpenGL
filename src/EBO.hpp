#pragma once

#include <gl/glew.h>

class EBO {
public:
	EBO(const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	}

	~EBO(){
		glDeleteBuffers(1, &ID);
	}

public:
	virtual void Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	virtual void UnBind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void speed() {
		glFlush();
	}

public:
	GLuint getID() const { return ID; }

private:
	GLuint ID;
};