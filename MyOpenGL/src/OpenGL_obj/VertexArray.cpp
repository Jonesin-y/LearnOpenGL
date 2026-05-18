#include "pch.h"
#include "VertexArray.h"
#include"VertexBuffer.h"
#include"BufferLayout.h"
#include<glad/glad.h>
VertexArray::VertexArray()
	:m_RendererID(0),m_ShaderPipeID(0)
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
	UnBind();
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBufferLayout(const VertexBuffer& vb,BufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	for (const auto& element :elements)
	{
		glEnableVertexAttribArray(m_ShaderPipeID);
		glVertexAttribPointer(	m_ShaderPipeID,
								element.Count,
								element.Type,
								element.Normalized,
								layout.Stride,
				   (const void*)element.Offset
		);
		m_ShaderPipeID++;

	}
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}
