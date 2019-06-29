# 第二节 编辑数学公式

# mathjax

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

# 安装Katex

[https://github.com/GitbookIO/plugin-katex](https://github.com/GitbookIO/plugin-katex)

1. 在你的书籍文件夹里创建book.json 
2. 里面写入如下内容
3. ```
   {
       "plugins": ["katex"]
   }
   ```
4. 运行安装 gitbook install就安装好了（安装很慢，一个小时\),可以换个地方安装，只要把book.json换个地方，再在这个folder安装gitbook install，然后把node\_modules 拷到你书籍所在的folder就可以。
Katex支持的公式https://khan.github.io/KaTeX/docs/supported.html
https://utensil-site.github.io/available-in-katex/

# 中文在cmd中乱码的问题：

1. 打开cmd, 输入chcp 65001chcp 65001
2. 右击cmd上方，选择属性--&gt;字体--&gt;SimSun-ExtB就可以显示了。

# 语法高亮

```
Supported languages
This is the list of all 120 languages currently supported by Prism, with their corresponding alias, to use in place of xxxx in the language-xxxx class:



Markup - markup
CSS - css
C-like - clike
JavaScript - javascript
ABAP - abap
ActionScript - actionscript
Ada - ada
Apache Configuration - apacheconf
APL - apl
AppleScript - applescript
AsciiDoc - asciidoc
ASP.NET (C#) - aspnet
AutoIt - autoit
AutoHotkey - autohotkey
Bash - bash
BASIC - basic
Batch - batch
Bison - bison
Brainfuck - brainfuck
Bro - bro
C - c
C# - csharp
C++ - cpp
CoffeeScript - coffeescript
Crystal - crystal
CSS Extras - css-extras
D - d
Dart - dart
Diff - diff
Docker - docker
Eiffel - eiffel
Elixir - elixir
Erlang - erlang
F# - fsharp
Fortran - fortran
Gherkin - gherkin
Git - git
GLSL - glsl
Go - go
GraphQL - graphql
Groovy - groovy
Haml - haml
Handlebars - handlebars
Haskell - haskell
Haxe - haxe
HTTP - http
Icon - icon
Inform 7 - inform7
Ini - ini
J - j
Jade - jade
Java - java
Jolie - jolie
JSON - json
Julia - julia
Keyman - keyman
Kotlin - kotlin
LaTeX - latex
Less - less
LiveScript - livescript
LOLCODE - lolcode
Lua - lua
Makefile - makefile
Markdown - markdown
MATLAB - matlab
MEL - mel
Mizar - mizar
Monkey - monkey
NASM - nasm
nginx - nginx
Nim - nim
Nix - nix
NSIS - nsis
Objective-C - objectivec
OCaml - ocaml
Oz - oz
PARI/GP - parigp
Parser - parser
Pascal - pascal
Perl - perl
PHP - php
PHP Extras - php-extras
PowerShell - powershell
Processing - processing
Prolog - prolog
.properties - properties
Protocol Buffers - protobuf
Puppet - puppet
Pure - pure
Python - python
Q - q
Qore - qore
R - r
React JSX - jsx
Reason - reason
reST (reStructuredText) - rest
Rip - rip
Roboconf - roboconf
Ruby - ruby
Rust - rust
SAS - sas
Sass (Sass) - sass
Sass (Scss) - scss
Scala - scala
Scheme - scheme
Smalltalk - smalltalk
Smarty - smarty
SQL - sql
Stylus - stylus
Swift - swift
Tcl - tcl
Textile - textile
Twig - twig
TypeScript - typescript
Verilog - verilog
VHDL - vhdl
vim - vim
Wiki markup - wiki
Xojo (REALbasic) - xojo
YAML - yaml
```
$$\hat f$$
$$\frac{\partial J(\theta)}{\partial \theta_{j}} = -\frac{1}{m}\sum_{i=1}^m(y^i - h_{\theta}(x^i))x_{j}^{i}$$  

http://www.aleacubase.com/cudalab/cudalab_usage-math_formatting_on_markdown.html
https://www.zybuluo.com/codeep/note/163962#3%E5%A6%82%E4%BD%95%E8%BE%93%E5%85%A5%E6%8B%AC%E5%8F%B7%E5%92%8C%E5%88%86%E9%9A%94%E7%AC%A6


