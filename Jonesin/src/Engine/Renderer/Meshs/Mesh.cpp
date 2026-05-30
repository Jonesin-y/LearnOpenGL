#include "pch.h"
#include "Mesh.h"
#include"Buffer.h"
#include"VertexArray.h"


Mesh::Mesh(const std::vector<Vertex>& vertexs, const std::vector<unsigned int>& indices)
	:m_Vertexs(vertexs),m_Indices(indices)
{
	m_VertexArray = std::make_shared<VertexArray>();
	m_VertexArray->Bind();
	BufferLayout layout{
		{ShaderType::Float3,"a_Position",GL_FALSE},
		{ShaderType::Float3,"a_Normal",GL_FALSE},
		{ShaderType::Float2,"a_TexCoord",GL_FALSE}
	};
	auto vb =std::make_shared<VertexBuffer>(vertexs);
	auto ib = std::make_shared<IndexBuffer>(indices);
	vb->SetBufferLayout(layout);
	m_VertexArray->AddVertexBuffer(vb);
	m_VertexArray->SetIndexBuffer(ib);

}

void Mesh::Bind()
{
	m_VertexArray->Bind();
}

