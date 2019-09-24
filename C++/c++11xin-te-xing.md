### C++新关键词

#### auto

#### decltype

#### using

### 解决内存泄漏的问题

#### shared\_ptr

 普通指针到智能指针的转换

```cpp
int* iPtr = new int(42);
shared_ptr<int> p(iPtr);
```

智能指针到普通指针的转换

```cpp
int* pI = p.get();
```

#### unique\_ptr

#### weak\_ptr

#### C++任意参数模板

### 多线程开发



