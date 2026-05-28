#include "pch.h"
#include "Environment.h"
#include"lightSource.h"
unsigned int Environment::GetLightSourcesSize()
{
	return m_lightSources.size() * sizeof(lightSource);
}
