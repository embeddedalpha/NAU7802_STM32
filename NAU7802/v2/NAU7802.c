/*
 * NAU7802.c
 *
 *  Created on: 07-Dec-2021
 *      Author: Kunal
 */


#include "NAU7802.h"

static int reset_1()
{
	int temp;
	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x00, 1, bit_0);
	Delay_ms(1);
	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x00, 0, bit_0);
	temp = I2C_Master_Read_Register_bit(NAU7802_1, nau7802_address, 0x00, bit_0);
	return temp;
}

static int reset_2()
{
	int temp;
	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x00, 1, bit_0);
	Delay_ms(1);
	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x00, 0, bit_0);
	temp = I2C_Master_Read_Register_bit(NAU7802_2, nau7802_address, 0x00, bit_0);
	return temp;
}

static void powerup_1()
{
	int temp;
	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x00, 1, bit_1); //Power up digital circuit
	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x00, 1, bit_2); //Power up analog circuit
	Delay_ms(100);
	do{
		temp = I2C_Master_Read_Register_bit(NAU7802_1, nau7802_address, 0x00, bit_3);
	}while(!(temp & I2C_Master_Read_Register_bit(NAU7802_1, nau7802_address, 0x00, bit_3)));
}

static void powerup_2()
{
	int temp;
	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x00, 1, bit_1); //Power up digital circuit
	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x00, 1, bit_2); //Power up analog circuit
	Delay_ms(100);
	do{
		temp = I2C_Master_Read_Register_bit(NAU7802_2, nau7802_address, 0x00, bit_3);
	}while(!(temp & I2C_Master_Read_Register_bit(NAU7802_2, nau7802_address, 0x00, bit_3)));
}


static void setLDO_1()
{

	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x01, 1, bit_5); //3.3v LDO
}

static void setLDO_2()
{

	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x01, 1, bit_5); //3.3v LDO
}

static void setGAIN_1()
{

	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x01, 1, bit_2 | bit_1 | bit_0); //GAIN x128
}

static void setGAIN_2()
{

	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x01, 1, bit_2 | bit_1 | bit_0); //GAIN x128
}

static void setSampleRate_1()
{

	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x02, 1, bit_5 | bit_4); //80SPS
}

static void setSampleRate_2()
{
	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x02, 1, bit_5 | bit_4); //80SPS
}

static void calibrate_1()
{
	int temp;
//	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x02, 0, bit_1 | bit_0); //Offset Calibration Internal
	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x02, 1, bit_2 ); //Trigger Calibration
	do{
		temp = I2C_Master_Read_Register_bit(NAU7802_1, nau7802_address, 0x02, bit_3);
	}while((temp == 1));
}

static void calibrate_2()
{
	int temp;
//	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x02, 0, bit_1 | bit_0); //Offset Calibration Internal
	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x02, 1, bit_2 ); //Trigger Calibration
	do{
		temp = I2C_Master_Read_Register_bit(NAU7802_2, nau7802_address, 0x02, bit_3);
	}while(temp == 1);
}



void NAU7802_1_Init(void)
{


	NAU7802_1.I2C = I2C1;
	NAU7802_1.mode = I2C_Fast_Mode;
	I2C_Master_Init(NAU7802_1);

//	reset_1();
//	powerup_1();
//	setLDO_1();
//	setGAIN_1();
//	setSampleRate_1();
//	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x11, 0x20); //Strong Pull up enabled
//	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x15, 0x30);
//	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x1b, 0xA9); //PGA inv | Chopper disabled 19 68
//	calibrate_1();
//
//	int temp = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x1B);



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
////
////	do{
////		temp = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x02);
////	}while( (temp & (1 << 2)) == (1 << 2) );
////


}

int32_t NAU7802_1_Get_Load_Cell_1(void)
{


	int temp1, temp2, temp3;
	int32_t x;
	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x02, 0, bit_7);
	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x00, 1, bit_4);
	do{
		temp1 = I2C_Master_Read_Register_bit(NAU7802_1, nau7802_address, 0x00, bit_5);
	}while(temp1 != 1);
	calibrate_1();

//
////	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x02, 0x30);
//	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x02, 0, bit_7);
//	temp1 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x02);
//	calibrate_1();
//	temp1 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x02);
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


//	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x02, 0xb0);
	I2C_Master_Write_Register_bits(NAU7802_1, nau7802_address, 0x02, 1, bit_7);
	temp1 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x02);
	calibrate_1();
	temp1 = I2C_Master_Read_Register(NAU7802_1, nau7802_address, 0x02);
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
//	int temp;

	NAU7802_2.I2C = I2C2;
	NAU7802_2.mode = I2C_Fast_Mode;
	I2C_Master_Init(NAU7802_2);

	reset_2();
	powerup_2();
	setLDO_2();
	setGAIN_2();
	setSampleRate_2();
	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x15, 0x30);
	calibrate_2();



//	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x00, 0x01);
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x00, 0x00);
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x00, 0x06); //PUD | PUA | Internal LDO
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x01, 0x27); //LDO 3.3V | Gain = x127
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x11, 0x20); //Strong Pull up enabled
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x15, 0x30); //
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x1b, 0x68); //PGA inv | Chopper disabled 19 68
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x02, 0x34);
//	Delay_ms(1000);
//	I2C_Master_Write_Register(NAU7802_2, nau7802_address, 0x00, 0x16);
//	Delay_ms(1);
}

int32_t NAU7802_2_Get_Load_Cell_1(void)
{
	int32_t temp1, temp2, temp3, x;
	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x02, 0, bit_7);
	calibrate_2();
	Delay_ms(50);
//	temp1 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x02);
//	temp1 &= ~(1 << 7);
//	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x02, temp1);
//	Delay_ms(1);
	temp1 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x12);
	temp2 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x13);
	temp3 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x14);

	x = temp1 << 16 | temp2 << 8 | temp3 << 0;
	return x;
}

int32_t NAU7802_2_Get_Load_Cell_2(void)
{
	int32_t temp1, temp2, temp3, x;
	I2C_Master_Write_Register_bits(NAU7802_2, nau7802_address, 0x02, 1, bit_7);
	calibrate_2();
	Delay_ms(50);
//	temp1 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x02);
//	temp1 |= 1 << 7;
//	I2C_Master_Write_Register(NAU7802_1, nau7802_address, 0x02, temp1);
//	Delay_ms(1);

	temp1 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x12);
	temp2 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x13);
	temp3 = I2C_Master_Read_Register(NAU7802_2, nau7802_address, 0x14);

	x = temp1 << 16 | temp2 << 8 | temp3 << 0;
	return x;
}



