#pragma once
#include <BaseComponent.h>

class Platform final : public dae::BaseComponent
{
public:
	void SetDimensions(const int width, const int height);

	glm::vec3 CalculateClampedPos(const glm::vec3& pos, const int width);
	glm::vec3 CalculateSnappedPos(const glm::vec3& pos, const int height);

private:
	Platform(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	int m_Width;
	int m_Height;
	int m_VerticalSnapOffset;
};

