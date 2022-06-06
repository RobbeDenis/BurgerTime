#pragma once
#include <BaseComponent.h>
#include <Collider.h>
#include <Observer.h>
#include <Subject.h>

class Plate final : public dae::BaseComponent
{
public:
	void PostLoad() override;
	void FixedUpdate() override;
	void Reset() override;

	bool CalculateClampedPos(glm::vec3& pos, const int height);
	void AddObserver(dae::Observer* observer);

private:
	Plate(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	dae::Collider* m_Collider;
	int m_Width;
	int m_Height;
	std::shared_ptr<dae::Subject> m_pSubject;
	bool m_Filled;
};


