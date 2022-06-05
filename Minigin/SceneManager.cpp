#include "RodEnginePCH.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Scene.h"

void dae::SceneManager::PostLoad()
{
	for (auto& scene : m_Scenes)
	{
		scene->PostLoad();
	}
}

void dae::SceneManager::Start()
{
	if (!m_ActiveScene)
		return;

	m_ActiveScene->Start();
}

void dae::SceneManager::Update()
{
	if (!m_ActiveScene)
		return;

	m_ActiveScene->Update();
}

void dae::SceneManager::FixedUpdate()
{
	if (!m_ActiveScene)
		return;

	m_ActiveScene->FixedUpdate();
}

void dae::SceneManager::LateUpdate()
{
	if (!m_ActiveScene)
		return;

	m_ActiveScene->LateUpdate();
}

void dae::SceneManager::Render()
{
	if (!m_ActiveScene)
		return;

	m_ActiveScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	InputManager::GetInstance().AddNewSceneCommands();
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::SetScene(const std::string& name)
{
	int i = 0;
	auto it = std::find_if(begin(m_Scenes), end(m_Scenes), [&i, name](auto scene)
		{
			++i;
			return scene->GetName() == name;
		});

	if (it == end(m_Scenes))
		return;

	m_SceneIdx = i - 1;
	m_ActiveScene = *it;
}
