#include "Buffer.h"
#include <glad/glad.h>
#include "Sources/KingdomEngine.h"

/////////////////////////////////////////////////////////////////////////////
// VertexBuffer /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

VertexBuffer::VertexBuffer(uint32_t size)
{

	glCreateBuffers(1, &m_RendererID);//opengl 4.5
	//glGenBuffers(1, &m_RendererID);

	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

//VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
//{
//
//	glCreateBuffers(1, &m_RendererID); ////opengl 4.5
//	//glGenBuffers(1, &m_RendererID);
//	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
//	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
//
//	m_size = size;
//}
//
//VertexBuffer::VertexBuffer(glm::vec3* vertices, uint32_t size)
//{
//	glCreateBuffers(1, &m_RendererID); ////opengl 4.5
//	//glGenBuffers(1, &m_RendererID);
//	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
//	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
//
//	m_size = size;
//}

VertexBuffer::VertexBuffer(void* vertices, uint32_t size, bool dynamic)
{
	glCreateBuffers(1, &m_RendererID); ////opengl 4.5
	//glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	if (dynamic)
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	m_size = size;
}



VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, uint32_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


/////////////////////////////////////////////////////////////////////////////
// IndexBuffer //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count)
{
	glCreateBuffers(1, &m_RendererID); //opengl 4.5
	//glGenBuffers(1, &m_RendererID); //opengl 3.3
	// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
	// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

