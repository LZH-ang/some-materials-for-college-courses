

/*本文件用于添加寄存器地址及结构体定义*/

/*片上外设基地址  */
#define PERIPHERAL_START 			((unsigned int)0x40000000)
	
/* AHB总线基地址 */
#define PERIPHERAL_AHB   			(PERIPHERAL_START+0x20000)//如果0x2 0000报错

/*APB2 总线基地址 */
#define PERIPHERAL_APB2   		(PERIPHERAL_START+0x10000)

/*GPIOB外设基地址*/
#define PERIPHERAL_GPIOA   		(PERIPHERAL_APB2+0x0800)
#define PERIPHERAL_GPIOB   		(PERIPHERAL_APB2+0x0c00)
#define PERIPHERAL_GPIOC   		(PERIPHERAL_APB2+0x1000)
#define PERIPHERAL_GPIOD   		(PERIPHERAL_APB2+0x1400)
#define PERIPHERAL_GPIOE   		(PERIPHERAL_APB2+0x1800)
#define PERIPHERAL_GPIOF   		(PERIPHERAL_APB2+0x1c00)
#define PERIPHERAL_GPIOG   		(PERIPHERAL_APB2+0x2000)

/* GPIOA寄存器地址,强制转换成指针 */
#define GPIOA_CRL   					*(unsigned int*)(PERIPHERAL_GPIOA+0x00)
#define GPIOA_CRH   					*(unsigned int*)(PERIPHERAL_GPIOA+0x04)
#define GPIOA_IDR   					*(unsigned int*)(PERIPHERAL_GPIOA+0x08)
#define GPIOA_ODR   					*(unsigned int*)(PERIPHERAL_GPIOA+0x0c)
#define GPIOA_BSRR   					*(unsigned int*)(PERIPHERAL_GPIOA+0x10)
#define GPIOA_BRR   					*(unsigned int*)(PERIPHERAL_GPIOA+0x14)
#define GPIOA_LCKR   					*(unsigned int*)(PERIPHERAL_GPIOA+0x18)
	
/* GPIOB寄存器地址,强制转换成指针 */
#define GPIOB_CRL   					*(unsigned int*)(PERIPHERAL_GPIOB+0x00)
#define GPIOB_CRH   					*(unsigned int*)(PERIPHERAL_GPIOB+0x04)
#define GPIOB_IDR   					*(unsigned int*)(PERIPHERAL_GPIOB+0x08)
#define GPIOB_ODR   					*(unsigned int*)(PERIPHERAL_GPIOB+0x0c)
#define GPIOB_BSRR   					*(unsigned int*)(PERIPHERAL_GPIOB+0x10)
#define GPIOB_BRR   					*(unsigned int*)(PERIPHERAL_GPIOB+0x14)
#define GPIOB_LCKR   					*(unsigned int*)(PERIPHERAL_GPIOB+0x18)

/* GPIOC寄存器地址,强制转换成指针 */
#define GPIOC_CRL   					*(unsigned int*)(PERIPHERAL_GPIOC+0x00)
#define GPIOC_CRH   					*(unsigned int*)(PERIPHERAL_GPIOC+0x04)
#define GPIOC_IDR   					*(unsigned int*)(PERIPHERAL_GPIOC+0x08)
#define GPIOC_ODR   					*(unsigned int*)(PERIPHERAL_GPIOC+0x0c)
#define GPIOC_BSRR   					*(unsigned int*)(PERIPHERAL_GPIOC+0x10)
#define GPIOC_BRR   					*(unsigned int*)(PERIPHERAL_GPIOC+0x14)
#define GPIOC_LCKR   					*(unsigned int*)(PERIPHERAL_GPIOC+0x18)
	
/* GPIOD寄存器地址,强制转换成指针 */
#define GPIOD_CRL   					*(unsigned int*)(PERIPHERAL_GPIOD+0x00)
#define GPIOD_CRH   					*(unsigned int*)(PERIPHERAL_GPIOD+0x04)
#define GPIOD_IDR   					*(unsigned int*)(PERIPHERAL_GPIOD+0x08)
#define GPIOD_ODR   					*(unsigned int*)(PERIPHERAL_GPIOD+0x0c)
#define GPIOD_BSRR   					*(unsigned int*)(PERIPHERAL_GPIOD+0x10)
#define GPIOD_BRR   					*(unsigned int*)(PERIPHERAL_GPIOD+0x14)
#define GPIOD_LCKR   					*(unsigned int*)(PERIPHERAL_GPIOD+0x18)
	
/* GPIOE寄存器地址,强制转换成指针 */
#define GPIOE_CRL   					*(unsigned int*)(PERIPHERAL_GPIOE+0x00)
#define GPIOE_CRH   					*(unsigned int*)(PERIPHERAL_GPIOE+0x04)
#define GPIOE_IDR   					*(unsigned int*)(PERIPHERAL_GPIOE+0x08)
#define GPIOE_ODR   					*(unsigned int*)(PERIPHERAL_GPIOE+0x0c)
#define GPIOE_BSRR   					*(unsigned int*)(PERIPHERAL_GPIOE+0x10)
#define GPIOE_BRR   					*(unsigned int*)(PERIPHERAL_GPIOE+0x14)
#define GPIOE_LCKR   					*(unsigned int*)(PERIPHERAL_GPIOE+0x18)

/* GPIOF寄存器地址,强制转换成指针 */
#define GPIOF_CRL   					*(unsigned int*)(PERIPHERAL_GPIOF+0x00)
#define GPIOF_CRH   					*(unsigned int*)(PERIPHERAL_GPIOF+0x04)
#define GPIOF_IDR   					*(unsigned int*)(PERIPHERAL_GPIOF+0x08)
#define GPIOF_ODR   					*(unsigned int*)(PERIPHERAL_GPIOF+0x0c)
#define GPIOF_BSRR   					*(unsigned int*)(PERIPHERAL_GPIOF+0x10)
#define GPIOF_BRR   					*(unsigned int*)(PERIPHERAL_GPIOF+0x14)
#define GPIOF_LCKR   					*(unsigned int*)(PERIPHERAL_GPIOF+0x18)
	
/* GPIOG寄存器地址,强制转换成指针 */
#define GPIOG_CRL   					*(unsigned int*)(PERIPHERAL_GPIOG+0x00)
#define GPIOG_CRH   					*(unsigned int*)(PERIPHERAL_GPIOG+0x04)
#define GPIOG_IDR   					*(unsigned int*)(PERIPHERAL_GPIOG+0x08)
#define GPIOG_ODR   					*(unsigned int*)(PERIPHERAL_GPIOG+0x0c)
#define GPIOG_BSRR   					*(unsigned int*)(PERIPHERAL_GPIOG+0x10)
#define GPIOG_BRR   					*(unsigned int*)(PERIPHERAL_GPIOG+0x14)
#define GPIOG_LCKR   					*(unsigned int*)(PERIPHERAL_GPIOG+0x18)
	
/*RCC外设基地址*/
#define PERIPHERAL_RCC   			(PERIPHERAL_AHB+0x1000)

/*RCC的APB2时钟使能寄存器地址,强制转换成指针*/
#define RCC_APB2ENR  					*(unsigned int*)(PERIPHERAL_RCC+0x18)
	
