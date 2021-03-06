#ifndef BUILD_LK
#include <linux/string.h>
#include <linux/kernel.h>
#endif

#include "lcm_drv.h"

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  		(720)
#define FRAME_HEIGHT 		(1280)

#define REGFLAG_DELAY         	(0XFFFE)
#define REGFLAG_END_OF_TABLE  	(0xFFFF)	// END OF REGISTERS MARKER


#define LCM_DSI_CMD_MODE	0

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static struct LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)	(lcm_util.set_reset_pin((v)))

#define UDELAY(n) 		(lcm_util.udelay(n))
#define MDELAY(n) 		(lcm_util.mdelay(n))

#define LCM_RM68200_ID 		(0x6820)


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)						lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)			lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)						lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)			lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

struct LCM_setting_table
{
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};


static struct LCM_setting_table lcm_initialization_setting[] = {
{0xFE,   1, {0x1}},
{0x24,   1,{0xC0}},
{0x25,   1,{0x53}},
{0x26,   1, {0x0}},
{0x2B,   1,{0xE5}},
{0x27,   1, {0xA}},
{0x29,   1, {0xA}},
{0x2F,   1,{0x44}},
{0x34,   1,{0x59}},
{0x1B,   1, {0x0}},
{0x12,   1, {0x8}},
{0x46,   1,{0x90}},
{0x52,   1,{0x8A}},
{0x53,   1, {0x0}},
{0x54,   1,{0x8A}},
{0x55,   1, {0x0}},
{0x5F,   1,{0x12}},
{0xFE,   1, {0x3}},
{ 0x0,   1, {0x5}},
{ 0x1,   1,{0x16}},
{ 0x2,   1, {0x1}},
{ 0x3,   1, {0x8}},
{ 0x4,   1, {0x0}},
{ 0x5,   1, {0x0}},
{ 0x6,   1,{0x50}},
{ 0x7,   1, {0x0}},
{ 0x8,   1, {0x0}},
{ 0x9,   1, {0x0}},
{ 0xA,   1, {0x0}},
{ 0xB,   1, {0x0}},
{ 0xC,   1, {0x0}},
{ 0xD,   1, {0x0}},
{ 0xE,   1, {0x5}},
{ 0xF,   1, {0x6}},
{0x10,   1, {0x7}},
{0x11,   1, {0x8}},
{0x12,   1, {0x0}},
{0x13,   1,{0x40}},
{0x14,   1, {0x0}},
{0x15,   1,{0xC5}},
{0x16,   1, {0x8}},
{0x17,   1, {0x9}},
{0x18,   1, {0xA}},
{0x19,   1, {0xB}},
{0x1A,   1, {0xC}},
{0x1B,   1, {0x0}},
{0x1C,   1,{0x40}},
{0x1D,   1, {0x0}},
{0x1E,   1,{0x85}},
{0x1F,   1, {0x8}},
{0x20,   1, {0x0}},
{0x21,   1, {0x0}},
{0x22,   1, {0x5}},
{0x23,   1, {0x4}},
{0x24,   1, {0x6}},
{0x25,   1,{0x2D}},
{0x26,   1, {0x0}},
{0x27,   1, {0x8}},
{0x28,   1, {0xA}},
{0x29,   1,{0x2D}},
{0x2A,   1, {0x0}},
{0x2B,   1, {0x0}},
{0x2D,   1, {0x0}},
{0x2F,   1, {0x0}},
{0x30,   1, {0x0}},
{0x31,   1, {0x0}},
{0x32,   1, {0x0}},
{0x33,   1, {0x0}},
{0x34,   1, {0x0}},
{0x35,   1, {0x0}},
{0x36,   1, {0x0}},
{0x37,   1, {0x0}},
{0x38,   1, {0x0}},
{0x39,   1, {0x0}},
{0x3A,   1, {0x0}},
{0x3B,   1, {0x0}},
{0x3D,   1, {0x0}},
{0x3F,   1, {0x0}},
{0x40,   1, {0x0}},
{0x41,   1, {0x0}},
{0x42,   1, {0x0}},
{0x43,   1, {0x0}},
{0x44,   1, {0x0}},
{0x45,   1, {0x0}},
{0x46,   1, {0x0}},
{0x47,   1, {0x0}},
{0x48,   1, {0x0}},
{0x49,   1, {0x0}},
{0x4A,   1, {0x0}},
{0x4B,   1, {0x0}},
{0x4C,   1, {0x0}},
{0x4D,   1, {0x0}},
{0x4E,   1, {0x0}},
{0x4F,   1, {0x0}},
{0x50,   1, {0x0}},
{0x51,   1, {0x0}},
{0x52,   1, {0x0}},
{0x53,   1, {0x0}},
{0x54,   1, {0x0}},
{0x55,   1, {0x0}},
{0x56,   1, {0x0}},
{0x58,   1, {0x0}},
{0x59,   1, {0x0}},
{0x5A,   1, {0x0}},
{0x5B,   1, {0x0}},
{0x5C,   1, {0x0}},
{0x5D,   1, {0x0}},
{0x5E,   1, {0x0}},
{0x5F,   1, {0x0}},
{0x60,   1, {0x0}},
{0x61,   1, {0x0}},
{0x62,   1, {0x0}},
{0x63,   1, {0x0}},
{0x64,   1, {0x0}},
{0x65,   1, {0x0}},
{0x66,   1, {0x0}},
{0x67,   1, {0x0}},
{0x68,   1, {0x0}},
{0x69,   1, {0x0}},
{0x6A,   1, {0x0}},
{0x6B,   1, {0x0}},
{0x6C,   1, {0x0}},
{0x6D,   1, {0x0}},
{0x6E,   1, {0x0}},
{0x6F,   1, {0x0}},
{0x70,   1, {0x0}},
{0x71,   1, {0x0}},
{0x72,   1, {0x0}},
{0x73,   1, {0x0}},
{0x74,   1, {0x1}},
{0x75,   1, {0x1}},
{0x76,   1, {0x1}},
{0x77,   1, {0x1}},
{0x78,   1, {0x1}},
{0x79,   1, {0x1}},
{0x7A,   1, {0x0}},
{0x7B,   1, {0x0}},
{0x7C,   1, {0x0}},
{0x7D,   1, {0x0}},
{0x7E,   1, {0x1}},
{0x7F,   1, {0x9}},
{0x80,   1, {0xB}},
{0x81,   1, {0xD}},
{0x82,   1, {0xF}},
{0x83,   1,{0x3F}},
{0x84,   1,{0x3F}},
{0x85,   1,{0x1C}},
{0x86,   1,{0x1C}},
{0x87,   1,{0x3F}},
{0x88,   1,{0x3F}},
{0x89,   1,{0x3F}},
{0x8A,   1,{0x3F}},
{0x8B,   1,{0x3F}},
{0x8C,   1,{0x3F}},
{0x8D,   1,{0x3F}},
{0x8E,   1,{0x3F}},
{0x8F,   1,{0x3F}},
{0x90,   1,{0x3F}},
{0x91,   1,{0x1D}},
{0x92,   1,{0x1C}},
{0x93,   1, {0x3}},
{0x94,   1, {0x2}},
{0x95,   1,{0x1C}},
{0x96,   1,{0x1D}},
{0x97,   1,{0x3F}},
{0x98,   1,{0x3F}},
{0x99,   1,{0x3F}},
{0x9A,   1,{0x3F}},
{0x9B,   1,{0x3F}},
{0x9C,   1,{0x3F}},
{0x9D,   1,{0x3F}},
{0x9E,   1,{0x3F}},
{0x9F,   1,{0x3F}},
{0xA0,   1,{0x3F}},
{0xA2,   1,{0x1C}},
{0xA3,   1,{0x1C}},
{0xA4,   1,{0x3F}},
{0xA5,   1,{0x3F}},
{0xA6,   1, {0xE}},
{0xA7,   1, {0xC}},
{0xA9,   1, {0xA}},
{0xAA,   1, {0x8}},
{0xAB,   1, {0x0}},
{0xAC,   1, {0x2}},
{0xAD,   1, {0xE}},
{0xAE,   1, {0xC}},
{0xAF,   1, {0xA}},
{0xB0,   1, {0x8}},
{0xB1,   1,{0x3F}},
{0xB2,   1,{0x3F}},
{0xB3,   1,{0x1C}},
{0xB4,   1,{0x1C}},
{0xB5,   1,{0x3F}},
{0xB6,   1,{0x3F}},
{0xB7,   1,{0x3F}},
{0xB8,   1,{0x3F}},
{0xB9,   1,{0x3F}},
{0xBA,   1,{0x3F}},
{0xBB,   1,{0x3F}},
{0xBC,   1,{0x3F}},
{0xBD,   1,{0x3F}},
{0xBE,   1,{0x3F}},
{0xBF,   1,{0x1C}},
{0xC0,   1,{0x1D}},
{0xC1,   1, {0x0}},
{0xC2,   1, {0x1}},
{0xC3,   1,{0x1D}},
{0xC4,   1,{0x1C}},
{0xC5,   1,{0x3F}},
{0xC6,   1,{0x3F}},
{0xC7,   1,{0x3F}},
{0xC8,   1,{0x3F}},
{0xC9,   1,{0x3F}},
{0xCA,   1,{0x3F}},
{0xCB,   1,{0x3F}},
{0xCC,   1,{0x3F}},
{0xCD,   1,{0x3F}},
{0xCE,   1,{0x3F}},
{0xCF,   1,{0x1C}},
{0xD0,   1,{0x1C}},
{0xD1,   1,{0x3F}},
{0xD2,   1,{0x3F}},
{0xD3,   1, {0x9}},
{0xD4,   1, {0xB}},
{0xD5,   1, {0xD}},
{0xD6,   1, {0xF}},
{0xD7,   1, {0x3}},
{0xDF,   1, {0x0}},
{0xDC,   1, {0x2}},
{0xDE,   1, {0x8}},
{0xFE,   1, {0xE}},
{ 0x1,   1,{0x75}},
{0xFE,   1, {0x4}},
{0x60,   1, {0x0}},
{0x61,   1, {0x6}},
{0x62,   1, {0xA}},
{0x63,   1, {0xC}},
{0x64,   1, {0x4}},
{0x65,   1,{0x10}},
{0x66,   1, {0xE}},
{0x67,   1, {0xA}},
{0x68,   1,{0x17}},
{0x69,   1, {0xC}},
{0x6A,   1,{0x10}},
{0x6B,   1, {0x7}},
{0x6C,   1, {0xF}},
{0x6D,   1, {0xB}},
{0x6E,   1, {0x1}},
{0x6F,   1, {0x0}},
{0x70,   1, {0x0}},
{0x71,   1, {0x6}},
{0x72,   1, {0xA}},
{0x73,   1, {0xC}},
{0x74,   1, {0x4}},
{0x75,   1,{0x10}},
{0x76,   1, {0xE}},
{0x77,   1, {0xA}},
{0x78,   1,{0x17}},
{0x79,   1, {0xC}},
{0x7A,   1,{0x10}},
{0x7B,   1, {0x7}},
{0x7C,   1, {0xF}},
{0x7D,   1, {0xB}},
{0x7E,   1, {0x1}},
{0x7F,   1, {0x0}},
{0xFE,   1, {0x0}},
{0x58,   1,{0xA9}},
{0x35,   0,   {0}},
{0x11,   1, {0x0}},
{REGFLAG_DELAY, 120, {}},
{0x29,   1, {0x0}},
{REGFLAG_DELAY, 20, {}},
{REGFLAG_END_OF_TABLE, 0x00, {}}
};

static struct LCM_setting_table lcm_sleep_in_setting[] = {
	// Display off sequence
	{0x01, 1, {0x00}},
	{REGFLAG_DELAY, 50, {}},
	
	{0x28, 1, {0x00}},
	{REGFLAG_DELAY, 50, {}},

	// Sleep Mode On
	{0x10, 1, {0x00}},
	{REGFLAG_DELAY, 50, {}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};

static void push_table(struct LCM_setting_table *table, unsigned int count,
		unsigned char force_update)
{
	unsigned int i;

	for (i = 0; i < count; i++)
	{
		unsigned cmd;

		cmd = table[i].cmd;
		switch (cmd)
		{
			case REGFLAG_DELAY:
				MDELAY(table[i].count);
				break;
			case REGFLAG_END_OF_TABLE:
				break;
			default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
		}
	}

}


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const struct LCM_UTIL_FUNCS * util)
{
	memcpy(&lcm_util, util, sizeof(struct LCM_UTIL_FUNCS));
}


static void lcm_get_params(struct LCM_PARAMS * params)
{
	memset(params, 0, sizeof(struct LCM_PARAMS));

	params->dsi.LANE_NUM = 3;
  params->dsi.packet_size = 256;
  params->dsi.vertical_backporch = 14;
  params->dsi.horizontal_sync_active = 4;
  params->dsi.horizontal_frontporch = 8;
  params->dsi.PLL_CLOCK = 236;
  params->type = 2;
  params->dsi.data_format.format = 2;
  params->dsi.PS = 2;
  params->dsi.vertical_sync_active = 2;
  params->width = 720;
  params->dsi.horizontal_active_pixel = 720;
  params->height = 1280;
  params->dsi.vertical_active_line = 1280;
  params->dbi.te_mode = 0;
  params->dbi.te_edge_polarity = 0;
  params->dsi.data_format.color_order = 0;
  params->dsi.data_format.trans_seq = 0;
  params->dsi.data_format.padding = 0;
  params->dsi.intermediat_buffer_num = 0;
  params->dsi.mode = 1;
  params->dsi.esd_check_enable = 1;
  params->dsi.customization_esd_check_enable = 1;
  params->dsi.cont_clock = 1;
  params->dsi.vertical_frontporch = 16;
  params->dsi.horizontal_backporch = 16;
}

static void lcm_init(void)
{

	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(50);
	SET_RESET_PIN(1);
	MDELAY(120);

	push_table(lcm_initialization_setting,sizeof(lcm_initialization_setting) /sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
 
	SET_RESET_PIN(1);
	MDELAY(150);
	SET_RESET_PIN(0);
	MDELAY(30);
	
	push_table(lcm_sleep_in_setting,sizeof(lcm_sleep_in_setting) /sizeof(struct LCM_setting_table), 1);

}


static void lcm_resume(void)
{   
	lcm_init();
}

static unsigned int lcm_compare_id(void)
{
	int array[4];
	char buffer[5];
	char id_high=0;
	char id_low=0;
	int id1=0;
	int id2=0;

	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(200);
	array[0]=0x01FE1500;
	dsi_set_cmdq(array,1, 1);

	array[0] = 0x00013700;
	dsi_set_cmdq(array, 1, 1);
	read_reg_v2(0xde, buffer, 1);

	id_high = buffer[0];
	read_reg_v2(0xdf, buffer, 1);
	id_low = buffer[0];
	id1 = (id_high<<8) | id_low;

	#if defined(BUILD_LK)
	printf("rm68200 %s id1 = 0x%04x, id2 = 0x%04x\n", __func__, id1,id2);
	#else
	printk("rm68200 %s id1 = 0x%04x, id2 = 0x%04x\n", __func__, id1,id2);
	#endif
	return (LCM_RM68200_ID == id1)?1:0;

}

// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------
struct LCM_DRIVER hct_rm68200_dsi_vdo_hd_cpt = 
{
	.name		= "hct_rm68200_dsi_vdo_hd_cpt",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,	
	.compare_id     = lcm_compare_id,	
};
