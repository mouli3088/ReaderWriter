#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
pthread_mutex_t w,r;
int value=90;
int readcount=0,SleepTime=5;
void *reader(void *re)
{
int temp=(int)re;
printf("\nReader%d is trying to enter",temp);
sleep(rand()%SleepTime);
pthread_mutex_lock(&r);
readcount++;
if(readcount==1)
pthread_mutex_lock(&w);
sleep(rand()%SleepTime);
printf("\nReader%d is Inside",temp);
printf("\nNumber of readers inside are %d",readcount);
printf("\nValue read by reader%d is :%d",temp,value);
pthread_mutex_unlock(&r);
pthread_mutex_lock(&r);
readcount--;
if(readcount==0)
{
pthread_mutex_unlock(&w);
}
pthread_mutex_unlock(&r);
printf("\nReader Left is %d",temp);
sleep(rand()%SleepTime);
}
void *writer(void *arg2)
{
int temp2=(int)arg2;
int writer_count;
writer_count++;
printf("\nWriter %d wants to enter",temp2);
sleep(rand()%SleepTime);
pthread_mutex_lock(&w);
printf("\nWriter entered is %d ",temp2);
value=value+10;
printf("\nValue after written by writer%d is %d",temp2,value);
sleep(rand()%SleepTime);
pthread_mutex_unlock(&w);
writer_count--;
printf("\nWriter left is %d",temp2);
sleep(rand()%SleepTime);
}
int main()
{
pthread_mutex_init(&w,NULL);
pthread_mutex_init(&r,NULL);
int n1,n2,i=0;
pthread_t tid1[10],tid2[10];
printf("\nEnter number of readers:");
scanf("%d",&n1);
printf("\nEnter number of writers:");
scanf("%d",&n2);
for(i=1;i<=n1;i++)
pthread_create(&tid1[i],NULL,reader,(void *)i);
for(i=1;i<=n2;i++)
pthread_create(&tid2[i],NULL,writer,(void *)i);
for(i=1;i<=n1;i++)
pthread_join(tid1[i],NULL);
for(i=1;i<=n2;i++)
pthread_join(tid2[i],NULL);
}
