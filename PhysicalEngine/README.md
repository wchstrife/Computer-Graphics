# A-3  Physical Engine

- 王宸昊
- 2019214541
- wch19@mails.tsinghua.edu.cn

## 实验要求

实现物理引擎当中的6种效果

1. collision
2. collision_stress
3. damping_test
4. newtons_cradle
5. rotation_test
6. spring_rotation

## 实验环境

VS2012(需要注意不能使用VS2015以上的版本，否则部分库文件会无法链接)

## 运行

```bash
./physics [scene]
```

## 实验原理

主要修改了src/physics/下的collisions、physics、spherebody、spring文件

根据手册的指导，实现了添加重力，实现球体到球体，球体到三角形以及球体到平面之间的碰撞

对球的速度和角速度以及力和扭矩的模拟

实现碰撞阻尼和弹簧阻尼。

## 实验效果

见实验录屏文件夹
