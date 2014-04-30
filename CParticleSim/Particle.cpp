#include "StdAfx.h"
#include "Particle.h"


Particle::Particle(Vector3D s, Vector3D v, float m, float r, float g, float b)
{
	this->M = m;
	this->V = v;
	this->S = s;

	this->Color_R = r;
	this->Color_G = g;
	this->Color_B = b;

	this->ResetAF();
}


Particle::~Particle(void)
{
}

void Particle::ResetAF()
{
	this->_A = this->A;
	this->_F = this->F;

	this->F.x = 0;
	this->F.y = 0;
	this->F.z = 0;

	this->A.x = 0;
	this->A.y = 0;
	this->A.z = 0;
}

void Particle::CalcSVA(float dt)
{
	this->F -= this->V*0.001f;
	this->A = this->F / this->M;
	this->V += this->A * dt;
	this->S += this->V * dt;
}