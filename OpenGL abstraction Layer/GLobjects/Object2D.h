#ifndef OBJECT_2D
#define OBJECT_2D

class Object_2D
{
	
	glm::vec4 color;
	//rendering parameters..
	int render_As;

	
public:
	Vertex_Buffer vertices;
	Index_buffer indices;
	shader_processor shader;

	Object_2D()
	{
		
	}
	Object_2D(Vertex_Buffer _vb,Index_buffer _ib,shader_processor sh,int render_as=GL_TRIANGLES)
	{
		vertices=Vertex_Buffer(_vb);
		indices=Index_buffer(_ib);
		shader=shader_processor(sh);
		render_As=render_as;
	}
	/*
////////////\\\\\\
///////|0|||||||///
///////|||||||||//
///////||||//////
///////||||\\\\\\\
///////||0||||||\\\\
///////|||||||||||\\\
///////|||||\\\\\\\\\\
///////||||||||\\\\\\\
///////||0||//////////
///////|1||||//////////
///////||||||///////
/////||||1|||///////
//|||||0|||1|||||///
//|1||||||||1||||///
/||||||    |||||0|///
/||0||       |||||///
/||||         |1||///
/|1|||       ||||||///
/||||||     |||||||///
/||0||||||||0|||||///
//|||||1|||||||1|///
::::::::::::::::::::
*/





	void render()
	{
		vertices.bind();
		indices.bind();
		shader.bind();
		
		glDrawElements(render_As,vertices.getSize(),GL_UNSIGNED_INT,NULL);
		vertices.unbind();
		indices.unbind();
		
	}
	void setRenderType(int render_type)
	{
		render_As=render_type;
	}
	void transllate(float x,float y)
	{
		
	}
	
};
#endif	