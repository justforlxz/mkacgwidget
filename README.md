# mkacgwidget
该项目是使用qt在linux下应用，需要使用Deepin　Desktop Environment.
程序架构为

```
—————————
         |——核心
         |——功能
         |—|—Dbus（电量）（语音）
         |—|—模块（对话）（一言）（邮件）（IRC）（语音）（动作）
         |——界面
         |—|——（仿live2d的SSP）（SAO血两条）（mailBox）（IRC聊天室）
```
依赖包
Arch：

```
sudo pacman -S qt5-base qt5-declarative g++
```

运行示例

![ys](Github_pic/1.png)

完成电量的监测和电池状态监测，完成经验值和升级。

![ys](Github_pic/2-1.png)

![ys](Github_pic/2-2.png)

![ys](Github_pic/3.png)

主题做的不怎么好，只是简单的替换文件。

![ys](Github_pic/4.png)

![ys](Github_pic/5.png)

歌曲现在出现问题了，网易云音乐似乎封了几个url，老的API估计没办法用了，有空换新的。

![ys](Github_pic/6.png)

语音操作已经做了一半了，实现了自动化录音及发送请求。

![ys](Github_pic/7.png)

这里还没做好，内容会超出。

![ys](Github_pic/8.png)
