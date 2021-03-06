#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer() 
{
}

VertexBuffer::VertexBuffer(const void * d, unsigned int s) : data(d), size(s)
{
	GLCall(glGenBuffers(1, &m_RenderID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, s, d, GL_DYNAMIC_DRAW));
}

void VertexBuffer::Upload(unsigned int offset, unsigned int s){
        if(s == 0)
          s = size;
        Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, s, data));
}


VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RenderID));
}

void VertexBuffer::Bind() const 
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}
