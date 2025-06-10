#pragma once

#include <gpiod.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <list>
#include <map>

namespace ACES{
    // 表示电机电源状态：关闭或开启
    enum class MotoPowerState{
        OFF,
        ON
    };
    // 电机转动方向
    enum class MotorDirection{
        CW, // 顺时针
        CCW //逆时针
    };
    //  电源控制线和方向控制线的 GPIO 编号, 这两个宏用于从 chip 中获取对应的 GPIO 引脚。
    #define         MOTOR_POWER_LINE        0   //电源控制线
    #define         MOTOR_DIRECTION_LINE    1   //方向控制线

    //基于单例模式的硬件控制接口（如 GPIO）
    class GPIO{
    public:
        // 单例模式： 单例模式的核心思想是：一个类只创建一个实例，并提供一个全局访问点。
        // 单例获取函数，防止创建多个 GPIO 控制实例，避免资源冲突。 单例模式-懒汉式，是线程安全的
        static GPIO& GetInstance(){
            static GPIO io;    // 局部静态变量，只在第一次调用时构造一次 GPIO 实例，且这个实例会在所有调用中共享。
            return io;         // 返回对这个唯一实例的引用
        }
        ~GPIO();
    protected:
        GPIO();     //构造函数不允许外部new出对象
    private:
        // 用于存储系统中打开的 GPIO 控制器（chip），支持多个 /dev/gpiochip*。
        std::list<struct gpiod_chip*> _chips;
        // 保存用到的 GPIO 线，如：_lines[0] 表示电源控制线，_lines[1] 表示方向控制线。
        std::map<int, struct gpiod_line*> _lines;
        // 表示电机当前是否正在运行中（可能用于防止重复调用）
        bool _inProgress;

    public:
        bool Init();                                               // 初始化
        void SetMotorPower(MotoPowerState state);                  // 控制电机是否供电
        void SetMotorDirection(MotorDirection direction);          // 控制电机转动方向
        bool RunCW(uint32_t seconds);                              // 电机顺时针运行seconds秒
        bool RunCCW(uint32_t seconds);                             // 电机逆时针运行seconds秒
    };
}
