#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
#define MAXN 10000
//�����������
/*
    < begin,1 >
    < end,2 >
    < integer,3 >
    < if,4 >
    < then,5 >
    < else,6 >
    < function,7 >
    < read,8 >
    < write,9 >
    < ��ʶ��,10 >
    < ����,11 >
    < =,12 >
    < <>,13 >
    < <=,14 >
    < <,15 >
    < >=,16 >
    < >,17 >
    < -,18 >
    < *,19 >
    < :=,20 >
    < (,21 >
    < ),22 >
    < ;,23 >
 */

//�����ֱ�
static char reserveWord[9][16] = {
    "begin","end","integer","if","then","else","function","read","write"
};

//���ұ�����
int searchReserve(char reserveWord[][16], char s[]){
    for (int i = 0; i < 9; i++)
    {
        if (strcmp(reserveWord[i], s) == 0)
        {
            return i + 1;//�����ֱ���
        }
    }
    return -1;//���򷵻�-1��������Ҳ��ɹ�����Ϊ��ʶ��
}

int judgetep(char tep){
    /* 
    ���һ���ַ�
    ��ĸ���� 1
    ���ַ��� 2
    = ���� 3
    - ���� 4
    * ���� 5
    ( ���� 6
    ) ���� 7
    < ���� 8
    > ���� 9
    : ���� 10
    ; ���� 11
    */
    if (tep >= 'a'&&tep <= 'z' || tep >= 'A'&&tep <= 'Z'|| tep=='_')
    {
        return 1;
    }
    else if (tep >= '0'&&tep <= '9')
    {
        return 2;
    }
    else if (tep =='=')
    {
        return 3;
    }
    else if (tep =='-')
    {
        return 4;
    }
    else if (tep == '*')
    {
        return 5;
    }
    else if (tep == '(')
    {
        return 6;
    }
    else if (tep == ')')
    {
        return 7;
    }
    else if (tep == '<')
    {
        return 8;
    }
    else if (tep == '>')
    {
        return 9;
    }
    else if (tep == ':')
    {
        return 10;
    }    
    else if (tep == ';')
    {
        return 11;
    }
    else
    {
        return 0;
    }
}

//Ԥ����,ȥ��ע��
void predo(char project[],int Pproject){
    char temp[MAXN];
    int cot = 0;
    for(int i = 0;i<=Pproject;i++){
        if (project[i]=='/'&&project[i+1]=='/')
        {
            while (project[i]!='\n')
            {
                i++;
            }
        }
        if (project[i]=='/'&&project[i+1]=='*')
        {
            i+=2;
            while (project[i]!='*'&&project[i+1]!='/')
            {
                i++;
                if(project[i]=='@'){
                    printf("ע���������֤�����ԣ�\n");
                    exit(0);
                }
            }
            i+=2;
        }
        if (project[i]!='\n'&&project[i]!='\t'&&project[i]!='\v'&&project[i]!='\r'){
            temp[cot++]=project[i];
        }
    }
    temp[cot]='\0';
    strcpy(project,temp);
}


void Reader(int &syn,char resourceproject[],char token[],int &Pproject){
    int i,cot=0;
    char tep;
    tep = resourceproject[Pproject];
    while (tep==' ')
    {
        Pproject++;
        tep = resourceproject[Pproject];
    }
    for (int i = 0; i < 16; i++)
    {
        token[i]='\0';
    }
    //�����ж�
    if (resourceproject[Pproject] == '@')
    {
        syn = 0;
        token[0]='@';
        token[1]='\0';
        return;
    }
    switch (judgetep(tep))
    {
    case 1:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        while (judgetep(resourceproject[Pproject])==1||judgetep(resourceproject[Pproject]==2)){
            token[cot++]=resourceproject[Pproject];
            Pproject++;
        }
        token[cot]='\0';
        syn = searchReserve(reserveWord,token);
        if(syn == -1){
            syn = 10;
        }
        break;
    case 2:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        while (judgetep(resourceproject[Pproject])==2)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
        }
        token[cot]='\0';
        syn = 11;
        break;
    case 3:
        token[cot++]=resourceproject[Pproject];
        token[cot]='\0';
        Pproject++;
        syn = 12;
        break;
    case 4:
        token[cot++]=resourceproject[Pproject];
        token[cot]='\0';
        Pproject++;
        syn = 18;
        break;
    case 5:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        token[cot]='\0';
        syn = 19;
        break;
    case 6:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        token[cot]='\0';
        syn = 21;
        break;
    case 7:
        token[cot++]=resourceproject[Pproject];
        token[cot]='\0';
        Pproject++;
        syn = 22;
        break;
    case 8:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        if (judgetep(resourceproject[Pproject])==3)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
            token[cot]='\0';
            syn = 14;
        }
        else if (judgetep(resourceproject[Pproject])==9)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
            token[cot]='\0';
            syn = 13;
        }
        else
        {        
            token[cot]='\0';
            syn = 15;
        }
        break;
    case 9:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        if (judgetep(resourceproject[Pproject])==12)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
            token[cot]='\0';
            syn = 16;            
        }
        else
        {
            token[cot]='\0';
            syn = 17;    
        }
        break;
    case 10:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        if (judgetep(resourceproject[Pproject])==3)
        {
            token[cot++]=resourceproject[Pproject];
            Pproject++;
            token[cot]='\0';
            syn = 20;            
        }
        else
        {
            printf("δ�鵽��Ӧ�ַ���������\n");
            exit(0);            
        }
        break;
    case 11:
        token[cot++]=resourceproject[Pproject];
        Pproject++;
        token[cot]='\0';
        syn = 23;  
        break;
    default:
        printf("δ�鵽��Ӧ�ַ���������\n");
        exit(0);
        break;
    }
    return;
}

//������
int main(){
    char resourceproject[MAXN];
    char token[16] = {0};
    int syn = -1;
    int i;
    int Pproject = 0;//Դ�����ȡָ��
    FILE *fp,*fp1;
    if((fp=fopen("D:\\project.txt","r"))==NULL){
        cout<<"Can't open this file~";
        exit(0);
    }
    resourceproject[Pproject]=fgetc(fp);
    while (resourceproject[Pproject]!='@')
    {
        Pproject++;
        resourceproject[Pproject]=fgetc(fp);
    }
    resourceproject[++Pproject]='\0';
    fclose(fp);
    cout<<"Դ����Ϊ:"<<endl;
    cout<<resourceproject<<endl;
    predo(resourceproject,Pproject);
    Pproject = 0;
    printf("-------------------------begin---------------------------\n");
    printf("�ֱ�----------------------------------------------���ʷ���\n");
    while (syn != 0)
    {
        Reader(syn,resourceproject,token,Pproject);
        switch (syn)
        {
        case 0:
            printf("������-------------------------------------------------%s\n",token);
            break;            
        case 10:
            printf("��ʶ��-------------------------------------------------%s\n",token);
            break;
        case 11:
            printf("����---------------------------------------------------%s\n",token);
            break;
        case 12:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 13:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 14:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 15:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 16:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 17:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 18:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 19:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 20:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 21:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 22:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        case 23:
            printf("%d---------------------------------------------------'%s'\n",syn,token);
            break;
        default:
            printf("�ؼ���-------------------------------------------------%s\n",token);
            break;
        }
    }
    printf("-----------------------finshed!--------------------------\n");
    
}