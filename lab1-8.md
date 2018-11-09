---
title : 自上而下，逐步求精
---

## 自上而下，逐步求精

#### 概念——自上而下的设计（逐步设计）

<center>  ![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/lab1-8/module%20program.png) </center>

- **自上而下**的设计是将系统分解成一个个小块，把**复杂抽象**的系统分解成**简单特定**的模块。
- 在**自上而下**的设计中，系统的整体概念被设计出，并指出下一层的子系统但不详细说明。然后，每个子系统都会进行更为细化的说明，例如，有时会分解为不同层级的子系统，以便让子系统分解成**基础元素**。

<center> ![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/lab1-8/top-down%20figure%201.gif) </center>

- 只要区分出所有基础元素，就可以像计算**模块**一样构建出。一旦构建出模块，就可以毫不费力地把它们组合在一起，由这些模块构建整个系统。
- 自上而下的设计通常是一个用**通俗语言**做出的计划，因为这是一种整体的把握。
- 另外，每个模块下所包含的子任务数一般比较少，在4-7个左右。任务划分的实质是问题规模缩减，更有助于开发人员完成简单部分。**任务划分要足够细，使得编码人员能使用计算机代码实现问题的每个部分**。

#### 如何做到**自顶向下，逐步求精**

<center> ![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/lab1-8/chart.png) </center>

#### 以观察的洗衣机为案例，用伪代码描述的控制程序设计

#### 1）从整体来看，洗衣机洗衣流程有哪些？

1. 漂洗
2. 脱水
3. 停机

#### 2）每个大步骤分别又包含哪些小步骤呢？

- 漂洗：注水->转筒转动->排水
- 脱水：滚筒转动
- 停机：机器停止

#### 3）用伪代码描述程序设计
> 假设洗衣机可执行的基本操作如下：<br/>
> water_in_switch(open_close) // open 打开上水开关，close关闭  <br/>
> water_out_switch(open_close) // open 打开排水开关，close关闭  <br/>
> get_water_volume() //返回洗衣机内部水的高度  <br/>
> motor_run(direction) // 电机转动。left左转，right右转，stop停 <br/>
> time_counter() // 返回当前时间计数，以秒为单位 <br/>
> halt(returncode) //停机，success 成功 failure 失败 <br/>

#### *0-1 注水

```c
water_in_switch(open)
water_out_switch(close)
WHILE get_water_volume() < need_volume
DO
	DO NOTHING
END WHILE
water_in_switch(close)
```

#### *0-2 排水

```c
water_out_switch(open)
WHILE get_water_volume() > 0
DO
	DO NOTHING
END WHILE
water_out_switch(close)
```

#### *0-3 滚筒转动(time)
```c
begin_time <- time_counter()
WHILE time_counter() < begin_time + time
DO
	motor_run(left)
	motor_run(right)
	motor_run(stop)
END
```

#### 1）漂洗
```c
注水()
滚筒转动(time)
排水()
```

#### 2）脱水
```c
滚筒转动(time)
```

#### 3）停机
```c
halt(success)
```
