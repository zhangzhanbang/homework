---
title:Python 交互式编程
---

## Python交互式编程——实验报告

#### 实验名称： 用Python做计算器，做数学题

#### 姓名： 张展邦

#### 学号：18342134



![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/lab4/python.png)



### 一、实验目的

1. 了解一种“解释型”语言 python
2. 使用 python 做一些简单的科学计算



### 二、实验环境

![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/lab4/sympy.png)

- 编程工具：Python（Anaconda）
- Sympy强力支持
- 操作系统：Windows 10



### 三、使用 python 作为计算器

**3.1 使用简单表达式**

- 基本的四则运算都可以直接计算出
- 另：**变量万能**

> \>>> sum = 3-1
>
> \>>> print(sum)
>
> 2
>
> \>>> 1+1
>
> 2
>
> \>>> sum = 2+3
>
> \>>> print(sum)
>
> 5
>
> \>>> sum *= 2
>
> \>>> print(sum)
>
> 10

- 除法分两种，用'/'，保留小数部分；用'//'，舍弃小数部分（向下取整）

> \>>> 1/3
>
> 0.3333333333333333
>
> \>>> 5//3
>
> 1

- 幂运算，用符号'**'，以下是 $ 3^2 $的计算例子

> \>>> 3**2
>
> 9

**3.2 使用数学函数**

Python里用专门用于数学计算的库math

- 导入math

> \>>> import math

- math有什么，用help函数

> \>>> help(math)


