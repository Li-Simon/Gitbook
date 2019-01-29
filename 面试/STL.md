# 标准模板库

STL这节包含两部分，一个是数据结构，一个是算法。对于这些数据结构，一方面要知道有哪些数据结构，然后要知道每一种数据结构的特征与功能，能实现哪些操作，然后是我们要知道每种数据结构使用的场景。然后要知道这些数据结构实现的原理是什么？比如红黑树这些。最终就是知道原理以后，我们能基于特定任务而创建自己的数据结构。  
algorithms，要知道有哪些算法，这些算法的操作对象是什么\(迭代器\)？哪些数据结构。然后就是熟悉常用的一些算法。  
Boost库包含150多个库，其中就有线性代数库uBLAS，Boost是STL的高阶版，当前自己用不到，因此，了解了STL就足够了。如果要用线性代数库，则Eigen可能是一个好的选择。遇到问题，需要开发库，原则来说先看已有的库，基本上已有的库就呢个满足自己的需求了。  
参考这篇文章 [C++ STL 一般总结](https://www.cnblogs.com/biyeymyhjob/archive/2012/07/22/2603525.html)  
STL中体现了泛型程序设计的思想，泛型是一种软件的复用技术。

### STL的六大组件：
##### 容器（Container）
是一种数据结构，如list,vector,deques,以模板的方法提供，为了访问容器中的数据，可以使用由容器类输出的迭代器。  
顺序容器：vector,lsit,deque,string.  
关联容器：set,multiset, map, mulmap,hash\_set,hash\_map,hash\_multiset,hash\_multimap  
杂项： stack,queue,valarray,bitset
##### 迭代器\(Iterator\)
提供了访问容器中对象的方法，例如，可以使用一堆迭代器指定list或vector中的一定范围的对象。迭代器如同一个指针。事实上，C++指针也是一种迭代器。但是迭代器也可以是那些定义了operator\*\(\)以及其它类似于指针的操作符地方的类对象。
##### 算法\(algorithm\)
是用来操作容器中数据的模板函数。列例如，STL中的sort\(\)来对一个vector中的数据进行排序。用find\(\)来搜索一个list中的对象，函数本身与他们操作的数据的结构和类型无关，因此他们可以在从简单数组到高级复杂容器的任何数据结构上使用。
##### 仿函数\(Function object\)
仿函数\(functor\)又称为函数对象\(function object\)，其实就是重载了\(\)操作符的struct，没有什么特别的地方。
##### 迭代适配器\(adaptor\)
##### 空间配置器\(allocator\)
其中主要工作包括1.对象的创建与销毁，2.内存的获取与释放  
[STL底层数据结构实现](http://www.cnblogs.com/hustlijian/p/3611424.html)  
[容器的基本特征](https://blog.csdn.net/weixin_41162823/article/details/79759081)  
![](/assets/Container_basic_properties.png)

顺序容器的基本特征  
![](/assets/sequence_containers_properties.png)

不同容器特有的特征  
![](/assets/container_unique_propetrties.png)

## data structure
1. array
2. vector
3. deque
4. list
5. stack
6. queue
7. set
8. map
9. pair 

###Set
set的特性是所有的元素都会根据键值自动排序，set的元素不像map那样同时拥有实值(value)和键值(key)，set元素的键值就是实值，实值就是键值。 Set不允许两个元素拥有相同的键值，不呢个通过迭代器修改set元素的值。  
multiset和set的唯一区别在于multiset允许键值重复。  
##algorithms





