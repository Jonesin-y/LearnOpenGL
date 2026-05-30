#pragma once
#include"Core.h"
#include<glm/glm.hpp>
#include<unordered_map>
#include<string>
#include"lightSource.h"
class Environment
{
public:
	Environment() = default;
	~Environment() = default;
	unsigned int GetLightSourcesSize();
	inline std::vector<lightSource>& GetLightSources() { return m_lightSources; }
	inline void SetLightSources(const std::vector<lightSource>&lightSources) { m_lightSources = lightSources; }
private:
	std::vector<lightSource> m_lightSources;
};

