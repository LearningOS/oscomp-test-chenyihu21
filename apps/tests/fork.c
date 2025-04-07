#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 子进程
        printf("This is the child process, PID: %d\n", getpid());
    } else {
        // 父进程
        printf("This is the parent process, PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
} 