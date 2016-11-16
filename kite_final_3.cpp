#include<time.h>
#include<string.h>
#include<iostream>
#include<math.h>
#include <stdio.h>
#include <GL/glut.h>
using namespace std;
float x[4],y[4];
int count=10;
void delay(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

// used for continuous movement in vertical direction and horizontal direction, depends on the value of count
void draw_continuous_vertical(int val)
{
    count--;
    if(count>0)
    {
      glTranslatef(0.0,val,0.0);    
      glutPostRedisplay(); 
      glutTimerFunc(100, draw_continuous_vertical, val);    
    }
}
void draw_continuous_horizontal(int val)
{
	count--;
	if(count>0)
	{
	  glTranslatef(val,0.0,0.0);    
	  glutPostRedisplay(); 
	  glutTimerFunc(100, draw_continuous_horizontal, val);    
	}
}

// special keys call back function used for movement using arrow keys
// count variable and draw_continuous function are used for continuous movement of the kite
void special_keys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
		    count=5;
		    draw_continuous_vertical(3.0);
		    // glTranslatef(0.0,1.0*5,0.0);
		    // glutPostRedisplay();
		    break;  
		case GLUT_KEY_DOWN:
		       	count=5;
		   	draw_continuous_vertical(-3.0);
		    // glTranslatef(0.0,-1.0*5,0.0);
		    // glutPostRedisplay();
		    break; 
		case GLUT_KEY_LEFT:
			count=5;
			draw_continuous_horizontal(-3.0);
		   // glTranslatef(-1.0*5,0.0,0.0);
		   // glutPostRedisplay();
		   	break;  
		case GLUT_KEY_RIGHT:
		   // glTranslatef(1.0*5,0.0,0.0);
		   // glutPostRedisplay();        
			count=5;
			draw_continuous_horizontal(3.0);
		   	break;   
	}
}

// keyboard callback function
void keyboard (unsigned char key, int x, int y)
{ 
	switch (key) {
		case 'q':        
		    glTranslatef(-1.0*5,1.0*5,0.0);
		    glutPostRedisplay();
		    break;  
		case 'w':
		    glTranslatef(1.0*5.0,1.0*5,0.0);
		    glutPostRedisplay();
		    break;  
		case 's':
		    glTranslatef(1.0*5,-1.0*5,0.0);
		    glutPostRedisplay();
		    break;  
		case 'a':
		    glTranslatef(-1.0*5,-1.0*5,0.0);
		    glutPostRedisplay();
		    break;     
		case 27:
		   exit(0);
		   break;
		default:
		   break;
	}  

}


/*
Draw rhombus for kite shape and draw tail using bezier curve
*/
void draw_kite()
{
	glColor3f(0.58, 0.0, 0.76);	
	// draw rhombus (kite)
	glBegin(GL_POLYGON);
	glVertex3f(60.0*1.5,60.0*1.5,0.0);
	glVertex3f(40.0*1.5,80.0*1.5,0.0);
	glVertex3f(60.0*1.5,100.0*1.5,0.0);
	glVertex3f(80.0*1.5,80.0*1.5,0.0);
	glEnd();
	int i;
	double t;

	glColor3f(1.0,1.0,1.0);
	// draw tail using bezier curve with 4 points
	glBegin(GL_POINTS);	
	for (t = 0.0; t < 1.0; t += 0.0005)
	{
	double xt = (pow(1-t, 3)*x[0]+3*t*pow(1-t,2)*x[1]+3*pow(t,2)*(1-t)*x[2]+pow(t, 3)*x[3]);
	double yt = (pow(1-t,3)*y[0]+3*t*pow(1-t,2)*y[1]+3*pow(t,2)*(1-t)*y[2]+pow(t,3)*y[3]);		
	glVertex2f(xt,yt);

	}
	glEnd();  
}

//  display callback function calls draw_kite function
void display(void)

   {
   glClear(GL_COLOR_BUFFER_BIT);
   draw_kite();
   glFlush();

}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
	gluOrtho2D(0.0,800,0.0,800);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  
 
}
int main(int argc, char** argv)
{
	x[0]=10*1.5;x[1]=20*1.5;x[2]=50*1.5;x[3]=60*1.5;
	y[0]=10*1.5;y[1]=25*1.5;y[2]=40*1.5;y[3]=60*1.5;	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Flying Kite");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);
	// glutIdleFunc(draw_continuous_util);
	glutMainLoop();
	return 0;
}