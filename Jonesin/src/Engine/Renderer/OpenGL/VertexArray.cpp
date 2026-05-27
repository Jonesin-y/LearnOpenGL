#include "pch.h"
#include"Core.h"
#include "VertexArray.h"
#include"Buffer.h"
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

void VertexArray::AddVertexBuffer(const Ref(VertexBuffer)& vb)
{
	Bind();
	vb->Bind();
	const auto& BufferLayout = vb->GetBufferLayout();
	auto& elements = BufferLayout.GetElements();
	for (const auto& element :elements)
	{
		glEnableVertexAttribArray(m_ShaderPipeID);
		glVertexAttribPointer(	m_ShaderPipeID,
								element.Count,
								SwitchShaderTypeToGladType(element.Type),
								element.Normalized,
								BufferLayout.GetStride(),
				   (const void*)(intptr_t)element.Offset
		);
		m_ShaderPipeID++;

	}
	m_VertexBuffers.push_back(vb);
}

void VertexArray::SetIndexBuffer(const Ref(IndexBuffer)& ib)
{
	m_IndexBuffer = ib;
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}
