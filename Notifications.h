#pragma once
#include <imgui.h>
#include "list.h"
#include "Timer.h"
#include "windowContext.h"


class Notification_Manager
{
	bool open;
	bool notificationPush;
	STACK_CHILD notification_stack; //notification stack..
	Timer t;						//timer..
	char *data;						//data casted to void,held in stack 
	//context-flags
	bool active;
	window_context ctx;

	
	ImVec2 window_pos;

public:
	Notification_Manager()
	{
		active=false;
		open=true;
		notificationPush=false;
		notification_stack=STACK_CHILD();

		ctx.generate_and_imply_default_settings();
	}
void render()
{
	
	if(!notification_stack.isEmpty())
	{
		t.startTimer();
		notificationPush=true;
	}

	if(t.isActive())
	{
		int count =0;
		if(notificationPush)
		{
		
		data=(char*)notification_stack.pop();
			notificationPush=false;
		}
		else;


		ImGui::SetNextWindowPos(ctx.win_pos);
		ImGui::SetNextWindowBgAlpha(ctx.bg_alfa);
		ImGui::SetNextWindowSize(ctx.win_size);
		ImGui::Begin("overlay_notification",&open,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_Tooltip);
			ImGui::Textview(ImGui::GetCurrentWindow()->ID,data);
			
		ImGui::End();

		if(t.getTicks()>2.0)
			t.reset();
		else;
	}
}



void pushNotification(char msg[1024])
	{
		data=(char*)malloc(sizeof(char)*1024);
			strcpy_s(data,1024,msg);
		notification_stack.push((void*)data);
		notificationPush=true;
	}
	~Notification_Manager()
	{

	}
};