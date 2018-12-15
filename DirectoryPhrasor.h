#ifndef D_F_
#define D_F_

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include <dirent.h>
#include <iostream>
#define MAX 512 

/*
struct payload
{
	char *str;
};
*/
class DirectoryPhrasor
{


DIR *wd;
dirent *dd; //directory discriptor..
char *filePath;
payload *data;


int pathSize;

//flags
bool ready;
bool stack_ready;
bool request_validity;

bool genList()
{
	if((wd=opendir(filePath))!=NULL) //if path is valid
	{
		//clear stack BUFFER..

		stack.clearStack();
		while((dd=readdir(wd))!=NULL)
		{
			if(dd->d_type==DT_REG)
		{
		//printf("\n%s",dd->d_name);

	/*	data=(payload*)malloc(sizeof(payload));
		
		data->d_ata=(char*)malloc(sizeof(char)*(dd->d_namlen+1));
		strcpy_s(data->d_ata,(sizeof(char)*(dd->d_namlen+1)),dd->d_name);

		stack.push((void*)data);

		payload *test=(payload*)stack.pop();

		printf("%s",test->d_ata);

		*/
			//extension detection..

			char *ptr=dd->d_name;
			while(*ptr!='\0')
			{
					
				if(*ptr=='.')
				{
					ptr++;
					static char extension[5];
					char *ep=extension;
					while(*ptr!='\0' || *ptr==' ')
					{
						*ep=*ptr;

						ptr++;
						ep++;
					}
					*ep='\0';

					//printf("%s",extension);
					if((strcmp(extension,"jpg"))==0 ||(strcmp(extension,"jpeg"))==0)
					{
						data=(payload*)malloc(sizeof(payload));
						data->str=(char*)malloc(dd->d_namlen+2+pathSize);
						strcpy_s(data->str,(sizeof(char)*(dd->d_namlen+2+pathSize)),filePath);
						strncat(data->str,"/",pathSize);
						strcat(data->str,dd->d_name);
						stack.push((void*)data);
						//printf("\n%s stacks::%d",data->str,stack.get_stack());
						stack.viewStack();


					}
					else
					break;

					break;
				}
				ptr++;

				//printf("%c",*ptr);


			}

		}
		else
			continue;
		
	}
		stack_ready=true;
		ready=true;
		return true;
	}
	else
	{
		printf("!!ERROR::illegal_dir");
		
		//flags..
		stack_ready=false;
		ready=false;
	
		return false;



	}

	

}

void resetFilevar()
{
	if(filePath!=NULL){
	free(filePath);
	filePath=NULL;
	stack_ready=false;
	}
	else
		return;
}
public:


STACK_CHILD stack;



DirectoryPhrasor()
{
	filePath=NULL;
	ready=false;
	stack_ready=false;
}

DirectoryPhrasor(std::string filePath_)
{
	if(filePath_.length()>0)
	{
		pathSize=(filePath_.length()+1);
		filePath=(char*)malloc(sizeof(char)*pathSize);
	
	strcpy_s(filePath,sizeof(char)*(filePath_.length()+1),filePath_.c_str());
	request_validity=genList();
	ready=true;
	stack_ready=true;
	}
	else if(strcmp(filePath_.c_str(), " ")==0)
	{
		ready=false;
		stack_ready=false;
	}
}

void setDir(std::string filePath_)
{
	if(filePath==NULL)
	{
	pathSize=(filePath_.length()+1);
	filePath=(char*)malloc(sizeof(char)*pathSize);
	strcpy_s(filePath,(sizeof(char)*pathSize),(char*)filePath_.c_str());
	bool status=genList();
	request_validity=status;
	if(status==false)
		resetFilevar();
	}
	else
	
	{
		free(filePath);
	pathSize=(filePath_.length()+1);
	filePath=(char*)malloc(sizeof(char)*pathSize);
		strcpy_s(filePath,(sizeof(char)*pathSize),(char*)filePath_.c_str());
		bool status=genList();
		request_validity=status;
		if(status=false)
		resetFilevar();
	}
}

bool wasRequestValid()
{
	return request_validity;
}
/*bool stackReady()
{
	return stack_ready;
}
*/
};

#endif

