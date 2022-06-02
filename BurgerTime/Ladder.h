#pragma once
#include <BaseComponent.h>

class Ladder final : public dae::BaseComponent
{
public:
	void SetDimensions(const int width, const int height);

	glm::vec3 CalculateClampedPos(const glm::vec3& pos, const int height);
	glm::vec3 CalculateSnappedPos(const glm::vec3& pos, const int width);
	bool CanSnapToLadder(const glm::vec3& pos, const int width);

private:
	Ladder(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	int m_Width;
	int m_Height;
	int m_SnapRange;
};

