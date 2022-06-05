#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class RenderComponent;
	class DebugRenderComponent;
	class Collider;

	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void AddRenderComponent(RenderComponent* pRenderComp);
		void AddDebugRenderComponent(DebugRenderComponent* pRenderComp);
		void AddCollider(Collider* pCollider);

		void PostLoad();
		void Start();
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;
		void Reset();

		void EnableDebugRender(bool enable) { m_EnableDebug = enable; };
		const std::string& GetName() { return m_Name; };
		const std::vector<Collider*>& GetColliders() const { return m_pColliders; };

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
		std::vector<DebugRenderComponent*> m_pDebugRenderComponents{};
		std::vector<Collider*> m_pColliders{};
		bool m_EnableDebug;
	};

}
