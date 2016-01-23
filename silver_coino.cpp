#include "GL/freeglut.h"
#include "GL/gl.h"
#include "iostream"
#include "math.h"
using namespace std;
int clicked=0;
GLfloat q,r,eat[2]={2,2},eat2[2]={10,10},eat3[2]={-10,10},eat4[2]={25,-30},eat5[2]={-20,-30},eat6[2]={-35,15},eati[2],speed=0.2;
GLint font=0,eaten=0;
char k;

int gameover=0,count,score;
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
        if(font==0) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        else if(font==1) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        else if(font==2) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        else if(font==3) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void display(void)
{  //==========================main page Display func===============
   if(clicked==0){
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
    font=3;
    drawBitmapText("Introduction :",-47,35,0);
    font=1;
    drawBitmapText("This is a coin collection Game in which One's collect the silver coin.",-47,31,0);
    drawBitmapText("This task is completed under the some rules. Speed of coin collecter ",-47,28,0);
    drawBitmapText("is increased contineously. and One green coin also persent in game if ",-47,25,0);
    drawBitmapText("one's collect it then speed decrease once .",-47,22,0);
    drawBitmapText("There are also persent some red colored obstacle. if One's touch of ",-47,19,0);
    drawBitmapText("these or electric wall then Game is Over.",-47,16,0);
    font=3;
    drawBitmapText("Controls : ",-47,10,0);
    font=2;
    drawBitmapText("P : Pause ",-42,2,0);
    drawBitmapText("R : Restart ",-42,-5,0);
    drawBitmapText("W",-3,3,0);
    drawBitmapText("S",-3,-7,0);
    drawBitmapText("A",-8,-2,0);
    drawBitmapText("D",2,-2,0);
    drawBitmapText("W : UP",11,4,0);
    drawBitmapText("S : DOWN",11,0,0);
    drawBitmapText("A : LEFT",11,-4,0);
    drawBitmapText("D : RIGHT",11,-8,0);
    font=0;
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
       glTranslatef(q,r,0);
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
    //===============Eat======================================
    glPointSize(10.90);
    glBegin(GL_POINTS);
       glColor3f(1,1,1);
      // glPointSize(10.90);
       glVertex2f(eat[0],eat[1]);
       glColor3f(1,0,0);
       glVertex2f(eat2[0],eat2[1]);
       glVertex2f(eat3[0],eat3[1]);
       glVertex2f(eat4[0],eat4[1]);
       glVertex2f(eat5[0],eat5[1]);
       glColor3f(0,1,0);
       glVertex2f(eat6[0],eat6[1]);
    glEnd();   
    //===================SCORE===============================
    glColor3f(0,1,0);
    font=1;
    drawBitmapText(" Score :",-7,40,0);
    int s1,s2,s3,s4;
    s1 = score/1000;s2 =(score/100)%10;s3=(score%100)/10;s4=score%10;
    char a[5]={s1+48,s2+48,s3+48,s4+48};
    glColor3f(0,1,0);
    drawBitmapText(a,5,40,0);
    if(gameover==1) 
    {  font=0;
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
{  if(clicked==1)
   {
	if(gameover==0)
   { switch(k){
    case 'w': { if(r<=46){r +=speed;}
                else{ r=-46;}
                break;
               }
    case 's': { if(r>=-46){r -=speed;}
                else{ r=46;}
                break;
              }
    case 'a': { if(q>=-46){q -=speed;}
                else{ q=46;}
                break;
              }
    case 'd':{ if(q<=46){q +=speed;}
                else{ q=-46;} 
                break;
              }
   } 
  }
  speed +=0.0001;
  for(int i=2;i<=6;i++)
  {   switch(i)
      {
        case 2:{eati[0]=eat2[0];eati[1]=eat2[1];break;}
        case 3:{eati[0]=eat3[0];eati[1]=eat3[1];break;}
        case 4:{eati[0]=eat4[0];eati[1]=eat4[1];break;}
        case 5:{eati[0]=eat5[0];eati[1]=eat5[1];break;}
        case 6:{eati[0]=eat6[0];eati[1]=eat6[1];break;}    
      }
      if(((abs(eati[0]-(1+q))<=0.8)&&(abs(eati[1]-(-1+r))<=0.8)))
      {
         if(i!=6) {gameover =1; glutIdleFunc(NULL);}
         if(i==6&&speed>0.01) speed = speed-0.01;

      }
      
   }   
  // cout<<"1+q , -1+r : "<<1+q<<" , "<<-1+r<<"\n";  
   if((abs(eat[0]-(1+q))<=1)&&(abs(eat[1]-(-1+r))<=1)) {eaten=1;score++;}//cout<<"eaten : "<<eaten<<"\n";}
   else eaten=0;
   if(eaten==1)
   {  int sign1,sign2,sign3,sign4;
      sign1 =rand()%2; sign3 =rand()%2;
      sign2 =rand()%2; sign4 =rand()%2;
      eat[0]=(rand()%44);eat[1]=rand()%44;
      eat2[0]=(rand()%44);eat2[1]=rand()%44;
      eat3[0]=(rand()%44);eat3[1]=rand()%44;
      if(sign1==1) {eat[0]=-eat[0];}if(sign2==1){eat[1]=-eat[1];}//eat
      if(sign3==1) {eat2[0]=-eat2[0];}if(sign4==1){eat2[1]=-eat2[1];}//r1
      if(rand()%2==1) {eat3[0]=-eat3[0];}if(rand()%2==1){eat3[1]=-eat3[1];}//r2
      if(rand()%2==1) {eat4[0]=-eat4[0];}if(rand()%2==1){eat4[1]=-eat4[1];}//r3
      if(rand()%2==1) {eat5[0]=-eat5[0];}if(rand()%2==1){eat5[1]=-eat5[1];}//r4
      if(rand()%2==1) {eat6[0]=-eat6[0];}if(rand()%2==1){eat6[1]=-eat6[1];}//r5      
     // cout<<"eat : "<<eat[0]<<" , "<<eat[1]<<"\n";        
   }
   //======================Gameover=========================================
   int x=2+q;int y=-2+r;
   if((x>=44)||(x<=-44)||(y<=-44)||(y>=44)){gameover =1; glutIdleFunc(NULL);}
   else if((((x>=-37)&&(x<=-25))&&(y==0))||(((x<=37)&&(x>=25))&&(y==0))){gameover =1; glutIdleFunc(NULL);}
   else if((((y>=-37)&&(y<=-25))&&(x==0))||(((y<=37)&&(y>=25))&&(x==0))){gameover =1; glutIdleFunc(NULL);}
   else if((((x>=-15)&&(x<=15))&&(y==0))||(((y<=15)&&(y>=-15))&&(x==0))){gameover =1; glutIdleFunc(NULL);}
   else  glutPostRedisplay();
   //=======================================================================    
    glutPostRedisplay();

    }
   
}
void restart(void)
{      if(clicked==1){
       q=0;r=0;score=0;gameover=0;speed=0.2;
       glutPostRedisplay();  
   }
}
//  keybooard controller.............
//=======================================================================
void keyboard(unsigned char key, int x, int y)
{
    if(clicked==1)
    { 
    if(key=='w') {k='w'; glutIdleFunc(transDisplay);} 
    if(key=='s') {k='s'; glutIdleFunc(transDisplay);}
    if(key=='d') {k='d';glutIdleFunc(transDisplay);}
    if(key=='a') {k='a'; glutIdleFunc(transDisplay);}
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
   if(clicked==0){glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);}
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
                   clicked=1; 
                   //cout<<"x,y : "<<x<<" "<<y<<"\n"; 
                   glutIdleFunc(display);             	
                  }
                  break;
       default:
              break;
   }
}
/*
* Request double buffer display mode.
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
