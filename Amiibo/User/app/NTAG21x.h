#ifndef NTAG21x_H_
#define NTAG21x_H_

#include <stdint.h>
#include "PN532.h"
#define NTAG_GET_VERSION         (0x60)
#define NTAG_READ                (0x30)
#define NTAG_FAST_READ           (0x3a)
#define NTAG_WRITE               (0xa2)
#define NTAG_COMPATIBILITY_WRITE (0xA0)
#define NTAG_CNT                 (0x39)
#define NTAG_CNT_ADDR            (0x02)
#define NTAG_PWD_AUTH            (0x1b)
#define NTAG_READ_SIG            (0x3c)
#define NTAG_READ_SIG_ADDR       (0x00)


typedef struct {
    PN532_ctx_t *PN532;
    uint8_t UID_Start;
    uint8_t UID_End;
    uint8_t CC_Address;
    uint8_t User_memory_Address_Start; 
    uint8_t User_memory_Address_End; 
    uint8_t Dynamic_lock_bytes_Address;
    uint8_t Configuration_pages_Start;
    uint8_t Configuration_pages_End;
    uint8_t Page_per_bytes;
}NTAG21x_t;

uint8_t NTAG21x_write_data(NTAG21x_t *NTAG21x,uint8_t start_addr,uint8_t end_addr,uint8_t need_write_data[]);
uint8_t* NTAG21x_Read(NTAG21x_t *NTAG21x,uint8_t page_address);
uint8_t* NTAG21x_CaculatePwd(NTAG21x_t *NTAG21x);
uint8_t NTAG21x_Pwd_Auth(NTAG21x_t *NTAG21x);
uint8_t NTAG21x_Select_Card(NTAG21x_t *NTAG21x);
uint8_t NTAG21x_Write_lock(NTAG21x_t *NTAG21x);
uint8_t NTAG21x_Read_Back_Comparison(NTAG21x_t* pn532,uint8_t* need_compariosn_data);

#endif
