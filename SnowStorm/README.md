# B-5 SnowStorm

- 王宸昊
- 2019214541
- wch19@mails.tsinghua.edu.cn

## 实验要求

实现简单的粒子效果-下雪

1) 实现下雪的粒子效果;
2) 粒子的大小不一，运动方向模拟雪花运动方向; 
3) 开始时雪花较少，随着时间慢慢增多;

## 实验环境

- OSX
- CMake
- GCC
- OpenGL
- GLUT
- GLEW
- GLM
- SOIL

## 运行

```bash
mkdir build
cd build
cmake ..
make
./SnowStorm [--width=x] [--height=y] [--title=”Chenhao Wang 2019214541”]
```

## 实验原理

按方向上键加快粒子下落的速度，按方向下键减少粒子下落速度。按下ESC退出程序

每个Snow Particle类有三个属性
1. glm::vec3 Position ： 粒子位置
2. glm::vec3 Velocity ： 粒子速度
3. GLfloat Size ： 粒子大小

对于每个粒子的初始化，随机初始化位置和速度大小后插入Buffer队列中，同时加载纹理，绑定。

随后随时间按照速度更改粒子的位置，同时每隔T时间不断生成新的粒子。

当粒子到达窗口的底端时，将其位置重新设置于窗口的最上方。

使用GLUT添加的键盘的响应事件，按下时增加或者减少速度的Y方向分量。

## 实验效果

见 B-5 SnowStorm 演示视频.mov
