#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>

using namespace std;

const int INF = 1000000000;
const int maxBit = 1 << 5;
const int maxNode = 1 << 10;
const int maxCode = 1 << 10;

// 节点信息结构
struct Node {
    // 值
    string value;
    // 权值
    float weight;
    // 父节点
    int parent;
    // 左子节点
    int lchild;
    // 右子节点
    int rchild;
};

// 编码信息结构
struct Code {
    // 编码字符
    int bit[maxBit];
    // 开始位置
    int start;
    // 值
    string value;
};

// 节点数组
Node huffman[maxNode];
// 编码数组
Code huffmanCode[maxCode];

// n个字符串
int n;

// 初始化Huffman树
void initHuffmanTree() {
    for(int i = 0; i < (2 * n) - 1; i++) {
        huffman[i].weight = 0;
        huffman[i].value = "";
        huffman[i].parent = -1;
        huffman[i].lchild = -1;
        huffman[i].rchild = -1;
    }
}


// 贪心法
// 构造Huffman树
void huffmanTree() {
    // 循环构建Huffman树
    for(int i = 0; i < n - 1; i++) {
        // m1,m2存放所有节点中权值最小的两个节点权值
        int m1 = INF;
        int m2 = INF;
        // x1,x2存放所有节点中权值最小的两个节点下标
        int x1 = 0;
        int x2 = 0;
        for(int j = 0; j < n + i; j++) {
            if(huffman[j].weight < m1 && huffman[j].parent == -1) {
                m2 = m1;
                x2 = x1;
                m1 = huffman[j].weight;
                x1 = j;
            } else if(huffman[j].weight < m2 && huffman[j].parent == -1) {
                m2 = huffman[j].weight;
                x2 = j;
            }
        }
        // 设置找到的两个节点的x1,x2的父节点信息
        huffman[x1].parent = n + i;
        huffman[x2].parent = n + i;
        huffman[n + i].weight = huffman[x1].weight + huffman[x2].weight;
        huffman[n + i].lchild = x1;
        huffman[n + i].rchild = x2;
    }
}

// huffman编码
void huffmanEncoding() {
    // 临时结构
    Code cd;
    int child, parent;
    for(int i = 0; i < n; i++) {
        cd.value = huffman[i].value;
        cd.start = n - 1;
        child = i;
        parent = huffman[child].parent;
        // 未到根节点
        while(parent != -1) {
            // 左孩子
            if(huffman[parent].lchild == child) {
                cd.bit[cd.start] = 0;
            } else {
                // 右孩子
                cd.bit[cd.start] = 1;
            }
            cd.start--;
            // 设置下一循环条件
            child = parent;
            parent = huffman[child].parent;
        }

        // 保存求出的每个叶子节点的Huffman编码结构
        for(int j = cd.start + 1; j < n; j++) {
            huffmanCode[i].bit[j] = cd.bit[j];
        }
        huffmanCode[i].start = cd.start;
        huffmanCode[i].value = cd.value;
    }
}

// 打印每个叶节点的Huffman编码和编码起始值
void printHuffmanCode() {
    for(int i = 0; i < n; i++) {
        cout << "第" << i + 1 << "个字符 " << huffmanCode[i].value << " 的Huffman编码为：";
        for(int j = huffmanCode[i].start + 1; j < n; j++) {
            cout << huffmanCode[i].bit[j];
        }
        cout << " 编码起始值为：" << huffmanCode[i].start << endl;
    }
    cout << endl;
}

// 解码Huffman编码
void HuffmanDecoding(string s) {
    vector<string> v;
    // 标识位
    int ok = 1;
    for(int i = 0; i < s.length();) {
        // 根节点
        int x = (2 * n) - 1 - 1;
        // 不为叶子节点
        while(huffman[x].lchild != -1 && huffman[x].rchild != -1) {
            // 左子树
            if(s[i] == '0') {
                x = huffman[x].lchild;
            } else {
                // 右子树
                x = huffman[x].rchild;
            }
            i++;
            // 处理0,1序列有误
            // 这种情况一般是结尾0,1序列少了，导致最后一个字符串解码失败
            if(i == s.length() && huffman[x].lchild != -1) {
                ok = 0;
                break;
            }
        }

        if(ok) {
            v.push_back(huffman[x].value);
        }
    }
    if(ok) {
        for(int i = 0; i < v.size(); i++) {
            cout << v[i];
        }
        cout << endl << endl;
    } else {
        cout << "解码有误。" << endl << endl;
    }
}

int main()
{
    while(true){
        system("color E9");
        char choice;
        system("cls");
        printf("--哈夫曼编译码器--\n");
        printf("1. 编码\n");
        printf("2. 译码\n");
        printf("3. 退出\n");
        printf("请输入命令: ");
        printf("\n");
        printf("请您选择(1-5):");
        choice = getch();
        while(choice!='1'&&choice!='2'&&choice!='3')
            choice = getch();
        printf("%c\n",choice);
        fflush(stdin);

        if(choice=='1') /*编码*/ 
        {
            system("cls");
            system("color BC");
            cout << "请输入字符串个数(0: 退出)：";
            cin >> n;
            if(n){
                char stop;
                // 初始化Huffman树
                initHuffmanTree();

                for(int i = 0; i < n; i++) {
                    cout << "一共" << n << "个字符串，请输入第" << i + 1 << "个字符串及其权值：";
                    cin >> huffman[i].value;
                    cin >> huffman[i].weight;
                }

                // 构造Huffman树
                huffmanTree();

                // huffman编码
                huffmanEncoding();

                // 打印每个叶节点的Huffman编码和编码起始值
                printHuffmanCode();
                
                printf("按任意键返回主菜单>>>");
                fflush(stdin);
                stop = getchar();
            }
        }

        if(choice=='2') /*译码*/ 
        {
            system("cls");
            system("color 3D");
            while(true){
                cout << "请输入一段符合上述编码的0,1序列(输入q：退出)：";
                string s;
                cin >> s;
                if(s[0] == 'q') {
                    cout << endl;
                    break;
                }
                cout << "原始0,1序列为：" << s << endl;
                cout << "解码后为：";
                // 解码
                HuffmanDecoding(s);
            }
        }

        if(choice=='3') /*退出*/ 
        {
            printf("\n欢迎再次使用");
            int c = getchar();
            return 0;
        }
    }
    
}

