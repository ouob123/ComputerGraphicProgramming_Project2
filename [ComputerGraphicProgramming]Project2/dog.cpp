// 2113141 김유진_컴퓨터 그래픽 프로그래밍 두 번째 과제
#include <GL/freeglut.h> // 텍스쳐 매핑을 위해 추가
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <stdio.h>

#pragma comment (lib, "legacy_stdio_definitions.lib")

GLfloat xrot = 0.9f, yrot = 0.8f, zrot = 1.0f;
unsigned int MyTextureObject[1];
AUX_RGBImageRec* pTextureImage[1];  //텍스쳐 저장 공간을 가리키는 포인터

#define TORSO_HEIGHT 5.0
#define UPPER_ARM_HEIGHT 2.0
#define LOWER_ARM_HEIGHT 1.0
#define UPPER_LEG_RADIUS  0.5
#define LOWER_LEG_RADIUS  0.5
#define LOWER_LEG_HEIGHT 1.0
#define UPPER_LEG_HEIGHT 2.0
#define UPPER_LEG_RADIUS  0.5
#define TORSO_RADIUS 1.0
#define UPPER_ARM_RADIUS  0.5
#define LOWER_ARM_RADIUS  0.5
#define HEAD_HEIGHT 1.5
#define HEAD_RADIUS 1.0
#define TAIL_HEIGHT 2.0
#define TAIL_RADIUS 0.25

typedef float point[3];

static GLfloat theta[19] = { 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0 }; /* initial joint angles */

static GLint angle = 0;

GLUquadricObj* t, * h, * lua, * lla, * rua, * rla, * lll, * rll, * rul, * lul, * ta;

double size = 1.0;

void torso()
{
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);

    GLfloat texture[4][2] = {
        {0.0 , 0.0},
        {1.0 , 0.0},
        {1.0 , 1.0},
        {0.0 , 1.0}
    };

    GLfloat light_diffuse1[] = { 1.0, 0.7, 0.7, 1.0 }; // 몸통 조명 색 : 연분홍
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void head()
{
    GLfloat light_diffuse2[] = { 1.0, 0.0, 0.5, 0.0 }; // 머리 조명 색 : 분홍
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse2);
    glPushMatrix();
    glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
    glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h, 1.0, 15, 15);
    glPopMatrix();
}

void right_upper_arm()
{
    GLfloat light_diffuse3[] = { 1.0, 0.3, 1.0 , 0.0 }; // 다리 윗부분 조명 색
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse3);
    glPushMatrix();
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();

}

void right_lower_arm()
{
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);

    GLfloat texture[4][2] = {
        {0.0 , 0.0},
        {1.0 , 0.0},
        {1.0 , 1.0},
        {0.0 , 1.0}
    };

    GLfloat light_diffuse4[] = { 1.0, 0.7, 0.7, 1.0 }; // 다리 아래부분 조명 색
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse4);
    glPushMatrix();
    glTranslatef(0.0, -LOWER_ARM_HEIGHT, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lll, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void left_upper_arm()
{
    GLfloat light_diffuse3[] = { 1.0, 0.3, 1.0 , 0.0 }; // 다리 윗부분 조명 색
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse3);
    glPushMatrix();
    glTranslatef(0.0, -LOWER_ARM_HEIGHT, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_arm()
{
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);

    GLfloat texture[4][2] = {
        {0.0 , 0.0},
        {1.0 , 0.0},
        {1.0 , 1.0},
        {0.0 , 1.0}
    };

    GLfloat light_diffuse4[] = { 1.0, 0.7, 0.7, 1.0 }; // 다리 아래부분 조명 색
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse4);
    glPushMatrix();
    glTranslatef(0.0, -LOWER_ARM_HEIGHT, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void right_upper_leg()
{
    GLfloat light_diffuse3[] = { 1.0, 0.3, 1.0 , 0.0 }; // 다리 윗부분 조명 색
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse3);
    glPushMatrix();
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_lower_leg()
{
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);

    GLfloat texture[4][2] = {
        {0.0 , 0.0},
        {1.0 , 0.0},
        {1.0 , 1.0},
        {0.0 , 1.0}
    };

    GLfloat light_diffuse4[] = { 1.0, 0.7, 0.7, 1.0 }; // 다리 아래부분 조명 색
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse4);
    glPushMatrix();
    glTranslatef(0.0, -LOWER_LEG_HEIGHT, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void left_upper_leg()
{
    GLfloat light_diffuse3[] = { 1.0, 0.3, 1.0 , 0.0 }; // 다리 윗부분 조명 색
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse3);
    glPushMatrix();
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_leg()
{
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);

    GLfloat texture[4][2] = {
        {0.0 , 0.0},
        {1.0 , 0.0},
        {1.0 , 1.0},
        {0.0 , 1.0}
    };
  
    GLfloat light_diffuse4[] = { 1.0, 0.7, 0.7, 1.0 }; // 다리 아래부분 조명 색
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse4);
    glPushMatrix();
    glTranslatef(0.0, -LOWER_LEG_HEIGHT, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void tail()
{
    GLfloat light_diffuse[] = { 1.0, 0.4, 0.5, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(ta, TAIL_RADIUS, TAIL_RADIUS, TAIL_HEIGHT, 10, 10);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);

    glRotatef(theta[0], 0.0, 1.0, 0.0);
    glRotatef(theta[1], 0.0, 0.0, -1.0);
    torso();
    glPushMatrix();

    glTranslatef(-(TORSO_RADIUS + HEAD_RADIUS) * 2.9, 0.0, 0.0);
    glRotatef(theta[2], 1.0, 0.0, 0.0);
    glRotatef(theta[3], 0.0, 1.0, 0.0);
    glRotatef(theta[4], 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.5 * HEAD_HEIGHT, 0.0);
    head();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS + UPPER_ARM_RADIUS) * 2.5, 0.05 * TORSO_HEIGHT, 1.0);
    glRotatef(theta[5], 0.0, 0.0, 1.0);
    glRotatef(theta[6], 1.0, 0.0, 0.0);
    right_upper_arm();

    glTranslatef(0.0, -2 * LOWER_ARM_HEIGHT, 0.0);
    glRotatef(theta[7], 0.0, 0.0, 1.0);
    glRotatef(theta[8], 1.0, 0.0, 0.0);
    right_lower_arm();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS + UPPER_ARM_RADIUS) * 2.5, -0.15 * TORSO_HEIGHT, -1.0);
    glRotatef(theta[9], 0.0, 0.0, 1.0);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    left_upper_arm();

    glTranslatef(0.0, -0.5 * UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[11], 0.0, 0.0, 1.0);
    glRotatef(theta[12], 1.0, 0.0, 0.0);
    left_lower_arm();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS + UPPER_LEG_RADIUS) * 0.7, 0.15 * UPPER_LEG_HEIGHT, 1.0);
    glRotatef(theta[13], 0.0, 0.0, 1.0);
    right_upper_leg();

    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[14], 0.0, 0.0, 1.0);
    right_lower_leg();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS + UPPER_LEG_RADIUS) * 0.7, 0.15 * UPPER_LEG_HEIGHT, -1.0);
    glRotatef(theta[15], 0.0, 0.0, 1.0);
    left_upper_leg();

    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[16], 0.0, 0.0, 1.0);
    left_lower_leg();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(TAIL_RADIUS, TAIL_HEIGHT * 0.2, 0.0);
    glRotatef(theta[17], 1.0, 0.0, 0.0);
    glRotatef(theta[18], 0.0, 0.0, 1.0);
    tail();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}



void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (angle == 0) { // torso1
            theta[angle] += 5.0;
            if (theta[angle] > 360.0) theta[angle] -= 360.0;
        }
        else if (angle == 1) { // torso2
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 2) { // head1
            theta[angle] += 5.0;
            if (theta[angle] > 45.0) theta[angle] = 45.0;
        }
        else if (angle == 3) { // head2 - 수정 필요
            theta[angle] += 5.0;
            if (theta[angle] > 90.0) theta[angle] = 90.0;
        }
        else if (angle == 4) { // head3 
            theta[angle] += 5.0;
            if (theta[angle] > 30.0) theta[angle] = 30.0;
        }
        else if (angle == 5) { // right_upper_arm1 
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 6) { // right_upper_arm2
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 7) { // right_lower_arm1
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 8) { // right_lower_arm2
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 9) { // left_upper_arm1
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 10) { // left_upper_arm2
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 11) { // left_lower_arm1
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 12) { // left_lower_arm2
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 13) { // right_upper_leg
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 14) { // right_lower_leg
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 15) { // left_upper_leg
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 16) { // left_lower_leg
            theta[angle] += 5.0;
            if (theta[angle] > 60.0) theta[angle] = 60.0;
        }
        else if (angle == 17) { // tail1
            theta[angle] += 5.0;
            if (theta[angle] > 45.0) theta[angle] = 45.0;
        }
        else if (angle == 18) { // tail2
            theta[angle] += 5.0;
            if (theta[angle] > 45.0) theta[angle] = 45.0;
        }

    }
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (angle == 0) { // torso1 
            theta[angle] -= 5.0;
            if (theta[angle] < 360.0) theta[angle] += 360.0;
        }
        else if (angle == 1) { // torso2 
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 2) { // head1 
            theta[angle] -= 5.0;
            if (theta[angle] < -45.0) theta[angle] = -45.0;
        }
        else if (angle == 3) { // head2 -수정 필요
            theta[angle] -= 5.0;
            if (theta[angle] < -90.0) theta[angle] = -90.0;
        }
        else if (angle == 4) { // head3 
            theta[angle] -= 5.0;
            if (theta[angle] < -30.0) theta[angle] = -30.0;
        }
        else if (angle == 5) { // right_upper_arm1 
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 6) { // right_upper_arm2
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 7) { // right_lower_arm1
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 8) { // right_lower_arm2
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 9) { // left_upper_arm1
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 10) { // left_upper_arm2
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 11) { // left_lower_arm1
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 12) { // left_lower_arm2
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 13) { // right_upper_leg
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 14) { // right_lower_leg
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 15) { // left_upper_leg
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 16) { // left_lower_leg
            theta[angle] -= 5.0;
            if (theta[angle] < -60.0) theta[angle] = -60.0;
        }
        else if (angle == 17) { // tail1
            theta[angle] -= 5.0;
            if (theta[angle] < -45.0) theta[angle] = -45.0;
        }
        else if (angle == 18) { // tail2
            theta[angle] -= 5.0;
            if (theta[angle] < -45.0) theta[angle] = -45.0;
        }
    }
    display();
}

void menu(int id)
{
    if (id < 19) angle = id;
    if (id == 19) exit(0);
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-15.0, 15.0, -15.0 * (GLfloat)h / (GLfloat)w,
            15.0 * (GLfloat)h / (GLfloat)w, -15.0, 15.0);
    else
        glOrtho(-15.0 * (GLfloat)w / (GLfloat)h,
            15.0 * (GLfloat)w / (GLfloat)h, 0.0, 15.0, -15.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myinit()
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess = { 100.0 };

    GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 }; // 하얀 조명
    GLfloat light_position0[] = { 0.5, 1.0, 1.0, 0.0 }; // 전체 조명 위치
    GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);

    /* allocate quadrics with filled drawing style */

    h = gluNewQuadric();
    gluQuadricDrawStyle(h, GLU_FILL);
    t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    gluQuadricTexture(t, GL_TRUE);
    lua = gluNewQuadric();
    gluQuadricDrawStyle(lua, GLU_FILL);
    lla = gluNewQuadric();
    gluQuadricDrawStyle(lla, GLU_FILL);
    gluQuadricTexture(lla, GL_TRUE);
    rua = gluNewQuadric();
    gluQuadricDrawStyle(rua, GLU_FILL);
    rla = gluNewQuadric();
    gluQuadricDrawStyle(rla, GLU_FILL);
    gluQuadricTexture(rla, GL_TRUE);
    lul = gluNewQuadric();
    gluQuadricDrawStyle(lul, GLU_FILL);
    lll = gluNewQuadric();
    gluQuadricDrawStyle(lll, GLU_FILL);
    gluQuadricTexture(lll, GL_TRUE);
    rul = gluNewQuadric();
    gluQuadricDrawStyle(rul, GLU_FILL);
    rll = gluNewQuadric();
    gluQuadricDrawStyle(rll, GLU_FILL);
    ta = gluNewQuadric();
    gluQuadricTexture(rll, GL_TRUE);
    gluQuadricDrawStyle(ta, GLU_FILL);
}

AUX_RGBImageRec* LoadBMP(char* szFilename) {
    FILE* pFile = NULL;
    if (!szFilename) {
        return NULL;
    }
    fopen_s(&pFile, szFilename, "r");
    if (pFile) {
        fclose(pFile);
        return auxDIBImageLoad(szFilename);     //파일로부터 메모리로
    }
    return NULL;
}

int LoadGLTextures(char* szFilePath) {       //파일을 로드하고 텍스쳐로 변환
    int Status = FALSE;
    glClearColor(1.0, 1.0, 1.0, 1.0);
    memset(pTextureImage, 0, sizeof(void*) * 1);    //포인터를 널로

    if (pTextureImage[0] = LoadBMP(szFilePath)) {   //비트맵을 로드하고 오류확인
        Status = TRUE;                              //상태 플랙을 True로
        glGenTextures(1, &MyTextureObject[0]);      //텍스쳐 생성
        glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
            pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
            0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glEnable(GL_TEXTURE_2D);
    }
    if (pTextureImage[0]) {                 //텍스쳐가 존재하면
        if (pTextureImage[0]->data) {       //텍스쳐 영상이 존재하면
            free(pTextureImage[0]->data);   //텍스쳐 영상공간 반납
        }
        free(pTextureImage[0]);             //텍스쳐 반납
    }
    return Status;
}

int main(int argc, char** argv)
{
    printf("argc = %d", argc);
    if (argc <= 1) {
        printf("\n%s\n\n", "Usage : TextureDLG3_Consol.exe [BMPFileName.bmp]");
        exit(1);
    }
    else if (argc > 2) {
        printf("\nToo Many Arguments!\nArgument is Only one\n");
        exit(1);
    }
    else {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(700, 700);
        glutCreateWindow("Dog");
        myinit();
        glutReshapeFunc(myReshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);

        glutCreateMenu(menu);
        glutAddMenuEntry("torso1", 0);
        glutAddMenuEntry("torso2", 1);
        glutAddMenuEntry("head1", 2);
        glutAddMenuEntry("head2", 3);
        glutAddMenuEntry("head3", 4);
        glutAddMenuEntry("right_upper_arm1", 5);
        glutAddMenuEntry("right_upper_arm2", 6);
        glutAddMenuEntry("right_lower_arm1", 7);
        glutAddMenuEntry("right_lower_arm2", 8);
        glutAddMenuEntry("left_upper_arm1", 9);
        glutAddMenuEntry("left_upper_arm2", 10);
        glutAddMenuEntry("left_lower_arm1", 11);
        glutAddMenuEntry("left_lower_arm2", 12);
        glutAddMenuEntry("right_upper_leg", 13);
        glutAddMenuEntry("right_lower_leg", 14);
        glutAddMenuEntry("left_upper_leg", 15);
        glutAddMenuEntry("left_lower_leg", 16);
        glutAddMenuEntry("tail1", 17);
        glutAddMenuEntry("tail2", 18);
        glutAddMenuEntry("quit", 19);
        glutAttachMenu(GLUT_MIDDLE_BUTTON);
        if (LoadGLTextures(argv[1])) {
            glEnable(GL_TEXTURE_2D);
            glutMainLoop();
        }
    }


}
