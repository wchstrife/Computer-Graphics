# B-6 TheBezierSurface

- 王宸昊
- 2019214541
- wch19@mails.tsinghua.edu.cn

## 实验要求

绘制贝塞尔曲面

1) 使用细分控制着色器 TCS 设置细分等级。
2) 使用细分控制着色器 TES 根据贝塞尔曲面的数学方程计算新顶点坐标、纹理坐标， 计算法线向量。
3) 添加键盘控制改变曲面的平滑度。

## 实验环境

- OSX
- CMake
- GCC
- OpenGL
- GLUT
- GLM
- SOIL

## 运行

```bash
mkdir build
cd build
cmake ..
make
./Bezier [--width=x] [--height=y] [--title=”2019214541 Chenhao Wang”]
```

## 实验原理

使用ESC键关闭程序，按下0键切换显示网格和纹理。

使用QWE键增加点的XYZ坐标值， ASD减少点XYZ的坐标值。

RT增加平滑度UV，FG减少平滑度uv

OpenGl定义一条曲线时，也把它定义为一个曲线方程。我们把这条曲线的参数成为u,它的值域就是曲线的定义域。曲面则需要u和v两个参数来描述。注意，u和v参数只表示了描述曲线的参数方程的范围，它们并没有反映实际的坐标值。其坐标可以表示为:x = f(u); y = g(u); z = h(u);

控制点

贝塞尔曲线的形状由控制点来控制。贝塞尔曲线的控制点个数为曲线的阶。根据控制点的个数，贝塞尔曲线又分为二次贝塞尔曲线，三次贝塞尔曲线，高阶贝塞尔曲线。

OpenGL提供了一些函数来绘制贝塞尔曲线和曲面。我们只需要提供控制点和u,v作为参数，然后调用求值函数来绘制曲线。

在本实验中使用5*5的GLfloat数组表示控制顶点，在每。次渲染的Update函数中，使用glMap2f, glMapGrid2f， glEvalMesh2等函数进行显示贝塞尔曲线

## 实验效果

见 Bezier-演示视频.mov
