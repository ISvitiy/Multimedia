//#define _CRT_SECURE_NO_WARNINGS
//#include <gl/glut.h>
//#include <gl/gl.h>
//#include <cmath>
//#include <time.h>
//#include <sys/timeb.h>
//#define _USE_MATH_DEFINES
//const double M_PI = 3.14;
//
//
//const float clockR = 80.0f,
//clockVol = 100.0f,
//angle1min = M_PI / 30.0f,
//
//minStart = 0.9f,
//minEnd = 1.0f,
//
//stepStart = 0.8f,
//stepEnd = 1.0f;
//
//float angleHour = 0,
//angleMin = 0,
//angleSec = 0;
//
//
//
//void newLine(float rStart, float rEnd, float angle){
//	float c = cos(angle), s = sin(angle);
//	glVertex2f(clockR*rStart*c, clockR*rStart*s);
//	glVertex2f(clockR*rEnd*c, clockR*rEnd*s);
//}
//
//
//
//void RenderScene(void){
//	int i;
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glLineWidth(2.0f);
//	glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_POINT_SMOOTH);
//	glEnable(GL_POLYGON_SMOOTH);
//
//	glBegin(GL_LINES);
//	for (i = 0; i<60; i++){
//		if (i % 5){ // normal minute
//			if (i % 5 == 1)
//				glColor3f(1.0f, 1.0f, 1.0f);
//			newLine(minStart, minEnd, i*angle1min);
//		}
//		else{
//			glColor3f(1.0f, 0.0f, 0.0f);
//			newLine(stepStart, stepEnd, i*angle1min);
//		}
//	}
//	glEnd();
//
//	glLineWidth(3.0f);
//	glBegin(GL_LINES);
//	newLine(0.0f, 0.5f, -angleHour + M_PI / 2);
//	newLine(0.0f, 0.8f, -angleMin + M_PI / 2);
//	glEnd();
//
//	glLineWidth(1.0f);
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glBegin(GL_LINES);
//	newLine(0.0f, 0.8f, -angleSec + M_PI / 2);
//	glEnd();
//
//	glutSwapBuffers();
//}
//
//void SetupRC(void){
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//}
//
/////////////////////////////////////////////////////////////
//// Called by GLUT library when the window has chanaged size
//void ChangeSize(GLsizei w, GLsizei h){
//	GLfloat aspectRatio;
//
//	// Prevent a divide by zero
//	if (h == 0)
//		h = 1;
//
//	// Set Viewport to window dimensions
//	glViewport(0, 0, w, h);
//
//	// Reset coordinate system
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	// Establish clipping volume (left, right, bottom, top, near, far)
//	aspectRatio = (GLfloat)w / (GLfloat)h;
//	if (w <= h)
//		glOrtho(-clockVol, clockVol, -clockVol / aspectRatio, clockVol / aspectRatio, 1.0, -1.0);
//	else
//		glOrtho(-clockVol * aspectRatio, clockVol * aspectRatio, -clockVol, clockVol, 1.0, -1.0);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//
//void TimerFunction(int value){
//	struct timeb tb;
//	time_t tim = time(0);
//	struct tm* t;
//	t = localtime(&tim);
//	ftime(&tb);
//
//	angleSec = (float)(t->tm_sec + (float)tb.millitm / 1000.0f) / 30.0f * M_PI;
//	angleMin = (float)(t->tm_min) / 30.0f * M_PI + angleSec / 60.0f;
//	angleHour = (float)(t->tm_hour > 12 ? t->tm_hour - 12 : t->tm_hour) / 6.0f * M_PI +
//		angleMin / 12.0f;
//
//	glutPostRedisplay();
//	glutTimerFunc(33, TimerFunction, 1);
//}
//
/////////////////////////////////////////////////////////////
//// Main program entry point
//int main(int argc, char* argv[]){
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	glutCreateWindow("glClock by bobo");
//
//	glutDisplayFunc(RenderScene);
//	glutReshapeFunc(ChangeSize);
//	glutTimerFunc(33, TimerFunction, 1);
//
//	SetupRC();
//
//	glutMainLoop();
//
//	return 0;
//}


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gl/glut.h>
#include <cstring>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define PI 3.141592653589793

GLfloat secAngle = 0.0;
GLfloat minAngle = 0.0;
GLfloat hourAngle = 0.0;
GLfloat hour = 0.0;

void draw();
void reshape(int width, int height);
void init();
void keyboard(unsigned char, int, int);
void drawClock();
void rotateSeconds();
void Synchronize();
void outputText(double x, double y, double z, double scale, char *s);


void Synchronize()
{
	GLfloat h, m, s;

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "System: %I:%S", timeinfo);

	if (timeinfo->tm_hour > 12) 
	{
		h = (timeinfo->tm_hour - 12) - (hourAngle / 30.0);
	}
	else
	{
		h = (timeinfo->tm_hour) - (hourAngle / 30.0);
	}

	m = timeinfo->tm_min - (minAngle / 6.0);
	s = timeinfo->tm_sec - (secAngle / 6.0);

	printf("Sistem Saati: %d : %d :%d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	printf("Sistem Saati Ayarlanıyor...\n");
	secAngle = timeinfo->tm_sec * 6.0;
	minAngle = timeinfo->tm_min * 6.0;

	if (timeinfo->tm_hour > 12) 
	{
		hourAngle = ((timeinfo->tm_hour - 12) * 30.0) + (float)((float)1 / 12.0 * minAngle);
		hour = ((timeinfo->tm_hour - 12) * 30.0);
	}
	else
	{
		hourAngle = ((timeinfo->tm_hour) * 30.0) + (float)((float)1 / 12.0 * minAngle);
		hour = ((timeinfo->tm_hour - 12) * 30.0);
	}
	printf("Saat Açısı  : %3.2f [%3.1f]\n", hourAngle, (float)((float)1 / 12 * minAngle));
	printf("Dakika Açısı: %3.2f\n", minAngle);
	printf("Saat Hatası: %3.1f h:%3.1fm:%3.1fs\n", h, m, s);
}



void rotateSeconds(int extra)
{
	secAngle += 6.0;

	if (secAngle == 360.0)
	{
		secAngle = 0.0;
		minAngle += 6.0;
		hourAngle = hour + ((float)1.0 / 12.0 * minAngle);
		Synchronize();
		if (minAngle == 360.0)
		{
			minAngle = 0.0;
			hourAngle += 6.0;

			if (hourAngle == 360.0)
			{
				hourAngle = 0.0;
			}
		}
	}
	//printf("Saat: %3d:%3.0f:%3.0f [%3.1f-%3.1f-%3.1f]\n", (int)(((hour/30.0)+12)), minAngle/6, secAngle/6, hourAngle, minAngle, secAngle);
	printf("Saat: %3dh:%3.0fm:%3.0fs [%3.1f-%3.1f-%3.1f]\n", (int)(hour / 30.0), minAngle / 6, secAngle / 6, hourAngle, minAngle, secAngle);
	glutPostRedisplay();
	glutTimerFunc(1000, rotateSeconds, 0);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	}
}


void init()
{
}


void outputText(double x, double y, double z, double scale, char *s)
{
	int i;

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	for (i = 0; i<strlen(s); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
	glPopMatrix();
}

void drawClock() {

	char buff[100];
	GLfloat x1 = 0.0;
	GLfloat y1 = 0.0;
	GLfloat z1 = 0.0;
	GLfloat radius = 10.0;
	GLfloat smallradius = 3.0;
	int angle;

	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glOrtho(0.0, 20.0, 0.0, 20.0, -10.0, 10.0);

	// Draw circle
	glPushMatrix();
	glTranslatef(10.0, 10.0, 0.0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 0.2, 1.0);
	glVertex3f(x1, y1, z1);
	for (angle = 0; angle <= 360; angle += 1)
		glVertex3f(x1 + cos(angle * PI / 180.0f)* radius, y1 + sin(angle * PI / 180.0f) * radius, z1);
	glEnd();
	glPopMatrix();

	//draw smaller circle
	// draw ticks
	glPushMatrix();
	glTranslatef(10.0, 10.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glLineWidth(2);
	for (angle = 0; angle <= 360; angle += 30)
	{
		glBegin(GL_LINES);
		if (angle == 0.0 || angle == 90.0 || angle == 180.0 || angle == 270.0 || angle == 360.0)
		{
			glColor3f(1.0, 0.2, 0.2);
			glVertex3f(x1 + cos(angle * PI / 180.0f)* (radius - 1.2), y1 + sin(angle * PI / 180.0f) * (radius - 1.2), z1 + 0.1);
			glVertex3f(x1 + cos(angle * PI / 180.0f)* radius, y1 + sin(angle * PI / 180.0f) * radius, z1 + 0.1);
		}
		else
		{
			glColor3f(0.2, 0.2, 0.2);
			glVertex3f(x1 + cos(angle * PI / 180.0f)* (radius - 0.5), y1 + sin(angle * PI / 180.0f) * (radius - 0.5), z1);
			glVertex3f(x1 + cos(angle * PI / 180.0f)* radius, y1 + sin(angle * PI / 180.0f) * radius, z1);
		}
		glEnd();
	}
	glPopMatrix();

	// Draw seconds line
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(1);
	glPushMatrix();

	glTranslatef(10.0, 10.0, 0.0);
	glRotatef(-secAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 2.0);
	glVertex3f(0.0, 8.5, 2.0);
	glEnd();
	glPopMatrix();

	// Draw minutes line
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2);
	glPushMatrix();

	glTranslatef(10.0, 10.0, 0.0);
	glRotatef(-minAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 9.0, 1.0);
	glEnd();
	glPopMatrix();

	// Draw hour line
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(3);
	glPushMatrix();

	glTranslatef(10.0, 10.0, 0.0);
	glRotatef(-hourAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 6.5, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(10.0);
	glPushMatrix();
	glTranslatef(10.0, 10.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(0.0, 0.0, 4.0);
	glEnd();
	glPopMatrix();

	sprintf(buff, "%2d:%2.0f:%2.0f", (int)((hour / 30.0) + 12), minAngle / 6, secAngle / 6, hourAngle, minAngle, secAngle);
	
	outputText(6.0, 12.0, 3.0, 0.01, buff);

	glFlush();
}

void reshape(int w, int h) {

	glutReshapeWindow(w, h);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(0.0, 20.0, 0.0, 20.0*((double)h / (double)w), -10.0, 10.0);
	else
		glOrtho(0.0, 20.0*((double)w / (double)h), 0.0, 20.0, -10.0, 10.0);
	glutDisplayFunc(drawClock);
}

void main(int argc, char* argv[])
{
	//	glutInit(&argc, argv[0]);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("OpenGL Clock");
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000, rotateSeconds, 0);
	Synchronize();

	glutMainLoop();
	//	return 0;

}