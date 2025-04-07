#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/syscall.h>

int main() {
    struct rlimit old_limit, new_limit;

    // 获取当前进程的栈大小限制
    if (syscall(SYS_prlimit64, getpid(), RLIMIT_STACK, NULL, &old_limit) == -1) {
        perror("prlimit64 get stack limit failed");
        return 1;
    }
    printf("Current STACK limits: soft=%llu, hard=%llu\n", (unsigned long long)old_limit.rlim_cur, (unsigned long long)old_limit.rlim_max);

    // 设置新的栈大小限制
    new_limit.rlim_cur = 8 * 1024 * 1024; // 8MB
    new_limit.rlim_max = 16 * 1024 * 1024; // 16MB
    if (syscall(SYS_prlimit64, getpid(), RLIMIT_STACK, &new_limit, NULL) == -1) {
        perror("prlimit64 set new stack limit failed");
        return 1;
    }
    printf("Set new STACK limits: soft=%llu, hard=%llu\n", (unsigned long long)new_limit.rlim_cur, (unsigned long long)new_limit.rlim_max);

    // 再次获取栈大小限制，验证是否设置成功
    if (syscall(SYS_prlimit64, getpid(), RLIMIT_STACK, NULL, &old_limit) == -1) {
        perror("prlimit64 get new stack limit failed");
        return 1;
    }
    printf("New STACK limits: soft=%llu, hard=%llu\n", (unsigned long long)old_limit.rlim_cur, (unsigned long long)old_limit.rlim_max);

    return 0;
}