#pragma once
#include<glm/glm.hpp>
#include<vector>
struct lightSource;
class Environment
{
public:
	Environment() = default;
	~Environment() = default;
	void SetLightSources() {};
private:
	std::vector<lightSource*> m_lightSources;
	
};

