
#pragma once 
#include <glm.hpp>

/*
CALCULATES FREE-VECTOR ROTATION ABOUT ANY ARB-IT-RA-RY AXIS IN 2-D PLANE..

*/
#define FROM_ORIGIN 0x0002
#define FREE_VECTOR 0x0001
namespace aRot
{
	
float  mag(glm::vec3 v)
{
//	return glm::sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	return glm::sqrt(glm::dot(v,v));

}

/*
@param--
vec    :vector to be rotated

pivot  :location of pivot in 2 D plane

normal :vector normal to plane of rotation

theta  :angle in Degree(not radian !)

*/
glm::vec3 rotatebyPivot(glm::vec3 vec,glm::vec3 pivot,glm::vec3 normal,float theta,bool Normalize=false,int return_as=FREE_VECTOR)
{

	float magnitude=mag(vec);
	

	//calculate direction vector..
	glm::vec2 tmp(vec);
	
	vec/=magnitude; //direction vector..
	//printf("\nvector rot::%f %f %f magnitude :%f",vec.x,vec.y,vec.z,magnitude);

	if(Normalize==false)   //Normalized operation..
	{

		
	
		if(return_as==FREE_VECTOR) //a free rotated vector...
		
		{
				return magnitude*glm::vec3(mag(vec)*glm::cos(glm::radians(theta)),mag((glm::cross(normal,vec)))* glm::sin(glm::radians(theta)) ,0);
		}
		else if(return_as==FROM_ORIGIN)						//or a vector from source of Pivot or generally origin..
			return magnitude*(glm::vec3(mag(vec)*glm::cos(glm::radians(theta)),mag((glm::cross(normal,vec)))* glm::sin(glm::radians(theta)) ,0) + pivot);


	}

	else			//Un-normalized operation..
		
		if(return_as==FREE_VECTOR)
		
			return magnitude*glm::vec3(mag(vec)*glm::cos(glm::radians(theta)),mag((glm::cross(normal,vec)))* glm::sin(glm::radians(theta)) ,0);
		
		else if(return_as==FROM_ORIGIN)
			return magnitude*(glm::vec3(mag(vec)*glm::cos(glm::radians(theta)),mag((glm::cross(normal,vec)))* glm::sin(glm::radians(theta)) ,0) + pivot);


}


/*
@param 

v	:	input-3d vector
r	:	output vec-2d imgui(call by ref.)
*/
void glm2Im(glm::vec3 v,ImVec2 &r)
{
	r.x=v.x,
	r.y=v.y;
}
ImVec2 glm2Im(glm::vec3 v)
{
	return ImVec2(v.x,v.y);

}
glm::vec3 Im2glm(ImVec2 src)
{
	
	return (glm::vec3(src.x,src.y,0));
}


};