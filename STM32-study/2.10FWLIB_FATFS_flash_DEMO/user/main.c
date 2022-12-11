#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_spi_flash.h"
#include "ff.h"
#include "diskio.h"
#include "string.h"

#define CHIPERASE	0
static BYTE flashwork[FF_MAX_SS] = {0};
static FRESULT res_flash;
static FATFS fs_flash;
static FIL fil_flash;
static FILINFO fno_flash;
static UINT frw_num;
static BYTE readbuffer[FF_MAX_SS] = {0};
/*-------------------------------------------------------*/
static FRESULT DEMO_TEST(void);
static FRESULT file_check(const TCHAR* path, FILINFO* fno);
FRESULT scan_files(char* path);

int main(void)
{
    LED_Init();
    LED_BLUE;
    USART_Config();
    printf("\r\n======================================================================");
    printf("\r\n=                           Hello STM32!                             =");
    printf("\r\n=                                                                    =");
    printf("\r\n=                     STM32F1_Fatfs Program Demo                     =");
    printf("\r\n=                                                                    =");
    printf("\r\n=                                           By Kelee                 =");
    printf("\r\n======================================================================");
#if CHIPERASE
    printf("\n>ERASE FATFS...\n");
    SPI_FLASH_Init();
    SPI_FLASH_ChipErase();
#endif
    res_flash = f_mount(&fs_flash, "3:", 1);
#if DEBUG
    printf("\n f_mount %d\n", res_flash);
#endif
    if(res_flash == FR_NO_FILESYSTEM)
    {
        printf("\n>FLASH_NO_FILESYSTEM START TO MKFS\n>WAIT...\n");
        res_flash = f_mkfs("3:", FM_FAT, 0, flashwork, sizeof flashwork);
#if DEBUG
        printf("\n f_mkfs %d\n", res_flash);
#endif
        if(res_flash == FR_OK)
        {
            printf("\n>MKFS OVER\n");
            res_flash = f_unmount("3:");
            res_flash = f_mount(&fs_flash, "3:", 1);
        }
        else
        {
            printf("\n>MKFS FAIL\n");
        }
    }
    else if(res_flash != FR_OK)
    {
        printf("\n>MOUNT FAIL\n");
    }
    else
    {	
		printf("\n>MOUNT OVER\n");
    }
	res_flash = DEMO_TEST();
#if DEBUG
    printf("\n DEMO_TEST %d\n", res_flash);
#endif
	res_flash = f_unmount("3:");
	if(res_flash == FR_OK)
    {
        printf("\n>TEST OVER\n");
    }
    while(1)
    {

    }
}


/*
SCAN_FILE,FILE_CHECK;
DEMO_TEST:
		SCAN_FILE
		getfree->open->lseek->printf->close
		SCAN_FILE
		mkdir&rename
		SCAN_FILE
		FILE_CHECK
*/

/* FatFs����ܲ��� */
static FRESULT DEMO_TEST(void)
{
	DIR dir;
	FATFS *pfs;
	DWORD fre_clust, fre_sect, tot_sect;
	char fpath[128];	/* ���浱ǰɨ��·�� */

    printf("\r\n======================================================================");
    printf("\r\n=                            DEMO TEST                               =");
    printf("\r\n======================================================================");
	printf("\n");
	/* Scan files */
	strcpy(fpath,"3:");
	res_flash = scan_files(fpath);
#if DEBUG
    printf("\n scan_files %d\n", res_flash);
	if(res_flash)return res_flash;
#endif
	printf("\r\n=                           DEVICE INFO                              =\r\n");
	/* Get volume information and free clusters of drive 3 */
    res_flash = f_getfree("3:", &fre_clust, &pfs);	
#if DEBUG
    printf("\n f_getfree %d\n", res_flash);
	if(res_flash)return res_flash;
#endif  
    /* Get total sectors and free sectors */
    tot_sect = (pfs->n_fatent - 2) * pfs->csize;
    fre_sect = fre_clust * pfs->csize;
    /* Print the free space (assuming 4KiB bytes/sector) */
    printf("\n>%10lu KiB total drive space.\n>%10lu KiB available.\n", tot_sect*4, fre_sect*4);

	printf("\r\n=                        SEEK&FORMATW TEST                           =\r\n");
	res_flash = f_open(&fil_flash, "3:FatFsR&WTEST.txt", FA_OPEN_ALWAYS|FA_WRITE|FA_READ );
#if DEBUG
    printf("\n f_open %d\n", res_flash);
	if(res_flash)return res_flash;
#endif 	
	if(res_flash == FR_OK)
	{
		/*  �ļ���λ */
		res_flash = f_lseek(&fil_flash,f_size(&fil_flash));
#if DEBUG
		printf("\n f_lseek %d\n", res_flash);
		printf("\n f_size %ld\n", f_size(&fil_flash));
		if(res_flash)return res_flash;
#endif
		if (res_flash == FR_OK)
		{
			/* ��ʽ��д�룬������ʽ����printf���� */
			f_printf(&fil_flash,"��ԭ���ļ������һ������:\n");
			f_printf(&fil_flash,"�豸�ܿռ䣺%8lu KiB��\n�豸���ÿռ䣺%8lu KiB��\n", tot_sect *4, fre_sect *4);
			/*  �ļ���λ���ļ���ʼλ�� */
			res_flash = f_lseek(&fil_flash,0);
#if DEBUG
			printf("\n f_lseek %d\n", res_flash);
			if(res_flash)return res_flash;
#endif
			/* ��ȡ�ļ��������ݵ������� */
			res_flash = f_read(&fil_flash,readbuffer,f_size(&fil_flash),&frw_num);
#if DEBUG
			printf("\n f_read %d\n", res_flash);
			if(res_flash)return res_flash;
#endif
			if(res_flash == FR_OK)
			{
				printf("\n>FILECONTENT��\n%s\n",readbuffer);
			}
		}
		res_flash = f_close(&fil_flash);
#if DEBUG
		printf("\n f_close %d\n", res_flash);
		if(res_flash)return res_flash;
#endif 	
		/* Scan files */
		strcpy(fpath,"3:");
		res_flash = scan_files(fpath);
#if DEBUG
		printf("\n scan_files %d\n", res_flash);
		if(res_flash)return res_flash;
#endif
		printf("\r\n=                        MKDIR&RENAME TEST                           =\r\n");
		/* ���Դ�Ŀ¼ */
		res_flash = f_opendir(&dir,"3:TestMKDir");
#if DEBUG
		printf("\n f_opendir %d\n", res_flash);
		if(res_flash)return res_flash;
#endif 	
		if(res_flash != FR_OK)
		{
			/* ��Ŀ¼ʧ�ܣ��ʹ���Ŀ¼ */
			res_flash = f_mkdir("3:TestMKDir");
#if DEBUG
			printf("\n f_mkdir %d\n", res_flash);
			if(res_flash)return res_flash;
#endif 
		}
		else
		{
			/* ɾ���ļ� */
			res_flash = f_unlink("3:TestMKDir/testmkdir.txt");
#if DEBUG
			printf("\n f_unlink %d\n", res_flash);
			if(res_flash)return res_flash;
#endif
			/* ���Ŀ¼�Ѿ����ڣ��ر��� */
			res_flash = f_closedir(&dir);
#if DEBUG
			printf("\n f_closedir %d\n", res_flash);
			if(res_flash)return res_flash;
#endif
			/* Scan files */
			strcpy(fpath,"3:");
			res_flash = scan_files(fpath);
#if DEBUG
			printf("\n scan_files %d\n", res_flash);
			if(res_flash)return res_flash;
#endif
		}
		if(res_flash == FR_OK)
		{
			/* ���������ƶ��ļ� */
			res_flash = f_rename("3:FatFsR&WTEST.txt","3:TestMKDir/testmkdir.txt"); 
#if DEBUG
			printf("\n f_rename %d\n", res_flash);
			if(res_flash)return res_flash;
#endif			
		} 
	}
	else
	{
		printf("\n>!! OPEN FILE FAIL��%d\n", res_flash);
		return res_flash;
	}
	printf("\n");
	/* Scan files */
	strcpy(fpath,"3:");
	res_flash = scan_files(fpath);
#if DEBUG
	printf("\n scan_files %d\n", res_flash);
	if(res_flash)return res_flash;
#endif
	/* Check files */
	res_flash = file_check("3:TestMKDir/testmkdir.txt", &fno_flash);
#if DEBUG
	printf("\n file_check %d\n", res_flash);
#endif
	return res_flash;
}

static FRESULT file_check(const TCHAR* path, FILINFO* fno)
{
    res_flash=f_stat(path,fno);
    switch(res_flash)
    {
    case FR_OK:
        printf("\n>%s STAT: \n",path);
        printf("\n>Size: %lu\n", fno->fsize);
        printf("\n>Timestamp: %u/%02u/%02u, %02u:%02u\n",
               (fno->fdate >> 9) + 1980, fno->fdate >> 5 & 15, fno->fdate & 31,
               fno->ftime >> 11, fno->ftime >> 5 & 63);
        printf("\n>Attributes: %c%c%c%c%c\n",
               (fno->fattrib & AM_DIR) ? 'D' : '-',		// ��һ��Ŀ¼
               (fno->fattrib & AM_RDO) ? 'R' : '-',		// ֻ���ļ�
               (fno->fattrib & AM_HID) ? 'H' : '-',		// �����ļ�
               (fno->fattrib & AM_SYS) ? 'S' : '-',		// ϵͳ�ļ�
               (fno->fattrib & AM_ARC) ? 'A' : '-');	// �����ļ�
        break;
    case FR_NO_FILE:
        printf("\n>IT IS NOT EXIST.\n");
        break;
    default:
        printf("\n>AN ERROR OCCOURED. (%d)\n", res_flash);
    }
    return res_flash;
}

/**
  * @brief  scan_files �ݹ�ɨ��FatFs�ڵ��ļ�
  * @param  path:��ʼɨ��·��
  * @retval result:�ļ�ϵͳ�ķ���ֵ
  */
FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
	char *fn;		// �ļ���	
    static FILINFO fno;

    res = f_opendir(&dir, path);		/* Open the directory */
    if (res == FR_OK) 
	{
        for(;;)
		{
            res = f_readdir(&dir, &fno);	/* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;	/* Break on error or end of dir */
#if FF_USE_LFN 
			fn = *fno.altname ? fno.altname : fno.fname; 
#else 
			fn = fno.fname; 
#endif 
//			if (*fn == '.') continue;		//���ʾ��ǰĿ¼������
            if (fno.fattrib & AM_DIR)		/* It is a directory */
			{                    
                i = strlen(path);
                sprintf(&path[i], "/%s", fn);
                res = scan_files(path);		/* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            } 
			else		/* It is a file. */
			{                                       
                printf("%s/%s\n", path, fn);	/* ������������ȡ�ض���ʽ���ļ�·�� */
            }
        }
        f_closedir(&dir);
    }
    return res;
/*
int main (void)
{
    FATFS fs;
    FRESULT res;
    char buff[256];


    res = f_mount(&fs, "", 1);
    if (res == FR_OK) {
        strcpy(buff, "/");
        res = scan_files(buff);
    }

    return res;
}
*/
}
