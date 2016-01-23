#include "GL/freeglut.h"
#include "GL/gl.h"
#include "iostream"
#include "math.h"
using namespace std;
int clickedNd=0;
GLfloat qnd,rnd,eatNd[2]={2,2},eat2Nd[2]={10,10},eat3Nd[2]={-10,10},eat4Nd[2]={25,-30},eat5Nd[2]={-20,-30};
GLfloat eat6Nd[2]={-35,15},eatiNd[2],speedNd=0.2;
GLint fontNd=0,eatenNd=0;
char kNd;

int gameoverNd=0,countNd,scoreNd;
void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}
void drawBitmapText(const char *string,float x,float y,float z) 
{  
    const char *c;
    glRasterPos3f(x, y,z);

    for (c=string; *c != '\0'; c++) 
    {
        if(fontNd==0) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        else if(fontNd==1) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        else if(fontNd==2) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        else if(fontNd==3) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void display(void)
{  //==========================main page Display func===============
   if(clickedNd==0){
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(.2, .2, .2);
   glRectf(-50, -50, 50,50);
   glColor3f(0.0, 1.0, 1.0);     //   playbutton
   glRectf(-15.0, -30.0, 15, -20);
   glColor3f(0,0,0);
   glLineWidth(14);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-50.0, -50.0);
        glVertex2f(50.0, -50.0);
        glVertex2f(50.0, 50.0);
        glVertex2f(-50.0, 50.0);
        glVertex2f(-50.0, -50.0);
    glEnd();  
    drawBitmapText("PLAY",-5,-27,0);
    glColor3f(1,1,1);
    drawBitmapText(".:  Silver conio  :.",-17,40,0);
    fontNd=3;
    drawBitmapText("Introduction :",-47,35,0);
    fontNd=1;
    drawBitmapText("This is a coin collection Game in which One's collect the silver coin.",-47,31,0);
    drawBitmapText("This task is completed under the some rules. speedNd of coin collecter ",-47,28,0);
    drawBitmapText("is increased contineously. and One green coin also persent in game if ",-47,25,0);
    drawBitmapText("one's collect it then speedNd decrease once .",-47,22,0);
    drawBitmapText("There are also persent some red colored obstacle. if One's touch of ",-47,19,0);
    drawBitmapText("these or electric wall then Game is Over.",-47,16,0);
    fontNd=3;
    drawBitmapText("Controls : ",-47,10,0);
    fontNd=2;
    drawBitmapText("P : Pause ",-42,2,0);
    drawBitmapText("r : Restart ",-42,-5,0);
    drawBitmapText("W",-3,3,0);
    drawBitmapText("S",-3,-7,0);
    drawBitmapText("A",-8,-2,0);
    drawBitmapText("D",2,-2,0);
    drawBitmapText("W : UP",11,4,0);
    drawBitmapText("S : DOWN",11,0,0);
    drawBitmapText("A : LEFT",11,-4,0);
    drawBitmapText("D : RIGHT",11,-8,0);
    fontNd=0;
   glutSwapBuffers();
   }
   //===========Game Display function==============================
   else
   { glLineWidth(1);
    glClear(GL_COLOR_BUFFER_BIT); 
   //================================boundary=======================
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-44.0, -44.0);
        glVertex2f(44.0, -44.0);
        glVertex2f(44.0, 44.0);
        glVertex2f(-44.0, 44.0);
        glVertex2f(-44.0, -44.0);
    glEnd();
    glBegin(GL_LINES);    
        glVertex2f(-15, 0);glVertex2f(15, 0);//+
        glVertex2f(0,-15);glVertex2f(0, 15);//+
        glVertex2f(0,37);glVertex2f(0,25);//v-top
        glVertex2f(0,-37);glVertex2f(0,-25);//v-down
        glVertex2f(37,0);glVertex2f(25,0);//h-left
        glVertex2f(-37,0);glVertex2f(-25,0);//h-right
    glEnd();
   //========================snake===================================
    
    glColor3f(1,1,0);
    glPushMatrix();
       glTranslatef(qnd,rnd,0);
       glPointSize(5);
       glBegin(GL_POINTS);
          glVertex2f(3,-3);
          glVertex2f(1,-3);
          glVertex2f(1,-1);
          glVertex2f(3,-1);
       glEnd(); 
       glPointSize(10);
       glBegin(GL_POINTS); 
          glVertex2f(2,-2);
       glEnd();   
    glPopMatrix();
    //===============eatNd======================================
    glPointSize(10.90);
    glBegin(GL_POINTS);
       glColor3f(1,1,1);
      // glPointSize(10.90);
       glVertex2f(eatNd[0],eatNd[1]);
       glColor3f(1,0,0);
       glVertex2f(eat2Nd[0],eat2Nd[1]);
       glVertex2f(eat3Nd[0],eat3Nd[1]);
       glVertex2f(eat4Nd[0],eat4Nd[1]);
       glVertex2f(eat5Nd[0],eat5Nd[1]);
       glColor3f(0,1,0);
       glVertex2f(eat6Nd[0],eat6Nd[1]);
    glEnd();   
    //===================scoreNd===============================
    glColor3f(0,1,0);
    fontNd=1;
    drawBitmapText(" Score :",-7,40,0);
    int sNd1,sNd2,sNd3,sNd4;
    sNd1 = scoreNd/1000;sNd2 =(scoreNd/100)%10;sNd3=(scoreNd%100)/10;sNd4=scoreNd%10;
    char aNd[5]={sNd1+48,sNd2+48,sNd3+48,sNd4+48};
    glColor3f(0,1,0);
    drawBitmapText(aNd,5,40,0);
    if(gameoverNd==1) 
    {  fontNd=0;
       glColor3f(0.5,0.5,0.5);
       glRectf(-40,-7,40,7);
       glColor3f(0,0,0);
       drawBitmapText("GAME OVER !!",-13,1,0);
       drawBitmapText("Press 'r' To Restart The Game ",-25,-5,0);
       glutIdleFunc(NULL);        
    }
    glutSwapBuffers();
  
    //========================================================   
    }

}//==================end of th eDisplay function==========================
void transDisplay(void)
{  if(clickedNd==1)
   {
	if(gameoverNd==0)
   { switch(kNd){
    case 'w': { if(rnd<=46){rnd +=speedNd;}
                else{ rnd=-46;}
                break;
               }
    case 's': { if(rnd>=-46){rnd -=speedNd;}
                else{ rnd=46;}
                break;
              }
    case 'a': { if(qnd>=-46){qnd -=speedNd;}
                else{ qnd=46;}
                break;
              }
    case 'd':{ if(qnd<=46){qnd +=speedNd;}
                else{ qnd=-46;} 
                break;
              }
   } 
  }
  speedNd +=0.0001;
  for(int i=2;i<=6;i++)
  {   switch(i)
      {
        case 2:{eatiNd[0]=eat2Nd[0];eatiNd[1]=eat2Nd[1];break;}
        case 3:{eatiNd[0]=eat3Nd[0];eatiNd[1]=eat3Nd[1];break;}
        case 4:{eatiNd[0]=eat4Nd[0];eatiNd[1]=eat4Nd[1];break;}
        case 5:{eatiNd[0]=eat5Nd[0];eatiNd[1]=eat5Nd[1];break;}
        case 6:{eatiNd[0]=eat6Nd[0];eatiNd[1]=eat6Nd[1];break;}    
      }
      if(((abs(eatiNd[0]-(1+qnd))<=0.8)&&(abs(eatiNd[1]-(-1+rnd))<=0.8)))
      {
         if(i!=6) {gameoverNd =1; glutIdleFunc(NULL);}
         if(i==6&&speedNd>0.01) speedNd = speedNd-0.01;

      }
      
   }   
  // cout<<"1+qnd , -1+rnd : "<<1+qnd<<" , "<<-1+rnd<<"\n";  
   if((abs(eatNd[0]-(1+qnd))<=1)&&(abs(eatNd[1]-(-1+rnd))<=1)) {eatenNd=1;scoreNd++;}//cout<<"eatenNd : "<<eatenNd<<"\n";}
   else eatenNd=0;
   if(eatenNd==1)
   {  int sign1Nd,sign2Nd,sign3Nd,sign4Nd;
      sign1Nd =rand()%2; sign3Nd =rand()%2;
      sign2Nd =rand()%2; sign4Nd =rand()%2;
      eatNd[0]=(rand()%44);eatNd[1]=rand()%44;
      eat2Nd[0]=(rand()%44);eat2Nd[1]=rand()%44;
      eat3Nd[0]=(rand()%44);eat3Nd[1]=rand()%44;
      if(sign1Nd==1) {eatNd[0]=-eatNd[0];}if(sign2Nd==1){eatNd[1]=-eatNd[1];}//eatNd
      if(sign3Nd==1) {eat2Nd[0]=-eat2Nd[0];}if(sign4Nd==1){eat2Nd[1]=-eat2Nd[1];}//r1
      if(rand()%2==1) {eat3Nd[0]=-eat3Nd[0];}if(rand()%2==1){eat3Nd[1]=-eat3Nd[1];}//r2
      if(rand()%2==1) {eat4Nd[0]=-eat4Nd[0];}if(rand()%2==1){eat4Nd[1]=-eat4Nd[1];}//r3
      if(rand()%2==1) {eat5Nd[0]=-eat5Nd[0];}if(rand()%2==1){eat5Nd[1]=-eat5Nd[1];}//r4
      if(rand()%2==1) {eat6Nd[0]=-eat6Nd[0];}if(rand()%2==1){eat6Nd[1]=-eat6Nd[1];}//r5      
     // cout<<"eatNd : "<<eatNd[0]<<" , "<<eatNd[1]<<"\n";        
   }
   //======================gameoverNd=========================================
   int xNd=2+qnd;int y=-2+rnd;
   if((xNd>=44)||(xNd<=-44)||(y<=-44)||(y>=44)){gameoverNd =1; glutIdleFunc(NULL);}
   else if((((xNd>=-37)&&(xNd<=-25))&&(y==0))||(((xNd<=37)&&(xNd>=25))&&(y==0))){gameoverNd =1; glutIdleFunc(NULL);}
   else if((((y>=-37)&&(y<=-25))&&(xNd==0))||(((y<=37)&&(y>=25))&&(xNd==0))){gameoverNd =1; glutIdleFunc(NULL);}
   else if((((xNd>=-15)&&(xNd<=15))&&(y==0))||(((y<=15)&&(y>=-15))&&(xNd==0))){gameoverNd =1; glutIdleFunc(NULL);}
   else  glutPostRedisplay();
   //=======================================================================    
    glutPostRedisplay();

    }
   
}
void restart(void)
{      if(clickedNd==1){
       qnd=0;rnd=0;scoreNd=0;gameoverNd=0;speedNd=0.2;
       glutPostRedisplay();  
   }
}
//  keybooard controller.............
//=======================================================================
void keyboard(unsigned char key, int x, int y)
{
    if(clickedNd==1)
    { 
    if(key=='w') {kNd='w'; glutIdleFunc(transDisplay);} 
    if(key=='s') {kNd='s'; glutIdleFunc(transDisplay);}
    if(key=='d') {kNd='d';glutIdleFunc(transDisplay);}
    if(key=='a') {kNd='a'; glutIdleFunc(transDisplay);}
    if(key=='r')
    {  glutIdleFunc(restart);}
    if(key=='p'){glutIdleFunc(NULL);}
    }
}
//end of keyboard function 
//========================================================================
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if(clickedNd==0){glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);}
   else glOrtho(-45.0, 45.0, -45.0, 45.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{  //cout<<"x,y : "<<x<<" "<<y<<"\n";
   switch (button) {
       case GLUT_LEFT_BUTTON:
                  if((x<391&&x>211)&&(y<451&&y>395))
                  {
                   clickedNd=1; 
                   //cout<<"x,y : "<<x<<" "<<y<<"\n"; 
                   glutIdleFunc(display);             	
                  }
                  break;
       default:
              break;
   }
}
/*
* Reqnduest double buffer display mode.
* Register mouse input callback functions
*/
int main(int argc, char** argv)
{  
     glutInit(&argc, argv); 
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(600, 600);
     glutInitWindowPosition(200, 100);
     glutCreateWindow("Silver_coino");
     init();
     glutMouseFunc(mouse);
     glutDisplayFunc(display);
     glutMouseFunc(mouse);
     glutReshapeFunc(reshape);
     glutKeyboardFunc(keyboard);
     glutMainLoop(); 
     return 0;
}
