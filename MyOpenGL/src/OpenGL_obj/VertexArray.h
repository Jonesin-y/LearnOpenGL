#pragma once
#include<memory.h>
#include <vector>

class VertexBuffer;
class IndexBuffer;
class LeyoutElement;
class BufferLayout;
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib);
	void Bind();
	void UnBind();

private:
	unsigned int m_RendererID;
	unsigned int m_ShaderPipeID;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

