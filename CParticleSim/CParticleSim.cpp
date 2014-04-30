// CParticleSim.cpp : Defines the entry point for the console application.
//
#include "ParticleSystem.h"
#include "Vector3D.h"
#include <vector>
#include <process.h>
#include "OpenGL_Helper.h"


ParticleSystem * PS;

ParticleSnapshot * snapshot;
int nsnapshot = 0;
bool play = true;
float pointsize = 5;
int mselection;
bool doselect = false;

TextureImage particleIMG;

bool isMLock = false;

float angleX = 0.0f;
float angleY = 0.0f;

float zoom = 0.4f;


void CalcThread(void *);

bool running;

int InitGL()
{
	BuildFont();
	
	//if(!LoadTGA(&particleIMG,"Data/particle1.tga")) printf("Paricle Textur konnte nicht geladen werden!\n");

	glEnable(GL_LIGHTING);


    //// track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);


    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    //// position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
	//float lightPos[4] = {0, 0, -1, -8.5f}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration

	mselection = 0;
	return 1;
}
int DrawTargets(bool isselectmode)
{
	if(!PS->PSnapshots.empty())
	{
		//if(snapshot != NULL) snapshot->Free();
		while(nsnapshot > PS->PSnapshots.size() - 1) nsnapshot--;
		while(nsnapshot < 0) nsnapshot++;
		snapshot = PS->PSnapshots[nsnapshot];PS->PSnapshots.front();
		if(play) nsnapshot++;
	}

	if(snapshot == NULL) return 1;

	//printf("----------------------------------------------------\n");
	//for(int n = 0 ; n < snapshot->nVertex ; n+=3)
	//{
	//	printf("   X=%f Y=%f Z=%f\n",snapshot->VertexArray[n],snapshot->VertexArray[n+1],snapshot->VertexArray[n+2]);
	//}


	glTranslatef(0,0,-8.0f);
	//glTranslatef(0,-1.5f,0);
	glRotatef(angleX,1,0,0);
	glRotatef(angleY,0,1,0);
	glScalef(zoom,zoom,zoom);
	glScalef(8,8,8);

	glPointSize(pointsize);

	for(int n = 0; n < snapshot->nVertex / 3; n++)
	{
		glLoadName(n + 1);
		int nv = n * 3;
		int nc = n * 4;


		
        glPushMatrix();
 

        glTranslatef(snapshot->VertexArray[nv],snapshot->VertexArray[nv + 1],snapshot->VertexArray[nv + 2]);

	
		
		if(mselection == (n + 1) && !isselectmode)
		{
			glColor4f (snapshot->ColorArray[nc],
				snapshot->ColorArray[nc + 1],
				snapshot->ColorArray[nc + 2],
				1);

			glRenderSphere(pointsize * 1.5f);
			glLineWidth(3);
			glColor3f(1,0,0);
			glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f(PS->Particles[n]._F.x * 100,PS->Particles[n]._F.y * 100,PS->Particles[n]._F.z * 100);
			glEnd();

			glColor3f(0,1,0);
			glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f(PS->Particles[n]._A.x * .1f ,PS->Particles[n]._A.y * .1f,PS->Particles[n]._A.z * .1f);
			glEnd();

			glColor3f(0,0,1);
			glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f(PS->Particles[n].V.x * 0.1,PS->Particles[n].V.y * 0.1,PS->Particles[n].V.z * 0.1);
			glEnd();
		}else{
			glColor4f (snapshot->ColorArray[nc],
				snapshot->ColorArray[nc + 1],
				snapshot->ColorArray[nc + 2],
				snapshot->ColorArray[nc + 3]);
			glRenderSphere(pointsize);
		}

        glPopMatrix();
	}

	glColor4f(1,1,1,1);




	glLoadName(0);
	return 1;
}
int DrawOrtho()
{
	glPrint(glWidth / 2 - 150,glHeight - 20,"KillerGoldFisch Productions");						// Print Title
	if(snapshot != NULL) glPrint(glWidth / 2 - 150,20,"Time %fs - %fs",nsnapshot / 25.0f,PS->PSnapshots.size() / 25.0f);
	if(mselection) glPrint(glWidth / 2 - 150,10,"Hit: %i",mselection);
	glBindTexture(GL_TEXTURE_2D, 0);
	return 1;
}
int KeyDOWN(bool allkeys[256],int key)
{
	if(key == VK_SPACE) isMLock = true;
	if(key == VK_UP) zoom *= 1.5f;
	if(key == VK_DOWN) zoom *= 0.6666;

	if(allkeys[82]) nsnapshot = 0;
	if(allkeys[80]) play = play ? false : true;
	if(allkeys[83]) { doselect = doselect ? false : true; mselection = 0; } //S

	if(key == VK_RIGHT) nsnapshot++;
	if(key == VK_LEFT) if(nsnapshot > 0) nsnapshot--;
	
	if(allkeys[187]) pointsize *= 1.5f;
	if(allkeys[189]) pointsize *= 0.66f;


	//for(int n = 0; n < 255;n++)
	//	if(allkeys[n]) printf("Key %i\n",n);
	
	return 1;
}
int MouseMove(int x, int y, int dx, int dy)
{
	if(isMLock)
	{
		angleY -= (float)dx;
		angleX -= (float)dy;
	}

	 
	if(doselect) mselection = Selection(x, y);

	//if(mselection) 
	//	printf("Hit : %i\n",mselection);

	return 1;
}
int MouseButton(HWND	hWnd,			// Handle For This Window
				UINT	uMsg,			// Message For This Window
				WPARAM	wParam,			// Additional Message Information
				LPARAM	lParam)
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_LBUTTONDOWN:							// Watch For Window Activate Message
		{
			isMLock = true;
			return 1;
		}
		case WM_LBUTTONUP:
		{
			isMLock = false;
			return 1;
		}
		case WM_RBUTTONDOWN:
		{
			mselection = Selection(glMouseX,glMouseY);
			//printf("Selection : %i X=%i Y=%i\n",mselection,glMouseX,glMouseY);
			return 1;
		}
		case WM_RBUTTONUP:
		{
			//mselection = 0;
			return 1;
		}
		case 522:
		{
			if(GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				zoom *= 1.5f;
			}else{
				zoom *= .666f;
			}
			return 1;
		}
	}
	//printf("%i %i\n",uMsg,GET_WHEEL_DELTA_WPARAM(wParam));
	return 1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	running = true;

	_beginthread( CalcThread, 0, NULL);

	snapshot = NULL;

	onInitGL = InitGL;
	onDrawGLOrtho = DrawOrtho;
	onMouseMove = MouseMove;
	onMouseButton = MouseButton;
	onKeyDOWN = KeyDOWN;
	onDrawGLTargets = DrawTargets;

	//getchar();

	int ret = StartGL(	L"CParticleSim",
					1000,
					600,
					false
					);

	running = false;

	//getchar();
	return 0;
}


void CalcThread(void * dummy)
{
	PS = new ParticleSystem();

	//PS->Debug = true;
	//for(float x = 0 ; x < 1 ; x += 0.1f)
	//	for(float y = 0 ; y < 1 ; y += 0.1f)
	//		for(float z = 0 ; z < 1 ; z += 0.1f)
	//			PS->Particles.push_back(Particle(Vector3D(x,y,z),Vector3D(),0.005));
	PS->AddSphere(Vector3D(0.0f,0.0f,0.0f),Vector3D(),0.6f,0.05f,0,0,1);
	//PS->AddSphere(Vector3D(0.0f,1.05f,0.0f),Vector3D(0,-2,0),0.5f,0.005f,1,1,0);
	PS->AddSphere(Vector3D(0.4f,-1.05f,0.0f),Vector3D(0,5.0f,0),0.3f,0.0005f,0,1,0);

	//for(float x = 0.2f ; x < 0.8f ; x += 0.1f)
	//	for(float y = 1.05 ; y < 1.55 ; y += 0.1f)
	//		for(float z = 0.2 ; z < 0.8f ; z += 0.1f)
	//			PS->Particles.push_back(Particle(Vector3D(x,y,z),Vector3D(0,-0.1f,0),0.0005));

	//PS->Particles.push_back(Particle(Vector3D(0.08,0,0),Vector3D(),0.0005));
	//PS->Particles.push_back(Particle(Vector3D(0.0,0,0),Vector3D(),0.0005));

	while(running)
	{while(PS->PSnapshots.size() > 10000 && running) Sleep(1);
		Sleep(1);
		PS->CalcNextStep();
		printf("Time %f\n",PS->CurrentTime);
	}
}
