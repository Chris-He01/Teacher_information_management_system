#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <malloc.h>
#include <windows.h>
#define LEN sizeof(struct Teacher)

struct Teacher
{
    int num;
    char name[20];//
    char sex[9];//
    char title[20];//
    char course[20];//
    int classes;//
    int class_num[10];
    float theory;
    float experiment;
    float sum_hours;
    struct Teacher *next;
}temp,temp2;

struct Teacher *head,*p1,*p2,*pt,*pr;//for head of teacher's list,p1 for new input, p2 is mainly for the end of the list
int n=0;

void login()
{
	system("cls");
	system("color  4E");
	printf("\n\n\n\n\n\n\n######################~Welcome to the course management system for teacher~#######################\n");
	printf("\n\n\n\t\t\t\t *************");
    printf("\n\n\n\n\t\t\t\t\t\tLoading");
	for(int i=0;i<6;i++)
	{
		Sleep(400);
		printf(".");
	}
    system("cls");

    return;

}

float simu_hours(struct Teacher *sp)//calculating the total time of courses
{
    switch(sp->classes)
    {
        case 2:sp->sum_hours=2.0*1.5*(sp->theory+sp->experiment);break;
        case 3:sp->sum_hours=3.0*2.0*(sp->theory+sp->experiment);break;
        case 4:sp->sum_hours=4.0*2.5*(sp->theory+sp->experiment);break;
        default:sp->sum_hours=sp->classes*2.5*(sp->theory+sp->experiment);break;
    }
    return 0;
}

int output(struct Teacher *pn,int a)//input,a=0search,a=1print all
{
    int i,k;
    if(pn==NULL&&n==0)
    {
        printf("\nNo data here!please choose to input in the function interface\n");
        return 0;
    }
    if(a==0)
    {
        printf("*****************************************************\n"
               "***************Search result for teacher's information：********************\n");
            printf("       teacher's ID:");
            printf("%d                                               \n",pn->num);
            printf("       Name:");
            printf("%s                                               \n",pn->name);
            printf("       Sex:");
            printf("%s                                               \n",pn->sex);
            printf("       Title:");
            printf("%s                                               \n",pn->title);
            printf("       course:");
            printf("%s                                               \n",pn->course);
            printf("       course amount:");
            printf("%d                                               \n",pn->classes);
        for(k=0;k<pn->classes;k++)
        {
            printf("       class%d:",k+1);
            printf("0%d                                             \n",pn->class_num[k]);
        }
            printf("       normal class amount:");
            printf("%.1f                                            \n",pn->theory);
            printf("       lab class amount:");
            printf("%.1f                                            \n",pn->experiment);
            printf("       totoal amount of course:");
            printf("%.1f                                            \n",pn->sum_hours);
            printf("*****************************************************\033[0m\n");
    }
    else if(a==1&&n!=0)
    {

        for(i=0;pn!=NULL&&i<=n;pn=pn->next,i++)
        {   printf("*****************Input Success******************\n");
            printf("       teacher's ID:");
            printf("%d                                               \n",pn->num);
            printf("       Name:");
            printf("%s                                               \n",pn->name);
            printf("       Sex:");
            printf("%s                                               \n",pn->sex);
            printf("       Title:");
            printf("%s                                               \n",pn->title);
            printf("       course:");
            printf("%s                                               \n",pn->course);
            printf("       course amount:");
            printf("%d                                               \n",pn->classes);
            for(k=0;k<pn->classes;k++)
            {
            printf("       class%d:",k+1);
            printf("0%d                                             \n",pn->class_num[k]);
            }
            printf("       normal class amount:");
            printf("%.1f                                            \n",pn->theory);
            printf("       lab class amount:");
            printf("%.1f                                            \n",pn->experiment);
            printf("       totoal amount of course:");
            printf("%.1f                                            \n",pn->sum_hours);
            putchar(10);
            printf("*****************************************************\n");
            printf("page%d(%din total)\n",i+1,n);
            system("pause");
            system("cls");

        }
    }
}

int sort(int a)
{
    if(head==NULL)
        return 2;

    pr=head;

    if(a==1)
    {
        printf("please input teacher ID:");
        scanf("%d",&temp.num);
       while(temp.num!=pr->num)
        {
            pr=pr->next;
            if(pr==NULL)
                break;
        }
    }

    else if(a==2)
    {
        while(getchar()!='\n');
        printf("please input teacher name:");
        scanf("%s",temp.name);

        while(strcmp(pr->name,temp.name)!=0)
        {
            pr=pr->next;
            if(pr==NULL)
                break;
        }
    }

    if(pr!=NULL) output(pr,0);

    else
    {
        printf("Failed to find this teacher's information!\n");
        system("pause");
		system("cls");
        return 0;
    }
     return 1;

}

int delet(void)//for deleting
{
    struct Teacher *p,*pp;
    if(pr==NULL)
    {
        if(sort(1)==0)
            return 1;
    }
    else
    {
        printf("please input the teacher ID to delete:%d\n",pr->num);
    }

    if(n==0)
    {
        head=NULL;
        return 1;
    }

    p=head;

    if(p->num==pr->num)// make this pointer equal to the head
    {
        head=head->next;
        n--;
        if(n==0)
        {
            head=NULL;
            pr=NULL;
            return 0;
        }
    }

    else if(p->num==p2->num)//make this pointer equal to the end
    {
        while(pr->num>p->num&&(p!=p2))//let p2 as the end
        {
            pp=p;
            p=p->next;
        }
        pp->next=pr;
        pr->next=NULL;
        pr=NULL;
        n--;
    }

    else//consider the case in the middle 
    {
        while(pr->num>p->num&&(p!=p2))
        {
            pp=p;
            p=p->next;
        }
        pp->next=pr->next;
        n--;
        pr=NULL;
    }

    return 0;
}

int insert()//add;insert or edit
{
        struct Teacher *p,*pp;
        int flag;

        p1=(struct Teacher *)malloc(LEN);
        if(pr==NULL)
        {
            printf("please input\nteacher's ID:");
            scanf("%d",&p1->num);
        }
        else
        {
            p1->num=pr->num;
            pr=NULL;
            printf("---new teacher's information---\n"
                   "teacher ID:%d\n",p1->num);
        }

        flag=p1->num;

        if(n==0)//for the first one
        {
            head=p1;
            p2=p1;
            head->next=NULL;
            p2->next=NULL;
        }

        if(flag==0)
        {
            p2->next=NULL;
            if(n==0) head=NULL;
            return 1;
        }//end

        //input
        printf("name:");
        scanf("%s",p1->name);
        while(getchar()!='\n');
        printf("sex:");
        scanf("%s",p1->sex);
        while(getchar()!='\n');
        printf("title:");
        scanf("%s",p1->title);
        while(getchar()!='\n');
        printf("course:");
        scanf("%s",p1->course);
        while(getchar()!='\n');

        do
        {
            printf("course number(>=2):");
            scanf("%d",&p1->classes);
            if(p1->classes<2)
                printf("wrong input,please try again!\n");
        }while(p1->classes<2);

        for(int k=0;k<p1->classes;k++)
        {
            printf("course%d:",k+1);
            scanf("%d",&p1->class_num[k]);
        }
        printf("normal teaching time:");
        scanf("%f",&p1->theory);
        printf("lab class time:");
        scanf("%f",&p1->experiment);

        simu_hours(p1);

        //another function for calculating

        if(n==0)
        {
            n++;
            return 0;
        }


        if(p1->num<head->num)//before the head
        {
            p1->next=head;
            head=p1;
            n++;
            return 0;
        }
        if(p1->num==head->num)//edit the head
        {
            p1->next=head->next;
            head=p1;
            return 0;
        }
        //after the head,don't know exact place
        //decide whether is before the end
        if(p1->num>p2->num)// after the end
        {
            p2->next=p1;
            p2=p1;
            p2->next=NULL;
            n++;
            return 0;
        }
        p=head;
        if(p1->num==p->num)//edit the end
        {
            while(p->next!=p2)
                p=p->next;

            p->next=p1;
            p2=p1;
            p2->next=NULL;
            return 0;
        }

        while((p1->num)>(p->num))//before the end
        {
            pp=p;
            p=p->next;
        }
        if(p1->num==p->num)//repeat,edit
        {
            pp->next=p1;
            p1->next=p->next;
            return 0;
        }
        else//sinply insert
        {
            pp->next=p1;
            p1->next=p;
            n++;
            return 0;
        }
   return 0;
}
int create()//creat
{
    int t=0;

    while(t!=1)
    {
        printf("pleas follow the instruction to input the teacher's information, teacher's ID end with 0\n");
        t=insert();
        system("pause");
        system("cls");

    }
    system("pause");
    return 0;
}
int search()
{
    system("color  6E");
    int a,b,c,d;
    do
    {
        printf("                                                     \n");
        printf("            About to search，pleas slect              \n");
        printf("                                                     \n");
        printf("                                                     \n");
        printf("               0.exit                                \n");
        printf("                                                     \n");
        printf("               1.search with teacher's ID            \n");
        printf("                                                     \n");
        printf("               2.search with teacher's name          \n");
        printf("                                                     \n");
        printf("                                      ^ ^            \n");
        printf("               please input:          V \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");

        int flag;
        do
        {
            scanf("%d",&a);
            switch(a)
            {
                case 1:system("cls");c=sort(a);break;
                case 2:system("cls");c=sort(a);break;
                case 0:system("cls");return 0;
                default:system("cls");printf("\nworng input, please try again\n");
                        printf("               0.exit                                \n");
                        printf("                                                     \n");
                        printf("               1.search with teacher's ID            \n");
                        printf("                                                     \n");
                        printf("               2.search with teacher's name          \n");
                        printf("                                                     \n");
                        printf("                                      ^ ^            \n");
                        printf("               please input:          V \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                ;a=0;
            }
            //if (flag==1) continue;
        }while(a==0);

        if(c==2)
        {
            printf("database is empty!about to return catalogue!");
            return 0;
        }//empty case

        if(c==0)
        {
            continue;
        }
        while(getchar()!='\n');
        getchar();
		system("cls");

        system("color  6E");
        do
        {
            printf("please choose the operation:\n"
               "0.exit\t 1.edit\t 2.delete\n"
               "please input:");
            scanf("%d",&b);
            switch(b)
            {
                case 1:insert();
                        printf("***********************EDIT SUCCESS**********************\n");
                        break;
                case 2:delet();
                        printf("***********************DELETE SUCCESS**********************\n");
                        break;
                case 0:break;
                default:printf("\nwrong input, please try again:");continue;
            }
            if(b==0) break;
        }while(b==0);

        pr=NULL;
        system("cls");
        if(n==0)
        {
            printf("\ndatabase is empty!about to return catalogue!\n");
            return 0;
        }//when enpty
    }while( a!=0);
}

int save()
{
    int cho;

    if(n!=0)
    {
        do
        {   system("color  6E");
            printf("Do you want to save the data into the file\n"
               "0.YES\t1.NO"
               "\nplease input:");
            scanf("%d",&cho);
            switch(cho)
            {
                case 0:break;
                case 1:return 0;
                default:printf("wrong input, please try again:\n");
            }
        }while(cho!=0);
    }
    else
    {
        system("color  6E");
        printf("\ncanot save, the data might be empty\n");
        return 0;
    }

    FILE *fp;
    if((fp=fopen("teacher.dat","wb"))==NULL)
        {
            printf("cannot open file\n");
            return(0);
        }
    p1=head;
    for (int i=0;i<n&&p1!=NULL;i++)
    {

        if(fwrite(p1,LEN,1,fp)!=1)
            printf("file wirte error.\nPosition is %d",i);
        p1=p1->next;
    }
    fclose(fp);
    printf("all the work is ok\n");
}

int start()
{
    struct Teacher *pp;
    int cho2;

    printf("\n\n\n\n\n\n");

    printf("                                                     \n");
    printf("  Do you want input new information or open existing file \n");
    printf("                                                     \n");
    printf("                                                     \n");
    printf("               0.open existing file                            \n");
    printf("                                                     \n");
    printf("               1.input new infromation                            \n");
    printf("                                                     \n");
    printf("         please input:");
    scanf("%d",&cho2);
    printf("                                                     \n");
    printf("                                      ^ ^            \n");
    printf("                                       V             \n");

    if(cho2==0)
    {
        FILE *fp;
        if((fp=fopen("teacher.dat","rb"))==NULL)
        {
            printf("cannot open file\n");
            exit(0);
        }

        n=0;

        do{

            p1=(struct Teacher *)malloc(LEN);

            if(fread(p1,LEN,1,fp)!=1)
            {
                printf("there is something wrong\n");
                exit(0);
            }

            if(n==0)
            {
              head=p1;
            }
            else pp->next=p1;
            n++;
            pp=p1;


        }while(p1->next!=NULL);

        p2=p1;
        p2->next=NULL;

        fclose(fp);
        system("cls");
        output(head,1);

    }

    else if(cho2==1)
    {
        system("cls");
        printf("*******About to read new teacher's information*******\n");

        create();

        printf("Information writing success\n");
        system("pause");
    }
}

void menu()
{
    int cho;
    //system("pause");
    system("cls");
    int cho1;
    do
    {
        system("color  6E");
        printf("\n\n************************WELLCOME TO FUNCTION INTERFACE************************\n\n");
        printf("\t1.show exiting information\n"
               "\t2.search data(edit & deleting)\n"
               "\t3.adding data\n"
               "\t4.ranking teacher's class hour\n"
               "\t0.exit function interface\n"
               "\n\tplease input:");
               scanf("%d",&cho);
               system("cls");
               switch(cho)
               {
                    case 1:output(head,1);break;
                    case 2:search();break;
                    case 3:insert();
                            printf("\nadding information success!\n");getchar();break;

                    //case 4:
                    case 0:system("cls");return;
               }
    system("cls");
    }while(cho!=0);
}

int main()
{


    login();

    start();

    menu();

    save();

    printf("\n------------------finished------------------");
    return 0;
}
