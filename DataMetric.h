#ifndef _img_metric
#define _img_metric
#include <imgui.h>
#include "Timer.h"
#include "Filters.h"
#include <glm.hpp>

/*
This headerfile implements as info pannel to user about current data being
displayed or used (image)...Showing whole digital profile of data including 
important information..

*/




/*
			-||-           -||-
            -||            -||-                          
            -\\   ((  ))  -//-
			 -\\ // 01 \\-//-
			    |0  1  0| -
                \0101010/- 
          =======|01010|=======
				/0101001\-
           -//-|101000100|-\\-
          -//- \\\\01////- -\\-
         -||-      \/       -||-
         -||-               -||-

	*/


class DataMetric
{
	char window_name[256];

	float window_alpha;

	//
	unsigned char *image;
	int h,w,c;
	char metric_buffer[1024];


	//animation and timing 

	float time,start,a;
	//////////histogram variable..
	float *hist_r,*hist_g,*hist_b;
	float plot_h,plot_w;
	//window flags..
	bool open;

	//ui state
	bool visiblity;
	bool hovered;
	bool histogram_header;
	bool initialized;


	Timer t;
protected:
	void setHistogramparameter()
	{
		hist_r=hist_g=hist_b=NULL;
		plot_h=50;
		plot_w=0;
		histogram_header=false;
		time=0.0;
		a=0.0;
		

	}

public:
	DataMetric()
	{
		open=true;
		image=NULL;
		window_alpha=0.0;
		visiblity=true;
		setHistogramparameter();
		initialized=true;
	}
	DataMetric(char name_window[256])
	{
		strcpy(window_name,name_window);
		open=true;
		window_alpha=0.0;
		image=NULL;
		visiblity=true;
		setHistogramparameter();
		initialized=true;
	}

	void render()
	{
		if(visiblity)
		{
		if(image!=NULL)
		{
						ImGui::PushStyleColor(ImGuiCol_Text,ImVec4(0.5,0.5,0.5,1));
						ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,ImVec4(0.3,0.3,0.3,0.8));
						ImGui::PushStyleColor(ImGuiCol_FrameBgActive,ImVec4(0.3,0.3,0.3,0.2));
						ImGui::PushStyleColor(ImGuiCol_SliderGrab,ImVec4(0.5,0.5,0.5,0.2));
						ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,ImVec4(0.5,0.5,0.5,0.5));

ImGui::Begin("metric",&open);
float data_size=(float)(sizeof(unsigned char)* 4 *(h*w)/8);
float compression_ratio=(h*w)/data_size;
sprintf(metric_buffer,"height:%dpx \n\nwidth:%dpx \n\nchannel:%d \n\n Size~ %.3f.B\n Compression Ratio:%.3f ",h,w,c,data_size,compression_ratio);
ImGuiID id=ImGui::GetCurrentWindow()->GetID("metric");
ImGui::Textview(id,metric_buffer,0.75);


		
ImGui::PushStyleColor(ImGuiCol_FrameBg,ImVec4(0.2,0.2,0.2,0.2));
					ImGui::BeginGroup();				
					ImGui::SliderFloat("plot scale",&plot_h,40.0f,100.0f);
					ImGui::PushStyleColor(ImGuiCol_FrameBg,ImVec4(0.3,0.3,0.3,a*0.2));
		
					//---------Histogram-------
					
					ImGui::PushStyleColor(ImGuiCol_PlotHistogram,ImVec4(0.8,0.2,0.2,a));
					ImGui::PlotHistogram("R",hist_r,256,0,NULL,0.0,FLT_MAX,ImVec2(plot_w,a*plot_h));
		
					ImGui::PushStyleColor(ImGuiCol_PlotHistogram,ImVec4(0.2,0.8,0.2,a));
					ImGui::PlotHistogram("G",hist_g,256,0,NULL,0.0,FLT_MAX,ImVec2(plot_w,a*plot_h));

					ImGui::PushStyleColor(ImGuiCol_PlotHistogram,ImVec4(0.2,0.2,0.8,a));
					ImGui::PlotHistogram("B",hist_b,256,0,NULL,0.0,FLT_MAX,ImVec2(plot_w,a*plot_h));
					ImGui::EndGroup();
					
					if(ImGui::IsItemHovered())
					{
							t.startTimer();
						a=glm::max<float>(0.50,tanh(t.getTicks()*10.0));
						
						
					}
					else
					{
						t.reset();
						a=0.50;
					}

					ImGui::PopStyleColor(5);

	ImGui::End(); 
	ImGui::PopStyleColor(5);

		}
		else
			;
		}
	}
	void uploadData(unsigned char *buffer,int height,int width,int channel)
	{
		image=buffer;
		h=height;
		w=width;
		c=channel;
		if(hist_b!=NULL)
			free(hist_b);hist_b=NULL;
		if(hist_r!=NULL)
			free(hist_r);hist_r=NULL;
		
		if(hist_g!=NULL)
			free(hist_g);hist_g=NULL;
		
		float *H_pkg=ImageProcessor::DataAbstractor::histogram(image,h,w);

	 hist_r=(float*)malloc(sizeof(float)*256);
	 hist_g=(float*)malloc(sizeof(float)*256);
	 hist_b=(float*)malloc(sizeof(float)*256);
		for(int loop=0;loop<255;loop++)
		{
			hist_r[loop]=H_pkg[loop];
			hist_g[loop]=H_pkg[loop+256];
			hist_b[loop]=H_pkg[loop+(255*2)+1];
			//printf("%f %f %f\n",H_pkg[loop],H_pkg[loop+256],H_pkg[loop+(255*2)+1]);
		}

	}

	void setVisiblity(bool visible)
	{
		
		visiblity=visible;
	}
	bool *getVisiblity()
	{
		return &visiblity;
	}


};
#endif