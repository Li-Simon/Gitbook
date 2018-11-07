# Linux Basic

# Ubuntu VirtualBox上建立share folder[^1]

[https://www.howtogeek.com/187703/how-to-access-folders-on-your-host-machine-from-an-ubuntu-virtual-machine-in-virtualbox/](https://www.howtogeek.com/187703/how-to-access-folders-on-your-host-machine-from-an-ubuntu-virtual-machine-in-virtualbox/)

1通过VirtualBox setting中的shared folded选定windows中的一个文件作为共享文件夹

要勾Auto-mount，否则在ubuntu中显示不出来

![](/assets/Linux_BuildSharedFolder_VirtualBoxSetting.png)

2.打开ubuntu，会发现medis中会有新的文件夹，sf\_ShareFolder,但是不能打开。

![](/assets/Linux_Sharedfolder_notDisplayed.png)

3.需要把我们的ubuntu虚拟机加入到vboxsf

命令：sudo adduser lipp vboxsf

4.重启虚拟机就可以用了![](/assets/Linux_Sharefolder_show.png)

# Linux下文本排序（文本中数字排序）

sort -n RS430FAVaraibles.txt -o RS430FAVaraiblesSorted.txt

#扩展磁盘空间
//查看虚拟磁盘空间信息，确认确实是需要扩容的虚拟硬盘。
VBoxManage showhdinfo "H:\VirtualBox VMs\Ubuntu_14.04\Ubuntu_14.04.vdi"
//计算要扩容的空间大小，我这里是要扩展到100G(1024*1024*1024*100)。
set/a 1024*1024*1024
//扩展虚拟硬盘空间，最后的数字替换成上面计算出的硬盘空间大小。
VBoxManage modifymedium "H:\VirtualBox VMs\Ubuntu_14.04\Ubuntu_14.04.vdi" --resizebyte 107374182400
copy directory:

