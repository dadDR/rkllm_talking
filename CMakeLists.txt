cmake_minimum_required(VERSION 3.10)
project(llm_demo)

set(CMAKE_CXX_FLAGS " -O3 -w -std=c++11 -DNDEBUG -DKENLM_MAX_ORDER=6 ")
set(CMAKE_C_FLAGS " -O3 -w -std=c++11 -DNDEBUG -DKENLM_MAX_ORDER=6 ")

# 添加所有源文件
set(SOURCE_FILES
    src/main.cpp
    src/text_to_Speech.cpp
    
    src/tn/glog/src/demangle.cc
    src/tn/glog/src/logging.cc
    src/tn/glog/src/raw_logging.cc
    src/tn/glog/src/symbolize.cc
    src/tn/glog/src/utilities.cc
    src/tn/glog/src/vlog_is_on.cc
    src/tn/glog/src/signalhandler.cc
    src/tn/gflags/src/gflags.cc
    src/tn/gflags/src/gflags_reporting.cc
    src/tn/gflags/src/gflags_completions.cc
    src/tn/openfst/src/lib/compat.cc
    src/tn/openfst/src/lib/flags.cc
    src/tn/openfst/src/lib/fst.cc
    src/tn/openfst/src/lib/fst-types.cc
    src/tn/openfst/src/lib/mapped-file.cc
    src/tn/openfst/src/lib/properties.cc
    src/tn/openfst/src/lib/symbol-table.cc
    src/tn/openfst/src/lib/symbol-table-ops.cc
    src/tn/openfst/src/lib/util.cc
    src/tn/openfst/src/lib/weight.cc
    src/tn/processor.cc
    src/tn/token_parser.cc
    src/tn/utf8_string.cc
    src/engipa/EnglishText2Id.cpp
    src/engipa/InitIPASymbols.cpp
    src/engipa/alphabet.cpp
    src/engipa/ipa.cpp
    src/hz2py/hanzi2phoneid.cpp
    src/hz2py/Hanz2Piny.cpp
    src/hz2py/pinyinmap.cpp
    src/nn_op/nn_conv1d.cpp
    src/nn_op/nn_softmax.cpp
    src/nn_op/nn_layer_norm.cpp
    src/nn_op/nn_relu.cpp
    src/nn_op/nn_gelu.cpp
    src/nn_op/nn_tanh.cpp
    src/nn_op/nn_flip.cpp
    src/nn_op/nn_cumsum.cpp
    src/nn_op/nn_softplus.cpp
    src/nn_op/nn_clamp_min.cpp
    src/nn_op/nn_sigmoid.cpp
    src/nn_op/nn_conv1d_transposed.cpp
    src/nn_op/nn_leaky_relu.cpp
    src/platform/tts_file_io.cpp
    src/platform/tts_logger.cpp
    src/utils/utils.cpp
    src/modules/iStft.cpp
    src/modules/hann.cpp
    src/modules/attention_encoder.cpp
    src/modules/multi_head_attention.cpp
    src/modules/ffn.cpp
    src/modules/ConvFlow.cpp
    src/modules/DDSConv.cpp
    src/modules/ElementwiseAffine.cpp
    src/modules/random_gen.cpp
    src/modules/ResidualCouplingLayer.cpp
    src/modules/ResBlock1.cpp
    src/modules/WN.cpp
    src/modules/pqmf.cpp
    src/models/TextEncoder.cpp
    src/models/StochasticDurationPredictor.cpp
    src/models/FixDurationPredictor.cpp
    src/models/DurationPredictor_base.cpp
    src/models/ResidualCouplingBlock.cpp
    src/models/Generator_base.cpp
    src/models/Generator_hifigan.cpp
    src/models/Generator_MS.cpp
    src/models/Generator_Istft.cpp
    src/models/Generator_MBB.cpp
    src/models/SynthesizerTrn.cpp

    SummerAsr-master2/src/am/am.cpp
    SummerAsr-master2/src/asr/asr.cpp
    SummerAsr-master2/src/decoder/ctc_beam_search_decoder.cpp
    SummerAsr-master2/src/feat/extract_feat.cpp
    SummerAsr-master2/src/feat/hanning.cpp
    SummerAsr-master2/src/nn/nn.cpp
    SummerAsr-master2/src/decoder/scorer.cpp
    SummerAsr-master2/src/vad/vad.cpp
    SummerAsr-master2/src/vad/vad_internal_api.c
    SummerAsr-master2/src/lm/bhiksha.cc
    SummerAsr-master2/src/lm/binary_format.cc
    SummerAsr-master2/src/lm/config.cc
    SummerAsr-master2/src/lm/lm_exception.cc
    SummerAsr-master2/src/lm/model.cc
    SummerAsr-master2/src/lm/quantize.cc
    SummerAsr-master2/src/lm/read_arpa.cc
    SummerAsr-master2/src/lm/search_hashed.cc
    SummerAsr-master2/src/lm/search_trie.cc
    SummerAsr-master2/src/lm/sizes.cc
    SummerAsr-master2/src/lm/trie.cc
    SummerAsr-master2/src/lm/trie_sort.cc
    SummerAsr-master2/src/lm/value_build.cc
    SummerAsr-master2/src/lm/virtual_interface.cc
    SummerAsr-master2/src/lm/vocab.cc
    SummerAsr-master2/src/util/bit_packing.cc
    SummerAsr-master2/src/util/ersatz_progress.cc
    SummerAsr-master2/src/util/exception.cc
    SummerAsr-master2/src/util/file.cc
    SummerAsr-master2/src/util/file_piece.cc
    SummerAsr-master2/src/util/float_to_string.cc
    SummerAsr-master2/src/util/integer_to_string.cc
    SummerAsr-master2/src/util/mmap.cc
    SummerAsr-master2/src/util/murmur_hash.cc
    SummerAsr-master2/src/util/parallel_read.cc
    SummerAsr-master2/src/util/pool.cc
    SummerAsr-master2/src/util/read_compressed.cc
    SummerAsr-master2/src/util/scoped.cc
    SummerAsr-master2/src/util/spaces.cc
    SummerAsr-master2/src/util/string_piece.cc
    SummerAsr-master2/src/util/usage.cc
    SummerAsr-master2/src/util/double-conversion/bignum.cc
    SummerAsr-master2/src/util/double-conversion/bignum-dtoa.cc
    SummerAsr-master2/src/util/double-conversion/cached-powers.cc
    SummerAsr-master2/src/util/double-conversion/diy-fp.cc
    SummerAsr-master2/src/util/double-conversion/double-conversion.cc
    SummerAsr-master2/src/util/double-conversion/fast-dtoa.cc
    SummerAsr-master2/src/util/double-conversion/fixed-dtoa.cc
    SummerAsr-master2/src/util/double-conversion/strtod.cc
    SummerAsr-master2/src/librnnoise/celt_lpc.c
    SummerAsr-master2/src/librnnoise/denoise.c
    SummerAsr-master2/src/librnnoise/kiss_fft.c
    SummerAsr-master2/src/librnnoise/pitch.c
    SummerAsr-master2/src/librnnoise/rnn.c
    SummerAsr-master2/src/librnnoise/rnn_data.c


)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 设置包含目录
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/tn/glog/src/glog
    ${CMAKE_SOURCE_DIR}/src
    ./eigen-3.4.0
    ./src/tn/header
    ./include
    ./src/header
    /usr/include
    ./SummerAsr-master2/include
    ./SummerAsr-master2/src
    ./SummerAsr-master2/src/until
)

# RKLLM API 路径
set(RKLLM_API_PATH "${CMAKE_SOURCE_DIR}/../../runtime/Linux/librkllm_api")
include_directories(${RKLLM_API_PATH}/include)

# 设置 RKLLM 库路径
set(RKLLM_RT_LIB ${RKLLM_API_PATH}/aarch64/librkllmrt.so)
target_link_libraries(${PROJECT_NAME} ${RKLLM_RT_LIB})

# 确保链接 pocketsphinx 和 sphinxbase
find_package(PkgConfig REQUIRED)
pkg_check_modules(POCKETSPHINX REQUIRED pocketsphinx)
pkg_check_modules(SPHINXBASE REQUIRED sphinxbase)

include_directories(${POCKETSPHINX_INCLUDE_DIRS} ${SPHINXBASE_INCLUDE_DIRS})
link_directories(${POCKETSPHINX_LIBRARY_DIRS} ${SPHINXBASE_LIBRARY_DIRS})

# 链接所需的库
target_link_libraries(${PROJECT_NAME} ${POCKETSPHINX_LIBRARIES} ${SPHINXBASE_LIBRARIES})

# 设置 espeak 库和包含目录
set(ESPEAK_INCLUDE_DIRS /usr/include/espeak)
set(ESPEAK_LIBRARIES /usr/lib/aarch64-linux-gnu/libespeak.so)

include_directories(${ESPEAK_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${ESPEAK_LIBRARIES})

# 添加 PortAudio
find_library(PORTAUDIO_LIBRARY NAMES portaudio PATHS /usr/lib/aarch64-linux-gnu)
include_directories(/usr/include)  # 添加 PortAudio 头文件的路径
target_link_libraries(${PROJECT_NAME} ${PORTAUDIO_LIBRARY})

# 可能需要调整的其他库的路径和设置

