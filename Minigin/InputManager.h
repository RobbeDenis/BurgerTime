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
		Down
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

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		~InputManager();

		void AddControllerCommand(const ControllerInput data, std::unique_ptr<Command> pCommand);
		void AddController(int controllerIndex);

		bool IsPressed(XBox360Controller::ControllerButton button, unsigned int controllerIdx = 0) const;
		bool IsReleased(XBox360Controller::ControllerButton button, unsigned int controllerIdx = 0) const;
		bool IsDown(XBox360Controller::ControllerButton button, unsigned int controllerIdx = 0) const;

	private:
		using ControllerCommandsMap = std::unordered_map<ControllerInput, std::unique_ptr<Command>, ControllerInputHasher>;
		ControllerCommandsMap m_ControllerCommands{};
		std::vector<std::unique_ptr<XBox360Controller>> m_Controllers{};
	};
}