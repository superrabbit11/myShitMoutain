#include"Mywidget.h"
#include"Statement.h"
using namespace std;

int main()
{
	InitList(L);
	InitList(L1);
	ReadFromFile(L, "file\\dishes.txt");
	ReadFromFile(L1, "file\\bill.txt");

	// ѭ����������
	mciSendString(_T("open \"music\\music.mp3\" type mpegvideo alias music"), NULL, 0, NULL);
	mciSendString(_T("play music repeat"), NULL, 0, NULL);

	WelcomeInterface();
	LoginInterface();
	cout << "ϵͳ��ʾ��ϣ�";

	mciSendString(_T("close music"), NULL, 0, NULL);

	return 0;
}

/********************************
		   ��ӭ����
********************************/
void WelcomeInterface()
{
	IMAGE img;
	initgraph(800, 450);//��ӭ���ڴ�С
	loadimage(&img, _T("photo\\welcome.png"), 800, 450);//����ͼƬ���ߣ���������
	putimage(0, 0, &img);//ͼƬ��ʾ��λ��
	HWND hwnd;// ���ô��ھ���������洰����Ϣ
	hwnd = GetHWnd();// ��ȡ���ھ��
	setWindowPosition(hwnd); //���ô���λ��
	SetWindowText(hwnd, _T("��ӭʹ�����ǵ�ϵͳ��")); //���ô��ڱ���
	Sleep(3000);     //������ͣ3��
	closegraph();   //�ر�ͼ��ҳ��
}



/********************************
		   ��¼����
********************************/
void LoginInterface()
{
	// ��ʼ�����ڴ�С
	initgraph(1280, 720);
	IMAGE img;

	// ����ͼƬ�����ÿ����������
	loadimage(&img, _T("photo\\login.png"), 1280, 720);
	putimage(0, 0, &img); // ��ʾͼƬ��λ��

	// ��ȡ���ھ��
	HWND hwnd = GetHWnd();
	setWindowPosition(hwnd);//���ô���λ��
	SetWindowText(hwnd, _T("֪��ʳ�����ӡ�������ʦ����ѧʳ�ò˵�����ϵͳ"));//���ô��ڱ���

	// ������ť
	createButton(_T("customerlogin"), 640, 100, 420, 210, _T("�˿͵�¼"), 100, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("adminlogin"), 640, 410, 420, 210, _T("����Ա��¼"), 100, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));

	BeginBatchDraw();//��ʼ��������

	while (1) {
		cleardevice();//����豸
		drawButtons(img);//���ư�ť
		EndBatchDraw();//������������

		MOUSEMSG msg = GetMouseMsg();
		msg = GetMouseMsg();// ��ȡ�����Ϣ
		if (isButtonClicked(buttonsMap[_T("customerlogin")]) == 1)
		{
			//�˿͵�¼

			setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ

			char Customeraccount[] = "Customer";//�˿��˺�
			char Customerpassword[] = "123456";//�˿�����

			// ��ʾ�����
			char inputAccont[100];
			char inputPassword[100];
			//��ʾ����򲢻�ȡ������˺�
			InputBox(inputAccont, 20, "�˺���֤", "�������˺ţ�Ĭ��ΪCustomer����", "��ֻ������Ĭ���˺���������", 0, 0, false);

			// ����˺�
			if (strcmp(inputAccont, Customeraccount) == 0)//�������˺���˿��˺���ͬ
			{
				cleardevice();//����豸�ϵ�����
				drawButtons(img);//���»��ư�ť
				BeginBatchDraw();//��ʼ��������
				EndBatchDraw();//������������
				MessageBox(hwnd, "���ڸ��˺ţ�", "�˺���֤", MB_OK | MB_ICONINFORMATION);//������ʾ��
				//��ʾ����򲢻�ȡ���������
				InputBox(inputPassword, 20, "������֤", "�������˺ţ�Ĭ��Ϊ123456����", "����Ĭ���˺���Ҳ��ֻ������Ĭ��������������", 0, 0, false);

				// �������
				if (strcmp(inputPassword, Customerpassword) == 0)//������������˿�������ͬ
				{
					MessageBox(hwnd, "������ȷ��", "������֤", MB_OK | MB_ICONINFORMATION);
					// ɾ����ť���رմ��ڣ���ת����ҳ��
					auto d1 = buttonsMap.find("customerlogin"); //���ҹ˿͵�¼��ť
					auto d2 = buttonsMap.find("adminlogin"); //���ҹ���Ա��¼��ť
					if (d1 != buttonsMap.end() && d2 != buttonsMap.end()) //����ҵ���������ť
					{
						buttonsMap.erase(d1);//ɾ���˿͵�¼��ť
						buttonsMap.erase(d2);//ɾ������Ա��¼��ť
					}
					//����豸
					cleardevice();
					//�ر�ͼ�ν���
					closegraph();
					//��ת����ҳ��
					Customermainface();
				}
				else
				{
					MessageBox(hwnd, "�������", "������֤", MB_OK | MB_ICONERROR);//������ʾ��
					continue;
				}
				break;
			}
			else
			{
				MessageBox(hwnd, "�����ڸ��˺ţ�����������", "�˺���֤", MB_OK | MB_ICONERROR);//������ʾ��
				break;
			}
		}
		else if (isButtonClicked(buttonsMap[_T("adminlogin")]) == 1)
		{
			//����Ա��¼

			setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ

			//�˿͵�Ĭ���˺ź�����
			char Customeraccount[] = "Admin";
			char Customerpassword[] = "123456";
			// ��ʾ��������������˺�
			char inputAccont[100];
			char inputPassword[100];
			InputBox(inputAccont, 20, "�˺���֤", "�������˺ţ�Ĭ��ΪAdmin����", "��ֻ������Ĭ���˺���������", 0, 0, false);

			// ���������˺��Ƿ���˿͵�Ĭ���˺�ƥ��
			if (strcmp(inputAccont, Customeraccount) == 0)
			{
				cleardevice();//����豸�ϵ�����
				drawButtons(img);//���»��ư�ť
				BeginBatchDraw();//��ʼ��������
				EndBatchDraw();//������������
				MessageBox(hwnd, "���ڸ��˺ţ�", "�˺���֤", MB_OK | MB_ICONINFORMATION);//��ʾ��Ϣ�򣬸�֪�û��˺Ŵ���
				InputBox(inputPassword, 20, "������֤", "�������˺ţ�Ĭ��Ϊ123456����", "����Ĭ���˺���Ҳ��ֻ������Ĭ��������������", 0, 0, false);

				// �������������Ƿ���˿͵�Ĭ������ƥ��
				if (strcmp(inputPassword, Customerpassword) == 0)
				{
					MessageBox(hwnd, "������ȷ��", "������֤", MB_OK | MB_ICONINFORMATION);

					// ɾ����ť���رմ��ڣ���ת����ҳ��
					auto d1 = buttonsMap.find("customerlogin");
					auto d2 = buttonsMap.find("adminlogin");
					if (d1 != buttonsMap.end() && d2 != buttonsMap.end())
					{
						buttonsMap.erase(d1);
						buttonsMap.erase(d2);
					}
					//����豸
					cleardevice();
					//�ر�ͼ�ν���
					closegraph();
					//��ת������Ա����
					Adminmainface();
				}
				else
				{
					MessageBox(hwnd, "�������", "������֤", MB_OK | MB_ICONERROR);//��ʾ��Ϣ�򣬸�֪�û��������
					continue;
				}
				break;
			}
			else
			{
				MessageBox(hwnd, "�����ڸ��˺ţ�����������", "�˺���֤", MB_OK | MB_ICONERROR);//��ʾ��Ϣ�򣬸�֪�û��˺Ų�����
				continue;
			}
		}
	}

	FlushBatchDraw();//ˢ���������Ƶ����ݣ�ȷ�����л��Ʋ�������ʾ�ڽ����ϣ�
	Sleep(30);//��ͣ30����
}


/********************************
		   ϵͳ�˿Ͷ�
********************************/
void Customermainface() 
{
	initgraph(1280, 720);
	cleardevice();
	IMAGE img;

	loadimage(&img, _T("photo\\customer.png"), 1280, 720);
	putimage(0, 0, &img);

	HWND hwnd = GetHWnd();
	setWindowPosition(hwnd);
	SetWindowText(hwnd, _T("֪��ʳ�����ӡ�������ʦ����ѧʳ�ò˵�����ϵͳ(�˿Ͷ�)"));

	createButton(_T("ordermenu"), 530, 300, 210, 80, _T("�鿴�˵�"), 50, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("order"), 530, 405, 210, 80, _T("���"), 50, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("consume"), 530, 510, 210, 80, _T("�������"), 50, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("exit"), 530, 615, 210, 80, _T("�˳�����"), 50, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));

	BeginBatchDraw();
	while (1) {
		ExMessage msg = getmessage();
		cleardevice();
		drawButtons(img);
		EndBatchDraw();

		if (isButtonClicked(buttonsMap[_T("ordermenu")])) {
			cleardevice();
			printdish();
			break;
		}
		else if (isButtonClicked(buttonsMap[_T("order")])) {
			Order(img);
			cleardevice();
			continue;
		}
		else if (isButtonClicked(buttonsMap[_T("consume")])) {
			cleardevice();
			Consumeface();
			break;
		}
		else if (isButtonClicked(buttonsMap[_T("exit")])) {
			cleardevice();
			Thanksface();
			break;
		}
	}
}
void printdish()
{
	initgraph(1280, 720);
	cleardevice();
	IMAGE img;

	loadimage(&img, _T("photo\\window.png"), 1280, 720);
	putimage(0, 0, &img);

	HWND hwnd1 = GetHWnd();
	setWindowPosition(hwnd1);
	SetWindowText(hwnd1, _T("֪��ʳ�����ӡ�������ʦ����ѧʳ�ò˵�����ϵͳ(�˿Ͷ�)"));

	setbkmode(OPAQUE);
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("˼Դ����"));
	outtextxy(40, 100, _T("���"));
	outtextxy(170, 100, _T("����"));
	outtextxy(300, 100, _T("�۸�"));
	outtextxy(470, 100, _T("����"));
	outtextxy(600, 100, _T("����ʳ��"));
	outtextxy(830, 100, _T("��ʦ"));
	outtextxy(960, 100, _T("�Ƿ�Ϊ�������ʦ��"));

	// ���Ʋ˵�����
	LinkList p = L->next;
	int y = 150;
	while (p) {
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(30, 0, _T("˼Դ����"));

		TCHAR buffer[50];
		_stprintf_s(buffer, _T("%d"), p->data.id);
		outtextxy(40, y, buffer);
		outtextxy(170, y, p->data.name);
		_stprintf_s(buffer, _T("%.2f"), p->data.price);
		outtextxy(300, y, buffer);
		_stprintf_s(buffer, _T("%d"), p->data.sales);
		outtextxy(470, y, buffer);
		outtextxy(600, y, p->data.canteen);
		outtextxy(830, y, p->data.chefName);
		outtextxy(960, y, p->data.chefIsExcellent ? _T("Yes") : _T("No"));
		y += 20;
		p = p->next;
	}

	setfillcolor(WHITE);
	fillrectangle(1060, 620, 1260, 700);

	// ���ư�ť�ı�
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("˼Դ����"));
	outtextxy(1125, 635, _T("����"));

	while (1) {
		ExMessage m2 = getmessage();

		if (m2.x > 1060 && m2.x < 1260 && m2.y > 620 && m2.y < 700)
		{
			setlinecolor(RED);
			rectangle(1060, 620, 1260, 700);
		}
		else {
			setlinecolor(BLACK);
			rectangle(1060, 620, 1260, 700);
		}
		if (m2.message == WM_LBUTTONDOWN) {
			cleardevice();
			Customermainface();
			break;
		}
	}
}
//��͹���
void Order(IMAGE& img)
{
	// �������Ѽ�¼
	Dish newDish;
	char inputBuffer[50];

	// �������Ʋ�����ظ�
	while (true)
	{
		InputBox(newDish.name, 50, "�����������Ʒ������");
		if (!IsDishNameDuplicate(L, newDish.name))
		{
			HWND hwndInput1 = GetHWnd();
			MessageBox(hwndInput1, "�ò�Ʒ�����ڣ�����������", "��ʾ", MB_OK);
		}
		else
		{
			break;
		}
	}

	// ������
	InputBox(inputBuffer, 10, "�����빺���Ʒ�����ڣ�������240601��");
	newDish.id = atoi(inputBuffer);

	// ����۸�
	InputBox(inputBuffer, 10, "�����������Ʒ�ļ۸�");
	newDish.price = atof(inputBuffer);

	InputBox(inputBuffer, 10, "�����빺���Ʒ�ķ���");
	newDish.sales = atof(inputBuffer);
	//��֤����Ա���������ݸ���
	LNode* p = L->next;
	while (p)
	{
		if (strcmp(p->data.name, newDish.name) == 0)
		{
			p->data.sales = p->data.sales + newDish.sales;
			break;
		}
		p = p->next;
	}

	// ����ʳ��
	InputBox(newDish.canteen, 50, "������������Ʒ����ʳ��");

	// �����ʦ����
	InputBox(newDish.chefName, 50, "������������Ʒ�ĳ�ʦ����");

	// �����Ʒ�Ƿ�ó�
	InputBox(inputBuffer, 10, "���ʲ�Ʒ�ó���1��ʾ�ǣ�0��ʾ��");
	newDish.chefIsExcellent = (atoi(inputBuffer) == 1);

	// ��������
	ListInsert(L1, newDish);
	WriteToFile(L1, "file\\bill.txt");
	WriteToFile(L, "file\\dishes.txt");

	HWND hwnd = GetHWnd();
	MessageBox(hwnd, "��˳ɹ���", "��ʾ", MB_OK);

	// ���������»���֮ǰ������
	cleardevice();
	putimage(0, 0, &img);

}

//�����������
void Consumeface()
{
	initgraph(1280, 720);
	cleardevice();
	IMAGE img;

	loadimage(&img, _T("photo\\window.png"), 1280, 720);
	putimage(0, 0, &img);

	HWND hwnd1 = GetHWnd();
	setWindowPosition(hwnd1);
	SetWindowText(hwnd1, _T("֪��ʳ�����ӡ�������ʦ����ѧʳ�ò˵�����ϵͳ(�˿Ͷ�)"));

	setbkmode(OPAQUE);
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("˼Դ����"));
	outtextxy(40, 100, _T("����"));
	outtextxy(170, 100, _T("����"));
	outtextxy(300, 100, _T("�۸�"));
	outtextxy(470, 100, _T("�������"));
	outtextxy(600, 100, _T("����ʳ��"));
	outtextxy(830, 100, _T("��ʦ"));
	outtextxy(960, 100, _T("�Ƿ�ó�"));

	// ���Ʋ˵�����
	LinkList p = L1->next;
	int y = 150;
	while (p) {
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(30, 0, _T("˼Դ����"));

		TCHAR buffer[50];
		_stprintf_s(buffer, _T("%d"), p->data.id);
		outtextxy(40, y, buffer);
		outtextxy(170, y, p->data.name);
		_stprintf_s(buffer, _T("%.2f"), p->data.price);
		outtextxy(300, y, buffer);
		_stprintf_s(buffer, _T("%d"), p->data.sales);
		outtextxy(470, y, buffer);
		outtextxy(600, y, p->data.canteen);
		outtextxy(830, y, p->data.chefName);
		outtextxy(960, y, p->data.chefIsExcellent ? _T("Yes") : _T("No"));
		y += 20;
		p = p->next;
	}

	setfillcolor(WHITE);
	fillrectangle(1060, 620, 1260, 700);

	// ���ư�ť�ı�
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("˼Դ����"));
	outtextxy(1125, 635, _T("����"));

	while (1) {
		ExMessage m2 = getmessage();

		if (m2.x > 1060 && m2.x < 1260 && m2.y > 620 && m2.y < 700)
		{
			setlinecolor(RED);
			rectangle(1060, 620, 1260, 700);
		}
		else {
			setlinecolor(BLACK);
			rectangle(1060, 620, 1260, 700);
		}
		if (m2.message == WM_LBUTTONDOWN)
		{
			cleardevice();
			Customermainface();
			break;
		}
	}
}

/********************************
		   ϵͳ����Ա��
********************************/
//������
void Adminmainface()
{
	/*cleardevice();
	Sleep(10);
	closegraph();*/

	// ��ʼ�����ڴ�С
	initgraph(1280, 720);
	cleardevice();
	IMAGE img;

	// ����ͼƬ�����ÿ����������
	loadimage(&img, _T("photo\\admin.png"), 1280, 720);
	putimage(0, 0, &img); // ��ʾͼƬ��λ��

	// ��ȡ���ھ��
	HWND hwnd = GetHWnd();
	setWindowPosition(hwnd);
	SetWindowText(hwnd, _T("֪��ʳ�����ӡ�������ʦ����ѧʳ�ò˵�����ϵͳ(����Ա��)"));//���ô��ڱ���

	// ������ť
	createButton(_T("add"), 530, 300, 210, 60, _T("������Ʒ"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("delete"), 530, 370, 210, 60, _T("ɾ����Ʒ"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("change"), 530, 440, 210, 60, _T("��Ϣ�޸�"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("check"), 530, 510, 210, 60, _T("��Ϣ��ѯ"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("sort"), 530, 580, 210, 60, _T("������"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("exit"), 530, 650, 210, 60, _T("�˳�����"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));

	BeginBatchDraw();//��������

	while (1) {
		cleardevice();
		drawButtons(img);

		MOUSEMSG msg = GetMouseMsg();
		msg = GetMouseMsg();// ��ȡ�����Ϣ
		if (isButtonClicked(buttonsMap[_T("add")]) == 1) {//���������Ʒ��ť�����
			cleardevice();//����豸
			drawButtons(img);//���ư�ť
			BeginBatchDraw();//��ʼ��������
			EndBatchDraw();//������������
			Adddish();//����������Ʒ����
		}
		else if (isButtonClicked(buttonsMap[_T("delete")]) == 1)//���ɾ����Ʒ��ť�����
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Deletedish();//����ɾ����Ʒ����
		}
		else if (isButtonClicked(buttonsMap[_T("change")]) == 1)//�����Ϣ�޸İ�ť�����
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Changedish();//������Ϣ�޸ĺ���
		}
		else if (isButtonClicked(buttonsMap[_T("check")]) == 1)//�����Ϣ��ѯ��ť�����
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Checkdish();//������Ϣ��ѯ����

		}
		else if (isButtonClicked(buttonsMap[_T("sort")]) == 1)//��������񵥰�ť�����
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Sortdish();//���������񵥺���
		}
		else if (isButtonClicked(buttonsMap[_T("exit")]) == 1)//����˳�����ť�����
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Thanksface();//�����˳�������
		}
	}

	FlushBatchDraw();
	Sleep(30);
}
//��ӡ�˵�
void printmenu()
{
	// ��ʼ�����ڴ�С
	initgraph(1280, 720);
	cleardevice();
	IMAGE img;

	// ����ͼƬ�����ÿ����������
	loadimage(&img, _T("photo\\window.png"), 1280, 720);
	putimage(0, 0, &img); // ��ʾͼƬ��λ��

	// ��ȡ���ھ��
	HWND hwnd = GetHWnd();
	setWindowPosition(hwnd);//���ô���λ��
	SetWindowText(hwnd, _T("֪��ʳ�����ӡ�������ʦ����ѧʳ�ò˵�����ϵͳ(����Ա��)"));//���ô��ڱ���

	setbkmode(OPAQUE); // �������屳��ģʽΪ��͸��
	setbkcolor(BLACK); // ���ñ�����ɫΪ��ɫ
	settextcolor(WHITE); // ����������ɫΪ��ɫ
	settextstyle(50, 0, "˼Դ����");//����������ʽ�ʹ�С
	outtextxy(40, 100, "���");//��ӡ��ű���
	outtextxy(170, 100, "����");//��ӡ��������
	outtextxy(300, 100, "�۸�");//��ӡ�۸����
	outtextxy(470, 100, "����");//��ӡ��������
	outtextxy(600, 100, "����ʳ��");//��ӡ����ʳ�ñ���
	outtextxy(830, 100, "��ʦ");//��ӡ��ʦ����
	outtextxy(960, 100, "�Ƿ�Ϊ�������ʦ��");//��ӡ�Ƿ�Ϊ�������ʦ������

	LinkList p = L->next;//��ȡ�����еĵ�һ����Ʒ��ָ��
	int y = 150; // ��ʼ y ���꣬��������Ļ�ϴ�ֱ��ӡ��Ʒ��Ϣ
	while (p) //��������
	{
		setbkmode(TRANSPARENT);
		settextcolor(BLACK); // ����������ɫΪ��ɫ
		settextstyle(30, 0, "˼Դ����"); //����������ʽ

		char buffer[50];
		// �����ͺ͸�����ת��Ϊ�ַ�����������outtextxy�������ö�λ�����
		sprintf_s(buffer, sizeof(buffer), "%d", p->data.id);
		outtextxy(40, y, buffer);
		outtextxy(170, y, p->data.name);
		sprintf_s(buffer, sizeof(buffer), "%.2f", p->data.price);
		outtextxy(300, y, buffer);
		sprintf_s(buffer, sizeof(buffer), "%d", p->data.sales);
		outtextxy(470, y, buffer);
		outtextxy(600, y, p->data.canteen);
		outtextxy(830, y, p->data.chefName);
		outtextxy(960, y, p->data.chefIsExcellent ? "Yes" : "No");
		y += 20; //���� y ���꣬������ʾ
		p = p->next;
	}
	setfillcolor(WHITE); //���������ɫΪ��ɫ
	fillrectangle(300, 380, 380, 410); //����һ�����ο�
	while (1) {
		ExMessage m2 = getmessage();

		if (m2.x > 300 && m2.x < 380 && m2.y>380 && m2.y < 410) { //�ж��û����λ���Ƿ��ھ��ο���
			setlinecolor(RED);  //���������߿���ɫΪ��ɫ
			rectangle(300, 380, 380, 410);
		}
		else {
			setlinecolor(WHITE);  //�����������߿���ɫΪ��ɫ
			rectangle(300, 380, 380, 410);
		}
		if (m2.message == WM_LBUTTONDOWN) { //���û�����������
			Adminmainface(); //���������Ա������
		}
	}
}
//������Ʒ����
bool IsDishNameDuplicate(LinkList L, const char* name)
{
	// ����Ƿ���ڸò�Ʒ���з���1���޷���0��
	LinkList p = L->next;
	while (p) {
		//�ж��Ƿ���������������ͬ�Ĳ�Ʒ
		if (strcmp(p->data.name, name) == 0)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}

void Adddish()
{
	// ������Ʒ
	Dish newDish;
	char inputBuffer[50];
	// �������Ʋ�����ظ�
	while (true)
	{
		InputBox(newDish.name, 50, "������������Ʒ������");//������������û������Ʒ����
		if (IsDishNameDuplicate(L, newDish.name)) //����������Ƿ�������ͬ���ƵĲ�Ʒ
		{
			HWND hwndInput1 = GetHWnd();//��õ�ǰ���ھ��
			MessageBox(hwndInput1, "�ò�Ʒ�Ѿ����ڣ�����������", "��ʾ", MB_OK);//������Ϣ��
		}
		else
		{
			break;//�����Ʒ�������ڣ�����ѭ��
		}
	}

	// ������
	InputBox(inputBuffer, 10, "������������Ʒ�ı��");//������������û������Ʒ���
	newDish.id = atoi(inputBuffer);//��������ַ���ת��Ϊ���ͱ��


	// ����۸�
	InputBox(inputBuffer, 10, "������������Ʒ�ļ۸�");//������������û������Ʒ�۸�
	newDish.price = atof(inputBuffer);//��������ַ���ת��Ϊ�����ͼ۸�

	// Ĭ������Ϊ0
	newDish.sales = 0;

	// ����ʳ��
	InputBox(newDish.canteen, 50, "������������Ʒ����ʳ��");//������������û������Ʒ����ʳ��

	// �����ʦ����
	InputBox(newDish.chefName, 50, "������������Ʒ�ĳ�ʦ����");//������������û�����������Ʒ�ĳ�ʦ����

	// �����ʦ�Ƿ�����
	InputBox(inputBuffer, 10, "�������ʦ�Ƿ����㣨1��ʾ�ǣ�0��ʾ��");//������������û������ʦ�Ƿ�����
	newDish.chefIsExcellent = (atoi(inputBuffer) == 1);//��������ַ���ת��Ϊ����ֵ

	// ���²˲�������
	ListInsert(L, newDish);//���²�Ʒ����������
	WriteToFile(L, "file\\dishes.txt");  //������д���ļ�
	printmenu();  //��ӡ�˵�

}
//ɾ����Ʒ
void Deletedish()
{
	char input[50];
	InputBox(input, 50, "������Ҫɾ���Ĳ�Ʒ����");//������������û�����Ҫɾ���Ĳ�Ʒ����
	if (IsDishNameDuplicate(L, input) == 0) //�жϲ�Ʒ�Ƿ����
	{
		HWND hwndInput1 = GetHWnd();//��ȡ��ǰ���ھ��
		MessageBox(hwndInput1, "�ò�Ʒ�����ڣ�����������", "��ʾ", MB_OK);//������Ϣ����ʾ��Ʒ������
	}
	ListDelete(L, input); //��������ɾ��ָ����Ʒ
	WriteToFile(L, "file\\dishes.txt"); //������д���ļ�
	HWND hwnd = GetHWnd();//��ȡ��ǰ���ھ��
	MessageBox(hwnd, "ɾ���ɹ���", "��ʾ", MB_OK);//������Ϣ����ʾɾ���ɹ�

}
//�޸Ĳ�Ʒ
void Changedish() {
	char input[50];
	InputBox(input, 50, "������Ҫ�޸ĵĲ�Ʒ����");//������Ϣ����ʾҪ�޸ĵĲ�Ʒ����
	if (!IsDishNameDuplicate(L, input)) { //�жϲ�Ʒ�Ƿ����
		HWND hwndInput1 = GetHWnd();//��ȡ��ǰ���ھ��
		MessageBox(hwndInput1, "�ò�Ʒ�����ڣ�����������", "��ʾ", MB_OK);//������Ϣ����ʾ��Ʒ������
	}
	else {
		Dish newDish;
		InputBox(newDish.name, 50, "�������µĲ�Ʒ����");//������������û������µĲ�Ʒ����
		char buffer[50];

		InputBox(buffer, 50, "�������µĲ�Ʒ���");//������������û������µĲ�Ʒ���
		newDish.id = atoi(buffer);//��������ַ���ת��Ϊ���ͱ��

		InputBox(buffer, 50, "�������µĲ�Ʒ�۸�");//������������û������Ʒ�۸�
		newDish.price = atof(buffer);//��������ַ���ת��Ϊ�����ͼ۸�

		InputBox(buffer, 50, "�������µĲ�Ʒ����");//������������û������Ʒ����
		newDish.sales = atoi(buffer);//��������ַ���ת��Ϊ��������

		InputBox(newDish.canteen, 50, "�������µĲ�Ʒ����ʳ��");//������������û������Ʒ����ʳ��
		InputBox(newDish.chefName, 50, "�������µ�������Ʒ�ĳ�ʦ����");//������������û�����������Ʒ�ĳ�ʦ����

		InputBox(buffer, 50, "�������µĳ�ʦ�Ƿ�Ϊ�����ʦ (0��1)");//������������û������ʦ�Ƿ�����
		newDish.chefIsExcellent = atoi(buffer);//��������ַ���ת��Ϊ����ֵ��1��ʾ���㣬0��ʾ������

		if (ListModify(L, input, newDish) == OK) {//�����޸������еĲ�Ʒ��Ϣ
			HWND hwndInput2 = GetHWnd();//��ȡ��ǰ���ھ��
			MessageBox(hwndInput2, "��Ʒ�޸ĳɹ���", "��ʾ", MB_OK);//������Ϣ����ʾ�޸ĳɹ�
		}
		else {
			HWND hwndInput2 = GetHWnd();//��ȡ��ǰ���ھ��
			MessageBox(hwndInput2, "��Ʒ�޸�ʧ�ܣ�", "��ʾ", MB_OK);//������Ϣ����ʾ�޸�ʧ��
		}
	}
}
//��ѯ��Ʒ
void Checkdish()
{
	char input[50];
	InputBox(input, 50, "������Ҫ��ѯ�Ĳ�Ʒ����");//������������û�����Ҫ��ѯ�Ĳ�Ʒ����
	LNode* result = LocateElem(L, input);  //�������в���ָ����Ʒ
	std::ostringstream oss;//����һ���ַ��������ڹ�����Ϣ������
	if (result)
	{
		//����Ʒ��š���Ʒ���ơ���Ʒ�۸񡢲�Ʒ��������Ϣд���ַ�����
		oss << "���: " << result->data.id << "\n";
		oss << "����: " << result->data.name << "\n";
		oss << "�۸�: " << result->data.price << "\n";
		oss << "����: " << result->data.sales << "\n";
		oss << "ʳ��: " << result->data.canteen << "\n";
		oss << "��ʦ: " << result->data.chefName << "\n";
		oss << "�����ʦ: " << (result->data.chefIsExcellent ? "��" : "��") << "\n";
		MessageBox(GetHWnd(), oss.str().c_str(), "��ѯ���", MB_OK);//������Ϣ����ʾ��ѯ���
	}
	else
	{
		MessageBox(GetHWnd(), "δ�ҵ��ò�Ʒ", "��ѯ���", MB_OK);//������Ϣ����ʾδ�ҵ��ò�Ʒ
	}
}

//�����񵥽���
void Sortdish()
{
	ListSort(L); //�������������
	WriteToFile(L, "file\\dishes.txt"); //������д���ļ�
	printmenu();   //��ӡ�˵�

}


/********************************
		   �˳�����
********************************/
void Thanksface()
{
	IMAGE img;
	initgraph(800, 450);//�˳����ڴ�С
	loadimage(&img, _T("photo\\byebye.png"), 800, 450);//����ͼƬ���ߣ���������
	putimage(0, 0, &img);//ͼƬ��ʾ��λ��
	HWND hwnd;// ���ô��ھ���������洰����Ϣ
	hwnd = GetHWnd();// ��ȡ���ھ��
	setWindowPosition(hwnd);//���ô���λ��
	SetWindowText(hwnd, _T("��лʹ�����ǵ�ϵͳ��"));//���ô��ڱ���
	Sleep(6000); //������ͣ6��
	closegraph(); //�ر�ͼ�ν���
}

/********************************
   ϵͳ��ˣ�������洢���ݣ�
********************************/

// ��ʼ��
Status InitList(LinkList& L)
{
	L = new LNode; //�����½ڵ���Ϊ����ͷ
	L->next = NULL;//����ͷ�ڵ����һ��ָ��Ϊ��
	return OK;
}


// �������������½ڵ�
Status ListInsert(LinkList& L, Dish dish)
{
	LinkList p = L;//pָ��ָ��ͷ�ڵ�
	while (p->next)   //�����ҵ�β���
	{
		p = p->next;
	}
	LinkList s = new LNode; //�����½ڵ�s
	s->data = dish; //����Ʒ��Ϣ��ֵ���½ڵ�s��������
	s->next = NULL;
	p->next = s;  //���p�������½ڵ�s
	return OK;
}

// ɾ�������� name ���Ե���ָ��ֵ�Ľڵ�
Status ListDelete(LinkList& L, const char* name)
{
	LinkList p = L;
	//���������жϸýڵ����һ�����ֵ�Ƿ�����Ҫɾ���Ľڵ�
	while (p->next && strcmp(p->next->data.name, name) != 0)
	{
		p = p->next;
	}
	if (!p->next) return ERROR;
	LinkList q = p->next;   //�ҵ���Ҫɾ���Ľڵ�
	p->next = q->next;   //����Ҫɾ���Ľڵ���������Ƴ�
	delete q;     //�ͷŽڵ��ڴ�
	return OK;
}

// ����ָ��name�Ľڵ�
LNode* LocateElem(LinkList L, const char* name)
{
	LinkList p = L->next;
	while (p && strcmp(p->data.name, name) != 0)  //�������ж�����ڵ��Ƿ���ڸ�ֵ
	{
		p = p->next;
	}
	return p; //�����ҵ��Ľڵ�
}

// �������򣨸��� sales �Ӵ�С����
void ListSort(LinkList& L)
{
	if (!L || !L->next || !L->next->next)
	{
		return; // �������Ϊ�ջ�ֻ��һ��Ԫ�أ���������
	}
	LNode* sorted = NULL; // ��������

	while (L->next != NULL)
	{
		// ��ԭ������ȡ�µ�һ���ڵ�
		LNode* p = L->next;
		L->next = p->next;//�Ƴ�ԭ�����еĵ�һ���ڵ�

		// ���뵽����������
		if (sorted == NULL || sorted->data.sales < p->data.sales)
		{
			// ���뵽��������Ŀ�ͷ
			p->next = sorted;
			sorted = p;
		}
		else {
			// �������������ҵ������λ��
			LNode* q = sorted;
			while (q->next != NULL && q->next->data.sales >= p->data.sales)
			{
				q = q->next;
			}
			p->next = q->next;
			q->next = p;
		}
	}
	L->next = sorted; //��������������������ԭ������
}

// �޸ģ�������ָ��name�Ľڵ����ݣ�
Status ListModify(LinkList& L, const char* name, Dish newdata)
{
	LinkList p = L->next;
	while (p != NULL)   //��������
	{
		if (strcmp(p->data.name, name) == 0)   //�ж�����ڵ��Ƿ���ڸ�ֵ
		{
			p->data = newdata;         //���ھ��޸ĸ�ֵΪnewdata
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}

// ���ļ���ȡ��������
Status ReadFromFile(LinkList& L, const char* filename)
{
	ifstream inFile(filename); //���ļ�
	if (!inFile)
	{
		cerr << "�ļ���ʧ�ܣ�" << endl;
		return ERROR;
	}
	//��ȡ�ļ��е�ÿ�����ݣ�������洢��������
	Dish dish;
	while (inFile >> dish.id >> dish.name >> dish.price >> dish.sales >> dish.canteen >> dish.chefName >> dish.chefIsExcellent)
	{
		ListInsert(L, dish); //����ȡ�������ݲ��뵽������
	}
	inFile.close(); //�ر��ļ�
	return OK;
}

// ����������д���ļ�
Status WriteToFile(LinkList& L, const char* filename)
{
	ofstream outFile(filename); //���ļ�
	if (!outFile) {
		cout << "�ļ���ʧ�ܣ�" << endl;
		return ERROR;
	}
	//��������������д���ļ�
	LinkList p = L->next;
	while (p) {
		outFile << p->data.id << " " << p->data.name << " " << p->data.price << " " << p->data.sales << " "
			<< p->data.canteen << " " << p->data.chefName << " " << p->data.chefIsExcellent << endl;//��ÿ���ڵ������д���ļ���ÿ���ֶ�֮���ÿո�ָ�
		p = p->next;
	}
	outFile.close();   //�ر��ļ������д��
	return OK;
}