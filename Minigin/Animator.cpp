#include "RodEnginePCH.h"
#include "Animator.h"
#include "RenderComponent.h"

dae::Animator::Animator(GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_pRenderComponent{ nullptr }
	, m_CurrentAnimationId{ 0 }
	, m_CurrentFrame{ 0 }
	, m_DstHeight{ 0 }
	, m_DstWidth{ 0 }
	, m_ElapsedTime{ 0 }
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

void dae::Animator::AddAnimation(const int id, const int nrOffFrames, const glm::vec2& srcPos, const float srcWidth, const float srcHeight, const bool mirror, const float timePerFrame)
{
	AnimationData animation;
	animation.Id = id;
	animation.NrOffFrames = nrOffFrames;
	animation.SrcPos = srcPos;
	animation.SrcHeight = srcHeight;
	animation.SrcWidth = srcWidth;
	animation.TimePerFrame = timePerFrame;
	animation.Mirror = mirror;

	m_Animations.push_back(animation);
}

void dae::Animator::SetAnimation(const int id)
{
	for (int i = 0; i < m_Animations.size(); i++)
	{
		if (m_Animations[i].Id == id)
		{
			m_CurrentAnimationId = i;

			m_pRenderComponent->SetSrc(
				m_Animations[i].SrcPos.x, 
				m_Animations[i].SrcPos.y, 
				m_Animations[i].SrcWidth, 
				m_Animations[i].SrcHeight);

			m_ElapsedTime = 0.f;
			m_CurrentFrame = 0;
		}
	}
}

void dae::Animator::FixedUpdate() 
{

}