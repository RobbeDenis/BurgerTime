#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class ETime final : public Singleton<ETime>
	{
	public:
		void Update();
		void FixedUpdateCompleted();

		float GetDeltaTime() const { return m_DeltaTime; };
		bool IsFixedUpdateReady() const { return m_IsFixedUpdateReady; };

	private:
		std::chrono::high_resolution_clock::time_point m_PrevTime;
		float m_DeltaTime = 0;
		float m_Lag = 0;
		float m_MsPerFixedUpdate = 0.02f;
		bool m_IsFixedUpdateReady = false;
	};
}