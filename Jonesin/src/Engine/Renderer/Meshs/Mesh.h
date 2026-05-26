#pragma once
#include"Texture2D.h"
#include"Vertex.h"
#include<vector>
class VertexArray;
class Material;
class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;
	inline void SetMaterial(const Ref(Material)& material) { m_Material = material; }

private:
	std::vector<Vertex>m_Vertexs;
	std::vector<unsigned int>Indices;
	std::vector<Texture2D*>Textures;



	Ref(Material) m_Material;
	Ref(VertexArray) m_VertexArray;
};

