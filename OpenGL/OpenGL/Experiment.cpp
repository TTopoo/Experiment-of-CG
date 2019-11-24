#include "Experiment.h"

//第一次实验
const GLfloat Pi = 3.14159;
//第二次实验GLPerspViewingProg3D
GLint winWidth = 400, winHeight = 400;         //定义显示窗口大小
GLfloat xx0 = 100.0, yy0 = 50.0, zz0 = 50;     //原始观察坐标
GLfloat xref = 50.0, yref = 50.0, zref = 0.0;  // Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;          // View up vector.
GLfloat xwMin = -40.0, xwMax = 40.0, ywMin = -60.0,
        ywMax = 60.0;                //设置裁剪窗口的坐标限制
GLfloat dnear = 25.0, dfar = 125.0;  //设置远近裁剪平面的位置

//总实验
float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};
float place[] = {0, 0, 5};
float fRotate = 0.0f;    //旋转因子（茶壶和桌子）
float fScale = 1.0f;     //缩放因子
float tRotate0 = 0.0f;   //旋转因子（茶壶）
float tRotate1 = 0.0f;   //旋转因子（茶壶）
float tRotate2 = 0.0f;   //旋转因子（茶壶）
bool bPersp = false;     //是否为透视投影 （vs 正投影）
bool bAnim = false;      // 茶壶和桌子是否旋转
bool bWire = false;      // 绘制模式是否为线形 （vs 填充）
bool isRotate0 = false;  //茶壶是否旋转
bool isRotate1 = false;  //茶壶是否旋转
bool isRotate2 = false;  //茶壶是否旋转
bool isRotate00 = false;  //茶壶是否旋转
bool isRotate11 = false;  //茶壶是否旋转
bool isRotate22 = false;  //茶壶是否旋转
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

  GLfloat light1_pos[] = {5.0, -3.0, 0.0, 1.0};  //设置光源位置，光源类型
  GLfloat light2_pos[] = {0.0, 1.0, 0.0, 0.0};

  GLfloat ambient0[] = {0.1, 0.1, 0.1, 1.0};   //环境光
  GLfloat diffuse0[] = {1.0, 0.0, 0.0, 1.0};   //漫反射
  GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};  //镜面反射

  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);

  /*
          //光线强度衰减系数 1 / ( a0 + a1 * d + a2 * d * d)
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
  glRotatef(30.0, 1.0, 0.0, 0.0);  //沿x轴旋转30度
  auxSolidTeapot(0.5);
  glPopMatrix();
  glFlush();
}

//按键回调函数
void key(unsigned char k, int x, int y) {
  switch (k) {
    case 'q': {
      exit(0);
      break;
    }  //退出
    case 'p': {
      bPersp = !bPersp;
      updateView(winHeight, winWidth);
      break;
    }  //切换正投影、透视投影

    case '1': {
      bAnim = !bAnim;
      break;
    }  //旋转模式的切换
    case 'o': {
      bWire = !bWire;
      break;
    }  //渲染方式的切换

      //相机操作

    case 'a': {  //向左移动
      center[0] += 0.1f;
      eye[0] += 0.1f;
      break;
    }
    case 'd': {  //向右移动
      center[0] -= 0.1f;
      eye[0] -= 0.1f;
      break;
    }
    case 'w': {  //向上移动
      center[1] -= 0.1f;
      eye[1] -= 0.1f;
      break;
    }
    case 's': {  //向下移动
      center[1] += 0.1f;
      eye[1] += 0.1f;
      break;
    }
    case 'z': {  //向前移动
      center[2] -= 0.1f;
      eye[2] -= 0.1f;
      break;
    }
    case 'c': {  //向后移动
      center[2] += 0.1f;
      eye[2] += 0.1f;
      break;
    }
    case '4': {  //相机转
      isRotate00 = !isRotate00;
      break;
    }
    case '5': {  //相机转
      isRotate11 = !isRotate11;
      break;
    }
    case '6': {  //相机转
      isRotate22 = !isRotate22;
      break;
    }

      //茶壶操作

    case 'l': {  //右移茶壶
      place[0] += 0.1f;
      break;
    }
    case 'j': {  //左移茶壶
      place[0] -= 0.1f;
      break;
    }
    case 'i': {  //后移茶壶
      place[1] += 0.2f;
      break;
    }
    case 'k': {  //前移茶壶
      place[1] -= 0.2f;
      break;
    }
    case 'e': {  //旋转茶壶
      isRotate0 = !isRotate0;
      break;
    }
    case 'r': {  //旋转茶壶
      isRotate1 = !isRotate1;
      break;
    }
    case 't': {  //旋转茶壶
      isRotate2 = !isRotate2;
      break;
    }
  }
}
void redraw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清除颜色缓存和深度缓存
  glLoadIdentity();  //初始化矩阵为单位矩阵
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

  //  观察位置(eye[0],eye[1],eye[2]
  //	物体位置(center[0],center[1],center[2]
  //	观察方向(x, y, z)

  if (bWire) {
    glPolygonMode(GL_FRONT_AND_BACK,
                  GL_LINE);  //设置多边形绘制模式：正反面，线型
  } else {
    glPolygonMode(GL_FRONT_AND_BACK,
                  GL_FILL);  //设置多边形绘制模式：正反面，填充
  }

  glEnable(GL_DEPTH_TEST);  //开启深度测试
  glEnable(GL_LIGHTING);    //开启光照模式
  glEnable(GL_LIGHT1);

  GLfloat light1_pos[] = {5.0, -3.0, 0.0, 1.0};  //设置光源位置，光源类型
  GLfloat light2_pos[] = {0.0, 1.0, 0.0, 0.0};

  GLfloat ambient0[] = {0.5, 0.5, 1.0, 1.0};   //环境光
  GLfloat diffuse0[] = {1.0, 0.0, 0.0, 1.0};   //漫反射
  GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};  //镜面反射

  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);

  glRotatef(fRotate, 0, 1.0f, 0);  //旋转
  glRotatef(-90, 1, 0, 0);         //旋转
  glScalef(0.2, 0.2, 0.2);         //缩放
  Draw_Scene(place);               //场景绘制

  if (isRotate0) tRotate0 += 0.5f;  //茶壶旋转
  if (isRotate1) tRotate1 += 0.5f;
  if (isRotate2) tRotate2 += 0.5f;
  glutSwapBuffers();  //交换缓冲区
}

void updateView(int width, int height) {
  glViewport(0, 0, width, height);  //设置视窗大小

  glMatrixMode(GL_PROJECTION);  //设置矩阵模式为投影
  glLoadIdentity();             //初始化矩阵为单位矩阵

  float whRatio = (GLfloat)width / (GLfloat)height;  //设置显示比例

  if (bPersp) {
    gluPerspective(45, whRatio, 1, 100);  //透视投影
                                          //参数：

    // GLdouble fovy 视角
    // GLdouble aspect 宽高比
    // GLdouble zNear 近处
    // GLdouble zFar 远处
  } else
    glOrtho(-3, 3, -3, 3, -100, 100);  //正投影
                                       //参数

  // GLdouble left,
  // GLdouble right,
  // GLdouble bottom,
  // GLdouble top,
  // GLdouble near,
  // GLdouble far

  glMatrixMode(GL_MODELVIEW);  //设置矩阵模式为模型
}

void Draw_Scene(float place[]) {
  //画茶壶
  glPushMatrix();
  glTranslatef(place[0], place[1], place[2]);  //控制平移
  glRotatef(90, 1, 0, 0);
  glRotatef(tRotate0, 0, 1, 0);  //控制旋转
  glRotatef(tRotate1, 1, 0, 0);  //控制旋转
  glRotatef(tRotate2, 0, 0, 1);  //控制旋转
  glutSolidTeapot(3);
  glPopMatrix();
}
void reshape(GLint width, GLint height) {
  if (height == 0)  //如果高度为0
  {
    height = 1;  //让高度为1（避免出现分母为0的现象）
  }
  height = width = min(height, width);
  winHeight = height;
  winWidth = width;

  updateView(winHeight, winWidth);  //更新视角
}
void idle() {
  glutPostRedisplay();  //调用当前绘制函数
}