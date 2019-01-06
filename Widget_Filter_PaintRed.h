#ifndef _WIDGET_PAINT_RED_UI
#define _WIDGET_PAINT_RED_UI
#include "Filters.h"
#include "Widget_SliderInput.h"

class Widget_UI_paintRed
{
	int min,max;
	ImageProcessor::Filters::Paint_Red filter_agent;
	Widget::SliderInput ui_pannel;
	bool visible;
	bool intrrupt;
	int saved_filter_param;
public:
	Widget_UI_paintRed()
	{
		min=0;
		max=140;
		intrrupt=false;
		ui_pannel=Widget::SliderInput("effect","Artify",min,max);

	}
	void render()
	{
		if(visible)
		{
			ui_pannel.render();
			if(saved_filter_param!=ui_pannel.getvalue())

			{
				intrrupt=true;
				saved_filter_param=ui_pannel.getvalue();
				filter_agent.setvalue(saved_filter_param);

			}

			else if(ui_pannel.isApplyButtonpressed())
			{
				intrrupt=true;
			}
			else
				{intrrupt=false;}
		}
		else return;
	}
	bool isVisible()
	{
	return visible;

	}
	bool applyFilter()
	{
		return ui_pannel.isApplyButtonpressed();
	}
	void processWith(unsigned char *image_input,int h,int w,int c)
	{
	filter_agent.setimage(image_input,h,w,c);
	filter_agent.process();
	}
	bool hasintrrupted()
	{
		if(intrrupt==true)
			{intrrupt=false;
		return true;}
		else
			return false;

	}
	void setVisiblity(bool visiblity)
	{
		visible=visiblity;
	}
	unsigned char* getProcessed()
	{
	return filter_agent.getimage();
	}
	
	
};
#endif