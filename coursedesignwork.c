#include<stdio.h>//小区物业管理系统
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct people
{
    char num;//计数，用于后面增添修改删除数据时的判断依据，不参与打印和输入
    char name[12];
    char sex[10];
    char IDnumber[20];
    char phone[12];
    int building;
    int roomID;
    int roomarea;
    struct people*next;
};
struct people*HEAD=NULL;//结构体头指针
struct people*plus_input();  //数据输入
int plus_output(struct people*);  //数据输出   输出时要按照表格输出
int plus_fwrite(struct people*);//写入函数,将链表中的数据存储到外部文件中
struct people*plus_fread();//读取函数，运行程序初获取文件中的数据将其存储在链表中
struct people*plus_add(int);  //增添数据(从指定位置插入)  在任意位置插入若干条
struct people*plus_delete(int);  //删除数据  可删除若干条
struct people*plus_modify(struct people*); //修改数据
struct people*plus_sort(struct people*);  //数据排序  包括升序排序和降序排序
int plus_query(struct people*);  //包括简单查询和组合查询
int plus_statistics(struct people*);  //数据统计
int plus_password(void);//进入系统需要输入正确的密码
int plus_getchoice(void);//一个选择函数用于获取用户对菜单的选择
int main(void)
{
    plus_password();
    int choice=0,i;
    HEAD=plus_fread();//程序开始时调用读取数据的函数，返回给链表的头指针；
    while(choice!=10)//用户输入10时退出系统
    {
        choice=plus_getchoice();//获取用户对菜单的选择
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
          case 6:HEAD=plus_sort(HEAD);break;
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
    puts("欢迎使用小区物业管理系统");
    puts("请选择以下功能");
    puts("1.添加用户信息");
    puts("2.修改用户信息");
    puts("3.删除用户信息");
    puts("4.查询用户信息");
    puts("5.数据信息统计");
    puts("6.数据信息排序");
    puts("7.显示所有用户信息");
    puts("8.用户信息从指定位置插入");
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
struct people*plus_input()
{
    int ch,i=1;
    struct people*current,*head=NULL;//定义头指针和位置指针；current表示当前位置
    current=(struct people*)malloc(sizeof(struct people));//动态分配内存空间
    while(current!=NULL)
    {
      current->num=i;
      printf("请依次输入新用户的信息:\nname:");
      scanf("%s",current->name);
      printf("\nsex:");
      scanf("%s",current->sex);
      printf("\nIDnumber:");
      scanf("%s",current->IDnumber);
      printf("\nphone:");
      scanf("%s",current->phone);
      printf("\nbuilding:");
      scanf("%d",&current->building);
      printf("\nroomID:");
      scanf("%d",&current->roomID);
      printf("\nroomarea:");
      scanf("%d",&current->roomarea);
      if(head==NULL)
      {  head=current;}
      printf("即将进入下一次新用户信息的输入，若要退出，请输入0，继续请输入1\n");
      i++;
      scanf("%d",&ch);//让用户是否连续输入信息进行选择；
      if(ch==0)
      {
        current->num=0;
        break;
      }
      //prev=current;
      current->next=(struct people*)malloc(sizeof(struct people));
      current=current->next;
    }

    puts("任务已完成，为您返回主界面");
    return head;
}
plus_output(struct people*HEAD)
{
    int i,j,k=0;
    struct people *current=HEAD;
    if(current==NULL)
    {
      printf("暂无用户的信息,为您返回主菜单.\n");
      return 0;
    }
    else printf("以下是用户信息列表:\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("|Name           |Sex   |IDnumber             |Phone         |building|roomID  |roomarea|\n");
    printf("----------------+------+---------------------+--------------+--------+--------+---------\n");
    while(current!=NULL)
    {
        
        printf("|%-15s|%-6s|",current->name,current->sex);
        for(i=0;current->IDnumber[i]!='\0';i++)
        { printf("%c",current->IDnumber[i]);}
        for(j=0;j<=20-i;j++)
        {printf(" ");}
        printf("|");
        for(i=0;current->phone[i]!='\0';i++)
        { printf("%c",current->phone[i]);}
        for(j=0;j<=13-i;j++)
         {printf(" ");}
        printf("|%-8d|%-8d|%-8d|\n",current->building,current->roomID,current->roomarea);
        k++;
        if(current->num==0)
        break;
        current=current->next;
        printf("----------------+------+---------------------+--------------+--------+--------+---------\n");
    }
    printf("----------------------------------------------------------------------------------------\n");
    printf("\n以上就是全部用户信息列表.\n");
    return 0;
}
plus_fwrite(struct people*HEAD)
{
  FILE*fp;
  int i,j,k=0;
  char word[20];
  if((fp=fopen("peoplemessage","w"))==NULL)
  {
    fprintf(stdout,"Can't open\"peoplemessage\"file.\n");
    exit(EXIT_FAILURE);
  }
  struct people *current=HEAD;
  fprintf(fp,"|Name           |Sex   |IDnumber             |Phone         |building|roomID  |roomarea|\n");
  while(current!=NULL)
    {
        
      fprintf(fp," %-15s %-6s ",current->name,current->sex);
      for(i=0;current->IDnumber[i]!='\0';i++)
      { fprintf(fp,"%c",current->IDnumber[i]);}
      for(j=0;j<=21-i;j++)
      {fprintf(fp," ");}
      for(i=0;current->phone[i]!='\0';i++)
      { fprintf(fp,"%c",current->phone[i]);}
      for(j=0;j<=14-i;j++)
      {fprintf(fp," ");}
      fprintf(fp,"%-8d %-8d %-8d\n",current->building,current->roomID,current->roomarea);
      k++;
      if(current->num==0)
      break;
      current=current->next;
    }
  fclose(fp);
  puts("用户数据已经存储到peoplemessage文件中\n");
  return 0;
}
struct people*plus_fread()
{
  FILE*in;
  int i=1;
  char wo,ch;
  if((in=fopen("peoplemessage","r"))==NULL)
  {
    fprintf(stdout,"Can't open\"peoplemessage\"file.\n");
    exit(EXIT_FAILURE);
  }
  struct people*current,*head=NULL;
  current=(struct people*)malloc(sizeof(struct people));
  while(in!=NULL)
  {  
    if((wo=getc(in))=='\n'&&((ch=getc(in))==' '))
    {
      fseek(in,-1L,SEEK_CUR);
      current->num=i;
      fscanf(in,"%s",current->name);
      fscanf(in,"%s",current->sex);
      fscanf(in,"%s",current->IDnumber);
      fscanf(in,"%s",current->phone);
      fscanf(in,"%d",&current->building);
      fscanf(in,"%d",&current->roomID);
      fscanf(in,"%d",&current->roomarea);
      if(head==NULL)
      {  head=current;}
      while(((wo=getc(in))==' ')&&(wo!='\n'))
      {  fseek(in,1L,SEEK_CUR);}
      if((wo=getc(in))==EOF)
        break;
      current->next=(struct people*)malloc(sizeof(struct people));
      current=current->next;
      i++;
      fseek(in,-2L,SEEK_CUR);
    }
  }
  current->num=0;
  fclose(in);
  return head;
}
struct people*plus_add(int numnum)
{
  struct people*need,*prev;
  int i,j,k=0,n;
  struct people *current=HEAD;
  need=(struct people*)malloc(sizeof(struct people));
  printf("请依次输入新用户的信息:\nname:");
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
        current->next=(struct people*)malloc(sizeof(struct people));
        need=current->next;
      }
      else
      {
        current->next=(struct people*)malloc(sizeof(struct people));
        need=current->next;
      }
      current->num=n+1;
      need->num=0;
      scanf("%s",need->name);
      printf("\nsex:");
      scanf("%s",need->sex);
      printf("\nIDnumber:");
      scanf("%s",need->IDnumber);
      printf("\nphone:");
      scanf("%s",need->phone);
      printf("\nbuilding:");
      scanf("%d",&need->building);
      printf("\nroomID:");
      scanf("%d",&need->roomID);
      printf("\nroomarea:");
      scanf("%d",&need->roomarea);
    }
    else if(numnum==1)
    {
      need->next=(struct people*)malloc(sizeof(struct people));
      need->next=HEAD;
      need->num=1;
      HEAD=need;
      scanf("%s",need->name);
      printf("\nsex:");
      scanf("%s",need->sex);
      printf("\nIDnumber:");
      scanf("%s",need->IDnumber);
      printf("\nphone:");
      scanf("%s",need->phone);
      printf("\nbuilding:");
      scanf("%d",&need->building);
      printf("\nroomID:");
      scanf("%d",&need->roomID);
      printf("\nroomarea:");
      scanf("%d",&need->roomarea);
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
      scanf("%s",need->name);
      printf("\nsex:");
      scanf("%s",need->sex);
      printf("\nIDnumber:");
      scanf("%s",need->IDnumber);
      printf("\nphone:");
      scanf("%s",need->phone);
      printf("\nbuilding:");
      scanf("%d",&need->building);
      printf("\nroomID:");
      scanf("%d",&need->roomID);
      printf("\nroomarea:");
      scanf("%d",&need->roomarea);
      break;
    }
    else current=current->next;
  }
  printf("插入信息完成\n");
  return HEAD;
}
struct people*plus_delete(int numnum)
{
  struct people*current=HEAD;
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
struct people*plus_modify(struct people*HEAD)
{
  struct people*current=HEAD;
  int numnum,choice;
  printf("请选择要修改项的位置\n");
  scanf("%d",&numnum);
  puts("请选择要修改的部分:1:name,2:sex,3:IDnumber,4:phone,5:building,6:roomID,7:roomarea\n");
  scanf("%d",&choice);
  puts("请输入新的信息:");
  while(current!=NULL)
  {
    if(current->num==numnum)
    {
      switch(choice)
      {
        case 1:scanf("%s",current->name);break;
        case 2:scanf("%s",current->sex);break;
        case 3:scanf("%s",current->IDnumber);break;
        case 4:scanf("%s",current->phone);break;
        case 5:scanf("%d",&current->building);break;
        case 6:scanf("%d",&current->roomID);break;
        case 7:scanf("%d",&current->roomarea);break;
        default:puts("无效的选择\n");
      }
      break;
    }
    else current=current->next;
  }
  puts("修改完成\n");
  return HEAD;
}
int plus_query(struct people*HEAD)
{
  struct people*current=HEAD;
  int i,*p,k;
  puts("请选择要查询的项目满足条件的个数");
  scanf("%d",&i);
  p=(int*)malloc(sizeof(int));
  char want[i][20];
  int choice[i],j,compare,numnum[i];
  puts("请选择要查询的条件:1:name,2:sex,3:IDnumber,4:phone,5:building,6:roomID,7:roomarea\n");
  for(j=0;j<=i-1;j++)
  {scanf("%d",&choice[j]);}
  puts("你选择了第");
  for(j=0;j<=i-1;j++)
  {printf("%d",choice[j]);}
  puts("条件\n");
  puts("请按照顺序依次为查询的项给予满足的条件");
  for(j=0;j<=i-1;j++)
  {
    if(choice[j]==5||choice[j]==6||choice[j]==7)
    scanf("%d",&numnum[j]);
    else 
    scanf("%s",want[j]);
  }
  printf("---------------------------------------------------------------------------------------------\n");
  printf("|Name           |Sex   |IDnumber             |Phone         |building|roomID  |roomarea|num|\n");
  while(current!=NULL)
  {
    for(j=0;j<=i-1;j++)
    {
      
      switch(choice[j])
      {
        case 1:compare=strcmp(want[j],current->name);break;
        case 2:compare=strcmp(want[j],current->sex);break;
        case 3:compare=strcmp(want[j],current->IDnumber);break;
        case 4:compare=strcmp(want[j],current->phone);break;
        case 5:compare=current->building-numnum[j];break;
        case 6:compare=current->roomID-numnum[j];break;
        case 7:compare=current->roomarea-numnum[j];break;
        default:compare=1;break;
      }
      if(compare!=0)
      break;
      else if(compare==0&&j==i-1)
      {
        printf("----------------+------+---------------------+--------------+--------+--------+--------------\n");  
        printf("|%-15s|%-6s|",current->name,current->sex);
        for(k=0;current->IDnumber[k]!='\0';k++)
        { printf("%c",current->IDnumber[k]);}
        for(j=0;j<=20-k;j++)
        {printf(" ");}
        printf("|");
        for(k=0;current->phone[k]!='\0';k++)
        { printf("%c",current->phone[k]);}
        for(j=0;j<=13-k;j++)
         {printf(" ");}
        printf("|%-8d|%-8d|%-8d|%-2d |\n",current->building,current->roomID,current->roomarea,current->num);
      }
    }
    if(current->num==0)
    break;
    current=current->next;
  }
  printf("--------------------------------------------------------------------------------------------\n");
  return 0;
  
}
int plus_statistics(struct people*)
{
  struct people*current=HEAD;
  int i,*p,k,s=0;
  puts("请选择要查询的项目满足条件的个数");
  scanf("%d",&i);
  p=(int*)malloc(sizeof(int));
  char want[i][20];
  int choice[i],j,compare,numnum[i];
  puts("请选择要查询的条件:1:name,2:sex,3:IDnumber,4:phone,5:building,6:roomID,7:roomarea\n");
  for(j=0;j<=i-1;j++)
  {scanf("%d",&choice[j]);}
  puts("你选择了第");
  for(j=0;j<=i-1;j++)
  {printf("%d",choice[j]);}
  puts("条件\n");
  puts("请按照顺序依次为查询的项给予满足的条件");
  for(j=0;j<=i-1;j++)
  {
    if(choice[j]==5||choice[j]==6||choice[j]==7)
    scanf("%d",&numnum[j]);
    else 
    scanf("%s",want[j]);
  }
  printf("---------------------------------------------------------------------------------------------\n");
  printf("|Name           |Sex   |IDnumber             |Phone         |building|roomID  |roomarea|num|\n");
  while(current!=NULL)
  {
    for(j=0;j<=i-1;j++)
    {
      
      switch(choice[j])
      {
        case 1:compare=strcmp(want[j],current->name);break;
        case 2:compare=strcmp(want[j],current->sex);break;
        case 3:compare=strcmp(want[j],current->IDnumber);break;
        case 4:compare=strcmp(want[j],current->phone);break;
        case 5:compare=current->building-numnum[j];break;
        case 6:compare=current->roomID-numnum[j];break;
        case 7:compare=current->roomarea-numnum[j];break;
        default:compare=1;break;
      }
      if(compare!=0)
      break;
      else if(compare==0&&j==i-1)
      {
        printf("----------------+------+---------------------+--------------+--------+--------+--------------\n");  
        printf("|%-15s|%-6s|",current->name,current->sex);
        for(k=0;current->IDnumber[k]!='\0';k++)
        { printf("%c",current->IDnumber[k]);}
        for(j=0;j<=20-k;j++)
        {printf(" ");}
        printf("|");
        for(k=0;current->phone[k]!='\0';k++)
        { printf("%c",current->phone[k]);}
        for(j=0;j<=13-k;j++)
         {printf(" ");}
        printf("|%-8d|%-8d|%-8d|%-2d |\n",current->building,current->roomID,current->roomarea,current->num);
        s++;
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
struct people*plus_sort(struct people*) //数据排序  包括升序排序和降序排序
{
  struct people*current=HEAD,*temp;
  int i=0,j=0,k=0,numnum,s;
  while(current!=NULL)//利用选择排序实现
  {
    if(current->roomarea>current->next->roomarea)//获取最大一项的位置
    {  temp=current;}
    else temp=current->next;
    do{
      if(current->num)
      if(temp->roomarea<current->next->roomarea)
        temp=current->next;
      else
        current=current->next;
    }while(current->num!=0);
    s=temp->num;
    plus_delete(s);
    printf("|%-15s|%-6s|",temp->name,temp->sex);
    for(i=0;temp->IDnumber[i]!='\0';i++)
    { printf("%c",temp->IDnumber[i]);}
    for(j=0;j<=20-i;j++)
    {printf(" ");}
    printf("|");
    for(i=0;temp->phone[i]!='\0';i++)
    { printf("%c",temp->phone[i]);}
    for(j=0;j<=13-i;j++)
    {printf(" ");}
    printf("|%-8d|%-8d|%-8d|\n",temp->building,temp->roomID,temp->roomarea);
    current=HEAD;
    if(current->num==0)
    break;
  }
  puts("已经按ROOMAREA大小递减排序\n");
  return HEAD;
}	
int plus_password(void)
{
  FILE*in;
  int i=0,j,ch;
  char wo;
  char password[15],savepassword[10][15];
  char people[15],savepeople[10][15];
  if((in=fopen("peoplemessage2","r"))==NULL)
  {
    fprintf(stdout,"Can't open\"peoplemessage2\"file.\n");
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
  puts(" 请输入用户名:");
  scanf("%s",people);
  do{
    for(j=0;j<=i;j++)
    {
      if(strcmp(people,savepeople[j])==0)
      break;
      if(strcmp(people,savepeople[j])!=0&&j==i)
      {
        puts("无效的用户名,请尝试重新输入:\n");
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
      puts("密码与用户名不匹配,请尝试重新输入密码\n");
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




