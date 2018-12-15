#ifndef _SLIDER_INPUT_H
#define _SLIDER_INPUT_H
#include "imgui.h"

namespace Widget
{
	class SliderInput
	{
		int slider_value;
		char slidername[20],widget_name[512];
		int min_val,max_val,val,saved_val;
		
		
		bool open;
		bool button_pressed;

	void reset_parameters()
	{
		button_pressed=false;
	}
	public:
		SliderInput()
		{
			open=true;
			button_pressed=false;
			val=0;

		}
		SliderInput(char slider_text[20],char widget_[512],int min,int max)
		{
			strcpy_s(slidername,slider_text);
			strcpy_s(widget_name,widget_);
			min_val=min;
			max_val=max;
			val=0;
			button_pressed=false;

		}
		void render()
		{
			
		reset_parameters();//reset every stuff before rendering every fucking.....


			ImGui::PushStyleColor(ImGuiCol_TitleBgActive,ImVec4(0.1,0.1,0.1,1.0));
			ImGui::Begin(widget_name,&open);
			
			ImGui::BeginGroup();
			ImGui::PushStyleColor(ImGuiCol_FrameBg,ImVec4(0.2,0.2,0.2,0.8));
			ImGui::PushStyleColor(ImGuiCol_SliderGrab,ImVec4(0.2,0.2,0.2,1.0));
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,ImVec4(0.1,0.1,0.1,1.0));
			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,ImVec4(0.5,0.5,0.5,1.0));
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive,ImVec4(0.1,0.1,0.1,1.0));


			ImGui::SliderInt(slidername,&val,min_val,max_val);//slider...
			if(ImGui::Button("Apply"))
			{
				button_pressed=true;
			}
			else;
			
			ImGui::PopStyleColor(5);
			ImGui::EndGroup();
			if(saved_val!=val)
		{
				saved_val=val;
			if(ImGui::IsItemHovered())
			{
				
			}
			else;
		}
			else;
		
			ImGui::End();
			ImGui::PopStyleColor();
		}
		int getvalue()
		{
			return val;
		}
		void setVal(int v0)
		{
			val=v0;

		}
		bool isApplyButtonpressed()
		{
				return button_pressed;
			
		}

	};
	class SliderInput_float
	{
	float slider_value;
		char slidername[20],widget_name[512];
		float min_val,max_val,val,saved_val;
		char decimal_format[5];
		
		bool open;
		bool button_pressed;


	void reset_parameters()
	{
		button_pressed=false;
		
	}
	public:
		SliderInput_float()
		{
			open=true;
			button_pressed=false;
			val=0;
			strcpy(decimal_format,"%.3f");

		}
		SliderInput_float(char slider_text[20],char widget_[512],float min,float max,char _decimal_format[5])
		{
			strcpy(slidername,slider_text);
			strcpy(widget_name,widget_);
			strcpy(decimal_format,_decimal_format);

			min_val=min;
			max_val=max;
			val=0;
			button_pressed=false;

		}
		void render()
		{
			
		reset_parameters();//reset every stuff before rendering every fucking.....


			ImGui::PushStyleColor(ImGuiCol_TitleBgActive,ImVec4(0.1,0.1,0.1,1.0));
			ImGui::Begin(widget_name,&open);
			
			ImGui::BeginGroup();
			ImGui::PushStyleColor(ImGuiCol_FrameBg,ImVec4(0.2,0.2,0.2,0.8));
			ImGui::PushStyleColor(ImGuiCol_SliderGrab,ImVec4(0.2,0.2,0.2,1.0));
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,ImVec4(0.1,0.1,0.1,1.0));
			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,ImVec4(0.5,0.5,0.5,1.0));
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive,ImVec4(0.1,0.1,0.1,1.0));


			ImGui::SliderFloat(slidername,&val,min_val,max_val,decimal_format);//slider...
			if(ImGui::Button("Apply"))
			{
				button_pressed=true;
			}
			else;
			
			ImGui::PopStyleColor(5);
			ImGui::EndGroup();
			if(saved_val!=val)
		{
				saved_val=val;
			if(ImGui::IsItemHovered())
			{
				
			}
			else;
		}
			else;
		
			ImGui::End();
			ImGui::PopStyleColor();
		}
		float getvalue()
		{
			return val;
		}
		void setVal(float v0)
		{
			val=v0;

		}
		void setStep(float step)
		{
			step*=1000;
			int step_extracted=(int)step;
			char buffer[10];
			char buffer2[15]="%.";
			sprintf(buffer,"%df",step_extracted);
			strcat(buffer2,buffer);
			strcpy(decimal_format,buffer2);
			return;
		}
		bool isApplyButtonpressed()
		{
		
				return button_pressed;
			
		}

	};

};


#endif