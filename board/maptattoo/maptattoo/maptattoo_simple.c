// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 *
 * Author: Fabio Estevam <fabio.estevam@freescale.com>
 */

#include <asm/arch-mx6/clock.h>
#include <asm/arch-mx6/iomux.h>
#include <asm/arch-mx6/crm_regs.h>
#include <asm/arch-mx6/imx-regs.h>
#include <asm/arch-mx6/mx6-ddr.h>
#include <asm/arch-mx6/mx6-pins.h>
#include <asm/arch-mx6/sys_proto.h>
#include <asm/gpio.h>
#include <asm/mach-imx/boot_mode.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/mach-imx/mxc_i2c.h>
#include <asm/io.h>
#include <linux/sizes.h>
#include <common.h>
#include <fsl_esdhc_imx.h>
#include <i2c.h>
#include <mmc.h>
#include <power/pmic.h>
#include <power/pfuze100_pmic.h>
#include "../common/pfuze.h"
#include <usb.h>
#include <usb/ehci-ci.h>
#if defined(CONFIG_MXC_EPDC)
#include <lcd.h>
#include <mxc_epdc_fb.h>
#endif
#include <configs/maptattoo.h>
DECLARE_GLOBAL_DATA_PTR;

#define UART_PAD_CTRL  (PAD_CTL_PKE | PAD_CTL_PUE |		\
	PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |		\
	PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#define USDHC_PAD_CTRL (PAD_CTL_PUS_22K_UP |			\
	PAD_CTL_SPEED_LOW | PAD_CTL_DSE_80ohm |			\
	PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#define ENET_PAD_CTRL  (PAD_CTL_PKE | PAD_CTL_PUE |             \
	PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED   |             \
	PAD_CTL_DSE_40ohm   | PAD_CTL_HYS)

#define I2C_PAD_CTRL (PAD_CTL_PKE | PAD_CTL_PUE |		\
		      PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |	\
		      PAD_CTL_DSE_40ohm | PAD_CTL_HYS |		\
		      PAD_CTL_ODE | PAD_CTL_SRE_FAST)

#define OTGID_PAD_CTRL (PAD_CTL_PKE | PAD_CTL_PUE |		\
			PAD_CTL_PUS_47K_UP | PAD_CTL_SPEED_LOW |\
			PAD_CTL_DSE_80ohm | PAD_CTL_HYS |	\
			PAD_CTL_SRE_FAST)

#define ELAN_INTR_PAD_CTRL (PAD_CTL_PKE | PAD_CTL_PUE | \
			    PAD_CTL_PUS_47K_UP | PAD_CTL_HYS)

#define EPDC_PAD_CTRL    (PAD_CTL_PKE | PAD_CTL_SPEED_MED |	\
	PAD_CTL_DSE_40ohm | PAD_CTL_HYS)

#define ETH_PHY_POWER	IMX_GPIO_NR(4, 21)

int dram_init(void)
{
	gd->ram_size = imx_ddr_size();

	return 0;
}

static iomux_v3_cfg_t const uart1_pads[] = {
	MX6_PAD_UART1_TXD__UART1_DCE_TX | MUX_PAD_CTRL(UART_PAD_CTRL),
	MX6_PAD_UART1_RXD__UART1_DCE_RX | MUX_PAD_CTRL(UART_PAD_CTRL),
};

void setup_iomux_uart(void)
{
	imx_iomux_v3_setup_multiple_pads(uart1_pads, ARRAY_SIZE(uart1_pads));
}


void setup_debug_led(void) {

	/* EPDC_VCOM1 - GPIO2[04] for DEBUG_LED control */
	imx_iomux_v3_setup_pad(MX6_PAD_EPDC_VCOM1__GPIO2_IO04 |
				MUX_PAD_CTRL(EPDC_PAD_CTRL));

	imx_iomux_v3_setup_pad(MX6_PAD_GPIO4_IO21__GPIO4_IO21 |
				MUX_PAD_CTRL(EPDC_PAD_CTRL));

	imx_iomux_v3_setup_pad(MX6_PAD_GPIO4_IO23__GPIO4_IO23 |
				MUX_PAD_CTRL(EPDC_PAD_CTRL));	
	/* Set as output */
	gpio_request(IMX_GPIO_NR(2, 4), "epdc_vcom1");
	gpio_direction_output(IMX_GPIO_NR(2, 4), 1);
	gpio_set_value(IMX_GPIO_NR(2, 4), 1);

	gpio_request(IMX_GPIO_NR(4, 21), "gpio4_io21");
	gpio_direction_output(IMX_GPIO_NR(4, 21), 0);
	gpio_set_value(IMX_GPIO_NR(4, 21), 0);

	gpio_request(IMX_GPIO_NR(4, 23), "gpio4_io23");
	gpio_direction_output(IMX_GPIO_NR(4, 23), 1);
	gpio_set_value(IMX_GPIO_NR(4, 23), 1);
}




#ifdef CONFIG_SPL_BUILD

#endif


#ifdef CONFIG_MXC_EPDC

#endif


#ifdef CONFIG_SYS_I2C
#define PC	MUX_PAD_CTRL(I2C_PAD_CTRL)

#endif





#ifdef CONFIG_FEC_MXC

#endif



#ifdef CONFIG_USB_EHCI_MX6
#ifndef CONFIG_DM_USB

#define USB_OTHERREGS_OFFSET	0x800
#define UCTRL_PWR_POL		(1 << 9)

#endif
#endif



#ifdef CONFIG_MXC_EPDC

#endif


int board_init(void)
{

	return 0;
}



int checkboard(void)
{

	return 0;
}


#ifdef CONFIG_MXC_KPD
#define MX6SLL_KEYPAD_CTRL (PAD_CTL_HYS | PAD_CTL_PKE | PAD_CTL_PUE | \
			   PAD_CTL_PUS_100K_UP | PAD_CTL_DSE_120ohm)

#endif /*CONFIG_MXC_KPD*/



#ifdef CONFIG_SPL_BUILD
#include <spl.h>
#include <linux/libfdt.h>

#define USDHC1_CD_GPIO	IMX_GPIO_NR(4, 7)
#define USDHC2_CD_GPIO	IMX_GPIO_NR(5, 0)
#define USDHC3_CD_GPIO	IMX_GPIO_NR(3, 22)


static void ccgr_init(void)
{
	struct mxc_ccm_reg *ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;
//from crm_regs.h works for mx6sll

	writel(0xFFFFFFFF, &ccm->CCGR0);
	writel(0xFFFFFFFF, &ccm->CCGR1);
	writel(0xFFFFFFFF, &ccm->CCGR2);
	writel(0xFFFFFFFF, &ccm->CCGR3);
	writel(0xFFFFFFFF, &ccm->CCGR4);
	writel(0xFFFFFFFF, &ccm->CCGR5);
	writel(0xFFFFFFFF, &ccm->CCGR6);

}

static void spl_dram_init(void) {

}

void my_board_init_f(ulong dummy)
{
	
	arch_cpu_init();
	ccgr_init();

	setup_debug_led();
	//timer_init();

	setup_iomux_uart();

	/* UART clocks enabled and gd valid - init serial console */
	preloader_console_init();


	spl_dram_init();

}
#endif
