#ifndef VEC3_H
#define VEC3_H

class vec3{
public:
	float x, y, z;

	vec3(){x = 0; y = 0; z = 0;}
	vec3(float q, float w, float r){ x = q; y = w; z = r;}
	virtual ~vec3() = default;
private:

};



#endif //VEC3_H