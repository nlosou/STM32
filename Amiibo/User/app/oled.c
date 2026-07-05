#include "oled.h"
#include "oled_font.h"
#include <string.h>


uint8_t oled_buffer[1024];

void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t color)
{
    if(x > 127 || y > 63) return; // 越界保护

    uint16_t byte_idx = (y / 8) * 128 + x;
    uint8_t bit_mask = 1 << (y % 8);

    if (color)
    {
        oled_buffer[byte_idx] |= bit_mask;  // 点亮
    } 
    else
    {
        oled_buffer[byte_idx] &= ~bit_mask; // 熄灭
    }
}



/**
 *@brief 在oled上打印字符
 *@param row表示行范围0～4,colum为列0～16列
 *@return
 *@note
 */
void OLED_ShowChar(uint8_t row,uint8_t colum,char letter)
{
    uint8_t x = row * 8;
    uint8_t y = colum* 16;

    if(letter >='A' && letter <='Z')
    {
        for(uint8_t j = 0 ; j < 16 ; j++)
        {
            if(j == 8)
            {
                y+=8;
            }
            for(uint8_t k = 0 ; k < 8 ; k++)
            {
                OLED_DrawPoint(x + (j & 0x07),y+k,(LetterUp8x16[letter - 'A'][j] >>(k)) & 0x01 );
            }
        }
    }
    if(letter >= 'a' && letter <= 'z')
    {
        for(uint8_t j = 0 ; j < 16 ; j++)
        {
            if(j == 8)
            {
                y+=8;
            }
            for(uint8_t k = 0 ; k < 8 ; k++)
            {
                OLED_DrawPoint(x + (j & 0x07),y+k,(LetterDown8x16[letter - 'a'][j] >>(k)) & 0x01 );
            }
        }
    }
    if(letter >= ' ' && letter <= '/')
    {
        for(uint8_t j = 0 ; j < 16 ; j++)
        {
            if(j == 8)
            {
                y+=8;
            }
            for(uint8_t k = 0 ; k < 8 ; k++)
            {
                OLED_DrawPoint(x + (j & 0x07),y+k,(Symbol[letter - ' '][j] >>(k)) & 0x01 );
            }
        }
    }
    if(letter >= '0' && letter <= '9')
    {
        for(uint8_t j = 0 ; j < 16 ; j++)
        {
            if(j == 8)
            {
                y+=8;
            }
            for(uint8_t k = 0 ; k < 8 ; k++)
            {
                OLED_DrawPoint(x + (j & 0x07),y+k,(Numbers8x16[letter - '0'][j] >>(k)) & 0x01 );
            }
        }
    }

}

void OLED_ShowString(uint8_t row,uint8_t colum,char* string)
{

    for(uint16_t idx = 0 ; idx < strlen(string); idx++)
    {
        OLED_ShowChar(row + idx,colum,string[idx]);
    }
}

void OLED_ShowHex(uint8_t row ,uint8_t colum,uint16_t num)
{
    uint8_t y = colum* 16;

    uint8_t temp;
    for(uint8_t idx = 0 ; idx < 4 ; idx++)  
    {
        temp = (num >> (12 - 4 * idx))&0x0F ; 
        for(uint8_t j = 0 ; j < 16 ;j++)
        {
            if( 8 == j)
            {
               y+=8; 
            }
            for(uint8_t k = 0 ; k < 8 ; k++)
            {

                OLED_DrawPoint((row+ idx) * 8 + (j & 0x07) ,y+k,(HexNumbers[temp][j] >>(k)) & 0x01 );
            }
        }
     y = colum*16;
    }
}

void OLED_ShowBin(uint8_t row ,uint8_t colum,uint16_t num)
{
    uint8_t y = colum* 16;

    uint8_t temp;
    for(uint8_t idx = 0 ; idx < 16 ; idx++)  
    {
        temp = (num >> (15 - idx))&0x01 ; 
        for(uint8_t j = 0 ; j < 16 ;j++)
        {
            if( 8 == j)
            {
               y+=8; 
            }
            for(uint8_t k = 0 ; k < 8 ; k++)
            {

                OLED_DrawPoint((row+ idx) * 8 + (j & 0x07) ,y+k,(HexNumbers[temp][j] >>(k)) & 0x01 );
            }
        }
        y = 0;
    }
}
void OLED_ShowDec(uint8_t row ,uint8_t colum,uint16_t num)
{
    uint8_t y = colum* 16;

    uint8_t temp;
    for(uint8_t idx = 0 ; idx < 16 ; idx++)  
    {
        temp = (num >> (15 - idx))&0x01 ; 
        for(uint8_t j = 0 ; j < 16 ;j++)
        {
            if( 8 == j)
            {
               y+=8; 
            }
            for(uint8_t k = 0 ; k < 8 ; k++)
            {

                OLED_DrawPoint((row+ idx) * 8 + (j & 0x07) ,y+k,(HexNumbers[temp][j] >>(k)) & 0x01 );
            }
        }
        y = 0;
    }
}
void oled_init_hal(oled_t* oled)
{
    if(oled == NULL)
    {
        return ;
    }
    i2c_init(oled->i2c_port);
}

uint16_t oled_init(oled_t* oled)
{
    if(oled == NULL) 
   {
       return  0;
   }
   uint8_t cmd[] = {0x00,0x8D,0x14,0xA4,0xAF,0x20,0x00};
   uint8_t data[1025] = {0x00};
   data[0] = 0x40;
   memset(&data[1],0x00,1024);
   i2c_msg_t msgs[2] = {
       oled->dev_address,0,sizeof(cmd),cmd,
       oled->dev_address,0,sizeof(data),data
   };

   return i2c_transfer(oled->i2c_port,msgs,2);
}


//清屏
uint16_t oled_clear(oled_t* oled)
{
    if(oled == NULL) 
   {
       return  0;
   }
   uint8_t data[1025];
   data[0] = 0x40;
   memset(&data[1],0x00,1024);
   i2c_msg_t msgs[1] = {
       oled->dev_address,0,sizeof(data),data
   };
   return i2c_transfer(oled->i2c_port,msgs,1);
}

//渲染屏幕
uint16_t oled_point(oled_t* oled)
{
    if(oled == NULL) 
   {
       return  0;
   }
   uint8_t pack_flush_cmds[] = {
    0x00,       
    0x20, 0x00, 
    
    0x21, 0x00, 0x7F, 
    0x22, 0x00, 0x07
   };
   uint8_t data[1025] = {0x00};
   data[0] = 0x40;
   memcpy(&data[1],oled_buffer,sizeof(oled_buffer));
   i2c_msg_t msgs[2] = {
       oled->dev_address,0,sizeof(pack_flush_cmds),pack_flush_cmds,
       oled->dev_address,0,sizeof(data),data
   };
   return i2c_transfer(oled->i2c_port,msgs,2);
}
uint16_t oled_transfer(oled_t* oled,uint8_t *data)
{
   if(oled == NULL) 
   {
       return  0;
   }
   i2c_msg_t msgs[1];
   msgs[0].addr = oled->dev_address;
   msgs[0].flags = 0;
   msgs[0].len = sizeof(data);
   msgs[0].buf=data;

   return i2c_transfer(oled->i2c_port,msgs,1);
}


