#include "StdAfx.h"
#include "ParticleSnapshot.h"
#include <stdlib.h>


ParticleSnapshot::ParticleSnapshot(float time, float * vertexArray, float * colorArray)
{
	this->nVertex = 0;
	this->nColors = 0;
	this->Time = time;
	this->VertexArray = vertexArray;
	this->ColorArray = colorArray;
}


ParticleSnapshot::~ParticleSnapshot(void)
{
}

void ParticleSnapshot::Free()
{
	free(this->VertexArray);
	free(this->ColorArray);
	free(this);
}