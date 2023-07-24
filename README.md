# WarGame
Qt战棋游戏

## 一、简介

使用了Qt的战棋游戏

## 二、部署

### （一）准备工作

安装Qt

### （二）配置

使用：C++、Qt5

环境：windows

### （三）部署截图

![部署截图](https://github.com/imrewang/WarGame/blob/main/screenshot/%E9%83%A8%E7%BD%B2%E6%88%AA%E5%9B%BE.png?raw=true)

## 三、运行截图

![开始页面](https://github.com/imrewang/WarGame/blob/main/screenshot/%E5%BC%80%E5%A7%8B%E7%95%8C%E9%9D%A2.png?raw=true)

![新手教程](https://github.com/imrewang/WarGame/blob/main/screenshot/%E6%96%B0%E6%89%8B%E6%95%99%E7%A8%8B.png?raw=true)

![游戏页面](https://github.com/imrewang/WarGame/blob/main/screenshot/%E6%B8%B8%E6%88%8F%E7%95%8C%E9%9D%A2.png?raw=true)

## 四、总结

### （一）设计模式方面

1.Qt槽和信号类似观察者模式


2.新手教程页面采用饿汉式 而 具体游戏页面采用懒汉式构造（单例模式）

由于connect在接收游戏页面退出信号同时delete游戏页面时，出现错误。但有new就应该有delete，所以采用对游戏页面设置Qt::WA_DeleteOnClose，在关闭这个窗口时Qt能够自动回收该窗口所占用的资源。


3.游戏整体和士兵等都是使用状态模式，将它们设置未begin,end等不同状态

但要注意，二者可能有同名状态，注意加上作用域


### （二）AI方面

1.使用双人模式完成的算法，在此基础上进行AI算法构建


2.采用寻找最近敌对人物的方式进行攻击


### （三）#寻路算法方面

1.寻找可行点时使用了BFS


2.找到去可行点的最短路径时，使用了DFS


3.放弃了迪杰斯特拉和A*算法


### （四）Qt动画方面

1.使用一格一格之间的移动完成士兵在整条路径上的移动


2.完善了按钮动效，要注意设置合理的时间间隔


## 五、改进方向

1.设置不同地图


2.改善游戏平衡


3.改进AI算法


## 六、说明

图片资源大多使用的是easytech游戏公司的《欧陆战争7：中世纪》的资源

其游戏官网为：https://ieasytech.com/
