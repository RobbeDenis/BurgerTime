#pragma once
#include <BaseComponent.h>
#include <Collider.h>

class Plate final : public dae::BaseComponent
{
public:
	void PostLoad() override;
	void FixedUpdate() override;

	bool CalculateClampedPos(glm::vec3& pos, const int height);

private:
	Plate(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	dae::Collider* m_Collider;
	int m_Width;
	int m_Height;
};


