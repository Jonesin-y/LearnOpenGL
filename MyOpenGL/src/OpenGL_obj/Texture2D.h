#pragma once
 
#include<string>


class Texture2D
{
public:
	Texture2D(const std::string& filePath);
	~Texture2D();
	void Bind(unsigned int slot)const;
	void UnBind()const;



private:
	GLuint RendererID;

	int m_Width, m_Height,m_BBP;
	unsigned char* m_TexData;
	std::string m_FilePath;

};

