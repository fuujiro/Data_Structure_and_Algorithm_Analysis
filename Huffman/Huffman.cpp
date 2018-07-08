#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <iomanip>

using namespace std; 

#define NULL_0 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_NUM 32767

typedef char **HuffmanCode;  //动态分配数组存储哈夫曼表码表

typedef struct{
    int weight;
    int parent, lchild, rchild;
}HTNode, *HuffmanTree;  //动态分配数组存储哈夫曼树

typedef struct{
    HuffmanTree HT;
    char        *c;
    int         length;
    HuffmanCode HC;
}Huffman;  //存储字符与代码


void Select(HuffmanTree HT,int end,int *s1,int *s2)//选择HT[1....i-1]中无双亲且权值最小的两个节点，其序号为s1，s2
{
    int i;
    int min1=MAX_NUM;
    int min2;
    for (i=1;i<=end;i++)//遍历查找权值最小的结点S1
    {
        if (HT[i].parent==0&&HT[i].weight<min1)
        {
            *s1=i;
            min1=HT[i].weight;
        }
    }
    min2=MAX_NUM;
    for(i=1;i<=end;i++)//遍历查找除S1外权值最小的结点S2
    {
        if(HT[i].parent==0&&(*s1!=i)&&min2>HT[i].weight)
        {
            *s2=i;
            min2=HT[i].weight;
        }
    }
}



Huffman HuffmanCoding(Huffman Hfm)
{//存放n个字符的权值（均〉0），构造哈夫曼树HT，并求出n个字符的构造哈夫曼编码HC
    int i, n, m, s1, s2, start;
    int c, f;
    char *cd;
    n = Hfm.length;
    if (n <= 1)  return Hfm;
    m = 2*n-1;
    for(i = n+1; i <= m; ++i) {//选择HT[1....i-1]中无双亲且权值最小的两个节点，其序号为s1，s2
        Select(Hfm.HT, i-1, &s1, &s2);
        Hfm.HT[s1].parent = i;//修改父亲位置
        Hfm.HT[s2].parent = i;
        Hfm.HT[i].lchild = s1;//修改孩子位置
        Hfm.HT[i].rchild = s2;
        Hfm.HT[i].weight = Hfm.HT[s1].weight + Hfm.HT[s2].weight;//父亲结点权值为左右孩子权值之和
    }
    //从叶子结点到根逆向求每个字符的哈夫曼编码
    Hfm.HC = (HuffmanCode)malloc((n+1)*sizeof(char *));//分配n个字符编码的头指针向量
    cd = (char *)malloc(n*sizeof(char));//分配求编码的工作空间
    cd[n-1] = '\0';//编码结束符
    
    for (i = 1; i <= n; ++i) {//逐个字符求哈夫曼编码
        start = n - 1;//编码结束符位置
        for (c = i, f = Hfm.HT[i].parent; f != 0; c = f, f = Hfm.HT[f].parent) {
            //从叶子到根逆向求编码
            if (c == Hfm.HT[f].lchild) {
                cd[--start] = '0';
            } else cd[--start] = '1';
        }
        Hfm.HC[i] = (char *)malloc((n-start)*sizeof(char));
        strcpy(Hfm.HC[i], &cd[start]);//从cd复制编码到Hfm.HC
    }
    free(cd);//释放工作空间
    return Hfm;
}

Huffman InputHuffman(Huffman Hfm)  //输入函数，控制用户输入字符和相应权值
{
    int i, n;
    printf("请输入字符集大小n: ");
    scanf("%d", &n);
    
    if (n <= 1) {
        printf("只有一个字符，无需编码!\n");//若只有一个数值则无需编码
        printf("\n请输入字符集大小n: ");
        scanf("%d",&n);
    }
    printf("\n");
    Hfm.HT = (HuffmanTree)malloc((2 * n) * sizeof(HTNode));
    Hfm.c = (char *)malloc((n + 1) * sizeof(char));
    
    for (i = 1; i <= n; i++) {
        printf("请输入字符: ");
        scanf("%s", &Hfm.c[i]);
        printf("请输入它的权值: ");
        scanf("%d", &Hfm.HT[i].weight);
        Hfm.HT[i].parent = 0;
        Hfm.HT[i].lchild = 0;
        Hfm.HT[i].rchild = 0;
        printf("\n");
    }
    for(; i <= 2*n-1; ++i) {
        Hfm.HT[i].weight = 0;
        Hfm.HT[i].parent = 0;
        Hfm.HT[i].lchild = 0;
        Hfm.HT[i].rchild = 0;
    }
    Hfm.length = n;
    return Hfm;
}

Huffman InitHuffman(Huffman Hfm)
{//初始化哈夫曼数，要求用户输入字符和相应权值
    printf("\n--哈夫曼树初始化--\n");
    int n, i;
    char x;
    FILE *fp;
    fp = fopen("hfmtree", "rt");//对文件hfmtree以读文本的形式打开
    if (fp == NULL_0) {
        Hfm = InputHuffman(Hfm);//调用InputHuffman函数，用户输入字符和相应权值存入哈夫曼数中
        fp = fopen("hfmtree", "wt");
        fprintf(fp, "%d\n", Hfm.length);
        for (i = 1; i <= Hfm.length; i++)
            fprintf(fp, "%c %d  ", Hfm.c[i], Hfm.HT[i].weight);
        rewind(fp);
    } else {
        getchar();
        printf("哈夫曼树已存在！\n请问你要新建一个哈夫曼树吗(Y/N)? ");//询问是否重新初始化
        scanf("%c", &x);
        if (x == 'Y'|| x == 'y') {
            Hfm = InputHuffman(Hfm);  //调用InputHuffman函数，用户输入字符和相应权值存入哈弗曼数中
            fp = fopen("hfmtree", "w+");
            fprintf(fp, "%d\n", Hfm.length);
            for (i = 1; i <= Hfm.length; i++)
                fprintf(fp, "%c %d  ", Hfm.c[i], Hfm.HT[i].weight);
            rewind(fp);
        } else { // 'N'||'n'
            fscanf(fp, "%d\n", &n);
            Hfm.c = (char *)malloc((n + 1) * sizeof(char));
            Hfm.HT = (HuffmanTree)malloc((2 * n) * sizeof(HTNode));
            for (i = 1; i <= n; i++)
                fscanf(fp, "%s %d  ", &Hfm.c[i], &Hfm.HT[i].weight);//将已经在文件中的字符和其对应的权重输入到Hfm.c[i]和&Hfm.HT[i].weight中
            for (i = 1; i <= n; i++) {//对每个节点初始化
                Hfm.HT[i].parent = 0;
                Hfm.HT[i].lchild = 0;
                Hfm.HT[i].rchild = 0;
            }
            for(; i <= 2*n-1; ++i) {
                Hfm.HT[i].weight = 0;
                Hfm.HT[i].parent = 0;
                Hfm.HT[i].lchild = 0;
                Hfm.HT[i].rchild = 0;
            }
            Hfm.length = n;
        }
    }
    fclose(fp);
    printf("哈夫曼树的初始化已完成!\n\n");
    Hfm = HuffmanCoding(Hfm);
    return Hfm;
}

void Encoding(Huffman Hfm)
{//利用已建好的Huffman树（如不在内存，则从文件hfmtree中读入），
    //对文件ToBeTran中的正文进行编码，然后将结果存入文件codefile中。
    int i = 0, j = 0, n, k = 0;
    char ch[60];
    FILE *fp, *fw;
    n = Hfm.length;
    printf("\n--编码--\n");
    
    do {
        printf("1. 对tobetrans.txt的正文进行编码\n");
        printf("2. 对键入的字符串进行编码\n");
        printf("请输入命令: ");
        scanf("%d", &k);
        printf("\n");
        if (k == 1) {
            if ((fw = fopen("tobetrans", "r+")) == NULL_0) {
                printf("tobetrans.txt不存在!\n\n");
            } else {
                printf("已读取tobetrans.txt中的正文\n");
                printf("哈夫曼编码: ");
                fscanf(fw, "%s", ch);
                fclose(fw);
                fp = fopen("codefile", "wt+");
                k = 0;
            }
        } else if (k == 2) {
            printf("请输入要编码的字符串: ");
            scanf("%s", ch);
            printf("哈夫曼编码: ");
            fp = fopen("codefile", "wt+");
            k = 0;
        }
        if (k == 0) {   //跳出do循环
            break;
        }
    } while (k != 1 || k != 2);
    
    while(ch[j]) {
        for (i = 1; i <= n; i++) {
            if (ch[j] == Hfm.c[i]) {
                printf("%s", Hfm.HC[i]);
                fprintf(fp, "%s", Hfm.HC[i]);
                break;
            }
        }
        j++;
    }
    printf("\n已将编码存入codefile.txt\n\n");
    rewind(fp);
    fclose(fp);
}

void Decoding(Huffman Hfm)
{//利用已建好的Huffman树将文件codefile中的代码进行译码，结果存入文件TextFile中。
    HuffmanTree p;
    int i, n;
    int j = 0;
    char d[500];
    FILE *fp;
    n = Hfm.length;
    printf("\n--译码--\n");
    if((fp = fopen("codefile", "r+")) == NULL_0) {
        printf("请输入哈夫曼编码:");
        scanf("%s",d);
    } else {
        fscanf(fp, "%s", d);//将文件中的字符输入到数组d中
        fclose(fp);
    }
    printf("经译码后codefile.txt的内容是: ");
    fp = fopen("TextFile","wt+");//以写入文件的形式打开TextFile
    while (d[j]) {
        p = &Hfm.HT[2*n-1];
        while (p->lchild || p->rchild) {
            if (d[j] == '0') {
                i = p->lchild;
                p = &Hfm.HT[i];
            } else {
                i = p->rchild;
                p = &Hfm.HT[i];
            }
            j++;
        }
        printf("%c", Hfm.c[i]);
        fprintf(fp,"%c", Hfm.c[i]);
    }
    printf("\n\n");
    fclose(fp);
}


void Print(Huffman Hfm)
{//将文件codefile以紧凑格式显示在终端上，每行50 个代码。
    int i, n;
    int m = 1;//计数器
    char ch;
    FILE *fprint;
    n = Hfm.length;
    printf("\n--打印代码文件--\n");
    
    printf("codefile.txt代码: \n");
    
    fprint = fopen("codefile", "rb");
    while (!feof(fprint)) {
        ch = fgetc(fprint);
        printf("%c", ch);
        m++;
        if (m % 50 == 0)//保证每一行输出50个字符
            printf("\n");
    }
    fclose(fprint);
    
    
    printf("\n编码文件: \n");
    printf("字符\t\t权值\t\t编码\n");
    for (i = 1; i <= n; i++) {//显示每一个字符对应的哈夫曼编码
        printf("%c\t\t", Hfm.c[i]);
        printf("%d\t\t", Hfm.HT[i].weight);
        printf("");
        puts(Hfm.HC[i]);
    }
    
    printf("\n");
    
}

int numb = 0;
void coprint(HuffmanTree start, HuffmanTree HT)
{//打印哈夫曼树
    char t = ' ';
    if (start != HT) {
        FILE *TreePrint;
        if ((TreePrint = fopen("TreePrint", "a")) == NULL_0) {
            printf("创建文件失败\n");
            return;
        }
        numb++;
        coprint(HT+start->rchild, HT);
        if (start->lchild != NULL_0 && start->rchild != NULL_0) {
            t = '<';
        }
        cout << setw(5*numb) << start->weight << t << endl;
        fprintf(TreePrint, "%d\n", start->weight);
        coprint(HT+start->lchild, HT);
        numb--;
        fclose(TreePrint);
    }
    
}

void Print_Tree(HuffmanTree HT, int w)
{//直观打印哈夫曼树
    HuffmanTree p;
    p = HT + w;
    printf("打印哈夫曼树: \n");
    coprint(p, HT);
    printf("打印完成！\n\n");
}



int main()
{
    Huffman Hfm;
    char k;
    while(1) {
        printf("--哈夫曼编译码器--         注: 用_代替空格\n");
        printf("I. 初始化\n");
        printf("C. 编码\n");
        printf("D. 译码\n");
        printf("P. 打印代码文件\n");
        printf("T. 打印哈夫曼树\n");
        printf("E. 退出\n");
        printf("请输入命令: ");
        scanf("%c",&k);
        k=toupper(k);
        switch(k) {
            case 'I':
                Hfm=InitHuffman(Hfm);
                getchar();
                break;
            case 'C':
                Encoding(Hfm);
                getchar();
                break;
            case 'D':
                Decoding(Hfm);
                getchar();
                break;
            case 'P':
                Print(Hfm);
                getchar();
                break;
            case 'T':
                Print_Tree(Hfm.HT, 2*Hfm.length-1);
                getchar();
                break;
            case 'E':
                exit(0);
            default:
            printf("错误！请重新输入命令！\n"); }
    }
}