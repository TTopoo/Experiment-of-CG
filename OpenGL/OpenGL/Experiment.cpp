#include "Experiment.h"

//��һ��ʵ��
const GLfloat Pi = 3.14159;
//�ڶ���ʵ��GLPerspViewingProg3D
GLint winWidth = 400, winHeight = 400;         //������ʾ���ڴ�С
GLfloat xx0 = 100.0, yy0 = 50.0, zz0 = 50;     //ԭʼ�۲�����
GLfloat xref = 50.0, yref = 50.0, zref = 0.0;  // Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;          // View up vector.
GLfloat xwMin = -40.0, xwMax = 40.0, ywMin = -60.0,
        ywMax = 60.0;                //���òü����ڵ���������
GLfloat dnear = 25.0, dfar = 125.0;  //����Զ���ü�ƽ���λ��

//��ʵ��
float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};
float place[] = {0, 0, 5};
float fRotate = 0.0f;    //��ת���ӣ���������ӣ�
float fScale = 1.0f;     //��������
float tRotate0 = 0.0f;   //��ת���ӣ������
float tRotate1 = 0.0f;   //��ת���ӣ������
float tRotate2 = 0.0f;   //��ת���ӣ������
bool bPersp = false;     //�Ƿ�Ϊ͸��ͶӰ ��vs ��ͶӰ��
bool bAnim = false;      // ����������Ƿ���ת
bool bWire = false;      // ����ģʽ�Ƿ�Ϊ���� ��vs ��䣩
bool isRotate0 = false;  //����Ƿ���ת
bool isRotate1 = false;  //����Ƿ���ת
bool isRotate2 = false;  //����Ƿ���ת
bool isRotate00 = false;  //����Ƿ���ת
bool isRotate11 = false;  //����Ƿ���ת
bool isRotate22 = false;  //����Ƿ���ת
float ANGLE = 0;

void w2init() {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(xx0, yy0, zz0, xref, yref, zref, Vx, Vy, Vz);
  glMatrixMode(GL_PROJECTION);
  glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void displayFcn() {
  glClear(GL_COLOR_BUFFER_BIT);
  // Set parameters for a square fill area.
  glColor3f(0.0, 1.0, 0.0);  // Set fill color to green.
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_LINE);  // Wire-frame back face.
  glBegin(GL_QUADS);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(100.0, 0.0, 0.0);
  glVertex3f(100.0, 100.0, 0.0);
  glVertex3f(0.0, 100.0, 0.0);
  glEnd();

  glFlush();
}

void reshapeFcn(GLint newWidth, GLint newHeight) {
  glViewport(0, 0, newWidth, newHeight);
  winWidth = newWidth;
  winHeight = newHeight;
}

void lineSegment_Circle_Line() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
  int i;

  glBegin(GL_LINE_LOOP);
  for (i = 0; i < 1000; ++i)
    glVertex2f(50 + 50 * cos(2 * Pi / 1000 * i),
               50 + 50 * sin(2 * Pi / 1000 * i));
  glEnd();
  glBegin(GL_LINES);
  glVertex2i(180, 15);
  glVertex2i(10, 145);
  glEnd();

  glFlush();
}

void wireQuadSurfs() {
  glClear(GL_COLOR_BUFFER_BIT);  // Clear display window.
  glColor3f(0.0, 0.0, 1.0);      // Set line-color to blue.

  // Set viewing parameters with world z axis as view-up direction.
  gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

  // Position and display GLUT wire-frame sphere.
  glPushMatrix();
  glTranslatef(1.0, 1.0, 0.0);
  glutWireSphere(0.75, 8, 6);
  glPopMatrix();

  // Position and display GLUT wire-frame cone.
  glPushMatrix();
  glTranslatef(1.0, -0.5, 0.5);
  glutWireCone(0.7, 2.0, 7, 6);
  glPopMatrix();

  // Position and display GLU wire-frame cylinder.
  GLUquadricObj* cylinder;  // Set name for GLU quadric object.
  glPushMatrix();
  glTranslatef(0.0, 1.2, 0.8);
  cylinder = gluNewQuadric();
  gluQuadricDrawStyle(cylinder, GLU_LINE);
  gluCylinder(cylinder, 0.6, 0.6, 1.5, 6, 4);
  glPopMatrix();
  glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
  glViewport(0, 0, newWidth, newHeight);
  glMatrixMode(GL_PROJECTION);
  glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 5.0);
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);
}

void teapot() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);

  GLfloat light1_pos[] = {5.0, -3.0, 0.0, 1.0};  //���ù�Դλ�ã���Դ����
  GLfloat light2_pos[] = {0.0, 1.0, 0.0, 0.0};

  GLfloat ambient0[] = {0.1, 0.1, 0.1, 1.0};   //������
  GLfloat diffuse0[] = {1.0, 0.0, 0.0, 1.0};   //������
  GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};  //���淴��

  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);

  /*
          //����ǿ��˥��ϵ�� 1 / ( a0 + a1 * d + a2 * d * d)
          glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0); //a0
          glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1); //a1
          glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0); //a2
  */
  glutSolidTeapot(0.4);
  glFlush();
}

GLfloat sgenparams[] = {1.0, 1.0, 1.0, 0.0};

void TeapotInit() {
  glClear(GL_COLOR_BUFFER_BIT);
  glShadeModel(GL_FLAT);

  AUX_RGBImageRec* TextureImage[1];
  TextureImage[0] = auxDIBImageLoad(L"2.bmp");

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_REPEAT,
  // GL_CLAMP glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX,
               TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
               TextureImage[0]->data);

  glEnable(GL_TEXTURE_2D);
  // glEnable(GL_TEXTURE_GEN_S);
  // glEnable(GL_TEXTURE_GEN_T);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);
  glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
}

void Teapot() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef(30.0, 1.0, 0.0, 0.0);  //��x����ת30��
  auxSolidTeapot(0.5);
  glPopMatrix();
  glFlush();
}

//�����ص�����
void key(unsigned char k, int x, int y) {
  switch (k) {
    case 'q': {
      exit(0);
      break;
    }  //�˳�
    case 'p': {
      bPersp = !bPersp;
      updateView(winHeight, winWidth);
      break;
    }  //�л���ͶӰ��͸��ͶӰ

    case '1': {
      bAnim = !bAnim;
      break;
    }  //��תģʽ���л�
    case 'o': {
      bWire = !bWire;
      break;
    }  //��Ⱦ��ʽ���л�

      //�������

    case 'a': {  //�����ƶ�
      center[0] += 0.1f;
      eye[0] += 0.1f;
      break;
    }
    case 'd': {  //�����ƶ�
      center[0] -= 0.1f;
      eye[0] -= 0.1f;
      break;
    }
    case 'w': {  //�����ƶ�
      center[1] -= 0.1f;
      eye[1] -= 0.1f;
      break;
    }
    case 's': {  //�����ƶ�
      center[1] += 0.1f;
      eye[1] += 0.1f;
      break;
    }
    case 'z': {  //��ǰ�ƶ�
      center[2] -= 0.1f;
      eye[2] -= 0.1f;
      break;
    }
    case 'c': {  //����ƶ�
      center[2] += 0.1f;
      eye[2] += 0.1f;
      break;
    }
    case '4': {  //���ת
      isRotate00 = !isRotate00;
      break;
    }
    case '5': {  //���ת
      isRotate11 = !isRotate11;
      break;
    }
    case '6': {  //���ת
      isRotate22 = !isRotate22;
      break;
    }

      //�������

    case 'l': {  //���Ʋ��
      place[0] += 0.1f;
      break;
    }
    case 'j': {  //���Ʋ��
      place[0] -= 0.1f;
      break;
    }
    case 'i': {  //���Ʋ��
      place[1] += 0.2f;
      break;
    }
    case 'k': {  //ǰ�Ʋ��
      place[1] -= 0.2f;
      break;
    }
    case 'e': {  //��ת���
      isRotate0 = !isRotate0;
      break;
    }
    case 'r': {  //��ת���
      isRotate1 = !isRotate1;
      break;
    }
    case 't': {  //��ת���
      isRotate2 = !isRotate2;
      break;
    }
  }
}
void redraw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //�����ɫ�������Ȼ���
  glLoadIdentity();  //��ʼ������Ϊ��λ����
  if (isRotate00) {//y
    //time_t seconds;
    //seconds = time(NULL)%360;
    ANGLE += 0.05;
    if (ANGLE >= 360) ANGLE = 0;
    float radius = 10.0f;
    float camX = sin(ANGLE) * radius;
    float camZ = cos(ANGLE) * radius;
    eye[0] = camX;
    eye[2] = camZ;
  }
  if (isRotate11) {  // x
    time_t seconds;
    seconds = time(NULL) % 360;
    float radius = 10.0f;
    float camY = -sin(seconds) * radius;
    float camZ = cos(seconds) * radius;
    eye[1] = camY;
    eye[2] = camZ;
  }
  gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);

  //  �۲�λ��(eye[0],eye[1],eye[2]
  //	����λ��(center[0],center[1],center[2]
  //	�۲췽��(x, y, z)

  if (bWire) {
    glPolygonMode(GL_FRONT_AND_BACK,
                  GL_LINE);  //���ö���λ���ģʽ�������棬����
  } else {
    glPolygonMode(GL_FRONT_AND_BACK,
                  GL_FILL);  //���ö���λ���ģʽ�������棬���
  }

  glEnable(GL_DEPTH_TEST);  //������Ȳ���
  glEnable(GL_LIGHTING);    //��������ģʽ
  glEnable(GL_LIGHT1);

  GLfloat light1_pos[] = {5.0, -3.0, 0.0, 1.0};  //���ù�Դλ�ã���Դ����
  GLfloat light2_pos[] = {0.0, 1.0, 0.0, 0.0};

  GLfloat ambient0[] = {0.5, 0.5, 1.0, 1.0};   //������
  GLfloat diffuse0[] = {1.0, 0.0, 0.0, 1.0};   //������
  GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};  //���淴��

  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);

  glRotatef(fRotate, 0, 1.0f, 0);  //��ת
  glRotatef(-90, 1, 0, 0);         //��ת
  glScalef(0.2, 0.2, 0.2);         //����
  Draw_Scene(place);               //��������

  if (isRotate0) tRotate0 += 0.5f;  //�����ת
  if (isRotate1) tRotate1 += 0.5f;
  if (isRotate2) tRotate2 += 0.5f;
  glutSwapBuffers();  //����������
}

void updateView(int width, int height) {
  glViewport(0, 0, width, height);  //�����Ӵ���С

  glMatrixMode(GL_PROJECTION);  //���þ���ģʽΪͶӰ
  glLoadIdentity();             //��ʼ������Ϊ��λ����

  float whRatio = (GLfloat)width / (GLfloat)height;  //������ʾ����

  if (bPersp) {
    gluPerspective(45, whRatio, 1, 100);  //͸��ͶӰ
                                          //������

    // GLdouble fovy �ӽ�
    // GLdouble aspect ��߱�
    // GLdouble zNear ����
    // GLdouble zFar Զ��
  } else
    glOrtho(-3, 3, -3, 3, -100, 100);  //��ͶӰ
                                       //����

  // GLdouble left,
  // GLdouble right,
  // GLdouble bottom,
  // GLdouble top,
  // GLdouble near,
  // GLdouble far

  glMatrixMode(GL_MODELVIEW);  //���þ���ģʽΪģ��
}

void Draw_Scene(float place[]) {
  //�����
  glPushMatrix();
  glTranslatef(place[0], place[1], place[2]);  //����ƽ��
  glRotatef(90, 1, 0, 0);
  glRotatef(tRotate0, 0, 1, 0);  //������ת
  glRotatef(tRotate1, 1, 0, 0);  //������ת
  glRotatef(tRotate2, 0, 0, 1);  //������ת
  glutSolidTeapot(3);
  glPopMatrix();
}
void reshape(GLint width, GLint height) {
  if (height == 0)  //����߶�Ϊ0
  {
    height = 1;  //�ø߶�Ϊ1��������ַ�ĸΪ0������
  }
  height = width = min(height, width);
  winHeight = height;
  winWidth = width;

  updateView(winHeight, winWidth);  //�����ӽ�
}
void idle() {
  glutPostRedisplay();  //���õ�ǰ���ƺ���
}