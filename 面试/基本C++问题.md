# 基本C++问题

#### 指针与引用的区别

指针是一个变量，该变量储存的是一个地址，指向内存中的一个内存单元；而引用只是原来变量的一个别名。

#### 数组名与指针的区别

数组名a可以当成数字首地址的指针,除如下两种情况，sizeof\(a\),&a.  
1.取sizeof得到不同结果；对数组取sizeof得到整个数组的长度；对指针取sizeof得到指针本身所占空间的大小。  
2.指针可以pointer++，数组名不可以。  
3.指针可以赋值再指向别人，数组名不可以。

### 实现String类的构造函数，析构函数和赋值函数

```cpp
#pragma once
class AString
{
public:
	AString(const char* str = NULL);
	AString(const AString &other);
	~AString(void);
	AString & operator=(const AString &other);
private:
	char *m_String;
};
```

```cpp
#include "StdAfx.h"
#include "AString.h"
#include <iostream>
using namespace std;

AString::~AString(void)
{
	cout<<"Destructing"<<endl;
	if(m_String != NULL)
	{
		delete [] m_String;
		m_String = NULL;
	}
}

AString::AString(const char* str)
{
	cout<<"Constructing"<<endl;
	if(str == NULL)
	{
		m_String = new char[1];
		*m_String = '\0';
	}
	else
	{
		m_String = new char[strlen(str)+1];
		strcpy(m_String, str);
	}
}

AString::AString(const AString &other)
{
	cout<<"Constructing copy"<<endl;
	m_String = new char[strlen(other.m_String)+1];
	strcpy(m_String, other.m_String);
}

AString & AString::operator=(const AString &other)
{
	cout<<"Operator = Function:"<<endl;
	if(this == &other)
	{
		return *this;
	}
	delete []m_String;
	m_String = new char[strlen(other.m_String)+1];
	strcpy(m_String, other.m_String);
	return *this;
}
```

```cpp
#include "StdAfx.h"
#include "AString.h"
#include <iostream>
using namespace std;

void main()
{
	cout<<"Step 1"<<endl;
	AString a("hello");
	cout<<"Step 2"<<endl;
	AString b("world");
	cout<<"Step 3"<<endl;
	AString c(a);
	cout<<"Step 4"<<endl;
	c = b;
	cout<<"Step 5"<<endl;
}
```

![](/assets/String_Result.png)

### 字符串指针赋值问题

如果指针没有分配空间，则会出现0xC0000005: Access violation writing location

```cpp
void main(int n)
{
    //char pStr[] = "abc";//right
    //char pStr[4] = "abc";//right
        //char pStr[3] = "abc";//wrong,need >=4
    char* pStr = "abc"; //wrong, 没有分配空间，
    char temp = 'b';
    pStr[0] = temp;
    printf("%s\n",pStr);
}
```
###析构函数能否写成虚函数
1. 基类的可以
2. 子类的不可以，会造成内存泄漏。


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
void main()
{
    CStackDeque<int> queue;
    queue.appendTail(1);
    int value = queue.deleteHead();
}
```

### 排序算法

核心是在数组中选择一个值，重新排列数组，使得该值左边的元素都小于该值，右边的元素都大于该值。分成两组后，再继续这种操作，以此递归下去，最终得到全排序。  
下面都是对数组操作，因此要注意下标问题。

```cpp
int CSort::Partition(int data[], int length, int start, int end)
{
       if(start >= end)
             return start;
       if(data == NULL || start <0 || end > length || length <= 0)
             throw new exception("Invidate parameters!");
       int small = start;
       srand((unsigned)time(NULL));//random seed
       int randInt = rand()%(end - start);
       int value = data[start + randInt];
       cout<<"Value: "<<value<<endl;
       swap(data[start+randInt],data[end]);//all element start from start,
       for(int index = start; index < end; index++)
       {
             if(data[index] < value)
             {
                    swap(data[index], data[small]);
                    small++;
             }
       }
       swap(data[small], data[end]);
       return small;
}

void CSort::QucikSort(int data[], int length, int start, int end)
{
    if(end <= start)
        return;

    int index = Partition(data,length,start,end);
    if(index>start)
    {
        QucikSort(data,length,start, index-1);
    }
    if(index < end)
    {
        QucikSort(data, length, index + 1 ,end);
    }
}
```

### 与，或，异或

负数的二进制表示  
举例：  
-5 在计算机中表达为：11111111 11111111 11111111 11111011。转换为十六进制：0xFFFFFFFB。  
-1在计算机中如何表示：  
先取1的原码：00000000 00000000 00000000 00000001  
得反码： 11111111 11111111 11111111 11111110  
得补码： 11111111 11111111 11111111 11111111  
可见，－1在计算机里用二进制表达就是全1。16进制为：0xFFFFFFFF。  
注：十六进制前缀是0x。  
![](/assets/And_or_xor.png)

#### 计算二进制中1的个数

```cpp
int CRecursion::CountNumber1(int n)
{
    int count = 0;
    while(n)
    {
        if(n&1)
            count++;
        n = n>>1;
    }
    return count;
}
```

### 链表

### 在O\(1\)时间内删除一个节点

方法：通过用节点下一个节点来覆盖这个节点，因此不需要查询将被删除节点前面的所有节点。

### 问题：

如果你传入一个指针，实际上你传入的就是一个物理地址，对于链表而言，你不能在链表头接入一个元素，因为最终出来的时候，指针（的地址）一直没变，因此技术你在函数里面对指针进行赋值，但是出了函数，有没有效果了。

一种会出错的删除做法：

```cpp
void CList::DeleteNode(ListNode* pListHead, ListNode* pToBeDeleted)
{
    if(!pListHead || !pToBeDeleted)
        return;

    if(pToBeDeleted->m_pNext == NULL)
    {
        pToBeDeleted = NULL;
    }
    if(pToBeDeleted->m_pNext != NULL)
    {

        /*pToBeDeleted->m_value = pToBeDeleted->m_pNext->m_value;/出错的做法
        pToBeDeleted->m_pNext = pToBeDeleted->m_pNext->m_pNext;
        delete pToBeDeleted->m_pNext;*///因为删除了pToBeDeleted->m_pNext，因此索引到此，访问了空地址，程序会崩溃。正确的做法如下

        ListNode* pNext = pToBeDeleted->m_pNext;//将要被删除的节点，在删除之前，复制它的值
        pToBeDeleted->m_value = pToBeDeleted->m_pNext->m_value;
        pToBeDeleted->m_pNext = pToBeDeleted->m_pNext->m_pNext;
        delete pNext;
    }
}
```

#### 对数组中奇偶数据分类排序

```
void CCArray::ReorderOddEven(int* data, int length, bool (*Func)(int))
{
    if(data==NULL || length <= 0)
        return;
    int* pBegin = data;
    int* pEnd = data + length - 1;

    while(pBegin < pEnd)
    {
        while(!Func(*pBegin))
        {
            pBegin++;
        }

        while(Func(*pEnd))
        {
            pEnd--;
        }

        int temp = *pEnd;
        *pEnd = *pBegin;
        *pBegin = temp;
    }
}
void main()
{
    const int length = 6;
    int data[] = {4,1,5,3,6,7};
    CCArray* test_arr = new CCArray();
    test_arr->ReorderOddEven(data, length, IsEven);//函数指针的调用
    for(int i = 0; i < length; i++)
    {
        cout<<data[i]<<endl;
    }
}
bool IsEven(int value)
{
    return (value&1) == 0;
}
```

### 为啥要用C++智能指针

1. 内存泄漏：是指操作系统将空间分配给你，但是那个空间被你申请后并没有被使用，并且没有相应的释放语句。也就是该空间不再被任何指针或引用所引用，成为一个幽灵空间，操作系统以为你在控制它，但其实你并没有控制它。  
2. 重复释放： 程序通过free或delete语句释放已经不属于该程序的空间。这是很危险的，因为第二次free的空间已经被别的程序所使用。所以C++中把这种错误当成了致命错误。  
   栈上的空间是由系统分配的。堆上的空间是由用户自己分配的。通过new创建，free释放。  

#### C++什么时候该使用new?该注意什么来防止内存泄漏？

#### 打印1到最大的n位数，比如n=2,怎打印1到99.

```cpp
void PrintToMaxofNDigits(int n);//输入要打印的位数
void PrintNumber(char* number);//打印字符串
bool Increment(char* number);//每次增加1看是否越界
void CRecursion::PrintToMaxofNDigits(int n)
{
    if(n <= 0)
        return;

    char *number = new char[n+1];
    memset(number,'0',n);
    number[n] = '\0';
    while(!Increment(number))
    {
        PrintNumber(number);
    }
    delete []number;
}

bool CRecursion::Increment(char* number)
{
    bool isOverFlow = false;
    int numLength = strlen(number);
    int nTakeOver = 0;
    for(int i = numLength - 1; i >=0; i--)
    {
        int nSum = number[i] -'0' + nTakeOver;
        if(i == numLength -1)
            nSum++;

        if(nSum >= 10)
        {
            if(i == 0)
            {
                isOverFlow = true;
            }
            else
            {
                number[i] = nSum - 10 + '0';
                nTakeOver = 1;
            }
        }
        else
        {
            number[i] = nSum + '0';
            break;
        }
    }
    return isOverFlow;
}

void CRecursion::PrintNumber(char* number)
{
    bool isBeginning0 = true;
    int nLength = strlen(number);
    for(int i = 0; i < nLength; ++i)
    {
        if(isBeginning0 && number[i] != '0')
            isBeginning0 = false;
        if(!isBeginning0)
        {
            printf("%c",number[i]);
        }
    }
    printf("\n");
}
```

printf\("%c",number\[i\]\);打印字符  
接下来是递归算法：  
通过递归，打印只针对于个位数，也就是index == length -1的位置。

```cpp
void CRecursion::PrintToMaxofNDigitsRecu(int n)
{
    if(n <= 0)
        return;

    char* number = new char[n+1];
    number[n] = '\0';
    for(int i =0; i < 10; i++)
    {
        number[0] = i+'0';
        PrintToMaxofNDigitsRecursively(number, n, 0);
    }
    delete[] number;
}

void CRecursion::PrintToMaxofNDigitsRecursively(char* number, int length, int index)
{
    if(index == length -1)
    {
        PrintNumber(number);
        return;
    }

    for(int i = 0; i < 10; i++)
    {
        number[index+1] = i + '0';
        PrintToMaxofNDigitsRecursively(number, length, index + 1);
    }
}
```

#### 输入两颗二叉树A和B，判断B是不是A的子结构。

通过递归实现。如果两个头节点相同，则比较两者的左右子树。如果不相同，则把A的左右子树当成树，看他们是否含有B。

```cpp
bool CTree::HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    bool result;
    if(pRoot2 == NULL)
        return true;
    if(pRoot1 == NULL)
        return false;

    if(pRoot1->m_nValue == pRoot2->m_nValue)
    {
        result = DoesTree1HaveTree1(pRoot1, pRoot2);
    }
    if(!result)
    {
        result = DoesTree1HaveTree1(pRoot1->m_pLeft, pRoot2);
    }
    if(!result)
    {
        result = DoesTree1HaveTree1(pRoot1->m_pRight, pRoot2);
    }
    return result;
}

bool CTree::DoesTree1HaveTree1(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    bool result;
    if(pRoot2 == NULL)
        return true;
    if(pRoot1 == NULL)
        return false;

    if(pRoot1->m_nValue != pRoot2->m_nValue)
    {
        return false;
    }

    return DoesTree1HaveTree1(pRoot1->m_pLeft, pRoot2->m_pLeft)&&DoesTree1HaveTree1(pRoot1->m_pRight, pRoot2->m_pRight);
}
```

#### 输入两个整数序列，第一个是栈的压入序列，第二个是不是栈的弹出序列

比如压入序列是1，2，3，4，5;则4，5，3，2，1是可能的弹出序列，而4，3，5，1，2不是弹出序列。

```cpp
bool CTree::IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    stack<int> stackData;
    const int* pNextPush = pPush;
    const int* pNextPop = pPop;
    int pushLength = 0;
    while(pushLength < nLength)
    {
        int topData = *pNextPop;
        while(*pNextPush != topData)
        {
            if(pNextPush == NULL)//no this element in the push list
                return false;
            stackData.push(*pNextPush);
            pNextPush++;
            pushLength++;
        }
        pNextPush++;
        pushLength++;
        pNextPop++;
    }
    while(!stackData.empty())
    {
        if(stackData.top() != *pNextPop)
        {
            return false;    
        }
        stackData.pop();
        pNextPop++;
    }
    return true;
}
```



