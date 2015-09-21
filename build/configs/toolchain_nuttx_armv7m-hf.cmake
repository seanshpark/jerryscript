# Copyright 2015 Samsung Electronics Co., Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include(CMakeForceCompiler)

set(CMAKE_SYSTEM_NAME NUTTX)
set(CMAKE_SYSTEM_PROCESSOR armv7l-hf)

set(FLAGS_COMMON_ARCH -mlittle-endian
                      -mthumb
                      -mcpu=cortex-m4
                      -march=armv7e-m
                      -mfpu=fpv4-sp-d16
                      -mfloat-abi=hard
                      -Wno-conversion)

CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)
