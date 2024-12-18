#ifndef MYWIDGET_H 
#define MYWIDGET_H 

#include <graphics.h> // 图形库
#include <string> // 处理字符串
#include <vector> // 处理向量（动态数组）
#include <map> // 处理映射（关联数组）
#include <tchar.h> // 处理字符和字符串
#include <conio.h> // 控制台输入输出
#include <cstdio> // 标准输入输出
#include <cstring> // 字符串处理函数
#include <mmsystem.h> // 多媒体系统函数
#include <windows.h> //  Windows API 
#include <iostream> // 标准输入输出流
#include <fstream> // 文件流，
#include <locale> // 本地化库
#include <cstring> // 字符串处理
#include <sstream> // 字符串流
#pragma comment(lib, "Winmm.lib") // 链接多媒体库
using namespace std;


// 设置窗口位置
void setWindowPosition(HWND hwnd) // 定义一个函数，用于设置窗口位置
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN); // 获取屏幕的宽度
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); // 获取屏幕的高度

    RECT rect; // 定义一个 RECT 结构体，用于存储窗口的尺寸和位置
    GetWindowRect(hwnd, &rect); // 获取窗口的当前尺寸和位置，将结果存储在 rect 结构体中
    int windowWidth = rect.right - rect.left; // 计算窗口的宽度
    int windowHeight = rect.bottom - rect.top; // 计算窗口的高度

    int x = (screenWidth - windowWidth) / 2; // 计算窗口左上角的 X 坐标，使其位于屏幕中央
    int y = (screenHeight - windowHeight) / 2; // 计算窗口左上角的 Y 坐标，使其位于屏幕中央
    MoveWindow(hwnd, x, y, rect.right - rect.left, rect.bottom - rect.top, TRUE); // 使用 MoveWindow 函数将窗口移动到目标位置
}

// 定义一个按钮结构体，包含按钮的属性
struct Button {
    int x, y, width, height, textSize; // 按钮的坐标、宽度、高度和文字大小
    const TCHAR* text; // 按钮显示的文本
    COLORREF textColor; // 按钮文字的颜色
    COLORREF borderColor; // 按钮边框的颜色
    COLORREF fillColor; // 按钮填充的颜色
    COLORREF hoverColor; // 按钮悬停时的颜色
    bool hovered; // 按钮是否悬停的状态
};

std::map<const TCHAR*, Button> buttonsMap; // 使用映射存储按钮

// 初始化按钮的属性
void initButton(Button& button, int x, int y, int width, int height, const TCHAR* text, int textSize, COLORREF textColor, COLORREF borderColor, COLORREF fillColor, COLORREF hoverColor) {
    button.x = x; // 设置按钮的 X 坐标
    button.y = y; // 设置按钮的 Y 坐标
    button.width = width; // 设置按钮的宽度
    button.height = height; // 设置按钮的高度
    button.text = text; // 设置按钮的文本
    button.textSize = textSize; // 设置按钮文本的大小
    button.textColor = textColor; // 设置按钮文本的颜色
    button.borderColor = borderColor; // 设置按钮边框的颜色
    button.fillColor = fillColor; // 设置按钮填充的颜色
    button.hoverColor = hoverColor; // 设置按钮悬停时的颜色
    button.hovered = false; // 初始化按钮的悬停状态为假
}

// 绘制按钮
void drawButton(Button& button)
{
    COLORREF currentFillColor = button.fillColor; // 设置当前填充颜色为按钮的填充颜色
    if (button.hovered) { // 如果按钮处于悬停状态
        currentFillColor = button.hoverColor; // 设置当前填充颜色为悬停颜色
    }

    setlinecolor(button.borderColor); // 设置按钮边框的颜色
    setfillcolor(currentFillColor); // 设置按钮填充的颜色
    solidrectangle(button.x, button.y, button.x + button.width, button.y + button.height); // 绘制实心矩形按钮

    setbkmode(TRANSPARENT); // 设置背景模式为透明
    settextcolor(button.textColor); // 设置文本颜色为按钮文本颜色
    settextstyle(button.textSize, 0, _T("思源黑体")); // 设置文本样式和大小
    int textWidth = textwidth(button.text); // 获取文本的宽度
    int textHeight = textheight(button.text); // 获取文本的高度
    int textX = button.x + (button.width - textWidth) / 2; // 计算文本的 X 坐标，使其在按钮中居中
    int textY = button.y + (button.height - textHeight) / 2; // 计算文本的 Y 坐标，使其在按钮中居中
    outtextxy(textX, textY, button.text); // 在指定位置绘制文本
}

// 检查鼠标是否悬停在按钮上
bool isMouseHover(Button& button)
{
    POINT mousePos; // 定义一个 POINT 结构体用于存储鼠标位置
    GetCursorPos(&mousePos); // 获取鼠标当前位置
    ScreenToClient(GetForegroundWindow(), &mousePos); // 将鼠标位置转换为窗口客户端坐标
    int mouseX = mousePos.x; // 获取鼠标的 X 坐标
    int mouseY = mousePos.y; // 获取鼠标的 Y 坐标
    // 检查鼠标是否在按钮范围内
    return (mouseX > button.x && mouseX < button.x + button.width && mouseY > button.y && mouseY < button.y + button.height);
}

// 检查按钮是否被点击
bool isButtonClicked(Button& button) {
    return isMouseHover(button) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000); // 如果鼠标悬停在按钮上且左键按下，返回真
}

// 创建一个按钮并添加到映射中
void createButton(const TCHAR* name, int x, int y, int width, int height, const TCHAR* text, int textSize, COLORREF textColor, COLORREF borderColor, COLORREF fillColor, COLORREF hoverColor) {
    Button button; // 定义一个按钮对象
    initButton(button, x, y, width, height, text, textSize, textColor, borderColor, fillColor, hoverColor); // 初始化按钮属性
    buttonsMap[name] = button; // 将按钮添加到映射中
}

// 绘制所有按钮
void drawButtons(const IMAGE& background) {
    putimage(0, 0, &background); // 将背景图片绘制到窗口

    for (auto& pair : buttonsMap) { // 遍历映射中的每个按钮
        Button& button = pair.second; // 获取当前按钮
        button.hovered = isMouseHover(button); // 检查按钮是否悬停
        drawButton(button); // 绘制按钮
    }

    FlushBatchDraw(); // 刷新批量绘制的内容
}

#endif 
