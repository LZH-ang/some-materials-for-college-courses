#include "bsp_iic_eeprom.h"

static __IO uint32_t  I2CTimeout = I2CT_FLAG_TIMEOUT;
static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);

//��ʱ��ɵ��쳣�������ͨ�����³�ʼ��retry?

void I2C_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;
	
	/*I2C_GPIO_Config*/
	/* ʹ���� I2C �йص�ʱ�� */
	EEPROM_I2C_APBxClock(EEPROM_I2C_CLK, ENABLE);
	EEPROM_I2C_GPIO_APBxClock(EEPROM_I2C_GPIO_CLK, ENABLE);
	  
  /* I2C_SCL��I2C_SDA*/
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN;
  GPIO_Init(EEPROM_I2C_SCL_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN;
  GPIO_Init(EEPROM_I2C_SDA_PORT, &GPIO_InitStructure);	

	/*I2C_Mode_Config*/
  /* I2C ���� */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	
	/* �ߵ�ƽ�����ȶ����͵�ƽ���ݱ仯 SCL ʱ���ߵ�ռ�ձ� */
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	
  I2C_InitStructure.I2C_OwnAddress1 =I2Cx_OWN_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	 
	/* I2C��Ѱַģʽ */
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	/* ͨ������ */
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
	/* I2C ��ʼ�� */
  I2C_Init(EEPROM_I2C, &I2C_InitStructure);
  
	/* ʹ�� I2C */
  I2C_Cmd(EEPROM_I2C, ENABLE);   
}

uint32_t I2C_EEPROM_ByteR(uint8_t addr)
{
	uint8_t data=0;
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_BUSY))
  {
		//EEPROM_INFO("\nNB\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
  }
	/*START*/
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)//EV5
	{
		//EEPROM_INFO("\nROK0\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
	}
	/*ADDRESS*/
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)//EV6
	{
		//EEPROM_INFO("\nROK1\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
	}
	/*SENDDATA*/
	I2C_SendData(EEPROM_I2C, addr);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR)//EV8
	{
		//EEPROM_INFO("\nROK2\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
	}
	/*START*/
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)//EV5
	{
		//EEPROM_INFO("\nROK3\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(4);
	}
	/*ADDRESS*/
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Block0_ADDRESS, I2C_Direction_Receiver);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR)//EV6
	{
		//EEPROM_INFO("\nROK4\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(5);
	}	
	/*RECEIVERDATA*/
	I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR)//EV7
	{
		//EEPROM_INFO("\nROK5\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(6);
	}	
	data = I2C_ReceiveData(EEPROM_I2C);
	/*STOP*/
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
	return data;
}

uint32_t I2C_EEPROM_ByteW(uint8_t Waddr, uint8_t* pData)
{
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_BUSY))
  {
		//EEPROM_INFO("\nNB\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(7);
  }
	/*START*/
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)//EV5
	{
		//EEPROM_INFO("\nWOK0\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(8);
	}
	/*ADDRESS*/
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)//EV6
	{
		//EEPROM_INFO("\nWOK1\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(9);
	}
	/*SENDDATA*/
	I2C_SendData(EEPROM_I2C, Waddr);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR)//EV8
	{
		//EEPROM_INFO("\nWOK2\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(10);
	}
	/*SENDDATA*/
	I2C_SendData(EEPROM_I2C, *pData);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)//EV8_2
	{
		//EEPROM_INFO("\nWOK3\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(11);
	}
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	/*STOP*/
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	return 1;
}

uint32_t I2C_EEPROM_PageW(uint8_t Waddr, uint8_t* pData, uint8_t NumByte)
{
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_BUSY))
  {
		//EEPROM_INFO("\nNB\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(12);
  }
	/*START*/
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)//EV5
	{
		//EEPROM_INFO("\nWOK0\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(13);
	}
	/*ADDRESS*/
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)//EV6
	{
		//EEPROM_INFO("\nWOK1\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(14);
	}
	/*SENDDATA*/
	I2C_SendData(EEPROM_I2C, Waddr);
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR)//EV8
	{
		//EEPROM_INFO("\nWOK2\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(15);
	}
	/*SENDDATA*/
  /* While there is data to be written */
  while(NumByte--)  
  {
    /* Send the current byte */
    I2C_SendData(EEPROM_I2C, *pData); 
    /* Point to the next byte to be written */
    pData++; 
    I2CTimeout = I2CT_FLAG_TIMEOUT;
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(16);
    } 
  }
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	/*STOP*/
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	return 1;
}

uint32_t I2C_EEPROM_BufferR(uint8_t Raddr, uint8_t* pBuffer, uint16_t NumByte)
{  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  //*((u8 *)0x4001080c) |=0x80; 
	while(I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_BUSY))
	{
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(17);
	}
  /* Send START condition */
  I2C_GenerateSTART(EEPROM_I2C, ENABLE);
  //*((u8 *)0x4001080c) &=~0x80;
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(18);
  }
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(19);
  } 
  /* Clear EV6 by setting again the PE bit */
//  I2C_Cmd(EEPROM_I2C, ENABLE);
  /* Send the EEPROM's internal address to write to */
  I2C_SendData(EEPROM_I2C, Raddr);  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(20);
  }  
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(EEPROM_I2C, ENABLE); 
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(21);
  }   
  /* Send EEPROM address for read */
  I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Block0_ADDRESS, I2C_Direction_Receiver); 
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(22);
  } 
  /* While there is data to be read */
  while(NumByte)  
  {
    if(NumByte == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);    
      /* Send STOP Condition */
      I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
    }
    /* Test on EV7 and clear it */    
    I2CTimeout = I2CT_FLAG_TIMEOUT; 
		while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)  
		{
			if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(23);
		}     
		/* Read a byte from the EEPROM */
		*pBuffer = I2C_ReceiveData(EEPROM_I2C);
		/* Point to the next location where the byte read will be saved */
		pBuffer++; 		
		/* Decrement the read bytes counter */
		NumByte--;           
  }
  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
  return 1;
}

void I2C_EEPROM_BufferW(uint8_t Waddr, uint8_t* pBuffer, uint16_t NumByte)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

  Addr = Waddr % I2C_PageSize;
  count = I2C_PageSize - Addr;
  NumOfPage =  NumByte / I2C_PageSize;
  NumOfSingle = NumByte % I2C_PageSize;
 
  /* If WriteAddr is I2C_PageSize aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage == 0) 
    {
			I2C_EEPROM_PageW(Waddr, pBuffer, NumOfSingle);
      EEPROM_ACK_POLL();
    }
    /* If NumByteToWrite > I2C_PageSize */
    else  
    {
      while(NumOfPage--)
      {
				I2C_EEPROM_PageW(Waddr, pBuffer, I2C_PageSize);
				EEPROM_ACK_POLL();
        Waddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;
      }

      if(NumOfSingle!=0)
      {
				I2C_EEPROM_PageW(Waddr, pBuffer, NumOfSingle);
        EEPROM_ACK_POLL();
      }
    }
  }
  /* If WriteAddr is not I2C_PageSize aligned  */
  else 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage== 0) 
    {
			I2C_EEPROM_PageW(Waddr, pBuffer, NumOfSingle);
      EEPROM_ACK_POLL();
    }
    /* If NumByteToWrite > I2C_PageSize */
    else
    {
      NumByte -= count;
      NumOfPage =  NumByte / I2C_PageSize;
      NumOfSingle = NumByte % I2C_PageSize;	
      
      if(count != 0)//д��û��aligned������
      {  
				I2C_EEPROM_PageW(Waddr, pBuffer, count);
        EEPROM_ACK_POLL();
        Waddr += count;
        pBuffer += count;
      } 
      
      while(NumOfPage--)
      {
				I2C_EEPROM_PageW(Waddr, pBuffer, I2C_PageSize);
        EEPROM_ACK_POLL();
        Waddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;  
      }
      if(NumOfSingle != 0)
      {
				I2C_EEPROM_PageW(Waddr, pBuffer, NumOfSingle);
        EEPROM_ACK_POLL();
      }
    }
  }  
}

uint32_t EEPROM_ACK_POLL(void)
{
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while(I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_BUSY))
  {
		//EEPROM_INFO("\nNB\n\r");
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
  }
	do
	{
		/*START*/
		I2C_GenerateSTART(EEPROM_I2C, ENABLE);
		I2CTimeout = I2CT_FLAG_TIMEOUT;
		while(I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_SB) == RESET)//EV5
		{
			//EEPROM_INFO("\nROK0\n\r");
			if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
		}
		/*ADDRESS*/
		I2C_Send7bitAddress(EEPROM_I2C, EEPROM_Block0_ADDRESS, I2C_Direction_Transmitter);
	}	
	while(I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_ADDR) == RESET);//EV6
	/*STOP*/
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	return 1;
	
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode��������룬����������λ���ĸ����ڳ���.
  * @retval ����0����ʾIIC��ȡʧ��.
  */
static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  EEPROM_ERROR("I2C�ȴ���ʱ!errorCode = %d",errorCode);
  return 0;
}

/**
  * @brief  I2C(AT24C02)��д����
  * @param  ��
  * @retval ��������1���쳣����0
  */
uint8_t I2C_Test(void)
{
	uint16_t i;
	uint8_t I2c_Buf_Write[256];
	uint8_t I2c_Buf_Read[256];

	printf("д�������\n\r");  
	for ( i=0; i<256; i++ ) //��仺��
  {   
    I2c_Buf_Write[i] = i;

    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)    
        printf("\n\r");    
   }
  //��I2c_Buf_Write��˳�����������д��EERPOM�� 
	I2C_EEPROM_BufferW(EEP_Firstpage, I2c_Buf_Write, 256);
  EEPROM_INFO("\n\rд�ɹ�\n\r");
  EEPROM_INFO("\n\r����������\n\r");
  //��EEPROM��������˳�򱣳ֵ�I2c_Buf_Read��
	I2C_EEPROM_BufferR(EEP_Firstpage, I2c_Buf_Read, 256); 
  //��I2c_Buf_Read�е�����ͨ�����ڴ�ӡ
	for (i=0; i<256; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			EEPROM_ERROR("0x%02X ", I2c_Buf_Read[i]);
			EEPROM_ERROR("����:I2C EEPROMд������������ݲ�һ��\n\r");
			return 0;
		}
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)printf("\n\r");  
	}
  EEPROM_INFO("I2C(AT24C02)��д���Գɹ�\n\r");
  return 1;
}