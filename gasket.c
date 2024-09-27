#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float x, y, z, height = 40, r = 70, i = 0.4, lightAngle = 0 ,cameraAngle = 0, normal[3];
int isOn = 0, grassPolygons = 0;

typedef float point3[3];
GLfloat pos[4] = { -50, 0, 0, 1 };

GLfloat green[] = { 0, 1, 0, 1 };
GLfloat yellow[] = { 1, 1, 0, 1 };
GLfloat white[] = { 1, 1, 1, 1 };
GLfloat black[] = { 0, 0, 0, 1 };
GLfloat brown[] = { 160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0, 1.0 };
GLfloat maroon[] = { 128.0 / 255.0, 0, 0, 1.0 };

// TOOLS

void normalize(float* v) 
{
	float length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (length != 0) {
		for (int i = 0; i < 3; i++) {
			v[i] = v[i] / length;
		}
	}
}

void cross_product(float* a, float* b, float* result) 
{
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = -(a[0] * b[2] - a[2] * b[0]);
	result[2] = a[0] * b[1] - a[1] * b[0];
	normalize(result);
}

void normal_vectors(float* a, float* b, float* c, float* result) 
{
	float x[] = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };				// Vertex differrences, n = (b-a) X (c-a)
	float y[] = { c[0] - a[0], c[1] - a[1], c[2] - a[2] };
	cross_product(x, y, result);
}

void subdivide(float v1[3], float v2[3], float v3[3], int depth) 
{
	if (depth == 0) {                        // End condition
		glBegin(GL_TRIANGLES);
			glVertex3fv(v1);
			glVertex3fv(v2);
			glVertex3fv(v3);
		glEnd();
		return;
	}

	point3 v12, v23, v31;
	for (int i = 0; i < 3; i++) {           // Calculate 3 new vertices at the midpoint of the previous ones 
		v12[i] = (v1[i] + v2[i]) / 2;
		v23[i] = (v2[i] + v3[i]) / 2;
		v31[i] = (v3[i] + v1[i]) / 2;
	}

	normalize(v12);							// Move the 3 new vertices on the unit sphere										
	normalize(v23);							// By normalizing we ensure norm is 1, maintining direction of vertex
	normalize(v31);

	subdivide(v1, v12, v31, depth - 1);     // Repeat recursively for the 4 new triangles
	subdivide(v12, v2, v23, depth - 1);
	subdivide(v31, v23, v3, depth - 1);
	subdivide(v12, v23, v31, depth - 1);
}


void myinit(void)
{
	/* attributes */
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
 	glClearColor(0.0, 0.0, 0.0, 0.0); /* black background */
	glColor3f(0.0, 0.0, 0.0); /* draw in black */

	/* set up viewing */
	/* 500 x 500 window with origin lower left */

	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();

	 glFrustum(-1, 1, -1, 1, 1, 300);							// Perspective view

	 glMatrixMode(GL_MODELVIEW);

	 glShadeModel(GL_SMOOTH);
	 glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);		// Viewer is close to the scene
}

// LIGHTS

void staticLight()
{
	glPushMatrix();

	glEnable(GL_LIGHT0);
	glRotatef(lightAngle, 0, 0, -1);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	GLfloat diff[] = { 1 * i, 1 * i, 0, 1 };					// Intensity changing based on sun/light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, diff);

	glPopMatrix();
}

void spotLight()
{
	glPushMatrix();	

	if (isOn) glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);
	GLfloat pos1[4] = { x, height, z, 1 };						// Spotlight position same as camera
	GLfloat direction[3] = { -x, -height, -z };
	
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	glPopMatrix();
}

// OBJECTS

void drawSun()    
{
	glPushMatrix();

	point3 v[]= { {0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333},								// Original tetraedron vertices
				{-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333} };

	glRotatef(lightAngle, 0, 0, -1);														// Sun tracking the point light source
	glTranslatef(pos[0], pos[1], pos[2]);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
	
	subdivide(v[0], v[1], v[3], 3);															// Recursive subdivision to draw sphere from tetraedron
	subdivide(v[0], v[1], v[2], 3);															// Subdivide each tetraedron side
	subdivide(v[1], v[2], v[3], 3);
	subdivide(v[0], v[2], v[3], 3);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);									// Turn off sun emission to not affect other objects
	glPopMatrix();
}

void drawGrass()
{
	if (!grassPolygons)
	{
		float grass[4][3] = {
		-40.0 , -5.0, 40.0,
		40.0, -5.0, 40.0,
		40.0, -5.0, -5.0,
		-40.0, -5.0, -5.0
		};

		glPushMatrix();

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green);

		glBegin(GL_POLYGON);
			normal_vectors(grass[0], grass[1], grass[2], normal);
			glNormal3fv(normal);
			glVertex3fv(grass[2]);
			glVertex3fv(grass[3]);
			glVertex3fv(grass[0]);
			glVertex3fv(grass[1]);
		glEnd();

		glPopMatrix();
	}
	else
	{
		float x_start, x_end, z_start, z_end, y, x_step, z_step, x0, x1, z0, z1;

		x_start = -40.0;              // Coordinates from original grass polygon
		x_end = 40.0;
		z_start = -5.0;
		z_end = 40.0;
		y = -5.0;
		x_step = (x_end - x_start) / 10;   // x,z of each small polygon to create 10x10 grid
		z_step = (z_end - z_start) / 10;

		glPushMatrix();

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green);

		for (int i = 0; i < 10; i++) 
		{
			for (int j = 0; j < 10; j++) 
			{
				 x0 = x_start + i * x_step;				// Coordinates of small polygons
				 x1 = x_start + (i + 1) * x_step;
				 z0 = z_start + j * z_step;
				 z1 = z_start + (j + 1) * z_step;

				float grass[4][3] = {
					{x0, y, z0},
					{x1, y, z0},
					{x1, y, z1},
					{x0, y, z1}
				};

				glBegin(GL_POLYGON);
					normal_vectors(grass[2], grass[1], grass[0], normal);
					glNormal3fv(normal);
					glVertex3fv(grass[2]);
					glVertex3fv(grass[3]);
					glVertex3fv(grass[0]);
					glVertex3fv(grass[1]);
				glEnd();
			}
		}
		glPopMatrix();
	}
}

void drawHouse()
{
	float building[5][4][3] = {
		{
			{-5.0, -5.0, 25.0},  // FRONT
			{5.0, -5.0, 25.0},    
			{5.0, 5.0, 25.0},     
			{-5.0, 5.0, 25.0}     
		},
		
		{
			{-5.0, -5.0, 5.0},	 // BACK
			{-5.0, 5.0, 5.0},
			{5.0, 5.0, 5.0}, 
			{5.0, -5.0, 5.0}		   
		},

		{
			{-5.0, -5.0, 5.0},   // LEFT
			{-5.0, -5.0, 25.0},  
			{-5.0, 5.0, 25.0},   
			{-5.0, 5.0, 5.0}   
		},
		
		{
			{5.0, -5.0, 25.0},  // RIGHT
			{5.0, -5.0, 5.0},   
			{5.0, 5.0, 5.0},    
			{5.0, 5.0, 25.0}    
		},
		
		{
			{-5.0, 5.0, 25.0},  // TOP
			{5.0, 5.0, 25.0},     
			{5.0, 5.0, 5.0},    
			{-5.0, 5.0, 5.0}    
		},
		
	};

	float roof1[2][3][3] = {
		{
			{-5.0, 5.0, 25.0},   // FRONT
			{5.0, 5.0, 25.0},    
			{0.0, 15.0, 25.0}   
		},
		
		{
			{-5.0, 5.0, 5.0}, 
			{0.0, 15.0, 5.0},	// BACK
			{5.0, 5.0, 5.0}        
		}
	};

	float roof2[2][4][3] = {
		
		{
			{-5.0, 5.0, 5.0},    // LEFT
			{-5.0, 5.0, 25.0},
			{0, 15.0, 25.0},  
			{0, 15.0, 5.0},
			

		},

		{
			{0, 15.0, 5.0},     // RIGHT
			{0, 15.0, 25.0},
			{5.0, 5.0, 25.0},  
			{5.0, 5.0, 5.0},
			
			  
			
		}
		
	};

	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, brown);
	
	for (int i = 0; i < 5; i++) 
	{
		normal_vectors(building[i][0], building[i][1], building[i][2], normal);  // Calculate normals for each wall

		glBegin(GL_POLYGON);
			glNormal3fv(normal);
			for (int j = 0; j < 4; j++) 
			{
				glVertex3fv(building[i][j]);
			}
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, maroon);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, maroon);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

	for (int i = 0; i < 2; i++) 
	{
		normal_vectors(roof1[i][0], roof1[i][1], roof1[i][2], normal);

		glBegin(GL_TRIANGLES);
			glNormal3fv(normal);
			for (int j = 0; j < 3; j++) 
			{
				glVertex3fv(roof1[i][j]);
			}
		glEnd();
	}

	for (int i = 0; i < 2; i++) 
	{
		normal_vectors(roof2[i][0], roof2[i][1], roof2[i][2], normal);    

		glBegin(GL_POLYGON);
			glNormal3fv(normal);
			for (int j = 0; j < 4; j++) 
			{
				glVertex3fv(roof2[i][j]);
			}
		glEnd();
	}

	glPopMatrix();
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /*clear the window */

	glLoadIdentity();

	x = r * sin(cameraAngle);							// Camera position in the circle with range r
	z = r * cos(cameraAngle);
	gluLookAt(x, height, z, 0, 0, 0, 0, 1, 0);
						
	staticLight();
	spotLight();
	
	drawSun();
	drawGrass();
	drawHouse();

	glutSwapBuffers();
}

// MENUS

void polygon_menu(int id) {
	if (id == 1) {
		grassPolygons = 0;
	}
	else if (id == 2) {
		grassPolygons = 1;
	}
}

void spotlight_menu(int id) {
	if (id == 3) {
		isOn = 1;
	}
	else if (id == 4) {
		isOn = 0;
	}
}

void shade_menu(int id) {
	if (id == 5) {
		glShadeModel(GL_SMOOTH);
	}
	else if (id == 6) {
		glShadeModel(GL_FLAT);
	}
}

void demo_menu(int id) //menu callback
{	
	if (id == 7) exit(0);
}

void idle() 
{
	lightAngle += 1;
	if (lightAngle <= 90)
		i = 0.4 + (lightAngle / 90.0) * (1.0 - 0.4);			// Before noon smoothly increase light intensity until i = 1
	else
		i = 1.0 - ((lightAngle - 90) / 90.0) * (1.0 - 0.4);		// After noon smoothly decrease light intensity until i = 0.4
	if (lightAngle >= 180.0)
	{
		lightAngle -= 180.0;									// When sun sets reset position to dawn
	}
		
	glutPostRedisplay();
}

void move_camera(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
		{
			cameraAngle += 0.3;
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			cameraAngle -= 0.3;
			break;
		}
		case GLUT_KEY_UP:
		{
			height += 5;
			break;
		}
		case GLUT_KEY_DOWN:
		{
			height -= 5;
			break;
		}
	}
	
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
/* Standard GLUT initialization */

	    glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); /* default, not needed */
	    glutInitWindowSize(500,500); /* 500 x 500 pixel window */
	    glutInitWindowPosition(0,0); /* place window top left on display */
	    glutCreateWindow("Daynight Cycle"); /* window title */
		myinit(); /* set attributes */

		int poly_menu = glutCreateMenu(polygon_menu);
		glutAddMenuEntry("Low",1);
		glutAddMenuEntry("High",2);

		int spot_menu = glutCreateMenu(spotlight_menu);
		glutAddMenuEntry("On", 3);
		glutAddMenuEntry("Off", 4);

		int s_menu = glutCreateMenu(shade_menu);
		glutAddMenuEntry("Smooth", 5);
		glutAddMenuEntry("Flat", 6);

		glutCreateMenu(demo_menu);
		glutAddSubMenu("Polygon", poly_menu);
		glutAddSubMenu("Spotlight", spot_menu);
		glutAddSubMenu("Shade", s_menu);
		
		glutAddMenuEntry("Quit", 7);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutDisplayFunc(display); /* display callback invoked when window opened */
		glutIdleFunc(idle);
		glutSpecialFunc(move_camera);

	    glutMainLoop(); /* enter event loop */
}