#include "RodEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "DebugRenderComponent.h"
#include "Collider.h"

using namespace dae;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
	, m_EnableDebug(false)
{

}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object.get()->SetScene(this);
}

void Scene::AddDebugRenderComponent(DebugRenderComponent* pRenderComp)
{
	m_pDebugRenderComponents.push_back(pRenderComp);
}

void Scene::AddRenderComponent(RenderComponent* pRenderComp)
{
	m_pRenderComponents.push_back(pRenderComp);
}

void Scene::AddCollider(Collider* pCollider)
{
	m_pColliders.push_back(pCollider);
}

void Scene::PostLoad()
{
	for (auto& object : m_Objects)
	{
		object->PostLoad();
	}
}

void Scene::Start()
{
	
	for (auto& object : m_Objects)
	{
		object->Start();
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

	if (m_EnableDebug)
	{
		for (const auto& comp : m_pDebugRenderComponents)
		{
			comp->Render();
		}
	}
}

