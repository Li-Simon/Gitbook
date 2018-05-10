# 第二节 编辑数学公式

可以参考[https://598753468.gitbooks.io/tex/content/fei\_xian\_xing\_fu\_hao.html](https://598753468.gitbooks.io/tex/content/fei_xian_xing_fu_hao.html)  
数学公式的编辑类似于Latex.

需要安装mathjax

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

gitbook pdf ./ mybook.pdf

[http://ldehai.com/blog/2016/11/30/write-with-gitbook/](http://ldehai.com/blog/2016/11/30/write-with-gitbook/)



no such file fontsettings.js



