#include "RodEnginePCH.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

#include "XBox360Controller.h"

class dae::XBox360Controller::XBox360ControllerImpl
{
public:
	XBox360ControllerImpl(int controllerIndex)
		: m_ControllerIndex{ controllerIndex }
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PrevState, sizeof(XINPUT_STATE));
	}

	void ProcessInput()
	{
		CopyMemory(&m_PrevState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		WORD buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PrevState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsPressed(ControllerButton button) const { return m_ButtonsPressedThisFrame & static_cast<unsigned int>(button); };
	bool IsReleased(ControllerButton button) const { return m_ButtonsReleasedThisFrame & static_cast<unsigned int>(button); };
	bool IsDown(ControllerButton button) const { return m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button); };

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PrevState{};
	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};
	int m_ControllerIndex{};
};

dae::XBox360Controller::XBox360Controller(int controllerIndex)
{
	m_pImpl = new XBox360ControllerImpl(controllerIndex);
}

dae::XBox360Controller::~XBox360Controller()
{
	delete m_pImpl;
}

void dae::XBox360Controller::ProcessInput()
{
	m_pImpl->ProcessInput();
}

bool dae::XBox360Controller::IsPressed(ControllerButton button) const 
{ 
	return m_pImpl->IsPressed(button);
};

bool dae::XBox360Controller::IsReleased(ControllerButton button) const 
{ 
	return m_pImpl->IsReleased(button);
};

bool dae::XBox360Controller::IsDown(ControllerButton button) const 
{ 
	return m_pImpl->IsDown(button);
};