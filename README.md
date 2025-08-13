# Overview

OpenGL是一套方便于用户使用的规范，而其本身包含了调用不同厂商直接在GPU中写好的程序接口，那些接口完成所有的功能实现，如完成2D、3D矢量图形渲染等功能。

OPENGL由以下模块组成：
1. GL(OpenGl)
  * OPENGL核心库
  * 作用：实现底层图形渲染API，负责显卡驱动通信，提供绘制点、线、面、纹理等基础功能
  * 头文件：<GL/gl.h>
  * 库文件：libGL.so
2. GLU(OpenGl Utility)
  * 作用：提供一些高级函数，如多边形细分、曲面、投影矩阵等，简化opengl编程
  * 头文件：<GL/glu.h>
  * 库：libGLU.so
3. GLUT(OpenGl Utility Toolkit)
  * 作用：窗口管理、输入事件、菜单等，方便快速创建opengl演示程序
  * 头文件：<GL/glut.h>
  * 库：libGLUT.so
4. GLEW(OpenGL Extension Wrangler Library)
  * 作用：管理和加载 OpenGL 扩展函数，解决不同平台/显卡支持的 OpenGL 版本和扩展不一致的问题。
  * 头文件：<GL/glew.h>
  * 库文件：libGLEW.so
5. GLM（OpenGL Mathematics）
  * 作用：提供向量、矩阵、变换等数学运算，专为 OpenGL 设计，语法类似 GLSL。
  * 头文件：<glm/glm.hpp>
  * 库文件：纯头文件库，无需链接