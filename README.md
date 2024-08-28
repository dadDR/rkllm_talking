# rkllm_talking

# 说明
- rkllm_talking 是一个独立编译的基于大模型的语音交流系统，是一个可以本地运行的系统，不需要连接网络
- 该项目的语音输入和输出参考自Github项目 SummerASR 和 SummerTTS ， 参考项目的Github链接如下
- SummerASR：https://github.com/huakunyang/SummerAsr
- SummerTTS：https://github.com/huakunyang/SummerTTS
- 本项目在 RK3588 的 Ubuntu Debin10 上编译运行通过


# 使用说明
- 将本项目的代码克隆到本地
- 进行编译（如果cmake报错可能需要清除Cmake缓存），具体执行命令为./build-linux.sh
- 将项目目录中的models置入编译后输出的可执行文件的同级目录下，项目中为./build/build_linux_aarch64_Release
- 需要注意的一点是：清除缓存可以直接删除build目录，但在再次运行时需要将项目目录中的models置入可执行文件的同级目录下，项目为./build/build_linux_aarch64_Release
- 项目目录结构为
  
  ├──build
  
  ├──build-android.sh
  ├──build-linux.sh
  ├──CMakeLists.txt
  ├──eigen-3.4.0
  ├──include
  ├──models
  ├── Readme.md
  ├──src
  ├──SummerAsr-master2 
- 其中rkllm部署需要v0.9.6 版本以上的NPU内核
- 项目使用Qwen-1_8B，使用时需要下载:
- git lfs install
- git clone https://huggingface.co/Qwen/Qwen-1_8B-Chat
- 在安装完PortAudio和espeak库后可在build_linux_aarch64_Release目录下执行执行以下命令运行：
- ulimit -HSn 10240
- ./llm_demo path/qwen.rkllm ./models/single_speaker_fast.bin test.wav

# 项目依赖
- PortAudio , espeak , RKLLM 

 
# 感谢
本项目参考并使用了下列方案，在此表示感谢
- SummerASR(https://github.com/huakunyang/SummerAsr)
- SummerTTS(https://github.com/huakunyang/SummerTTS)
- 野火嵌入式AI教程RKLLM部署方案(https://doc.embedfire.com/linux/rk356x/Ai/zh/latest/lubancat_ai/env/rkllm.html)





