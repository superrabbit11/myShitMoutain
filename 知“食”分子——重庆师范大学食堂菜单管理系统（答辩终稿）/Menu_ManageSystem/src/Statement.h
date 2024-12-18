#ifndef STATEMENT_H
#define STATEMENT_H
#define OK 1 
#define ERROR 0 

typedef int Status;
typedef int ElemType;

struct Dish
{
	int id;                     // ���
	char name[200];              // ����
	double price;               // �۸�
	int sales;                  // ����
	char canteen[200];           // ��Ʒ����ʳ��
	char chefName[200];          // ������Ʒ�ĳ�ʦ����
	bool chefIsExcellent;       // �����ʦ�Ƿ��������ʦ
};

//������
typedef struct LNode
{
	Dish data;
	struct LNode* next;
} LNode, * LinkList;

LinkList L;
LinkList L1;

bool IsDishNameDuplicate(LinkList L, const char* name);

//��ӭ����
void WelcomeInterface();

//��¼����
void LoginInterface();

/*�˿Ͷ�*/
void Customermainface();//������
void printdish();
void Order(IMAGE& img);//��ͽ���
void Consumeface();//�鿴�����������

/*����Ա*/
void Adminmainface();//������
void printmenu();
void Adddish();
void Deletedish();
void Changedish();
void Checkdish();
void Sortdish();

//�˳�ҳ��
void Thanksface();

//ϵͳ��ˣ�������洢��
Status InitList(LinkList& L);
Status ListInsert(LinkList& L, Dish dish);
Status ListDelete(LinkList& L, const char* name);
LNode* LocateElem(LinkList L, const char* name);
void ListSort(LinkList& L);
Status ListModify(LinkList& L, const char* name, Dish newdata);
Status ReadFromFile(LinkList& L, const char* filename);
Status WriteToFile(LinkList& L, const char* filename);

#endif
