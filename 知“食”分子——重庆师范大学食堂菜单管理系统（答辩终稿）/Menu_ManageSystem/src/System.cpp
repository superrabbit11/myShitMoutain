#include"Mywidget.h"
#include"Statement.h"
using namespace std;

int main()
{
	InitList(L);
	InitList(L1);
	ReadFromFile(L, "file\\dishes.txt");
	ReadFromFile(L1, "file\\bill.txt");

	// 循环播放音乐
	mciSendString(_T("open \"music\\music.mp3\" type mpegvideo alias music"), NULL, 0, NULL);
	mciSendString(_T("play music repeat"), NULL, 0, NULL);

	WelcomeInterface();
	LoginInterface();
	cout << "系统演示完毕！";

	mciSendString(_T("close music"), NULL, 0, NULL);

	return 0;
}

/********************************
		   欢迎界面
********************************/
void WelcomeInterface()
{
	IMAGE img;
	initgraph(800, 450);//欢迎窗口大小
	loadimage(&img, _T("photo\\welcome.png"), 800, 450);//设置图片宽、高，填满窗口
	putimage(0, 0, &img);//图片显示的位置
	HWND hwnd;// 设置窗口句柄变量保存窗口信息
	hwnd = GetHWnd();// 获取窗口句柄
	setWindowPosition(hwnd); //设置窗口位置
	SetWindowText(hwnd, _T("欢迎使用我们的系统！")); //设置窗口标题
	Sleep(3000);     //程序暂停3秒
	closegraph();   //关闭图形页面
}



/********************************
		   登录界面
********************************/
void LoginInterface()
{
	// 初始化窗口大小
	initgraph(1280, 720);
	IMAGE img;

	// 加载图片并设置宽高填满窗口
	loadimage(&img, _T("photo\\login.png"), 1280, 720);
	putimage(0, 0, &img); // 显示图片的位置

	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	setWindowPosition(hwnd);//设置窗口位置
	SetWindowText(hwnd, _T("知“食”分子——重庆师范大学食堂菜单管理系统"));//设置窗口标题

	// 创建按钮
	createButton(_T("customerlogin"), 640, 100, 420, 210, _T("顾客登录"), 100, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("adminlogin"), 640, 410, 420, 210, _T("管理员登录"), 100, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));

	BeginBatchDraw();//开始批量绘制

	while (1) {
		cleardevice();//清除设备
		drawButtons(img);//绘制按钮
		EndBatchDraw();//结束批量绘制

		MOUSEMSG msg = GetMouseMsg();
		msg = GetMouseMsg();// 获取鼠标消息
		if (isButtonClicked(buttonsMap[_T("customerlogin")]) == 1)
		{
			//顾客登录

			setbkcolor(WHITE);//设置背景颜色为白色

			char Customeraccount[] = "Customer";//顾客账号
			char Customerpassword[] = "123456";//顾客密码

			// 显示输入框
			char inputAccont[100];
			char inputPassword[100];
			//显示输入框并获取输入的账号
			InputBox(inputAccont, 20, "账号验证", "请输入账号（默认为Customer）：", "你只能输入默认账号啦，哈哈", 0, 0, false);

			// 检查账号
			if (strcmp(inputAccont, Customeraccount) == 0)//若输入账号与顾客账号相同
			{
				cleardevice();//清除设备上的内容
				drawButtons(img);//重新绘制按钮
				BeginBatchDraw();//开始批量绘制
				EndBatchDraw();//结束批量绘制
				MessageBox(hwnd, "存在该账号！", "账号验证", MB_OK | MB_ICONINFORMATION);//弹出提示框
				//显示输入框并获取输入的密码
				InputBox(inputPassword, 20, "密码验证", "请输入账号（默认为123456）：", "输入默认账号啦也就只能输入默认密码啦，哈哈", 0, 0, false);

				// 检查密码
				if (strcmp(inputPassword, Customerpassword) == 0)//若输入密码与顾客密码相同
				{
					MessageBox(hwnd, "密码正确！", "密码验证", MB_OK | MB_ICONINFORMATION);
					// 删除按钮，关闭窗口，跳转到主页面
					auto d1 = buttonsMap.find("customerlogin"); //查找顾客登录按钮
					auto d2 = buttonsMap.find("adminlogin"); //查找管理员登录按钮
					if (d1 != buttonsMap.end() && d2 != buttonsMap.end()) //如果找到这两个按钮
					{
						buttonsMap.erase(d1);//删除顾客登录按钮
						buttonsMap.erase(d2);//删除管理员登录按钮
					}
					//清空设备
					cleardevice();
					//关闭图形界面
					closegraph();
					//跳转到主页面
					Customermainface();
				}
				else
				{
					MessageBox(hwnd, "密码错误！", "密码验证", MB_OK | MB_ICONERROR);//弹出提示框
					continue;
				}
				break;
			}
			else
			{
				MessageBox(hwnd, "不存在该账号，请重新输入", "账号验证", MB_OK | MB_ICONERROR);//弹出提示框
				break;
			}
		}
		else if (isButtonClicked(buttonsMap[_T("adminlogin")]) == 1)
		{
			//管理员登录

			setbkcolor(WHITE);//设置背景颜色为白色

			//顾客的默认账号和密码
			char Customeraccount[] = "Admin";
			char Customerpassword[] = "123456";
			// 显示输入框用于输入账号
			char inputAccont[100];
			char inputPassword[100];
			InputBox(inputAccont, 20, "账号验证", "请输入账号（默认为Admin）：", "你只能输入默认账号啦，哈哈", 0, 0, false);

			// 检查输入的账号是否与顾客的默认账号匹配
			if (strcmp(inputAccont, Customeraccount) == 0)
			{
				cleardevice();//清除设备上的内容
				drawButtons(img);//重新绘制按钮
				BeginBatchDraw();//开始批量绘制
				EndBatchDraw();//结束批量绘制
				MessageBox(hwnd, "存在该账号！", "账号验证", MB_OK | MB_ICONINFORMATION);//显示消息框，告知用户账号存在
				InputBox(inputPassword, 20, "密码验证", "请输入账号（默认为123456）：", "输入默认账号啦也就只能输入默认密码啦，哈哈", 0, 0, false);

				// 检查输入的密码是否与顾客的默认密码匹配
				if (strcmp(inputPassword, Customerpassword) == 0)
				{
					MessageBox(hwnd, "密码正确！", "密码验证", MB_OK | MB_ICONINFORMATION);

					// 删除按钮，关闭窗口，跳转到主页面
					auto d1 = buttonsMap.find("customerlogin");
					auto d2 = buttonsMap.find("adminlogin");
					if (d1 != buttonsMap.end() && d2 != buttonsMap.end())
					{
						buttonsMap.erase(d1);
						buttonsMap.erase(d2);
					}
					//清空设备
					cleardevice();
					//关闭图形界面
					closegraph();
					//跳转到管理员界面
					Adminmainface();
				}
				else
				{
					MessageBox(hwnd, "密码错误！", "密码验证", MB_OK | MB_ICONERROR);//显示消息框，告知用户密码错误
					continue;
				}
				break;
			}
			else
			{
				MessageBox(hwnd, "不存在该账号，请重新输入", "账号验证", MB_OK | MB_ICONERROR);//显示消息框，告知用户账号不存在
				continue;
			}
		}
	}

	FlushBatchDraw();//刷新批量绘制的内容（确保所有绘制操作都显示在界面上）
	Sleep(30);//暂停30毫秒
}


/********************************
		   系统顾客端
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
	SetWindowText(hwnd, _T("知“食”分子——重庆师范大学食堂菜单管理系统(顾客端)"));

	createButton(_T("ordermenu"), 530, 300, 210, 80, _T("查看菜单"), 50, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("order"), 530, 405, 210, 80, _T("点餐"), 50, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("consume"), 530, 510, 210, 80, _T("消费情况"), 50, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("exit"), 530, 615, 210, 80, _T("退出程序"), 50, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));

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
	SetWindowText(hwnd1, _T("知“食”分子——重庆师范大学食堂菜单管理系统(顾客端)"));

	setbkmode(OPAQUE);
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("思源黑体"));
	outtextxy(40, 100, _T("编号"));
	outtextxy(170, 100, _T("菜名"));
	outtextxy(300, 100, _T("价格"));
	outtextxy(470, 100, _T("销量"));
	outtextxy(600, 100, _T("所属食堂"));
	outtextxy(830, 100, _T("厨师"));
	outtextxy(960, 100, _T("是否为“优秀厨师”"));

	// 绘制菜单内容
	LinkList p = L->next;
	int y = 150;
	while (p) {
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(30, 0, _T("思源黑体"));

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

	// 绘制按钮文本
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("思源黑体"));
	outtextxy(1125, 635, _T("返回"));

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
//点餐功能
void Order(IMAGE& img)
{
	// 新增消费记录
	Dish newDish;
	char inputBuffer[50];

	// 输入名称并检查重复
	while (true)
	{
		InputBox(newDish.name, 50, "请输入所需菜品的名称");
		if (!IsDishNameDuplicate(L, newDish.name))
		{
			HWND hwndInput1 = GetHWnd();
			MessageBox(hwndInput1, "该菜品不存在！请重新输入", "提示", MB_OK);
		}
		else
		{
			break;
		}
	}

	// 输入编号
	InputBox(inputBuffer, 10, "请输入购买菜品的日期（案例：240601）");
	newDish.id = atoi(inputBuffer);

	// 输入价格
	InputBox(inputBuffer, 10, "请输入所需菜品的价格");
	newDish.price = atof(inputBuffer);

	InputBox(inputBuffer, 10, "请输入购买菜品的份数");
	newDish.sales = atof(inputBuffer);
	//保证管理员端销量数据更新
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

	// 输入食堂
	InputBox(newDish.canteen, 50, "请输入新增菜品所属食堂");

	// 输入厨师名称
	InputBox(newDish.chefName, 50, "请输入制作菜品的厨师名称");

	// 输入菜品是否好吃
	InputBox(inputBuffer, 10, "请问菜品好吃吗（1表示是，0表示否）");
	newDish.chefIsExcellent = (atoi(inputBuffer) == 1);

	// 插入链表
	ListInsert(L1, newDish);
	WriteToFile(L1, "file\\bill.txt");
	WriteToFile(L, "file\\dishes.txt");

	HWND hwnd = GetHWnd();
	MessageBox(hwnd, "点菜成功！", "提示", MB_OK);

	// 清屏并重新绘制之前的内容
	cleardevice();
	putimage(0, 0, &img);

}

//消费情况界面
void Consumeface()
{
	initgraph(1280, 720);
	cleardevice();
	IMAGE img;

	loadimage(&img, _T("photo\\window.png"), 1280, 720);
	putimage(0, 0, &img);

	HWND hwnd1 = GetHWnd();
	setWindowPosition(hwnd1);
	SetWindowText(hwnd1, _T("知“食”分子——重庆师范大学食堂菜单管理系统(顾客端)"));

	setbkmode(OPAQUE);
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("思源黑体"));
	outtextxy(40, 100, _T("日期"));
	outtextxy(170, 100, _T("菜名"));
	outtextxy(300, 100, _T("价格"));
	outtextxy(470, 100, _T("购买份数"));
	outtextxy(600, 100, _T("所属食堂"));
	outtextxy(830, 100, _T("厨师"));
	outtextxy(960, 100, _T("是否好吃"));

	// 绘制菜单内容
	LinkList p = L1->next;
	int y = 150;
	while (p) {
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(30, 0, _T("思源黑体"));

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

	// 绘制按钮文本
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("思源黑体"));
	outtextxy(1125, 635, _T("返回"));

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
		   系统管理员端
********************************/
//主界面
void Adminmainface()
{
	/*cleardevice();
	Sleep(10);
	closegraph();*/

	// 初始化窗口大小
	initgraph(1280, 720);
	cleardevice();
	IMAGE img;

	// 加载图片并设置宽高填满窗口
	loadimage(&img, _T("photo\\admin.png"), 1280, 720);
	putimage(0, 0, &img); // 显示图片的位置

	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	setWindowPosition(hwnd);
	SetWindowText(hwnd, _T("知“食”分子——重庆师范大学食堂菜单管理系统(管理员端)"));//设置窗口标题

	// 创建按钮
	createButton(_T("add"), 530, 300, 210, 60, _T("新增菜品"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("delete"), 530, 370, 210, 60, _T("删除菜品"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("change"), 530, 440, 210, 60, _T("信息修改"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("check"), 530, 510, 210, 60, _T("信息查询"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("sort"), 530, 580, 210, 60, _T("销量榜单"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));
	createButton(_T("exit"), 530, 650, 210, 60, _T("退出程序"), 40, WHITE, BLACK, RGB(72, 116, 203), RGB(0, 32, 96));

	BeginBatchDraw();//批量绘制

	while (1) {
		cleardevice();
		drawButtons(img);

		MOUSEMSG msg = GetMouseMsg();
		msg = GetMouseMsg();// 获取鼠标消息
		if (isButtonClicked(buttonsMap[_T("add")]) == 1) {//如果新增菜品按钮被点击
			cleardevice();//清空设备
			drawButtons(img);//绘制按钮
			BeginBatchDraw();//开始批量绘制
			EndBatchDraw();//结束批量绘制
			Adddish();//调用新增菜品函数
		}
		else if (isButtonClicked(buttonsMap[_T("delete")]) == 1)//如果删除菜品按钮被点击
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Deletedish();//调用删除菜品函数
		}
		else if (isButtonClicked(buttonsMap[_T("change")]) == 1)//如果信息修改按钮被点击
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Changedish();//调用信息修改函数
		}
		else if (isButtonClicked(buttonsMap[_T("check")]) == 1)//如果信息查询按钮被点击
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Checkdish();//调用信息查询函数

		}
		else if (isButtonClicked(buttonsMap[_T("sort")]) == 1)//如果销量榜单按钮被点击
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Sortdish();//调用销量榜单函数
		}
		else if (isButtonClicked(buttonsMap[_T("exit")]) == 1)//如果退出程序按钮被点击
		{
			cleardevice();
			drawButtons(img);
			BeginBatchDraw();
			EndBatchDraw();
			Thanksface();//调用退出程序函数
		}
	}

	FlushBatchDraw();
	Sleep(30);
}
//打印菜单
void printmenu()
{
	// 初始化窗口大小
	initgraph(1280, 720);
	cleardevice();
	IMAGE img;

	// 加载图片并设置宽高填满窗口
	loadimage(&img, _T("photo\\window.png"), 1280, 720);
	putimage(0, 0, &img); // 显示图片的位置

	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	setWindowPosition(hwnd);//设置窗口位置
	SetWindowText(hwnd, _T("知“食”分子——重庆师范大学食堂菜单管理系统(管理员端)"));//设置窗口标题

	setbkmode(OPAQUE); // 设置字体背景模式为不透明
	setbkcolor(BLACK); // 设置背景颜色为黑色
	settextcolor(WHITE); // 设置字体颜色为白色
	settextstyle(50, 0, "思源黑体");//设置字体样式和大小
	outtextxy(40, 100, "编号");//打印标号标题
	outtextxy(170, 100, "菜名");//打印菜名标题
	outtextxy(300, 100, "价格");//打印价格标题
	outtextxy(470, 100, "销量");//打印销量标题
	outtextxy(600, 100, "所属食堂");//打印所属食堂标题
	outtextxy(830, 100, "厨师");//打印厨师标题
	outtextxy(960, 100, "是否为“优秀厨师”");//打印是否为“优秀厨师”标题

	LinkList p = L->next;//获取链表中的第一个菜品的指针
	int y = 150; // 初始 y 坐标，用于在屏幕上垂直打印菜品信息
	while (p) //遍历链表
	{
		setbkmode(TRANSPARENT);
		settextcolor(BLACK); // 设置字体颜色为黑色
		settextstyle(30, 0, "思源黑体"); //设置字体样式

		char buffer[50];
		// 将整型和浮点型转换为字符串，并调用outtextxy函数在置顶位置输出
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
		y += 20; //增加 y 坐标，换行显示
		p = p->next;
	}
	setfillcolor(WHITE); //设置填充颜色为白色
	fillrectangle(300, 380, 380, 410); //绘制一个矩形框
	while (1) {
		ExMessage m2 = getmessage();

		if (m2.x > 300 && m2.x < 380 && m2.y>380 && m2.y < 410) { //判断用户点击位置是否在矩形框内
			setlinecolor(RED);  //在则设置线框颜色为红色
			rectangle(300, 380, 380, 410);
		}
		else {
			setlinecolor(WHITE);  //不在则设置线框颜色为白色
			rectangle(300, 380, 380, 410);
		}
		if (m2.message == WM_LBUTTONDOWN) { //若用户按下鼠标左键
			Adminmainface(); //进入管理人员主界面
		}
	}
}
//新增菜品功能
bool IsDishNameDuplicate(LinkList L, const char* name)
{
	// 检查是否存在该菜品（有返回1，无返回0）
	LinkList p = L->next;
	while (p) {
		//判断是否有与输入名称相同的菜品
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
	// 新增菜品
	Dish newDish;
	char inputBuffer[50];
	// 输入名称并检查重复
	while (true)
	{
		InputBox(newDish.name, 50, "请输入新增菜品的名称");//弹出输入框让用户输入菜品名称
		if (IsDishNameDuplicate(L, newDish.name)) //检查链表中是否已有相同名称的菜品
		{
			HWND hwndInput1 = GetHWnd();//获得当前窗口句柄
			MessageBox(hwndInput1, "该菜品已经存在，请重新输入", "提示", MB_OK);//弹出消息框
		}
		else
		{
			break;//如果菜品名不存在，跳出循环
		}
	}

	// 输入编号
	InputBox(inputBuffer, 10, "请输入新增菜品的编号");//弹出输入框让用户输入菜品编号
	newDish.id = atoi(inputBuffer);//将输入的字符串转换为整型编号


	// 输入价格
	InputBox(inputBuffer, 10, "请输入新增菜品的价格");//弹出输入框让用户输入菜品价格
	newDish.price = atof(inputBuffer);//将输入的字符串转换为浮点型价格

	// 默认销量为0
	newDish.sales = 0;

	// 输入食堂
	InputBox(newDish.canteen, 50, "请输入新增菜品所属食堂");//弹出输入框让用户输入菜品所属食堂

	// 输入厨师姓名
	InputBox(newDish.chefName, 50, "请输入制作菜品的厨师名称");//弹出输入框让用户输入制作菜品的厨师姓名

	// 输入厨师是否优秀
	InputBox(inputBuffer, 10, "请输入厨师是否优秀（1表示是，0表示否）");//弹出输入框让用户输入厨师是否优秀
	newDish.chefIsExcellent = (atoi(inputBuffer) == 1);//将输入的字符串转换为布尔值

	// 将新菜插入链表
	ListInsert(L, newDish);//将新菜品插入链表中
	WriteToFile(L, "file\\dishes.txt");  //将链表写入文件
	printmenu();  //打印菜单

}
//删除菜品
void Deletedish()
{
	char input[50];
	InputBox(input, 50, "请输入要删除的菜品名称");//弹出输入框让用户输入要删除的菜品名称
	if (IsDishNameDuplicate(L, input) == 0) //判断菜品是否存在
	{
		HWND hwndInput1 = GetHWnd();//获取当前窗口句柄
		MessageBox(hwndInput1, "该菜品不存在！请重新输入", "提示", MB_OK);//弹出消息框提示菜品不存在
	}
	ListDelete(L, input); //从链表中删除指定菜品
	WriteToFile(L, "file\\dishes.txt"); //将链表写入文件
	HWND hwnd = GetHWnd();//获取当前窗口句柄
	MessageBox(hwnd, "删除成功！", "提示", MB_OK);//弹出消息框提示删除成功

}
//修改菜品
void Changedish() {
	char input[50];
	InputBox(input, 50, "请输入要修改的菜品名称");//弹出消息框提示要修改的菜品名称
	if (!IsDishNameDuplicate(L, input)) { //判断菜品是否存在
		HWND hwndInput1 = GetHWnd();//获取当前窗口句柄
		MessageBox(hwndInput1, "该菜品不存在！请重新输入", "提示", MB_OK);//弹出消息框提示菜品不存在
	}
	else {
		Dish newDish;
		InputBox(newDish.name, 50, "请输入新的菜品名称");//弹出输入框让用户输入新的菜品名称
		char buffer[50];

		InputBox(buffer, 50, "请输入新的菜品编号");//弹出输入框让用户输入新的菜品编号
		newDish.id = atoi(buffer);//将输入的字符串转换为整型编号

		InputBox(buffer, 50, "请输入新的菜品价格");//弹出输入框让用户输入菜品价格
		newDish.price = atof(buffer);//将输入的字符串转换为浮点型价格

		InputBox(buffer, 50, "请输入新的菜品销量");//弹出输入框让用户输入菜品销量
		newDish.sales = atoi(buffer);//将输入的字符串转换为整型销量

		InputBox(newDish.canteen, 50, "请输入新的菜品所属食堂");//弹出输入框让用户输入菜品所属食堂
		InputBox(newDish.chefName, 50, "请输入新的制作菜品的厨师名称");//弹出输入框让用户输入制作菜品的厨师姓名

		InputBox(buffer, 50, "请输入新的厨师是否为优秀厨师 (0或1)");//弹出输入框让用户输入厨师是否优秀
		newDish.chefIsExcellent = atoi(buffer);//将输入的字符串转换为布尔值，1表示优秀，0表示不优秀

		if (ListModify(L, input, newDish) == OK) {//尝试修改链表中的菜品信息
			HWND hwndInput2 = GetHWnd();//获取当前窗口句柄
			MessageBox(hwndInput2, "菜品修改成功！", "提示", MB_OK);//弹出消息框提示修改成功
		}
		else {
			HWND hwndInput2 = GetHWnd();//获取当前窗口句柄
			MessageBox(hwndInput2, "菜品修改失败！", "提示", MB_OK);//弹出消息框提示修改失败
		}
	}
}
//查询菜品
void Checkdish()
{
	char input[50];
	InputBox(input, 50, "请输入要查询的菜品名称");//弹出输入框让用户输入要查询的菜品名称
	LNode* result = LocateElem(L, input);  //在链表中查找指定菜品
	std::ostringstream oss;//创建一个字符串流用于构建消息框内容
	if (result)
	{
		//将菜品编号、菜品名称、菜品价格、菜品销量等信息写入字符串流
		oss << "编号: " << result->data.id << "\n";
		oss << "名称: " << result->data.name << "\n";
		oss << "价格: " << result->data.price << "\n";
		oss << "销量: " << result->data.sales << "\n";
		oss << "食堂: " << result->data.canteen << "\n";
		oss << "厨师: " << result->data.chefName << "\n";
		oss << "优秀厨师: " << (result->data.chefIsExcellent ? "是" : "否") << "\n";
		MessageBox(GetHWnd(), oss.str().c_str(), "查询结果", MB_OK);//弹出消息框显示查询结果
	}
	else
	{
		MessageBox(GetHWnd(), "未找到该菜品", "查询结果", MB_OK);//弹出消息框提示未找到该菜品
	}
}

//销量榜单界面
void Sortdish()
{
	ListSort(L); //对链表进行排序
	WriteToFile(L, "file\\dishes.txt"); //将链表写入文件
	printmenu();   //打印菜单

}


/********************************
		   退出界面
********************************/
void Thanksface()
{
	IMAGE img;
	initgraph(800, 450);//退出窗口大小
	loadimage(&img, _T("photo\\byebye.png"), 800, 450);//设置图片宽、高，填满窗口
	putimage(0, 0, &img);//图片显示的位置
	HWND hwnd;// 设置窗口句柄变量保存窗口信息
	hwnd = GetHWnd();// 获取窗口句柄
	setWindowPosition(hwnd);//设置窗口位置
	SetWindowText(hwnd, _T("感谢使用我们的系统！"));//设置窗口标题
	Sleep(6000); //程序暂停6秒
	closegraph(); //关闭图形界面
}

/********************************
   系统后端（用链表存储数据）
********************************/

// 初始化
Status InitList(LinkList& L)
{
	L = new LNode; //创建新节点作为链表头
	L->next = NULL;//设置头节点的下一个指针为空
	return OK;
}


// 在链表最后插入新节点
Status ListInsert(LinkList& L, Dish dish)
{
	LinkList p = L;//p指针指向头节点
	while (p->next)   //遍历找到尾结点
	{
		p = p->next;
	}
	LinkList s = new LNode; //创建新节点s
	s->data = dish; //将菜品信息赋值给新节点s的数据域
	s->next = NULL;
	p->next = s;  //结点p向后插入新节点s
	return OK;
}

// 删除链表中 name 属性等于指定值的节点
Status ListDelete(LinkList& L, const char* name)
{
	LinkList p = L;
	//遍历链表，判断该节点的下一个结点值是否是需要删除的节点
	while (p->next && strcmp(p->next->data.name, name) != 0)
	{
		p = p->next;
	}
	if (!p->next) return ERROR;
	LinkList q = p->next;   //找到需要删除的节点
	p->next = q->next;   //将需要删除的节点从链表中移除
	delete q;     //释放节点内存
	return OK;
}

// 查找指定name的节点
LNode* LocateElem(LinkList L, const char* name)
{
	LinkList p = L->next;
	while (p && strcmp(p->data.name, name) != 0)  //遍历并判断链表节点是否存在该值
	{
		p = p->next;
	}
	return p; //返回找到的节点
}

// 插入排序（根据 sales 从大到小排序）
void ListSort(LinkList& L)
{
	if (!L || !L->next || !L->next->next)
	{
		return; // 如果链表为空或只有一个元素，无需排序
	}
	LNode* sorted = NULL; // 有序链表

	while (L->next != NULL)
	{
		// 从原链表中取下第一个节点
		LNode* p = L->next;
		L->next = p->next;//移除原链表中的第一个节点

		// 插入到有序链表中
		if (sorted == NULL || sorted->data.sales < p->data.sales)
		{
			// 插入到有序链表的开头
			p->next = sorted;
			sorted = p;
		}
		else {
			// 在有序链表中找到插入的位置
			LNode* q = sorted;
			while (q->next != NULL && q->next->data.sales >= p->data.sales)
			{
				q = q->next;
			}
			p->next = q->next;
			q->next = p;
		}
	}
	L->next = sorted; //将排序后的链表重新连接原链表上
}

// 修改（链表中指定name的节点数据）
Status ListModify(LinkList& L, const char* name, Dish newdata)
{
	LinkList p = L->next;
	while (p != NULL)   //遍历链表
	{
		if (strcmp(p->data.name, name) == 0)   //判断链表节点是否存在该值
		{
			p->data = newdata;         //存在就修改该值为newdata
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}

// 从文件读取链表数据
Status ReadFromFile(LinkList& L, const char* filename)
{
	ifstream inFile(filename); //打开文件
	if (!inFile)
	{
		cerr << "文件打开失败！" << endl;
		return ERROR;
	}
	//读取文件中的每个数据，并将其存储在链表中
	Dish dish;
	while (inFile >> dish.id >> dish.name >> dish.price >> dish.sales >> dish.canteen >> dish.chefName >> dish.chefIsExcellent)
	{
		ListInsert(L, dish); //将读取到的数据插入到链表中
	}
	inFile.close(); //关闭文件
	return OK;
}

// 将链表数据写入文件
Status WriteToFile(LinkList& L, const char* filename)
{
	ofstream outFile(filename); //打开文件
	if (!outFile) {
		cout << "文件打开失败！" << endl;
		return ERROR;
	}
	//遍历链表并将数据写入文件
	LinkList p = L->next;
	while (p) {
		outFile << p->data.id << " " << p->data.name << " " << p->data.price << " " << p->data.sales << " "
			<< p->data.canteen << " " << p->data.chefName << " " << p->data.chefIsExcellent << endl;//将每个节点的数据写入文件，每个字段之间用空格分隔
		p = p->next;
	}
	outFile.close();   //关闭文件，完成写入
	return OK;
}