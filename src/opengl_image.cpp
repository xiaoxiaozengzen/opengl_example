// 纯GL相关头文件实现图片显示（假设图片数据已准备好，使用GLUT窗口）

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// 假设你有一张RGB图片，宽高如下（可替换为实际图片数据）
const int imgWidth = 256;
const int imgHeight = 256;
unsigned char image[imgHeight][imgWidth][3]; // 伪造一张纯色图片

GLuint textureID;

void InitImageData() {
  // 填充为蓝色
  for (int y = 0; y < imgHeight; ++y)
    for (int x = 0; x < imgWidth; ++x) {
      image[y][x][0] = 0;   // R
      image[y][x][1] = 128; // G
      image[y][x][2] = 255; // B
    }
}

void InitTexture() {
  /**
   * @brief 用于生成一个或多个纹理对象的ID（标识符），类似于缓冲区对象的 glGenBuffers
   */
  glGenTextures(1, &textureID);

  /**
   * @brief 用于将指定的纹理对象绑定到当前的纹理目标，让后续的纹理操作都作用于这个纹理对象
   * @param target 纹理目标，
   *               GL_TEXTURE_2D（二维纹理）
   *               GL_TEXTURE_1D（一维纹理）
   *               GL_TEXTURE_3D（三维纹理）
   *               GL_TEXTURE_CUBE_MAP（立方体纹理）
   * @param texture 要绑定的纹理对象ID，这里是之前生成的textureID
   */
  glBindTexture(GL_TEXTURE_2D, textureID);

  /**
   * @brief 用于设置当前绑定纹理对象的参数，比如纹理的过滤方式、环绕方式等。
   * @param target 纹理目标，通常是 GL_TEXTURE_2D
   * @param pname 要设置的参数名称:
   *              GL_TEXTURE_MIN_FILTER：纹理缩小时的过滤方式
   *              GL_TEXTURE_MAG_FILTER：纹理放大时的过滤方式
   *              GL_TEXTURE_WRAP_S：S方向（水平）的环绕方式
   *              GL_TEXTURE_WRAP_T：T方向（垂直）的环绕方式
   * @param param 参数值，通常是一个整数或枚举值，表示具体的过滤方式或环绕方式
   *        常用的过滤方式有：
   *              GL_NEAREST：最近点过滤，直接取最近的像素值，类似马赛克效果
   *              GL_LINEAR：线性过滤，使用周围像素的加权平均值，效果更平滑
   *        常用的环绕方式有：
   */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  /**
   * @brief 用于为当前绑定的二维纹理对象分配内存并上传像素数据，即把图片数据传到 GPU 作为纹理。
   * @param target 纹理目标，通常是 GL_TEXTURE_2D
   * @param level 纹理的细节级别，通常为0表示基础级别
   * @param internalFormat 纹理在显存中的格式，这里使用 GL_RGB 表示 RGB 格式
   * @param width 纹理的宽度
   * @param height 纹理的高度
   * @param border 边框宽度，通常为0
   * @param format 像素数据的格式，这里使用 GL_RGB 表示 RGB 格式
   * @param type 像素数据的类型，这里使用 GL_UNSIGNED_BYTE 表示无符号字节类型
   * @param data 指向实际像素数据的指针，这里是之前填充的 image 数组
   */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);

  /**
   * @brief 启用纹理映射
   */
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureID);

  /**
   * @brief 开始定义一个图元（如点、线、三角形、四边形等）
   * 
   * @note 它和 glEnd 配对使用，在这两个函数之间，你可以指定顶点、颜色、纹理坐标等。
   *      
   * @note 这里使用 GL_QUADS 表示我们要绘制一个四边形
   */
  glBegin(GL_QUADS);

  /**
   * @brief 四组顶点和纹理坐标，每一组表示把纹理的某个角贴到屏幕的某个角上
   * 
   * @note 纹理坐标范围是[0, 1]，(0, 0)表示纹理的左下角，(1, 1)表示纹理的右上角
   * @note 顶点坐标范围是[-1, 1]，(-1, -1)表示窗口的左下角，(1, 1)表示窗口的右上角
   * 
   * @note 纹理坐标(0, 0)对应纹理的左下角，顶点坐标(-1, -1)对应窗口的左下角。将纹理的左下角贴到窗口的左下角。
   */
  glTexCoord2f(0, 0);
  glVertex2f(-0.5, -0.5);
  glTexCoord2f(1, 0);
  glVertex2f(1, -1);
  glTexCoord2f(1, 1);
  glVertex2f(1, 1);
  glTexCoord2f(0, 1);
  glVertex2f(-1, 1);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(512, 512);
  glutCreateWindow("Pure GL Image Show");

  InitImageData();
  InitTexture();

  glutDisplayFunc(Display);
  glutMainLoop();
  return 0;
}