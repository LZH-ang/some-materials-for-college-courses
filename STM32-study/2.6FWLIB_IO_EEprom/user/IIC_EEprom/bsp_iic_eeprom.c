#include "bsp_iic_eeprom.h"
#include "bsp_iic_io.h"

static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);

//��ʱ��ɵ��쳣�������ͨ�����³�ʼ��retry?

uint8_t I2C_EEPROM_CheckOk(void)
{
	if (i2c_CheckDevice(EEPROM_Block0_ADDRESS) == 0)
	{
		return 1;
	}
	else
	{
		/* ʧ�ܺ��мǷ���I2C����ֹͣ�ź� */
		I2C_TIMEOUT_UserCallback(0);
		i2c_Stop();		
		return 0;
	}
}
/*
*********************************************************************************************************
*	�� �� ��: ee_ReadBytes
*	����˵��: �Ӵ���EEPROMָ����ַ����ʼ��ȡ��������
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 _usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 _pReadBuf : ��Ŷ��������ݵĻ�����ָ��
*	�� �� ֵ: 0 ��ʾʧ�ܣ�1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t I2C_EEPROM_ByteR(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize)
{
	uint16_t i;
	/* ���ô���EEPROM�漴��ȡָ�����У�������ȡ�����ֽ� */
	/* ��1��������I2C���������ź� */
	i2c_Start();
	/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_SendByte(EEPROM_Block0_ADDRESS | EEPROM_I2C_WR);	/* �˴���дָ�� */	 
	/* ��3�����ȴ�ACK */
	if (i2c_WaitAck() != 0)
	{
		I2C_TIMEOUT_UserCallback(1);
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}
	/* ��4���������ֽڵ�ַ��24C02ֻ��256�ֽڣ����1���ֽھ͹��ˣ������24C04���ϣ���ô�˴���Ҫ���������ַ */
	i2c_SendByte((uint8_t)_usAddress);
	/* ��5�����ȴ�ACK */
	if (i2c_WaitAck() != 0)
	{
		I2C_TIMEOUT_UserCallback(2);
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}
	/* ��6������������I2C���ߡ�ǰ��Ĵ����Ŀ����EEPROM���͵�ַ�����濪ʼ��ȡ���� */
	i2c_Start();
	/* ��7������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_SendByte(EEPROM_Block0_ADDRESS | EEPROM_I2C_RD);	/* �˴��Ƕ�ָ�� */
	/* ��8��������ACK */
	if (i2c_WaitAck() != 0)
	{
		I2C_TIMEOUT_UserCallback(3);
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}	
	/* ��9����ѭ����ȡ���� */
	for (i = 0; i < _usSize; i++)
	{
		_pReadBuf[i] = i2c_ReadByte();	/* ��1���ֽ� */	
		/* ÿ����1���ֽں���Ҫ����Ack�� ���һ���ֽڲ���ҪAck����Nack */
		if (i != _usSize - 1)
		{
			i2c_Ack();	/* �м��ֽڶ����CPU����ACK�ź�(����SDA = 0) */
		}
		else
		{
			i2c_NAck();	/* ���1���ֽڶ����CPU����NACK�ź�(����SDA = 1) */
		}
	}
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 1;	/* ִ�гɹ� */

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 0;
}
/*
*********************************************************************************************************
*	�� �� ��: ee_WriteBytes
*	����˵��: ����EEPROMָ����ַд���������ݣ�����ҳд�������д��Ч��
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 _usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 _pWriteBuf : ��Ŷ��������ݵĻ�����ָ��
*	�� �� ֵ: 0 ��ʾʧ�ܣ�1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t I2C_EEPROM_ByteW(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize)
{
	uint16_t i,m;
	uint16_t usAddr;
	/* 
		д����EEPROM�������������������ȡ�ܶ��ֽڣ�ÿ��д����ֻ����ͬһ��page��
		����24xx02��page size = 8
		�򵥵Ĵ�����Ϊ�����ֽ�д����ģʽ��ûд1���ֽڣ������͵�ַ
		Ϊ���������д��Ч��: ����������page wirte������
	*/
	usAddr = _usAddress;	
	for (i = 0; i < _usSize; i++)
	{
		/* �����͵�1���ֽڻ���ҳ���׵�ַʱ����Ҫ���·��������źź͵�ַ */
		if ((i == 0) || (usAddr & (EEPROM_PageSize - 1)) == 0)
		{
			/*���ڣ�������ֹͣ�źţ������ڲ�д������*/
			i2c_Stop();
			/* ͨ���������Ӧ��ķ�ʽ���ж��ڲ�д�����Ƿ����, һ��С�� 10ms 			
				CLKƵ��Ϊ200KHzʱ����ѯ����Ϊ30������
			*/
			for (m = 0; m < 100; m++)
			{				
				/* ��1��������I2C���������ź� */
				i2c_Start();	
				/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
				i2c_SendByte(EEPROM_Block0_ADDRESS | EEPROM_I2C_WR);	/* �˴���дָ�� */			
				/* ��3��������һ��ʱ�ӣ��ж������Ƿ���ȷӦ�� */
				if (i2c_WaitAck() == 0)
				{
					break;
				}
			}
			if (m  == 100)
			{
				I2C_TIMEOUT_UserCallback(4);
				goto cmd_fail;	/* EEPROM����д��ʱ */
			}	
			/* ��4���������ֽڵ�ַ��24C02ֻ��256�ֽڣ����1���ֽھ͹��ˣ������24C04���ϣ���ô�˴���Ҫ���������ַ */
			i2c_SendByte((uint8_t)usAddr);			
			/* ��5�����ȴ�ACK */
			if (i2c_WaitAck() != 0)
			{
				I2C_TIMEOUT_UserCallback(5);
				goto cmd_fail;	/* EEPROM������Ӧ�� */
			}
		}	
		/* ��6������ʼд������ */
		i2c_SendByte(_pWriteBuf[i]);	
		/* ��7��������ACK */
		if (i2c_WaitAck() != 0)
		{
			I2C_TIMEOUT_UserCallback(6);
			goto cmd_fail;	/* EEPROM������Ӧ�� */
		}
		usAddr++;	/* ��ַ��1 */		
	}
	/* ����ִ�гɹ�������I2C����ֹͣ�ź� */
	i2c_Stop();
	return 1;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 0;
}

uint8_t EEPROM_ACK_POLL(void)
{
	uint16_t i=100;
	do
	{
		/*START*/
		i2c_Start();
		/*ADDRESS*/
		i2c_SendByte(EEPROM_Block0_ADDRESS | EEPROM_I2C_RD);
		i--;if(i==0)I2C_TIMEOUT_UserCallback(7);
	}	
	while(i2c_WaitAck() != 0);
	/*STOP*/
	i2c_Stop();
	return 1;
}

void EEPROM_Erase(void)
{
	uint16_t i;
	uint8_t buf[EEPROM_SIZE];
	
	if(I2C_EEPROM_CheckOk() == 0)
	{
		/* û�м�⵽EEPROM */
		printf("û�м�⵽����EEPROM!\r\n");			
		return;
	}
	/* ��仺���� */
	for (i = 0; i < EEPROM_SIZE; i++)
	{
		buf[i] = 0xFF;
	}
	/* дEEPROM, ��ʼ��ַ = 0�����ݳ���Ϊ 256 */
	if (I2C_EEPROM_ByteW(buf, 0, EEPROM_SIZE) == 0)
	{
		printf("����eeprom����\r\n");
		return;
	}
	else
	{
		printf("����eeprom�ɹ���\r\n");
	}
}

/*--------------------------------------------------------------------------------------------------*/
//static void EEPROM_Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
//{
//	for(; nCount != 0; nCount--);
//}

/*
 * eeprom AT24C02 ��д����
 * ��������1���쳣����0
 */
uint8_t EEPROM_Test(void) 
{
  uint16_t i;
	uint8_t write_buf[EEPROM_SIZE];
  uint8_t read_buf[EEPROM_SIZE];
  
/*-----------------------------------------------------------------------------------*/  
  if(I2C_EEPROM_CheckOk() == 0)
	{
		/* û�м�⵽EEPROM */
		printf("û�м�⵽����EEPROM!\r\n");			
		return 0;
	}
/*------------------------------------------------------------------------------------*/  
  /* �����Ի����� */
	for(i = 0; i < EEPROM_SIZE; i++)
	{		
		write_buf[i] = i;
	}
/*------------------------------------------------------------------------------------*/  
  if (I2C_EEPROM_ByteW(write_buf, 0, EEPROM_SIZE) == 0)
	{
		printf("дeeprom����\r\n");
		return 0;
	}
	else
	{		
		printf("дeeprom�ɹ���\r\n");
	}
  /*д��֮����ʱ����һֱѯ����ȥ������Ȼ�����*/
	EEPROM_ACK_POLL();
/*-----------------------------------------------------------------------------------*/
  if (I2C_EEPROM_ByteR(read_buf, 0, EEPROM_SIZE) == 0)
	{
		printf("��eeprom����\r\n");
		return 0;
	}
	else
	{		
		printf("��eeprom�ɹ����������£�\r\n");
	}
/*-----------------------------------------------------------------------------------*/  
  for (i = 0; i < EEPROM_SIZE; i++)
	{
		if(read_buf[i] != write_buf[i])
		{
			printf("0x%02X ", read_buf[i]);
			printf("����:EEPROM������д������ݲ�һ��");
			return 0;
		}
    printf(" %02X", read_buf[i]);
		
		if ((i & 15) == 15)
		{
			printf("\r\n");	
		}		
	}
  printf("eeprom��д���Գɹ�\r\n");
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
