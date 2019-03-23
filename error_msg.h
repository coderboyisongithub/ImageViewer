#pragma once
#include <stdio.h>

enum MsgType
{
	ERR,WARN,INFO
};
inline void  err_(const char *msg,MsgType t)
	{
		switch(t)
		{
		case MsgType::ERR:
			{
				printf("\n#ERROR!!#%s\n",msg);
				break;
			}
		case MsgType::WARN:
			{
				printf("\n#WARNNING!#:%s\n",msg);
				break;
			}
		case MsgType::INFO:
			{
				printf("\n#INFO#:%s\n",msg);
				break;
			}
		
		}
}