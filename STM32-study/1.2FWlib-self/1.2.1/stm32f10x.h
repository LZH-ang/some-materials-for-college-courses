

/*本文件用于添加寄存器地址及结构体定义*/
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;


/*片上外设基地址  */
#define PERIPHERAL_START 			((unsigned int)0x40000000)
	
/* AHB总线基地址 */
#define PERIPHERAL_AHB   			(PERIPHERAL_START+0x20000)//如果0x2 0000报错

/*APB2 总线基地址 */
#define PERIPHERAL_APB2   		(PERIPHERAL_START+0x10000)

/*GPIOX外设基地址*/
#define PERIPHERAL_GPIOA   		(PERIPHERAL_APB2+0x0800)
#define PERIPHERAL_GPIOB   		(PERIPHERAL_APB2+0x0c00)
#define PERIPHERAL_GPIOC   		(PERIPHERAL_APB2+0x1000)
#define PERIPHERAL_GPIOD   		(PERIPHERAL_APB2+0x1400)
#define PERIPHERAL_GPIOE   		(PERIPHERAL_APB2+0x1800)
#define PERIPHERAL_GPIOF   		(PERIPHERAL_APB2+0x1c00)
#define PERIPHERAL_GPIOG   		(PERIPHERAL_APB2+0x2000)

/* GPIOX寄存器地址,强制转换成指针 */
#define GPIOA     ((GPIO_def*)PERIPHERAL_GPIOA)
#define GPIOB     ((GPIO_def*)PERIPHERAL_GPIOB)
#define GPIOC     ((GPIO_def*)PERIPHERAL_GPIOC)
#define GPIOD     ((GPIO_def*)PERIPHERAL_GPIOD)
#define GPIOE     ((GPIO_def*)PERIPHERAL_GPIOE)
#define GPIOF     ((GPIO_def*)PERIPHERAL_GPIOF)
#define GPIOG     ((GPIO_def*)PERIPHERAL_GPIOG)
	
/*RCC外设基地址*/
#define PERIPHERAL_RCC   			(PERIPHERAL_AHB+0x1000)

/*RCC寄存器地址,强制转换成指针*/
#define RCC 			((RCC_def*)PERIPHERAL_RCC)
	
/*寄存器结构体定义*/
typedef struct //英文路径才能正常提示结构体成员
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
