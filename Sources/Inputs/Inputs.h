#pragma once
#include "Sources/Application.h"


class Inputs {

public:
	static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); };
	static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); };

	static float GetMouseX() { return s_Instance->GetMouseXImpl(); };
	static float GetMouseY() { return s_Instance->GetMouseYImpl(); };

	static std::pair<float,float> GetMousePos() { return s_Instance->GetMousePosImpl(); };

protected:

	static bool IsKeyPressedImpl(int keycode);
	static bool IsMouseButtonPressedImpl(int button);
	static float GetMouseXImpl();
	static float GetMouseYImpl();
	static std::pair<float, float> GetMousePosImpl();
private:
	static Inputs* s_Instance;
};