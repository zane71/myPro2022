//У԰����ϵͳ
#include "stdio.h"
#include "stdlib.h"
#include "byebye.h"
#include "xinan.h"
#include "denglu.h"
#include "welcom.h"
#include "menu1.h"
#include "menu2.h"
#include "map.h"
#include "password.h"
//#include <unistd.h>
#define Max_num 100
#define INFINITY 32768
//??????????????????????????????????????????????????????????
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

//����ṹ��
typedef struct
{
    int NO;  //�ص����
    char name[50]; //�ص���
}Vextype;

//�ڽӾ���ṹ��
typedef struct
{
    int arcs[Max_num + 1][Max_num + 1];  //�߼�
    Vextype vex[Max_num + 1];   //���㼯
    int vexnum;    //������Ŀ
    int arcnum;    //����Ŀ
}AdjMatrix;


//���ݵص���ȷ���ص����
int Locate(AdjMatrix* G, char name[]);
//�����ڽӾ��󴴽�������
void Create_AdjMatrix(AdjMatrix* G);
//�������������
void Print_AdjMatrix(AdjMatrix* G);
//������ȱ������о���
void DFSTrave(AdjMatrix G);
void DFS(AdjMatrix G, int i);
//����µص�
void Add_Place();
//�����·��
void Add_Route();
//������·��
void Del_Route();
//�����ɵص�
void Del_Place();
//����prim�㷨�������ͨͼ
void Prim(AdjMatrix* G, int start);
//��ѯ��ĳ����������������ͨͼ
void Prim_MiniSpanTree(AdjMatrix* G);
//����Dijkstra�㷨��Ԫ������·��
void Dijkstra(AdjMatrix* G, int start, int end, int dist[], int path[][Max_num + 1]);
//��ѯ���������������·��
void Dij_Short_Path();
//��ѯ����������������·��
void All_Path(AdjMatrix* G);
//��ѯ�ص���Ϣ
void plcae();
//���˵�
void menu(AdjMatrix G);
//menu1�˵��Ķ�Ӧ����
void switch1(AdjMatrix G);
//menu2�˵��Ķ�Ӧ����
void switch2();
//�洢��Ϣ
void Store(AdjMatrix* G);
//��ȡ��Ϣ
int Read();

void menu(AdjMatrix G)
{
    int choice;
    //system("cls");
    choice = denglu(); //�û����� 0�˳�  1����Ա 2�û�
    //����Ա��½
    if (choice == 1) {
        password();    //ƥ���û�������˺š����� 
        menu1();       //����Ա�˵�����
        switch1(G);    //����Ա����ѡ��
    }

    //�ͻ���½
    else if (choice == 2) {
        system("cls");
        menu2();       //�û��˵�����
        switch2();     //�û�����ѡ��
    }
    else if (choice == 0) {
        system("cls");
        byebye();
    }
    else {
        printf("\t\t\t\t\t��Ǹ�������ڸõ�½ģʽ!\n");
        exit(-1);
    }
}
//������
int main()
{
    AdjMatrix G;
    Read(&G);
    welcom();
    xinan();
    menu(G);
    
    return 0;
}


//���ݵص���ȷ���ص����
int Locate(AdjMatrix* G, char name[])
{
    
    
    //TODO  ����
    int i;
    for (i = 1; i <= G->vexnum; i++) {
        //ͼ�к��иþ��㣬�ҵ������
        if (!strcmp(G->vex[i].name, name))

            return i;
    }

    return -1;
}

//�����ڽӾ��󴴽�������
void Create_AdjMatrix(AdjMatrix* G)
{
    int i, j, k, weight;
    char name1[50], name2[50];
    printf("\n\n\n\n\t\t\t********************************    ��  ��  ��  ѧ   ********************************\n\n\n\n");
    printf("\t\t\t�����µ�ͼ...\n\n");
    printf("\t\t\t������ѧУ�еĵص���Ŀ��·����Ŀ��");
    scanf("%d %d", &G->vexnum, &G->arcnum);

    //��ʼ������Ϣ  ���100����
    for (i = 1; i <= G->vexnum; i++) {
        for (j = 1; j <= G->vexnum; j++) {
            G->arcs[i][j] = INFINITY;
        }
    }
 

    //��ʼ�����㼯��
    for (i = 1; i <= G->vexnum; i++) {
        printf("\t\t\t�������%d���ص���ź����֣�", i);
        scanf("%d %s", &G->vex[i].NO, G->vex[i].name);
    }
    printf("\n");
    //�����߹�ϵ
    for (k = 1; k <= G->arcnum; k++) {
        printf("\t\t\t�������%d��������������ص����ֺ�·�����ȣ�", k);
        scanf("%s %s %d", name1, name2, &weight);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = weight;
        G->arcs[j][i] = weight;
    }
    printf("\n\t\t\t�����µ�ͼ�ɹ���\n\n");
    Store(G);
}

//�������������
/*void Print_AdjMatrix(AdjMatrix *G)
{

    int i, j;
    for(i = 1; i <= G->vexnum; i++)
        printf("%8s", G->vex[i].name);
    printf("\n\n");
    for(i = 1; i <= G->vexnum; i++){
        for(j = 1; j <= G->vexnum; j++){
            if(G->arcs[i][j] == INFINITY)
                printf("       #");
           else
                printf("%8d", G->arcs[i][j]);
        }
        printf("\n");
    }
}
*/
int visited[Max_num + 1];
//������ȱ������о���
//�����ջ���  �ѽ��
void DFS(AdjMatrix *G, int i)
{
    printf("%s ", G->vex[i].name);
    visited[i] = 1;
    for (int k = 1; k <= G->vexnum; k++) {
        if (visited[k] == 0 && G->arcs[i][k] < INFINITY)
            DFS(G, k);
    }
}

void DFSTrave(AdjMatrix G)
{
    for (int j = 1; j <= G.vexnum; j++) {
        visited[j] = 0;
    }
    //AdjMatrix Gtemp = G;
 
    for (int j = 1; j <= G.vexnum; j++) {
        if (visited[j] == 0) {
            DFS(&G, j);
        }
    }
}

//����µص�
void Add_Place(AdjMatrix* G)
{
    char name[50];
    int i, j, m, num;
    printf("\n\n\n\t\t\t\t\t����µص�...\n");
    printf("\t\t\t\t\t������Ҫ��ӵص����Ŀ��");
    scanf("%d", &num);
    m = G->vexnum;
    G->vexnum += num;

    //��ʼ���¼���ı���Ϣ����
    for (j = 1; j <= num; j++) {
        for (i = 1; i <= G->vexnum; i++) {

            G->arcs[i][m + j] = INFINITY;
            G->arcs[m + j][i] = INFINITY;

        }
    }

    //�¼���Ķ�����Ϣ
    for (i = m + 1; i <= G->vexnum; i++) {
        printf("\t\t\t\t\t�������%d���ص���ź����֣�", i);
        scanf("%d %s", &G->vex[i].NO, G->vex[i].name);
    }
    Store(G);
    //  Print_AdjMatrix(G);
}

//�����·��
void Add_Route(AdjMatrix* G)
{

    char name1[50], name2[50];
    char choice = 'y';
    int arcnum = G->arcnum, weight, i, j;

    while (choice == 'y' || choice == 'Y') {
        printf("\t\t\t\t\t������������������������ֺ�·�������������");
        scanf("%s %s %d", name1, name2, &weight);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = weight;
        G->arcs[j][i] = weight;
        G->arcnum += 1;
        printf("\t\t\t\t\t�Ƿ�������·��(y || n)��");
        getchar();
        choice = getchar();
    }
    Store(G);
    // Print_AdjMatrix(G);
}

//������·��
void Del_Route(AdjMatrix* G)
{

    char name1[50], name2[50];
    char choice = 'y';
    int  i, j;

    while (choice == 'y' || choice == 'Y') {
        printf("\t\t\t\t\t������Ҫ������������������:");
        scanf("%s %s", name1, name2);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = INFINITY;
        G->arcs[j][i] = INFINITY;
        G->arcnum -= 1;
        printf("\t\t\t\t\t�Ƿ��������·��(y || n)��");
        getchar();
        choice = getchar();
    }
    Store(G);
    //  Print_AdjMatrix(G);
}

//�����ɵص�
void Del_Place(AdjMatrix* G)
{
    char name[50];
    char choice;
    int  i, j, k;
    printf("\t\t\t\t\t\n\n������Ҫ�����ĵص�����:");
    scanf("%s", name);
    printf("\t\t\t\t\t�Ƿ�����������㣺(y || n)��");
    getchar();
    choice = getchar();
    while (choice == 'y' || choice == 'Y') {
        //printf("\t\t\t\t\t\n\n������Ҫ�����ĵص�����:");
        //scanf("%s", name);
        k = Locate(G, name);
        if (k == -1) {
            printf("û�иõص�\n");
            return;
        }

        //printf("%d", k);
        //ɾ���õ� ����㸲��
        
        //G->vexnum -= 1;
        //�߸��� 
        //if (k == G->vexnum) {
        //    //G->vex[k].name = "false";
        //    G->vex[k].NO = 1000000;
        //}
        for (j = 1; j <= G->vexnum; j++) {
            if (G->arcs[k][j] < INFINITY) {
                G->arcnum -= 1;
                //G->arcs[k][j] = INFINITY;
                //G->arcs[j][k] = INFINITY;
            }
        }
            
        //for (j = 1; j <= G->vexnum; j++) {
        //    if (G->arcs[j][k] < INFINITY) {
        //        G->arcnum -= 1;
        //        //G->arcs[k][j] = INFINITY;
        //        //G->arcs[j][k] = INFINITY;
        //    }
        //}
        for (j = k; j <= G->vexnum; j++) {
            
            G->vex[j] = G->vex[j + 1];
            G->vex[j].NO = j;
        }


        for (i = k; i <= G->vexnum; i++) {
            for (j = 1; j <= G->vexnum; j++) {
                G->arcs[i][j] = G->arcs[i + 1][j];
                //G->arcs[i][j] = INFINITY;
            }
        }
        for (j = k; j <= G->vexnum; j++) {
            for (i = 1; i <= G->vexnum; i++) {
                G->arcs[i][j] = G->arcs[i][j + 1];
            } 
            //G->arcnum -= 1;
        }
        G->vexnum -= 1;
        choice = 'n';
        //       Print_AdjMatrix(G); 
    }
    Store(G);
    //  Print_AdjMatrix(G);
}

//����prim�㷨�������ͨͼ
void Prim(AdjMatrix* G, int start)
{
    struct {
        int adjvex;
        int lowcost;
        int pass;
    }closedge[Max_num + 1];
    int i, e, k, m, min;

    //��ʼ��
    closedge[start].lowcost = 0;
    for (i = 1; i <= G->vexnum; i++) {
        if (i != start) {
            closedge[i].adjvex = start;
            closedge[i].lowcost = G->arcs[start][i];

        }
    }

    //����Сֵ�ı�
    for (e = 1; e <= G->vexnum - 1; e++) {

        min = INFINITY;
        for (k = 1; k <= G->vexnum; k++) {
            if (closedge[k].lowcost != 0 && closedge[k].lowcost < min) {
                m = k;
                min = closedge[k].lowcost;
            }
        }
        //��ֹ�����ӡ
        if (closedge[m].lowcost != 0) {
            printf("\t%s----->%s: ����Ϊ%d\n", G->vex[closedge[m].adjvex].name, G->vex[m].name, closedge[m].lowcost);

        }
        closedge[m].lowcost = 0;

        //����󣬸���closedge����
        for (i = 1; i <= G->vexnum; i++) {
            if (i != m && G->arcs[m][i] < closedge[i].lowcost) {
                closedge[i].lowcost = G->arcs[m][i];
                closedge[i].adjvex = m;
            }
        }
    }

}

//��ѯ��ĳ����������������ͨͼ
void Prim_MiniSpanTree(AdjMatrix* G)
{
    system("cls");
    char name[50], choice = 'y';
    int start;

    printf("\t\t\t\t\t   ��Ѳ�������...\n\n\n\n");
    while (choice == 'y' || choice == 'Y') {
        printf("\t\t\t\t\t��������㣺");
        scanf("%s", name);
        start = Locate(G, name);
        Prim(G, start);
        printf("\t\t\t\t\t�Ƿ������ѯ(y || n): ");
        getchar();
        choice = getchar();
    }
}

//����Dijkstra�㷨��Ԫ������·��
void Dijkstra(AdjMatrix* G, int start, int end, int dist[], int path[][Max_num + 1])
{
    int mindist, i, j, k, t = 1;

    //��ʼ��
    for (i = 1; i <= G->vexnum; i++) {
        dist[i] = G->arcs[start][i];
        //     printf("dst_%d = %d\n",i,dist[i]);
        if (G->arcs[start][i] != INFINITY)
            path[i][1] = start;
    }



    path[start][0] = 1;

    //Ѱ�����·��
    for (i = 2; i <= G->vexnum; i++) {
        mindist = INFINITY;
        for (j = 1; j <= G->vexnum; j++) {
            if (!path[j][0] && dist[j] < mindist) {
                mindist = dist[j];
                k = j;
            }
        }
        if (mindist == INFINITY)  break;
        path[k][0] = 1;
        //�޸ļ��������·��
        for (j = 1; j <= G->vexnum; j++) {
            if (!path[j][0] && G->arcs[k][j] < INFINITY && G->arcs[k][j] + dist[k] < dist[j]) {
                dist[j] = dist[k] + G->arcs[k][j];

                //��¼���·��
                t = 1;
                while (path[k][t]) {
                    path[j][t] = path[k][t];
                    t++;
                }
                path[j][t] = k;
                path[j][t + 1] = 0;
            }
        }
    }
    if (dist[end] == INFINITY) {
        printf("\n\n\t%s----->%s  ������ͨ·!!!\n", G->vex[start].name, G->vex[end].name);
        return;
    }
    //������·��
    printf("\n\n\t%s----->%s�����·�ߣ�%s ", G->vex[start].name, G->vex[end].name, G->vex[start].name);
    for (j = 2; path[end][j]; j++) {
        printf("����>%s ", G->vex[path[end][j]].name);
    }
    
    printf("����>%s", G->vex[end].name);
    printf("\n\t����Ϊ��%d\n", dist[end]);

}

//��ѯ���������������·��
void Dij_Short_Path(AdjMatrix* G)
{
    system("cls");
    char name[50], choice = 'y';
    int start, end;
    int dist[Max_num + 1];
    printf("\t\t\t\t\t   ���·��...\n\n\n\n");
    while (choice == 'y' || choice == 'Y') {
        int path[Max_num + 1][Max_num + 1] = { 0 };
        printf("\n\t\t\t\t\t��������㣺");
        scanf("%s", name);
        start = Locate(G, name);
        printf("\t\t\t\t\t�������յ㣺");
        scanf("%s", name);
        end = Locate(G, name);
        Dijkstra(G, start, end, dist, path);
        printf("\t\t\t\t\t�Ƿ������ѯ(y || n)��");
        getchar();
        choice = getchar();
    }
}

//��ѯ����������������·��
int pre[Max_num + 1];  //���һ��·�еĸ������������е��±�
boolean pathvisted[Max_num + 1][Max_num + 1];
int flag = 0;



void Path(AdjMatrix* G, int start, int end, int length, int dist)
{
    /*if (length > G->vexnum) {
        return;
    }*/
    if (flag >= Max_num) {
        return;
    }
    int i;
    if (pre[length] == end && length < G->vexnum) {
        printf("%s ", G->vex[pre[1]].name);
        flag++;
        
        for (i = 2; i <= length; i++) {
            printf("����> %s", G->vex[pre[i]].name);
            if (G->arcs[pre[i - 1]][pre[i]] != INFINITY) {
                dist += G->arcs[pre[i - 1]][pre[i]];
            }
        }
        printf("����Ϊ: %d\n", dist);
        dist = 0;
    }
    else {  	// û������������
        i = 1;
        while (i <= G->vexnum) {
            if (!visited[i] && G->arcs[pre[length]][i] < INFINITY) {
                visited[i] = 1;
                pre[length + 1] = i;
                Path(G, i, end, length + 1, dist);
                visited[i] = 0;
            }
            i++;
        }
    }

    
}

void All_Path(AdjMatrix* G)
{
    system("cls");
    flag = 0;
    //boolean false;
    memset(pathvisted, 0, sizeof(pathvisted));
    int i, start, end;
    int flag1 = 0;
    int flag2 = 0;
    char name1[50], name2[50];
    int dist = 0;

    printf("\t\t\t\t\t��������㣺");
    scanf("%s", name1);
    start = Locate(G, name1);
    //printf("%d",start);
    printf("\t\t\t\t\t�������յ㣺");
    scanf("%s", name2);
    end = Locate(G, name2);

    //�Ӹ��ж� ��ֹ��ѭ��
    for (int a = 1; a <= G->vexnum; a++) {
        if (G->arcs[end][a] < INFINITY) {
            flag1 = 1;
            break;
        }
    }
    for (int a = 1; a <= G->vexnum; a++) {
        
        if (G->arcs[start][a] < INFINITY) {
            flag2 = 1;
            break;
        }
    }
    if (flag1 == 0||flag2==0) {
        printf("%s---->%s������·��Ϊ��\n", G->vex[start].name, G->vex[end].name);
        printf("��δ����ͨ·\n");
        return;
    }
    for (i = 1; i <= Max_num; i++) {
        visited[i] = 0;
    }
    visited[start] = 1;  // ���ʹ�����Ϊ1
    pre[1] = start;
    printf("%s---->%s������·��Ϊ��\n", G->vex[start].name, G->vex[end].name);
    Path(G, start, end, 1, dist);
}


//�洢�ص㼰·����Ϣ��message��txt�ļ���
void Store(AdjMatrix* G)
{
    FILE* fp;
    char* str = NULL;
    if ((fp = fopen("message.txt", "w")) == NULL) {
        printf("\t\t\t\t\t��Ǹ���޷������洢!\n");
        return;
    }

    printf("\t\t\t�洢��Ϣ��...\n");
    //save header
    //sprintf(str,"%d,%d",);
    
    //G->vex[j].NO = 1000000
    fprintf(fp, "%d,%d\n", G->vexnum, G->arcnum);

    //save vex info
    int k;
    for (k = 1; k <= G->vexnum; k++) {
        if (G->vex[k].NO < 1000000) {
            fprintf(fp, "%d %s\n", G->vex[k].NO, G->vex[k].name);
        }
         
    }

    //save arc info
    int i, j;
    for (i = 1; i <= G->vexnum; i++)
        for (j = i; j <= G->vexnum; j++)
        {
            if (G->arcs[i][j] != INFINITY) {
                fprintf(fp, "%s %s %d\n", G->vex[i].name, G->vex[j].name, G->arcs[i][j]);
            }
        }

    fclose(fp);
    printf("\t\t\t\t\t��ϲ���洢�ɹ�!\n\n");
}



//��ȡ�ص㼰·����Ϣ
//AdjMatrix Read()
int Read(AdjMatrix* G)
{
    FILE* fp;
    char line[1024];
    if ((fp = fopen("message.txt", "r")) == NULL) {
        printf("\t\t\t\t\t��Ǹ���޷�������ȡ!\n");
        return 0;
    }
    printf("\t\t\t   ��ȡ��Ϣ��...\n");


    int position = 0;
    char* p = "";              //����һ��ָ��
    char* delima = ",";        //��һ�зָ���
    
    {
        fgets(line, 1024, fp);  //��ȡһ��

        p = strtok(line, delima);
        G->vexnum = atoi(p); //������
        p = strtok(NULL, delima);
        G->arcnum = atoi(p);//����
        //printf("%d,%d",G->vexnum,G->arcnum);
        int i, j;
        for (i = 1; i <= G->vexnum; i++)      //�߼���ʼ�������
        {
            for (j = 1; j <= G->vexnum; j++)
            {
                G->arcs[i][j] = INFINITY;//�߼�
                G->arcs[j][i] = INFINITY;
            }
        }

        int k;
        for (k = 0; k < G->vexnum; k++)  //��ȡ�ص���Ϣ����д�����
        {
            fgets(line, 1024, fp);
            p = "";
            p = strtok(line, "\n");//��ȥ���з�
            p = strtok(p, " "); //�ո�Ϊ�ָ��
            G->vex[k + 1].NO = atoi(p);
            p = strtok(NULL, delima);
            strcpy(G->vex[k + 1].name, p);
            //printf("%s",G->vex[k+1].name);
        }

        for (i = 0; i < G->arcnum; i++) //��ȡ����Ϣ����д�����
        {
            fgets(line, 1024, fp);
            p = "";
            //p = strtok(line, "\n");//��ȥ���з�
            p = strtok(line, " ");
            //printf("%s", p);

            int i = Locate(G, p);
            //printf("%d ", i);
            p = strtok(NULL, " ");
            int j = Locate(G, p);
            //printf("%d", j);
            p = strtok(NULL, " ");
            G->arcs[i][j] = atoi(p);
            G->arcs[j][i] = atoi(p);
            //printf("\n");
        }

    }

    fclose(fp);
    printf("\t\t\t\t\t��ϲ,  ��ȡ�ɹ�!\n\n");

    return 1;
}

//��ѯ�ص���Ϣ
void plcae(AdjMatrix* G)
{
    system("cls");
    char place[500], name[50], choice = 'y';
    int i;
    FILE* fp;

    printf("\t\t\t\t\t   �ص���Ϣ��ѯ...\n\n\n\n\n");
    for (i = 1; i <= G->vexnum; i++)
        printf("%s  ", G->vex[i].name);
    printf("\n");
    while (choice == 'y' || choice == 'Y') {
        printf("\t\t\t\t\t��������Ҫ�˽�ľ�������");
        scanf("%s", name);
        if ((fp = fopen(name, "rt")) == NULL) {
            printf("\t\t\t\t\t��Ǹ���ļ�δ�����򿪣�\n");
            return;
        }
        while ((fgets(place, 500, fp)) != NULL) {
            printf("%s", place);
        }
        fclose(fp);
        getchar();
        printf("\n\n\t\t\t\t\t�Ƿ�Ҫ����(y || n)��");
        scanf("%c", &choice);
    }
}

//menu1�˵��Ķ�Ӧ����
void switch1(AdjMatrix G)
{

    int choice;
    printf("\n\t\t\t\t\t\t����������Ҫ�Ĺ��ܣ�");
    scanf("%d", &choice);
    sleep(1);
    system("cls");
    switch (choice) {
    case 1:Create_AdjMatrix(&G); break;  //����Ա�ֶ����봴���µ�ͼ
    case 2:Add_Place(&G);   break;  //����µص�
    case 3:Del_Place(&G);   break;  //�����ɵص�
    case 4:Add_Route(&G);   break;  //�����·��
    case 5:Del_Route(&G);   break;  //������·��
    case 6:DFSTrave(G); break;       //������ȱ������о���
    case 0:menu(G);  break;
    default:
        printf("\033[31m\t\t\t\t\t��Ǹ����������!!!\n");
    }

    if (choice != 0) {
        getchar();
        printf("\t\t\t\t\t��enter������......");
        getchar();
        system("cls");
        menu1();
        switch1(G);
    }
}

//menu2�˵��Ķ�Ӧ����
void switch2()
{
    
    int choice, k;
    AdjMatrix G;
    //fread(&G, sizeof(AdjMatrix), 1, fp);
    Read(&G);

    printf("\t\t\t\t\t����������Ҫ�Ĺ��ܣ�");
    scanf("%d", &choice);

    switch (choice) {
    case 1: map(); break; //�鿴У԰ƽ��ͼ
    case 2: plcae(&G); break; //�ص���Ϣ��ѯ
    case 3: Dij_Short_Path(&G); break; //���·��
    case 4: All_Path(&G); break;       //����·��
    case 5: Prim_MiniSpanTree(&G); break; //�����ͨͼ
    case 0: menu(G); break;   //�˳�
    default:
        printf("\t\t\t\t\t\t��Ǹ�������������󣡣���\n");
    }
    if (choice != 0) {
        getchar();
        printf("\n\n\t\t\t\t\t��enter������......\n");
        getchar();
        system("cls");
        menu2();
        switch2();
    }
}
