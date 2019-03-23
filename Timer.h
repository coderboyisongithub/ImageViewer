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
	void calculate_time()
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
	
		flag_active=true;
		calculate_time();
	}
	void reset()
	{
		second_passed=0.0;
		second_start=reset_point;
		flag_active=false;

	}

	bool isActive()
	{
		return flag_active;
	}
	float getTicks()
	{
	
		if(flag_active)
		{
			calculate_time();
			return second_passed;
		}
		else
			return 0.0f;
	}
};
#endif