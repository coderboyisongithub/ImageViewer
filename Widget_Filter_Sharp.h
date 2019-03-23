#ifndef _WIDGET_FILTER_SHARP_H
#define _WIDGET_FILTER_SHARP_H

#include "Filters.h"
#include "Widget_SliderInput.h"
/*
This headerfile combine user-interface and filter operation as one..so that user could..
apply filter via UI provided..
This class hold interaction with user and manage to implement filter operation over data
fed..
*/

class Widget_UI_Sharpness
{
	float min,max;
	ImageProcessor::Filters::Sharp Sharp_agent;
	Widget::SliderInput_float ui_pannel;
	//flags..
	bool visible;
	bool intrrupt;

	//accumulator..
	float saved_sharpness;
public:
	Widget_UI_Sharpness()
	{
			min=0; max=5.0;
			visible=false;
			intrrupt=false;
			ui_pannel=Widget::SliderInput_float(" ","Sharpness",0.0,5.0,"%0.5f");
			
	}
	bool applyFilter()
	{
		if(ui_pannel.isApplyButtonpressed())
			ui_pannel.setVal(0.0);

		return ui_pannel.isApplyButtonpressed();
		
	}
	void render()
	{
		if(visible)
		{
		ui_pannel.render();
		if(saved_sharpness!=ui_pannel.getvalue())
		{
			intrrupt=true;
			saved_sharpness=ui_pannel.getvalue();
			Sharp_agent.setSharpnessParameter(saved_sharpness);

		}
		else if(ui_pannel.isApplyButtonpressed())
		{
			intrrupt=true;
		}
		else
			intrrupt=false;
		}

	}

	bool hasintrrupted()

	{
		if(intrrupt)
		{
			intrrupt=false;
			return true;
		}
		else
			return intrrupt;

	}
	void processWith(unsigned char *image_input,int h,int w,int c)
	{
		Sharp_agent.setimage(image_input,h,w,c);
		Sharp_agent.process();
	
	}
	void setVisiblity(bool visible_)
	{
		visible=visible_;
	}
	unsigned char* getProcessed()
	{
		return Sharp_agent.getimage();
	}
	bool isVisible()
	{
		return visible;
	}
};

#endif