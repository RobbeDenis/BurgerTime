#include "RodEnginePCH.h"
#include "InputManager.h"
#include "SceneManager.h"

dae::InputManager::~InputManager()
{
	m_Commands.erase(begin(m_Commands), end(m_Commands));
}

bool dae::InputManager::ProcessInput()
{
	if (m_Skip)
	{
		m_Skip = false;
		return true;
	}

	const int sceneIdx = SceneManager::GetInstance().GetSceneIdx();

	for (const std::unique_ptr<XBox360Controller>& controller : m_Controllers)
	{
		controller->ProcessInput();

		for (auto& command : m_Commands[sceneIdx]->first)
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

void dae::InputManager::AddControllerCommand(const ControllerInput data, std::unique_ptr<Command> pCommand, const int sceneIdx)
{
	if (m_Commands[sceneIdx]->first.find(data) != end(m_Commands[sceneIdx]->first))
	{
		m_Commands[sceneIdx]->first[data] = std::move(pCommand);
		return;
	}

	m_Commands[sceneIdx]->first.emplace(data, std::move(pCommand));
}

void dae::InputManager::AddController(int controllerIndex)
{
	m_Controllers.push_back(std::make_unique<XBox360Controller>(controllerIndex));
}

void dae::InputManager::AddKeyboardCommand(const KeyboardInput data, std::unique_ptr<Command> pCommand, const int sceneIdx)
{
	std::pair<std::unique_ptr<Command>, bool> pair = { std::move(pCommand), false };

	if (m_Commands[sceneIdx]->second.find(data) != end(m_Commands[sceneIdx]->second))
	{
		m_Commands[sceneIdx]->second[data] = std::move(pair);
		return;
	}

	m_Commands[sceneIdx]->second.emplace(data, std::move(pair));
}

void dae::InputManager::ProcessKeyboardInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	const int sceneIdx = SceneManager::GetInstance().GetSceneIdx();

	for (auto& command : m_Commands[sceneIdx]->second)
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

void dae::InputManager::AddNewSceneCommands()
{
	ControllerCommandsMap ccmap{};
	KeyboardCommandsMap kcmap{};
	SceneCommands* pair = new SceneCommands{ std::move(ccmap),  std::move(kcmap) };
	m_Commands.push_back(std::move(pair));
}

void dae::InputManager::Reset()
{


	m_Skip = true;
}