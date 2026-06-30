# ESP32-S3 简易网络收音机（Web网页控制）
[![Arduino](https://img.shields.io/badge/Arduino-ESP32S3-blue)](https://www.arduino.cc/)
[![License MIT](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![AudioI2S](https://img.shields.io/badge/lib-ESP32--audioI2S-orange)](https://github.com/schreibfaul1/ESP32-audioI2S)

基于 ESP32-S3 + MAX98357A 功放实现的**广东地区喜马拉雅网络收音机**，内置Web网页控制面板，手机/电脑连接WiFi即可切换电台、调节音量、自定义播放音频流地址。

## 项目简介
本项目使用 Arduino 框架开发，依托 `ESP32-audioI2S` 音频库解析 m3u8 网络音频流，内置广东全省各地市广播电台列表，无需按键屏幕，仅通过局域网网页完成全部操作。
- 主控：ESP32-S3（必须带PSRAM，解码音频流需要大内存）
- 音频输出：标准I2S数字音频，适配MAX98357A / PCM5102A功放模块
- 控制方式：内置WebServer，浏览器可视化操作界面
- 音频源：喜马拉雅直播m3u8广播流，覆盖广东、广州、深圳、珠三角各地电台

<img width="493"  alt="image" src="https://github.com/user-attachments/assets/2f185065-d7ff-4e68-af35-8274198b717f" />

## 功能特性
1. 📻 内置40+广东本地广播电台一键切换（音乐、新闻、交通、股市、地市综合广播）
2. 🌐 自定义音频URL输入框，支持任意公开m3u8/HTTP音频流播放
3. 🔊 网页滑块实时调节音量（音量范围 0~21）
4. 📱 手机/电脑同一局域网访问ESP32网页控制台，无需APP
5. 📶 自动WiFi连接，串口打印本机IP、连接状态、播放日志
6. 🛠 纯软件实现，无屏幕、按键、触控等外设依赖
7. 📝 网页自带状态提示，切换电台/调音量实时返回成功/失败信息

## 硬件清单
| 器件 | 说明 |
|------|------|
| ESP32-S3 开发板 | 必须搭载PSRAM（推荐8MB PSRAM） |
| I2S D类功放 | MAX98357A（推荐）/ PCM5102A |
| 扬声器 | 4Ω 3W 无源喇叭 |
| 杜邦线若干 | 用于I2S接线 |
| 5V电源 | 功放模块建议5V供电，避免音量失真 |

## I2S硬件接线（代码默认引脚）
代码中宏定义引脚：
```cpp
#define I2S_DOUT 6   // 音频数据DIN
#define I2S_BCLK 5   // I2S位时钟BCK
#define I2S_LRC 4    // 左右声道LRCK/WS
```
### 接线对照表
| ESP32-S3 | I2S功放模块 | 功能 |
|---------|------------|------|
| GPIO 6  | DIN        | 音频数据流 |
| GPIO 5  | BCLK / BCK | 位同步时钟 |
| GPIO 4  | LRC / WS   | 声道帧时钟 |
| GND     | GND        | 共地（必须连接，消除杂音） |
| 5V      | VIN        | 功放供电（3.3V音量会偏小失真） |

> 若需要修改引脚，直接修改代码顶部 `#define` 三个数字即可。

## 开发环境与依赖库
### 1. Arduino IDE 环境配置
1. 安装 Arduino IDE
2. 添加ESP32开发板管理器地址：
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
3. 开发板管理器安装 `esp32` 核心（版本 ≥2.0.10）
4. 开发板选择：`ESP32S3 Dev Module`，开启 PSRAM

### 2. 必须安装库
1. **ESP32-audioI2S**（核心音频解码库）
   GitHub地址：https://github.com/schreibfaul1/ESP32-audioI2S
   - 下载ZIP → Arduino：项目 → 加载库 → 添加.ZIP库
2. 内置标准库无需手动安装：
   - WiFi.h
   - WebServer.h
   - Arduino.h

## 快速部署步骤
### 步骤1：修改WiFi信息
打开 `esp32_s3_audio.ino`，修改顶部WiFi账号密码：
```cpp
String ssid = "你的WiFi名称";
String password = "你的WiFi密码";
```

### 步骤2：自定义电台列表（可选）
`AudioList[]` 结构体存放所有电台，格式：
```cpp
{"音频流地址", "电台显示名称"},
```
可自行新增/删除喜马拉雅或其他公开m3u8直播地址。

### 步骤3：编译上传
1. 开发板选择 ESP32-S3 Dev Module，PSRAM启用
2. 上传代码到开发板
3. 打开串口监视器（波特率115200）

### 步骤4：使用收音机
1. 上电后ESP32自动连接WiFi，串口打印局域网IP地址
2. 手机/电脑连接同一WiFi，浏览器输入打印的IP地址
3. 网页操作说明：
   - 下拉框：选择内置电台，松开自动切换播放
   - 自定义音频URL：粘贴m3u8地址，点击「播放URL」
   - 音量滑块：拖动调节，松开自动生效
   - 底部状态栏：显示操作成功/失败提示

## 代码关键逻辑说明
1. **WiFi连接**：20秒超时，连不上WiFi直接卡死等待重启
2. **音频驱动**：`audio.setPinout()` 绑定I2S引脚，默认音量15
3. **Web服务接口**
   - `/`：返回完整控制网页（内嵌HTML+JS，无外部资源依赖）
   - `/setRadio`：POST接口，切换内置电台
   - `/setVolume`：POST接口，设置音量0~21
   - `/playUrl`：POST接口，播放自定义音频流
4. **播放流程**：切换电台时先停止当前流，延时100ms再连接新URL
5. **循环任务**：`audio.loop()` 音频解码 + `server.handleClient()` 网页请求并行处理
