#pragma once
#include"Core.h"
#include<glm/glm.hpp>
#include<vector>
struct lightSource;
class Environment
{
public:
	Environment() = default;
	~Environment() = default;
	unsigned int GetLightSourcesSize();
	inline std::vector<Ref(lightSource)>& GetLightSources() { return m_lightSources; }
	inline void SetLightSources(std::vector<Ref(lightSource)>lightSources) { m_lightSources = lightSources; }
private:
	std::vector<Ref(lightSource)> m_lightSources;
	
};

