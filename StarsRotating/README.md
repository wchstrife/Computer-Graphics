# B-1 StarsRotating

- 王宸昊
- 2019214541
- wch19@mails.tsinghua.edu.cn

## 实验要求

绘制出星星旋转的效果

1) 多个星星绕着一个中心旋转;
2) 星星的颜色不同;
3) 效果类似螺旋的效果，星星不断向外圈扩散;
4) 至少实现阿基米德螺线、对数螺线、费马螺线中一种的效果;

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
./assignment2 [--width=x] [--height=y] [--title=”Assignment 2”]
```

## 实验原理

实现一个Star类，其中包括位置和颜色属性，具体的定义分别为位置索引的float pos和颜色向量glm::vec3 color。

每个随机赋予每个Star实例一个随机的颜色，为了减少计算量，提前计算好所有的位置坐标，存储在starPos向量中，每个Star当前的坐标由索引表示。

渲染过程中，每次生成一个Star实例，将其加入到队列中，并对其位置索引进行自增，超过索引的最大值回到窗口原点。

预计算坐标值，采用阿基里德罗螺旋线参数方程进行更新。

## 实验效果

见StarsRotating-演示视频.mov
