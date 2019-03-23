#pragma once
#define WINDOW_CONTEXT_CONFIGURATION_1_POINT_O

#include <imgui.h>

enum StateVariable
{
	ACTIVE_=1,
	DE_ACTIVE=2
};


struct window_context
{
	ImVec2 win_pos;					 //window_position
	ImVec2 win_size;					//window_Size
	StateVariable win_state;			//window states..

	float bg_alfa;						//background alfa value;

	bool focused;
	void generate_and_imply_default_settings()
	{
		win_pos=ImVec2(10,10);
		win_state=StateVariable::DE_ACTIVE;
		bg_alfa=0.8;
		win_size=ImVec2(300,30);
		focused=false;
	}

};

