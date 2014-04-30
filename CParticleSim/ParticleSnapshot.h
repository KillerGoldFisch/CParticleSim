#pragma once
class ParticleSnapshot
{
public:
	float Time;

	float * VertexArray;
	float * ColorArray;

	int nVertex;
	int nColors;

	ParticleSnapshot(float time, float * vertexArray, float * colorArray);
	~ParticleSnapshot(void);

	void Free();
};

