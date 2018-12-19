/*
 * Copyright (C) 2016  Nexell Co., Ltd.
 * Author: DeokJin, Lee <truevirtue@nexell.co.kr>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <sysheader.h>
#if defined(PMIC_ON)
#include <i2c_gpio.h>
#if 0
#include <mp8845.h>

#define MP8845_CORE_I2C_GPIO_GRP 		4
#define MP8845_CORE_I2C_SCL 			11
#define MP8845_CORE_I2C_SDA 			10
#define MP8845_CORE_I2C_SCL_ALT			0
#define MP8845_CORE_I2C_SDA_ALT			0

#define MP8845_ARM_I2C_GPIO_GRP 		4
#define MP8845_ARM_I2C_SCL 			9
#define MP8845_ARM_I2C_SDA 			8
#define MP8845_ARM_I2C_SCL_ALT			0
#define MP8845_ARM_I2C_SDA_ALT			0

/************************************************
  * Rookie Board (PMIC: MP8845C)  - Reference 2016.04.05
  * ARM		: 1.25V
  * CORE	: 1.1V
  ************************************************/
void pmic_board_init(void)
{
	char data[4];

	/* I2C init for CORE power. */
	I2C_INIT(MP8845_CORE_I2C_GPIO_GRP, MP8845_CORE_I2C_SCL, MP8845_CORE_I2C_SDA,
			MP8845_CORE_I2C_SCL_ALT, MP8845_CORE_I2C_SDA_ALT);

	/* PFM -> PWM mode */
	mp8845_read(MP8845C_REG_SYSCNTL1, data, 1);
	data[0] |= 1 << 0;
	mp8845_write(MP8845C_REG_SYSCNTL1, data, 1);

	/* Core voltage change */
	mp8845_read(MP8845C_REG_SYSCNTL2, data, 1);
	data[0] |= 1 << 5;
	mp8845_write(MP8845C_REG_SYSCNTL2, data, 1);

	data[0] = 75 | 1 << 7;							// 1.1V
//	data[0] = 79 | 1<< 7;							// 1.125V
//	data[0] = 90 | 1 << 7;							// 1.2021V
	mp8845_write(MP8845C_REG_VSEL, data, 1);

	/* I2C init for ARM power. */
	I2C_INIT(MP8845_ARM_I2C_GPIO_GRP, MP8845_ARM_I2C_SCL, MP8845_ARM_I2C_SDA,
			MP8845_ARM_I2C_SCL_ALT, MP8845_CORE_I2C_SDA_ALT);

	/* PFM -> PWM mode */
	mp8845_read(MP8845C_REG_SYSCNTL1, data, 1);
	data[0] |= 1 << 0;
	mp8845_write(MP8845C_REG_SYSCNTL1, data, 1);

	/* ARM voltage change */
#if (ARM_VOLTAGE_CONTROL_SKIP == 0)
	mp8845_read(MP8845C_REG_SYSCNTL2, data, 1);
	data[0] |= 1 << 5;
	mp8845_write(MP8845C_REG_SYSCNTL2, data, 1);

//	data[0] = 75 | 1 << 7;   // 1.1V
	data[0] = 80 | 1 << 7; // 1.135V
	mp8845_write(MP8845C_REG_VSEL, data, 1);
#endif

	data[0] = 0x62 | 1 << 7;						// 98: 1.2556V
//	data[0] = 90 | 1<<7;							// 90: 1.2021 V
//	data[0] = 80 | 1<<7;							// 80: 1.135V
//	data[0] = 75 | 1 << 7;							// 75: 1.1V
	mp8845_write(MP8845C_REG_VSEL, data, 1);

	I2C_DEINIT();
}
#else
#include <nxe2000.h>

#define NXE2000_I2C_GPIO_GRP                    1                               // GPIOE
#define NXE2000_I2C_SCL                         12                              // SCL : GPIOE09
#define NXE2000_I2C_SDA                         11                              // SDA: GPIOE08
#define NXE2000_I2C_SCL_ALT                     2                               // SCL : ALT0
#define NXE2000_I2C_SDA_ALT                     2                               // SDA : ALT0

/************************************************
  * AVN Board (PMIC: NXE2000)  - Reference 2016.04.05
  * ARM         : 1.25V
  * CORE        : 1.2V
  * DDR         : 1.5V
  * DDR_IO      : 1.5Vf
  ************************************************/
void pmic_board_init(void)
{
         char data[4];
 
         /* I2C init for CORE & NXE2000 power. */
        I2C_INIT(NXE2000_I2C_GPIO_GRP, NXE2000_I2C_SCL, NXE2000_I2C_SDA,
                        NXE2000_I2C_SCL_ALT, NXE2000_I2C_SDA_ALT);

        /* ARM voltage change */        // 1.25V
        data[0] = nxe2000_get_dcdc_step(NXE2000_DEF_DDC1_VOL);
        nxe2000_write(NXE2000_REG_DC1VOL, data, 1);
        /* Core voltage change */       // 1.2V
        data[0] = nxe2000_get_dcdc_step(NXE2000_DEF_DDC2_VOL);
        nxe2000_write(NXE2000_REG_DC2VOL, data, 1);
        /* DDR3 voltage change */       // 1.5V
        data[0] = nxe2000_get_dcdc_step(NXE2000_DEF_DDC4_VOL);
        nxe2000_write(NXE2000_REG_DC4VOL, data, 1);
}
#endif
#endif
