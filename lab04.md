---
  title: Audio Coding
---

## Audio Coding

<center> ![](https://raw.githubusercontent.com/zhangzhanbang/homework/gh-pages/images/lab04/audio%20coding.jpg) </center >

- 计算机之所以能构造出一个近乎于真实的世界，源于它复制了人类的两大感觉：视觉与听觉，其对应的是图像与声音，但这项工作可不是那么容易。计算机让人们更容易享受到音乐，沉浸其中，又曾想过它是怎么通过各种转换，到了你的耳边，变成一个个美妙的音符呢？下面让我们一起来探讨吧！


### How to transfer

- 思考一下人是怎么听到声音的？我们能听到声音，是因为声音通过空气传到我们的耳朵，引起鼓膜的振动，进而把相关信号传到大脑，经过一系列信号转换，变成了我们所听到的声音。

![](https://raw.githubusercontent.com/zhangzhanbang/homework/gh-pages/images/lab04/hearing.jpg) 

- 声音是一种波动，声音波动会引起介质的振动——空气分子的有节奏的振动，使周围的空气产生疏密变化，形成疏密相间的纵波，这就产生了声波。在物理上，声音是一种机械波，拥有波动传播的性质，例如频率和波长。因此，我们可以通过收集相关物理信息，来复制声音。

![](https://raw.githubusercontent.com/zhangzhanbang/homework/gh-pages/images/lab04/Sound%20wave.jpg)

- 采用的方法叫做采样：定期对声音信号进行数字化处理，让连续的时间信号，变成离散的数字信号。 </br>

- 采样率则是指每秒钟收集了多少个样本，单位HZ。采样频率越高所能描述的声波频率就越高。根据 Nyquist采样定律：采样率大于或等于连续信号最高频率分量的2倍时，采样信号可以用来完美重构原始连续信号。
 ![](https://raw.githubusercontent.com/zhangzhanbang/homework/gh-pages/images/lab04/collect.gif)
- 信息处理的过程大致如下：

> 1.声电转换 </br>
> 2.抽样（模数转换） </br>
> 3.量化（将数字信号用适当的数值表示） </br>
> 4.编码（数据压缩） </br>
> 5.传输（网络或者其他方式） </br>
> 6.解码（数据还原）  </br>
> 7.反抽样（数模转换） </br>
> 8.电声转换

### Sound format

- 既然已经了解声音转换原理，下面就介绍一下常见的音频格式。

1. WAV格式。WAV是微软公司开发的一种声音文件格式，也叫波形声音文件，是最早的数字音频格式，被Windows平台及其应用程序广泛支持，压缩率低。

![](https://raw.githubusercontent.com/zhangzhanbang/homework/gh-pages/images/lab04/wav.png ) 

2. MP3格式。MP3全称是MPEG-1 Audio Layer 3，它在1992年合并至MPEG规范中。MP3能够以高音质、低采样率对数字音频文件进行压缩。应用最普遍。

 ![](https://raw.githubusercontent.com/zhangzhanbang/homework/gh-pages/images/lab04/MP3.jpg) 

3. APE格式。APE是一种无损压缩音频格式,在音质不降低的前提下，大小压缩到传统无损格式 WAV 文件的一半

 ![](https://raw.githubusercontent.com/zhangzhanbang/homework/gh-pages/images/lab04/APE.jpg) 

4. FLAC格式。FLAC即是Free Lossless Audio Codec的缩写，是一套著名的自由音频无损压缩编码，其特点是无损压缩。

![](https://raw.githubusercontent.com/zhangzhanbang/homework/gh-pages/images/lab04/flac.jpg) 

5. AAC格式。AAC实际上是高级音频编码的缩写。AAC是由Fraunhofer IIS-A、杜比和AT&T共同开发的一种音频格式，它是MPEG-2规范的一部分。AAC所采用的运算法则与MP3的运算法则有所不同，AAC通过结合其他的功能 来提高编码效率。AAC的音频算法在压缩能力上远远超过了以前的一些压缩算法（比如MP3等）。它还同时支持多达48个音轨、15个低频音轨、更多种采样率和比特率、多种语言的兼容能力、更高的解码效率。总之，AAC可以在比MP3文件缩小30%的前提下提供更好的音质。

  ![](https://raw.githubusercontent.com/zhangzhanbang/homework/gh-pages/images/lab04/aac.png) 
