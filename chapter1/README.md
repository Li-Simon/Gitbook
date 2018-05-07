# 第一章：怎么安装使用GitBook

怎么利用gitbook生成自己的书，可以参考如下链接
https://www.jianshu.com/p/cf4989c20bd8

在安装好Node.js与gitbook之后，我们可以利用gitbook的GUI创建一本书，写入一些章节，然后保存，然后在cmd到该书summary.md所在的路径，然后再利用gitbook init进行初始化，然后再利用gitbook serve在浏览器上对书内容进行访问。
当然，个gitbook serve这一步会出错，会出现fontsettings.js找不到的情况，我们需要修改C:\Users\pili\.gitbook\versions\3.2.3\lib\output\website\copyPluginAssets.js，设置confirm: false，再重启个gitbook serve就可以了。
详见https://github.com/GitbookIO/gitbook/issues/1309
然后就可以在 http://localhost:4000 访问书籍了
![](/assets/FirstChapter1.PNG)

