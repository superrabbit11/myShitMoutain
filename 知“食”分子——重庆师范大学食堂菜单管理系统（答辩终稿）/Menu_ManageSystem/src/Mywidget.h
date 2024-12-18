#ifndef MYWIDGET_H 
#define MYWIDGET_H 

#include <graphics.h> // ͼ�ο�
#include <string> // �����ַ���
#include <vector> // ������������̬���飩
#include <map> // ����ӳ�䣨�������飩
#include <tchar.h> // �����ַ����ַ���
#include <conio.h> // ����̨�������
#include <cstdio> // ��׼�������
#include <cstring> // �ַ���������
#include <mmsystem.h> // ��ý��ϵͳ����
#include <windows.h> //  Windows API 
#include <iostream> // ��׼���������
#include <fstream> // �ļ�����
#include <locale> // ���ػ���
#include <cstring> // �ַ�������
#include <sstream> // �ַ�����
#pragma comment(lib, "Winmm.lib") // ���Ӷ�ý���
using namespace std;


// ���ô���λ��
void setWindowPosition(HWND hwnd) // ����һ���������������ô���λ��
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN); // ��ȡ��Ļ�Ŀ��
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); // ��ȡ��Ļ�ĸ߶�

    RECT rect; // ����һ�� RECT �ṹ�壬���ڴ洢���ڵĳߴ��λ��
    GetWindowRect(hwnd, &rect); // ��ȡ���ڵĵ�ǰ�ߴ��λ�ã�������洢�� rect �ṹ����
    int windowWidth = rect.right - rect.left; // ���㴰�ڵĿ��
    int windowHeight = rect.bottom - rect.top; // ���㴰�ڵĸ߶�

    int x = (screenWidth - windowWidth) / 2; // ���㴰�����Ͻǵ� X ���꣬ʹ��λ����Ļ����
    int y = (screenHeight - windowHeight) / 2; // ���㴰�����Ͻǵ� Y ���꣬ʹ��λ����Ļ����
    MoveWindow(hwnd, x, y, rect.right - rect.left, rect.bottom - rect.top, TRUE); // ʹ�� MoveWindow �����������ƶ���Ŀ��λ��
}

// ����һ����ť�ṹ�壬������ť������
struct Button {
    int x, y, width, height, textSize; // ��ť�����ꡢ��ȡ��߶Ⱥ����ִ�С
    const TCHAR* text; // ��ť��ʾ���ı�
    COLORREF textColor; // ��ť���ֵ���ɫ
    COLORREF borderColor; // ��ť�߿����ɫ
    COLORREF fillColor; // ��ť������ɫ
    COLORREF hoverColor; // ��ť��ͣʱ����ɫ
    bool hovered; // ��ť�Ƿ���ͣ��״̬
};

std::map<const TCHAR*, Button> buttonsMap; // ʹ��ӳ��洢��ť

// ��ʼ����ť������
void initButton(Button& button, int x, int y, int width, int height, const TCHAR* text, int textSize, COLORREF textColor, COLORREF borderColor, COLORREF fillColor, COLORREF hoverColor) {
    button.x = x; // ���ð�ť�� X ����
    button.y = y; // ���ð�ť�� Y ����
    button.width = width; // ���ð�ť�Ŀ��
    button.height = height; // ���ð�ť�ĸ߶�
    button.text = text; // ���ð�ť���ı�
    button.textSize = textSize; // ���ð�ť�ı��Ĵ�С
    button.textColor = textColor; // ���ð�ť�ı�����ɫ
    button.borderColor = borderColor; // ���ð�ť�߿����ɫ
    button.fillColor = fillColor; // ���ð�ť������ɫ
    button.hoverColor = hoverColor; // ���ð�ť��ͣʱ����ɫ
    button.hovered = false; // ��ʼ����ť����ͣ״̬Ϊ��
}

// ���ư�ť
void drawButton(Button& button)
{
    COLORREF currentFillColor = button.fillColor; // ���õ�ǰ�����ɫΪ��ť�������ɫ
    if (button.hovered) { // �����ť������ͣ״̬
        currentFillColor = button.hoverColor; // ���õ�ǰ�����ɫΪ��ͣ��ɫ
    }

    setlinecolor(button.borderColor); // ���ð�ť�߿����ɫ
    setfillcolor(currentFillColor); // ���ð�ť������ɫ
    solidrectangle(button.x, button.y, button.x + button.width, button.y + button.height); // ����ʵ�ľ��ΰ�ť

    setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
    settextcolor(button.textColor); // �����ı���ɫΪ��ť�ı���ɫ
    settextstyle(button.textSize, 0, _T("˼Դ����")); // �����ı���ʽ�ʹ�С
    int textWidth = textwidth(button.text); // ��ȡ�ı��Ŀ��
    int textHeight = textheight(button.text); // ��ȡ�ı��ĸ߶�
    int textX = button.x + (button.width - textWidth) / 2; // �����ı��� X ���꣬ʹ���ڰ�ť�о���
    int textY = button.y + (button.height - textHeight) / 2; // �����ı��� Y ���꣬ʹ���ڰ�ť�о���
    outtextxy(textX, textY, button.text); // ��ָ��λ�û����ı�
}

// �������Ƿ���ͣ�ڰ�ť��
bool isMouseHover(Button& button)
{
    POINT mousePos; // ����һ�� POINT �ṹ�����ڴ洢���λ��
    GetCursorPos(&mousePos); // ��ȡ��굱ǰλ��
    ScreenToClient(GetForegroundWindow(), &mousePos); // �����λ��ת��Ϊ���ڿͻ�������
    int mouseX = mousePos.x; // ��ȡ���� X ����
    int mouseY = mousePos.y; // ��ȡ���� Y ����
    // �������Ƿ��ڰ�ť��Χ��
    return (mouseX > button.x && mouseX < button.x + button.width && mouseY > button.y && mouseY < button.y + button.height);
}

// ��鰴ť�Ƿ񱻵��
bool isButtonClicked(Button& button) {
    return isMouseHover(button) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000); // ��������ͣ�ڰ�ť����������£�������
}

// ����һ����ť����ӵ�ӳ����
void createButton(const TCHAR* name, int x, int y, int width, int height, const TCHAR* text, int textSize, COLORREF textColor, COLORREF borderColor, COLORREF fillColor, COLORREF hoverColor) {
    Button button; // ����һ����ť����
    initButton(button, x, y, width, height, text, textSize, textColor, borderColor, fillColor, hoverColor); // ��ʼ����ť����
    buttonsMap[name] = button; // ����ť��ӵ�ӳ����
}

// �������а�ť
void drawButtons(const IMAGE& background) {
    putimage(0, 0, &background); // ������ͼƬ���Ƶ�����

    for (auto& pair : buttonsMap) { // ����ӳ���е�ÿ����ť
        Button& button = pair.second; // ��ȡ��ǰ��ť
        button.hovered = isMouseHover(button); // ��鰴ť�Ƿ���ͣ
        drawButton(button); // ���ư�ť
    }

    FlushBatchDraw(); // ˢ���������Ƶ�����
}

#endif 
