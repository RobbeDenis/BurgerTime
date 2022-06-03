#include "RodEnginePCH.h"
#include "Animator.h"
#include "RenderComponent.h"
#include "ETime.h"

dae::Animator::Animator(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_pRenderComponent{ nullptr }
	, m_CurrentAnimationIndex{ 0 }
	, m_CurrentFrame{ 0 }
	, m_DstHeight{ 0 }
	, m_DstWidth{ 0 }
	, m_ElapsedTime{ 0 }
	, m_Pause{ false }
{

}

void dae::Animator::PostLoad()
{
	m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();
	m_pRenderComponent->UseSrc(true);
}

void dae::Animator::SetDst(const glm::vec2& dstPos, const float dstWidth, const float dstHeight)
{
	m_pRenderComponent->SetDst(dstPos.x, dstPos.y, dstWidth, dstHeight);
}

void dae::Animator::Pause()
{
	m_Pause = true;
}

void dae::Animator::Play()
{
	m_Pause = false;
}

void dae::Animator::AddAnimation(const int id, const int nrOffFrames, const glm::vec2& srcPos, const float srcWidth, const float srcHeight, const bool mirror, const float TimePerFrame, const bool loop)
{
	AnimationData animation;
	animation.Id = id;
	animation.NrOffFrames = nrOffFrames;
	animation.SrcPos = srcPos;
	animation.SrcHeight = srcHeight;
	animation.SrcWidth = srcWidth;
	animation.TimePerFrame = TimePerFrame;
	animation.Mirror = mirror;
	animation.Loop = loop;

	m_Animations.push_back(animation);
}

void dae::Animator::SetAnimation(const int id)
{
	for (int i = 0; i < m_Animations.size(); i++)
	{
		if (m_Animations[i].Id == id)
		{
			m_CurrentAnimationIndex = i;

			m_pRenderComponent->SetSrc(
				m_Animations[i].SrcPos.x, 
				m_Animations[i].SrcPos.y, 
				m_Animations[i].SrcWidth, 
				m_Animations[i].SrcHeight);

			m_pRenderComponent->Mirror(m_Animations[i].Mirror);

			m_ElapsedTime = 0.f;
			m_CurrentFrame = 0;
			m_Pause = false;
		}
	}
}

void dae::Animator::FixedUpdate() 
{
	if (m_Pause || m_Animations.empty())
		return;

	const AnimationData& animation = m_Animations[m_CurrentAnimationIndex];

	// Return if animation only has 1 frame
	// Return if animation enden and doesn't loop
	if (animation.NrOffFrames <= 1 || (!animation.Loop && m_CurrentFrame >= animation.NrOffFrames))
		return;

	m_ElapsedTime += ETime::GetInstance().GetDeltaTime();

	while (m_ElapsedTime >= animation.TimePerFrame)
	{
		++m_CurrentFrame;
		if (m_CurrentFrame >= animation.NrOffFrames)
		{
			if (!animation.Loop)
				return;

			m_CurrentFrame = 0;
		}

		m_pRenderComponent->SetSrc(
			animation.SrcPos.x + (m_CurrentFrame * animation.SrcWidth),
			animation.SrcPos.y,
			animation.SrcWidth,
			animation.SrcHeight);

		m_ElapsedTime -= animation.TimePerFrame;
	}
}