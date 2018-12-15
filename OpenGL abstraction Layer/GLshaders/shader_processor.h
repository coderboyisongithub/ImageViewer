
#ifndef SHDR_PHRASOR
#define SHDR_PHRASOR


using namespace std;


struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class shader_processor
{
	unsigned int ID; //shader program...
	std::string shaderfile;
	ShaderProgramSource glslPrasor(std::string shader_file)
{
	
	fstream file(shader_file.c_str(),ios::in);

	enum class ShaderType
	{
		NONE= -1,VERTEX=0,FRAGMENT=1
	};

string line;
stringstream ss[2];
ShaderType shader=ShaderType::NONE;

while(getline(file,line))
{
	if(line.find("#shader") !=string::npos)
	{
	if(line.find("vertex")!=string::npos)
		shader=ShaderType::VERTEX;
	else if(line.find("fragment")!=string::npos)
		shader=ShaderType::FRAGMENT;
	}
	else
	{
		ss[(int)shader]<<line<<"\n";
	}
}
	
ShaderProgramSource Source_control;
Source_control.vertexSource=ss[0].str();
Source_control.fragmentSource=ss[1].str();

//std::cout<<"\nvertex source\n"<<ss[0].str()<<"\nfrag\n"<<ss[1].str();

return Source_control;
}

	//flags
	bool ready;

public:
	shader_processor()
	{
		ID=NULL;
		ready=false;
	}

	shader_processor(std::string shaderpath)
	{
		shaderfile=std::string(shaderpath);
		ShaderProgramSource source=glslPrasor(shaderfile);

		//std::cout<<"vertex\n"<<source.vertexSource.c_str()<<"\n"<<source.fragmentSource.c_str();

		ID=createShader(source.vertexSource,source.fragmentSource);
		ready=true;
	}
	unsigned int  createShader(std::string &vertex_source,std::string &fragment_source)
{

	//vertex_shader..
	unsigned int vs,fs; //shader id
	const char *data=vertex_source.c_str(); //updating with vertex shader script...
	
	vs=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs,1,&data,NULL);
	glCompileShader(vs);
	 int status_vertex;
	glGetShaderiv(vs,GL_COMPILE_STATUS,&status_vertex);
	if(status_vertex==GL_FALSE)
	{

		char buffer[2048];
		int size;
		glGetShaderiv(vs,GL_BUFFER_SIZE,&size);
		printf("buffer size:%d",size);
		glGetShaderInfoLog(vs,sizeof(buffer),NULL,buffer);
		printf("!ERROR::SHADER(VERTEX)::COMPILATION FAILED::failure parameters..\n%s",buffer);
	}
	else
	{
	}
	//fragment shader construction..
	int status_frag;
	data=fragment_source.c_str(); //updating with fragment shader source..

	fs=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs,1,&data,NULL);
	glCompileShader(fs);
	glGetShaderiv(fs,GL_COMPILE_STATUS,&status_frag);
	if(status_frag==GL_FALSE)
	{

		char buffer[2048];
		glGetShaderInfoLog(fs,sizeof(buffer),NULL,buffer);
		printf("!ERROR::SHADER(FRAGMENT)::COMPILATION FAILED::failure parameters..\n%s",buffer);
	}
	else
	{
	}

	unsigned int GPU_program=glCreateProgram();
	glAttachShader(GPU_program,vs); //vertex shader attachment
	glAttachShader(GPU_program,fs);  //fragmetn shader attachment

	//experimental..
	glLinkProgram(GPU_program);
	glValidateProgram(GPU_program);



	return GPU_program; //return shader program (compiled,validated and linked..)

}



	unsigned int getUniformLoc(std::string uniform)
	{
		bind();
		
		unsigned int location=glGetUniformLocation(ID,uniform.c_str());
		_ASSERT(location!=-1);
		//unbind();
		return location;
	}

	void setUniform1i(std::string uniform,int v0)
	{
		bind();
		unsigned int location=getUniformLoc(uniform);
		glUniform1i(location,v0);
	}
	void setUniform1f(std::string uniform,float v0)
	{
		bind();
		
		unsigned int location=getUniformLoc(uniform);
		glUniform1f(location,v0);

		//unbind();

	}

	void setUniformat4x4(std::string uniform,float *data)
	{
		bind();
		unsigned int location=getUniformLoc(uniform);
		glUniformMatrix4fv(location,1,GL_FALSE,data)	;
	}
	void bind()
	{
		if(ready)
		glUseProgram(ID);
		
		else 
		{
			printf("!ERROR::SHADER BINDING FAILURE::SHADER NOT READY..");
			abort();
		}
		
	}
	void unbind()
	{
		glUseProgram(0);
	}

	unsigned int getProgram()
	{
		return ID;
	}
};
#endif
