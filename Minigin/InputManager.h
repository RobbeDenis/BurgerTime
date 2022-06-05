#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include "Command.h"
#include "XBox360Controller.h"

namespace dae
{
	enum class ButtonState
	{
		Pressed,
		Released,
		Down,
		Inactive
	};

	struct ControllerInput
	{
		using CButton = XBox360Controller::ControllerButton;
		CButton Button{};
		ButtonState State = ButtonState::Pressed;

		ControllerInput(CButton button, ButtonState state)
			: Button{ button }
			, State{ state }{}

		bool operator==(const ControllerInput& other) const
		{
			return (Button == other.Button) && (State == other.State);
		}
	};

	struct ControllerInputHasher
	{
		std::size_t operator() (const ControllerInput& data) const
		{
			std::size_t button = std::hash<unsigned int>()(static_cast<unsigned int>(data.Button));
			std::size_t state = std::hash<unsigned int>()(static_cast<unsigned int>(data.State));

			return button ^ state;
		}
	};

	struct KeyboardInput
	{
		SDL_Scancode Key = SDL_SCANCODE_0;
		ButtonState State = ButtonState::Pressed;

		KeyboardInput(const SDL_Scancode key, const ButtonState state)
			: Key{ key }
			, State{ state }{}

		bool operator==(const KeyboardInput& other) const
		{
			return (Key == other.Key) && (State == other.State);
		}
	};

	struct KeyboardInputHasher
	{
		std::size_t operator() (const KeyboardInput& data) const
		{
			std::size_t key = std::hash<unsigned int>()(static_cast<unsigned int>(data.Key));
			std::size_t state = std::hash<unsigned int>()(static_cast<unsigned int>(data.State));

			return key ^ state;
		}
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		~InputManager();

		void AddControllerCommand(const ControllerInput data, std::unique_ptr<Command> pCommand, const int sceneIdx);
		void AddController(int controllerIndex);

		bool IsPressed(XBox360Controller::ControllerButton button, unsigned int controllerIdx = 0) const;
		bool IsReleased(XBox360Controller::ControllerButton button, unsigned int controllerIdx = 0) const;
		bool IsDown(XBox360Controller::ControllerButton button, unsigned int controllerIdx = 0) const;

		void AddKeyboardCommand(const KeyboardInput data, std::unique_ptr<Command> pCommand, const int sceneIdx);

		void AddNewSceneCommands();

	private:
		using ControllerCommandsMap = std::unordered_map<ControllerInput, std::unique_ptr<Command>, ControllerInputHasher>;
		using KeyboardCommandsMap = std::unordered_map<KeyboardInput, std::pair<std::unique_ptr<Command>, bool>, KeyboardInputHasher>;
		using SceneCommands = std::pair<ControllerCommandsMap, KeyboardCommandsMap>;
		std::vector<SceneCommands*> m_Commands{};

		std::vector<std::unique_ptr<XBox360Controller>> m_Controllers{};
		void ProcessKeyboardInput();
	};
}