#pragma once
#include "Vector3D.h"
class Particle
{
public:
	Vector3D S;
	Vector3D V;
	Vector3D A;

	Vector3D _A;
	Vector3D _F;

	Vector3D F;

	float M;

	float Color_R;
	float Color_G;
	float Color_B;
public:
	Particle(Vector3D s, Vector3D v, float m, float r, float g, float b);
	~Particle(void);

	void ResetAF();
	void CalcSVA(float dt);
};

