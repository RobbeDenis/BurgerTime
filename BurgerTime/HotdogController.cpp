#include "HotdogController.h"
#include <ETime.h>
#include <random>
#include "Character.h"
#include "Ladder.h"
#include "Platform.h"

HotdogController::HotdogController(dae::GameObject* gameObject)
	: BaseComponent(gameObject)
	, m_Character(nullptr)
	, m_Target(nullptr)
	, m_MaxActivateDelay(0.2f)
	, m_ActivateDelay(0.f)
	, m_Active(false)
	, m_State(0)
	, m_UsingLadder(false)
	, m_WidthDetectOffset(1)
	, m_PrevLadder(nullptr)
	, m_PrevPlatform(nullptr)
{

}

void HotdogController::Reset()
{
	m_State = 0;
	m_PrevLadder = nullptr;
	m_PrevPlatform = nullptr;
	m_UsingLadder = false;
	m_Active = false;
}

void HotdogController::PostLoad()
{
	m_Character = m_pGameObject->GetComponent<Character>();
}

void HotdogController::FixedUpdate()
{
	if (!m_Target)
		return;

	if (!m_Active)
	{
		m_ActivateDelay += dae::ETime::GetInstance().GetDeltaTime();
		if (m_ActivateDelay >= m_MaxActivateDelay)
		{
			m_ActivateDelay = 0.f;
		}
		m_Active = false;
	}

	glm::vec3 thisPos = m_pGameObject->GetWorldPosition();
	Ladder* thisLadder = m_Character->GetOverlappingLadder(); thisLadder;
	Platform* thisPlatform = m_Character->GetOverlappingPlatform(); thisPlatform;

	glm::vec3 targetPos = m_Target->GetGameObject()->GetWorldPosition();
	Ladder* targetLadder = m_Target->GetOverlappingLadder(); targetLadder;
	Platform* targetPlatform = m_Target->GetOverlappingPlatform(); targetPlatform;

	if (m_State == CharacterState::Idle)
	{
		// LOOK IF TARGET IS RIGHT OR LEFT
		if (thisPos.x < targetPos.x)
		{
			m_State = CharacterState::WalkRight;
		}
		else
		{
			m_State = CharacterState::WalkLeft;
		}
	}

	// WHEN USING PLATFORM
	if (!m_UsingLadder)
	{
		// IF ON SAME PLATFORM AND WALKING TO TARGET
		if (thisPlatform && thisPlatform == targetPlatform && m_State == CharacterState::WalkRight)
		{
			if(thisPos.x < targetPos.x)
				return;
		}
		// IF ON SAME PLATFORM AND WALKING TO TARGET
		if (thisPlatform && thisPlatform == targetPlatform && m_State == CharacterState::WalkLeft)
		{
			if (thisPos.x > targetPos.x)
				return;
		}


		// LOOK IF A LADDER HAS TO BE USED
		// IF WALKING OR IDLE ON A PLATFORM
		if (m_State == CharacterState::WalkRight || m_State == CharacterState::WalkLeft || m_State == CharacterState::Idle)
		{
			if (thisLadder && m_PrevLadder != thisLadder && thisLadder->CanSnapToLadder(thisPos, m_Character->GetWidth()))
			{
				// 30/70 to go on the ladder
				if (20 <= rand() % 100)
				{
					// IF NOT AT THE END OF A LADDER GO DOWN OR UP DEPENDING ON TARGET POS
					if (!(thisLadder->IsAtEndOffLadder(thisPos, m_Character->GetHeight())))
					{
						if (thisPos.y < targetPos.y)
						{
							m_State = CharacterState::LadderDown;
						}
						else
						{
							m_State = CharacterState::LadderUp;
						}
					}
					// IF AT THE END OF A LADDER GO WICH EVER WAY POSSIBLE
					else if (thisPos.y < thisLadder->GetGameObject()->GetWorldPosition().y)
					{
						m_State = CharacterState::LadderDown;
					}
					else
					{
						m_State = CharacterState::LadderUp;
					}

					m_PrevPlatform = thisPlatform;
					m_UsingLadder = true;
					return;
				}
				else
				{
					// IF ON SAME PLATFORM AND WALKING TO TARGET
					if (thisPlatform == targetPlatform && m_State == CharacterState::WalkRight)
					{
						if (thisPos.x < targetPos.x)
							return;
					}
					// IF ON SAME PLATFORM AND WALKING TO TARGET
					if (thisPlatform == targetPlatform && m_State == CharacterState::WalkLeft)
					{
						if (thisPos.x > targetPos.x)
							return;
					}

					// IF NOT AT THE END OF A LADDER GO DOWN OR UP DEPENDING ON TARGET POS
					if (!(thisLadder->IsAtEndOffLadder(thisPos, m_Character->GetHeight())))
					{
						if (thisPos.y < targetPos.y)
						{
							m_State = CharacterState::LadderDown;
						}
						else
						{
							m_State = CharacterState::LadderUp;
						}
					}
					// IF AT THE END OF A LADDER GO WICH EVER WAY POSSIBLE
					else if (thisPos.y < thisLadder->GetGameObject()->GetWorldPosition().y)
					{
						m_State = CharacterState::LadderDown;
					}
					else
					{
						m_State = CharacterState::LadderUp;
					}

					m_PrevPlatform = thisPlatform;
					m_UsingLadder = true;
					return;
				}
			}
		}

		if (thisPlatform)
		{
			// WALK OTHER WAY IF AT THE END OF PLATFORM
			if (m_State == CharacterState::WalkLeft)
			{
				if (thisPos.x - m_WidthDetectOffset < thisPlatform->GetGameObject()->GetWorldPosition().x)
					m_State = CharacterState::WalkRight;
			}
			else if (m_State == CharacterState::WalkRight)
			{
				if (thisPos.x + m_WidthDetectOffset + m_Character->GetWidth() > thisPlatform->GetGameObject()->GetWorldPosition().x + thisPlatform->GetWidth())
					m_State = CharacterState::WalkLeft;
			}
		}
	}

	// WHEN USING LADDER
	if (m_UsingLadder)
	{
		// IF NEW PLATFORM OVERLAPS
		if (thisPlatform && m_PrevPlatform != thisPlatform)
		{
			if (thisPlatform->CanSnapToPlatform(thisPos, m_Character->GetHeight()))
			{
				// IF THIS PLATFORM IS THE SAME AS THE TARGETS ONE GO TO TARGET
				if (thisPlatform == targetPlatform)
				{
					// LOOK IF TARGET IS RIGHT OR LEFT
					if (thisPos.x < targetPos.x)
					{
						m_State = CharacterState::WalkRight;
					}
					else
					{
						m_State = CharacterState::WalkLeft;
					}

					m_PrevLadder = thisLadder;
					m_UsingLadder = false;
					return;
				}

				// IF CHAR WAS GOING UP
				if (m_State == CharacterState::LadderUp)
				{
					// IF TARGET HIGHER AND NOT THE END OF LADDER -> KEEP GOING
					if (thisPos.y > targetPos.y && !(thisLadder->IsAtEndOffLadder(thisPos, m_Character->GetHeight())))
					{
						m_PrevPlatform = thisPlatform;
						return;
					}
				}
				// IF CHAR WAS GOING DOWN
				else if(m_State == CharacterState::LadderDown)
				{
					// IF TARGET IS LOWER AND NOT THE END AF LADDER -> KEEP GOING
					if (thisPos.y < targetPos.y && !(thisLadder->IsAtEndOffLadder(thisPos, m_Character->GetHeight())))
					{
						m_PrevPlatform = thisPlatform;
						return;
					}
				}

				// ELSE GO ON PLATFORM
				if (thisPos.x < targetPos.x)
				{
					m_State = CharacterState::WalkRight;
				}
				else
				{
					m_State = CharacterState::WalkLeft;
				}
				m_PrevLadder = thisLadder;
				m_UsingLadder = false;
				return;
			}
		}
	}
}

void HotdogController::Update()
{
	switch (m_State)
	{
	case CharacterState::WalkRight:
		m_Character->MoveRight();
		break;
	case CharacterState::WalkLeft:
		m_Character->MoveLeft();
		break;
	case CharacterState::LadderDown:
		m_Character->MoveDownLadder();
		break;
	case CharacterState::LadderUp:
		m_Character->MoveUpLadder();
		break;
	default:
		break;
	}
}