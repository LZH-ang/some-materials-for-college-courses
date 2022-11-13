

/*���ļ�������ӼĴ�����ַ���ṹ�嶨��*/
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;


/*Ƭ���������ַ  */
#define PERIPHERAL_START 			((unsigned int)0x40000000)
	
/* AHB���߻���ַ */
#define PERIPHERAL_AHB   			(PERIPHERAL_START+0x20000)//���0x2 0000����

/*APB2 ���߻���ַ */
#define PERIPHERAL_APB2   		(PERIPHERAL_START+0x10000)

/*GPIOX�������ַ*/
#define PERIPHERAL_GPIOA   		(PERIPHERAL_APB2+0x0800)
#define PERIPHERAL_GPIOB   		(PERIPHERAL_APB2+0x0c00)
#define PERIPHERAL_GPIOC   		(PERIPHERAL_APB2+0x1000)
#define PERIPHERAL_GPIOD   		(PERIPHERAL_APB2+0x1400)
#define PERIPHERAL_GPIOE   		(PERIPHERAL_APB2+0x1800)
#define PERIPHERAL_GPIOF   		(PERIPHERAL_APB2+0x1c00)
#define PERIPHERAL_GPIOG   		(PERIPHERAL_APB2+0x2000)

/* GPIOX�Ĵ�����ַ,ǿ��ת����ָ�� */
#define GPIOA     ((GPIO_def*)PERIPHERAL_GPIOA)
#define GPIOB     ((GPIO_def*)PERIPHERAL_GPIOB)
#define GPIOC     ((GPIO_def*)PERIPHERAL_GPIOC)
#define GPIOD     ((GPIO_def*)PERIPHERAL_GPIOD)
#define GPIOE     ((GPIO_def*)PERIPHERAL_GPIOE)
#define GPIOF     ((GPIO_def*)PERIPHERAL_GPIOF)
#define GPIOG     ((GPIO_def*)PERIPHERAL_GPIOG)
	
/*RCC�������ַ*/
#define PERIPHERAL_RCC   			(PERIPHERAL_AHB+0x1000)

/*RCC�Ĵ�����ַ,ǿ��ת����ָ��*/
#define RCC 			((RCC_def*)PERIPHERAL_RCC)
	
/*�Ĵ����ṹ�嶨��*/
typedef struct //Ӣ��·������������ʾ�ṹ���Ա
{
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_def;

typedef struct
{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
}RCC_def;
