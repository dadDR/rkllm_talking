#include "speech_to_text.h"  // 包含语音转文字功能的头文件
#include <stdio.h>           // 标准输入输出库
#include <sys/time.h>        // 用于获取时间的库
#include <iostream>          // 用于标准输入输出流操作的库
#include <fstream>           // 文件流操作库
#include <iomanip>           // 用于控制输出格式的库
#include <sys/types.h>       // 包含数据类型定义的库
#include <sys/stat.h>        // 用于文件状态操作的库
#include <dirent.h>          // 目录操作库
#include <unistd.h>          // POSIX 操作系统 API 库
#include <cstring>           // 用于字符串操作的库，包含 strstr 函数
#include <ctime>             // 时间库
#include <stdint.h>          // 标准整数类型库
#include <vector>            // 向量容器库
#include "extract_feat.h"    // 特征提取相关的头文件
#include "asr.h"             // 自动语音识别（ASR）相关头文件
#include <portaudio.h>       // PortAudio 库，用于音频输入输出

// 定义采样率、每个缓冲区的帧数、音频通道数和采样格式
#define SAMPLE_RATE 16000          // 采样率为16000Hz
#define FRAMES_PER_BUFFER 512      // 每个缓冲区包含512帧
#define NUM_CHANNELS 1             // 单声道（一个通道）
#define SAMPLE_FORMAT paInt16      // 采样格式为16位整型


PaStream *stream;

/**
 * 函数：speech_to_text
 * 描述：录制音频并将其转换为文字。
 * 返回值：std::string，识别到的文本结果。
 */
std::string speech_to_text() {
    const int max_record_duration = 5; // 最大录音时长为5秒
    const int total_frames = SAMPLE_RATE * max_record_duration; // 总帧数，根据录音时长和采样率计算
    string asrResult;
    // 初始化 PortAudio 库
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return "";
    }

    // 打开默认音频流
    //PaStream *stream;
    err = Pa_OpenDefaultStream(&stream,
                               NUM_CHANNELS,   // 输入通道数
                               0,              // 输出通道数（这里不需要输出）
                               SAMPLE_FORMAT,  // 采样格式
                               SAMPLE_RATE,    // 采样率
                               FRAMES_PER_BUFFER, // 每个缓冲区的帧数
                               NULL,           // 没有回调函数
                               NULL);          // 没有回调函数的用户数据
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return "";
    }
    printf("开始录制\r\n");
    // 开始音频流
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return "";
    }

    // 用于存储录制的音频数据的向量
    std::vector<int16_t> wavBuf;
    int16_t buffer[FRAMES_PER_BUFFER]; // 临时缓冲区，用于存储从音频流中读取的帧
    int frames_recorded = 0; // 已录制的帧数


    printf("开始存储录制数据\r\n");

    // 循环录制音频，直到达到最大帧数
    while (frames_recorded < total_frames) {
        err = Pa_ReadStream(stream, buffer, FRAMES_PER_BUFFER); // 从流中读取数据
        if (err != paNoError) {
            std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
            break;
        }

	std::cout << "Read " << frames_recorded << " frames" << std::endl;

        // 将读取的音频数据添加到 wavBuf 中
        wavBuf.insert(wavBuf.end(), buffer, buffer + FRAMES_PER_BUFFER);
        frames_recorded += FRAMES_PER_BUFFER; // 更新已录制的帧数
    }
    std::cout << "Total frames recorded: " << frames_recorded << std::endl;

    std::cout << "Wav buffer size: " << wavBuf.size() << std::endl;
    std::cout << "Wav buffer pointer: " << static_cast<void*>(wavBuf.data()) << std::endl;

    // 停止音频流
    err = Pa_StopStream(stream);
    printf("音频流停止");
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    }
    Pa_CloseStream(stream);  // 关闭音频流
    Pa_Terminate();          // 终止 PortAudio 库

    // 获取开始时间和结束时间用于计算时间消耗
    struct timeval start, end;
    float timeuse, wavDur = static_cast<float>(wavBuf.size()) / SAMPLE_RATE; // 计算录音的时长

    gettimeofday(&start, NULL); // 获取模型加载开始时间
    void *asrData = asrInit("../model/am.model", "../model/char.txt", "../model/lm.model", false); // 初始化 ASR 模型
    gettimeofday(&end, NULL); // 获取模型加载结束时间
    timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec; // 计算模型加载时间
    std::cout << "Model loading time costs: " << std::setprecision(6) << timeuse / 1000000 << 's' << "\n"; // 输出模型加载时间

    gettimeofday(&start, NULL); // 获取 ASR 开始时间
try {
    asrResult = asrRun_without_vad(asrData, wavBuf.data(), wavBuf.size());
} catch (const std::exception &e) {
    std::cerr << "Exception caught: " << e.what() << std::endl;
}
 //   std::string asrResult = asrRun_without_vad(asrData, wavBuf.data(), wavBuf.size()); // 运行 ASR 识别，传入录音数据
    gettimeofday(&end, NULL); // 获取 ASR 结束时间


    std::cout << "Wav buffer size: " << wavBuf.size() << std::endl;
    std::cout << "Wav buffer pointer: " << wavBuf.data() << std::endl;

    std::cout << "Asr Result: " << asrResult << "\n"; // 输出识别结果
    timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec; // 计算 ASR 识别时间
    std::cout << "Wav duration: " << std::setprecision(6) << wavDur << "s, Asr Decoding time costs: " << std::setprecision(6) << timeuse / 1000000 << "s, RTF: " << std::setprecision(6) << (timeuse / 1000000) / wavDur << "\n"; // 输出识别时间和实时因子（RTF）

    return asrResult; // 返回识别结果
}

