#include "ExampleLayer.h"
#include"Renderer3D.h"
ExampleLayer::ExampleLayer()
{

}
void ExampleLayer::OnAttach()
{

}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate()
{
	m_Renderer3D->BeginScene();
	m_Renderer3D->SubmitMesh()
}

void ExampleLayer::OnEvent(Event& event)
{

}
