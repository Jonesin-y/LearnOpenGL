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
	Mesh(const std::vector<Vertex>&vertexs,const std::vector<unsigned int>indices,std::vector<Texture2D*>textures);
	Mesh() = default;
	~Mesh() = default;
	inline void SetMaterial(const Ref(Material)& material) { m_Material = material; }
private:
	std::vector<Vertex>m_Vertexs;
	std::vector<unsigned int>m_Indices;
	std::vector<Texture2D*>m_Textures;


	Ref(Material) m_Material;
	Ref(VertexArray) m_VertexArray;
};

