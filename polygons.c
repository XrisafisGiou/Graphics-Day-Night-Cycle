//#include <GL/glut.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//float left = 0, right = 500, bottom = 0, top = 500, dx = 0, dy = 0, prevx = 0, prevy = 0;
//typedef GLfloat point2[2];
//point2 vertices[6];
//int n, flag = 0;
//float red, green, blue;
//point2* points;
//
//void myinit(void)
//{
//	/* attributes */
//	glEnable(GL_BLEND);
//	glClearColor(1.0, 1.0, 1.0, 0.0); /* white background */
//	glColor3f(0.0, 0.0, 0.0); /* draw in black */
//
//	/* set up viewing */
//	/* 500 x 500 window with origin lower left */
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void hexagon(int n)
//{
//	int j, k;
//	point2 q = { 400.0,500.0 };
//	vertices[0][0] = 300.0;
//	vertices[0][1] = 619.0;
//	vertices[1][0] = 475.0;
//	vertices[1][1] = 719.0;
//	vertices[2][0] = 649.0;
//	vertices[2][1] = 619.0;
//	vertices[3][0] = 649.0;
//	vertices[3][1] = 418.0;
//	vertices[4][0] = 475.0;
//	vertices[4][1] = 317.0;
//	vertices[5][0] = 300.0;
//	vertices[5][1] = 417.0;
//
//	for (k = 0; k < n; k++)
//	{
//		j = rand() % 6;
//
//		q[0] = (q[0] + vertices[j][0]) * 1.0 / 3.0;
//		q[1] = (q[1] + vertices[j][1]) * 1.0 / 3.0;
//		points[k][0] = q[0];
//		points[k][1] = q[1];
//	}
//}
//
//void pentagon(int n)
//{
//	int j, k;
//	point2 q = { 400.0,500.0 };
//	vertices[0][0] = 497.2;
//	vertices[0][1] = 303.6;
//	vertices[1][0] = 301.2;
//	vertices[1][1] = 303.6;
//	vertices[2][0] = 240.4;
//	vertices[2][1] = 490.0;
//	vertices[3][0] = 398.8;
//	vertices[3][1] = 605.2;
//	vertices[4][0] = 557.2;
//	vertices[4][1] = 490.0;
//
//	for (k = 0; k < n; k++)
//	{
//		j = rand() % 5;
//
//		q[0] = (q[0] + vertices[j][0]) * 3.0 / 8.0;
//		q[1] = (q[1] + vertices[j][1]) * 3.0 / 8.0;
//		points[k][0] = q[0];
//		points[k][1] = q[1];
//	}
//}
//
//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */
//
//	for (int k = 0; k < n; k++)
//	{
//		if (flag)
//		{
//			red = (float)rand() / RAND_MAX;
//			green = (float)rand() / RAND_MAX;
//			blue = (float)rand() / RAND_MAX;
//		}
//		else
//		{
//			red = 0.0;
//			green = 0.0;
//			blue = 0.0;
//		}
//		glColor3f(red, green, blue);
//		glDrawBuffer(GL_FRONT_AND_BACK);
//
//		glBegin(GL_POINTS);
//		glVertex2fv(points[k]);
//		glEnd();
//
//	}
//	if (flag) glutPostRedisplay();
//
//	glutSwapBuffers();
//	glFlush(); /* clear buffers */
//}
//
//void demo_menu(int id) //menu callback
//{
//	if (id == 1)
//	{
//		n = 15000;
//		flag = 1;
//		hexagon(n);
//		glutPostRedisplay();
//	}
//	else if (id == 2)
//	{
//		n = 12000;
//		flag = 0;
//		hexagon(n);
//		glutPostRedisplay();
//	}
//	else if (id == 3)
//	{
//		n = 12000;
//		flag = 0;
//		pentagon(n);
//		glutPostRedisplay();
//	}
//	else  if (id == 4) exit(0);
//}
//
//void move(int x, int y)
//{
//	if (prevx == 0 && prevy == 0) {
//		prevx = x;
//		prevy = y;
//	}
//
//	dx = x - prevx;
//	dy = y - prevy;
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(left, right, bottom, top);
//	glMatrixMode(GL_MODELVIEW);
//	glutPostRedisplay();
//
//	left -= dx;
//	right -= dx;
//	bottom += dy;
//	top += dy;
//	prevx = x;
//	prevy = y;
//}
//
//void mouse(int button, int state, int x, int y)
//{
//	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
//	{
//		prevx = 0;
//		prevy = 0;
//	}
//}
//
//void main(int argc, char** argv)
//{
//
//	/* Standard GLUT initialization */
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); /* default, not needed */
//	glutInitWindowSize(500, 500); /* 500 x 500 pixel window */
//	glutInitWindowPosition(0, 0); /* place window top left on display */
//	glutCreateWindow("Moving Polygons"); /* window title */
//	myinit(); /* set attributes */
//
//	points = (point2*)malloc(15000 * sizeof(point2));
//
//	n = 12000;
//	hexagon(n);
//
//	glutCreateMenu(demo_menu);
//	glutAddMenuEntry("15000 points, random alternating color", 1);
//	glutAddMenuEntry("Hexagon r=1/3", 2);
//	glutAddMenuEntry("Pentagon r=3/8", 3);
//	glutAddMenuEntry("Quit", 4);
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//	glutDisplayFunc(display); /* display callback invoked when window opened */
//	glutMouseFunc(mouse);
//	glutMotionFunc(move);
//	glutMainLoop(); /* enter event loop */
//}
