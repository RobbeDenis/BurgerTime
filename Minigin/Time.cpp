#include "RodEnginePCH.h"
#include "Time.h"

void dae::Time::Update()
{
	auto curruntTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(curruntTime - m_PrevTime).count();
	m_PrevTime = curruntTime;
	m_Lag += m_DeltaTime;

	// Check if fixed update is lagging behind
	if (m_Lag >= m_MsPerFixedUpdate)
	{
		m_IsFixedUpdateReady = true;
	}
}

void dae::Time::FixedUpdateCompleted()
{
	// Check if fixed update was ready
	if (m_IsFixedUpdateReady)
	{
		m_Lag -= m_MsPerFixedUpdate;

		// return if still lagging behind
		if (m_Lag >= m_MsPerFixedUpdate)
		{
			return;
		}

		m_IsFixedUpdateReady = false;
	}
}
