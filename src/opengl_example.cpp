#include <stdio.h>
#include <stdlib.h>

// 必须先包含GLEW头文件，再包含其他OpenGL头文件，否则会导致符号冲突
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/**
 * 一个全局的GL变量，用于操作顶点的缓冲器对象
 */
GLuint VBO, EBO;

static void RenderScenceCB() {
  /**
   * @brief 用于清除指定的缓冲区，通常用于每一帧绘制开始时清空窗口内容，保证画面不会残留上一次的内容
   * 
   * @note 可以多种缓冲区一起清除，如颜色缓冲、深度缓冲等
   *       例如：glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   * 
   * @note 清除颜色缓冲后，窗口背景色会变为glClearColor设置的颜色
   *       如果没有设置glClearColor，则默认背景色为黑色
   * 
   * @note 该函数必须在绘制之前调用，否则不会看到任何内容
   */
  glClear(GL_COLOR_BUFFER_BIT);

  /**
   * @brief 启用顶点属性数组，告诉OpenGL我们将使用顶点数据
   * 
   * @note 顶点属性是 OpenGL 渲染的基础，决定了每个顶点的空间位置和各种视觉特征，
   *       是实现各种图形和视觉效果的核心数据。没有顶点属性，OpenGL 无法知道如何绘制和处理你的图形。
   * 
   * @note 顶点属性数组是OpenGL中用于存储顶点数据的缓冲区，通常用于传递顶点坐标、颜色、法线等信息
   * 
   * @note 这里index=0是一个逻辑概念，即使用第一租顶点属性数组
   *       一般可以自定义0是位置，1是颜色，2是法线等，这些都是自定义的，可以修改
   * 
   * @note 在绘制完成后，通常需要禁用顶点属性数组，以避免影响后续的绘制操作
   *       例如：glDisableVertexAttribArray(0);
   */
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  /**
   * @brief 用于指定顶点属性数组的数据格式和在缓冲区中的存储方式，让 OpenGL 知道如何从 VBO（顶点缓冲对象）中读取顶点数据。
   * 
   * @param index 顶点属性的索引，跟glEnableVertexAttribArray()中使用的索引保持一致
   * @param size 每个顶点属性的组件数量，即该属性一组数据的大小，通常为2（如纹理坐标）、3（如位置、法线）或4（如颜色）
   * @param type 数据类型，通常是GL_FLOAT（浮点数），也可以是GL_INT（整数）等
   * @param normalized 是否将数据归一化，如果为GL_TRUE，则将整数数据归一化到[0, 1]或[-1, 1]范围。浮点数一般为GL_FALSE，整数类型通常为GL_TRUE
   * @param stride 相邻顶点属性之间的字节偏移量，即步长，如果为0，则表示紧密排列
   * @param pointer 在每个顶点的起始位置的偏移量，通常为0表示从缓冲区的开头开始读取
   */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  
  /**
   * @brief 按照索引数组的顺序绘制顶点，实现顶点重用和高效绘制。
   * @param mode 绘制模式，指定如何解释顶点数据
   *             GL_POINTS：将每个顶点作为一个独立的点绘制
   *             GL_LINES：将每两个顶点连接成一条线段
   *             GL_LINE_STRIP：将顶点依次连接成一条折线
   *             GL_TRIANGLES：每三个顶点组成一个三角形
   *             GL_TRIANGLE_STRIP：每三个顶点组成一个三角形，且共享边
   * @param count 要绘制的顶点数量，这里是6，表示绘制两个三角形
   * @param type 索引数据的类型，通常是GL_UNSIGNED_INT（无符号整数），也可以是GL_UNSIGNED_SHORT等
   * @param indices 指向索引数据的指针，通常为0表示使用当前绑定的EBO（元素缓冲对象）
   */
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


  /**
   * @brief 用于按照指定的方式从当前绑定的顶点缓冲区（VBO）中顺序读取顶点数据并进行绘制
   * @param mode 绘制模式，指定如何解释顶点数据
   *             GL_POINTS：将每个顶点作为一个独立的点绘制
   *             GL_LINES：将每两个顶点连接成一条线段
   *             GL_LINE_STRIP：将顶点依次连接成一条折线
   *             GL_TRIANGLES：每三个顶点组成一个三角形
   *             还有其他模式，如GL_TRIANGLE_STRIP、GL_TRIANGLE_FAN等
   * @param first 指定从哪个顶点开始绘制，通常为0表示从第一个顶点开始
   * @param count 指定要绘制的顶点数量，根据绘制模式的不同，实际绘制的图元数量会有所不同
   * 
   * @note 在调用此函数之前，必须确保已经正确设置了顶点属性指针（glVertexAttribPointer）并启用了相应的顶点属性数组（glEnableVertexAttribArray）
   * @note 此函数会使用当前绑定的顶点缓冲区（VBO）中的数据进行绘制
   * @note 绘制完成后，通常需要禁用顶点属性数组（glDisableVertexAttribArray）以避免影响后续的绘制操作
   * @note 该函数不会自动刷新屏幕，需要调用glutSwapBuffers()来交换前后缓冲区以显示绘制结果
   * 
   */
  glDrawArrays(GL_TRIANGLES, 0, 3);

  /**
   * @brief 禁用顶点属性数组，通常在绘制完成后调用，以避免影响后续的绘制操作
   * 
   * @param index 顶点属性的索引，通常与glEnableVertexAttribArray()中使用的索引一致
   */
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  /**
   * @brief 用于交换前后台缓冲区，实现双缓冲显示。
   */
  glutSwapBuffers();
}


static void CreateVertexBuffer() {
  // 正方形的四个顶点坐标
  float Vertices[] = {
    // x,    y,     z,    u,    v
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 0.0f, 0.0f
  };

  GLuint Indices[] = {0, 1, 2, 2, 3, 0};

  /**
   * @brief 用于生成缓冲区对象的标识符（ID），通常用于创建 VBO（顶点缓冲对象）、EBO（索引缓冲对象）等。
   * @param n 要生成的缓冲区对象的数量
   * @param buffers 指向GLuint数组的指针，用于存储生成的缓冲区对象ID
   * 
   * @note 只分配ID，不分配实际的显存空间。
   * 
   * @note 生成的ID后续可用 glBindBuffer 绑定，再用 glBufferData 分配和上传数据
   */
  glGenBuffers(1, &VBO);

  /**
   * @brief 绑定指定类型的缓冲区对象到当前的OpenGL上下文
   * @param type 缓冲区的类型：
   *             GL_ARRAY_BUFFER，顶点属性缓冲区，存储顶点信息，如顶点坐标，颜色、法线等
   *             GL_ELEMENT_ARRAY_BUFFER，元素索引缓冲区，存储顶点索引数据，用于索引绘制
   * @param buffer 要绑定的缓冲区对象的ID，这里是之前创建并存储顶点数据的VBO
   * 
   * @note 绑定缓冲区后，后续对该类型缓冲区的操作（如设置数据、绘制等）都会作用于当前绑定的缓冲区
   */
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  
  /**
   * @brief 为当前绑定的缓冲区对象分配显存空间，并（可选）上传数据。常用于 VBO（顶点缓冲对象）、EBO（索引缓冲对象）等。
   * @param target 缓冲区的类型，通常是 GL_ARRAY_BUFFER（顶点缓冲）或 GL_ELEMENT_ARRAY_BUFFER（索引缓冲）
   * @param size 要分配的缓冲区大小（以字节为单位）
   * @param data 指向要上传到缓冲区的数据的指针，如果为 NULL，则只分配空间不上传数据
   * @param usage 指定缓冲区的使用模式，常用的有：
   *              GL_STATIC_DRAW：数据不会改变，适合静态几何体
   *              GL_DYNAMIC_DRAW：数据会改变，适合动态几何体
   *              GL_STREAM_DRAW：数据每次绘制都会改变，适合临时数据
   * 
   */
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

/**
 * 主函数
 */
int main(int argc, char **argv) {
  /**
   * @brief GLUT/FreeGLUT 的初始化入口，必须最先调用，为 OpenGL
   * 程序创建窗口和上下文做准备。
   */
  glutInit(&argc, argv);

  /**
   * @brief 用于设置窗口的显示模式，即指定窗口的缓冲类型、颜色模式等。
   * 
   * 缓冲类型： 
   * GLUT_SINGLE  单缓冲模式，只有一个前台缓冲区，绘制操作直接在屏幕上进行，容易出现闪烁
   * GLUT_DOUBLE 双缓冲模式，前台和后台各有一个缓冲区，绘制操作在后台缓冲区完成后再交换到前台，减少闪烁
   * 颜色模式：
   * GLUT_RGB    RGB颜色模式，使用红、绿、蓝三种颜色通道
   * GLUT_RGBA   RGBA颜色模式，除了RGB外，还包含Alpha通道（透明度）
   * 其他模式：
   * GLUT_DEPTH  深度缓冲，用于处理3D场景中的深度测试
   * 
   */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  /**
   * @brief 设置窗口的大小(宽度和高度)
   */
  glutInitWindowSize(1136, 640);    //窗口尺寸

  /**
   * @brief 用于设置窗口初始显示时左上角的位置（以屏幕左上角为原点，单位：像素）。
   * @note (x, y)，x表示窗口左上角的横坐标，y表示窗口左上角的纵坐标。
   */
  glutInitWindowPosition(100, 100); //窗口位置

  /**
   * @brief 创建一个 OpenGL 窗口，并初始化 OpenGL 上下文。
   * 
   * @note 必须在设置完window的相关参数后调用此函数。
   */
  glutCreateWindow("20200414-02");  //窗口标题

  /**
   * @brief 注册窗口的显示（绘制）回调函数。
   * 
   * @note 参数是一个函数指针，指向一个无参数、无返回值的函数。
   * @note 每当窗口需要重绘时（例如窗口被遮挡后重新显示，或调用 glutPostRedisplay()），GLUT会调用这个回调函数。
   * @note 在这个回调函数中，通常会执行绘制操作，如清除屏幕、设置颜色、绘制几何图形等。
   * @note 必须在glutMainLoop()之前调用此函数，以确保GLUT知道如何绘制窗口内容。
   * 
   */
  glutDisplayFunc(RenderScenceCB);

  /**
   * @brief 初始化GLEW库，加载和初始化所有 OpenGL 扩展函数指针，让你可以在代码中直接使用 OpenGL 的新特性（如 VBO、着色器等）。
   * 
   * @note 必须在创建 OpenGL 上下文（即 glutCreateWindow 之后）调用，否则初始化会失败
   */
  GLenum res = glewInit();
  if (res != GLEW_OK) {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return 1;
  }

  /**
   * void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
   * @brief 设置清除颜色缓冲区时所用的颜色，也就是窗口背景色。
   * 
   * @note 此处设置的颜色，会在每次调用glClear(GL_COLOR_BUFFER_BIT)时生效
   * 
   */
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // 创建顶点，并分配顶点空间
  CreateVertexBuffer();

  /**
   * @brief OpenGL 程序进入事件循环，持续响应窗口和用户操作，是 GLUT 应用的核心入口
   * 
   * @note 该函数不会返回，程序将在此循环中持续运行，直到窗口关闭。
   */
  glutMainLoop();
  return 0;
}