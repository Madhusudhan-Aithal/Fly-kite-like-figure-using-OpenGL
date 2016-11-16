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
void draw_continuous_v(int val)
{
    
    // glTranslatef(1.0,0.0,0.0);
    count--;
    if(count>0)
    {
      glTranslatef(0.0,val,0.0);    
      glutPostRedisplay(); 
      glutTimerFunc(100, draw_continuous_v, val);    
    }
}
void draw_continuous_h(int val)
{
    count--;
    if(count>0)
    {
      glTranslatef(val,0.0,0.0);    
      glutPostRedisplay(); 
      glutTimerFunc(100, draw_continuous_h, val);    
    }
}
void keyboard (unsigned char key, int x, int y)
{ 
     switch (key) {
        case 'c':
        count=100;
        draw_continuous_v(3.0);
        count=100;
        draw_continuous_h(3.0);
        count=100;
        draw_continuous_v(-3.0);
        count=100;
        draw_continuous_h(-3.0);
          break;
        case '1':        
            glTranslatef(-1.0*5,1.0*5,0.0);
            glutPostRedisplay();
            break;  
        case '2':
            glTranslatef(1.0*5.0,1.0*5,0.0);
            glutPostRedisplay();
            break;  
        case '3':
            glTranslatef(1.0*5,-1.0*5,0.0);
            glutPostRedisplay();
            break;  
        case '4':
            glTranslatef(-1.0*5,-1.0*5,0.0);
            glutPostRedisplay();
            break; 
        case 'u':
            count=10;
            draw_continuous_v(3.0);
            // glTranslatef(0.0,1.0*5,0.0);
            // glutPostRedisplay();
            break;  
        case 'd':
        count=10;
        draw_continuous_v(-3.0);
            // glTranslatef(0.0,-1.0*5,0.0);
            // glutPostRedisplay();
            break; 
        case 'l':
        count=10;
        draw_continuous_h(-3.0);
           // glTranslatef(-1.0*5,0.0,0.0);
           // glutPostRedisplay();
           break;  
        case 'r':
           // glTranslatef(1.0*5,0.0,0.0);
           // glutPostRedisplay();
        count=10;
        draw_continuous_h(3.0);
           break;   
        case 'q':
           exit(0);
           break;
        default:
           break;
   }  

}


void draw_kite()
{
   glColor3f(0.58, 0.0, 0.76);	
   glBegin(GL_POLYGON);
   glVertex3f(60.0*1.5,60.0*1.5,0.0);
   glVertex3f(40.0*1.5,80.0*1.5,0.0);
   glVertex3f(60.0*1.5,100.0*1.5,0.0);
   glVertex3f(80.0*1.5,80.0*1.5,0.0);
   	glEnd();
   	int i;
	double t;
	
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);
	for (t = 0.0; t < 1.0; t += 0.0005)
	{
		double xt = (pow(1-t, 3)*x[0]+3*t*pow(1-t,2)*x[1]+3*pow(t,2)*(1-t)*x[2]+pow(t, 3)*x[3]);
		double yt = (pow(1-t,3)*y[0]+3*t*pow(1-t,2)*y[1]+3*pow(t,2)*(1-t)*y[2]+pow(t,3)*y[3]);		
		glVertex2f(xt,yt);

	}
	glEnd();  
}


void draw_kite_outer()
 
   {
    glTranslatef(0.05, 0.0, 0.0); 
	draw_kite();    
   }
  
void display(void)

   {
   glClear(GL_COLOR_BUFFER_BIT);
   draw_kite_outer();   
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
    // glutIdleFunc(draw_continuous_util);
      glutMainLoop();
      return 0;
   }