# 第二节 编辑数学公式

可以参考[https://598753468.gitbooks.io/tex/content/fei\_xian\_xing\_fu\_hao.html](https://598753468.gitbooks.io/tex/content/fei_xian_xing_fu_hao.html)  
数学公式的编辑类似于Latex.

需要安装mathjax

```
npm install mathjax
安装特定版本的npm install mathjax@2.6.1
```

首先在书籍project的最顶成新建一个book.json,内容如下

```
{
    "gitbook": "3.2.3",
    "plugins": ["mathjax"],
    "links": {
        "sidebar": {
            "Contact us / Support": "https://www.gitbook.com/contact"
        }
    },
    "pluginsConfig": {
    "mathjax":{
            "forceSVG": true
        }
        }
}
```

然后再用gitbook install命令安装mathjax

安装之后gitbook就出现编译错误了，也不能编译生成pdf文件。不论mathjax是哪个版本，从2.5开始都出错。下面选择用katex

gitbook pdf ./ mybook.pdf  （./ mybook.pdf 之间有空格）

[http://ldehai.com/blog/2016/11/30/write-with-gitbook/](http://ldehai.com/blog/2016/11/30/write-with-gitbook/)

no such file fontsettings.js,在上一节有讲怎么处理。

安装Katex [https://github.com/GitbookIO/plugin-katex](https://github.com/GitbookIO/plugin-katex)

1. 在你的书籍文件夹里创建book.json 
2. 里面写入如下内容
3. ```
   {
       "plugins": ["katex"]
   }
   ```
4. 运行安装 gitbook install就安装好了



