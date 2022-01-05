#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if(sig == SIGALRM)
        puts("TIME OUT!");
    alarm(2);
}

int main( int argc, char* argv[])
{
    int i;
    struct sigaction act;
    act.sa_handler = timeout;    //保存函数指针
    sigemptyset(&act.sa_mask);   //将sa_mask函数的所有位初始化成0
    act.sa_flags = 0;            //sa_flag同样初始化成0
    sigaction(SIGALRM, &act, 0); //注册SIGALRM信号的处理器

    alarm(2); //2秒后发生SIGALARM信号

    for(int i = 0; i < 3; i++)
    {
        puts("wati...");
        sleep(100);
    }
    return 0;   
}