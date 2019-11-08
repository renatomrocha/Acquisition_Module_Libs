#ifndef MAX11632_H
#define MAX11632_H

//Conversion Register Messages


			



//Setup Register Messages

#define MAX11632_SETUP1					0x6A
#define MAX11632_SETUP2					0x7A
#define MAX11632_SETUP3					0x4A
#define MAX11632_SETUP4					0x5A


#define MAX11632_RESET_FIFO				0x08


//Averaging Register
#define MAX11632_AVG					0x00

#define EOC                             5





typedef enum
{
MAX11632_RC_0 = 0x86,    //Read_Channel 0 
MAX11632_RC_1 = 0x8E,    //Read_Channel 1
MAX11632_RC_2 = 0x96,    //Read_Channel 2 
MAX11632_RC_3 = 0x9E,    //Read_Channel 3
MAX11632_RC_4 = 0xA6 ,   //Read_Channel 4
MAX11632_RC_5 = 0xAE , 
MAX11632_RC_6 = 0xB6 , 
MAX11632_RC_7 = 0xBE , 
MAX11632_RC_8 = 0xC6 , 
MAX11632_RC_9 = 0xCE ,
MAX11632_RC_10 = 0xD6 ,
MAX11632_RC_11 = 0xDE ,
MAX11632_RC_12 = 0xE6 ,
MAX11632_RC_13 = 0xEE ,
MAX11632_RC_14 = 0xF6 ,
/////////////////////////////////MULTI CHANNELS
MAX11632_RCU_1	 = 0x88,    //Read_Channel 0 
MAX11632_RCU_2 = 0x90,
MAX11632_RCU_3 = 0x98,
MAX11632_RCU_4 = 0xA0,
MAX11632_RCU_5 = 0xA8,
MAX11632_RCU_6 = 0xB0,
MAX11632_RCU_7 = 0xB8,
MAX11632_RCU_8 = 0xC0,
MAX11632_RCU_9 = 0xC8,
MAX11632_RCU_10 = 0xD0,
MAX11632_RCU_11 = 0xD8,
MAX11632_RCU_12 = 0xE0,
MAX11632_RCU_13 = 0xE8,
MAX11632_RCU_14 = 0xF0,


} max11632_channels;





#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class MAX11632 {
 public:
  MAX11632(int8_t spi_cs, int8_t spi_mosi, int8_t spi_miso, int8_t spi_clk);
  MAX11632(void);

  boolean begin(void);
  void send_conf(void);
  uint16_t readSingleChannel(uint8_t n_channel);
  void readMultipleChannels(uint16_t buffer[], uint8_t n_channel);
  float Convert_to_Voltage(uint16_t val);
  
 private:
 
  int8_t _sclk, _miso, _mosi, _cs;
  void activateCS(int8_t s);
  
  max11632_channels selectChannel(uint8_t channel,bool mult);

  void requestRead(uint8_t data);
  void SingleRead(uint8_t buffer[2]);
  void MultipleRead(uint16_t buffer[], uint8_t n_channel);
  void spiReadSingle(uint8_t buffer[2]);
  void spiReadMultiple(uint16_t buffer[], uint8_t n_channel);
  void spiSend(uint8_t x);
  void reset_fifo(void);
  
  };

#endif
