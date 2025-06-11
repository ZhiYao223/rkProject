#include <chrono>
#include <thread>

#include "gpio.h"

namespace ACES{
    GPIO::GPIO() : _inProgress(false)
    {
        
    }

    GPIO::~GPIO()
    {
        // 析构函数，释放所有打开的 GPIO 线和芯片资源，防止内存泄漏。
        if (_lines.size() > 0){
            // 遍历 _lines 容器，释放每个 GPIO 线资源。
            for (auto i = _lines.begin(); i != _lines.end(); i++)
            {
                gpiod_line_release(i->second); // 释放每个 GPIO 线
            }
        }
        // 遍历 _chips 容器，释放每个 GPIO 芯片资源。
        /*这里的 _chips 是一个 std::list，存储了所有打开的 GPIO 芯片。每个芯片对应一个 /dev/gpiochip* 设备文件。
          这样可以避免资源泄漏，确保系统资源得到合理利用。*/
        if (!_chips.empty()){
            for (auto i = _chips.begin(); i != _chips.end(); i++)
            {
                gpiod_chip_close(*i); // 关闭每个芯片,确保在程序结束时，所有打开的 GPIO 资源都被正确释放。。
            }
        }
    }
    // 初始化 GPIO（通用输入输出）引脚的逻辑, 通过 libgpiod（Linux GPIO 控制库）来控制引脚
    bool GPIO::Init()
    {
        // 初始化3个指针，分别用于代表 GPIO 芯片和两个控制引脚。
        struct gpiod_chip* gpiochip1 = nullptr;           // gpiochip1 芯片
        struct gpiod_line* powerLine = nullptr;           // 代表 GPIO 控制器中的一个具体引脚 GPIO1_A4
        struct gpiod_line* directionLine = nullptr;       // 代表 GPIO 控制器中的一个具体引脚 GPIO1_B0
        
        try{
            // NET_STATUS
            // 打开一个 GPIO 芯片（类似 /dev/gpiochip1），失败则抛出异常。
            gpiochip1 = gpiod_chip_open_by_name("gpiochip1");
            if (gpiochip1 == nullptr){
                throw std::runtime_error("Failed to open gpiochip1");
            }
            // 获取编号为 4 的 GPIO 引脚，对应于 GPIO1_A4，用于控制电源开关。 A4端口 -> 4 = (0*8 + 4)
            powerLine = gpiod_chip_get_line(gpiochip1, 4);  // GPIO1_A4
            if (powerLine == nullptr){
                throw std::runtime_error("Failed to get power line");
            }
            // 获取编号为 8 的 GPIO 引脚，对应于 GPIO1_B0，用于控制电机方向。B0端口 -> 8 = (1*8 + 0)
            directionLine = gpiod_chip_get_line(gpiochip1, 8);  // GPIO1_B0s
            if (directionLine == nullptr){
                throw std::runtime_error("Failed to get direction line");
            }
            // 配置两个 GPIO 引脚为输出模式，并设置初始值:
            // 电源线：设为关闭（OFF = 0）
            gpiod_line_request_output(powerLine, "powerLine", static_cast<uint8_t>(MotoPowerState::OFF));
            // 方向线：设为顺时针（CW = 0）
            gpiod_line_request_output(directionLine, "directionLine", static_cast<uint8_t>(MotorDirection::CW));
            // 将成功打开的芯片和引脚存入类的私有成员容器中，以便之后使用和统一释放。
            _chips.push_back(gpiochip1);                    // 芯片
            _lines[MOTOR_POWER_LINE] = powerLine;           // 电机电源线
            _lines[MOTOR_DIRECTION_LINE] = directionLine;   // 电机方向线

        }
        // 如果上面任一行抛出异常（例如设备不存在、权限问题），就会进入这里，释放已申请的资源，防止内存泄漏或设备占用不释放。
        catch(...) {
            if (powerLine) gpiod_line_release(powerLine);
            if (directionLine) gpiod_line_release(directionLine);
            if (gpiochip1) gpiod_chip_close(gpiochip1);
            printf("GPIO init failed\n");
            return false;
        }
        return true;
    }
    // 设置电机的电源状态为开启（ON）或关闭（OFF），通过控制 GPIO 输出电平实现。
    void GPIO::SetMotorPower(MotoPowerState state)
    {
        // 如果参数 state 是 ON（开启），就设置引脚为高电平（1）；否则（即 OFF），设置为低电平（0）；
        gpiod_line_set_value(_lines[MOTOR_POWER_LINE], MotoPowerState::ON == state ? 1 : 0);
    }
    // 设置电机的旋转方向为顺时针（CW）或逆时针（CCW），通过控制 GPIO 输出电平实现。
    void GPIO::SetMotorDirection(MotorDirection direction)
    {
        // 如果参数 direction 是 CW（顺时针），就设置引脚为高电平（1）；否则（即 CCW），设置为低电平（0）；
        gpiod_line_set_value(_lines[MOTOR_DIRECTION_LINE], MotorDirection::CW == direction ? 1 : 0);
    }
    // 让电机顺时针（CW）转动一段指定的时间 seconds，然后自动停止，并确保运行期间不被其他操作打断。
    bool GPIO::RunCW(uint32_t seconds)
    {
        // 表示当前是否有电机运行任务正在执行；
        if (_inProgress){
            return false;    //如果已经在运行中，直接返回 false，防止重复触发多个电机运行线程。
        }
        _inProgress = true; // 标记电机正在运行。
        // 建一个新的线程，用于异步运行电机，不阻塞主线程；
        // 线程函数体内，设置电机方向为顺时针（CW），打开电机电源，休眠 seconds 秒，然后关闭电机电源，最后将 _inProgress 重置为 false。
        std::thread([this, seconds](){              // [this, seconds] 表示捕获当前对象指针和运行时间参数。
            SetMotorDirection(MotorDirection::CW);  // 设置电机为顺时针方向。
            SetMotorPower(MotoPowerState::ON);      // 启动电机（通电）。
            std::this_thread::sleep_for(std::chrono::seconds(seconds)); // 等待指定的时间（单位为秒），表示电机持续转动这段时间。
            SetMotorPower(MotoPowerState::OFF);     // 时间到了后关闭电机（断电）。
            this->_inProgress = false;              // 恢复状态，表示电机任务已完成，可以允许下一次操作。
        }).detach();                                // 将线程分离，让其自行运行并在结束后自动回收资源，不需要手动 join()；

        return true;
    }

    bool GPIO::RunCCW(uint32_t seconds)
    {
        // 防止电机重复启动（即在运行期间再次调用该函数无效）
        if (_inProgress)
            return false;    // 如果当前电机已经在运行，立即返回 false。
        _inProgress = true;  // 否则设置为 true，表示电机已启动。

        // 创建一个新的线程来控制电机的运行
        std::thread([this, seconds](){   // 捕获当前对象指针和秒数参数。
            SetMotorDirection(MotorDirection::CCW); // 设置电机方向为顺时针。
            SetMotorPower(MotoPowerState::ON);      // 打开电机电源，开始运行。
            std::this_thread::sleep_for(std::chrono::seconds(seconds)); // 当前线程休眠 seconds 秒，模拟电机运行时间
            SetMotorPower(MotoPowerState::OFF);     // 关闭电机电源，停止运行。
            this->_inProgress = false;              // 重置标志位，表示当前操作已完成，可以再次运行电机。
        }).detach();    // 表示该线程与主线程分离，主线程继续执行，线程在后台执行电机控制逻辑， 这是实现非阻塞的关键。

        return true;
    }
}
