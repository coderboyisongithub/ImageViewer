#ifndef INDEX_
#define INDEX_

class Index_buffer
{
	unsigned int ID;
	unsigned int *indices;

	//index defenition parameters..
	int as_used;
	int as_binded;
	int buffer_count;
	int buffer_size;
	
	//flags
	bool ready;

public:

	Index_buffer()
	{
		ID=NULL;
		indices=NULL;
		buffer_size=NULL;
		ready=false;
	}


Index_buffer(unsigned int *aIndex,int aSize,int bCount,int bind_as=GL_ELEMENT_ARRAY_BUFFER,int use_as=GL_STATIC_DRAW )
	{
		as_used=use_as;
		as_binded=bind_as;
		buffer_count=bCount;
		buffer_size=aSize;
		indices=aIndex;
		
	glGenBuffers(bCount,&ID);
	glBindBuffer(bind_as,ID);
	glBufferData(bind_as,aSize,aIndex,use_as);
	glBindBuffer(bind_as,0);
	ready=true;
	}
/*
Index_buffer(Index_buffer &src)
	{
		as_used=src.as_used;
		as_binded=src.as_binded;
		buffer_count=src.buffer_count;
		buffer_size=src.buffer_size;
		indices=src.indices;


		glGenBuffers(buffer_count,&ID);
	glBindBuffer(as_binded,ID);
	glBufferData(as_binded,buffer_size,indices,as_used);
	glBindBuffer(as_binded ,0);
	}
	*/
	void bind()
	{
		
		if(status()==false)
		{
			printf("\n!!ERROR::INDEX_BUFFER::BIND FAILURE~::#BUFFER NOT INITLIZED.. :(");
			abort();

		}
		else
		{
		glBindBuffer(as_binded,ID);
		}

	}

	int getSize()
	{
		return buffer_size;
	}
	void unbind()
	{

		if(status()==false)
		{
			printf("\n!!ERROR::INDEX_BUFFER::UN-BIND FAILURE~::#BUFFER NOT INITLIZED.. :(");
			abort();

		}
		else
		{
			glBindBuffer(as_binded,0);
		}

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