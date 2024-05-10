

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spi.h"

int main(void){
  
  SPI_Init();
  
while(1){
        
		SPI_Data_Flush();
		SPI_Data_Add(0x55);
		SPI_Data_Add(0x66);
		SPI_Data_Add(0x77);
		
        SPI_Data_Transceive();
		
		
		
		_delay_ms(500);
		
		
	}
}
