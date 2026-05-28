#include "pch.h"
#include "Buffer.h"
#include<glad/glad.h>

unsigned int ShaderDataTypeSize(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Float1: return 4;
	case ShaderType::Float2:return 4 * 2;
	case ShaderType::Float3:return 4 * 3;
	case ShaderType::Float4:return 4 * 4;
	case ShaderType::Mat3:return 3 * 3 * 4;
	case ShaderType::Mat4:return 4 * 4 * 4;
	case ShaderType::Int1:return 4;
	case ShaderType::Int2:return 4 * 2;
	case ShaderType::Int3:return 4 * 3;
	case ShaderType::Int4:return 4 * 4;
	}
	std::cout << "Invalid Type!" << std::endl;
	__debugbreak();
	return 0;
}

unsigned int ShaderDataTypeCount(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Float1: return		1;
	case ShaderType::Float2:return		2;
	case ShaderType::Float3:return		3;
	case ShaderType::Float4:return		4;
	case ShaderType::Mat3:return		3 * 3;
	case ShaderType::Mat4:return		4 * 4;
	case ShaderType::Int1:return		1;
	case ShaderType::Int2:return		2;
	case ShaderType::Int3:return		3;
	case ShaderType::Int4:return		4;
	}
	std::cout << "Invalid Type!" << std::endl;
	__debugbreak();
	return 0;

}

unsigned int SwitchShaderTypeToGladType(ShaderType type)
{
	switch (type)
	{
	case ShaderType::Float1: return GL_FLOAT;
	case ShaderType::Float2:return GL_FLOAT;
	case ShaderType::Float3:return GL_FLOAT;
	case ShaderType::Float4:return GL_FLOAT;
	case ShaderType::Mat3:return GL_FLOAT;
	case ShaderType::Mat4:return GL_FLOAT;
	case ShaderType::Int1:return GL_INT;
	case ShaderType::Int2:return GL_INT;
	case ShaderType::Int3:return GL_INT;
	case ShaderType::Int4:return GL_INT;
	}
	std::cout << "Invalid Type!" << std::endl;
	__debugbreak();
	return 0;
}


//-------------BufferElement----------------//

BufferElement::BufferElement(ShaderType type, const std::string& name, bool normalized)
	:Name(name), Type(type), Count(ShaderDataTypeCount(type)),Size(ShaderDataTypeSize(type)), Normalized(normalized), Offset(0)
{
	std::cout << Size << std::endl;
}
//-------------BufferLayout----------------//

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& Elements):
	m_Elements(Elements)
{
	CaculateLayout();
}

BufferLayout::BufferLayout()
{

}
BufferLayout::~BufferLayout()
{

}
void BufferLayout::CaculateLayout()
{
	unsigned int offset = 0;
	m_Stride = 0;
	for (auto& element : m_Elements)
	{
		element.Offset = offset;
		m_Stride += element.Size;
		offset += element.Size;
	}
}


//-------------VertexBuffer----------------//

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertexs)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(Vertex), vertexs.data(), GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

inline ::std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, unsigned int count) 
{
	return std::make_shared<VertexBuffer>(data, count); 
}

inline ::std::shared_ptr<VertexBuffer> VertexBuffer::Create(const std::vector<Vertex>& vertexs) 
{
	return std::make_shared<VertexBuffer>(vertexs); 
}

//-------------IndexBuffer----------------//
IndexBuffer::IndexBuffer(const void* data, unsigned int count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

inline ::std::shared_ptr<IndexBuffer> IndexBuffer::Create(const void* data, unsigned int count) 
{
	return std::make_shared<IndexBuffer>(data, count); 
}

::std::shared_ptr<IndexBuffer> IndexBuffer::Create(const std::vector<unsigned int> indices)
{
	auto result = std::make_shared<IndexBuffer>(indices);
	result->SetCount(indices.size());
	return result;
}

UniformBuffer::UniformBuffer(unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, UniformBuffer::m_BindingPoint, m_RendererID);
	UniformBuffer::m_BindingPoint++;
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
void UniformBuffer::Submit(const void* data, unsigned int offset, unsigned int size)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
}

void UniformBuffer::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
