#pragma once
#include"Texture2D.h"
#include"Vertex.h"
#include"Core.h"
#include<vector>
class ShaderLibrary;
class VertexArray;
class Material;
class Mesh
{
public:
	Mesh(const std::vector<Vertex>&vertexs,const std::vector<unsigned int>&indices);
	Mesh() = default;
	~Mesh() = default;
	void Bind();
	inline void SetMaterial(const Ref(Material)& material) { m_Material = material; }
	inline std::vector<unsigned int>& GetIndices() { return m_Indices; }
private:
	std::vector<Vertex>m_Vertexs;
	std::vector<unsigned int>m_Indices;

	Ref(Material) m_Material;
	Ref(VertexArray) m_VertexArray;
};

