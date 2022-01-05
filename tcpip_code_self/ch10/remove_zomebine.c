#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    if(WIFEXITED(status))
    {
        printf(" Removed proc id: %d\n", id);  // 子进程的pid
        printf(" Child send : %d\n", WEXITSTATUS(status));  // 子进程的返回值
    }
}

int main(int argc, char* argv[])
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;//信号处理函数
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);
    
    //有意思的是，当两个子进程谁先死与sleep时间有关
    //而父子进程谁先输出是不一定的
    pid= fork();
    if(pid == 0)//子进程执行阶段
    {
        puts(" Hi I'm child process 1");
        sleep(5);
        return 12;
    }
    else //父进程执行阶段
    {
        printf("Child proc id :%d \n ", pid);
        pid = fork();
        if(pid == 0)
        {
            puts(" Hi! I'm child process 2 ");
            sleep(5);
            exit(24);
        }
        else
        {
            int i;
            printf("Child proc id: %d\n", pid);
            for( i = 0; i < 10; i++)
            {
                puts("wait");
                sleep(5);
            }
        }
    }
    return 0;
}