#ifndef img_view
#define img_view
#include <opencv2\opencv.hpp>
//#include "Filters.h"
//#include "Widget_SliderInput.h"
#include "Widget_Filter_Blur.h"
#include "Widget_Filter_Retro.h"
#include "Widget_Filter_Sharp.h"
#include "Widget_Filter_PaintRed.h"
#include "Widget_Filter_Teselate.h"
#include "Notifications.h"
#include <math.h>
#include "error_msg.h"
#include "Timer.h"
/*                         ...-+...+--
                          .=+.+.
                /\     .+.+..-
             ////\\\\-------
		   //////\\\\\\-----
         ////////\\\\\\\\  |
	   //////////\\\\\\\\\\
     ////////////\\\\\\\\\\\\
     [][][][][][][][][][][][]
	 [][][][][][][][][][][][]
	 [][][][]|	   |[]+  +[]]
	 [][][][]|	   |[]+  +[]]
	 [][][][]|	  o|[[][][][]
	 [][][][]|	   |[[][][][]
	 [][][][]|_____|[[][][][]
	 -----------------------

*/

class imageViewer
{
	char *wname;
	bool open;
	unsigned char *image;
	unsigned char *clone_;
	LIST_LINKED picture_list;
	unsigned int GPU_texture;
	unsigned char* buffer[3];
	int pl_size;			//picture list size;
	
	//Image Processors..
	Widget_UI_blur Blur;
	Widget_UI_Retro Retro;
	Widget_UI_Sharpness Sharp;
	Widget_UI_paintRed Artify;
	Widget_UI_Tesselate Tesselate;
	//window_Filters Filters;	
	DataMetric metricAnalyzer;
	Notification_Manager notifications;
	
	//##
	Timer navigation_button;
	float nav_button_Scalef;


	//flags 
	bool ready;
	bool _flag_gpu_installation;
	 
		bool filter_optionBlur;
		bool filter_optionRetro;
		bool filter_optionSharp;
		bool filter_optionartify;
		bool filter_optionTesselate;

	bool flag_filter_blur,flag_filter_retro,flag_filter_sharp,flag_filter_tesselate;
	bool model_window_flag;

	int index;	//index of picture list
	int w,h,c;
	float img_alpha;

	

	int value_int;
	void buff2GPU()
	{
		glBindTexture(GL_TEXTURE_2D,GPU_texture);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,GL_FALSE,GL_RGBA,GL_UNSIGNED_BYTE,image);
		glBindTexture(GL_TEXTURE_2D,0);
		
	}
	void buff2GPU(unsigned char *buffer)
	{
		
		glBindTexture(GL_TEXTURE_2D,GPU_texture);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,GL_FALSE,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
		glBindTexture(GL_TEXTURE_2D,0);
		
	}

	float getDiagonal(float x,float y)
	{
		return glm::sqrt(((x*x)+(y*y)));
	}

	void loadBuffer(int index)
	{
		//GPU upload protocall/...
		if(image!=NULL)
		{	stbi_image_free(image);
		image=NULL;
		}
		else;
		if(clone_!=NULL)
		{
			free(clone_);
				clone_=NULL;
		}
		else;
		linked_list *base=picture_list.get_Node(index);
		if(base!=NULL)
		{
		payload *p=(payload*)base->payload;

		//printf("\n\nindex:%d  requested nodes:%x",index,picture_list.get_Node(index));

		//Bitmap loading segment...

			stbi_set_flip_vertically_on_load(0);
			image=stbi_load(p->str,&w,&h,&c,4);
		
			int count=0;
	///////////////////////////////////////////////

			if(image)
			{
			printf("\nImage loaded height:%d width:%d channels:%d size:%d*%d blocks " ,h,w,c,sizeof(unsigned char),w*h*c);
			
			metricAnalyzer.uploadData(image,h,w,c,true);
			
			clone_=(unsigned char*)malloc(sizeof(unsigned char)*w*h*4);
			memcpy(clone_,image,sizeof(unsigned char)*w*h*4);
			
			buff2GPU(); //upload to GPU slot
			
			}
			
			else

			{
				 char *buff_=(char*)malloc(sizeof(char)*1024);
				sprintf(buff_,"imageViewer:loading failed::Cant read image due to undefined problems \n source:%s",p->str);
				err_(buff_,MsgType::WARN);
				if(count<picture_list.getsize())
				{
					err_("shifting next img buffer",MsgType::INFO);

					index++;
					loadBuffer(index);

				}
				else;

			}
		}
		

		else
		{
			printf("\n'list node invalid");
			return;
		}
		
	}
	//render routines for filter window ui_
	void Filter_Window()
	{
			
		float s_width=50,s_height=80;
		ImGui::Begin("Filters",&open);

			ImGui::PushStyleColor(ImGuiCol_FrameBg,ImVec4(0.2,0.2,0.2,0.2));
		ImGui::BeginGroup();
				if(ImGui::Selectable("B",&filter_optionBlur,ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowDoubleClick,ImVec2(s_height,s_width)))
				Blur.setVisiblity(filter_optionBlur);

				if(ImGui::Selectable("R",&filter_optionRetro,ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowDoubleClick,ImVec2(s_height,s_width)))
				Retro.setVisiblity(filter_optionRetro);
				
				if(ImGui::Selectable("S",&filter_optionSharp,ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowDoubleClick,ImVec2(s_height,s_width)))
					Sharp.setVisiblity(filter_optionSharp);
				
				if(ImGui::Selectable("Artify",&filter_optionartify,ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowDoubleClick,ImVec2(s_height,s_width)))
					Artify.setVisiblity(filter_optionartify);
				if(ImGui::Selectable("Tesselate",&filter_optionTesselate,ImGuiSelectableFlags_::ImGuiSelectableFlags_AllowDoubleClick,ImVec2(s_height,s_width)))
					Tesselate.setVisiblity(filter_optionTesselate);
				
				ImGui::EndGroup();

		ImGui::PopStyleColor();

			ImGui::End();
	}



	void startup_routines()
	{
		model_window_flag=false;
		_flag_gpu_installation=0;
		index=0;
		value_int=1.0;
		img_alpha=0.0;

		//animation variable..
		nav_button_Scalef=0.90;

		 filter_optionBlur=false;
		filter_optionRetro=false;
		filter_optionSharp=false;
		
	}
public:
	imageViewer()
	{
		open=false;
		ready=false;
		image=NULL;
		startup_routines();

	}
	imageViewer(std::string name)
	{
		wname=(char*)malloc(sizeof(char)*(name.length()+1));
		strcpy_s(wname,sizeof(char)*(name.length()+1),name.c_str());
		open=true;
		ready=true;
		value_int=1.0;
		startup_routines();
		
	
	}
	void render()
	{
		ImGui::PushStyleColor(ImGuiCol_Border,ImVec4(0.2,0.2,0.2,0.8));
		ImGui::PushStyleColor(ImGuiCol_Button,ImVec4(0.2,0.2,0.2,0.1));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive,ImVec4(0.2,0.2,0.2,0.8));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered,ImVec4(0.1,0.1,0.1,0.8));
		
		notifications.render();

		if(ready)
		{
			
			ImGui::Begin(wname,&open,ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
			
		ImGui::BeginGroup();
		ImGuiID id=ImGui::GetCurrentWindow()->GetID(wname,NULL);
		
		
		//ImGui::ShowMetricsWindow(&open);
		
		//Image viwer menu bar...
static bool sel=false;
static bool insight_ =true;

		if(ImGui::BeginMenuBar())
		{
			if(ImGui::BeginMenu("File"))
			{
				if(ImGui::Button("save"))
			ImGui::OpenPopup("save_");	
				
	if(ImGui::BeginPopupModal("save_",NULL))
					{
		
						static char *savename=(char*)malloc(sizeof(char)*512);
						savename[0]='\0';
						ImGui::InputText("name",savename,sizeof(char)*512);
						
						ImGui::Text("%s.jpg",savename);
						
							if(ImGui::Button("ok"))
							{
								cv::Mat saveimg(h,w,CV_8UC4,image);
								std::vector<int>compression_param;
								compression_param.push_back(CV_IMWRITE_PNG_COMPRESSION);
								compression_param.push_back(9);
								cv::imwrite(savename,saveimg,compression_param);
								//cv::imwrite("hello",saveimg);
								ImGui::CloseCurrentPopup();
								
								
				
							}

							ImGui::EndPopup();
					}
				ImGui::EndMenu();
				
			}

			
			if(ImGui::BeginMenu("Tools"))
			{
		
			if(ImGui::MenuItem("Filters",NULL,&sel))
			{
			}
			
			if(ImGui::MenuItem("Insight",NULL,metricAnalyzer.getVisiblity()))
				{
					
				}
				ImGui::EndMenu();
			}
			
		ImGui::EndMenuBar();
		}
	
		
	ImGui::GetCurrentWindow()->DC.CursorPos.x+=ImGui::GetCurrentWindow()->Size.x/2-100;
	ImGui::BeginGroup();
	if(ImGui::Button("<",ImVec2(nav_button_Scalef*100,nav_button_Scalef*100)))
		{
			if(index==0)
			{
				notifications.pushNotification("No Image"); 
			}
			else
			{
			index--;
			loadBuffer(index);
			//notifications.pushNotification("prev image");
			img_alpha=0.0;
			}
		}
		else;
		ImGui::SameLine();
		
		
		if(ImGui::Button(">",ImVec2(nav_button_Scalef*100,nav_button_Scalef*100)))
		{
			if(index==pl_size)
			{notifications.pushNotification("No more Image.. :-(");}

			else
			{
			index++;
			loadBuffer(index);
			img_alpha=0.0;
			}
		}
		else;
		ImGui::EndGroup();
		float speed=20.0;
		if(ImGui::IsItemHovered())
		{
			navigation_button.startTimer();
		nav_button_Scalef=glm::max<float>(0.90,glm::tanh(navigation_button.getTicks()*speed));
		}
		else
		{
			navigation_button.reset();
			nav_button_Scalef=0.90;

		}
	
		
		

		if(!picture_list.isEmpty())
		{
			
			

		//if(image!=NULL)
		//stbi_image_free(image);

	ImTextureID imID=(void*)GPU_texture;
float aspect_ratio=0.1/0.1;
//float diag=getDiagonal(ImGui::GetCurrentWindow()->Size.x,ImGui::GetCurrentWindow()->Size.y);
float diag=getDiagonal(ImGui::GetCurrentWindow()->Size.y,ImGui::GetCurrentWindow()->Size.x);
float capture=0.40; //cover area of image(%)
float DAR=(diag*capture)/(diag*capture); //display aspect ratio..
float SAR=(float)((float)w/(float)h); //stored aspect ratio
float height=SAR; 
float width=DAR;

ImGui::Image(imID,ImVec2(height*(diag*capture),width*(diag*capture)),ImVec2(0,0),ImVec2(1.0,1.0),ImVec4(1,1,1,img_alpha));

		}
		
		else;

	
		ImGui::EndGroup();
		

		ImGui::End();


		
		

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

			if(image!=NULL)
			{
				ImageProcessor::Filters::ChannelMixer ch;

				ch.setImage(image,h,w,c);

					if(sel)
			Filter_Window();
	          else ;

				if(img_alpha<1.0)
	img_alpha+=0.05;
					if(Blur.isVisible())
					{
					
					if(Blur.hasintrrupted())
					{

						Blur.processWith(image,h,w,c); //upload mem-block which contains image..
						
						if(Blur.filterApply())
						{
							//printf("\nover~writing orignal memoryblock at :%x by block at %x",image,Blur.getProcessed());
							memcpy(image,Blur.getProcessed(),sizeof(unsigned char)*w*h*4);
							
						}
						else
						{
							memcpy(clone_,Blur.getProcessed(),sizeof(unsigned char)*w*h*4); //retrive data from image processor..The processed image...
							
						}
						
						buff2GPU(clone_);
						metricAnalyzer.uploadData(clone_,h,w,c);


					}
					Blur.render();
					}

					else;

				if(Retro.isVisible())
				{
						
					if(Retro.hasintrrupted()) //user logged an update..to re-process with new input parameters
					{
						
						Retro.processWith(image,h,w,c);
					
						if(Retro.applyFilter())
						{
						memcpy(image,Retro.getProcessed(),sizeof(unsigned char)*w*h*4);
						}

						else
					{
						memcpy(clone_,Retro.getProcessed(),sizeof(unsigned char)*w*h*4); //creating a copy of processed image to clone_
					}
					buff2GPU(clone_); //uploading image to GPU buffer..
					metricAnalyzer.uploadData(Retro.getProcessed(),h,w,c); //uploading data for Insight..

					
					}
					Retro.render();			

				}
				if(Sharp.isVisible())
				{
					
					
					Sharp.render();
				if(Sharp.hasintrrupted())
				{
					
					Sharp.processWith(image,h,w,c);
					if(Sharp.applyFilter())
					{
						memcpy(image,Sharp.getProcessed(),sizeof(unsigned char)*h*w*4);
						
					}
					else
					{memcpy(clone_,Sharp.getProcessed(),sizeof(unsigned char)*h*w*4);}

				buff2GPU(clone_);
				metricAnalyzer.uploadData(clone_,h,w,c); //uploading data for Insight..
				}

				}
				if(Artify.isVisible())
				{
					
					Artify.render();
					if(Artify.hasintrrupted())
					{
						Artify.processWith(image,h,w,c);	
						if(Artify.applyFilter())
							{memcpy(image,Artify.getProcessed(),sizeof(unsigned char)*h*w*4);
						}
						else
						{
						memcpy(clone_,Artify.getProcessed(),sizeof(unsigned char)*h*w*4);
						}
						buff2GPU(clone_);
						metricAnalyzer.uploadData(clone_,h,w,c); //uploading data for Insight..

					}
					else;
				

				}
				if(Tesselate.isVisible())
				{
					Tesselate.render();
					if(Tesselate.hasintrrupted())
					{
						

						
						Tesselate.processWith(image,h,w,c);
						if(Tesselate.filterApply())
						{
							
							uchar *memblock=Tesselate.getProcessed();
							if(memblock!=NULL)
							memcpy(image,Tesselate.getProcessed(),sizeof(unsigned char)*h*w*4);
							else
								;
						}
						else
						{
							uchar* memblock=Tesselate.getProcessed();
							if(memblock!=NULL)
								memcpy(clone_,memblock,sizeof(unsigned char)*h*w*4);
							else
								;

						}
						buff2GPU(clone_);
						metricAnalyzer.uploadData(clone_,h,w,c); //uploading data for Insight..
					}
				}
				
				
				metricAnalyzer.render();
			} 
			else;
	
		
	
		
		
		ImGui::PopStyleColor(4);
		


		}
	
		else
		{
			printf("\nImageViewer::system not ready..:(");

			abort(); //program NOT ready..
			}
		
	}

	void setImage(unsigned char *image_src)
	{
		image=image_src;
			
	}
	bool uploadList(LIST_LINKED src_upld_list)
	{
		puts("list uploaded..");
		if(!src_upld_list.isEmpty())
		{
			if(picture_list.isEmpty())
			picture_list.destroy();
			else;
			src_upld_list.copyTo(picture_list);
			index=0;
		loadBuffer(index);
		pl_size=picture_list.getsize();
		return true;
		}

		else
			return true;
		
	}
	void setupGPUmemory()
	{
		glGenTextures(1,&GPU_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,GPU_texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,0);
		_flag_gpu_installation=1;
	}
	

};

#endif