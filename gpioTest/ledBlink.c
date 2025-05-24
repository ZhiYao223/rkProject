/*使用 sysfs 接口控制 GPIO1_B2-----引脚编号42。
	1. gcc -o ledBlink ledBlink.c	// 编译程序
	2. sudo ./ledBlink				// 运行程序
	3. sudo ./ledBlink &   			//在后台运行

1. 设置开机启动
重新加载 systemd 配置
sudo systemctl daemon-reexec
sudo systemctl daemon-reload

2. 设置服务开机自启
sudo systemctl enable ledBlink.service

3. 立即启动一次测试
sudo systemctl start ledBlink.service

4. 查看状态（检查是否正常）
sudo systemctl status ledBlink.service

5 禁用开机启动服务:
sudo systemctl disable ledBlink.service
这将取消 ledBlink.service 在系统启动时自动运行。

6. （可选）立即停止服务, 如果你不想等重启，可以立刻停止它：
sudo systemctl stop ledblink.service

查看已启用的自启服务：
systemctl list-unit-files --type=service



*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// 目标GPIO1_B2编号
#define GPIO_NUM "42"

// 写入文件函数
void write_file(const char *path, const char *value) {
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror(path);
        exit(1);
    }
    write(fd, value, strlen(value));
    close(fd);
}

int main() {
    char path[64];

    // 1. 导出 GPIO42
    write_file("/sys/class/gpio/export", GPIO_NUM);
    usleep(100000); // 等待GPIO文件创建

    // 2. 设置方向为输出
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%s/direction", GPIO_NUM);
    write_file(path, "out");

    // 3. 进行亮灭循环
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%s/value", GPIO_NUM);
    for (int i = 0; i < 60; ++i) {  // 循环20次
        write_file(path, "0"); // 点亮LED（低电平）
        sleep(1);
        write_file(path, "1"); // 熄灭LED（高电平）
        sleep(1);
    }

    // 4. 清理 GPIO
    write_file("/sys/class/gpio/unexport", GPIO_NUM);
    return 0;
}