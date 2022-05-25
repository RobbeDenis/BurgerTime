#include "RodEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object.get()->SetScene(this);
}

void Scene::AddRenderComponent(RenderComponent* pRenderComp)
{
	m_pRenderComponents.push_back(pRenderComp);
}

void Scene::PostLoad()
{
	for (auto& object : m_Objects)
	{
		object->PostLoad();
	}
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& comp : m_pRenderComponents)
	{
		comp->Render();
	}
}

