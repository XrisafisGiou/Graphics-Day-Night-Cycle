//#include <GL/glut.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>
//
//int vx = 1, vy = 0, vz = 1, b = 90;
//float theta = 0, scale = 1, a = 1, rcenter = 90;
//
//void myinit(void)
//{
//	/* attributes */
//	glEnable(GL_BLEND);
//	glEnable(GL_DEPTH_TEST);
//	glClearColor(0.0, 0.0, 0.0, 0.0); /* black background */
//	glColor3f(0.0, 0.0, 0.0); /* draw in black */
//
//	/* set up viewing */
//	/* 500 x 500 window with origin lower left */
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-100.0, 100.0, -100.0, 100.0, -200.0, 200.0);
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void drawCube()
//{
//	glScalef(3.0, 3.0, 3.0); // Cube length needs to be a = 6
//
//	glColor3f(1.0, 0.0, 0.0);
//	glNewList(1, GL_COMPILE);
//
//	glBegin(GL_POLYGON);
//	glVertex3f(-1, 1, 1);
//	glVertex3f(1, 1, 1);
//	glVertex3f(1, -1, 1);
//	glVertex3f(-1, -1, 1);
//	glEnd();
//
//	glEndList();
//
//	glCallList(1);			   // FRONT
//
//	glPushMatrix();
//	glColor3f(1.0, 0.0, 1.0);  // BACK
//	glRotatef(180, 0, 1, 0);
//	glCallList(1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glColor3f(0.0, 0.0, 1.0);  // RIGHT
//	glRotatef(90, 0, 1, 0);
//	glCallList(1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glColor3f(0.0, 1.0, 0.0);  // LEFT
//	glRotatef(-90, 0, 1, 0);
//	glCallList(1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glColor3f(0.0, 1.0, 1.0); // TOP
//	glRotatef(90, 1, 0, 0);
//	glCallList(1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glColor3f(0.0, 1.0, 1.0); // BOTTOM
//	glRotatef(-90, 1, 0, 0);
//	glCallList(1);
//	glPopMatrix();
//}
//
//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /*clear the window */
//
//	glLoadIdentity();
//
//	glTranslatef(0, 0, -b);
//	if (rcenter != b)
//		glTranslatef(0, 0, -rcenter);
//	glRotatef(theta, vx, vy, vz);
//	if (rcenter != b)
//		glTranslatef(0, 0, rcenter);
//
//	glScalef(scale, scale, scale);
//
//	drawCube();
//
//	glutSwapBuffers();
//}
//
//void demo_menu(int id) //menu callback
//{
//	if (id == 1)
//	{
//		rcenter = b;
//	}
//	else if (id == 2)
//	{
//		rcenter = 8 * b / 10;
//	}
//	else  if (id == 3) exit(0);
//}
//
//void idle() {
//	theta += 2;
//	if (theta >= 360.0)
//		theta -= 360.0;
//
//	scale += a * 0.02;
//	if (scale >= 2)
//		a = -1;
//	else if (scale <= 1)
//		a = 1;
//
//	glutPostRedisplay();
//}
//
//void main(int argc, char** argv)
//{
//
//	/* Standard GLUT initialization */
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); /* default, not needed */
//	glutInitWindowSize(500, 500); /* 500 x 500 pixel window */
//	glutInitWindowPosition(0, 0); /* place window top left on display */
//	glutCreateWindow("Moving Cube"); /* window title */
//	myinit(); /* set attributes */
//
//	glutCreateMenu(demo_menu);
//	glutAddMenuEntry("Self Rotate", 1);
//	glutAddMenuEntry("Vertex Rotate", 2);
//	glutAddMenuEntry("Quit", 3);
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//	glutDisplayFunc(display); /* display callback invoked when window opened */
//	glutIdleFunc(idle);
//
//	glutMainLoop(); /* enter event loop */
//}
