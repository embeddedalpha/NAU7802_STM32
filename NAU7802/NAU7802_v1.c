/*
 * NAU7802.c
 *
 *  Created on: 07-Dec-2021
 *      Author: Kunal
 */


#include "NAU7802.h"


void NAU7802_1_Init(void)
{
//	int off11,off12,off13;
//	int off21,off22,off23;
//	int gain11,gain12,gain13,gain14;
//	int gain21,gain22,gain23,gain24;
	int temp;
//
//	nau1[0] = 0;
//	nau1[1] = 0;

	NAU7802_1.I2C = I2C1;
	NAU7802_1.mode = I2C_Fast_Mode;
	I2C_Master_Init(NAU7802_1);

	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x00, 0x01);
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x00, 0x00);
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x00, 0x06); //PUD | PUA | Internal LDO
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x01, 0x27); //LDO 3.3V | Gain = x127
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x11, 0x20); //Strong Pull up enabled
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x15, 0x30); //
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x1b, 0x68); //PGA inv | Chopper disabled 19 68
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x02, 0x34);
	Delay_ms(1000);
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x00, 0x16);
	Delay_ms(1);
//
//	do{
//		temp = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x02);
//	}while( (temp & (1 << 2)) == (1 << 2) );
//


}

int32_t NAU7802_1_Get_Load_Cell_1(void)
{
	int temp1, temp2, temp3;
	int32_t x;

	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x02, 0x30);
	Delay_ms(50);
//	do{
//		temp1 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x00);
//	}while((temp1 & (1 << 5)) != (1 << 5));
	temp1 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x12);
	temp2 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x13);
	temp3 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x14);

	x = temp1 << 16 | temp2 << 8 | temp3 << 0;
	return x;
}

int32_t NAU7802_1_Get_Load_Cell_2(void)
{
	int32_t temp1, temp2, temp3, x;


	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x02, 0xb0);
	Delay_ms(50);
//	do{
//		temp1 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x00);
//	}while((temp1 & (1 << 5)) != (1 << 5));
	temp1 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x12);
	temp2 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x13);
	temp3 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x14);

	x = temp1 << 16 | temp2 << 8 | temp3 << 0;
	return x;
}



void NAU7802_2_Init()
{
	int temp;

	NAU7802_2.I2C = I2C2;
	NAU7802_2.mode = I2C_Fast_Mode;
	I2C_Master_Init(NAU7802_2);

	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x00, 0x01);
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x00, 0x00);
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x00, 0x06); //PUD | PUA | Internal LDO
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x01, 0x27); //LDO 3.3V | Gain = x127
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x11, 0x20); //Strong Pull up enabled
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x15, 0x30); //
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x1b, 0x68); //PGA inv | Chopper disabled 19 68
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x02, 0x34);
	Delay_ms(1000);
	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x00, 0x16);
	Delay_ms(1);
}

int32_t NAU7802_2_Get_Load_Cell_1(void)
{
	int32_t temp1, temp2, temp3, x;
	temp1 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x02);
	temp1 &= ~(1 << 7);
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x02, temp1);
	Delay_ms(1);
	temp1 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x12);
	temp2 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x13);
	temp3 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x14);

	x = temp1 << 16 | temp2 << 8 | temp3 << 0;
	return x;
}

int32_t NAU7802_2_Get_Load_Cell_2(void)
{
	int32_t temp1, temp2, temp3, x;
	temp1 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x02);
	temp1 |= 1 << 7;
	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x02, temp1);
	Delay_ms(1);

	temp1 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x12);
	temp2 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x13);
	temp3 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x14);

	x = temp1 << 16 | temp2 << 8 | temp3 << 0;
	return x;
}


