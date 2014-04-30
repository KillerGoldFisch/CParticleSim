#include "StdAfx.h"
#include "ParticleSystem.h"
#include <vector>
#include <math.h>


ParticleSystem::ParticleSystem(void)
{
	this->CurrentTime = 0;
	this->CalcTimeStep = 0.001f;
	this->RenderTimeStep = 0.001f;//1.0f/25.0f;//
	this->_nextSnapshot = -0.0001f;

	this->Debug = false;
}


ParticleSystem::~ParticleSystem(void)
{
}

void ParticleSystem::CalcNextStep()
{
	if(this->Debug) printf("\n\nNEW Step at %fs with %i Partivles\n", this->CurrentTime , this->Particles.size());

	for(int n = 0; n < this->Particles.size();n++) this->Particles[n].ResetAF();

	for(int n1 = 0; n1 < this->Particles.size();n1++)
	{
		for(int n2 = n1 + 1; n2 < this->Particles.size();n2++)
		{
			if(this->Debug) printf("Calc Partivles %i - %i\n",n1,n2);
			this->_calcP(n1,n2);
		}
	}

	for(int n = 0; n < this->Particles.size();n++)
	{
		this->Particles[n].CalcSVA(this->CalcTimeStep);

		if(this->Debug)
		{
			printf("Move Particle %i\n",n);
			printf("    S = %s\n", this->Particles[n].S.toString().c_str());
			printf("    V = %s\n", this->Particles[n].V.toString().c_str());
			printf("    A = %s\n", this->Particles[n].A.toString().c_str());
			printf("    F = %s\n", this->Particles[n].F.toString().c_str());
		}
	}

	this->CurrentTime += this->CalcTimeStep;

	if(this->CurrentTime > this->_nextSnapshot)
	{
		this->MakeSnapshot();
		this->_nextSnapshot += this->RenderTimeStep;
	}
}

void ParticleSystem::_calcP(int n1, int n2)
{
	Particle * p1 = &this->Particles[n1];
	Particle * p2 = &this->Particles[n2];

	Vector3D * s1 = &p1->S;
	Vector3D * s2 = &p2->S;

	Vector3D ds = *s2 - *s1;
	Vector3D unitv = ds.unit();

	float f = this->_calcF(ds.len());
	
	Vector3D vf = unitv * f;

	p1->F -= vf;
	p2->F += vf;

	if(this->Debug)
	{
		printf("    s1 = %s\n", s1->toString().c_str());
		printf("    s2 = %s\n", s2->toString().c_str());
		printf("    ds = %s\n", ds.toString().c_str());
		printf("    f  = %f\n", f);
		printf("    vf = %s\n", vf.toString().c_str());
		printf("    f1 = %s\n", p1->F.toString().c_str());
		printf("    f2 = %s\n", p2->F.toString().c_str());
	}

}

float ParticleSystem::_calcF(float dist)
{
	//return (0.01f/pow(dist*10,4) - 1/pow(dist*100,2))*0.01;
	if(dist > 0.17f) return 0;
	return (20*exp(-40*1.5*dist)-exp(-20*1.5*dist)) * 0.2;
}

void ParticleSystem::MakeSnapshot()
{
	float * points = (float *)malloc(sizeof(float) * this->Particles.size() * 4);
	float * colors = (float *)malloc(sizeof(float) * this->Particles.size() * 5);

	if(points == NULL || colors== NULL)
	{
		printf("Konnte kein Speicher Reserviren\n");
		if(points != NULL) free(points);
		if(colors != NULL) free(points);
		return;
	}

	ParticleSnapshot * PS = new ParticleSnapshot(this->CurrentTime,points,colors);

	int  nv = 0;
	int nc = 0;

	for(int n = 0; n < this->Particles.size();n++)
	{
		points[nv] = this->Particles[n].S.x;
		points[nv + 1] = this->Particles[n].S.y;
		points[nv + 2] = this->Particles[n].S.z;
		nv += 3;

		float fmod = this->Particles[n].F.len() * 100;

		colors[nc] = (this->Particles[n].Color_R + fmod ) / 2.0f;
		colors[nc + 1] = this->Particles[n].Color_G - fmod;
		colors[nc + 2] = this->Particles[n].Color_B - fmod;
		colors[nc + 3] = 0.666f;
		nc += 4;
	}

	PS->nVertex = nv;
	PS->nColors = nc;

	this->PSnapshots.push_back(PS);
}

void ParticleSystem::AddSphere(Vector3D pos, Vector3D v, float radius,float mass,float r, float g, float b)
{
	const float step = 0.09f;
	for(float x = -radius ; x < radius ; x += step)
		for(float y = -radius ; y < radius ; y += step)
			for(float z = -radius ; z < radius ; z += step)
			{
				Vector3D vec = Vector3D(x,y,z);
				if(vec.len() > radius) continue;
				vec += pos;
				this->Particles.push_back(Particle(vec,v,mass,r,g,b));
			}
}