## SN74LS47N BCD-To-Seven Segment Decoder/Driver
### Pins defintion
  - BI = Blanking input(BI)/Ripple blanking output(RBO)
  - RBI = Ripple blanking input
  - LT = Lamp test
  - Pins D_PIN=11, C_PIN=10, B_PIN=9, A_PIN=8, RBI_PIN=7, BI_PIN=6, LT_PIN=5


    int pins[8]={5, 6, 7, 8, 9, 10, 11,0};


  ###Characters and operating modes
   - Operation RBI: turns off the segments. It needs 
     LT pin set to HIGH and everything else set to LOW
   
   - Operation BI: turns off the segments. It needs 
     BI pin set to LOW regardless of the state of any other pin
     
   - Operation LT: turns on all segments (test mode). It needs
     LT pin set to LOW and BI pin set to HIGH



    enum{
          CHAR_0=0, CHAR_1=1, CHAR_2=2, CHAR_3=3, CHAR_4=4, 
          CHAR_5=5, CHAR_6=6, CHAR_7=7, CHAR_8=8, CHAR_9=9, 
          CHAR_10=10, CHAR_11=11, CHAR_12=12, CHAR_13=13, 
          CHAR_14=14, CHAR_15=15, OP_BI=16, OP_RBI=17, OP_LT=18 };
        
- Pins states expressed in bits from least significant bit (right most)
  to most significant bit (left most) according to the order they are 
  connected to the arudino, which is defined in the enum above, **for example:**


##### character 0 = 0b0000111

|0b|0|0|0|0|1|1|1|
| :----: |
||D|C|B|A|RBI|BI|LT|


 ##### character 1 = 0b0001x11
|0b|0|0|0|1|x|1|1|
| :----: |
||D|C|B|A|RBI|BI|LT|

* note: x means that the IC does not care about the state of that pin
