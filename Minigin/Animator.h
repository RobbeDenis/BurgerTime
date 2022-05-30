#pragma once
#include "BaseComponent.h"

namespace dae
{
	class RenderComponent;
	class Animator final : public BaseComponent
	{
	public:
		void PostLoad() override;
		void FixedUpdate() override;
		void AddAnimation(const int id, const int nrOffFrames, const glm::vec2& srcPos, const float srcWidth, const float srcHeight, const float TimePerFrame = 250.f);
		void SetAnimation(const int id);
		void SetDst(const glm::vec2& dstPos, const float dstWidth, const float dstHeight);

	private:
		struct AnimationData
		{
			glm::vec2 SrcPos;
			float SrcWidth;
			float SrcHeight;
			float TimePerFrame;
			int Id;
			int NrOffFrames;
		};

		Animator(GameObject* gameObject);
		template <typename T>
		friend T* GameObject::AddComponent();

		std::vector<AnimationData> m_Animations;
		RenderComponent* m_pRenderComponent;

		// Animation info
		glm::vec2 m_DstPos;
		float m_DstWidth;
		float m_DstHeight;
		float m_ElapsedTime;
		int m_CurrentAnimationId;
		int m_CurrentFrame;
	};
}

