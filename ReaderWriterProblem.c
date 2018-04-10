#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
pthread_mutex_t writeraccess,readeraccess;
int value=90,rc,wc;
int readcount=0,SleepTime=5;
void *reader(void *arg1)
{
int rc=*((int *)arg1)+1;
 
printf("\nReader%d is trying to enter",rc);
sleep(rand()%SleepTime);
pthread_mutex_lock(&readeraccess);
readcount++;

if(readcount==1)
{
pthread_mutex_lock(&writeraccess);
}
printf("\nReader%d is Inside",rc);
printf("\nNumber of readers inside are %d",readcount);
printf("\nValue read by reader%d is :%d",rc,value);
pthread_mutex_unlock(&readeraccess);
sleep(rand()%SleepTime);
pthread_mutex_lock(&readeraccess);
readcount--;
printf("\nReader leaving ..."); 
sleep(rand()%SleepTime);
if(readcount==0)
{
pthread_mutex_unlock(&writeraccess);
}
pthread_mutex_unlock(&readeraccess);

printf("\nReader Left is %d",rc);
sleep(rand()%SleepTime);
}
void *writer(void *arg2)
{
wc++;
printf("\nWriter %d wants to enter",wc);
sleep(rand()%SleepTime);
pthread_mutex_lock(&writeraccess);
printf("\nWriter entered is %d ",wc);
value=value+10;
printf("\nValue after written by writer%d is %d",wc,value);
sleep(rand()%SleepTime);
pthread_mutex_unlock(&writeraccess);
 wc--;
printf("\nWriter left is %d",wc+1);
sleep(rand()%SleepTime);
}
int main()
{
int n1,n2,i=0;
printf("\nEnter number of readers(Max 10):");
scanf("%d",&n1);
printf("\nEnter number of writers(Max 10):");
scanf("%d",&n2);
pthread_mutex_init(&writeraccess,NULL);
pthread_mutex_init(&readeraccess,NULL);
pthread_t tid1[10],tid2[10];
for(i=0;i<n1;i++)
{
pthread_create(&tid1[i],NULL,reader,&i);
}
for(i=0;i<n2;i++)
{
pthread_create(&tid2[i],NULL,writer,&i);
}
for(i=0;i<n1;i++)
{
pthread_join(tid1[i],NULL);
}
for(i=0;i<n2;i++)
{
  pthread_join(tid2[i],NULL);
}
}
