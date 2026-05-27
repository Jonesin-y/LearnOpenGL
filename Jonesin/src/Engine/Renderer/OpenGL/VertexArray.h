#pragma once
#include"Core.h"
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
	void AddVertexBuffer(const Ref(VertexBuffer)& vb);
	void SetIndexBuffer(const Ref(IndexBuffer)& ib);
	inline std::vector <Ref(VertexBuffer)>& GetVertexBuffers() { return m_VertexBuffers; }
	inline Ref(IndexBuffer)& GetIndexBuffer() { return m_IndexBuffer; }
	void Bind();
	void UnBind();

private:
	unsigned int m_RendererID;
	unsigned int m_ShaderPipeID;
	std::vector<Ref(VertexBuffer)> m_VertexBuffers;
	Ref(IndexBuffer) m_IndexBuffer;
};

