#include <stdio.h>
#include <sys/sysinfo.h> // 包含 sysinfo 结构体定义

int main() {
    struct sysinfo info;

    // 调用 sysinfo 系统调用
    if (sysinfo(&info) != 0) {
        perror("sysinfo failed");
        return 1;
    }

    // 打印系统信息
    printf("System Uptime: %lu seconds\n", info.uptime); // 系统启动时间（秒）
    printf("Total RAM: %lu KB\n", info.totalram); // 总物理内存（以字节为单位）
    printf("Free RAM: %lu KB\n", info.freeram); // 空闲物理内存（以字节为单位）
    printf("Shared RAM: %lu KB\n", info.sharedram); // 共享内存（以字节为单位）
    printf("Buffer RAM: %lu KB\n", info.bufferram); // 缓冲区内存（以字节为单位）
    printf("Total Swap: %lu KB\n", info.totalswap); // 总交换空间（以字节为单位）
    printf("Free Swap: %lu KB\n", info.freeswap); // 空闲交换空间（以字节为单位）
    printf("Number of Processors: %d\n", info.procs); // 当前运行的进程数
    printf("Total High Memory: %lu KB\n", info.totalhigh); // 总高位内存（以字节为单位）
    printf("Free High Memory: %lu KB\n", info.freehigh); // 空闲高位内存（以字节为单位）
    printf("Memory Unit Size: %u bytes\n", info.mem_unit); // 内存单位大小（字节）

    return 0;
}