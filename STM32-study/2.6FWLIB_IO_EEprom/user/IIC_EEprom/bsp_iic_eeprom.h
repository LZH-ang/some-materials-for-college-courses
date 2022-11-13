#ifndef __bsp_iic_eeprom_H
#define __bsp_iic_eeprom_H

#include "stm32f10x.h"
#include "bsp_usart.h"

/*��Ϣ���*/
#define EEPROM_DEBUG_ON         		0
#define EEPROM_INFO(fmt,arg...)     printf("<<-EEPROM-INFO->> "fmt"\n",##arg)
#define EEPROM_ERROR(fmt,arg...)    printf("<<-EEPROM-ERROR->> "fmt"\n",##arg)
#define EEPROM_DEBUG(fmt,arg...)    do{\
																	  if(EEPROM_DEBUG_ON)\
                                    printf("<<-EEPROM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                    }while(0)

/* �����ַֻҪ��STM32��ҵ�I2C������ַ��һ������ */
#define I2Cx_OWN_ADDRESS7      0X0A   
/* AT24C01/02ÿҳ��8���ֽ� */
#define EEPROM_PageSize           8
/* AT24C04/08A/16Aÿҳ��16���ֽ� */
//#define I2C_PageSize           16	
/* EEPROM Addresses defines */
#define EEPROM_Block0_ADDRESS 0xA0   /* E2 = 0 */
//#define EEPROM_Block1_ADDRESS 0xA2 /* E2 = 0 */
//#define EEPROM_Block2_ADDRESS 0xA4 /* E2 = 0 */
//#define EEPROM_Block3_ADDRESS 0xA6 /* E2 = 0 */
#define EEPROM_SIZE				 256			 /* 24xx02������ */

#define EEPROM_I2C 														I2C1
#define EEPROM_I2C_APBxClock                  RCC_APB1PeriphClockCmd
#define EEPROM_I2C_CLK                        RCC_APB1Periph_I2C1
#define EEPROM_I2C_GPIO_APBxClock             RCC_APB2PeriphClockCmd
#define EEPROM_I2C_GPIO_CLK                   RCC_APB2Periph_GPIOB     
#define EEPROM_I2C_SCL_PORT                   GPIOB   
#define EEPROM_I2C_SCL_PIN                    GPIO_Pin_6
#define EEPROM_I2C_SDA_PORT                   GPIOB 
#define EEPROM_I2C_SDA_PIN                    GPIO_Pin_7
					
uint8_t I2C_EEPROM_CheckOk(void);
uint8_t I2C_EEPROM_ByteW(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t I2C_EEPROM_ByteR(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t EEPROM_ACK_POLL(void);
void EEPROM_Erase(void);
uint8_t EEPROM_Test(void);

#endif /*__bsp_iic_eeprom_H*/
