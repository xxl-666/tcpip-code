#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig) //信号处理器
{
    if(sig == SIGALRM)
        puts("TIME OUT!");
    alarm(2);//为了每隔2秒重复产生SIGALRM信号，在喜好处理器中掉哟个alarm函数
}
void keycontrol(int sig)//信号处理器
{
    if(sig == SIGINT)
        puts("CTRL+C pressed");
}

int main(int argc, char* argv[])
{
    int i;
    signal(SIGALRM, timeout);//注册信号以及相应处理器
    signal(SIGINT, keycontrol);
    alarm(2); //预约2秒后发生SIGALRM信号

    for (i =0; i<3 ;i++)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}