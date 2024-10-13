# rkllm_talking

# Description
- rkllm_talking is a standalone compiled voice communication system based on a large model, which can run locally without requiring an internet connection.
- The voice input and output of this project reference the Github projects SummerASR and SummerTTS. The Github links to the reference projects are as follows:
- SummerASR: https://github.com/huakunyang/SummerAsr
- SummerTTS: https://github.com/huakunyang/SummerTTS
- This project has been successfully compiled and run on RK3588's Ubuntu Debian 10.
- The code for running the project and the cmake-related files are on Github. Since the entire project is too large, the full project can be downloaded from Baidu Netdisk.
- Link: https://pan.baidu.com/s/1g1ucz1efKthsmbCbum4xWQ?pwd=2141 
  Extraction code: 2141
- The project's demo video is also included in the open-source repository on Github.

# Usage Instructions
- Download the project from Baidu Netdisk.
- Compile the project (if cmake reports an error, you may need to clear the cmake cache). The specific command to execute is `./build-linux.sh`.
- Place the "models" folder from the project directory at the same level as the compiled executable file. In the project, it is `./build/build_linux_aarch64_Release`.
- One thing to note: to clear the cache, you can directly delete the "build" directory, but when re-running, you need to place the "models" folder from the project directory at the same level as the executable file, which is `./build/build_linux_aarch64_Release`.
- The project directory structure is as follows:
  
  ├──build-android.sh
  
  ├──build-linux.sh
  
  ├──CMakeLists.txt
  
  ├──eigen-3.4.0
  
  ├──include
  
  ├──models
  
  ├── Readme.md
  
  ├──src
  
  └── SummerAsr-master2
  
- The rkllm deployment requires an NPU kernel version of v0.9.6 or higher.
- The project uses Qwen-1_8B, and you need to download it for usage:
- `git lfs install`
- `git clone https://huggingface.co/Qwen/Qwen-1_8B-Chat`
- After installing the PortAudio and espeak libraries, you can run the following command in the `build_linux_aarch64_Release` directory:
- `ulimit -HSn 10240`
- `./llm_demo path/qwen.rkllm ./models/single_speaker_fast.bin test.wav`

# Project Dependencies
- PortAudio, espeak, RKLLM

# Contact Information
- QQ: 2867191922
- WeChat (weixin): zjq15396069991
- Email: zhujiaqi@tiangong.edu.cn

# Acknowledgements
This project references and uses the following solutions, and we express our gratitude:
- SummerASR (https://github.com/huakunyang/SummerAsr)
- SummerTTS (https://github.com/huakunyang/SummerTTS)
- Wildfire Embedded AI Tutorial for RKLLM Deployment (https://doc.embedfire.com/linux/rk356x/Ai/zh/latest/lubancat_ai/env/rkllm.html)


========================================================================================================================================================================================



# 说明
- rkllm_talking 是一个独立编译的基于大模型的语音交流系统，是一个可以本地运行的系统，不需要连接网络
- 该项目的语音输入和输出参考自Github项目 SummerASR 和 SummerTTS ， 参考项目的Github链接如下
- SummerASR：https://github.com/huakunyang/SummerAsr
- SummerTTS：https://github.com/huakunyang/SummerTTS
- 本项目在 RK3588 的 Ubuntu Debin10 上编译运行通过
- 在github上的是项目运行的代码和cmake相关文件，因整个项目太大，故要获取整个项目的话需要在百度网盘上下载
- 链接：https://pan.baidu.com/s/1g1ucz1efKthsmbCbum4xWQ?pwd=2141 
  提取码：2141
- 项目的演示视频也置入于github开源中



# 使用说明
- 从百度网盘上下载本项目
- 进行编译（如果cmake报错可能需要清除Cmake缓存），具体执行命令为./build-linux.sh
- 将项目目录中的models置入编译后输出的可执行文件的同级目录下，项目中为./build/build_linux_aarch64_Release
- 需要注意的一点是：清除缓存可以直接删除build目录，但在再次运行时需要将项目目录中的models置入可执行文件的同级目录下，项目为./build/build_linux_aarch64_Release
- 项目目录结构为
  
  ├──build-android.sh
  
  ├──build-linux.sh
  
  ├──CMakeLists.txt
  
  ├──eigen-3.4.0
  
  ├──include
  
  ├──models
  
  ├── Readme.md
  
  ├──src
  
  └── SummerAsr-master2
  
- 其中rkllm部署需要v0.9.6 版本以上的NPU内核
- 项目使用Qwen-1_8B，使用时需要下载:
- git lfs install
- git clone https://huggingface.co/Qwen/Qwen-1_8B-Chat
- 在安装完PortAudio和espeak库后可在build_linux_aarch64_Release目录下执行执行以下命令运行：
- ulimit -HSn 10240
- ./llm_demo path/qwen.rkllm ./models/single_speaker_fast.bin test.wav

# 项目依赖
- PortAudio , espeak , RKLLM

# 联系方式
- qq:2867191922
- 微信（weixin）: zjq15396069991
- 邮箱：zhujiaqi@tiangong.edu.cn

 
# 感谢
本项目参考并使用了下列方案，在此表示感谢
- SummerASR(https://github.com/huakunyang/SummerAsr)
- SummerTTS(https://github.com/huakunyang/SummerTTS)
- 野火嵌入式AI教程RKLLM部署方案(https://doc.embedfire.com/linux/rk356x/Ai/zh/latest/lubancat_ai/env/rkllm.html)




