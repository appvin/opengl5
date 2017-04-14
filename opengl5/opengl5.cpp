#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;

GLfloat length = 0.5, movelength = 0.2;
//GLfloat camPosX = 0, camPosZ = 1, Radius = 3.0;


class Camera {
public:
	Camera()
	{
		cameraPosX = cameraPosY = cameraPosZ = 3.0;
		cameraUpX = 0; cameraUpY = 1.0; cameraUpZ = 0;
	}

	void moveForward(GLfloat const distance)
	{
		cameraPosZ -= distance;
	}
	void moveBack(GLfloat const distance)
	{
		cameraPosZ += distance;
	}
	void moveRight(GLfloat const distance)
	{
		cameraPosX += distance;
	}
	void moveLeft(GLfloat const distance)
	{
		cameraPosX -= distance;
	}
	void rotate(GLfloat const pitch, GLfloat const yaw)
	{

	}

	GLfloat pfov, pratio, pnear, pfar;
	GLfloat cameraPosX, cameraPosY, cameraPosZ;
	GLfloat cameraFrontX, cameraFrontY, cameraFrontZ;
	GLfloat cameraRightX, cameraRightY, cameraRightZ;
	GLfloat cameraUpX, cameraUpY, cameraUpZ;
};

Camera cam;

void cube()
{
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0, 0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(length, length, length);
	glVertex3f(-length, length, length);
	glVertex3f(-length, -length, length);
	glVertex3f(length, -length, length);

	glColor3f(1.0f, 1.0f, 0);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-length, -length, -length);
	glVertex3f(-length, length, -length);
	glVertex3f(length, length, -length);
	glVertex3f(length, -length, -length);

	glColor3f(0, 1.0f, 0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(length, length, length);
	glVertex3f(length, length, -length);
	glVertex3f(-length, length, -length);
	glVertex3f(-length, length, length);

	glColor3f(0, 1.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-length, -length, -length);
	glVertex3f(length, -length, -length);
	glVertex3f(length, -length, length);
	glVertex3f(-length, -length, length);

	glColor3f(0, 0, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(length, length, length);
	glVertex3f(length, -length, length);
	glVertex3f(length, -length, -length);
	glVertex3f(length, length, -length);

	glColor3f(1.0f, 0, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-length, -length, -length);
	glVertex3f(-length, -length, length);
	glVertex3f(-length, length, length);
	glVertex3f(-length, length, -length);

	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);
	gluPerspective(30, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.cameraPosX, cam.cameraPosY, cam.cameraPosZ, 0, 0, 0, cam.cameraUpX, cam.cameraUpY, cam.cameraUpZ);
	//GLfloat t = clock();
	//camPosX = sin(t / 1000.0)*Radius;
	//camPosZ = cos(t / 1000.0)*Radius;
	//glTranslatef(0.5, -0.5, -1.5);
	cube();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	{
		cam.moveForward(movelength);
		break;
	}
	case 'a':
	{
		cam.moveLeft(movelength);
		break;
	}
	case 's':
	{
		cam.moveBack(movelength);
		break;
	}
	case 'd':
	{
		cam.moveRight(movelength);
		break;
	}
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("cube");
	glutPostRedisplay();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}