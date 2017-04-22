#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;

GLfloat length = 0.1f, movelength = 0.02f;
GLfloat angle = 3.1415926535898f / 720.0f;

class Camera {
public:
	Camera()
	{
		cameraPosX = cameraPosY = 0.0f; cameraPosZ = 1.0f;
		cameraUpX = 0; cameraUpY = 1.0; cameraUpZ = 0;
		d_pitch = d_yaw = 0.0f;
		RR();
	}

	void moveForward(GLfloat const distance)
	{
		cameraPosX += cameraFrontX*distance;
		cameraPosY += cameraFrontY*distance;
		cameraPosZ += cameraFrontZ*distance;
	}

	void moveBack(GLfloat const distance)
	{
		cameraPosX -= cameraFrontX*distance;
		cameraPosY -= cameraFrontY*distance;
		cameraPosZ -= cameraFrontZ*distance;
	}

	void moveRight(GLfloat const distance)
	{
		cameraPosX += cameraRightX*distance;
		cameraPosY += cameraRightY*distance;
		cameraPosZ += cameraRightZ*distance;
	}

	void moveLeft(GLfloat const distance)
	{
		cameraPosX -= cameraRightX*distance;
		cameraPosY -= cameraRightY*distance;
		cameraPosZ -= cameraRightZ*distance;
	}

	void rotate(GLfloat const pitch, GLfloat const yaw)
	{
		d_pitch += pitch;
		d_yaw += yaw;
		RR();
	}

	void RR()
	{
		cameraFrontX = -sin(d_yaw)*cos(d_pitch);
		cameraFrontY = sin(d_pitch);
		cameraFrontZ = -cos(d_yaw)*cos(d_pitch);
		GLfloat sum = sqrt(pow(cameraFrontX, 2) + pow(cameraFrontY, 2) + pow(cameraFrontZ, 2));
		cameraFrontX /= sum;
		cameraFrontY /= sum;
		cameraFrontZ /= sum;
		cameraRightX = cos(d_yaw);
		cameraRightY = 0;
		cameraRightZ = -sin(d_yaw);
		sum = sqrt(pow(cameraRightX, 2) + pow(cameraRightY, 2) + pow(cameraRightZ, 2));
		cameraRightX /= sum;
		cameraRightY /= sum;
		cameraRightY /= sum;
	}

	GLfloat pfov, pratio, pnear, pfar;
	GLfloat cameraPosX, cameraPosY, cameraPosZ;
	GLfloat cameraFrontX, cameraFrontY, cameraFrontZ;
	GLfloat cameraRightX, cameraRightY, cameraRightZ;
	GLfloat cameraUpX, cameraUpY, cameraUpZ;
	int mouse_x, mouse_y;
	GLfloat radius = 3.0f, d_pitch, d_yaw;
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
	gluPerspective(60, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.cameraPosX, cam.cameraPosY, cam.cameraPosZ, cam.cameraPosX+cam.cameraFrontX, cam.cameraPosY + cam.cameraFrontY, cam.cameraPosZ + cam.cameraFrontZ, cam.cameraUpX, cam.cameraUpY, cam.cameraUpZ);
	//GLfloat t = clock();
	//camPosX = sin(t / 1000.0)*Radius;
	//camPosZ = cos(t / 1000.0)*Radius;
	glPushMatrix();
	glTranslatef(0.5, -0.5, -1.0);
	cube();
	glPopMatrix();
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
	if (state == GLUT_DOWN)
	{
		cam.mouse_x = x;
		cam.mouse_y = y;
	}
}

void mousemove(int x, int y)
{
	GLfloat pitch, yaw;
	yaw = (cam.mouse_x - x)*angle;
	pitch = (cam.mouse_y - y)*angle;
	cam.mouse_x = x;
	cam.mouse_y = y;
	cam.rotate(pitch, yaw);
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
	glutMouseFunc(mouse);
	glutMotionFunc(mousemove);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}