#ifndef ENTRY_PANNEL
#define ENTRY_PANNEL
#include <iostream>
#include <imgui_internal.h>
#include "DirectoryPhrasor.h"
#include <string.h>
#include "Timer.h"


class Dialoge_directory
{
	const char *filePath;
	const char *D;
	const char *Wname;
	const char *oldText;
	bool status;

	DirectoryPhrasor Turtle;

	//flags
	bool list_status;
	bool list_updated;


	//timers..
	Timer timer_okbtn,timer_inptxt;
	
	float okbtn_scale_factor;
	float inptxt_frame_rounding_factor;
	void animation_parameters()
	{
		okbtn_scale_factor=0.30;
	inptxt_frame_rounding_factor=0.0;
	}
public:
Dialoge_directory()
{
	filePath=NULL;
	Wname=NULL;
	status=false;
	list_status=false;
	list_updated=false;
	//UI elements
	animation_parameters();

}

Dialoge_directory(std::string window_name)
{
	//filePath=( char*)malloc(sizeof(char)*PathVariable.length());
	//strcpy_s((char*)filePath,sizeof(filePath),(char*)PathVariable.c_str());
	Wname=(char*)malloc(sizeof(char)*window_name.length()+1);
	assert(Wname!=NULL);
	strcpy_s((char*)Wname,sizeof(Wname),(char*)window_name.c_str());
	
	D=(char*)malloc(sizeof(char)*1024);
	assert(D!=NULL);
	oldText=(char*)malloc(sizeof(char)*1024);
	assert(oldText!=NULL);
	for(int loop=0;loop<1024;loop++)
	{
		(char)D[loop]=NULL;
		(char)oldText[loop]=NULL;
	}
	status=false;
	list_status=false;
	list_updated=false;

	//UI elements
	animation_parameters();

}


bool Getstatus()
{
	return status;
}

void render()
{
	ImGuiStyle &style=ImGui::GetStyle();

	ImGui::Begin((char*)Wname,&status);
	ImGui::BeginGroup();

	ImGui::PushStyleColor(ImGuiCol_Border,ImGui::GetColorU32(ImVec4(0.2,0.2,0.2,1.0)));
	ImGui::PushStyleColor(ImGuiCol_FrameBg,ImGui::GetColorU32(ImVec4(0.2,0.2,0.2,1.0)));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,inptxt_frame_rounding_factor*30.0);	 
	

	ImGui::BeginChild("entryPoint",ImVec2(0,100),true,ImGuiWindowFlags_::ImGuiWindowFlags_ChildWindow);
	ImGui::BeginGroup();
	ImGui::InputText("directory",(char*)D,sizeof(char)*1024,0);
	ImGui::EndGroup();
	if(ImGui::IsItemActive())
	{
		timer_inptxt.startTimer();
		inptxt_frame_rounding_factor=glm::tanh(timer_inptxt.getTicks());
	}
	else
	{
		timer_inptxt.reset();
		inptxt_frame_rounding_factor=0.1;
	}
	
	ImGuiID id=ImGui::GetCurrentWindow()->GetID(Wname);
	bool s=true;
	ImGui::Textview(id,D);
	/*
	ImRect text_box(ImVec2(ImGui::GetCurrentWindow()->DC.CursorPos.x,ImGui::GetCurrentWindow()->DC.CursorPos.y),ImVec2(ImGui::GetCurrentWindow()->DC.CursorPos.x+(0.5*ImGui::GetCurrentWindow()->Size.x) , ImGui::GetCurrentWindow()->DC.CursorPos.y + (0.25*ImGui::GetCurrentWindow()->Size.y)));
	bool textregion_hover;
	ImGui::ButtonBehavior(text_box,id,&textregion_hover,NULL,0);
	ImGui::GetCurrentWindow()->DrawListInst.AddRect(text_box.Min,text_box.Max,ImGui::GetColorU32(ImVec4(0.2,0.2,0.2,0.2)));
	//the tool tip!>
	if(textregion_hover)
	{
		ImGui::BeginTooltip();
		ImGui::Text("%s",D);
		ImGui::EndTooltip();
	}
	else;

	

	ImVec2 text_size=ImGui::CalcTextSize(D,NULL);
	ImGui::RenderTextClipped(text_box.Min,text_box.Max,D,NULL,NULL);
	*/

	ImGui::EndChild();
	ImGui::PopStyleColor(2);
	ImGui::PopStyleVar(1);
	ImGui::EndGroup();
	ImGui::PushStyleColor(ImGuiCol_Button,ImGui::GetColorU32(ImVec4(0.2,0.2,0.2,1.0)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered,ImGui::GetColorU32(ImVec4(0.2,0.2,0.2,okbtn_scale_factor*0.5)));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive,ImGui::GetColorU32(ImVec4(0.2,0.2,0.2,0.8)));
	float size_upper=min(0.25*ImGui::GetCurrentWindow()->Size.x,80.0);
	float size_lower=max(size_upper,30.0);
	float size=max(size_upper,size_lower);

	ImGui::BeginGroup();
	if(ImGui::Button("ok",ImVec2(okbtn_scale_factor*size,okbtn_scale_factor*30)))
	{
		LIST_LINKED list;
	if(strcmp(oldText,D)!=0) //if new request 
	{
	//	printf("\nnew request");
		strcpy((char*)oldText,D); 
		Turtle.setDir(std::string(D));
		if(Turtle.wasRequestValid())
		{
			list_updated=true;  //list updated..
		}
		else;
	}
	else;
	//printf("list prer...\n\n");
	//list.viewAll(true);		
	}
	else;
	ImGui::EndGroup();

	 if(ImGui::IsItemHovered())
	 {
		 timer_okbtn.startTimer();
		 okbtn_scale_factor=glm::max<float>(0.85,glm::tanh(timer_okbtn.getTicks()*30.0));
	 }
	 else
	 {
		 timer_okbtn.reset();
		 okbtn_scale_factor=0.85;

	 }
	ImGui::PopStyleColor(3);
	ImGui::End();
	status=true;
}

void getList(LIST_LINKED &tmp)
{
	
	if(!Turtle.stack.isEmpty())
	{
			if(!tmp.isEmpty())
			{
				tmp.destroy(); //refresh list
				
				return;
			}
			
			else;

	

	while(!Turtle.stack.isEmpty())
		{
			//printf("\n(before insertion )list()->node pointer:%x list->self pointer:%x",tmp.list,tmp.list->my);
			//printf("\nheader node:%x self pointer:%x",tmp.list,tmp.list->my);
			tmp.insert(Turtle.stack.pop());
			//printf("\nTURTLE::list:size:%d",tmp.getsize());
			//printf("\n(after insertion)list()->node pointer:%x list->self pointer:%x",tmp.list,tmp.list->my);
			

		
		}
	
	list_updated=false;
	}
	else
		return;

}
bool anyUpdate()
{
	return list_updated;
}

};

#endif 