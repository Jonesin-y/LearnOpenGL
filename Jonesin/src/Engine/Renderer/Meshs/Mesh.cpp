#include "pch.h"
#include "Mesh.h"
#include"Buffer.h"
#include"VertexArray.h"


Mesh::Mesh(const std::vector<Vertex>& vertexs, const std::vector<unsigned int> indices, std::vector<Texture2D*> textures)
	:m_Vertexs(vertexs),m_Indices(indices),m_Textures(textures)
{
	m_VertexArray->Bind();
	BufferLayout layout{
		{ShaderType::Float3,GL_FALSE},
		{ShaderType::Float3,GL_FALSE},
		{ShaderType::Float2,GL_FALSE}
	};
	auto vb =VertexBuffer::Create(vertexs);
	auto ib = IndexBuffer::Create(indices);
	vb->SetBufferLayout(layout);
	m_VertexArray->AddVertexBuffer(vb);
	m_VertexArray->SetIndexBuffer(ib);

}

