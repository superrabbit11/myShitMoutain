#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define ENDFLAG 99999  // 定义结束标志，用于手动插入数据时的输入结束

typedef int KeyType; // 定义关键字类型为整型

typedef struct BSTNode {
    KeyType key; // 每个节点的关键字
    struct BSTNode* lchild, * rchild; // 左右孩子指针
} BSTNode, * BSTree;

// 插入节点到二叉排序树中
void InsertBST(BSTree& T, KeyType key);
// 中序遍历二叉排序树
void InOrderTraverse(BSTree T);
// 在二叉排序树中查找关键字为key的结点
BSTree SearchBST(BSTree T, KeyType key);
// 删除二叉排序树中的结点
void DeleteBST(BSTree& T, KeyType key);
// 输出所有大于等于给定x值的结点数据
void PrintGreaterOrEqual(BSTree T, KeyType x);
// 将二叉排序树保存到文件中
void SaveToFile(BSTree T, ofstream& fout);
// 从文件中加载二叉排序树
void LoadFromFile(BSTree& T, ifstream& fin);
// 计算二叉排序树的深度
int CalculateDepth(BSTree T);
// 计算二叉排序树的平均查找长度（APL）
double CalculateAPL(BSTree T);
// 辅助函数：计算APL并打印详细过程
void CalculateAPLAndPrint(BSTree T, int depth, int& totalDepth, int& nodeCount, KeyType* keysVisited);
// 显示菜单
void ShowMenu();

// 通过数据创建平衡的二叉排序树
BSTree CreateBalancedBST(KeyType* data, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    BSTree node = new BSTNode();
    node->key = data[mid];
    node->lchild = CreateBalancedBST(data, start, mid - 1);
    node->rchild = CreateBalancedBST(data, mid + 1, end);
    return node;
}

// 从文件中加载并创建二叉排序树
void LoadAndCreateBST(BSTree& T, const string& filename) {
    ifstream fin(filename);  // 打开文件流，准备从文件中读取数据
    if (fin.is_open()) {  // 如果文件成功打开
        KeyType data[100]; // 假设最多存储100个数据
        int index = 0;  // 数据索引

        // 从文件中读取数据直到文件末尾
        while (fin >> data[index]) {
            index++;
        }
        fin.close();  // 关闭文件流

        if (index > 0) {  // 如果文件中有数据
            // 对读取的数据进行排序
            sort(data, data + index);
            T = CreateBalancedBST(data, 0, index - 1);  // 创建平衡的二叉排序树
            cout << "从文件加载成功！" << endl;  // 输出加载成功消息
        }
        else {  // 如果文件中没有数据
            cout << "文件中没有数据。" << endl;  // 输出文件无数据消息
            cout << "是否手动插入数据？(y/n): ";  // 提示用户手动插入数据的选择
            char choice;  // 用户选择变量
            cin >> choice;  // 输入选择

            if (choice == 'y' || choice == 'Y') {  // 如果用户选择是
                cout << "请输入要插入的关键字（以 " << ENDFLAG << " 结束输入）：" << endl;  // 提示用户输入关键字
                KeyType key;  // 插入关键字变量
                while (true) {  // 循环读取用户输入直到结束标志
                    cin >> key;
                    if (key == ENDFLAG) break;
                    InsertBST(T, key);  // 将输入的关键字插入二叉排序树中
                }
                cout << "插入成功！" << endl;  // 输出插入成功消息
            }
        }
    }
    else {  // 如果文件打开失败
        cout << "无法打开文件 " << filename << endl;  // 输出无法打开文件消息
    }
}

// 中序遍历二叉排序树
void InOrderTraverse(BSTree T) {
    if (T != NULL) {  // 如果树非空
        InOrderTraverse(T->lchild);  // 遍历左子树
        cout << T->key << " ";  // 输出当前节点的关键字
        InOrderTraverse(T->rchild);  // 遍历右子树
    }
}

// 查找结点
BSTree SearchBST(BSTree T, KeyType key) {
    if (!T || key == T->key) return T;  // 如果树为空或者找到目标节点，返回该节点
    else if (key < T->key) return SearchBST(T->lchild, key);  // 如果目标值小于当前节点值，在左子树中查找
    else return SearchBST(T->rchild, key);  // 如果目标值大于当前节点值，在右子树中查找
}

// 插入结点
void InsertBST(BSTree& T, KeyType key) {
    if (!T) {  // 如果树为空
        BSTNode* S = new BSTNode;  // 创建新节点
        S->key = key;  // 设置节点关键字
        S->lchild = S->rchild = NULL;  // 设置左右子树为空
        T = S;  // 将新节点作为根节点
    }
    else if (key < T->key) {  // 如果插入值小于当前节点值，插入左子树
        InsertBST(T->lchild, key);
    }
    else {  // 如果插入值大于等于当前节点值，插入右子树
        InsertBST(T->rchild, key);
    }
}

// 删除结点
void DeleteBST(BSTree& T, KeyType key) {
    BSTNode* p = T;  // p指向待删除节点
    BSTNode* f = NULL;  // f指向p的父节点
    while (p) {  // 找到待删除节点p和其父节点f
        if (p->key == key)
            break;
        f = p;
        if (p->key > key)
            p = p->lchild;
        else
            p = p->rchild;
    }
    if (!p) return;  // 如果未找到待删除节点，直接返回

    BSTNode* q = p;  // q指向实际删除的节点
    if (p->lchild && p->rchild) {  // 如果p有左右孩子
        BSTNode* s = p->lchild;  // s指向p的左孩子
        while (s->rchild) {  // 找到s的右子树的最右节点
            q = s;
            s = s->rchild;
        }
        p->key = s->key;  // 将s的值赋给p
        if (q != p)
            q->rchild = s->lchild;
        else
            q->lchild = s->lchild;
        delete s;  // 删除s节点
        return;
    }
    else if (!p->rchild) {  // 如果p没有右孩子
        p = p->lchild;  // 将p的左孩子赋给p
    }
    else if (!p->lchild) {  // 如果p没有左孩子
        p = p->rchild;  // 将p的右孩子赋给p
    }

    if (!f)  // 如果p是根节点
        T = p;  // 直接将p作为新的根节点
    else if (q == f->lchild)  // 如果p是f的左孩子
        f->lchild = p;  // 将p挂在f的左边
    else
        f->rchild = p;  // 将p挂在f的右边
    delete q;  // 删除q节点
}

// 输出所有大于等于给定x值的结点数据
void PrintGreaterOrEqual(BSTree T, KeyType x) {
    if (T != NULL) {  // 如果树非空
        PrintGreaterOrEqual(T->lchild, x);  // 遍历左子树
        if (T->key >= x) {  // 如果当前节点的值大于等于x
            cout << T->key << " ";  // 输出当前节点的值
        }
        PrintGreaterOrEqual(T->rchild, x);  // 遍历右子树
    }
}

// 将二叉排序树保存到文件中
void SaveToFile(BSTree T, ofstream& fout) {
    if (T != NULL) {  // 如果树非空
        fout << T->key << endl;  // 将当前节点的值写入文件
        SaveToFile(T->lchild, fout);  // 保存左子树
        SaveToFile(T->rchild, fout);  // 保存右子树
    }
}

// 从文件中加载二叉排序树
void LoadFromFile(BSTree& T, ifstream& fin) {
    T = NULL;  // 初始化树为空
    KeyType key;  // 用于存储从文件中读取的值
    while (fin >> key) {  // 从文件中读取值
        InsertBST(T, key);  // 插入树中
    }
}

// 计算二叉排序树的深度
int CalculateDepth(BSTree T) {
    if (T == NULL) return 0;  // 如果树为空，深度为0
    int lDepth = CalculateDepth(T->lchild);  // 计算左子树深度
    int rDepth = CalculateDepth(T->rchild);  // 计算右子树深度
    return max(lDepth, rDepth) + 1;  // 树的深度为左右子树深度的较大值加1
}

// 辅助函数：计算APL并打印详细过程
void CalculateAPLAndPrint(BSTree T, int depth, int& totalDepth, int& nodeCount, KeyType* keysVisited) {
    if (T != NULL) {  // 如果树非空
        keysVisited[nodeCount] = T->key;  // 记录访问的关键字
        totalDepth += depth;  // 累加深度
        nodeCount++;  // 结点数加1
        CalculateAPLAndPrint(T->lchild, depth + 1, totalDepth, nodeCount, keysVisited);  // 递归处理左子树
        CalculateAPLAndPrint(T->rchild, depth + 1, totalDepth, nodeCount, keysVisited);  // 递归处理右子树
    }
}

// 计算二叉排序树的平均查找长度（APL）
double CalculateAPL(BSTree T) {
    int totalDepth = 0;  // 总深度
    int nodeCount = 0;  // 结点数
    KeyType keysVisited[100];  // 记录访问的关键字
    CalculateAPLAndPrint(T, 1, totalDepth, nodeCount, keysVisited);  // 计算总深度和结点数
    double apl = (double)totalDepth / nodeCount;  // 计算平均查找长度
    cout << "节点访问顺序：";
    for (int i = 0; i < nodeCount; i++) {
        cout << keysVisited[i] << " ";  // 输出访问的关键字
    }
    cout << endl;
    cout << "总查找长度：" << totalDepth << ", 节点总数：" << nodeCount << endl;  // 输出总深度和结点数
    return apl;  // 返回平均查找长度
}

// 显示菜单
void ShowMenu() {
    cout << "================================================" << endl;
    cout << "|       ****** 二叉排序树操作 ******           |" << endl;
    cout << "================================================" << endl;
    cout << "|                                              |" << endl;
    cout << "|        1. 插入节点                           |" << endl;
    cout << "|        2. 删除节点                           |" << endl;
    cout << "|        3. 查找节点                           |" << endl;
    cout << "|        4. 输出中序遍历结果                   |" << endl;
    cout << "|        5. 输出大于等于x值的节点数据          |" << endl;
    cout << "|        6. 保存到文件                         |" << endl;
    cout << "|        7. 从文件加载                         |" << endl;
    cout << "|        8. 计算二叉排序树的深度               |" << endl;
    cout << "|        9. 计算平均查找长度（APL）            |" << endl;
    cout << "|        0. 退出程序                           |" << endl;
    cout << "|                                              |" << endl;
    cout << "================================================" << endl;
}


// 主函数
int main() {
    BSTree T = NULL;  // 初始化树为空
    int choice;  // 用户选择
    KeyType key, x;  // 关键字和给定值

    do {
        ShowMenu();  // 显示菜单
        cout << "请选择操作：";  // 提示用户选择
        cin >> choice;  // 输入选择

        switch (choice) {
        case 1:
            cout << "请输入要插入的关键字：";
            cin >> key;
            InsertBST(T, key);
            break;
        case 2:
            cout << "请输入要删除的关键字：";
            cin >> key;
            DeleteBST(T, key);
            break;
        case 3:
            cout << "请输入要查找的关键字：";
            cin >> key;
            if (SearchBST(T, key))
                cout << "找到了关键字为 " << key << " 的结点。" << endl;
            else
                cout << "没有找到关键字为 " << key << " 的结点。" << endl;
            break;
        case 4:
            InOrderTraverse(T);
            cout << endl;
            break;
        case 5:
            cout << "请输入给定值 x：";
            cin >> x;
            PrintGreaterOrEqual(T, x);
            cout << endl;
            break;
        case 6: {
            ofstream fout("bstree.txt");
            if (fout.is_open()) {
                SaveToFile(T, fout);
                fout.close();
                cout << "保存成功！" << endl;
            }
            else {
                cout << "无法打开文件保存数据。" << endl;
            }
            break;
        }
        case 7:
            LoadAndCreateBST(T, "bstree.txt");
            break;
        case 8:
            cout << "二叉排序树的深度为：" << CalculateDepth(T) << endl;
            break;
        case 9:
            cout << "平均查找长度（APL）为：" << CalculateAPL(T) << endl;
            break;
        case 0:
            cout << "退出程序。" << endl;
            break;
        default:
            cout << "无效的选择，请重新输入。" << endl;
        }
    } while (choice != 0);

    return 0;
}
