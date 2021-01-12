

#ifndef SHDR_PARSOR
#define SHDR_PARSOR

using namespace std;


struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class shader_processor
{
	unsigned int ID; //shader program...
	 //parameters stored for debugging...
	int shader_bind_status;
	
	/// @brief /////////////////////////
	

	std::string shaderfile;
	enum class ShaderType
	{
		NONE= -1,VERTEX=0,FRAGMENT=1
	};

	ShaderProgramSource glslParsor(std::string shader_file)
{
	
fstream file(shader_file.c_str(),ios::in);
assert(file.is_open()!=false);

	
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
		ShaderProgramSource source=glslParsor(shaderfile);

		//std::cout<<"vertex\n"<<source.vertexSource.c_str()<<"\n"<<source.fragmentSource.c_str();

		ID=createShader(source.vertexSource,source.fragmentSource);
		ready=true;
	}
	
	unsigned int  createShader(std::string& vertex_source, std::string& fragment_source)
	{

		//vertex_shader..
		unsigned int vs, fs; //shader id
		const char* data = vertex_source.c_str(); //updating with vertex shader script...


		GLERR();
		vs = glCreateShader(GL_VERTEX_SHADER);

glShaderSource(vs, 1, &data, NULL);
glCompileShader(vs);
		
		int status_vertex;
glGetShaderiv(vs, GL_COMPILE_STATUS, &status_vertex);
		if (status_vertex == GL_FALSE)
		{

			char buffer[2048];
			int size;
			glGetShaderiv(vs, GL_BUFFER_SIZE, &size);
			printf("buffer size:%d", size);
			glGetShaderInfoLog(vs, sizeof(buffer), NULL, buffer);
			printf("!ERROR::SHADER(VERTEX)::COMPILATION FAILED::failure parameters..\n%s", buffer);
			abort();
		}
		else;
		//fragment shader construction..
		int status_frag;
		data = fragment_source.c_str(); //updating with fragment shader source..

fs = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fs, 1, &data, NULL);
glCompileShader(fs);

			glGetShaderiv(fs, GL_COMPILE_STATUS, &status_frag);
			if (status_frag == GL_FALSE)
			{

				char buffer[2048];
				glGetShaderInfoLog(fs, sizeof(buffer), NULL, buffer);
				printf("!ERROR::SHADER(FRAGMENT)::COMPILATION FAILED::failure parameters..\n%s", buffer);
				abort();
			}
			else;

		unsigned int GPU_program = glCreateProgram();
	
glAttachShader(GPU_program, vs); //vertex shader attachment


glAttachShader(GPU_program, fs); 


			GLint program_link,program_validation;
glLinkProgram(GPU_program);
			{
				glGetProgramiv(GPU_program, GL_LINK_STATUS, &program_link);
				if (program_link == GL_FALSE)
				{
					char buffer[2048];
					glGetProgramInfoLog(GPU_program, sizeof(char) * 2048, NULL, buffer);
					printf("!ERROR::SHADER::LINKING FAILED::failure parameters..\n%s", buffer);
					abort();
				}
				else;
			}
glValidateProgram(GPU_program);
	
			{
				glGetProgramiv(GPU_program, GL_LINK_STATUS, &program_validation);
				if (program_validation == GL_FALSE)
				{
					char buffer[2048];
					glGetProgramInfoLog(GPU_program, sizeof(char) * 2048, NULL, buffer);
					printf("!ERROR::SHADER::VALIDATION FAILED::failure parameters..\n%s", buffer);
					abort();

				}
			}

			return GPU_program; //return shader program (compiled,validated and linked..)

}



	unsigned int getUniformLoc(std::string uniform)
	{
		bind();
		
		unsigned int location=glGetUniformLocation(ID,uniform.c_str());
		GLERR();
		if (shader_bind_status == 0)
		{
			printf("\nWARRNING!::SHADER TRYING TO BE OPERATED MAY NOT BE BOUND/ATTACHED WITH CURRENT OPENGL CONTEXT.\n");
		}
		_ASSERT(location!=-1);
		
		return location;
	}

	void setUniform1i(std::string uniform, int v0)
	{
		bind();
		unsigned int location = getUniformLoc(uniform);
		glUniform1i(location, v0);
		GLERR();
		unbind();
	}
	void setUniform1f(std::string uniform,float v0)
	{
		bind();
		
		unsigned int location=getUniformLoc(uniform);
		glUniform1f(location,v0);
		GLERR();
		unbind();

	}
	void setUniformvec4f(std::string uniform,glm::vec4 v)
	{
		bind();
		unsigned int loc=getUniformLoc(uniform);
		glUniform4f(loc,v.x,v.y,v.z,v.w);
		GLERR();
		unbind();


	}

	void setUniformat4x4(std::string uniform,float *data,GLboolean transpose=GL_FALSE)
	{
		bind();
		unsigned int location=getUniformLoc(uniform);
		glUniformMatrix4fv(location,1,transpose,data);
		GLERR();
	}
	void bind()
	{
		if (ready)
		{
			glUseProgram(ID);
			glGetIntegerv(GL_CURRENT_PROGRAM, &shader_bind_status);
			assert(shader_bind_status != 0); //if shader binding fails..

		}
		else 
		{
			printf("!ERROR::SHADER::SHADER NOT READY..");
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
