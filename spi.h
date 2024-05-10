


#define  SPI_SCK_DDR      DDRB
#define  SPI_SCK_PORT     PORTB
#define  SPI_SCK_PIN      PINB
#define  SPI_SCK_bp       0U

#define  SPI_MISO_DDR     DDRD
#define  SPI_MISO_PORT    PORTD
#define  SPI_MISO_PIN     PIND
#define  SPI_MISO_bp      4U

#define  SPI_MOSI_DDR     DDRC
#define  SPI_MOSI_PORT    PORTC
#define  SPI_MOSI_PIN     PINC
#define  SPI_MOSI_bp      0U

#define  SPI_CSN_DDR      DDRD
#define  SPI_CSN_PORT     PORTD
#define  SPI_CSN_PIN      PIND
#define  SPI_CSN_bp       7U

#define  SPI_BIT_DELAY    5
#define  SPI_BUF_SIZE     32
#define  SPI_DATA_MSB_FIRST


void     SPI_Struct_Init(void);
void     SPI_Flush_Tx_Buf(void);
void     SPI_Flush_Rx_Buf(void);

void     SPI_GPIO_Init(void);
void     SPI_Bit_Delay(void);

void     SPI_Set_SCK(uint8_t state);
uint8_t  SPI_Get_MISO(void);
void     SPI_Set_MOSI(uint8_t state);
void     SPI_Set_CSN(uint8_t state);

uint8_t  SPI_Transceive(uint8_t data);

void     SPI_Data_Flush(void);
void     SPI_Data_Add(uint8_t data);
void     SPI_Data_Fill(uint8_t *data, uint16_t len);
void     SPI_Data_Transceive(void);


uint8_t  SPI_Get_Tx_Buf(uint16_t index);
uint8_t  SPI_Get_Rx_Buf(uint16_t index);
uint16_t SPI_Get_Tx_Buf_Index(void);
uint16_t SPI_Get_Rx_Buf_Index(void);
uint8_t  SPI_Get_Rx_Data(void);
uint8_t  SPI_Get_Rx_Last(void);


void     SPI_Init(void);
