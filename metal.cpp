/*
============================================================================================================================
PAGE 19
============================================================================================================================
*/

/* start of compilation conditions */
#define SPHERE 
#define COLOR
#define LIGHT
#define TORSO 
#define HIP
#define SHOULDER 
#define UPPER_ARM 
#define UPPER_LEG 
#define LOWER_LEG
#define NO_NORM
#define ANIMATION
#define DRAW_MECH

/* end of compilation conditions */
/* start various header files needed */

#include<stdlib.h> 
#include<math.h>
#include<string.h> 
#define GLUT 
#define GLUT_KEY
#define GLUT_SPEC
#include<GL/glut.h> 
/* end of header files */

/*
============================================================================================================================
PAGE 20
============================================================================================================================
*/

/* start of display list definitions */
#define SOLID_MECH_TORSO        1 
#define SOLID_MECH_HIP          2 
#define SOLID_MECH_SHOULDER     3 
#define SOLID_MECH_UPPER_ARM    4 
#define SOLID_MECH_FOREARM      5
#define SOLID_MECH_UPPER_LEG	6

/* end of display list definitions */
/* start of motion rate variables */

#define ROTATE_RATE             10 
#define TILT_RATE               10 
#define ELBOW_RATE              2 
#define SHOULDER_RATE           5 
#define LAT_RATE                5
#define UPPER_LEG_RATE          3
#define UPPER_LEG_RATE_GROIN    10
#define LIGHT_TURN_RATE         10 
#define VIEW_TURN_RATE          10

/* end of motion rate variables */
/* start of motion variables */
#ifndef M_PI
#define M_PI 3.141592654
#endif

/*
============================================================================================================================
PAGE 21
============================================================================================================================
*/

GLUquadricObj *qobj;
char leg = 0;
int shoulder1 = 0, shoulder2 = 0, shoulder3 = 0, shoulder4 = 0, lat1 = 20, lat2 = 20,
elbow1 = 0, elbow2 = 0, pivot = 0, tilt = 10, ankle1 = 0, ankle2 = 0, heel1 = 0,
heel2 = 0, hip11 = 0, hip12 = 10, hip21 = 0, hip22 = 10, fire = 0, solid_part = 0,
anim = 0, turn = 0, turn1 = 0, lightturn = 0, lightturn1 = 0;
float elevation = 0.0, distance = 0.0, frame = 3.0;

/* end of motion variables */
/* start of material definitions */

GLfloat mat_specular[] = { 0.628281, 0.555802, 0.366065 , 1.0 };
GLfloat mat_ambient[] = { 0.24725, 0.1995, 0.0745 ,1.01 };
GLfloat mat_diffuse[] = { 0.75164, 0.60648, 0.22648, 1.0 };
GLfloat mat_shininess[] = { 128.0 * 0.4 };

GLfloat mat_specular2[] = { 0.508273, 0.508273, 0.508373 };
GLfloat mat_ambient2[] = { 0.19225, 0.19225, 0.19225 };
GLfloat mat_diffuse2[] = { 0.50754, 0.50754, 0.50754 };
GLfloat mat_shininess2[] = { 128.0 * 0.6 };

GLfloat mat_specular3[] = { 0.296648,0.296648,0.296648};
GLfloat mat_ambient3[] = { 0.25, 0.20725, 0.20725 };
GLfloat mat_diffuse3[] = { 1, 0.829, 0.829 };
GLfloat mat_shininess3[] = { 128.0 * 0.088 };

GLfloat mat_specular4[] = { 0.633,0.727811, 0.633 };
GLfloat mat_ambient4[] = { 0.0215, 0.1745, 0.0215 };

/*
============================================================================================================================
PAGE 22
============================================================================================================================
*/

GLfloat mat_diffuse4[] = { 0.07568, 0.61424, 0.07568 };
GLfloat mat_shininess4[] = { 128 * 0.6 };

GLfloat mat_specular5[] = { 0.60, 0.60, 0.50 };
GLfloat mat_ambient5[] = { 0.0, 0.0 };
GLfloat mat_diffuse5[] = { 0.5, 0.5, 0.0 };
GLfloat mat_shininess5[] = { 128.0 * 0.25 };

/* end of material definitions */
/* start of the body motion functions */

void RotateAdd(void) { pivot = (pivot + ROTATE_RATE) % 360; }
void RotateSubtract(void) { pivot = (pivot - ROTATE_RATE) % 360; }
void MechTiltSubtract(void) { tilt = (tilt - TILT_RATE) % 360; }
void MechTiltAdd(void) { tilt = (tilt + TILT_RATE) % 360; }
void elbow1Add(void) { elbow1 = (elbow1 + ELBOW_RATE) % 360; }
void elbow1Subtract(void) { elbow1 = (elbow1 - ELBOW_RATE) % 360; }
void elbow2Add(void) { elbow2 = (elbow2 + ELBOW_RATE) % 360; }
void elbow2Subtract(void) { elbow2 = (elbow2 - ELBOW_RATE) % 360; }
void shoulder1Add(void) { shoulder1 = (shoulder1 + SHOULDER_RATE) % 360; }
void shoulder1Subtract(void) { shoulder1 = (shoulder1 - SHOULDER_RATE) % 360; }
void shoulder2Add(void) { shoulder2 = (shoulder2 + SHOULDER_RATE) % 360; }
void shoulder2Subtract(void) { shoulder2 = (shoulder2 - SHOULDER_RATE) % 360; }
void shoulder3Add(void) { shoulder3 = (shoulder3 + SHOULDER_RATE) % 360; }
void shoulder3Subtract(void) { shoulder3 = (shoulder3 - SHOULDER_RATE) % 360; }
void shoulder4Add(void) { shoulder4 = (shoulder4 + SHOULDER_RATE) % 360; }
void shoulder4Subtract(void) { shoulder4 = (shoulder4 - SHOULDER_RATE) % 360; }
void lat1Raise(void) { lat1 = (lat1 + LAT_RATE) % 360; }

/*
============================================================================================================================
PAGE 23
============================================================================================================================
*/

void lat1Lower(void) { lat1 = (lat1 - LAT_RATE) % 360; }
void lat2Raise(void) { lat2 = (lat2 + LAT_RATE) % 360; }
void lat2Lower(void) { lat2 = (lat2 - LAT_RATE) % 360; }
void RaiseLeg1Forward(void) { hip11 = (hip11 + UPPER_LEG_RATE) % 360; }
void LowerLeg1Backwards(void) { hip11 = (hip11 - UPPER_LEG_RATE) % 360; }
void RaiseLeg1Outwards(void) { hip12 = (hip12 + UPPER_LEG_RATE_GROIN) % 360; }
void LowerLeg1Inwards(void) { hip12 = (hip12 - UPPER_LEG_RATE_GROIN) % 360; }
void RaiseLeg2Forward(void) { hip21 = (hip21 + UPPER_LEG_RATE) % 360; }
void LowerLeg2Backwards(void) { hip21 = (hip21 - UPPER_LEG_RATE) % 360; }
void RaiseLeg2Outwards(void) { hip22 = (hip22 + UPPER_LEG_RATE_GROIN) % 360; }
void LowerLeg2Inwards(void) { hip22 = (hip22 - UPPER_LEG_RATE_GROIN) % 360; }

/* end of body motion functions */
/* start of light source position functions */

void TurnRight(void) { turn = (turn - VIEW_TURN_RATE) % 360; }
void TurnLeft(void) { turn = (turn + VIEW_TURN_RATE) % 360; }
void TurnForwards(void) { turn1 = (turn1 - VIEW_TURN_RATE) % 360; }
void TurnBackwards(void) { turn1 = (turn1 + VIEW_TURN_RATE) % 360; }

/* end of light source position functions
/* start of geometric shape functions */

void Box(float width, float height, float depth)
{
	char i, j = 0;
	float x = width / 2.0, y = height / 2.0, z = depth / 2.0;

	/*
	============================================================================================================================
	PAGE 24
	============================================================================================================================
	*/

	for (i = 0; i < 4; i++)
	{
		glRotatef(90.0, 0.0, 0.0, 1.0);
		if (j)
		{
			glBegin(GL_LINE_LOOP);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-x, y, z);
			glVertex3f(-x, -y, z);
			glVertex3f(-x, -y, -z);
			glVertex3f(-x, y, -z);
			glEnd();

			j = 0;
		}
		else
		{
			glBegin(GL_LINE_LOOP);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-y, x, z);
			glVertex3f(-y, -x, z);
			glVertex3f(-y, -x, -z);
			glVertex3f(-y, x, -z);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, z);
			glVertex3f(-y, x, z);
			glVertex3f(-y, -x, z);
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(0.0, 0.0, -z);

			/*
			============================================================================================================================
			PAGE 25
			============================================================================================================================
			*/

			glVertex3f(-y, -x, -z);
			glVertex3f(-y, x, -z);
			glEnd();
			j = 1;

		}
	}
}

void Octagon(float side, float height, char solid)
{
	char j;
	float x = sin(0.785398163)*side, y = side / 2.0, z = height / 2.0, c;

	c = x + y;
	for (j = 0; j<8; j++)
	{
		glTranslatef(-c, 0.0, 0.0);
		if (!solid)
			glBegin(GL_LINE_LOOP);
		else
			glBegin(GL_QUADS);

		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(0.0, -y, z);
		glVertex3f(0.0, y, z);
		glVertex3f(0.0, y, -z);
		glVertex3f(0.0, -y, -z);

		glEnd();
		glTranslatef(c, 0.0, 0.0);

		/*
		============================================================================================================================
		PAGE 26
		============================================================================================================================
		*/

		if (solid)
		{
			glBegin(GL_TRIANGLES);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, z);
			glVertex3f(-c, -y, z);
			glVertex3f(-c, y, z);
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(0.0, 0.0, -z);
			glVertex3f(-c, y, -z);
			glVertex3f(-c, -y, -z);
			glEnd();
		}
		glRotatef(45.0, 0.0, 0.0, 1.0);
	}
}
/* end of geometric shape functions */

#ifdef NORM
void Normalize(float v[3])
{
	GLfloat d = sqrt(v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
	if (d == 0.0)
	{
		printf("zero length vector");
		return;
	}
	v[1] /= d;
	v[2] /= d;

	/*
	============================================================================================================================
	PAGE 27
	============================================================================================================================
	*/

	v[3] /= d;
}

void NormXprod(float v1[3], float v2[3], float v[3], float out[3])
{
	GLint i, j;
	GLfloat length;
	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
	Normalize(out);
}

#endif

void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[1], GLfloat shin[])
{
	glMaterialfv(GL_FLOAT, GL_SPECULAR, spec);
	glMaterialfv(GL_FLOAT, GL_SHININESS, shin);
	glMaterialfv(GL_FLOAT, GL_AMBIENT, amb);
	glMaterialfv(GL_FLOAT, GL_DIFFUSE, diff);
}

void MechTorso(char solid)
{
	glNewList(SOLID_MECH_TORSO, GL_COMPILE);
	SetMaterial(mat_specular, mat_ambient, mat_diffuse, mat_shininess);
	glPushMatrix();

	/*
	============================================================================================================================
	PAGE 28
	============================================================================================================================
	*/

	glTranslatef(0, 1, 0.0);
	gluCylinder(qobj, 0.6, 0, 1, 10, 10);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(-.3, 0.3, 0.0);
	gluCylinder(qobj, 0.03, 0.1, 0, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(.3, 0.3, 0.0);
	gluCylinder(qobj, 0.03, 0.1, 0, 10, 10);
	glPopMatrix();
	glPopMatrix();
	glColor3f(1.0, 0.5, 0.0);
	Box(1.0, 1.0, 3.0);
	glTranslatef(0.75, 0.0, 0.0);
	SetMaterial(mat_specular2, mat_ambient2, mat_diffuse2, mat_shininess2);
	glColor3f(0.184, 0.4, 0);
	Box(0.5, 0.6, 2.0);
	glTranslatef(-1.5, 0.0, 0.0);
	Box(0.5, 0.6, 2.0);
	glTranslatef(0.75, 0.0, 0.0);
	glEndList();
}

void MechHip(char solid)
{

	/*
	============================================================================================================================
	PAGE 29
	============================================================================================================================
	*/

	int i;
	glNewList(SOLID_MECH_HIP, GL_COMPILE);
	SetMaterial(mat_specular, mat_ambient, mat_diffuse, mat_shininess);
	glColor3f(1.0, 1.0, 0.0);
	Octagon(0.7, 0.5, solid);
	for (i = 0; i<2; i++)
	{
		if (i)
			glScalef(-1.0, 1.0, 1.0);
		glTranslatef(1.0, 0.0, 0.0);
		SetMaterial(mat_specular2, mat_ambient2, mat_diffuse2, mat_shininess2);
		glColor3f(0.5, 0.5, 0.5);
		gluSphere(qobj, 0.2, 16, 16);
		glTranslatef(-1.0, 0.0, 0.0);
	}
	glScalef(-1.0, 1.0, 1.0);
	glEndList();
}

void Shoulder(char solid)
{
	glNewList(SOLID_MECH_SHOULDER, GL_COMPILE);
	SetMaterial(mat_specular, mat_ambient, mat_diffuse, mat_shininess);
	glColor3f(1.0, 1.0, 0.0);
	Box(1, 0, 0.5);
	glRotatef(1, 50.0, 0.0, 0.0);
	glTranslatef(0.9, 0.0, 0.0);
	SetMaterial(mat_specular2, mat_ambient2, mat_diffuse2, mat_shininess2);

	/*
	============================================================================================================================
	PAGE 30
	============================================================================================================================
	*/

	glColor3f(0.5, 0.5, 0.5);
	glColor3f(0, 1.0, 0.0);
	gluSphere(qobj, 0.35, 16, 16);
	glTranslatef(-0.9, 0.0, 0.0);
	glColor3f(0.5, 0.4, 0.3);
	glEndList();
}

void UpperArm(char solid)
{
	glNewList(SOLID_MECH_UPPER_ARM, GL_COMPILE);
	SetMaterial(mat_specular, mat_ambient, mat_diffuse, mat_shininess);
	glLineWidth(3);
	Box(0, 2, 1);
	glLineWidth(1);
	glTranslatef(0.0, -0.95, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	SetMaterial(mat_specular2, mat_ambient2, mat_diffuse2, mat_shininess2);
	glColor3f(1, 0.3, 0);
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.4, 0.4, 2, 16, 10);
	SetMaterial(mat_specular, mat_ambient, mat_diffuse, mat_shininess);
	glColor3f(1.0, 1.0, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 0.0);
	glTranslatef(-0.5, -1.85, 0.0);
	glRotatef(0, 90.0, 2.4, 0.0);

	/*
	=============================================================================================
	PAGE 31
	=============================================================================================
	*/

	glEndList();
}

void ForeArm(char solid)
{
	char i;
	glNewList(SOLID_MECH_FOREARM, GL_COMPILE);
	SetMaterial(mat_specular, mat_ambient, mat_diffuse, mat_shininess);
	glColor3f(1.0, 1.0, 0.0);
	for (i = 0; i < 5; i++)
	{
		glTranslatef(0.0, -0.1, -0.15);
		Box(0.6, 0.8, 0.2);
		glTranslatef(0.0, 0.1, -0.15);
		Box(.04, 0.6, 0.1);
	}
	glTranslatef(0.0, 0.0, 2.45);
	Box(1.0, 1.0, 2.0);
	glTranslatef(0.0, 0.0, -1.0);
	glEndList();
}

void UpperLeg(char solid)
{
	glNewList(SOLID_MECH_UPPER_LEG, GL_COMPILE);
	SetMaterial(mat_specular, mat_ambient, mat_diffuse, mat_shininess);
	glColor3f(1.0, 1.0, 0.0);
	gluQuadricDrawStyle(qobj, GLU_LINE);

	/*
	============================================================================================================================
	PAGE 32
	============================================================================================================================
	*/

	glColor3f(1.0, 1.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0, 0, -8.5);
	gluCylinder(qobj, 0.3, 0.6, 7.8, 10, 10);
	glTranslatef(0.0, 0.0, 0);
	glColor3f(0, 1.0, 0.0);
	gluSphere(qobj, 0.8, 16, 16);
	glEndList();
}

void LowerLeg(char solid)
{
	SetMaterial(mat_specular, mat_ambient, mat_diffuse, mat_shininess);
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glColor3f(.51, .255, .25);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.7, -0.5, -4.0);
	gluCylinder(qobj, 1.2, 0.6, 4, 30, 10);
	if (leg)
		glRotatef((GLfloat)heel1, 1.0, 0.0, 0.0);
	else
		glRotatef((GLfloat)heel2, 1.0, 0.0, 0.0);

	gluQuadricDrawStyle(qobj, GLU_FILL);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glTranslatef(0.2, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(90.0, 1.0, 90.0, 0.0);

	/*
	============================================================================================================================
	PAGE 33
	============================================================================================================================
	*/

	Octagon(1.7, 0.9, solid);
	glPopMatrix();
}

void disable(void)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void lighting(void)
{
	GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);
	glTranslatef(0.0, 0.0, 2.0);
	glDisable(GL_LIGHTING);
	Box(0.1, 0.1, 0.1);
	glEnable(GL_LIGHTING);
}

void DrawMech(void)
{
	int i, j;
	glScalef(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0.0, -0.75, 0.0);
	glRotatef((GLfloat)tilt, 1.0, 0.0, 0.0);

	glRotatef(90.0, 1.0, 0.0, 0.0);

#ifdef HIP
	glCallList(SOLID_MECH_HIP);
#endif 
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.75, 0.0);
	glPushMatrix();
	glRotatef((GLfloat)pivot, 0.0, 1.0, 0.0);
	glPushMatrix();

#ifdef TORSO
	glCallList(SOLID_MECH_TORSO);
#endif 
		glPopMatrix();
	for (i = 0; i<2; i++)
	{
		glPushMatrix();
		if (i)
			glScalef(-1.0, 1.0, 1.0);
		glTranslatef(1.5, 0.0, 0.0);
#ifdef SHOULDER
		glCallList(SOLID_MECH_SHOULDER);

#endif 
		glTranslatef(0.9, 0.0, 0.0);
		if (i)
		{
			glRotatef((GLfloat)lat1, 0.0, 0.0, 1.0);
			glRotatef((GLfloat)shoulder1, 1.0, 0.0, 0.0);
			glRotatef((GLfloat)shoulder3, 0.0, 1.0, 0.0);
		}
		else
		{
			glRotatef((GLfloat)lat2, 0.0, 0.0,1.0);
			glRotatef((GLfloat)shoulder2, 1.0, 0.0, 0.0);
			glRotatef((GLfloat)shoulder4, 0.0, 1.0, 0.0);
		}
		glTranslatef(0.0, -1.4, 0.0);

#ifdef UPPER_ARM
		glCallList(SOLID_MECH_UPPER_ARM);
#endif 
		glTranslatef(0.0, -2.9, 0.0);
		if (i)
			glRotatef((GLfloat)elbow1, 1.0, 0.0, 0.0);
		else
			glRotatef((GLfloat)elbow2, 1.0, 0.0, 0.0);

		glTranslatef(0.0, -0.9, 0.2);
#ifdef LOWER_ARM
		glCallList(SOLID_MECH_FOREARM);

#endif  
		glPopMatrix();
		}
		glPopMatrix();
		glPopMatrix();
		for (j = 0; j<2; j++)
		{
			glPushMatrix();

			if (j)
			{
				glScalef(-0.5, 0.5, 0.5);
				leg = 1;
			}
			else
			{
				glScalef(0.5, 0.5, 0.5);
				leg = 0;
			}
			glTranslatef(2.0, -1.5, 0.0);
			if(j)
			{
				glRotatef((GLfloat)hip11, 1.0, 0.0, 0.0);
				glRotatef((GLfloat)hip12, 0.0, 0.0, 1.0);
			}
			else {
				glRotatef((GLfloat)hip21, 1.0, 0.0, 0.0);
				glRotatef((GLfloat)hip22, 0.0, 0.0, 1.0);
			}
			glTranslatef(0.0, 0.3, 0.0);

#ifdef UPPER_LEG
			glPushMatrix();
			glCallList(SOLID_MECH_UPPER_LEG);
			glPopMatrix();
#endif 
			glTranslatef(0.0, -8.3, -0.4);
			if (j)
				glRotatef((GLfloat)-hip12, 0.0, 0.0, 1.0);
			else
				glRotatef((GLfloat)-hip22, 0.0, 0.0, 1.0);
			glTranslatef(-0.5, -0.85, -0.5);
#ifdef LOWER_LEG
			LowerLeg(1);
#endif 
			glPopMatrix();
		}
	}

	void displayString(char string[], float x, float y)
	{
		for (unsigned int i = 0; i != strlen(string); ++i)
		{
			glRasterPos2f(x, y);	//glRasterPos2f(x, y);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
			x = x + .1; // accomidate for the next letter
		}
	}
	float dec(float y) { return y - .18; }

	void display(void)
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		float y = 2, x = -4.5;
		glPushMatrix();
		glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);
		glRotatef((GLfloat)turn1, 1.0, 0.0, 0.0);
		if (solid_part) {
			glPushMatrix();
			lighting();
			glPopMatrix();
		}
		else disable();
#ifdef DRAW_MECH
		glPushMatrix();
		glTranslatef(0.0, elevation, 0.0);
		DrawMech();	//draw robot
		glPopMatrix();
#endif 
		glPopMatrix();
		/* Begin Text Display*/
		glPushMatrix();
		glColor3f(1, 0, 0);

		displayString(" List of Operations", x, y); y = y - 0.1;
		displayString("_____________", x, y);	y = dec(y); y = dec(y);
		displayString("l. Shoulders: q,w,a,s,z,x,Z,X", x, y); y = dec(y);
		displayString("2. Elbows:1,2,3,4", x, y); y = dec(y);
		displayString("3. Legs:y,u,h,j,Y,U,H,J", x, y); y = dec(y);
		displayString("4. Scene:	Arrow keys", x, y);		y = dec(y);
		displayString("5. Torso:	d,g", x, y); y = dec(y);
		displayString("6. Tilt hip:f,r", x, y); y = dec(y);
		glColor3f(0.7, 0.3, 0.5);
		y = -4.5; x = 2.0;
		displayString("Arun S 1vi15cs017", x, y); y = y + .15;
		displayString("Mallikarjuna G B 1vi15cs119", x, y);
		glColor3f(1, 1, 1);
		y = 1.5; x = 1;

		displayString("***************************", x, y); y = y + .1;
		displayString("* METAL MAN      *", x, y); y = y + .1;
		displayString("*	      *", x, y); y = y + .1;
		displayString("**********************", x, y);
		glLineWidth(2);
		glPopMatrix();
		/*End Text Display*/
		glFlush();
		glutSwapBuffers();
	}

	void myinit(void)
	{
		char i = 1;
		qobj = gluNewQuadric();
		SetMaterial(mat_specular2, mat_ambient2, mat_diffuse2, mat_shininess2);
		glEnable(GL_DEPTH_TEST);
		MechTorso(i);
		MechHip(i);
		Shoulder(i);
		UpperArm(i);
		ForeArm(i);
		UpperLeg(i);
	}

	void myReshape(int w, int h)
	{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0, 1.2, -5.5);/* viewing transform  */
	}
#ifdef ANIMATION

	void animation_walk(void) //idle func idlefunc=NULL to stop animation
	{
		float angle;
		static int step;
		if (step == 0 || step == 2) {
			if (frame >= 0.0 && frame <= 21.0) {   //for diff type of motion 'if'condition





 /*
=============================================================================================
PAGE 40-47
=============================================================================================
*/



				if (frame == 0.0) frame = 3.0;
				angle = (180 / M_PI) * (acos(((cos((M_PI / 180) * frame) * 2.043) + 1.1625) / 3.2059));
				//conversion for rotation matrix

				if (frame > 0)
					elevation = -(3.2055 - (cos((M_PI / 180) * angle) * 3.2055));
				else
					elevation = 0.0;

				if (step == 0)
				{
					hip11 = -(frame * 1.7);
					if (1.7 * frame > 15) heel1 = frame * 1.7;
					heel2 = 0;
					ankle1 = frame * 1.7;
					if (frame > 0)
						hip21 = angle;
					else
						hip21 = 0;
					ankle2 = -hip21;
					shoulder1 = frame * 1.5;
					shoulder2 = -frame * 1.5;
					elbow1 = frame;
					elbow2 = -frame;
				}
				else
				{
					hip21 = -(frame * 1.7);
					if (1.7 * frame > 15)
						heel2 = frame * 1.7;
					heel1 = 0;
					ankle2 = frame * 1.7;
					if (frame > 0)
						hip11 = angle;
					else
						hip11 = 0;
					ankle1 = -hip11;
					shoulder1 = -frame * 1.5;
					shoulder2 = frame * 1.5;
					elbow1 = -frame;
					elbow2 = frame;
				}
				if (frame == 21)
					step++;
				if (frame < 21)
					frame = frame + 3.0;
			}
		}
		if (step == 1 || step == 3)
		{
			if (frame <= 21.0 && frame >= 0.0)
			{
				angle = (180 / M_PI) * (acos(((cos((M_PI / 180)*frame)* 2.043) + 1.1625) / 3.2029));
				if (frame > 0)
					elevation = -(3.2055 - (cos((M_PI / 180) * angle)*3.2055));
				else
					elevation = 0.0;
				if (step == 1){
					elbow2 = hip11 = -frame;
					elbow1 = heel1 = frame; heel2 = 15;
					ankle1 = frame;

					if (frame > 0)
						hip21 = angle;
					else
						hip21 = 0;

					ankle2 = -hip21;  shoulder1 = 1.5 * frame; shoulder2 = -frame * 1.5;
				}
				else
				{
					elbow1 = hip21 = -frame;
					elbow2 = heel2 = frame;
					heel1 = 15;
					ankle2 = frame;
					if (frame >0)
						hip11 = angle;
					else
						hip11 = 0;
					ankle1 = -hip11;
					shoulder1 = -frame * 1.5;
					shoulder2 = frame* 1.5;
				}
				if (frame == 0.0)
					step++;
				if (frame > 0)
					frame = frame - 3.0;
			}
		}
		if (step == 4) step = 0;
		distance += 0.1678;
		glutPostRedisplay();//refresh screen with new values
	}
#endif



	void animation(void) { animation_walk(); } //calling idle func /*/ARGSUSED1*/ 

	void keyboard(unsigned char key, int x, int y)
	{
		int i = 0;
		switch(key) {   /*start arm control functions */

		case 'q': {shoulder2Subtract();	i++; } break;
		case 'a': {shoulder2Add();	i++; } break;
		case 'w': {shoulder1Subtract();	i++; } break;
		case 's': {shoulder1Add();	i++; } break;
		case '2': {shoulder3Add();	i++; } break;
		case '1': {shoulder4Add();	i++; } break;
		case '4': {shoulder3Subtract();	i++; } break;
		case '3': {shoulder4Subtract();	i++; } break;
		case 'z': {lat2Raise();      i++; } break;
		case 'Z': {lat2Lower();	i++; }break;
		case 'x': {lat1Raise();      i++; } break;
		case 'X': {lat1Lower();	i++; }break;
		case 'A': {elbow2Add();	i++; }break;
		case 'Q': {elbow2Subtract(); i++; }break;
		case 'S': {elbow1Add();	i++; } break;
		case 'W': {elbow1Subtract(); i++; } break;
			/*end of arm control functions*/
			/*start of torso control functions*/
		case 'd': { RotateAdd(); i++; } break;
		case 'g': { RotateSubtract(); i++; }break;
		case 'r': { MechTiltAdd(); i++; }break;
		case 'f': {	MechTiltSubtract(); i++; }break;
			/*start of torso control functions*/
			/*end of leg control functions*/
		case 'h': { RaiseLeg2Forward(); i++; } break;
		case 'y': {	LowerLeg2Backwards(); i++; } break;
		case 'Y': { RaiseLeg2Outwards(); i++; } break;
		case 'H': {	LowerLeg2Inwards();	i++; } break;
		case 'j': {	RaiseLeg1Forward(); 	i++; } break;
		case 'u': {	LowerLeg1Backwards(); i++; } break;
		case 'U': {	RaiseLeg1Outwards(); 	i++; } break;
		case 'J': {	LowerLeg1Inwards(); 	i++; } break;
			/*end of leg control functions */
	}

	if (i)
		glutPostRedisplay();
}
/*ARGSUSED1*/


void special(int key, int x, int y) 
{
	int i = 0;
	switch (key) {
		/* start of view position functions */
	case GLUT_KEY_RIGHT: { 	TurnRight();	i++; } 	break;
	case GLUT_KEY_LEFT: { 	TurnLeft();	i++; } 	break;
	case GLUT_KEY_DOWN: { 	TurnForwards(); i++; } break;
	case GLUT_KEY_UP: { 	TurnBackwards(); i++; } 	break;
		/* end of view postions functions */
	}
	if (i) glutPostRedisplay();
}

void menu_select(int mode) {
	switch (mode)
	{
		case 1: glutIdleFunc(animation); break;
		case 2: glutIdleFunc(NULL);	break;
		case 3: exit(EXIT_SUCCESS);
	}
}
/*ARGSUSED */

void null_select(int mode) { }

void glutMenu(void)
{
	glutCreateMenu(menu_select);
#ifdef ANIMATION
	glutAddMenuEntry("Start Walk", 1);
	glutAddMenuEntry("Stop Walk", 2);
#endif 
	glutAddMenuEntry("Quit", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
	/*   start of glut windosGng and control functions*/
	glutInit(&argc, argv); //initialize cmd line arg
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // set type of display 
	glutInitWindowSize(800, 600);	//resolution
	glutCreateWindow("OpenGL project: By Arun And Mallikarjuna");
	//Output window title
	myinit();	//calling init function.
				//set graphics functions 
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMenu();
	glutMainLoop();
	/* end of glut windowing and control functions */
	return 0; /*ANSI C requires main to return int.*/
}