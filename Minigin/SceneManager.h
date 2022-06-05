#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetScene(const std::string& name);
		int GetSceneIdx() const { return m_SceneIdx; };

		void PostLoad();
		void Start();
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render();
		void Reset();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
		int m_SceneIdx = 0;
	};
}
