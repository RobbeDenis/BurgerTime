#pragma once
#include "RodEnginePCH.h"
#include "GameObject.h"

namespace dae
{
	class BaseComponent
	{
	public:
		virtual void PostLoad() {};
		virtual void Start() {};
		virtual void Update() {};
		virtual void FixedUpdate() {};
		virtual void LateUpdate() {};
		virtual void Reset() {};

		virtual ~BaseComponent() = default;

		GameObject* GetGameObject() const { return m_pGameObject; };

	protected:
		BaseComponent(GameObject* gameObject) : m_pGameObject{ gameObject } {};

	private:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		// Only the gameObject is allowed to set the gameObject
		void SetGameObject(GameObject* gameObject);
		friend GameObject;

	protected:
		GameObject* m_pGameObject;
	};
}

