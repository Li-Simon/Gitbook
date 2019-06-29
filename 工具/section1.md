# 第一节 Gitbook的安装与使用
Gitbook是Github旗下的产品，它提供书籍的编写与管理的功能，一个核心特征就是，它管理书也像管理代码一样，可以对数据进行fork,建立新的branch,使得书也可以进行版本迭代。也可以与多人合作，来编辑，更新书籍，适合单人创作或者多人共同创作。
怎么利用gitbook生成自己的书，可以参考如下链接
https://www.jianshu.com/p/cf4989c20bd8
https://www.cnblogs.com/Lam7/p/6109872.html

在安装好Node.js与gitbook之后，我们可以利用gitbook的GUI创建一本书，写入一些章节，然后保存，然后在cmd到该书summary.md所在的路径，然后再利用gitbook init进行初始化，然后再利用gitbook serve在浏览器上对书内容进行访问。
当然，个gitbook serve这一步会出错，会出现fontsettings.js找不到的情况，我们需要修改C:\Users\pili\.gitbook\versions\3.2.3\lib\output\website\copyPluginAssets.js，设置confirm: false，再重启个gitbook serve就可以了。
详见https://github.com/GitbookIO/gitbook/issues/1309
然后就可以在 http://localhost:4000 访问书籍了
![](/assets/FirstChapter1.PNG)
如果想让章节有层次感的显示，则可以在summary.md中设置
![](/assets/GitbookChapterSectionPart.png)


#Error: Error with command "svgexport"
在cmd中安装：npm install svgexport -g
##生成pdf
gitbook pdf ./ ./ML2.pdf

###换行
一行之后加两个以上的空格。

###同步
在gitbook 客户端book->Repository Setting...中添加Gitbook中书的地址即可：
https://github.com/Li-Simon/Gitbook.git
一般是在gitbook中先创建一本书，然后再copy到本地。  
