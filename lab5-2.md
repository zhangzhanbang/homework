---
  title : AI_SNAKE
---

### 字符游戏—智能蛇 实验报告

#### 实验名称：智能蛇

#### 张展邦 18342134

---

## 索引 ##

* [一、实验目的](#1)
* [二、实验环境](#2)
* [三、控制输入/输出设备](#3)
	* [1、VT 100终端标准](#4) 
	* [2、实现kbhit()——检测键盘输入](#5)
* [四、编写智能算法](#6)
	* [1、程序要求](#7) 
	* [2、程序框架](#8)
	* [3、函数设计](#9)
* [五、总结](#10)

----



<h3 id="1"> 一、实验目的 </h3>

1.  了解 算法 与 “智能” 的关系
2. 通过算法赋予蛇智能
3. 了解 Linux IO 设计的控制



<h3 id="2"> 二、实验环境 </h3>

1. Linux Ubuntu
2. 编辑环境Sublime，编译gcc
3. 镜像提供：刘聪老师



<h3 id="3"> 三、控制输入/输出设备 </h3>

<h4 id="4"> 1、VT 100终端标准 </h4>

VT100是一个终端类型定义,VT100控制码是用来在终端扩展显示的代码。

较为有用的控制码：

```c
printf("\033[2J"); //实现清屏
printf("\033[y;xH"); //设置光标位置
```

<h4 id="5"> 2、实现kbhit()——检测键盘输入</h4>

简单的，对游戏来说，玩家在不操作的时候，对应的游戏人物也会攻击、防御和移动，等待玩家操作的空隙有很多的游戏内容设置，这都需要函数kbhit()。

kbhit()函数用于检测是否有键盘输入（按下按键），在window下只需要调用库windows.h即可使用，老师给出了kbhit()在Linux下手动实现的版本，用法与window的几乎一致，嵌入程序即可。



<h3 id="6"> 四、编写智能算法 </h3>

<h4 id="7"> 1、程序要求 </h4>

1. 请修改初始化字符矩阵，或者通过文件读入地图。地图中有一些你设定的障碍物（墙）
2. 请实现如下算法决定蛇行走的方向
3. 思考：一个长度为5的障碍物能困死该自动跑的蛇吗？

**决定蛇行走的方向函数的伪代码**

```c
    // Hx,Hy: 头的位置
    // Fx,Fy：食物的位置
	function whereGoNext(Hx,Hy,Fx,Fy) {
	// 用数组movable[3]={“a”,”d”,”w”,”s”} 记录可走的方向
	// 用数组distance[3]={0,0,0,0} 记录离食物的距离
	// 分别计算蛇头周边四个位置到食物的距离。H头的位置，F食物位置
	//     例如：假设输入”a” 则distance[0] = |Fx – (Hx-1)| + |Fy – Hy|
	//           如果 Hx-1，Hy 位置不是Blank，则 distance[0] = 9999
	// 选择distance中存最小距离的下标p，注意最小距离不能是9999
	// 返回 movable[p]
	}
```

- re 1：地图设置：初始一个食物，障碍块6个，均随机生成。
- re 2：上述伪代码算法为贪心，往四个方向走，选与食物曼哈顿距离最小的方向。
- re 3：可以，若在边角处障碍物与墙壁形成只有一个开口的矩形（宽度为1），矩形内有食物，蛇进去就出不来了。

<h4 id="8"> 2、程序框架 </h4>

```c
输出字符矩阵
WHILE not 游戏结束 DO
	wait(time)
    ch＝whereGoNext(Hx,Hy,Fx,Fy)
    CASE ch DO
		‘A’:左前进一步，break 
		‘D’:右前进一步，break    
		‘W’:上前进一步，break    
		‘S’:下前进一步，break    
	END CASE
	输出字符矩阵
END WHILE
输出 Game Over!!! 
```

对比snake_eat.c可以发现，把输入的指令换成了预设的指令

<h4 id="9"> 3、函数设计 </h4>

策略：先生存再吃食物

问题1： 如何确保每走一步蛇仍生存？

> 容易发现，蛇头若一直追着自己的尾巴跑，蛇是不会被困住的。
>
> 考虑蛇是否生存的条件之一是蛇头与蛇尾之间是否有通路，可用dfs实现。
>
> 容易发现，蛇身一旦过长，以上条件失效的几率会很大。
>
> 条件之一失效后考虑条件之二：有无可能走进死胡同。
>
> 即便考虑以上，还会出现追着尾巴跑最容易出现的问题：循环跟着尾巴跑。
>
> 一种优化的方案：在每个状态下，在可行的最优行走方案中找与尾巴曼哈顿距离最远的。

问题2： 如何吃食物？

> 选择与食物曼哈顿距离最小的方向去走

问题3： 要是蛇头与食物没有可行通路怎么办？

> 跟着尾巴走，否则优先跟着食物走

问题4： 要是都没有可行通路到达食物和蛇尾怎么办？

> 在可行选项中，选择离蛇尾最远的走，拉开距离

问题5： emm，这个目光短浅啊，还是会挂的啊！

> 目前可写的就是，你设计一个估价函数，用A*算法（启发式搜索）去跑（图很小），选最优的方向跑。
>
> 再优一点，机器学习？

```c
/*
	备注：蛇尾设置为'T'
*/
int wrong(int x, int y) //判断是否不合法
{
	if (x <= 1 || y <= 1 || x >= 12 || y >= 12
	 || map[x][y] == BODY || map[x][y] == HEAD)
		return 1;
	return 0;
}

int dfs(int x, int y, int target_x, int target_y)//搜索，看能不能到达target
{
	vis[x][y] = 1;
	int i, ret = 0;
	REP(i, 1, 4)
	{
		int tx = x+dx[i], ty = y+dy[i];
		if (tx == target_x && ty == target_y) return 1;
		if (wrong(tx, ty) || vis[tx][ty]) continue ; //不合法
		ret |= dfs(tx, ty, target_x, target_y);
	}
	return ret;
}

int check_dfs(int x, int y, int target_x, int target_y)
{
	int i, j;
	REP(i, 1, N)
		REP(j, 1, N) vis[i][j] = 0;
    //清空vis数组，vis[i][j]表示这个点ij是否被访问过
	return dfs(x, y, target_x, target_y);
}

int to_tail(int x, int y)
{
	int ret = 0, i, j;
    //是否吃食物有所不同
	if (map[x][y] != FOOD) 
	{
		int x_tail1 = x_snake[len_snake];
		int y_tail1 = y_snake[len_snake];
		int x_tail2 = x_snake[len_snake-1];
		int y_tail2 = y_snake[len_snake-1];
		map[x_tail1][y_tail1] = BLANK;
		map[x_tail2][y_tail2] = TAIL; 
		ret = check_dfs(x, y, x_tail2, y_tail2);
		map[x_tail2][y_tail2] = BODY;
		map[x_tail1][y_tail1] = TAIL;
	}
	else
	{
		int x_tail = x_snake[len_snake];
		int y_tail = y_snake[len_snake];
		ret = check_dfs(x, y, x_tail, y_tail);
	}
	return ret;
}

char whereGoNext()
{
	int mx_dis = -1, dis_tail = -1, i;
	int x_towards, y_towards; 
	int x_head = x_snake[1], y_head = y_snake[1];
	int x_tail = x_snake[len_snake], y_tail = y_snake[len_snake];
	char step = '!';
	int ok_to_food = check_dfs(x_head, y_head, x_food, y_food);
	int ok_to_tail = 0;
	REP(i, 1, 4) //判断是否存在可行方案——到达蛇尾
	{
		int tx = x_snake[1]+dx[i];
		int ty = y_snake[1]+dy[i];
		if (wrong(tx, ty)) continue ;
		ok_to_tail |= to_tail(tx, ty);
	}
	if (ok_to_food) //优先走到食物
	{
		x_towards = x_food;
		y_towards = y_food;
	}
	else if (ok_to_tail) //否则跟着尾巴走
	{
		x_towards = x_tail;
		y_towards = y_tail;
	}
	else x_towards = y_towards = -1; //无法到达食物和尾巴
	REP(i, 1, 4)
	{
		int tx = x_snake[1]+dx[i];
		int ty = y_snake[1]+dy[i];
		if (wrong(tx, ty)) continue ; //越界
		if (ok_to_tail && !to_tail(tx, ty)) continue ; //在存在可行方案时，当前方案不可行
		if (x_towards != -1) //有目标走，食物或者尾巴
		{
			int t_dis = abs(tx-x_towards)+abs(ty-y_towards);
			int t_dis_tail = abs(tx-x_tail)+abs(ty-y_tail); 
			if (mx_dis == -1 || mx_dis > t_dis)
				mx_dis = t_dis, dis_tail = t_dis_tail, step = typ[i];
			else if (mx_dis == t_dis && dis_tail < t_dis_tail)
				mx_dis = t_dis, dis_tail = t_dis_tail, step = typ[i];
		}
		else // 往远离尾巴方向走
        {
			int t_dis_tail = abs(tx-x_tail)+abs(ty-y_tail); 
            if (dis_tail < t_dis_tail)
                dis_tail = t_dis_tail, step = typ[i];
        }
	}
	return step;
}
```



<h3 id="10"> 五、总结 </h3>

1、学习了Linux的IO，包括输出终端标准和检测键盘输入函数kbhit()。

2、智能算法的设计，算法的具体设计决定蛇的智能。项目一开始给出的贪心算法，简单的考虑了一点——尽量吃到食物，程序较为简单，自然存在蛇走不出来的情况。在遇到类似的具体问题的时候，情况一般不复杂，但是需要考虑的点很多。提出一个算法，实现，考虑不周的地方可以通过数据来显示出来，进而会提出更多的问题，发现更多的漏洞。真正的智能算法，应该是能够自我修复漏洞。 

