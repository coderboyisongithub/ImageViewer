
#ifndef _WIDGET_FILTER_RETRO
#define _WIDGET_FILTER_RETRO
#include "Filters.h"
#include "Widget_SliderInput.h"


//This headerfile implement UI for filter operators;;

class Widget_UI_Retro
{
	
	
	int min,max;
	
	ImageProcessor::Filters::Retro Retro_agent;
	Widget::SliderInput Retro_pannel;
	int saved_filter_strength;
	//widget flags...
	bool visible;
	bool intrrupt;
	
	//no-copy flags..
	bool kernel_size_updated;
	
public:
	Widget_UI_Retro()
	{
		min=0;max=50;

		visible=false;
		Retro_pannel=Widget::SliderInput("Retro","strength",min,max);
		intrrupt=false;
	}
	void processWith(unsigned char *image_input,int h,int w,int c)
	{
		Retro_agent.setimage(image_input,h,w,c);
		Retro_agent.process();

	}
	void render()
	{
		
		if(visible)
		{
			Retro_pannel.render();
		if(saved_filter_strength!=Retro_pannel.getvalue()) //intrrupted an update..
		{
			intrrupt=true;
			saved_filter_strength=Retro_pannel.getvalue();
			Retro_agent.setFilterStrength(saved_filter_strength);
			//Retro_agent.process();
		}
		else if(applyFilter()) //if user pressed apply button to apply filter thats also a kind of intrrupt..
		{
			
			intrrupt=true;
		}
		else{intrrupt=false;}
		
		//Retro_pannel.render(); dont destroy order of execution ...it will cause un-predictable malfunction..
		}

		else;	
	}
	unsigned char *getProcessed()
	{
		return Retro_agent.getimage();
	}
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
	void setVisiblity(bool _visiblity)
	{
		visible=_visiblity;
	}
	bool isVisible()
	{
		return visible;
	}
	bool hasintrrupted()
	{
		if(intrrupt==true)
		{intrrupt=false;return true;}
		else
			return false;
	}
	bool applyFilter()
	{
	
	return Retro_pannel.isApplyButtonpressed();
		
	}
};
#endif