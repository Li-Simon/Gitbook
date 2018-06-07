# Linux Basic

# Ubuntu VirtualBox上建立share folder

1通过VirtualBox setting中的shared folded选定windows中的一个文件作为共享文件夹

要勾Auto-mount，否则在ubuntu中显示不出来

![](/assets/Linux_BuildSharedFolder_VirtualBoxSetting.png)

2.打开ubuntu，会发现medis中会有新的文件夹，sf\_ShareFolder,但是不能打开。

![](/assets/Linux_Sharedfolder_notDisplayed.png)

3.需要把我们的ubuntu虚拟机加入到vboxsf

命令：sudo adduser lipp vboxsf

4.重启虚拟机就可以用了

