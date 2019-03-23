// image.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LunchBox.h"



/*
					Mr.owl says
			    __/\_____/\___
			   /              \
			  /  ___     ___   \    _____________________
			  |  \_/     \_/   |   /Don't Dare to copy ! |
			  |	     ;f;       |  /______________________|
			   \\            //
			   / \ _______ /  \
			  / 			   \
			 //    \\\///      \\
			///    ///\\\      \\\
		   /////             \\\\\\
		  ////////////\\\\\\\\\\\\\\
		 ////////////  \\\\\\\\\\\\\\
		/////////\\\\  /////\\\\\\\\\\
	   ////////\\\\\\\////////\\\\\\\\\
	  ///////   \\\\\\///////  \\\\\\\\\
	 /////       \\\\\//////       \\\\\\
	              {}      {}  
			 }{{}}}{}}  {}}{}{{}{
		  

*/

GLFWwindow *Window;
Index_buffer ib;
Vertex_Buffer vb;
shader_processor sh;
Object_2D box;
ImGuiContext *maincontext;
Dialoge_directory widget("Open");
imageViewer im("viewer");



LIST_LINKED lst;


unsigned int TexID;
unsigned char* openglTexBuff;
    unsigned char* tex_pixels = NULL;
float POS[]=
{
	-1.0,-1.0,-2.0,
	1.0,-1.0,-2.0,
	1.0,1.0,-2.0,
	-1.0,1.0,-2.0
};

float texCoords[] = {
			0.0,0.0,
			1.0,0.0,
			1.0,1.0,
			0.0,1.0
};

unsigned int index[]={
	0,1,2,
	2,3,0
};

float scale_x=1.0,scale_y=1.0,translate_X=0.0,translate_Y=0.0,translate_Z=0.0;
float val=0.0;
float translation[]={
		scale_x,0,0,0,

		0,scale_y,0,0,

		0,0,1,0,

		translate_X,translate_Y,translate_Z,1
	
};


float rotation_arr[]=
{
	sin(val),cos(val),0,0,
	cos(val),sin(val),0,0,
	0,0,1,0,
	0,0,0,1  

};





void Display()
{
	

static float color=0.0;

	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


	
	box.shader.setUniformat4x4("translation_matrix",translation);
	box.shader.setUniformat4x4("rotation_matrix",rotation_arr);
	
	//box.shader.setUniform1f("col",glm::sin(t.getTicks()));

	
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,TexID);
box.shader.setUniform1f("col",1.0);
box.shader.setUniform1i("a_texture",0);
box.render();




ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowRounding,0.0);

widget.render();
if(widget.anyUpdate()) //if list updated..then retrive list..
	{
	widget.getList(lst);
	im.uploadList(lst);			
	}
else;	

	im.render();


	ImGui::PopStyleVar();

	/*
	x=rcos$
	y=rsin$

	*/

	glFlush();


}

void EnginInit()
{
	//depth functions..
	
	//glEnable(GL_TEXTURE_2D);

	IMGUI_CHECKVERSION();
	maincontext=ImGui::CreateContext();
	ImGui::SetCurrentContext(maincontext);
	ImGuiIO &io=ImGui::GetIO();
	
    int tex_w, tex_h;
	//io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);
	io.Fonts->AddFontFromFileTTF("RobotoCondensed-Bold.ttf",15.0,NULL);
	
	io.WantTextInput=true;
	
	vb=Vertex_Buffer(POS,4*3*sizeof(float),0,3,1);
	ib=Index_buffer(index,3*2*sizeof(unsigned int),1);
	sh=shader_processor(std::string("shader.glsl"));
	box=Object_2D(vb,ib,sh,GL_TRIANGLES);
	
	int h,w,c;
	stbi_set_flip_vertically_on_load(1);
	openglTexBuff=stbi_load("brick.jpg",&w,&h,&c,4);
	glGenTextures(1,&TexID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,TexID);	
		
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,512,512,GL_FALSE,GL_RGBA,GL_UNSIGNED_BYTE,openglTexBuff);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
	if(openglTexBuff!=NULL)stbi_image_free(openglTexBuff);

	im.setupGPUmemory();

	
	//s.loadImage(std::string("C:\\Users\\Overclock\\Desktop\\star war ART.jpg"));
}


void ImGuiRender()
{
	bool status=true;
	
}
void main()
{
	

	/*
	Spidy..
			-||-           -||-
            -||            -||-                          
            -\\-  ((  ))  -//-
			 -\\-// 01 \\-//-
			    |0  1  0| -
                \0101010/- 
          =======|01010|=======
				/0101001\-
           -//-|101000100|-\\-
          -//- \\\\01////- -\\-
         -||-      \/       -||-
         -||-               -||-

	*/

	if(!glfwInit())
	{

		abort();
	}
	Window=glfwCreateWindow(1224,786,"Window",NULL,NULL);
	if(!Window)
	{
		abort();
	}
	glfwMakeContextCurrent(Window);
	glfwSwapInterval(1);
	glewInit();
 EnginInit(); //
 ImGui_ImplGlfwGL3_Init(Window,true,NULL);
 

	while(!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();
		{
			ImGuiRender();
		}

		Display();
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(Window);

	}

}