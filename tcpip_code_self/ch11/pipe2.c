#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int fds[2];
    char str1[] = "Who are you?";
    char str2[] = "Thank you for your message";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        write(fds[1], str1, sizeof(str1));
        sleep(2);//删掉这行会导致父进程的read一直阻塞（read本身是阻塞的）
        //因为数据进⼊管道后变成 了⽆主数据。也就是通过 read 函数先读取数据的进程将得到数据，即使该进程将数据传到了管道。

        read(fds[0], buf, BUF_SIZE);
        printf("Child proc output: %s \n", buf);
    }
    else
    {
        read(fds[0], buf, BUF_SIZE);//如果子进程不sleep就会都读取管道中的数据，而父进程因为read函数一直阻塞在这里
        printf("Parent proc output: %s \n", buf);
        write(fds[1], str2, sizeof(str2));
        sleep(3);
    }
    return 0;
}
