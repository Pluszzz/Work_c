#include<stdio.h>
#include<math.h>
int jiecheng(int);
int main(void)
{
    double x;//指数
    double z;//精度
    double y=0;//结果
    scanf("%lf",&x);
    scanf("%lf",&z);
    double i=0;//计数单位
    do{
      if(i==0)
      {
          y+=1;//麦克劳林的第一项1
      }
      else
      {
          y+=pow(x,i)/jiecheng(i);//从第二项开始pow(x,i)表示x的i次方，jiecheng()是一个阶乘函数
      }
      i++;
    }while(pow(x,i)/jiecheng(i)>z);//当pow(x,i)绝对值<e时跳出循环
    printf("%f",y);
}
int jiecheng(int n)
{
    int m=1,i;
    if(n==0)
    {
        return 1;
    }
    for(i=n;i!=1;i--)
    {
        m*=i;
    }
    return m;

}