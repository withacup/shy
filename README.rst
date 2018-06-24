###一轮：
* Implement hashmap

* https://leetcode.com/problems/reverse-string/description/

* https://leetcode.com/problems/kth-largest-element-in-an-array/description/

* https://leetcode.com/problems/string-to-integer-atoi/description/

* Second minimum number in array

* https://leetcode.com/problems/shortest-word-distance/description/

* https://leetcode.com/problems/linked-list-cycle/description/

* https://leetcode.com/problems/shortest-word-distance-iii/description/

* given a sorted array, rotated at a pivot, find the maximum element

https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/

* what is encapsulation(封装)

* https://leetcode.com/problems/first-unique-character-in-a-string/description/
* https://leetcode.com/problems/minimum-path-sum/description/

* 大部分时间在问general behavior question。 比如要是组里有人不工作怎么办， 工作如果没法在deadline之前完成怎么办。tech question：1. 给了两个表格关于资金流动的，问怎么把所有的情况改成最少的交易次数。2. 问怎么找到一个Manager 管理的下面所有层的employees。

* 给学生名字和成绩，求最高平均分。好久没有面试，生疏了许多，最后貌似是 maintain 了两个 HashMap 做出来的……
找第二个最小的数字 我直接问面试官O(N) 扫两遍做行吗 面试官说可以 然后记得最开始问清楚可不可以有duplicate 规定不一样 我的是允许有 比如 -3 -3 2 返回的是-3

* Find and sort Continuous path,
e.g.[ [4,5], [9,4], [11,9], [5, 1] ] -> [ [11,9], [9, 4], [4,5], [5, 1] ]
这题之前没⻅过，我⽤hashmap做的，原题[11,9]⽤的是java⾥⾯的pair存
的，edge case有点多，花了点时间

###二轮：
* https://leetcode.com/problems/third-maximum-number/description/
* https://leetcode.com/problems/climbing-stairs/description/
* what's the difference between java and python?

* 后边问了简单的转置，矩阵相乘这种基础题，又问了reverse string。

* 前两道给了经典题目，一个跨三步的爬楼梯问题，一个求 10^n 的题，飞快做完之后只用了半个小时，然后给我加了一道让实现 HashMap ……也算经典题目了，面经里见过，但并没有去了解，磕磕绊绊一边沟通一边写，到最后也没做出来，其实就是不了解 Hash 的概念。做完一度以为挂了，结果今天给了回复，下一轮 bluejeans。

* 遇到的challenge呀，或者你做过的最interesting的东西是啥呀

###Onsite:
implement hashmap
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
https://leetcode.com/problems/trapping-rain-water/description/

https://leetcode.com/problems/subarray-sum-equals-k/description/
Find the shortest subarray in a list of integers which has a sum over the target value。这道题目一开始那个女生给出来是all positive的，然后那个vp上来就改成了我们也要考虑negative。
第二题是把subarray改成subset，然后要求正好等于target number。


一共五轮，每轮两个人。

1） 很多基本数据结构问题, 包括hashmap内部是如何实现O(1) access, 如果有collision,内部如何处理。
      给一串单词，返回其中所有unique单词，不能用到Set. . From 1point 3acres bbs
      解释什么是dead lock, 如何防止或者减少deadlock. 解释right join 和 left join有啥区别。
      设计一个order management system, 怎么吧order提交到交易所，怎么处理交易所根据这个order返回的数据, 问的很笼统，不知到对方想问什么。.本文原创自1point3acres论坛

.留学论坛-一亩-三分地
2)  Longest non repeating char. 
     Top K most frequent elements. 都是LC原题。
     问你project中用到过哪些open source framework, 详细介绍其中一个framework 的用途以及它的优缺点。
. 一亩-三分-地，独家发布


3） 有一个class, its constructor takes in a list of integers。然后要求实现constructor和一个函数：给两个数A,B，return the number of all elements in the list of integers between (A,B), 但要求O(1)时间复杂度。可以利用constructor做任何preprocessing, proprocessing没有复杂度限制。
      设计一个trading blotter系统，不断有新的trade进来怎么处理，有多个client同时打开同一个trade进行编辑，怎么处理，后台，前台，数据库怎么设计，等等。比较开放。

4）实现一个函数：给两串字母。怎么通过 stack pop或者push来吧第一串字母转化成第二串。比如： ABC, CBA 就是 push A, push B, push C, pop pop pop. 若无法转化返回exception。
     问为啥要离开目前公司来高盛，连续追问为啥是高盛，为啥是这个部门，为啥要离开现在岗位。
. more info on 1point3acres
5）一道BST的简单题，涉及到BFS, 具体记不清了。 来源一亩.三分地论坛. 
     LRU Cache.. 围观我们@1point 3 acres
     设计tiny url.怎么处理恶意访问, 比如给个黄色网站，比如invalid url. 怎么实现 rate limiter 来控制machine generated request。

判断二叉树是不是BST. Waral 博客有更多文章,
链表找环
一个n*n的表格中共有几个正方形。
还有一题不记得了，反正也非常简单。。
statistics:
Alice和Bob一起玩扔硬币游戏，任意一人扔出head则游戏结束，扔出head的人赢。Alice先扔，求两人胜率。
Trouble shooting和design：
一个网站，可以返回用户查询的data。这个网站原来工作正常，现在突然变得非常慢，说出所有可能的原因（具体记不得了，大意）。
设计一个文件系统（没搞懂面试官想问什么，反正他是这么说的。。。）

###奇葩：
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=418101&highlight=%B8%DF%CA%A2
