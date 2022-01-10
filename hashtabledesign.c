#include<stdio.h>
#include<ctype.h>         //toascii函数
#include<stdlib.h>
#define HASH_SIZE 50//哈希表的长度
#define Name_SIZE 20//名字表长度
#define R 49//小于哈希表长度的R
//int i,key;
struct Name
{
    char *name;            //姓名
    int ascii;             //对应的ascii码和
};
struct hash
{
    char *name;            //姓名                 
    int ascii;             //对应ASCII码和
    int s;                 //查找长度
};
Name NameList[Name_SIZE];
hash hashtable[HASH_SIZE];
void init_Namelistlist ( );      //初始化姓名表
void C_hashtable ( ) ;      //创建hash表
void collison (int i );          //冲突函数,第i个姓名表发生冲突
void print_Namelist ( );
void print_hash ( );         //打印函数

void init_Namelist( )
{
    NameList[0].name="zhangsan";
    NameList[1].name="lisi";
    NameList[2].name="wangmazi";
    NameList[3].name="ergoudan";
    NameList[4].name="tieniu";
    NameList[5].name="dabendan";
    NameList[6].name="xunan";
    NameList[7].name="zhoulei";
    NameList[8].name="tanglei";
    NameList[9].name="xiaomin";
    NameList[10].name="xiaohong";
    NameList[11].name="xiaoli";
    NameList[12].name="damin";
    NameList[13].name="jinzhengyu";
    NameList[14].name="xiasaobi";
    NameList[15].name="xuyang";
    NameList[16].name="lihao";
    NameList[17].name="huangzhifeng";
    NameList[18].name="liangsifen";
    NameList[19].name="yanzhiwo";
    NameList[20].name="liyanlin";
    NameList[21].name="liuxiaohan";
    NameList[22].name="tanghuan";
    NameList[23].name="gongxiaoyu";
    NameList[24].name="haoren";
    NameList[25].name="huairen";
    NameList[26].name="shuchang";
    NameList[27].name="lixinru";
    NameList[28].name="zhouhang";
    NameList[29].name="wangcunwen";
    int i,j;
    for(i=0;i<Name_SIZE;i++)
    {    
        for(j=0;(*(NameList[i].name+j))!='\0';j++)             
        NameList[i].ascii+=toascii(*(NameList[i].name+j));            //ascii码求和
    }                  
}
void collison (int i)
{
    int key,flag;
    flag=0;                                                           //未探测至末尾
    key=(NameList[i].ascii)%R;
    while(hashtable[key].s != 0)
    {
        key=key+1; 
      //  printf("%d",key);                                             //线性探测每次加1
        if(key==HASH_SIZE-1){                                          //探测至哈希表末端
            key=0;
            flag=1;                                                    //探测至末尾标识                       
        }
    }
    if(hashtable[key].s==0)
        {
            hashtable[key].name=NameList[i].name;
            hashtable[key].ascii=NameList[i].ascii;
            if(flag==0)
            hashtable[key].s= (key-(NameList[i].ascii%R))+1 ;
            else
            hashtable[key].s= (HASH_SIZE-(NameList[i].ascii%R))+key+1;   //查找次数                                                                                       //查找次数
        }
}
void C_hashtable()                                      //创建哈希函数
{
    int i,key;
    for(i=0;i<HASH_SIZE;i++)
    {
        hashtable[i].name="\0";
        hashtable[i].ascii=0;
        hashtable[i].s=0;                              //初始化哈希表
    }
    for(i=0;i<Name_SIZE;i++)
    {
        key=(NameList[i].ascii)%R;                        //除留余数法
        if(hashtable[key].s == 0 )                      //未发生冲突
        {
            hashtable[key].name=NameList[i].name;
            hashtable[key].ascii=NameList[i].ascii;
            hashtable[key].s=1;
        }
        else                                                //发生冲突
          collison ( i );                                 //调用冲突函数
        
    }

}
void show()
{
    printf("******************************Hashtable_creat******************************\n");
     printf("please input \n A:print Namelist \n B:print the hash table \n C:exit\n");
}
void print_Namelist ( )
{
    int i;
    for(i=0;i<Name_SIZE;i++)
    {
        printf("number:%d\tname:%s\tascii:%d\n",i,NameList[i].name,NameList[i].ascii);
    }
}
void print_hash ( )
{   
    int i;
    float ASL=0.0;                         //平均查找长度
    for(i=0;i<HASH_SIZE;i++)
    {   
        printf("number:%d\tname:%s\tascii:%d\t%d\n",i,hashtable[i].name,hashtable[i].ascii,hashtable[i].s);
        ASL+=hashtable[i].s;
    }
    ASL=ASL/Name_SIZE;
    printf("ASL:%f\n",ASL);
}
int main()
{
  char c;
  while(1)
  {
    show( );
    init_Namelist( );
    C_hashtable( );
    printf ("please in put the order: \n");  
    scanf("%c",&c);
    getchar( );    
    switch(c)
    {
      case 'A':print_Namelist ( );break;
      case 'B' :print_hash ( );break;
      case 'C' :break;
      // default: printf("EROOR\n");break;
    }
  }
     return 0;
}