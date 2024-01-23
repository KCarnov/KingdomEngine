#pragma once


//#include "Hazel/Events/ApplicationEvent.h"
#include "Sources/Events/KeyEvent.h"
#include "Sources/Events/MouseEvent.h"


class ImGuiLayer 
{
public:
	ImGuiLayer();
	~ImGuiLayer() = default;

	void OnAttach();
	void OnDetach();
	void OnEvent(Event& e);

	void Begin();
	void ImGuiFrame();
	void End();

	void BlockEvents(bool block) { m_BlockEvents = block; }
		
	void SetDarkThemeColors();

private:
	bool m_BlockEvents = true;
};


