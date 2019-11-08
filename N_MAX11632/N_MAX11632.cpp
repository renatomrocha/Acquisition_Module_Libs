#include "N_MAX11632.h"
#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif

#include <stdlib.h>
#include <SPI.h>

static SPISettings max11632_spisettings = SPISettings(500000, MSBFIRST, SPI_MODE0);



// Software (bitbang) SPI
MAX11632::MAX11632(int8_t spi_cs, int8_t spi_mosi, int8_t spi_miso, int8_t spi_clk) {
  _sclk = spi_clk;
  _cs = spi_cs;
  _miso = spi_miso;
  _mosi = spi_mosi;

}

// Hardware SPI init
MAX11632::MAX11632(void) {
  _sclk = _miso = _mosi = -1;
  
  }

//Rotina de iniciação do objeto MAX11632
boolean MAX11632::begin(void) {
  pinMode(9, OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(EOC, INPUT);
  activateCS(0);

  if (_sclk != -1) {
    //define pin modes
    pinMode(_sclk, OUTPUT); 
    pinMode(_mosi, OUTPUT); 
    pinMode(_miso, INPUT);
  } else {
    //start and configure hardware SPI
    SPI.begin();
  }

  //reset_fifo();
  

  return true;
}

void MAX11632::send_conf(void) {

  requestRead(MAX11632_SETUP1);
	
	
}

void MAX11632::reset_fifo(void) {

  requestRead(MAX11632_RESET_FIFO);
 
	
	
}

uint16_t MAX11632::readSingleChannel(uint8_t n_channel) {
	//Reads single channel 
	max11632_channels command;
	command = selectChannel(n_channel,false);

	uint8_t buffer[2]={0,0};
	uint16_t An_val;
	float V_val;
	requestRead(command);
	
	SingleRead(buffer);
	
	An_val = buffer[0] << 8 | buffer[1];
	return An_val;
}



void MAX11632::readMultipleChannels(uint16_t buffer[], uint8_t n_channel) {
	//Reads multiple channels from 0 - (n_channel)
	//Fills buffer with values read from FIFO
	
	max11632_channels command;
	
	command = selectChannel(n_channel , true);
	
	requestRead(command);
	//delay(1);
	MultipleRead(buffer , n_channel);
	

}





/********************************************** BASIC FUNCTIONS *******************************************************************************/
void MAX11632::requestRead(uint8_t data) {
  
	//uint16_t read= 0x0000;
  // Inicia ciclo de clock
  SPI.beginTransaction(max11632_spisettings); 

  // Efetua chip Select
  activateCS(1);  
  
  delay(5);
  
  // Envio de dados
 spiSend(data); 

  
   // Deactivate CS
  activateCS(0);
  while(EOC==HIGH){Serial.println("Converting...");}
  // Terminate CLK	
  SPI.endTransaction();
  
 
  
  }

  
  
void MAX11632::SingleRead(uint8_t buffer[2]) {
   uint16_t rep;
  
   SPI.beginTransaction(max11632_spisettings); // Inicia ciclo de clock


  activateCS(1);  // Efetua chip Select
  
  delay(5);
  
  spiReadSingle(buffer); // Envio de dados
	
 activateCS(0);
   SPI.endTransaction();
   
  
}

void MAX11632::MultipleRead(uint16_t buffer[], uint8_t n_channel) {
   uint16_t rep;
  
   SPI.beginTransaction(max11632_spisettings); // Inicia ciclo de clock


  activateCS(1);  // Efetua chip Select
  
  delay(5);
  
  spiReadMultiple(buffer,n_channel); // Envio de dados
	
 activateCS(0);
   SPI.endTransaction();
   
  
}

void MAX11632::spiReadSingle(uint8_t buffer[]){
	
	
	uint16_t mask = 0x0FFF;
	
	for(uint8_t i = 0; i<2;i++){
	buffer[i]= SPI.transfer(0x00);
	}
	


}  


void MAX11632::spiReadMultiple(uint16_t buffer[], uint8_t n_channel) {
	uint8_t var[2] = {0,0};
	
	uint16_t mask = 0x0FFF;
	for(uint8_t j=0; j<=n_channel;j++){
		for(uint8_t i = 0; i<2;i++){
		var[i]= SPI.transfer(0x00);
		}
	buffer[j]= var[0] << 8 | var[1];
	
	}
	

}  



//////////////////////////////////////////////////////////////////////////////////////////////////////////

float MAX11632::Convert_to_Voltage(uint16_t val){
	float declive = 0.001220703125;
	
	float voltage = declive * val;
	
	return voltage;
}


void MAX11632::spiSend(uint8_t x) {
   
	SPI.transfer(x);
  
  }
 

 max11632_channels MAX11632::selectChannel(uint8_t channel, bool mult){
	max11632_channels command;
	
	if (!mult){
	switch(channel){
		case 0:
			command = MAX11632_RC_0;
			break;
		case 1:
			command = MAX11632_RC_1;
			break;
		case 2:
			command = MAX11632_RC_2;
			break;
		case 3:
			command = MAX11632_RC_3;
			break;
		case 4:
			command = MAX11632_RC_4;
			break;
		case 5:
			command = MAX11632_RC_5;
			break;
		case 6:
			command = MAX11632_RC_6;
			break;
		case 7:
			command = MAX11632_RC_7;
			break;
		case 8:
			command = MAX11632_RC_8;
			break;
		case 9:
			command = MAX11632_RC_9;
			break;
		case 10:
			command = MAX11632_RC_10;
			break;
		case 11:
			command = MAX11632_RC_11;
			break;
		case 12:
			command = MAX11632_RC_12;
			break;
		case 13:
			command = MAX11632_RC_13;
			break;
		case 14:
			command = MAX11632_RC_4;
			break;
	
	}
	}
	else{
		switch(channel){
		case 1:
			command = MAX11632_RCU_1;
			break;
		case 2:
			command = MAX11632_RCU_2;
			break;
		case 3:
			command = MAX11632_RCU_3;
			break;
		case 4:
			command = MAX11632_RCU_4;
			break;
		case 5:
			command = MAX11632_RCU_5;
			break;
		case 6:
			command = MAX11632_RCU_6;
			break;
		case 7:
			command = MAX11632_RCU_7;
			break;
		case 8:
			command = MAX11632_RCU_8;
			break;
		case 9:
			command = MAX11632_RCU_9;
			break;
		case 10:
			command = MAX11632_RCU_10;
			break;
		case 11:
			command = MAX11632_RCU_11;
			break;
		case 12:
			command = MAX11632_RCU_12;
			break;
		case 13:
			command = MAX11632_RCU_13;
			break;
		case 14:
			command = MAX11632_RCU_4;
			break;
	
	}
		
		
	}
	//Serial.println(command,HEX);
	return command;
	
}

 
 
 


 
void MAX11632::activateCS(int8_t slot){
switch(slot){
	
	case 1:
		digitalWrite(9, HIGH);
		digitalWrite(10, LOW);
		digitalWrite(11, HIGH);
		digitalWrite(12, LOW);
		break;
	
	case 0:
		
		digitalWrite(9 , HIGH);
		digitalWrite(10, HIGH);
		digitalWrite(11, HIGH);
		digitalWrite(12, HIGH);
		break;
		
		}
}