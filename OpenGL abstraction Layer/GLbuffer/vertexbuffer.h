#ifndef VERTEX_
#define VERTEX_

class Vertex_Buffer
{
	unsigned int  ID;
	float *vertex_data;
	//buffer difinition variables..

	int as_used;	 //buffer used for ::default value GL_STATIC_DRAW;..
	int as_binded;	 //buffer binded for what?::default value GL_ARRAY_BUFFER
	int bCount;		 //number of buffer created..
	 int bsize;		//elements in buffer..total no of vertices..

	//flags
	bool ready;
public:
Vertex_Buffer()
	{
		ID=NULL;
		vertex_data=NULL;
		bCount=0;
		bsize=0;

		ready=false;


	}

Vertex_Buffer(float *aData,int aSize,int aindex,int vertex_comp,int buffCount,int use_as=GL_STATIC_DRAW,int bind_as=GL_ARRAY_BUFFER)
	{


as_used=use_as;
as_binded=bind_as;
bCount=buffCount;
bsize=aSize;

	glGenBuffers(1,&ID);
	glBindBuffer(bind_as,ID);
	glBufferData(bind_as,aSize,aData,use_as);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(bind_as,0);

	ready=true;

	}

	void bind()
	{
		if(status())
		{glBindBuffer(as_binded,ID);}
		else
		{
			printf("\n!ERROR::VERTEX BUFFER::BIND FAILURE~::#BUFFER NOT READY..");
			abort();
		}

	
	}

	void unbind()
	{
		if(status())
		{glBindBuffer(as_binded,0);}
		else
		{
			printf("\n!ERROR::VERTEX BUFFER::UN-BIND FAILURE~::#BUFFER NOT READY..");
			abort();

		}

	}

int getSize()
	{
		return bsize;
	}

bool status()
	{
	//check weather object is in  position of being used..
		return ready;
	}

	unsigned int getID()
	{
		return ID;
	}
};
#endif