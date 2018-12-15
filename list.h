#ifndef LIST_
#define LIST_

#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>


#define FLUSH_ free();
#define FOOD_ int;

struct payload
{
	char *str;
};

struct linked_list
{
	void *payload;
	linked_list *next,*prev,*my;
linked_list* attach_next(void *src)
{
	
	if(my->next!=NULL)
		{printf("restricted node creation..bridge already occupied!!");
	exit(0);
	}
	else{

		my->next=(linked_list*)malloc(sizeof(linked_list));
		my->next->prev=my;
		my->next->next=NULL;
		my->next->my=my->next;
		my->next->payload=src;
		return my->next;
	}
	}
linked_list* get_root()
{
	linked_list *tmp=my;while(tmp->prev!=NULL){tmp=tmp->prev;}return tmp;
}
linked_list *get_tip()
{
	linked_list *tmp=my;while(tmp->next!=NULL){tmp=tmp->next;}return tmp;
}
void kill(linked_list *target)
{
	if(target!=NULL)
	{
		linked_list *t=search(target);
		if(t!=NULL) //means if target found in list..
		{
			//time to verify weather target is on root node or tip or b/w some where..
			if(t->next==NULL &&t->prev!=NULL)//tip node...
			{
				t->prev->next=t->next;
				linked_list* target_node=t->get_root();
				free(t);
			}
			else if(t->next!=NULL &&t->prev!=NULL) //centernode
			{
				t->prev->next=t->next;
				t->next->prev=t->prev;
				free(t);
			}
			else if(t->prev==NULL) //root node....
			{
			return;
			}
		}
		else
			puts("!!TARGET NOT FOUND IN LIST TO KILL..");return;
	}
	else
	{
		puts("\n!!CANT KILL NULL POINTER\n");return;
	}

}
linked_list* search(linked_list *target)
{
	linked_list *dummyPtr=(linked_list*)(get_root());
	while(dummyPtr!=NULL)
	{
		if(dummyPtr==target)
		{
			return dummyPtr; //if found..

		}
		else
			dummyPtr=dummyPtr->next;
	}
	return NULL; //if not found...
}
};
linked_list* init_List()
{
	linked_list *ref;
	ref=(linked_list*)malloc(sizeof(linked_list));
	ref->my=ref;
	ref->payload=NULL;
	ref->next=NULL;
	ref->prev=NULL;
	return ref;

}
class LIST_LINKED
{
	
	int nodes;

	
void copyNode(linked_list *dst,linked_list *src)
	{
		dst->my=src->my;
		dst->next=src->next;
		dst->payload=src->payload;
		dst->prev=src->prev;

		printf("\nLIST_LINKED::cpynode()->self ptr:%p payload ptr:%p self-next ptr:%p",src->my,src->payload,src->next);
		return;

	}

public:
	linked_list *list,*root;
	LIST_LINKED()
	{
		list=init_List();
		root=list;
		nodes=1;
	}

	linked_list *get_Node( int index)
{
	if(index<0)
	{
		printf("\nLIST_LINKED::OPERATOR::get_Node()->!!wrong argument (index < 0)");
		abort();
	}

	else if(index>getsize())
		return NULL;
	else
	{
		linked_list *tmp=getFirstNode();
		for(int iter=0;iter<index;iter++)
		{
			
			tmp=tmp->next;
		}
		return tmp;
	}
}

	void copyTo(LIST_LINKED &dest)
	{
		if(!dest.isEmpty())
		{
			dest.destroy();
		}
		linked_list *iter=getFirstNode();
		
		printf("\n\nCPY::FUNC\n");
		while(dest.getsize()!=getsize())
		{
			dest.insert(iter->payload);
			payload *dat=(payload*)dest.list->payload;
			printf("%s\n",dat->str);
			iter=iter->next;

		}
	}
	
void insert(void *food)
	{
		if(food!=NULL){
		list=list->attach_next(food);
		nodes+=1;}
		else
			{puts("null pointer cant be listed..");
		return;}
	}
	linked_list *getFirstNode()
	{
		return (list->get_root()->next);
	}
	int getsize()
	{
		return (nodes-1);
	}
void destroy()
	{
		printf("\n\n FUNCTION DESTROY CALLED..");
		if(list->next==NULL && list->prev==NULL)
		{
			puts("\nLIST_LINKED::OPERATION::destroy()->list empty ...nothing to destroy");
			return;
		}

		while(getsize()!=0)
		{
#pragma warning(suppress: 6273)
			printf("\nLIST_LINKED::OPERATION::destroy()-> list node mem block:0x%x size remaining(%d)",list,getsize());

			list=list->prev;
			free(list->next);
			list->next=NULL;
			nodes-=1;

		}
#pragma warning(suppress: 6273)
		printf("\nseed node block:%x list r/w header node:%x",root,list);
		/*copyNode(list,dummyPtr);
		list=dummyPtr;
		*/
		
	//	printf("\n\n data::lost%x %x %x",list,root,dummyPtr);

		printf("\nremaining nodes:%d list seed block :0x%x",getsize(),root);
		//printf("\n\nlist data::%x",list->next);
	}
	void viewAll(bool newline)
	{
		linked_list *dummyPtr=root;
		if(newline==false)
		while(dummyPtr!=NULL)
		{
			//printf("||tree NODE:0x%x # list NODE:0x%x|||==>",dummyPtr->payload,dummyPtr->my);
			dummyPtr=dummyPtr->next;
		}
		else
			while(dummyPtr!=NULL)
		{
#pragma warning(suppress: 6273)
			printf("|tree NODE:0x%x # list NODE:0x%x||",dummyPtr->payload,dummyPtr->my);
			printf("\n || \n");printf(" \\/ \n");
			dummyPtr=dummyPtr->next;
		}
		printf("XXXNULL");
	}
	bool isEmpty()
	{
		return (getsize()==0 ? true:false);
	}
	
};

class STACK_CHILD
{
	linked_list *top;
	int stacks;
	linked_list* get_end()
	{
		linked_list *dummyPtr=top;
		while(dummyPtr->prev!=NULL)
		{
			dummyPtr=dummyPtr->prev;
		}
		return dummyPtr;

	}
public:
	STACK_CHILD()
	{
	top=init_List();
	//printf("\n0x%x",top);
	stacks=1;
	}
	
	void push(void *link)
	{
		linked_list* tmp=init_List();
		tmp->payload=link; //link to payload..
		tmp->prev=top;  //backlink
		top=tmp;
		stacks+=1;
	}
	void* pop()
	{
		void *tmp;
		tmp=top->payload;
		
		/*payload *data=(payload*)tmp;
		printf("\ndata :%s",data->str);
		*/

		linked_list *iter=top;
		if(top->prev!=NULL)
				{
				top=top->prev;  //mov to prev node
				//printf("\n0x%x",iter);
				free(iter);
				//puts("payload deleted");
				stacks-=1;
				return tmp;
				}
		else
			{puts("STACK::OPERATION::pop()->null exception in stack operation...");
		
			if(top->payload!=NULL)
				{free(top->payload);
				top->payload=NULL;
				}
		top->next=top->prev=NULL;
		}

	}
	void invert()
	{
		STACK_CHILD *stack;
		linked_list *list_buffer=(linked_list*)malloc(sizeof(linked_list)*stacks),*dummyPtr=top;
		for(int i=0;i<stacks;i++)
		{
			list_buffer[i].payload=pop();
		}
		for(int i=(stacks-1);i<=0;i--)
		{
			push(list_buffer[i].payload);
		}
	}
	void viewStack()
	{
		if(top->prev==NULL && top->next==NULL) //first stack payload ...no data member further..
		{
			puts("STACK::OPERATION::viewstack()->!error----stack empty..");
			return;
		}
		else
		{
		linked_list *dummyPtr=top;
		do
		{
#pragma warning(suppress: 6273)
			printf("\nSTACK::OPERATION::viewstack()->stack element (payload)mem block.:0x%x stack node at:0x%3x",dummyPtr->payload,dummyPtr);
			dummyPtr=dummyPtr->prev;
		}while(dummyPtr->next!=NULL);
	}
	}
	int get_stack()
	{ return (stacks-1);}
	void clearStack()
	{
		if(!isEmpty())
		{ 
			while(get_stack()!=0)
			{
				pop();
			}
		}
		else
		{
			printf("\nSTACK::OPERATION::clearstack()->stack is empty");
			return ;
		}
	}

	bool isEmpty()
	{
		return (get_stack()==0 ? true:false);
	}

};
/*
struct N_ARYTREE
{
	long long int data; //int key
	int number_of_friends; //total no of neighbour
	N_ARYTREE *my,*parent;
	linked_list *friends,*root;
	N_ARYTREE* allocator()
	{
	N_ARYTREE * tmp=(N_ARYTREE*)malloc(sizeof(N_ARYTREE));
	tmp->my=tmp;
	tmp->friends=init_List();
	tmp->root=tmp->friends; //setup root pointer...
	tmp->parent=NULL;
	tmp->data=0;
	tmp->number_of_friends=0;
	return tmp;
	}
	
	void attach_friend(int food)
	{
		N_ARYTREE *tmp=allocator(); //new friend allocated..
		//time to attach with list...
		my->friends=my->friends->attach_next(tmp);
		my->friends->pointer->data=food;
		my->friends->pointer->parent=my; // set parent pointer to friends...
		my->number_of_friends+=1;
		//friend attached to list..
	}

	void traverse_relations( N_ARYTREE *parent)
	{
		clock_t fire=clock(),end;
	
		int traversals=0;
		//visit root node an stack all its friends...
		N_ARYTREE *dummyPtr=parent;
		STACK_CHILD stack;
		linked_list *list=dummyPtr->root->next;
			printf("\nstacks:%d\n",stack.get_stack());
		//check for friends..
hell:
		while(list!=NULL)
		{
			printf("\npushing friends pointer: 0x%x to stack dummyRoot: 0x%x",list->pointer,dummyPtr->my);
			stack.push(list->pointer);
			list=list->next;
			
		}
	printf("\nstacks:%d\n",stack.get_stack());
		while(stack.get_stack()!=0)
		{dummyPtr=stack.pop();
		printf(" dummy pointer location:0x%x location data:%d",dummyPtr->my,dummyPtr->data);
		traversals+=1;
		if(dummyPtr->root->next!=NULL)
		{list=dummyPtr->root->next;
		goto hell;}
		else
			goto hell;
		}
	
		end=clock();
		printf("time taken in traversal:%f sec..",(double)(end-fire)/CLOCKS_PER_SEC);

			printf("\n %d traversal(TOTAL) done",(traversals+1));
		
	}
	linked_list* searchFriend(N_ARYTREE *target)
	{N_ARYTREE *base=my;
		linked_list *list=base->root->next;
		int pos=1;
		while(list!=base->friends)
		{
			if(list->pointer==target)
			{
				return list;
			}
			else
			{
			list=list->next;
			pos+=1;

			}

		}
		return NULL;
	}
	void killFriend(N_ARYTREE *target)
	{
		//the problem is how to identify to root node.....b'cause root node must not be deallocated
		//the way to recog.root ndoe is to check if parent node of given node ==NULL...because how i made the program...then root node will only be the node which lack parent node.
		//to avoid program from runtime crashing I need to avoid deallocation of root node..in case root node was asked for kill>?! then all of its friends and pointers will be deallocated..
		if(target->parent!=NULL) //if given node is not a parent node....
		{
			N_ARYTREE *dummyparent=target->parent;
			dummyparent->friends->next=target->root->next;
			dummyparent->friends=target->friends;
			dummyparent->number_of_friends+=target->number_of_friends;
			//time to search target node in friends list of parent node...
			printf("%d",dummyparent->data);
			linked_list *dummyPtr=searchFriend(target);
			if(dummyPtr!=NULL)
			{
				dummyparent->root->kill(dummyPtr);
				dummyparent->number_of_friends-=1;
				free(target);

			}
			else
			{
				puts("!ERROR IN FINDING TARGET NODE..");
				return ;
			}


		}
		else
		{
			puts("!ROOT NODE DELETION::REQUEST DENIED!!");

			return;

		}
		
	}


	
};


N_ARYTREE* init_tree()

{
	N_ARYTREE* tmp=( N_ARYTREE* )malloc(sizeof( N_ARYTREE ));
	tmp->my=tmp;
	tmp->friends=init_List();
	tmp->root=tmp->friends;
	tmp->parent=NULL; ///since it is an independent node ...No parent..
	tmp->data=0;
	tmp->number_of_friends=0;
	return tmp;
}

*/


/*
void main()
{
	N_ARYTREE *node=init_tree();
	node->data=10;
	node->attach_friend(1000);
	node->attach_friend(2000);
	node->attach_friend(9000);
	node->attach_friend(4738247);
	node->traverse_relations(node);
	
	STACK_CHILD stack;
	stack.push(node);
	stack.push(node->friends->pointer);
printf("%d",(stack.pop())->data);
while(1)
printf("\n\n\n%f",(float)(rand()*0.00001));
	_getch();

}
*/
#endif