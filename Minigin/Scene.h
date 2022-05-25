#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class RenderComponent;

	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void AddRenderComponent(RenderComponent* pRenderComp);

		void Remove(const std::shared_ptr<GameObject>& object);

		void PostLoad();
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_Objects{};
		std::vector<RenderComponent*> m_pRenderComponents{};

		static unsigned int m_IdCounter; 
	};

}
