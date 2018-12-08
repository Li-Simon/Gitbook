\`\`\#最短路径Dijkstra算法  
需要回答一个问题，最小生成树算法与最短路径算法这些图算法之间的关联，也就是他们基于什么相同的原理？以及他们与最优化算法之间的关系是什么？图算法是否可以连续化？  
这些算法主要使用了松弛技术。  
也就是，对每个顶点$$v \in V$$，都设置一个属性d\[v\]，用来描述从源点到v的最短路径上权值的上界，称为最短路径估计，我们用$$\Theta(V)$$时间的过程来对最短路径估计和前驱初始化：  

INITIALIZE-SINGLE-SOURCE(G,s)
for each vertex $$v \in V[G]$$:
&emsp;do $$d[v] \gets \infty $$
&emsp;&emsp; $$\pi[v] \gets NIL$$    
$$d[s] \gets 0$$  
在松弛一条边(u,v)的过程中，要测试是否可以通过u，对迄今找到的v的最短路径进行松弛；如果可以改进的话，则更新d[v]与$$\pi[v]$$。一次松弛操作可以减小最短路径估计的值d[v]，并更新v的前驱域$$\pi[v]$$。下面的伪代码对边(u,v)进行了松弛操作。  
RELAX(u,v,w)
if $$d[v] > d[u]+ w(u,v)$$:
&emsp;then do $$d[v] \gets d[u] + w(u,v)$$
&emsp;&emsp; $$\pi[v] \gets u$$    



