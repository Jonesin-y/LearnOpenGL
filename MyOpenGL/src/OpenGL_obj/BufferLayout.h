#pragma once
#define GL_FLOAT 0x1406
#define GL_INT 0x1404

class LayoutElement
{
public:
	unsigned int Count;
	unsigned int Type;
	unsigned char Normalized;
	unsigned int Offset;
};
class BufferLayout
{
public:
	unsigned int Stride;
	unsigned int Offset;
public:
	BufferLayout();
	~BufferLayout();
	inline std::vector<LayoutElement>&GetElements(){ return m_Elements; }
	template<typename T>
	void Push(unsigned int count, unsigned char normalized)
	{
		static_assert(false, "Unsupported Type!");
	}
	template<>
	void Push<float>(unsigned int count, unsigned char normalized)
	{
		
		m_Elements.push_back({ count, GL_FLOAT, normalized,Offset });
		Offset = Offset + count * sizeof(float);
		Stride = Stride + count * sizeof(float);

	}
	template<>
	void Push<int>(unsigned int count, unsigned char normalized)
	{
		
		m_Elements.push_back({ count, GL_INT, normalized, Offset });
		Offset = Offset + count * sizeof(int);
		Stride = Stride + count * sizeof(int);
	};

private:
	std::vector<LayoutElement>m_Elements;
	
};

