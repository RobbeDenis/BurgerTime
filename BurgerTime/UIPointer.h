#pragma once
#include <BaseComponent.h>
#include <Observer.h>
#include <Subject.h>

class UIPointer final : public dae::BaseComponent
{
public:
	void PostLoad() override;
	void Up();
	void Down();
	void SetMax(const int max);
	void AddObserver(dae::Observer* observer);
	void Confirm();

	int GetIndex() const { return m_Index; };

private:
	UIPointer(dae::GameObject* gameObject);
	template <typename T>
	friend T* dae::GameObject::AddComponent();

	void ReplacePointer();

	glm::vec3 m_StartPos;
	std::shared_ptr<dae::Subject> m_pSubject;
	int m_Width;
	int m_Height;
	int m_Offset;
	int m_Index;
	int m_Max;
};

