#include "View/MainWindow.h"
#include <QApplication>
#include <QTextCodec>

#ifdef __WIN32
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#endif
int main(int argc, char *argv[])
{

#ifdef _WIN32
    //http://m.blog.csdn.net/article/details?id=52789570
    //控制台显示乱码纠正
   // system("chcp 65001"); //设置字符集（使用SetConsoleCP(65001)设置无效，原因未知）
    SetConsoleOutputCP (65001);
    CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体来支持中文显示。
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = 16; // leave X as zero
    info.FontWeight = FW_NORMAL;
    wcscpy(info.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
#endif
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");//设置编码格式
    QTextCodec::setCodecForLocale(codec);
    MainWindow w;
    w.show();

    return a.exec();
}
