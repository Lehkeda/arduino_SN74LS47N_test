/*
 * -------------------------------------------------------------------
 *               SN74LS47N BCD-To-Seven Segment Decoder/Driver
 * -------------------------------------------------------------------
 * Author: Hesham El-sewify (LehKeda) 
 * Last edit: 21th of March 2019
 * Copyright 2019 Hesham El-sewify (LehKeda)
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * 
 */
  
/* ------------------ 
 * Pins defintion
 * ------------------ 
 * BI = Blanking input(BI)/Ripple blanking output(RBO)
 * RBI = Ripple blanking input
 * LT = Lamp test
 * Pins D_PIN=11, C_PIN=10, B_PIN=9, A_PIN=8, RBI_PIN=7, BI_PIN=6, LT_PIN=5
 */
int pins[8]={5, 6, 7, 8, 9, 10, 11,0};

/* ---------------------------------
 * Characters and operating modes
 * ---------------------------------
 *  - Operation RBI: turns off the segments. It needs 
 *    LT pin set to HIGH and everything else set to LOW
 *  
 *  - Operation BI: turns off the segments. It needs 
 *    BI pin set to LOW regardless of the state of any other pin
 *    
 *  - Operation LT: turns on all segments (test mode). It needs
 *    LT pin set to LOW and BI pin set to HIGH
 */

enum{
  CHAR_0=0, CHAR_1=1, CHAR_2=2, CHAR_3=3, CHAR_4=4, 
  CHAR_5=5, CHAR_6=6, CHAR_7=7, CHAR_8=8, CHAR_9=9, 
  CHAR_10=10, CHAR_11=11, CHAR_12=12, CHAR_13=13, 
  CHAR_14=14, CHAR_15=15, OP_BI=16, OP_RBI=17, OP_LT=18 };

/* Pins states expressed in bits from least significant bit (right most)
 * to most significant bit (left most) according to the order they are 
 * connected to the arudino, which is defined in the enum above, for example:
 * character 0 = 0b0000111
 *                 |||||||______
 *                / /|| \\___   |
 *               | | | \  |  |  |
 *               V V V V  V  V  V 
 *               D C B A RBI BI LT
 * 
 * character 1 = 0b0001x11
 *                 |||||||______
 *                / /|| \\___   |
 *               | | | \  |  |  |
 *               V V V V  V  V  V 
 *               D C B A RBI BI LT
 *
 * note: x means that the IC doesn't care about the state of that pin
 */
const char chars_ops[19]={
  // CHAR_0    CHAR_1     CHAR_2
  0b0000111, 0b0001111, 0b0010111, 
  
  // CHAR_3    CHAR_4     CHAR_5
  0b0011111, 0b0100111, 0b0101111, 
  
  // CHAR_6    CHAR_7     CHAR_8
  0b0110111, 0b0111111, 0b1000111, 
  
  // CHAR_9    CHAR_10   CHAR_11
  0b1001111, 0b1010111, 0b1011111, 
  
  // CHAR_12   CHAR_13   CHAR_14
  0b1100111, 0b1101111, 0b1110111,
  
  // CHAR_15   OP_BI    OP_RBI      OP_LT
  0b1111111, 0b0000000, 0b0000001, 0b0000010 };

void show_character_op(int char_op_num=0){
  for(int i=0; i<7; i++){
    digitalWrite(pins[i], bitRead(chars_ops[char_op_num], i));
  }
}

void setup() {
  // Set pins to output 
  for(int i=0; pins[i]; i++){
    pinMode(pins[i], OUTPUT);  
  }
}

void loop() {
  // Display all 16 characters
  for(int i=0; i<16; i++){
    show_character_op(i);
    if(i==15){
      delay(2000);
    }else{
      delay(500);
    }
  }

  // Test the display
  show_character_op(OP_LT);
  delay(2000);

  // Blank the display
  show_character_op(OP_BI);
  delay(2000);
}
