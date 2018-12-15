#ifndef _TIMERS_H
#define _TIMERS_H
#include "imgui.h"

class Timer
{
	float second_passed;
	float second_start;
	float reset_point;

	//timer flag;
	bool flag_active;
public:
	Timer()
	{
		second_passed=0.0;
		reset_point=0.0;
		second_start=0.0;
		flag_active=false;

	}
	void startTimer()
	{
	
	if(second_passed==second_start)
	{
		second_start=ImGui::GetTime();second_passed+=0.00000001;
	}
	else
	{
		second_passed=ImGui::GetTime()-second_start;
	}

	}
	void reset()
	{
		second_passed=0.0;
		second_start=reset_point;

	}

	float getTicks()
	{
		return second_passed;
	}
};
#endif