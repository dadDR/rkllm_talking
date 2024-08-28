#include <string.h>
#include <unistd.h>
#include <string>
#include "rkllm.h"
#include <fstream>
#include <iostream>
#include <csignal>
#include <vector>
#include "text_to_Speech.h"

#include <thread>
#include <chrono>
#include <sstream>
#include <algorithm>

#include <stdio.h>
#include <sys/time.h>
//#include <iostream>
//#include <fstream>
#include <iomanip>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
//#include <unistd.h>
//#include <string.h>
#include <ctime>
#include <stdint.h>
//#include <vector>
#include "extract_feat.h"
#include "asr.h"
#include <portaudio.h>

#define SAMPLE_RATE 16000
#define FRAMES_PER_BUFFER 512
#define NUM_CHANNELS 1
#define SAMPLE_FORMAT paInt16


#define PROMPT_TEXT_PREFIX "system You are a helpful assistant.  user"
#define PROMPT_TEXT_POSTFIX "assistant"

using namespace std;
LLMHandle llmHandle = nullptr;
char* tts_model_path;
string textfile = "outputllm.txt";

char* tts_textfile_path;

char* tts_wavfile_path;

string rkllm_answer;



void writeTextToFile(const std::string& filePath, const std::string& content) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "无法打开文件以写入: " << filePath << std::endl;
        return;
    }
    outFile << content;
    outFile.close();
}


void exit_handler(int signal)
{
    if (llmHandle != nullptr)
    {
        {
            cout << "程序即将退出" << endl;
            LLMHandle _tmp = llmHandle;
            llmHandle = nullptr;
            rkllm_destroy(_tmp);
        }
        exit(signal);
    }
}

void callback(RKLLMResult *result, void *userdata, LLMCallState state)
{
    if (state == LLM_RUN_FINISH)
    {
	
        printf("\n");

        // 读取文件内容并去掉空格和换行符
        //std::ifstream infile(textfile);
        //std::stringstream buffer;
        //buffer << infile.rdbuf();
        //std::string file_content = buffer.str();
      //  infile.close();

	//调用文字转语音的函数
//	text_to_speech(tts_textfile_path , tts_model_path , tts_wavfile_path);


        // 去掉空格和换行符
    //    file_content.erase(std::remove_if(file_content.begin(), file_content.end(), ::isspace), file_content.end());

        // 将处理后的内容存储到变量中
        //std::string processed_content = file_content;
	//打印变量来测试
	//printf("%s" , processed_content.c_str());



        // 清空文件内容
        //std::ofstream clear_file(textfile, std::ofstream::out | std::ofstream::trunc);
        //clear_file.close();

        // 调用 text_to_speech 函数输出语音
  //      text_to_speech(processed_content , tts_model_path);
    }
    else if (state == LLM_RUN_ERROR)
    {
        printf("\\run error\n");
    }
    else
    {
        printf("%s", result->text);
        
        // 将 result->text 去掉空格和换行符
        std::string clean_text(result->text);
        clean_text.erase(std::remove_if(clean_text.begin(), clean_text.end(), ::isspace), clean_text.end());
        // 将处理后的内容添加到变量中
        rkllm_answer += clean_text;


    }
}


//语音输入识别的相关定义开始
const int max_record_duration = 5; // 固定录音时长5秒
const int total_frames = SAMPLE_RATE * max_record_duration;

PaStream *stream;


//语音输入识别的相关定义结束

//PaStream *stream;//声明音频流

int main(int argc, char **argv)
{
/*
    if (argc != 3)
    {
        printf("Usage: %s <rkllm_model_path> <tts_model_path>\n", argv[0]);
        return -1;
    }*/


    if (argc != 4)
    {
    	printf("Usage: %s <rkllm_model_path> <tts_model_path> <outwavfile_path> \n" , argv[0]);
    }


    string rkllm_model(argv[1]);
    string tts_model(argv[2]);
    string output_text_file = "output_text.txt"; // 固定的文本文件路径

    string speech_input;//语音输入字符串

    tts_model_path = argv[2];
   // tts_textfile_path = argv[3];
    tts_wavfile_path = argv[3];

    signal(SIGINT, exit_handler);
    printf("rkllm init start\n");

    //设置参数及初始化
    RKLLMParam param = rkllm_createDefaultParam();
    param.model_path = rkllm_model.c_str();
    param.num_npu_core = 2;
    param.top_k = 1;
    param.max_new_tokens = 256;
    param.max_context_len = 512;
    param.logprobs = false;
    param.top_logprobs = 5;
    param.use_gpu = false;
    rkllm_init(&llmHandle, param, callback);
    printf("rkllm init success\n");

    vector<string> pre_input;
    pre_input.push_back("把下面的现代文翻译成文言文：到了春风和煦，阳光明媚的时候，湖面平静，没有惊涛骇浪，天色湖光相连，一片碧绿，广阔无际；沙洲上的鸥鸟，时而飞翔，时而停歇，美丽的鱼游来游去，岸上与小洲上的花草，青翠欲滴。");
    pre_input.push_back("以咏梅为题目，帮我写一首古诗，要求包含梅花、白雪等元素。");
    pre_input.push_back("上联: 江边惯看千帆过");
    pre_input.push_back("把这句话翻译成中文：Knowledge can be acquired from many sources. These include books, teachers and practical experience, and each has its own advantages. The knowledge we gain from books and formal education enables us to learn about things that we have no opportunity to experience in daily life. We can also develop our analytical skills and learn how to view and interpret the world around us in different ways. Furthermore, we can learn from the past by reading books. In this way, we won't repeat the mistakes of others and can build on their achievements.");
    pre_input.push_back("把这句话翻译成英文：RK3588是新一代高端处理器，具有高算力、低功耗、超强多媒体、丰富数据接口等特点");
    pre_input.push_back("通过语音输入问题");
    cout << "\n**********************可输入以下问题对应序号获取回答/或自定义输入********************\n"
         << endl;
    for (int i = 0; i < (int)pre_input.size(); i++)
    {
        cout << "[" << i << "] " << pre_input[i] << endl;
    }
//    cout << "[voice] 通过语音输入问题" << endl; // 添加语音选项提示
//    cout << "\n*************************************************************************\n"
//         << endl;


//    speech_to_text();


    while (true)
    {
        std::string input_str;
        printf("\n");
        printf("user: ");
        std::getline(std::cin, input_str);
        if (input_str == "exit")
        {
            break;
        }

        for (int i = 0; i < (int)pre_input.size(); i++)
        {
	     //如果输入语音的话，就调用语音输入
	     //
	     if(i == 4)
	     {
	     	printf("语音输入\r\n");
		
		//调用语音输入函数
	        // Initialize PortAudio
    		PaError err = Pa_Initialize();

    		if (err != paNoError) {
        		std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        		return -1;
    		}

    	        err = Pa_OpenDefaultStream(&stream,
                                           NUM_CHANNELS,
                               		   0,
                               	           SAMPLE_FORMAT,
                               		   SAMPLE_RATE,
                               		   FRAMES_PER_BUFFER,
                               		   NULL,
                               		   NULL);

    		if (err != paNoError) {
        		std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        		return -1;
    		 }
		printf("请开始说话\r\n");
    		 err = Pa_StartStream(stream);
    		if (err != paNoError) {
        		std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        		return -1;
    		}

    		std::vector<int16_t> wavBuf;
    		int16_t buffer[FRAMES_PER_BUFFER];
    		int frames_recorded = 0;


	        while (frames_recorded < total_frames) {
        		err = Pa_ReadStream(stream, buffer, FRAMES_PER_BUFFER);
        		if (err != paNoError) {
            			std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
            			break;
        		}

        		wavBuf.insert(wavBuf.end(), buffer, buffer + FRAMES_PER_BUFFER);
       		 	frames_recorded += FRAMES_PER_BUFFER;
    		}

    		err = Pa_StopStream(stream);
    		if (err != paNoError) {
        		std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    		}
		//printf("stream will close \r\n");
    		Pa_CloseStream(stream);
    		Pa_Terminate();
		//printf("stream is closed\r\n");
    		struct timeval start, end;
    		float timeuse, wavDur = static_cast<float>(wavBuf.size()) / SAMPLE_RATE;
		//printf("timeuse is cleared\r\n");
    		gettimeofday(&start, NULL);
		//printf("model will load\r\n");
    		void *asrData = asrInit("./models/am.model", "./models/char.txt", "./models/lm.model", false);
    		gettimeofday(&end, NULL);
    		timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    		std::cout << "Model loading time costs: " << std::setprecision(6) << timeuse / 1000000 << 's' << "\n";

    		gettimeofday(&start, NULL);
    		std::string asrResult = asrRun_without_vad(asrData, wavBuf.data(), wavBuf.size());
    		gettimeofday(&end, NULL);

    		std::cout << "Asr Result: " << asrResult << "\n";
    		timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    		std::cout << "Wav duration: " << std::setprecision(6) << wavDur << "s, Asr Decoding time costs: " << std::setprecision(6) << timeuse / 1000000 << "s, RTF: " << std::setprecision(6) << (timeuse / 1000000) / wavDur << "\n";
		
		
		//将语音内容置入大模型
		input_str = asrResult;

         	//speech_input = speech_to_text();
		// 打印 speech_input 的内容
    		//std::cout << "Speech Input: " << speech_input << std::endl;
   		 // 清空 speech_input 的内容
    		//speech_input.clear();
	     }
	     else if(input_str == to_string(i))
             {
                input_str = pre_input[i];  // 如果用户输入的是序号，则将其替换为对应的预设输入
                cout << input_str << endl;
             }
        }
        // 拼接前缀和后缀以生成完整的输入文本
        // string text = PROMPT_TEXT_PREFIX + input_str + PROMPT_TEXT_POSTFIX;
        string text = input_str;


        // 调用大模型
        printf("robot: ");
        rkllm_run(llmHandle, input_str.c_str(), NULL);

        // 等待回调完成并保存文本
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 确保回调完成

        // 打印处理后的内容
        printf("Processed Content: %s\n", rkllm_answer.c_str());


	text_to_speech(rkllm_answer.c_str() , tts_model_path , tts_wavfile_path);
	 	




        // 清空处理后的内容
        rkllm_answer.clear();




        // 读取大模型输出文本
 //       std::ifstream inFile("output_text.txt");
   //     if (!inFile)
     //   {
       //     cerr << "无法读取文本文件" << endl;
         //   continue;
       // }
      //  std::string output_text((std::istreambuf_iterator<char>(inFile)),
        //                        std::istreambuf_iterator<char>());

        // 调用 text_to_speech 生成语音
//        text_to_speech(output_text, tts_model);

        //inFile.close();
    }

    rkllm_destroy(llmHandle);

    return 0;
}


