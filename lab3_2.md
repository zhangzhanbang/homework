---
  title : machine language programming
---

### 硬件编程–机器指令编程——实验报告

#### 实验名称： 硬件编程与机器指令编程学习
#### 张展邦 18342134

## 索引 ##
* [一、实验目的](#1)
* [二、实验工具](#2)
* [三、实验过程](#3)
	* [前置知识](#4) 
	* [Program 1 简单程序](#5)
	* [program 2 简单循环](#6)

<h3 id="1"> 一、实验目的 </h3>

- 理解冯·诺伊曼计算机的结构
- 理解机器指令的构成
- 理解机器指令执行周期
- 用汇编编写简单程序

<h3 id="2"> 二、实验工具 </h3>

- 简单 CPU 仿真工具 [Pippin CPUSim](http://www.science.smith.edu/~jcardell/Courses/CSC103/CPUsim/cpusim.html)
- 由于这个网页实在太老，需要设置兼容性视图以及安装环境[点这里](https://ks0508.github.io/SE-project/QA1/jre.zip)
- 最后感谢一波老学委的辛勤付出

<h3 id="3"> 三、实验过程 </h3>

<h4 id="4"> 前置知识 </h4>

##### 做实验之前要先学一些指令（PIPPIN Instruction Set）

- ADD X 把储存在内存地址X的值加到累加器ACC
- ADD #n 把数值n加到累加器ACC
- SUB X/#n 减法
- MUL X/#n 乘法
- DIV X/#n 除法
- LOD X 将累加器ACC的值置为储存在内存地址X的值
- LOD #n 将累加器ACC的值置为n
- STO X 将内存地址X的值置为当前累加器ACC的值
- JMP n 无条件跳转：将PC设置为n并在该地址执行指令。
- JMZ n	 条件跳转：if 累加器ACC = 0，将PC设置为n并在该地址执行指令；否则转到下一条指令。

##### RAM，PC，IR，Decoder，MUX，ALU，ACC都是些什么东西

- RAM 内存，用于存储指令与值，仔细看模拟器两者是分区储存的
- PC 用于记录CPU当前执行到的指令的地址
- IR 指令存储器，暂时存储当前要执行的指令
- Decoder 解码器，解析指令
- MUX 数据选择器（中转电子元件），从多个输入信号中选择一个输出
- ALU 算术逻辑单元，实现计算
- ACC 存储计算结果的存储器

<h4 id = "5" > Program 1:  Add 2 numbers（简单程序）<h4>

1. 根据表格把指令填进模拟器

![]( https://github.com/zhangzhanbang/homework/raw/gh-pages/images/machine%20code/program1/p1.png)

2. 一步一步看按step（明白了原理后按play流畅观影）

![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/machine%20code/program1/p2.png)

3. 最后无聊看一下机器代码是怎么样的（做完homework后想必都会分解机器码了）

![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/machine%20code/program1/p3.png)

##### 指令背后的执行

##### LOD #3

1. PC当前记录的地址是0，在内存中地址为0的指令LOD #3取出
2. 经过传输，指令LOD #3被储存在IR中
3. IR将LOD指令传输给Decoder，解码后，Decoder把LOD指令传给ALU，并命令MUX把操作数3传递到ALU
4. ALU进行计算
5. 计算后的结果存储到ACC
6. 指令执行后，PC的地址+2，指向下一条要执行的指令

##### ADD W

1. PC当前记录的地址为8，把内存中地址为8的指令ADD W取出
2. 经过传输，指令ADD W被储存在IR中
3. IR将ADD指令传输给Decoder，解码后，Decoder把ADD指令传给ALU，ALU指示ACC把值传过来，Decoder再指示把内存里地址为W的值传过来，指示MUX接收内存传来的值，并将其传到ALU里。
4. ALU进行计算
5. 计算后的结果存储到ACC
6. 指令执行后，PC的地址+2，指向下一条要执行的指令

##### LOD #3 和 ADD W 在具体实现的时候有什么不同

- Decoder将指令解析后，发出的指示不一样。LOD #3时，仅需指示将值3传至ALU；ADD W时，需要先指示ACC把值传至ALU，然后再从内存中调取地址为W的值，传至ALU。

##### 从二进制的角度看执行

##### 1）指令“LOD #7”的二进制形式

- 00010100 00000111
- 第一部分，说明指示是LOD #n的格式
- 第二部分，说明加的数是7

##### 2）解释RAM的地址

- 指令地址二进制第一位为0，相邻指令的二进制地址相差2
- 内存地址二进制第一位为1，相邻存储地址相差1

##### 3）该机器CPU是几位的？（按累加器的位数）

- 8位

##### 4）写出该程序对应的 C语言表达。

	int_8 w = 3;
	int_8 x = 7;
	int_8 y = 7+w;

- - - 

<h4 id = "6"> Program 2:  Count down loop（简单循环）<h4>

##### 根据表格把指令填进模拟器

![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/machine%20code/program2/p2-1.png)

##### 程序功能

- 循环

##### 对应的c语言程序

	int_8 x = 3;
	while (1)
	{
		x --;
		if (x == 0) break ;
	}
	
##### 修改程序，用机器语言实现 10+9+8+..1 ，输出结果存放于内存 Y

##### C语言计算过程

	int_8 x = 10, y = 0;
	while (1)
	{
		y = y+x;
		x --;
		if (x == 0) break ;
	}
##### 机器语言的计算过程

- ![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/machine%20code/program2/p2-2.png)
- ![](https://github.com/zhangzhanbang/homework/raw/gh-pages/images/machine%20code/program2/p2-3.png)
- 由于框过于窄，地址16的指令为HLT

##### 高级语言与机器语言的区别与联系

- 高级语言，脱离计算机硬件，接近算法语言，易学、易掌握，程序可读性好，可维护性强，可靠性高。
- 机器语言，能实现对硬件的直接控制，指令与计算机执行的动作一一对应。
- 由于机器语言是是计算机唯一能接受和执行的语言，因此，高级语言必须通过编译器转化为机器语言才能在机器上运行。
