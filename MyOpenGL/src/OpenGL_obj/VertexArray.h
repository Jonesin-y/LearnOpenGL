#pragma once
#include <vector>
class VertexBuffer;
class LeyoutElement;
class BufferLayout;
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void AddBufferLayout(const VertexBuffer& vb, BufferLayout& layout);
	void Bind();
	void UnBind();

private:
	unsigned int m_RendererID;
	unsigned int m_ShaderPipeID;
};

