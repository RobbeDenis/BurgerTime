#include "RodEnginePCH.h"
#include "InputManager.h"

dae::InputManager::~InputManager()
{
	m_ControllerCommands.erase(begin(m_ControllerCommands), end(m_ControllerCommands));
}

bool dae::InputManager::ProcessInput()
{
	for (const std::unique_ptr<XBox360Controller>& controller : m_Controllers)
	{
		controller->ProcessInput();

		for (auto& command : m_ControllerCommands)
		{
			switch (command.first.State)
			{
			case ButtonState::Pressed:
				if (controller->IsPressed(command.first.Button))
					command.second->Execute();
				break;

			case ButtonState::Released:
				if (controller->IsReleased(command.first.Button))
					command.second->Execute();
				break;

			case ButtonState::Down:
				if (controller->IsDown(command.first.Button))
					command.second->Execute();
				break;
			}
		}
	}

	ProcessKeyboardInput();

	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(XBox360Controller::ControllerButton button, unsigned int controllerIdx) const
{
	if (m_Controllers.empty() || m_Controllers.size() <= controllerIdx)
		return false;

	return m_Controllers[controllerIdx]->IsPressed(button);
}

bool dae::InputManager::IsReleased(XBox360Controller::ControllerButton button, unsigned int controllerIdx) const
{
	if (m_Controllers.empty() || m_Controllers.size() <= controllerIdx)
		return false;

	return m_Controllers[controllerIdx]->IsReleased(button);
}

bool dae::InputManager::IsDown(XBox360Controller::ControllerButton button, unsigned int controllerIdx) const
{
	if (m_Controllers.empty() || m_Controllers.size() <= controllerIdx)
		return false;

	return m_Controllers[controllerIdx]->IsDown(button);
}

void dae::InputManager::AddControllerCommand(const ControllerInput data, std::unique_ptr<Command> pCommand)
{
	if (m_ControllerCommands.find(data) != end(m_ControllerCommands))
	{
		m_ControllerCommands[data] = std::move(pCommand);
		return;
	}

	m_ControllerCommands.emplace(data, std::move(pCommand));
}

void dae::InputManager::AddController(int controllerIndex)
{
	m_Controllers.push_back(std::make_unique<XBox360Controller>(controllerIndex));
}

void dae::InputManager::AddKeyboardCommand(const KeyboardInput data, std::unique_ptr<Command> pCommand)
{
	std::pair<std::unique_ptr<Command>, bool> pair = { std::move(pCommand), false };

	if (m_KeyboardCommands.find(data) != end(m_KeyboardCommands))
	{
		m_KeyboardCommands[data] = std::move(pair);
		return;
	}

	m_KeyboardCommands.emplace(data, std::move(pair));
}

void dae::InputManager::ProcessKeyboardInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	for (auto& command : m_KeyboardCommands)
	{
		bool currentState = state[command.first.Key];

		switch (command.first.State)
		{
			case ButtonState::Pressed:
			{
				if (currentState && !command.second.second)
					command.second.first->Execute();
				break;
			}
			case ButtonState::Released:
			{
				if (!currentState && command.second.second)
					command.second.first->Execute();
				break;
			}
			case ButtonState::Down:
			{
				if (currentState && command.second.second)
					command.second.first->Execute();
				break;
			}
		}

		command.second.second = currentState;
	}
}