
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spi.h"

typedef struct spi_t{
  uint8_t  TxBuf[SPI_BUF_SIZE];
  uint8_t  RxBuf[SPI_BUF_SIZE];
  uint8_t  RxLast;
  uint16_t TxIndex;
  uint16_t RxIndex;
}spi_t;

spi_t SPI;

void SPI_Struct_Init(void){
  SPI_Flush_Tx_Buf();
  SPI_Flush_Rx_Buf();
}

void SPI_Flush_Tx_Buf(void){
  for(uint16_t i=0;i<SPI_BUF_SIZE;i++){
    SPI.TxBuf[i]=0;
  }
  SPI.TxIndex=0;
}

void SPI_Flush_Rx_Buf(void){
  for(uint16_t i=0;i<SPI_BUF_SIZE;i++){
    SPI.RxBuf[i]=0;
  }
  SPI.RxIndex=0;
  SPI.RxLast=0;
}

void SPI_GPIO_Init(void){
  SPI_SCK_DDR  |= (1<<SPI_SCK_bp);
  SPI_MISO_DDR &=~(1<<SPI_MISO_bp);
  SPI_MOSI_DDR |= (1<<SPI_MOSI_bp);
  SPI_CSN_DDR  |= (1<<SPI_CSN_bp);
  
  SPI_SCK_PORT &=~(1<<SPI_SCK_bp);
  SPI_MISO_PORT|= (1<<SPI_MISO_bp);
  SPI_MOSI_PORT&=~(1<<SPI_MOSI_bp);
  SPI_CSN_PORT |= (1<<SPI_CSN_bp);
}

void SPI_Bit_Delay(void){
  _delay_us(SPI_BIT_DELAY);
}

void SPI_Set_SCK(uint8_t state){
  if(state==1){
    SPI_SCK_PORT |= (1<<SPI_SCK_bp);
  }else{
    SPI_SCK_PORT &=~(1<<SPI_SCK_bp);
  }
}

uint8_t SPI_Get_MISO(void){
  if(SPI_MISO_PIN & (1<<SPI_MISO_bp)){
    return 1;
  }else{
    return 0;
  }
}

void SPI_Set_MOSI(uint8_t state){
  if(state==1){
    SPI_MOSI_PORT |= (1<<SPI_MOSI_bp);
  }else{
    SPI_MOSI_PORT &=~(1<<SPI_MOSI_bp);
  }
}

void SPI_Set_CSN(uint8_t state){
  if(state==1){
    SPI_CSN_PORT  |= (1<<SPI_CSN_bp);
  }else{
    SPI_CSN_PORT  &=~(1<<SPI_CSN_bp);
  }
}

uint8_t SPI_Transceive(uint8_t data){
  uint8_t rx_data=0;
  SPI_Bit_Delay();
  
  #ifdef SPI_DATA_MSB_FIRST
  for(uint8_t i=0;i<8;i++){
    if(data & 0x80){
	  SPI_Set_MOSI(1);
	}else{
	  SPI_Set_MOSI(0);
	}
	data<<=1;
	SPI_Bit_Delay();
	SPI_Set_SCK(1);
	rx_data<<=1;
	rx_data |= SPI_Get_MISO();
	SPI_Bit_Delay();
	SPI_Set_SCK(0);
	SPI_Bit_Delay();
  }
  #else
  for(uint8_t i=0;i<8;i++){
    if(data & 0x01){
	  SPI_Set_MOSI(1);
	}else{
	  SPI_Set_MOSI(0);
	}
	data>>=1;
	SPI_Bit_Delay();
	SPI_Set_SCK(1);
	rx_data |= (SPI_Get_MISO()<<i);
	SPI_Bit_Delay();
	SPI_Set_SCK(0);
	SPI_Bit_Delay();
  }
  #endif
  
  SPI_Set_MOSI(0);
  return 0;
}


void SPI_Data_Flush(void){
  SPI_Flush_Tx_Buf();
  SPI_Flush_Rx_Buf();
}

void SPI_Data_Add(uint8_t data){
  SPI.TxBuf[SPI.TxIndex] = data;
  SPI.TxIndex++;
  if(SPI.TxIndex>=SPI_BUF_SIZE){
    SPI.TxIndex=0;
  }
}

void SPI_Data_Fill(uint8_t *data, uint16_t len){
  for(uint16_t i=0;i<len;i++){
    SPI_Data_Add(data[i]);
  }
}

void SPI_Data_Transceive(void){
  SPI_Set_CSN(0);
  for(uint16_t i=0;i<SPI.TxIndex;i++){
    SPI.RxBuf[SPI.RxIndex] = SPI_Transceive(SPI.TxBuf[i]);
	SPI.RxLast = SPI.RxBuf[SPI.RxIndex];
	SPI.RxIndex++;
	if(SPI.RxIndex>=SPI_BUF_SIZE){
	  SPI.RxIndex=0;
	}
  }
  SPI_Set_CSN(1);
}



uint8_t SPI_Get_Tx_Buf(uint16_t index){
  return SPI.TxBuf[index];
}

uint8_t SPI_Get_Rx_Buf(uint16_t index){
  return SPI.RxBuf[index];
}

uint16_t SPI_Get_Tx_Buf_Index(void){
  return SPI.TxIndex;
}

uint16_t SPI_Get_Rx_Buf_Index(void){
  return SPI.RxIndex;
}

uint8_t SPI_Get_Rx_Data(void){
  uint8_t temp = SPI.RxBuf[SPI.RxIndex];
  SPI.RxIndex++;
  return temp;
}

uint8_t SPI_Get_Rx_Last(void){
  return SPI.RxLast;
}


void SPI_Init(void){
  SPI_GPIO_Init();
  
}