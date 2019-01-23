#最短路径Dijkstra算法  
需要回答一个问题，最小生成树算法与最短路径算法这些图算法之间的关联，也就是他们基于什么相同的原理？以及他们与最优化算法之间的关系是什么？图算法是否可以连续化？  
首先定义从u到v之间的最短路径的权为：  
&emsp;&emsp; $$\delta(u,v) = \min(w(p):u\to v)$$，如果存在一条从u到v的路径。  
&emsp;&emsp; $$\delta(u,v) = \infty$$，否则。  
###松弛技术
这些算法主要使用了松弛技术[^1]。  
也就是，对每个顶点$$v \in V$$，都设置一个属性d\[v\]，用来描述从源点到v的最短路径上权值的上界，称为最短路径估计，我们用$$\Theta(V)$$时间的过程来对最短路径估计和前驱初始化：  
第一步是对最短路径估计的值d[v]以及v的前驱域$$\pi[v]$$进行初始化。    
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

基于松弛的算法。松弛是改变最短路径和前驱的唯一方式，这节的算法之间的区别在于对每条边进行松弛操作的次数不同，以及对边进行松弛操作的次序有所不同。在Dijkstra算法以及关于有向无回图路图的最短路径算法中，对每条边执行一次松弛操作。在Bellman-Ford算法中，对每条边执行多次松弛操作。  
###Bellman-Ford算法
Bellman-Ford算法能在一般的情况(带有负权边的情况下)，解决单源最短路径问题。  
BELLMAN--FORD(G,w,s)    
INITIALIZE-SINGLE-SOURCE(G,s)    
for $$i \gets i$$ to $$|V[G]|-1$$    
&emsp;do for each edge $$(u,v) \in E[G]$$    
&emsp;&emsp;do RELAX(u, v, w)     
for each $$edge(u,v)\in E[G]$$    
&emsp;do if $$d[v] > d[u] + w(u,v)$$    
&emsp;&emsp;then return FALSE    
return TRUE  
###Dijkstra算法   
DIJKSTRA(G,w,s)    
INITIALIZE-SINGLE-SOURCE(G,s)      
$$S\gets \emptyset$$    
$$Q\gets V[G]$$   
while $$Q\ne \emptyset$$      
&emsp;do $$u \gets EXTRACT-MIN[Q]$$       
&emsp;&emsp;$$S \gets S \bigcup u$$         
&emsp;&emsp;for each vertex$$v\in Adj[u]$$    
&emsp;&emsp;&emsp;do RELAX(u, v, w)      

[^1]: 《算法导论》单源最短路径  