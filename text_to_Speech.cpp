#include "SynthesizerTrn.h"
#include "utils.h"
#include "Hanz2Piny.h"
#include "hanzi2phoneid.h"
#include "portaudio.h"
#include "text_to_Speech.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>



using namespace std;

void convertAudioToWavBuf(char* toBuf, char* fromBuf, int totalAudioLen) {
    char* header = toBuf;
    int byteRate = 16 * 16000 * 1 / 8;
    int totalDataLen = totalAudioLen + 36;
    int channels = 1;
    int longSampleRate = 16000;

    header[0] = 'R'; // RIFF/WAVE header
    header[1] = 'I';
    header[2] = 'F';
    header[3] = 'F';
    header[4] = (char)(totalDataLen & 0xff);
    header[5] = (char)((totalDataLen >> 8) & 0xff);
    header[6] = (char)((totalDataLen >> 16) & 0xff);
    header[7] = (char)((totalDataLen >> 24) & 0xff);
    header[8] = 'W';
    header[9] = 'A';
    header[10] = 'V';
    header[11] = 'E';
    header[12] = 'f'; // 'fmt ' chunk
    header[13] = 'm';
    header[14] = 't';
    header[15] = ' ';
    header[16] = 16; // 4 bytes: size of 'fmt ' chunk
    header[17] = 0;
    header[18] = 0;
    header[19] = 0;
    header[20] = 1; // format = 1
    header[21] = 0;
    header[22] = (char)channels;
    header[23] = 0;
    header[24] = (char)(longSampleRate & 0xff);
    header[25] = (char)((longSampleRate >> 8) & 0xff);
    header[26] = (char)((longSampleRate >> 16) & 0xff);
    header[27] = (char)((longSampleRate >> 24) & 0xff);
    header[28] = (char)(byteRate & 0xff);
    header[29] = (char)((byteRate >> 8) & 0xff);
    header[30] = (char)((byteRate >> 16) & 0xff);
    header[31] = (char)((byteRate >> 24) & 0xff);
    header[32] = (char)(1 * 16 / 8); // block align
    header[33] = 0;
    header[34] = 16; // bits per sample
    header[35] = 0;
    header[36] = 'd';
    header[37] = 'a';
    header[38] = 't';
    header[39] = 'a';
    header[40] = (char)(totalAudioLen & 0xff);
    header[41] = (char)((totalAudioLen >> 8) & 0xff);
    header[42] = (char)((totalAudioLen >> 16) & 0xff);
    header[43] = (char)((totalAudioLen >> 24) & 0xff);

    memcpy(toBuf + 44, fromBuf, totalAudioLen);
}



int text_to_speech(const char* textstring, char* modelFilePath,  char* outputWavFilePath)
{
    const Hanz2Piny hanz2piny;

    std::string line(textstring);

    // 如果字符串是UTF-8编码，并且以BOM开头，移除BOM
    if (hanz2piny.isStartWithBom(line)) {
        line = std::string(line.cbegin() + 3, line.cend());
    }

    float* dataW = NULL;
    int32_t modelSize = ttsLoadModel(const_cast<char*>(modelFilePath), &dataW);

    SynthesizerTrn* synthesizer = new SynthesizerTrn(dataW, modelSize);
    int32_t spkNum = synthesizer->getSpeakerNum();
    std::cout << "Available speakers in the model are " << spkNum << std::endl;

    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    int32_t dataLen;
    int16_t* audioData = synthesizer->infer(line, 0, 1.0, dataLen);

    int totalAudioLen = dataLen * sizeof(int16_t);
    char* wavBuf = new char[totalAudioLen + 44];
    convertAudioToWavBuf(wavBuf, reinterpret_cast<char*>(audioData), totalAudioLen);

    std::ofstream outFile(outputWavFilePath, std::ios::binary);
    outFile.write(wavBuf, totalAudioLen + 44);
    outFile.close();

    // PortAudio playback
    PaStream* stream;
    err = Pa_OpenDefaultStream(&stream, 0, 1, paInt16, 16000, 256, NULL, NULL);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    err = Pa_WriteStream(stream, audioData, dataLen);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    Pa_CloseStream(stream);
    Pa_Terminate();

    delete[] wavBuf;
    delete synthesizer;

    return 0;
}
