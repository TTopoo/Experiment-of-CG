#include "Experiment.h"

extern GLint winWidth, winHeight;
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(winWidth, winHeight);
  /* 取消注释即可运行
  //第一次实验
  {
    glutInitWindowPosition(50, 50);
    int w1 = glutCreateWindow("第一次实验");
    glutDisplayFunc(lineSegment_Circle_Line);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
  }

  //第二次实验
  {
    glutInitWindowPosition(450, 50);
    int w2 = glutCreateWindow("第二次实验GLPerspViewingProg3D");
    w2init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(reshapeFcn);

    glutInitWindowPosition(850, 50);
    int w3 = glutCreateWindow("第二次实验GLQuadricSurfs");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(wireQuadSurfs);
    glutReshapeFunc(winReshapeFcn);
  }

  //第三次实验
  {
    glutInitWindowPosition(50, 450);
    int w4 = glutCreateWindow("第三次实验Light");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(teapot);

    glutInitWindowPosition(450, 450);
    int w5 = glutCreateWindow("第三次实验Teapot");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    TeapotInit();
    glutDisplayFunc(Teapot);
  }
  */
  //总实验
  {
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(850, 450);
    int w6 = glutCreateWindow("总实验");
    glutDisplayFunc(redraw);   //注册绘制回调函数
    glutReshapeFunc(reshape);  //注册重绘回调函数
    glutKeyboardFunc(key);     //注册按键回调函数
    glutIdleFunc(idle);        //注册全局回调函数：空闲时调用
  }
  glutMainLoop();
}