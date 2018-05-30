# COM连接点

[COM连接点 - 最简单的例子](https://blog.csdn.net/zj510/article/details/39056097)

```cpp
 AtlAdvise(spCar, sinkptr, __uuidof(_IMyCarEvents), &cookies);
 sinkptr指向了一个CComObject<CSink>
 CComObject<CSink>* sinkptr = nullptr;  
 CComObject<CSink>::CreateInstance(&sinkptr);
```

换句话说，一旦将sink对象成功挂载到了COM对象，那么sink对象的生命周期就由对应的COM\(spCar\)对象来管理。

一旦挂载成功，sink对象就托管给对应的COM对象了，如果对应的COM对象析构了，那么所有它管理的sink对象也就释放了。

```
CLR是什么？
```

# COM Interop\(互操作\)

COM\(Component Object Model. 组件对象模型\)是微软之前推荐的一种开发技术，由于微软过去十多年里开发了大量的COM组件，

然而不可能再使用.Net技术重写这些COM组件实现的功能，所以为了解决在.Net中的托管代码能够调用COM组件中问题，.NET平台下提供了COM Interop, 即[COM互操作技术](http://www.cnblogs.com/zhili/archive/2013/01/14/NetInterop.html)，COM interop不仅支持在托管代码中使用COM组件，而且支持向COM组件中使用.NET程序集。

1.在.NET中使用COM组件

在.NET中使用COM对象，主要有三种方法：

1. 使用TlbImpl工具为COM组件创建一个互操作程序集来绑定早期的COM对象，这样就可以在程序中添加互操作程序集来调用COM对象
2. 通过反射来后期绑定COM对象
3. 通过P/Invoke创建COM对象或使用C++ Interop为COM对象编写包装类

但是我们经常使用的都是方法一，下面介绍下使用方法一在.NET 中使用COM对象的步骤：

1. 找到要使用的COM 组件并注册它。
   使用 regsvr32.exe 注册或注销 COM DLL。                 
2. 在项目中添加对 COM 组件或类型库的引用。                 

**添加引用时，Visual Studio 会用到Tlbimp.exe（类型库导入程序），Tlbimp.exe程序将生成一个 .NET Framework 互操作程序集。该程序集又称为运行时可调用包装 \(RCW\)，其中包含了包装COM组件中的类和接口。Visual Studio 将生成组件的引用添加至项目。**

      3. 创建RCW中类的实例，这样就可以使用托管对象一样来使用COM对象。

下面通过一个图更好地说明在.NET中使用COM组件的过程：

![](/assets/DotNetCallCOMWithCOM-interop.png)

**在COM中使用.NET程序集**

 　　.NET 公共语言运行时通过COM可调用包装（COM Callable Wrapper,即CCW）来完成与COM类型库的交互。CCW可以使COM客户端认为是在与普通的COM类型交互，同时使.NET组件认为它正在与托管应用程序交互。在这里CCW是非托管COM客户端与托管对象之间的一个代理。 CCW既可以维护托管对象的生命周期，也负责数据类型在COM和.NET之间的相互转换。实现在COM使用.NET 类型的基本步骤如：

1. 在C\#项目中添加互操作特性

  可以修改C\#项目属性使程序集对COM可见。右键解决方案选择属性，在“应用程序标签”中选择“程序集信息”按钮，在弹出的对话框中选择 “使程序集COM可见” 选项，如下图所示：

![](/assets/COMCallDotNet1.png)

2. 生成COM类型库并对它进行注册以供COM客户端使用

在“生成”标签中，选中 “为COM互操作注册”选项，如下图：

![](/assets/ComCallDotNet2.png)

勾选“为COM互操作注册”选项后，Visual Studio会调用类型库导出工具\(Tlbexp.exe\)为.NET程序集生成COM类型库再使用程序集注册工具\(Regasm.exe\)来完成对.NET程序集和生成的COM类型库进行注册，这样COM客户端可以使用CCW服务来对.NET对象进行调用了。

**总结**

　　介绍到这里，本专题的内容就结束，本专题主要对.NET 提供的互操作的技术做了一个总的概括，在后面的专题中将会对具体的技术进行详细的介绍和给出一些简单的使用例子。



