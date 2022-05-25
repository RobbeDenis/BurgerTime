#pragma once
namespace dae
{
	class XBox360Controller final
	{
	public:
		enum class ControllerButton
		{
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000,
			ButtonUp = 0x0001,
			ButtonDown = 0x0002,
			ButtonLeft = 0x0004,
			ButtonRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftStick = 0x0040,
			RightStick = 0x0080,
			LeftBumper = 0x0100,
			RightBumper = 0x0200,
		};

		explicit XBox360Controller(int controllerIndex);
		~XBox360Controller();

		void ProcessInput();

		bool IsPressed(ControllerButton button) const;
		bool IsReleased(ControllerButton button) const;
		bool IsDown(ControllerButton button) const;

	private:
		class XBox360ControllerImpl;
		XBox360ControllerImpl* m_pImpl;
	};
}