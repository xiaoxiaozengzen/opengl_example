#include <stdio.h>
#include <stdlib.h>

// 必须先包含GLEW头文件，再包含其他OpenGL头文件，否则会导致符号冲突
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

/**
 * 一个全局的GL变量，用于操作顶点的缓冲器对象
 */
GLuint VBO;
 
//渲染回调函数
static void RenderScenceCB()
{
    // 清空颜色缓存
    glClear(GL_COLOR_BUFFER_BIT);
 
    // 开启顶点属性
    glEnableVertexAttribArray(0);
    // 绑定GL_ARRAY_BUFFER缓冲器
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 告诉管线怎样解析bufer中的数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
 
    // 开始绘制几何图形(绘制一个点)
    glDrawArrays(GL_POINTS, 0, 1);
 
    //  禁用顶点数据
    glDisableVertexAttribArray(0);
 
    // 交换前后缓存
    glutSwapBuffers();
}
 
//创建顶点缓冲器
static void CreateVertexBuffer()
{
    // 将点置于屏幕中央
    float Vertices[3] = {0.0f, 0.0f, 0.0f};
 
    // 创建缓冲器
    glGenBuffers(1, &VBO);
    // 绑定GL_ARRAY_BUFFER缓冲器
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 绑定顶点数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}
 
/**
 * 主函数
 */
int main(int argc, char** argv)
{
    /**
     * @brief GLUT/FreeGLUT 的初始化入口，必须最先调用，为 OpenGL 程序创建窗口和上下文做准备。
     */
    glutInit(&argc, argv);
 
    //显示模式：双缓冲、RGBA
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
 
    //窗口设置
    glutInitWindowSize(1136, 640);     //窗口尺寸
    glutInitWindowPosition(100, 100);  //窗口位置
    glutCreateWindow("20200414-02");   //窗口标题
 
    //开始渲染
    glutDisplayFunc(RenderScenceCB);
 
    //检查GLEW是否就绪，必须要在GLUT初始化之后！
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
 
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 
    CreateVertexBuffer();
 
    //通知开始GLUT的内部循环
    glutMainLoop();
    return 0;
}