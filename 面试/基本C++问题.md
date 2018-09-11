# 基本C++问题

### sizeof

定义一个空的类型，里面没有任何成员变量和成员函数，但是对该类型求sizeof，得到的结果是多少？  
答案：1；  
不是0的原因是，当我们声明该类型的实例时，它必须在内存中有一定的空间，否则无法使用这些实例，至少占多少内存，由编译器决定，在VS中，每个空类型的实例占1字节的空间。  
面试官：如果在该类型里面添加一个构造函数和析构函数，再对该类型求sizeof，得到的结果又是多少？  
应聘者：1。因为调用构造函数与析构函数只需要知道函数的地址即可，而这些函数的地址只与类型相关，与类型的实例无关，编译器也不会因为这两个函数而在实例中添加额外的信息。  
面试官：那如果把析构函数标记为虚函数呢？  
应聘者：编译器一旦发现一个类型中有虚函数，就会为该类型生成虚函数表，并在该类型的每一个实例中添加一个指向该虚函数表的指针，在32位的机器上，一个指针占4字节，因此求sizeof是4,不是4+1,因为只是指向虚函数表的指针的大小，在64位机器上，一个指针占8字节，因此求sizeof是8.

#### 数组与指针的sizeof

sizeof对数组，得到整个数组所占空间的大小。  
sizeof对指针，得到指针本身所占空间的大小。  
数组的名字就是一个指针，该指针指向数组的第一个元素，我们可以用一个指针来访问数组。也就是数组名加元素下标来访问数组元素或者获取数组元素的值。

```cpp
int data1[] = {1,4,7,9,6};
cout<<sizeof(data1)<<endl;
cout<<"1st of data1:"<<*data1<<endl;
cout<<"2st of data1:"<<*(data1 + 1)<<endl;
cout<<"1st of data1:"<<*(data1+3)<<endl;

20
1st of data1:1
2st of data1:4
1st of data1:9
```

#### class与struct区别

C++中Class成员变量或者成员函数默认private,而struct成员变量默认为public.  
C\#中，class与struct的成员变量与成员函数都默认是private.

```cpp
#include <iostream>
#include <array>
int main ()
{
    std::array<int,5> myints;
    std::cout << "size of myints:" << myints.size() << std::endl;
    std::cout << "sizeof(myints):" << sizeof(myints) << std::endl;
    return 0;
}
size of myints: 5
sizeof(myints): 20
```

#### String 类

[string](http://rsljdkt.iteye.com/blog/774188)的构造、拷贝构造、析构、赋值、输出、比较、字符串加、长度、子串

## 数据结构

数据结构一直是技术面试的重点，大多数面试题都是围绕数组，字符串，链表，树，栈以及队列这几种常用的数据结构展开的，因此每一个面试者毒药熟练掌握着集中数据结构。  
数组和字符串是两种最基本的数据结构，他们用连续内存分别储存数据和字符。链表和树是面试中出现频率最高的数据结构，由于操作链表和树需要大量的指针，应聘者在解决相关问题的时候一定要留意代码的鲁棒性，否则容易出现程序崩溃的问题。栈是一个与递归密切相关的数据结构，同样队列也与广度优先遍历算法密切相关，深入理解这两种数据结构能帮助我们解决很多算法问题。

### 数组

它占用一块连续的内存空间并按照顺序存储数据，创建数据时，我们需要首先指定数组的容量大小，然后根据大小分配内存。即使我们只在数组中存储一个数字，也需要为所有的数据预先分配内存，因此数组的空间效率不是很好，经常会有空闲的区域没有得到充分利用。  
数组中的内存是连续的，因此我们可以根据下标在O\(1\)时间读/写任何元素，因此它的时间效率是很高的。我们可以根据数组时间效率高的优点来实现简单的哈希表，把数组的下标设为哈希表的键值（key）,数组中的数据设为哈希表的value。这样就可以在O\(1\)时间内实现查找，从而快速，高效地解决很多问题。

### Vector

针对数组空间效率不高的问题，人们有设计实现了多种动态数组，比如STL中的vector,为了避免浪费，我们首先为数组开辟较小的空间，然后往数组中添加数据，当数据的数目超过数字的容量时，我们再重新分配一个更大的空间（STL中vector每次扩容时，新的容量都是前一次的两倍），把之前的数据复制到新的数组中，再把之前的内存释放，这样就减小内存的浪费。每次扩容都需要大量的额外操作，因此尽量减小改变数组容量大小的次数。  
简单设计Vector：一开始，新建一个大小为N的数组（弄成数组是保证内存是连续的），当vector中的元素内存超出开始的数组内存大小时，就新建一个大小为2N的数值，把原来的数组copy到新的数组，再释放原来的内存。用这种节奏来创建更大的数组来容纳更多的vector。

```cpp
void CList::ReplaceEmpty(char str[], int length)
{
    if(str == NULL || length <=0)
        return;
    int count = 0;
    int num = 0;
    while(str[num] != '\0')
    {
        if(str[num] == ' ')
            count++;
        num++;
    }
    int newStringLength = num + 2*count;
    int newNum = newStringLength;
    if(newStringLength >= length)
        return;
    for(int n = num; n >= 0; n--)
    {
        if(str[n] == ' ')
        {
            str[newNum--] = '0';
            str[newNum--] = '2';
            str[newNum--] = '%';
        }
        else
            str[newNum--] = str[n];
    }
}
```

### 二叉树：

#### 树的遍历

1. 前序遍历：先访问根结点，再访问左子结点，最后访问右子结点。  
2. 中序遍历：先访问左子结点，再访问根结点，最后访问右子结点。  
3. 后序遍历：先访问左子结点，再访问右子结点，再访问根结点。  
   前中后表示访问根结点的时间。  
   ![](/assets/Tree_ergodic.png)

根据前序，中序来重建树：

![](/assets/preOrder_inOrder_1.png)

前序中，第一个点就是根结点，根据根结点的值，在中序中找到根结点的值，则根结点之前的是坐子树，根结点之后的是右子树。 根据中序排列中左子树的大小（长度）L，在前序排列中找到左子树（从1到L），因此对于左子树，又得到了前序和中序排列。对右子树也可以得到前序与中序排列。由此递归实现。  
![](/assets/preOrder_inOrder_2.png)

```cpp
BinaryTreeNode* CTree::ConstructBinaryTree(int* preorderS,int* preorderEnd, int* inorderS, int* inorderEnd)
{
    int rootValue = preorderS[0];
    int* rootNode = inorderS;

    while(rootNode <= inorderEnd && *rootNode != rootValue) //find root in inorder
    {
        ++rootNode;
    }
    int LTLen = rootNode - inorderS;
    BinaryTreeNode* RootTree = new BinaryTreeNode();
    RootTree->m_nValue = rootValue;
    if(LTLen >0)
    {
        RootTree->m_pLeft = ConstructBinaryTree(preorderS+1, preorderS+LTLen, inorderS, rootNode-1);
    }
    if(LTLen < preorderEnd - preorderS)
    {
        RootTree->m_pRight = ConstructBinaryTree(preorderS+LTLen + 1, preorderEnd, rootNode+1, inorderEnd);
    }
    return RootTree;
}

void CTree::PreOrderPrint(BinaryTreeNode* BTree)
{
    if(BTree != NULL)//print root first
    {
        m_preorder.push_back(BTree->m_nValue);
        cout<<BTree->m_nValue<<endl;
    }
    if(BTree->m_pLeft != NULL)
    {
        PreOrderPrint(BTree->m_pLeft);
    }
    if(BTree->m_pRight != NULL)
    {
        PreOrderPrint(BTree->m_pRight);
    }    
}

void CTree::InOrderPrint(BinaryTreeNode* BTree)
{
    if(BTree->m_pLeft != NULL)
    {
        InOrderPrint(BTree->m_pLeft);
    }
    if(BTree != NULL)//print root second
    {
        m_preorder.push_back(BTree->m_nValue);
        cout<<BTree->m_nValue<<endl;
    }
    if(BTree->m_pRight != NULL)
    {
        InOrderPrint(BTree->m_pRight);
    }    
}

void CTree::PostOrderPrint(BinaryTreeNode* BTree)
{
    if(BTree->m_pLeft != NULL)
    {
        PostOrderPrint(BTree->m_pLeft);
    }

    if(BTree->m_pRight != NULL)
    {
        PostOrderPrint(BTree->m_pRight);
    }    

    if(BTree != NULL)//print root last
    {
        m_postorder.push_back(BTree->m_nValue);
        cout<<BTree->m_nValue<<endl;
    }
}
```

### 栈与队列

栈：先进后出，压入push,弹出pop  
队列：后进先出，压入push,弹出pop  
用两个栈来实现队列。模板类的实现要在.h里面

```cpp
#pragma once
#include <stack>
using namespace std;

template <class T>
class CStackDeque
{
public:
	CStackDeque(void){};
	~CStackDeque(void){};
	void appendTail(const T& node);
	T deleteHead();

private:
	stack<T> m_stack1;
	stack<T> m_stack2;
};

template<class T>
void CStackDeque<T>::appendTail(const T& node)
{
	m_stack1.push(node);
}

template<class T>
T CStackDeque<T>::deleteHead()
{
	if(m_stack2.size() <= 0)
	{
		while(m_stack1.size() > 0)
		{
			T& node = m_stack1.top();
			m_stack1.pop();
			m_stack2.push(node);
		}
	}

	if(m_stack2.size() <= 0)
		throw new exception("queue is empty!");

	T node2 = m_stack2.top();
	m_stack2.pop();
	return node2;
}
```



