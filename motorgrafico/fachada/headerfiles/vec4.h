#ifndef VEC4_H
#define VEC4_H

class vec4{
public:
	float x, y, z, a;

	vec4(float q, float w, float r, float al){ x = q; y = w; z = r; a = al;}
	virtual ~vec4() = default;
private:

};



#endif //VEC4_H