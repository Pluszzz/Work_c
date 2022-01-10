#include<stdio.h>//小区物业管理系统
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct people;
typedef struct people *name;
typedef name student;
struct people
{
    char num;//计数，用于后面增添修改删除数据时的判断依据，不参与打印和输入
    char number[10];//学号
    char name[12];
    char sex[10];
    char sdept[20];
    int Chinese;
    int Mathmatics;
    int English;
    int tatal;
    student next;
};
student HEAD=NULL;//结构体头指针
student plus_input();//数据输入
int plus_output(student );//数据输出   输出时要按照表格输出
int plus_fwrite(student );//写入函数,将链表中的数据存储到外部文件中
student plus_fread();//读取函数，运行程序初获取文件中的数据将其存储在链表中
student plus_add(int);//增添数据(从指定位置插入)  在任意位置插入若干条
student plus_delete(int);//删除数据  可删除若干条
student plus_modify(student );//修改数据
student plus_sort(student );//数据排序  包括升序排序和降序排序
int plus_query(student );//包括简单查询和组合查询
int plus_statistics(student );//数据统计
int plus_password(void);//进入系统需要输入正确的密码
int plus_getchoice(void);//一个选择函数用于获取学生对菜单的选择
int main(void)
{
    //plus_password();
    int choice=0,i;
    HEAD=plus_fread();//程序开始时调用读取数据的函数，返回给链表的头指针；
    while(choice!=10)//学生输入10时退出系统
    {
        choice=plus_getchoice();//获取学生对菜单的选择
        switch (choice)//通过不同的需求进入函数
        {
          case 1:HEAD=plus_input();break;
          case 2:plus_modify(HEAD);break;
          case 3:printf("请选择要输入项的序号(0号)即最后一项\n");
                 scanf("%d",&i);
                 HEAD=plus_delete(i);
                 printf("删除任务完成\n");
                 break;
          case 4:plus_query(HEAD);break;
          case 5:plus_statistics(HEAD);break;
          case 6://HEAD=plus_sort(HEAD);break;
          case 7:plus_output(HEAD);break;
          case 8:printf("请选择要插入的位置(输入0即代表从末尾添加):\n");
                 scanf("%d",&i);
                 HEAD=plus_add(i);break;
          case 9:plus_fwrite(HEAD);break;
          default:    break;
        }
    }
    printf("Bye\n");
    return 0;
}
int plus_getchoice(void)
{
    int ch=0;
    puts("-----------------------");
    puts("欢迎使用学生成绩管理系统");
    puts("请选择以下功能");
    puts("1.添加学生信息");
    puts("2.修改学生信息");
    puts("3.删除学生信息");
    puts("4.查询学生信息");
    puts("5.数据信息统计");
    puts("6.数据信息排序");
    puts("7.显示所有学生信息");
    puts("8.学生信息从指定位置插入");
    puts("9.数据存储入文件");
    puts("10.退出管理系统");
    puts("-----------------------");
    scanf("%d",&ch);
    while(ch>10||ch<1)//没有在规定的范围内选择则提示用户重新选择；
    {
        printf("请按照系统的提示进行选择\n");
        scanf("%d",&ch);
    }
    return ch;//把数字返回给main()；

}
student plus_input()
{
    int ch,i=1;
    student current,head=NULL;//定义头指针和位置指针；current表示当前位置
    current=(student )malloc(sizeof(struct people));//动态分配内存空间
    while(current!=NULL)
    {
      current->num=i;
      printf("请依次输入新学生的信息:\nnumber:");
      scanf("%s",current->number);
      printf("\nname:");
      scanf("%s",current->name);
      printf("\nsex:");
      scanf("%s",current->sex);
      printf("\nsdept:");
      scanf("%s",current->sdept);
      printf("\nChinese:");
      scanf("%d",&current->Chinese);
      printf("\nMathmatics:");
      scanf("%d",&current->Mathmatics);
      printf("\nEnglish:");
      scanf("%d",&current->English);
      printf("\ntatal:");
      scanf("%d",&current->tatal);
      if(head==NULL)
      {  head=current;}
      printf("即将进入下一次新学生信息的输入，若要退出，请输入0，继续请输入1\n");
      i++;
      scanf("%d",&ch);//让学生是否连续输入信息进行选择；
      if(ch==0)
      {
        current->num=0;
        break;
      }
      //prev=current;
      current->next=(student )malloc(sizeof(struct people));
      current=current->next;
    }

    puts("任务已完成，为您返回主界面");
    return head;
}
plus_output(student HEAD)
{
    int i,j,k=0;
    struct people *current=HEAD;
    if(current==NULL)
    {
      printf("暂无学生的信息,为您返回主菜单.\n");
      return 0;
    }
    else printf("以下是学生信息列表:\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("|Number      |Name           |Sex   |sdept          |Chinese|Mathmatics|English|tatal|\n");
    printf("-------------+---------------+------+---------------+-------+----------+-------+------\n");
    while(current!=NULL)
    {
        for(i=0;current->number[i]!='\0';i++)
        { printf("%c",current->number[i]);}
        for(j=0;j<=12-i;j++)
        {printf(" ");}
        printf("|%-15s|%-6s|%-15s|",current->name,current->sex,current->sdept);
        
        printf("%-7d|%-10d|%-7d|%-5d|\n",current->Chinese,current->Mathmatics,current->English,current->tatal);
        k++;
        if(current->num==0)
        break;
        current=current->next;
        printf("-------------+---------------+------+---------------+-------+----------+-------+------\n");
    }
    printf("--------------------------------------------------------------------------------------\n");
    printf("\n以上就是全部学生考试信息列表.\n");
    getchar();
    return 0;
}
plus_fwrite(student HEAD)
{
  FILE*fp;
  int i,j,k=0;
  char word[20];
  if((fp=fopen("message1","w"))==NULL)
  {
    fprintf(stdout,"Can't open\"message1\"file.\n");
    exit(EXIT_FAILURE);
  }
  student current=HEAD;
  fprintf(fp,"|Number      |Name          |Sex  |sdept        |Chinese|Mathmatics|English  |tatal|\n");
  while(current!=NULL)
    {    
      fprintf(fp," ");
      for(i=0;current->number[i]!='\0';i++)
      { fprintf(fp,"%c",current->number[i]);}
      for(j=0;j<=12-i;j++)
      {fprintf(fp," ");}
      fprintf(fp,"%-15s%-6s%-15s",current->name,current->sex,current->sdept);
        
      fprintf(fp,"%-7d%-11d%-10d%-5d\n",current->Chinese,current->Mathmatics,current->English,current->tatal);
      k++;
      if(current->num==0)
      break;
      current=current->next;
    }
  fclose(fp);
  puts("学生数据已经存储到message1文件中\n");
  return 0;
}
student plus_fread()
{
  FILE*in;
  int i=1;
  char wo,ch;
  if((in=fopen("message1","r"))==NULL)
  {
    fprintf(stdout,"Can't open\"message1\"file.\n");
    exit(EXIT_FAILURE);
  }
  student current,head=NULL;
  current=(student )malloc(sizeof(struct people));
  while(in!=NULL)
  {  
    if((wo=getc(in))=='\n'&&((ch=getc(in))==' '))
    {
      fseek(in,-1L,SEEK_CUR);
      current->num=i;
      fscanf(in,"%s",current->number);
      fscanf(in,"%s",current->name);
      fscanf(in,"%s",current->sex);
      fscanf(in,"%s",current->sdept);
      fscanf(in,"%d",&current->Chinese);
      fscanf(in,"%d",&current->Mathmatics);
      fscanf(in,"%d",&current->English);
      fscanf(in,"%d",&current->tatal);
      if(head==NULL)
      {  head=current;}
      while(((wo=getc(in))==' ')&&(wo!='\n'))
      {  fseek(in,1L,SEEK_CUR);}
      if((wo=getc(in))==EOF)
        break;
      current->next=(student )malloc(sizeof(struct people));
      current=current->next;
      i++;
      fseek(in,-2L,SEEK_CUR);
    }
  }
  current->num=0;
  fclose(in);
  return head;
}
student plus_add(int numnum)
{
  student need,*prev;
  int i,j,k=0,n;
  struct people *current=HEAD;
  need=(student )malloc(sizeof(struct people));
  printf("请依次输入新学生的信息:\n");
  while(current!=NULL)
  {
    if(numnum==0)
    {
      while(current->num!=0)//不是最后一项
      {
        if(current->next->num!=0)//找到最后一项的前一项
        {  
          current=current->next;
          continue;
        }
        break;
      }
      n=current->num;//记录前一项的项数
      if(current->num!=0)
      {
        current=current->next;
        current->next=(student )malloc(sizeof(struct people));
        need=current->next;
      }
      else
      {
        current->next=(student )malloc(sizeof(struct people));
        need=current->next;
      }
      current->num=n+1;
      need->num=0;
      fflush(stdin);
      printf("number:");
      scanf("%s",need->number);
      printf("\nname:");
      scanf("%s",need->name);
      printf("\nsex:");
      scanf("%s",need->sex);
      printf("\nsdept:");
      scanf("%s",need->sdept);
      printf("\nChinese:");
      scanf("%d",&need->Chinese);
      printf("\nMathmatics:");
      scanf("%d",&need->Mathmatics);
      printf("\nEnglish:");
      scanf("%d",&need->English);
      printf("\ntatal:");
      scanf("%d",&need->tatal);
    }
    else if(numnum==1)
    {
      need->next=(student )malloc(sizeof(struct people));
      need->next=HEAD;
      need->num=1;
      HEAD=need;
      printf("number:");
      scanf("%s",need->number);
      printf("\nname:");
      scanf("%s",need->name);
      printf("\nsex:");
      scanf("%s",need->sex);
      printf("\nsdept:");
      scanf("%s",need->sdept);
      printf("\nChinese:");
      scanf("%d",&need->Chinese);
      printf("\nMathmatics:");
      scanf("%d",&need->Mathmatics);
      printf("\nEnglish:");
      scanf("%d",&need->English);
      printf("\ntatal:");
      scanf("%d",&need->tatal);
      while(current->num!=0)
      {
        current->num+=1;
        current=current->next;
      }
    }
    else if(current->num+1==numnum)
    {  
      need->num=current->num+1;
      need->next=current->next;
      current->next=need;
      printf("number:");
      scanf("%s",need->number);
      printf("\nname:");
      scanf("%s",need->name);
      printf("\nsex:");
      scanf("%s",need->sex);
      printf("\nsdept:");
      scanf("%s",need->sdept);
      printf("\nChinese:");
      scanf("%d",&need->Chinese);
      printf("\nMathmatics:");
      scanf("%d",&need->Mathmatics);
      printf("\nEnglish:");
      scanf("%d",&need->English);
      printf("\ntatal:");
      scanf("%d",&need->tatal);
      break;
    }
    else current=current->next;
  }
  printf("插入信息完成\n");
  return HEAD;
}
student plus_delete(int numnum)
{
  student current=HEAD;
  //int numnum;
  while(current!=NULL)
  {
    if(numnum==0)//删除最后一项
    {
      if(current->num==0)//只有一项时
      {
        HEAD=NULL;
        break;
      }
      while(current->num!=0)//非只有一项时，current->num不会在第一项，所以判断current->next->num;若其等于0；则将current->next=NULL;
      {  
        if(current->next->num==0)
        {
          current->num=0;
          current->next=NULL;
          break;
        }
        current=current->next;
      }
      break;
    }

    else if(current->num==numnum)//删除的不是最后一项时，若是删除第一项；令HEAD=第一个的next指针
    {
      HEAD=current->next;
      current=current->next;
      while(current->num>numnum&&current->num!=0)//后续序号-1
      {  
        current->num-=1;
      }
      break;
    }    
    while(current->num!=numnum)//若不是第一项也不是最后一项
    {
      if(current->next->num==numnum)
      {
        current->next=current->next->next;
        while(current->num!=0)//后续序号-1
        {  
          if(current->num>numnum)
          current->num-=1;
          current=current->next;
        }
        break;
      }
      else current=current->next;
    }
    break;
  }
  return HEAD;
}
student plus_modify(student HEAD)
{
  student current=HEAD;
  int numnum,choice;
  printf("请选择要修改项的位置\n");
  scanf("%d",&numnum);
  puts("请选择要修改的部分:1:number,2:name,3:sex,4:sdept,5:Chinese,6:Mathmatics,7:English,8:tatal\n");
  scanf("%d",&choice);
  puts("请输入新的信息:");
  while(current!=NULL)
  {
    if(current->num==numnum)
    {
      switch(choice)
      {
        case 1:scanf("%s",current->number);break;
        case 2:scanf("%s",current->name);break;
        case 3:scanf("%s",current->sex);break;
        case 4:scanf("%s",current->sdept);break;
        case 5:scanf("%s",current->Chinese);break;
        case 6:scanf("%d",&current->Mathmatics);break;
        case 7:scanf("%d",&current->English);break;
        case 8:scanf("%d",&current->tatal);break;
        default:puts("无效的选择\n");
      }
      break;
    }
    else current=current->next;
  }
  puts("修改完成\n");
  return HEAD;
}
int plus_query(student HEAD)
{
  student current=HEAD;
  int i,*p,k;
  puts("请选择要查询的项目满足条件的个数");
  scanf("%d",&i);
  p=(int*)malloc(sizeof(int));
  char want[i][20];
  int choice[i],j,compare,numnum[i];
  puts("请选择要查询的条件:1:number,2:name,3:sex,4:sdept,5:Chinese,6:Mathmatics,7:English,8:tatal\n");
  for(j=0;j<=i-1;j++)
  {scanf("%d",&choice[j]);}
  puts("你选择了第");
  for(j=0;j<=i-1;j++)
  {printf("%d",choice[j]);}
  puts("条件\n");
  puts("请按照顺序依次为查询的项给予满足的条件");
  for(j=0;j<=i-1;j++)
  {
    if(choice[j]==6||choice[j]==7||choice[j]==8)
    scanf("%d",&numnum[j]);
    else 
    scanf("%s",want[j]);
  }
  printf("---------------------------------------------------------------------------------------------\n");
  printf("|Number      |Name           |Sex   |sdept             |Chinese         |Mathmatics|English  |tatal|\n"); 
  while(current!=NULL)
  {
    for(j=0;j<=i-1;j++)
    {
      
      switch(choice[j])
      {
        case 1:compare=strcmp(want[j],current->number);break;
        case 2:compare=strcmp(want[j],current->name);break;
        case 3:compare=strcmp(want[j],current->sex);break;
        case 4:compare=strcmp(want[j],current->sdept);break;
        case 5:compare=current->Chinese-numnum[j];break;
        case 6:compare=current->Mathmatics-numnum[j];break;
        case 7:compare=current->English-numnum[j];break;
        case 8:compare=current->tatal-numnum[j];break;
        default:compare=1;break;
      }
      if(compare!=0)
      break;
      else if(compare==0&&j==i-1)
      {
        printf("-----------+----------------+------+---------------------+--------------+--------+--------+---------\n");
        while(current!=NULL)
        {
          for(i=0;current->number[i]!='\0';i++)
          { printf("%c",current->number[i]);}
          for(j=0;j<=12-i;j++)
          {printf(" ");}
          printf("|%-15s|%-6s|%-15s|",current->name,current->sex,current->sdept);
          
          printf("%-7d|%-10d|%-7d|%-5d|\n",current->Chinese,current->Mathmatics,current->English,current->tatal);
          k++;
          if(current->num==0)
          break;
          current=current->next;
          printf("-------------+---------------+------+---------------+-------+----------+-------+------\n");
        }
      }
    }
    if(current->num==0)
    break;
    current=current->next;
  }
  printf("--------------------------------------------------------------------------------------------\n");
  return 0;
  
}
int plus_statistics(student )
{
  student current=HEAD;
  int i,*p,k;
  puts("请选择要查询的项目满足条件的个数");
  scanf("%d",&i);
  p=(int*)malloc(sizeof(int));
  char want[i][20];
  int choice[i],j,compare,numnum[i];
  puts("请选择要查询的条件:1:number,2:name,3:sex,4:sdept,5:Chinese,6:Mathmatics,7:English,8:tatal\n");
  for(j=0;j<=i-1;j++)
  {scanf("%d",&choice[j]);}
  puts("你选择了第");
  for(j=0;j<=i-1;j++)
  {printf("%d",choice[j]);}
  puts("条件\n");
  puts("请按照顺序依次为查询的项给予满足的条件");
  for(j=0;j<=i-1;j++)
  {
    if(choice[j]==6||choice[j]==7||choice[j]==8)
    scanf("%d",&numnum[j]);
    else 
    scanf("%s",want[j]);
  }
  printf("---------------------------------------------------------------------------------------------\n");
  printf("|Number      |Name           |Sex   |sdept             |Chinese         |Mathmatics|English  |tatal|\n"); 
  while(current!=NULL)
  {
    for(j=0;j<=i-1;j++)
    {
      
      switch(choice[j])
      {
        case 1:compare=strcmp(want[j],current->number);break;
        case 2:compare=strcmp(want[j],current->name);break;
        case 3:compare=strcmp(want[j],current->sex);break;
        case 4:compare=strcmp(want[j],current->sdept);break;
        case 5:compare=current->Chinese-numnum[j];break;
        case 6:compare=current->Mathmatics-numnum[j];break;
        case 7:compare=current->English-numnum[j];break;
        case 8:compare=current->tatal-numnum[j];break;
        default:compare=1;break;
      }
      if(compare!=0)
      break;
      else if(compare==0&&j==i-1)
      {
        printf("-----------+----------------+------+---------------------+--------------+--------+--------+---------\n");
        while(current!=NULL)
        {
          for(i=0;current->number[i]!='\0';i++)
          { printf("%c",current->number[i]);}
          for(j=0;j<=12-i;j++)
          {printf(" ");}
          printf("|%-15s|%-6s|%-15s|",current->name,current->sex,current->sdept);
          
          printf("%-7d|%-10d|%-7d|%-5d|\n",current->Chinese,current->Mathmatics,current->English,current->tatal);
          k++;
          if(current->num==0)
          break;
          current=current->next;
          printf("-------------+---------------+------+---------------+-------+----------+-------+------\n");
        }
      }
    }
    if(current->num==0)
    break;
    current=current->next;
  }
  printf("--------------------------------------------------------------------------------------------\n");
  printf("满足条件的数据共有%d项",s);
  return s;
}
/*student plus_sort(student ) //数据排序  包括升序排序和降序排序
{
  student current=HEAD,temp;
  int i=0,j=0,k=0,numnum,s;
  while(current!=NULL)//利用选择排序实现
  {
    if(current->tatal>current->next->tatal)//获取最大一项的位置
    {  temp=current;}
    else temp=current->next;
    do{
      if(current->num)
      if(temp->tatal<current->next->tatal)
        temp=current->next;
      else
        current=current->next;
    }while(current->num!=0);
    s=temp->num;
    plus_delete(s);
    printf("|%-15s|%-6s|",temp->name,temp->sex);
    for(i=0;temp->sdept[i]!='\0';i++)
    { printf("%c",temp->sdept[i]);}
    for(j=0;j<=20-i;j++)
    {printf(" ");}
    printf("|");
    for(i=0;temp->Chinese[i]!='\0';i++)
    { printf("%c",temp->Chinese[i]);}
    for(j=0;j<=13-i;j++)
    {printf(" ");}
    printf("|%-8d|%-8d|%-8d|\n",temp->Mathmatics,temp->English,temp->tatal);
    current=HEAD;
    if(current->num==0)
    break;
  }
  puts("已经按tatal大小递减排序\n");
  return HEAD;
}	*/
int plus_password(void)
{
  FILE*in;
  int i=0,j,ch;
  char wo;
  char password[15],savepassword[10][15];
  char people[15],savepeople[10][15];
  if((in=fopen("message2","r"))==NULL)
  {
    fprintf(stdout,"Can't open\"message2\"file.\n");
    exit(EXIT_FAILURE);
  }
  while(in!=NULL)
  {
    fscanf(in,"%s",savepeople[i]);
    fscanf(in,"%s",savepassword[i]);
    if((ch=getc(in))!=EOF)
    {
      i++;
      fseek(in,-1L,SEEK_CUR);
      continue;
    }
    else break;
  }
  puts(" 请输入学生名:");
  scanf("%s",people);
  do{
    for(j=0;j<=i;j++)
    {
      if(strcmp(people,savepeople[j])==0)
      break;
      if(strcmp(people,savepeople[j])!=0&&j==i)
      {
        puts("无效的学生名,请尝试重新输入:\n");
        scanf("%s",people);
      }
    }
    if(strcmp(people,savepeople[j])==0)
      break;

  }while(strcmp(people,savepeople[j])!=0);

  puts("\n请输入密码:");
  for (i = 0;; i++)
 {
  password[i] = getch();
  switch (password[i])
  {
  case '\b':
   password[--i] = '\0';
   i--;
   printf("\b \b");
   break;
  case '\r':
   password[i] = '\0';
   putchar('\n');
   break;
  default:
   putchar('*');
   break;
  }
  if (password[i] == '\0') break;
 }

  if(strcmp(password,savepassword[j])==0)
  {
    puts("密码正确，进入菜单\n");
    return 0;
  }
  else 
  {

  }
  do{
      puts("密码与学生名不匹配,请尝试重新输入密码\n");
      puts("\n请输入密码:");
      for (i = 0;; i++)
      {
      password[i] = getch();
      switch (password[i])
      {
      case '\b':
      password[--i] = '\0';
      i--;
      printf("\b \b");
      break;
      case '\r':
      password[i] = '\0';
      putchar('\n');
      break;
      default:
      putchar('*');
     break;
  }
  if (password[i] == '\0') break;
 }

      if(strcmp(password,savepassword[j])==0)
      break;
  }while(strcmp(password,savepassword[j])!=0);
    puts("密码正确，进入菜单\n");
    return 0;
}




