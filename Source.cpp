#include "windows.h"
#include "gl/Gl.h"
#include "gl/glut.h"
#include "math.h"

#define	checkImageWidth 64
#define	checkImageHeight 64

static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;

int boatStatus = -1;
float boatX = 0;
float boatY = 0;

int carStatus = -1;
float carX = 0;
float carY = 0;
float counter = 0;

char COLOR = 'R';
int flag = 1;

//------------------ CREATE CHECKERED TEXTURE ------------------//

void makeTexture(void)
{
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++)
	{
		for (j = 0; j < checkImageWidth; j++)
		{
			c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)50;
		}
	}
}

//------------------ CREATE SCENERY ------------------//

//------------------ DRAW RIVER ------------------//

void River()
{
	//------> Set color properties

	GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat qaFullAmbient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat qaSurfaceBlue[] = { 0.230, 0.598, 0.761, 1.0 };
	GLfloat qaDeepBlue[] = { 0.059, 0.247, 0.962, 1.0 };
	GLfloat qaLowAmbient[] = { 0.2, 0.2, 0.2, 1.0 };

	//------>  Turn off diffuse and specular reflection. Set ambient light to full.

	glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBlack);
	glMaterialfv(GL_FRONT, GL_SPECULAR, qaBlack);
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaFullAmbient);

	glPushMatrix();

	glBegin(GL_POLYGON);

	//------> Draw River Bottom

	glMaterialfv(GL_FRONT, GL_AMBIENT, qaDeepBlue);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1200, 0, 0.0f);

	//------> Draw River Surface

	glMaterialfv(GL_FRONT, GL_AMBIENT, qaSurfaceBlue);
	glVertex3f(1200, 250, 0.0f);
	glVertex3f(1150, 230, 0.0f);
	glVertex3f(1100, 250, 0.0f);
	glVertex3f(1050, 230, 0.0f);
	glVertex3f(1000, 250, 0.0f);
	glVertex3f(950, 230, 0.0f);
	glVertex3f(900, 250, 0.0f);
	glVertex3f(950, 230, 0.0f);
	glVertex3f(800, 250, 0.0f);
	glVertex3f(850, 230, 0.0f);
	glVertex3f(700, 250, 0.0f);
	glVertex3f(750, 230, 0.0f);
	glVertex3f(600, 250, 0.0f);
	glVertex3f(650, 230, 0.0f);
	glVertex3f(500, 250, 0.0f);
	glVertex3f(550, 230, 0.0f);
	glVertex3f(400, 250, 0.0f);
	glVertex3f(450, 230, 0.0f);
	glVertex3f(300, 250, 0.0f);
	glVertex3f(350, 230, 0.0f);
	glVertex3f(200, 250, 0.0f);
	glVertex3f(250, 230, 0.0f);
	glVertex3f(100, 250, 0.0f);
	glVertex3f(50, 230, 0.0f);
	glVertex3f(0, 250, 0.0f);
	glEnd();

	glPopMatrix();
}

//------------------ DRAW BOAT ------------------//

void Boat(int i)
{
	//------> Set color properties

	GLfloat qaBoatInner[] = { 0.832f, 0.393f, 0.042f, 1.0 };
	GLfloat qaStand[] = { 0.970f, 0.941f, 0.941f, 1.0 };
	GLfloat qaBigFlag[] = { 0.230, 0.598, 0.761, 1.0 };
	GLfloat qaBoatOuter[] = { 0.862f, 0.644f, 0.042f, 1.0 };
	GLfloat qaSmallFlag[] = { 0.640f, 0.0f, 0.0f, 1.0 };
	GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat qaBlue[] = { 0.0, 0.0, 1.0, 1.0 };

	glPushMatrix();

	//------> Draw Stand with Checkered Texture

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);
	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_AMBIENT, qaStand);
	glTexCoord2f(0.0, 0.0); glVertex3f(450, 300, 0.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(460, 300, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(460, 600, 0.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(450, 600, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//------> Draw Boat Inner

	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_AMBIENT, qaBoatInner);
	glVertex3f(300, 280, 0.0f);
	glVertex3f(800, 350, 0.0f);
	glVertex3f(350, 320, 0.0f);
	glEnd();

	//------> Draw Big Flag with Checkered Texture

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);
	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_AMBIENT, qaBigFlag);
	glTexCoord2f(0.0, 0.0); glVertex3f(460, 400, 0.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(650, 400, 0.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(460, 600, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//------> Set Conditions to Change Small Flag Color

	if (COLOR == 'R')
		glMaterialfv(GL_FRONT, GL_AMBIENT, qaSmallFlag);
	else if (COLOR == 'G')
		glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
	else if (COLOR == 'B')
		glMaterialfv(GL_FRONT, GL_AMBIENT, qaBlue);

	//------> Draw Small Flag

	glBegin(GL_POLYGON);
	glVertex3f(350, 550, 0.0f);
	glVertex3f(450, 550, 0.0f);
	glVertex3f(450, 600, 0.0f);
	glEnd();

	//------> Draw Boat Outer

	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_AMBIENT, qaBoatInner);
	glVertex3f(350, 200, 0.0f);
	glVertex3f(700, 200, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, qaBoatOuter);
	glVertex3f(800, 350, 0.0f);
	glVertex3f(300, 280, 0.0f);
	glEnd();

	glPopMatrix();
}

//------------------ SET CONDTION  ------------------//

//------> Set condition to move boat
void MoveBoat()
{
	if (boatStatus == 1)
	{
		boatX += .5; //boatX = boadtX + .5;
	}
	if (boatX > 1200)
	{
		boatX = -600;
	}
	glPushMatrix();
	glTranslatef(boatX, boatY, 0);
	Boat(1);
	glPopMatrix();
}

//------------------ DISPLAY FUNCTION  ------------------//

void DisplayBoat()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

	//*****************************************
	//------>Write  code here

	flag = 1;
	MoveBoat();
	River();

	//*****************************************

	glFlush(); // Render now
	glutPostRedisplay();
	glutSwapBuffers();
}

//------------------ KEYBOARD HANDLING  ------------------//

//------> Boat will start and stop moving on pressing 'S' or 's' Key

void keyboardBoat(unsigned char key, int x, int y)
{
	switch (key) {
	case 's':
	case 'S':
	{
		if (boatStatus == -1)
			boatStatus = 1;
		else if (boatStatus == 1)
			boatStatus = -1;
		break;
	}
	default:
		break;
	}
}

//------------------ MOUSE HANDLING  ------------------//

//------> Small Flag will change its color on pressing left mouse button

void MouseBoat(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (COLOR == 'R')
			COLOR = 'G';
		else if (COLOR == 'G')
			COLOR = 'B';
		else if (COLOR == 'B')
			COLOR = 'R';
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 1)
	{
		DisplayBoat();
	}
}

//------------------ INIT FUNCTION  ------------------//

void MyInit()
{
	glClearColor(0.720, 0.845, 0.916, 0.0);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
	glOrtho(0.0f, 1200, 0.0f, 800, -3.0, 3.0);

	//------> Texture set up

	makeTexture();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0,											// level 0
		GL_RGBA,									// use only R, G, B and A components
		checkImageWidth, checkImageHeight,			//texture has width x height texels
		0,											// no border
		GL_RGBA,									// texels are in RGBA format
		GL_UNSIGNED_BYTE,							// color components are unsigned bytes
		checkImage);

	//------> Lighting set up

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//------> Set lighting intensity and color

	GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	//------> Set the light position

	GLfloat qaLightPosition[] = { 1000, 700, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}

//------> Main function: GLUT runs as a console application starting at main()

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);							// Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(1000, 600);					// Set the window's initial width & height
	glutInitWindowPosition(10, 10);					// Position the window's initial top-left corner

	glutCreateWindow("First Window");
	MyInit();
	glutDisplayFunc(DisplayBoat);
	glutKeyboardFunc(keyboardBoat);					// Register display callback Keyboard handler for window re-paint
	glutMouseFunc(MouseBoat);						// Register display callback Mouse handler for window re-paint

	glutMainLoop();									// Enter the infinitely event-processing loop
	return 0;
}