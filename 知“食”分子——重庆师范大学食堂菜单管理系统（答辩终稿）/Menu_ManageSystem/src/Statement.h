#ifndef STATEMENT_H
#define STATEMENT_H
#define OK 1 
#define ERROR 0 

typedef int Status;
typedef int ElemType;

struct Dish
{
	int id;                     // 编号
	char name[200];              // 名称
	double price;               // 价格
	int sales;                  // 销量
	char canteen[200];           // 菜品所属食堂
	char chefName[200];          // 制作菜品的厨师名称
	bool chefIsExcellent;       // 这个厨师是否是优秀厨师
};

//链表定义
typedef struct LNode
{
	Dish data;
	struct LNode* next;
} LNode, * LinkList;

LinkList L;
LinkList L1;

bool IsDishNameDuplicate(LinkList L, const char* name);

//欢迎界面
void WelcomeInterface();

//登录界面
void LoginInterface();

/*顾客端*/
void Customermainface();//主界面
void printdish();
void Order(IMAGE& img);//点餐界面
void Consumeface();//查看消费情况界面

/*管理员*/
void Adminmainface();//主界面
void printmenu();
void Adddish();
void Deletedish();
void Changedish();
void Checkdish();
void Sortdish();

//退出页面
void Thanksface();

//系统后端（用链表存储）
Status InitList(LinkList& L);
Status ListInsert(LinkList& L, Dish dish);
Status ListDelete(LinkList& L, const char* name);
LNode* LocateElem(LinkList L, const char* name);
void ListSort(LinkList& L);
Status ListModify(LinkList& L, const char* name, Dish newdata);
Status ReadFromFile(LinkList& L, const char* filename);
Status WriteToFile(LinkList& L, const char* filename);

#endif
