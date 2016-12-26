# Recommend-System-GUI
QT/C++ for simple book management and recommendation

Version:
Qt 5.7.1
Qt Creator 4.2.0
Visual Studio Community 2015
sqlite3

OS:
Windows 10

Kit:
Desktop Qt 5.7.1 MSVC2015 64bit

注意事项：
打开项目时，请打开Login文件夹中的Login.pro。名为"build..."的文件夹是build的时候生成的，sqlite文件夹里存放了我们的数据库。
login.cpp中有两处绝对路径需要修改，一个是图片，一个是数据库，尝试过使用相对路径但是会报错。
运行时如遇到qmake相关错误，请先删除文件夹下的Login.pro.user，再根据Kit信息重新载入项目。
视频演示中，part1是注册和登陆，part2是图书管理和推荐系统的界面。
