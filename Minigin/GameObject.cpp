#include "RodEnginePCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Scene.h"

using namespace dae;

dae::GameObject::GameObject(std::string label)
	: m_Label{ label }
	, m_Dirty{ true }
{}

dae::GameObject::GameObject() 
	: m_Label{ "" }
	, m_Dirty{ true }
{};

dae::GameObject::~GameObject() 
{
	for (BaseComponent* comp : m_pComponents)
	{
		delete comp;
		comp = nullptr;
	}
};

void dae::GameObject::PostLoad()
{
	for (BaseComponent* comp : m_pComponents)
	{
		comp->PostLoad();
	}

	for (std::shared_ptr<GameObject> obj : m_pChildren)
	{
		obj->PostLoad();
	}
}

void dae::GameObject::Start()
{
	for (BaseComponent* comp : m_pComponents)
	{
		comp->Start();
	}

	for (std::shared_ptr<GameObject> obj : m_pChildren)
	{
		obj->Start();
	}
}

void dae::GameObject::Update()
{
	for (BaseComponent* c : m_pComponents)
	{
		c->Update();
	}

	for (std::shared_ptr<GameObject> obj : m_pChildren)
	{
		if (m_Dirty)
		{
			obj->SetWorldPosition(m_WorldPosition + m_LocalPosition);
			m_Dirty = false;
		}

		obj->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (BaseComponent* c : m_pComponents)
	{
		c->FixedUpdate();
	}

	for (std::shared_ptr<GameObject> obj : m_pChildren)
	{
		obj->FixedUpdate();
	}
}

void dae::GameObject::LateUpdate()
{
	for (BaseComponent* c : m_pComponents)
	{
		c->LateUpdate();
	}

	for (std::shared_ptr<GameObject> obj : m_pChildren)
	{
		obj->LateUpdate();
	}
}

void dae::GameObject::Reset()
{
	for (BaseComponent* c : m_pComponents)
	{
		c->Reset();
	}

	for (std::shared_ptr<GameObject> obj : m_pChildren)
	{
		obj->Reset();
	}
}

void dae::GameObject::SetScene(Scene* pScene)
{
	m_pScene = pScene;
}

void dae::GameObject::SetWorldPosition(const glm::vec3& pos)
{
	m_WorldPosition = pos;
	m_Dirty = true;
}

void dae::GameObject::SetWorldPosition(float x, float y)
{
	SetWorldPosition(x, y, 0.f);
}

void dae::GameObject::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
	m_Dirty = true;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	m_Dirty = true;
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	SetLocalPosition(x, y, 0.f);
}

void dae::GameObject::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	m_Dirty = true;
}

dae::Scene* dae::GameObject::GetScene() const
{
	if (m_pParent)
		return m_pParent->GetScene();
	else
		return m_pScene;
}


std::shared_ptr<GameObject> dae::GameObject::AddChild()
{
	return AddChild("");
}

std::shared_ptr<GameObject> dae::GameObject::AddChild(const std::string& label)
{
	std::shared_ptr<GameObject> pChild = std::make_shared<GameObject>();

	pChild->m_Label = label;
	pChild->m_pParent = this;

	m_pChildren.push_back(pChild);

	return pChild;
}

std::shared_ptr<GameObject> dae::GameObject::GetChild(size_t index)
{
	if (index >= m_pChildren.size())
		return nullptr;

	return m_pChildren[index];
}

std::shared_ptr<GameObject> dae::GameObject::GetChild(const std::string& label)
{
	auto it = std::find_if(begin(m_pChildren), end(m_pChildren), [&label](auto pChild)
		{
			return pChild->m_Label == label;
		});

	if (it == end(m_pChildren))
		return nullptr;

	return *it;
}

void dae::GameObject::RemoveChild(std::string label)
{
	m_pChildren.erase(std::remove_if(begin(m_pChildren), end(m_pChildren), [&label](auto pChild)
		{
			return pChild->m_Label == label;
		}), end(m_pChildren));
}

void dae::GameObject::RemoveChild(size_t index)
{
	if (index >= m_pChildren.size())
		return;

	m_pChildren.erase(begin(m_pChildren) + index);
}