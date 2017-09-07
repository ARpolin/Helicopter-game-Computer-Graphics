#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>

float block_xaxis=47.5,block_yaxis=10; //define block range
float helimove=0; //define heli move
int i=0;
float blockspeed=0.04;
int score=0;
void init (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f); //Dispaly color
	glMatrixMode(GL_PROJECTION); //specifies which function is the current matrix.
	glLoadIdentity(); //Load the matrix.
	glOrtho(0.0, 100.0,0.0, 100.0, -3.0 , 0.0); //projection details
}
void drawhelicopter()
{
	glColor3f(0.0,0.0,0.0); //helicopter color
	glRectf(10,49.8,19.8,44.8);//body
	glRectf(2,46,10,48);//tail
	glRectf(2,46,4,51);//tail up
	glRectf(14,49.8,15.8,52.2);//propeller stand
	glRectf(7,53.6,22.8,52.2);//propeller

}
void gameOverScreen() {
  background(0);
  textAlign(CENTER);
  fill(255);
  textSize(30);
  text("Game Over", height/2, width/2 - 20);
  textSize(15);
  //text("Click to Restart", height/2, width/2 + 10);
}
void boundary()
{
	glColor3f(0.3,0.7,0.2); //boundary color
	glRectf(0.0,0.0,100.0,10.0);//top
	glRectf(0.0,100.0,100.0,90.0);//foor
}
void block()
{
	glColor3f(1.0,0.0,0.0); //block color
	glRectf(block_xaxis,block_yaxis,block_xaxis+5,block_yaxis+35); //block starting position
}
void crashcondition()
{
	glClear (GL_COLOR_BUFFER_BIT);
	if((i==360||i==-360)//boundary check
   ||(((int)block_xaxis==10||(int)block_xaxis==7||(int)block_xaxis==4||(int)block_xaxis==1)&&(int)block_yaxis<53+(int)helimove&&(int)block_yaxis+35>53+(int)helimove)//fornt check
   ||(((int)block_xaxis==9||(int)block_xaxis==3||(int)block_xaxis==6)&&(int)block_yaxis<45+(int)helimove&&(int)block_yaxis+35>45+(int)helimove)//lower body checking 
   ||(((int)block_xaxis==0)&&(int)block_yaxis<46+(int)helimove&&(int)block_yaxis+35>46+(int)helimove)//lower tail checking
	) 
{
	gameOverScreen();
	printf("GAME OVER\nClose the console window to exit...\n");
	//exit(0);
}
else 
	{ 
		glPushMatrix();//start
		boundary();
		glTranslatef(0.0,helimove,0.0);
		drawhelicopter();//code for helicopter
		if(block_xaxis<-10) 
		{ 
			block_xaxis=47.5;
			block_yaxis=(rand()%25)+20;
		} 
		else 
		block_xaxis-=blockspeed;
		glTranslatef(block_xaxis,-helimove,0.0);
		block();
		glPopMatrix(); //end
		
	}
}
void myDisplay(void)
{
	crashcondition();
	glutSwapBuffers();
	glFlush(); 
}
void Heliup()
{
	helimove+=0.1; //b=0 clicking mouse 0.1 increase 
	i++;
	glutPostRedisplay();
}
void Helidown()
{
	helimove-=0.1;
	i--;   //b=0 clicking mouse 0.1 decrease 
	glutPostRedisplay();
}
/*void Reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}*/
void keyboard (unsigned char key, int x, int y)
{
	bool start;
	int startTime;
     switch(key)
     {
		case 'q':
            exit(0);
			break;
		case 's':
			start=true;
            if(start==false)
               startTime=glutGet(GLUT_ELAPSED_TIME);//note down the initial time
               break;
               default:
               break;
		}
}

void mouse(int btn,int state,int x,int y)
{
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(Heliup);
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
		glutIdleFunc(Helidown);
	glutPostRedisplay();
}
void main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (500, 400);
glutInitWindowPosition (100, 150);
glutCreateWindow ("Helicopter");
//glutReshapeFunc(Reshape);
glutDisplayFunc(myDisplay);
//glutKeyboardFunc(keyboard);
glutMouseFunc(mouse); 
init ();
glutMainLoop();
}
