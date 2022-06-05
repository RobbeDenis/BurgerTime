#pragma once

namespace dae
{
	class BaseComponent;
	class Scene;

	class GameObject final
	{
	public:
		GameObject(); 
		GameObject(std::string label); 
		~GameObject();

		void PostLoad();
		void Start();
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Reset();

		size_t GetChildAmount() const { return m_pChildren.size(); };
		std::shared_ptr<GameObject> AddChild(const std::string& label);
		std::shared_ptr<GameObject> AddChild();
		std::shared_ptr<GameObject> GetChild(size_t index);
		std::shared_ptr<GameObject> GetChild(const std::string& label);
		void RemoveChild(std::string label);
		void RemoveChild(size_t index);

		Scene* GetScene() const;
		void SetScene(Scene* pScene);

		void SetWorldPosition(const glm::vec3& pos);
		void SetWorldPosition(float x, float y);
		void SetWorldPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(float x, float y, float z);
		glm::vec3 GetWorldPosition() const { return m_WorldPosition + m_LocalPosition; };
		glm::vec3 GetLocalPosition() const { return m_LocalPosition; };

		const std::string& GetLabel() const { return m_Label; };

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<BaseComponent*> m_pComponents{};
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};

		std::string m_Label;

		GameObject* m_pParent = nullptr;
		Scene* m_pScene = nullptr;

		glm::vec3 m_WorldPosition;
		glm::vec3 m_LocalPosition;
		bool m_Dirty;

	public:
		template <typename T> 
		T* AddComponent()
		{
			T* comp = new T(this);

			// If template is not a component
			if (!dynamic_cast<BaseComponent*>(comp))
			{
				std::cout << "Warning: GameObject T* AddComponent() Tried adding something that is not a component" << std::endl;
				return nullptr;
			}

			m_pComponents.push_back(comp);
			return comp;
		}

		template <typename T> 
		T* GetComponent() const
		{
			auto it = std::find_if(begin(m_pComponents), end(m_pComponents), [](auto comp)
				{
					return dynamic_cast<T*>(comp);
				});

			if (it == end(m_pComponents))
			{
				std::cout << "Warning: GameObject T* GetComponent() Component has not been found" << std::endl;
				return nullptr;
			}

			return dynamic_cast<T*>(*it);
		}

		template <typename T> 
		void RemoveComponent()
		{
			std::erase(begin(m_pComponents), std::remove(begin(m_pComponents), end(m_pComponents), [](BaseComponent* comp)
				{
					return dynamic_cast<T*>(comp);
				}));
		}
	};
}
