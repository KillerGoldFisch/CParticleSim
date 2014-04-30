#pragma once
#include "ParticleSystem.h"
#include "Particle.h"
#include "ParticleSnapshot.h"
#include <vector>



class ParticleSystem
{
private:
	float _nextSnapshot;

	float _calcF(float dist);
	void _calcP(int n1, int n2);
public:
	std::vector<ParticleSnapshot*> PSnapshots;

	std::vector<Particle> Particles;

	float CurrentTime;
	float CalcTimeStep;
	float RenderTimeStep;

	bool Debug;
public:

	ParticleSystem(void);
	~ParticleSystem(void);

	void CalcNextStep();
	void MakeSnapshot();
	void AddSphere(Vector3D pos,Vector3D v, float radius,float mass ,float r, float g, float b);
};

