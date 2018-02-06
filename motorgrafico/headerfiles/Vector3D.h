#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>


class Vector3D{
public:	
	float X;
	float Y;
	float Z;

	Vector3D();
	Vector3D(float x, float y, float z);
	virtual ~Vector3D();


} ;

#endif //VECTOR3D_H