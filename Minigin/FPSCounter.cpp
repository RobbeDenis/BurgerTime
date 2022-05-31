#include "RodEnginePCH.h"
#include "FPSCounter.h"
#include "TextComponent.h"
#include "ETime.h"

void dae::FPSCounter::PostLoad()
{
	m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();

	if (m_pTextComponent == nullptr)
	{
		std::cout << "Warning: dae::FPSCounter::PostLoad() TextComponent was not found" << std::endl;
	}
}

void dae::FPSCounter::Update()
{
	float elapsedTime = ETime::GetInstance().GetDeltaTime();

	if (m_UseSmoothing)
	{
		m_ElapsedIntervalTime += elapsedTime;
		if (m_ElapsedIntervalTime >= m_UpdateInterval)
		{
			int fps = int(1 / elapsedTime);
			m_pTextComponent->SetText(std::to_string(fps) + " FPS");
			m_ElapsedIntervalTime = 0;
		}
	}
	else
	{
		int fps = int(1 / elapsedTime);
		m_pTextComponent->SetText(std::to_string(fps) + " FPS");
	}
}

void dae::FPSCounter::UseSmoothing(bool enable)
{
	m_UseSmoothing = enable;
}
