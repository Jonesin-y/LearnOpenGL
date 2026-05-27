#pragma once
#define GL_FALSE 0
#define GL_FLOAT 0x1406
#define GL_INT 0x1404
#include"Vertex.h"
#include<vector>
#include<string>
enum class ShaderType
{
	NONE = 0,Float1,Float2,Float3,Float4,Mat3,Mat4,Int1,Int2,Int3,Int4,Bool
};
unsigned int ShaderDataTypeSize(ShaderType type);
unsigned int ShaderDataTypeCount(ShaderType type);
unsigned int SwitchShaderTypeToGladType(ShaderType type);
struct BufferElement
{
	std::string Name;
	unsigned int Count;
	unsigned int Size;
	ShaderType Type;
	unsigned char Normalized;
	unsigned int Offset;
	BufferElement(ShaderType type, const std::string& name, bool normalized = GL_FALSE);
};
class BufferLayout
{
public:
	BufferLayout();
	BufferLayout(const std::initializer_list<BufferElement>& Elements);
	~BufferLayout();
	inline const int GetStride() const { return m_Stride; }
	inline const std::vector<BufferElement>&GetElements()const { return m_Elements; }
	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

private:
	void CaculateLayout();
private:
	std::vector<BufferElement>m_Elements;
	int m_Stride;

};
class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const std::vector<Vertex>& vertexs);

	~VertexBuffer();
	void Bind()const;
	void UnBind()const;
	void SetBufferLayout(BufferLayout& layout) { m_BufferLayout = layout; }
	inline const BufferLayout& GetBufferLayout()const { return m_BufferLayout; }

	static::std::shared_ptr<VertexBuffer> Create(const void* data, unsigned int count);
	static::std::shared_ptr<VertexBuffer> Create(const std::vector<Vertex>& vertexs);
private:
	unsigned int m_RendererID;
	BufferLayout m_BufferLayout;
};
class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int count);
	IndexBuffer(const std::vector<unsigned int>&indices);
	~IndexBuffer();
	void Bind()const;
	void UnBind()const;
	inline void SetCount(unsigned int count) { m_Count = count; }
	inline unsigned int GetCount() { return m_Count; }

	static::std::shared_ptr<IndexBuffer> Create(const void* data, unsigned int count);
	static::std::shared_ptr<IndexBuffer> Create(const std::vector<unsigned int>indices);

private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};

