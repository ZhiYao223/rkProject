以下是你提供的 `README.md` 文档的全文中文翻译（**命令行部分保持原样**）：
---

# 用于 LVGL 的 VSCode 模拟器项目

[LVGL](https://github.com/lvgl/lvgl) 主要是为微控制器和嵌入式系统编写的，不过你也可以在 **个人电脑上运行这个库**，无需任何嵌入式硬件。在 PC 上编写的代码可以直接复制到嵌入式系统中使用。

本项目已为 VSCode 预先配置，并可以在 Windows、Linux 和 macOS 上运行。项目中还包含了 FreeRTOS，可选启用，以更好地模拟嵌入式系统的行为。

---

## 快速开始

### 安装 SDL 和构建工具

* **Windows（使用 vcpkg）：** `vcpkg install sdl2`（`vcpkg` 可从 [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg) 安装），还需安装 MinGW 或其他编译器和 `cmake`。
* **macOS（使用 Homebrew）：** `brew install sdl2 cmake make`
* **Linux：**

  * **Debian/Ubuntu：** `sudo apt install build-essential cmake libsdl2-dev`
  * **Arch：** `sudo pacman -S base-devel cmake sdl2`
  * **Fedora：** `sudo dnf install @development-tools cmake SDL2-devel`
* **手动安装 SDL：** 可从 [SDL 官方网站](https://github.com/libsdl-org/SDL/releases) 下载并将头文件/库文件放入项目中。
* **验证安装：** 使用以下命令确认是否安装成功：`sdl2-config --version`、`cmake --version`、`gcc --version`、`g++ --version`

### 获取 PC 项目

克隆 PC 端项目及其相关子模块：

```bash
git clone --recursive https://github.com/lvgl/lv_port_pc_vscode
```

---

## 使用说明

### Visual Studio Code

1. 请确保已安装好 [SDL 和构建工具](#install-sdl-and-build-tools)
2. 双击 `simulator.code-workspace` 或通过 VSCode 的 `File/Open Workspace from File` 打开项目
3. 安装推荐的插件
4. 点击左侧的“运行和调试”页面，并在顶部下拉菜单中选择 `Debug LVGL demo with gdb`，如下图所示：
   ![image](https://github.com/lvgl/lv_port_pc_vscode/assets/7599318/f527b235-5718-4949-b5f0-bd807b3a64ba)
5. 点击播放按钮或按 F5 开始调试

#### ArchLinux 用户

由于 VSCode 官方未提供 Arch 的安装包，需要使用 AUR 管理器 `paru` 进行安装。命令如下：

```bash
paru -S visual-studio-code-bin
```

#### macOS

Apple 默认的 clang 不支持 `-fsanitize=leak` 标志。

要使用 Homebrew 安装的最新版 clang 编译，请执行以下步骤：

1. `brew install llvm`
2. 按下 `cmd+shift+p`，运行 `Cmake: select a kit`，然后选择 `[Scan for kits]`
3. 再次 `cmd+shift+p`，运行 `Cmake: select a kit`，选择刚刚安装的 clang（应显示为 `Using compilers C=/opt/homebrew/opt/llvm/bin/clang ...`）
4. 运行 `cmd+shift+p`，执行 `Cmake: Configure` 重新配置
5. 使用上面第 4 步的方法进行构建

---

### FreeRTOS 配置说明

要正确配置本项目，RTOS（实时操作系统）需要大量堆内存，特别是在调试 SDL 窗口应用时。本项目中已将堆大小设置为 **512 MB**（经过实验验证）：

```c
#define configTOTAL_HEAP_SIZE ( ( size_t ) ( 512 * 1024 * 1024 ) )  // 512 MB Heap
```

该设置能确保 SDL 窗口及时显示。如果减小此值，可能会导致 SDL 窗口严重延迟，甚至无法显示。因此必须分配足够的堆内存，才能顺利调试和运行。

---

### 启用 FreeRTOS

要启用本项目中的 RTOS 部分，请在 `lv_conf.h` 中将：

```c
#define LV_USE_OS   LV_OS_NONE
```

修改为：

```c
#define LV_USE_OS   LV_OS_FREERTOS
```

另外，还需要在 `CMakeLists.txt` 中启用 FreeRTOS 所有文件的编译，即将：

```cmake
option(USE_FREERTOS "Enable FreeRTOS" OFF)
```

修改为：

```cmake
option(USE_FREERTOS "Enable FreeRTOS" ON)
```

---

### 使用 CMake 构建

本项目使用了 CMake 构建系统，即使不使用 VSCode 也可以进行编译，只需在项目根目录中运行以下命令：

```bash
mkdir build
cd build
cmake ..
make -j
```

---

## 可选库

项目还支持 FreeType 和 FFmpeg，你可以按以下方式进行安装：

### Linux

```bash
# FreeType 支持
wget https://kumisystems.dl.sourceforge.net/project/freetype/freetype2/2.13.2/freetype-2.13.2.tar.xz
tar -xf freetype-2.13.2.tar.xz
cd freetype-2.13.2
make
make install
```

```bash
# FFmpeg 支持
git clone https://git.ffmpeg.org/ffmpeg.git ffmpeg
cd ffmpeg
git checkout release/6.0
./configure --disable-all --disable-autodetect --disable-podpages --disable-asm --enable-avcodec --enable-avformat --enable-decoders --enable-encoders --enable-demuxers --enable-parsers --enable-protocol='file' --enable-swscale --enable-zlib
make
sudo make install
```

---

### (RT)OS 支持

本项目可以在各种操作系统上运行，例如 pthread、Windows、FreeRTOS 等。对 FreeRTOS 提供了内置支持。

---

## 测试说明

该项目专为 [VSCode](https://code.visualstudio.com) 配置，已在以下平台测试通过：

* Ubuntu Linux
* Windows WSL（Ubuntu Linux）

要求你的系统中已正确安装并配置好以下工具：

* GCC
* GDB
* make

要在 VSCode 中启用调试功能，还需要安装 GDB 插件（如：[这个扩展](https://marketplace.visualstudio.com/items?itemName=webfreak.debug)），项目中所有构建和调试设置都已预先配置在 `.workspace` 文件中。

本项目默认使用 **SDL**，但也可以替换为其他内置的 LVGL 驱动。

---

如需将本翻译版本导出为 PDF、Markdown 或 HTML，欢迎告诉我，我可以继续为你整理输出。是否需要？
