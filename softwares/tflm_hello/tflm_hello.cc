/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "main_functions.h"
#include "platform.h"
#include "uart.h"

int main(int argc, char* argv[]) {
  float y;
  setup();
  
  // a value between 0 and 20 (inference per cycle)
  y = run_inference(1.2423);

  // asm (
  //   "fadd f31, f31, (%[y])\n"
  //   :
  //   : [y] "r" (y)
  // );
  
  if(y > 0.8 && y < 1.0){
    asm (
      "addi x31, x0, 1\n"
    );
  }
  
}
