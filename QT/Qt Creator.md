# Qt Creator

[VS2017上面安装QT](https://www.jianshu.com/p/a81350d630dd)

2.1 打开Qt下载页面：[https://download.qt.io/](https://download.qt.io/)  
2.2 进入路径：/official\_releases/qt/5.9/5.9.1/，下载文件 qt-opensource-windows-x86-5.9.1.exe  
然后安装,Qt5.9.1不需要全选，不然需要13G的空间，安装时间也太长，就选下面两项  
![](/assets/importQT-Install-1.png)

安装好之后

1. 打开Visual Studio 2017，点击菜单栏中的“工具”，找到“扩展和更新”：
2. 在扩展和更新中，点击左侧目录进入Visual Studio Marketplace，搜索关键词Qt，第一个结果就是Qt Visual Studio Tools，安装：
3. 安装完成后，菜单栏中会出现新的一项：Qt VS Tools，点击进入Qt Options，点击“Add”，在path一栏中设置Qt 5.9.1的安装路径，如果路径不正确，会红字提示你没有找到某个特定的文件。
4. 以上配置工作完成后，新建项目，在Visual C++类别中选择Qt，然后选择Qt GUI Application，按照默认配置，即可生成项目文件。
5. 使用VS开发Qt项目，比起Qt Creator，有一个不太方便的地方就是对于ui文件的编辑。在项目文件目录中找到.ui后缀的文件，双击打开，会发现它会用另一个软件：Qt Designer打开.ui文件，有一点影响开发效率，不过总体来说还算可以接受。
6. 完成自己的项目代码后，我们选择生成解决方案，但是会报错，原因是SDK的配置不合适。在VS菜单栏中找到“项目”，点击“重定解决方案目标”，选择Windows10 的SDK版本，再次编译，成功



