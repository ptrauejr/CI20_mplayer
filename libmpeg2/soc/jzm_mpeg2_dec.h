/*
 * Copyright (C) 2006-2014 Ingenic Semiconductor CO.,LTD.
 *
 * This file is part of MPlayer.
 *
 * MPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MPlayer; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/****************************************************************
*****************************************************************/

#ifndef __JZM_MPEG2_DEC_H__
#define __JZM_MPEG2_DEC_H__
#include "jzm_vpu.h"

/************************************************************
 Chain Space Allocation
 ************************************************************/
#define TCSM1_BANK0         (VPU_BASE | 0xC0000)
#define SRAM_BANK0          (VPU_BASE | 0xF0000)

//#define JZM_SIMPLE
#ifdef  JZM_SIMPLE
#define MPEG2_FIFO_DEP          8
#else
#define MPEG2_FIFO_DEP          16
#endif

#define MSRC_ONE_LEN            (1024)
#define MSRC_DEP                MPEG2_FIFO_DEP
#define MSRC_BUF_LEN            (MSRC_ONE_LEN*MSRC_DEP) /*0x4000*/

#define TCSM1_MSRC_BUF          SRAM_BANK0

#define MC_CHN_ONELEN           (32<<2)
#define MC_CHN_DEP              MPEG2_FIFO_DEP 
#define MC_CHN_LEN              (MC_CHN_ONELEN*MC_CHN_DEP) /*0x800*/
#define TCSM1_MOTION_DHA        (TCSM1_BANK0)
#define TCSM1_MOTION_DSA        (TCSM1_MOTION_DHA + MC_CHN_LEN- 4)

#define VMAU_CHN_ONELEN         (8<<2)
#define VMAU_CHN_DEP            MPEG2_FIFO_DEP
#define VMAU_CHN_LEN            (VMAU_CHN_ONELEN*VMAU_CHN_DEP) /*0x200*/
//#define VMAU_CHN_BASE           (TCSM1_BANK0+ 0x800)
#define VMAU_CHN_BASE           (TCSM1_MOTION_DHA+ MC_CHN_LEN)
#define VMAU_END_FLAG           (VMAU_CHN_BASE+VMAU_CHN_LEN- 4)

#define DBLK_CHN_ONELEN         (2<<2)
#define DBLK_CHN_DEP            MPEG2_FIFO_DEP
#define DBLK_CHN_LEN            (DBLK_CHN_ONELEN*DBLK_CHN_DEP)
//#define DBLK_CHN_BASE           (TCSM1_BANK0+ 0xa00)
#define DBLK_CHN_BASE           (VMAU_CHN_BASE+ VMAU_CHN_LEN)
#define DBLK_END_FLAG           (DBLK_CHN_BASE+DBLK_CHN_LEN)
#define DBLK_SEND_FLAG          (DBLK_END_FLAG + 4)

#define DBLK_DMA_END_BASE       DBLK_END_FLAG
#define DBLK_CHN_END_BASE       DBLK_SEND_FLAG

#define DOUT_Y_STRD  (16)
#define DOUT_C_STRD  (8)



/* ----------------- SDE VLC TABLE ---------------- */
//mba
#define MBA_5_BASE  0x1f0 //0x1f0-0x1f7a
#define MBA_5_LEN  8 //0x1f0-0x1f7a
#define MBA_11_BASE  0x080 //0x080-0x0bf
#define MBA_11_LEN  64 //0x080-0x0bf
//mb
#define MB_I_BASE 0x222 //0x222
#define MB_I_LEN 1
#define MB_P_BASE 0x1a0 //0x1a0-0x1af
#define MB_P_LEN 16 //0x1a0-0x1af
#define MB_B_BASE 0x100 //0x100-0x11f
#define MB_B_LEN 32 //0x100-0x11f
//cbp
#define CBP_7_BASE 0x0c0 //0x0c0-0x0ff
#define CBP_7_LEN 64 //0x0c0-0x0ff
#define CBP_9_BASE 0x120 //0x120-0x13f
#define CBP_9_LEN 32 //0x120-0x13f
//dc
#define DC_lum_5_BASE 0x1f8 // 0x1f8-0x1ff
#define DC_lum_5_LEN 8 // 0x1f8-0x1ff
#define DC_long_BASE 0x200 // 0x200-0x207
#define DC_long_LEN 8 // 0x200-0x207
#define DC_chrom_5_BASE 0x208 // 0x208-0x20f
#define DC_chrom_5_LEN 8 // 0x208-0x20f
//dct
#define DCT_B15_8_BASE	0x000 //0x000-0x07f
#define DCT_B15_8_LEN	128 //0x000-0x07f
#define DCT_B15_10_BASE	0x210 //0x210-0x217
#define DCT_B15_10_LEN	8 //0x210-0x217
#define DCT_13_BASE	0x140 // 0x140-0x15f
#define DCT_13_LEN	32 // 0x140-0x15f
#define DCT_15_BASE	0x160 //0x160-0x17f
#define DCT_15_LEN	32 //0x160-0x17f
#define DCT_16_BASE	0x1b0 //0x1b0-0x1bf
#define DCT_16_LEN	16 //0x1b0-0x1bf
#define DCT_B14AC_5_BASE  0x1c0 //0x1c0-0x1cf
#define DCT_B14AC_5_LEN  16 //0x1c0-0x1cf
#define DCT_B14DC_5_BASE  0x1d0 //0x1d0-0x1df
#define DCT_B14DC_5_LEN  16 //0x1d0-0x1df
#define DCT_B14_8_BASE	  0x180//0x180-0x19f
#define DCT_B14_8_LEN	  32//0x180-0x19f
#define DCT_B14_10_BASE	0x218 //0x218-0x21f
#define DCT_B14_10_LEN	8 //0x218-0x21f
// mvd
#define MV_4_BASE	0x220//0x220-0x221
#define MV_4_LEN	2//0x220-0x221
#define MV_10_BASE	0x1e0//0x1e0-0x1ef
#define MV_10_LEN	16//0x1e0-0x1ef
// dmv
#define DMV_2_BASE	0x223//0x223
#define DMV_2_LEN	1//0x223


__place_k0_data__ unsigned int MBA_5_HW[8] = {
  0x55650000, 0x34344444, 0x23232323, 0x13131313, 0x01010101, 0x01010101, 0x01010101, 0x01010101, // 0x0 
};
__place_k0_data__ unsigned int MBA_11_HW[64] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 0x0 
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x1f0b200b, 0x1d0b1e0b, 0x1b0b1c0b, 0x190b1a0b, // 0x1 
  0x170b180b, 0x150b160b, 0x140a140a, 0x130a130a, 0x120a120a, 0x110a110a, 0x100a100a, 0x0f0a0f0a, // 0x2 
  0x0e080e08, 0x0e080e08, 0x0e080e08, 0x0e080e08, 0x0d080d08, 0x0d080d08, 0x0d080d08, 0x0d080d08, // 0x3 
  0x0c080c08, 0x0c080c08, 0x0c080c08, 0x0c080c08, 0x0b080b08, 0x0b080b08, 0x0b080b08, 0x0b080b08, // 0x4 
  0x0a080a08, 0x0a080a08, 0x0a080a08, 0x0a080a08, 0x09080908, 0x09080908, 0x09080908, 0x09080908, // 0x5 
  0x08070807, 0x08070807, 0x08070807, 0x08070807, 0x08070807, 0x08070807, 0x08070807, 0x08070807, // 0x6 
  0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, // 0x7 
};
__place_k0_data__ unsigned int MB_P_HW[16] = {
  0x12051106, 0x01051a05, 0x08030803, 0x08030803, 0x02020202, 0x02020202, 0x02020202, 0x02020202, // 0x0 
  0x0a010a01, 0x0a010a01, 0x0a010a01, 0x0a010a01, 0x0a010a01, 0x0a010a01, 0x0a010a01, 0x0a010a01, // 0x1 
};
__place_k0_data__ unsigned int MB_B_HW[32] = {
  0x11060006, 0x1a061606, 0x1e051e05, 0x01050105, 0x08040804, 0x08040804, 0x0a040a04, 0x0a040a04, // 0x0 
  0x04030403, 0x04030403, 0x04030403, 0x04030403, 0x06030603, 0x06030603, 0x06030603, 0x06030603, // 0x1 
  0x0c020c02, 0x0c020c02, 0x0c020c02, 0x0c020c02, 0x0c020c02, 0x0c020c02, 0x0c020c02, 0x0c020c02, // 0x2 
  0x0e020e02, 0x0e020e02, 0x0e020e02, 0x0e020e02, 0x0e020e02, 0x0e020e02, 0x0e020e02, 0x0e020e02, // 0x3 
};
__place_k0_data__ unsigned int CBP_7_HW[64] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 0x0 
  0x12071107, 0x18071407, 0x22072107, 0x28072407, 0x3f063f06, 0x30063006, 0x09060906, 0x06060606, // 0x1 
  0x1f051f05, 0x1f051f05, 0x10051005, 0x10051005, 0x2f052f05, 0x2f052f05, 0x20052005, 0x20052005, // 0x2 
  0x07050705, 0x07050705, 0x0b050b05, 0x0b050b05, 0x0d050d05, 0x0d050d05, 0x0e050e05, 0x0e050e05, // 0x3 
  0x05050505, 0x05050505, 0x0a050a05, 0x0a050a05, 0x03050305, 0x03050305, 0x0c050c05, 0x0c050c05, // 0x4 
  0x01040104, 0x01040104, 0x01040104, 0x01040104, 0x02040204, 0x02040204, 0x02040204, 0x02040204, // 0x5 
  0x04040404, 0x04040404, 0x04040404, 0x04040404, 0x08040804, 0x08040804, 0x08040804, 0x08040804, // 0x6 
  0x0f030f03, 0x0f030f03, 0x0f030f03, 0x0f030f03, 0x0f030f03, 0x0f030f03, 0x0f030f03, 0x0f030f03, // 0x7 
};
__place_k0_data__ unsigned int CBP_9_HW[32] = {
  0x00090009, 0x36093909, 0x3b093709, 0x3e093d09, 0x17081708, 0x1b081b08, 0x1d081d08, 0x1e081e08, // 0x0 
  0x27082708, 0x2b082b08, 0x2d082d08, 0x2e082e08, 0x19081908, 0x16081608, 0x29082908, 0x26082608, // 0x1 
  0x35083508, 0x3a083a08, 0x33083308, 0x3c083c08, 0x15081508, 0x1a081a08, 0x13081308, 0x1c081c08, // 0x2 
  0x25082508, 0x2a082a08, 0x23082308, 0x2c082c08, 0x31083108, 0x32083208, 0x34083408, 0x38083808, // 0x3 
};
__place_k0_data__ unsigned int DC_lum_5_HW[8] = {
  0x12121212, 0x12121212, 0x22222222, 0x22222222, 0x03030303, 0x33333333, 0x43434343, 0x00655454, // 0x0 
};
__place_k0_data__ unsigned int DC_chrom_5_HW[8] = {
  0x02020202, 0x02020202, 0x12121212, 0x12121212, 0x22222222, 0x22222222, 0x33333333, 0x00554444, // 0x0 
};
__place_k0_data__ unsigned int DC_long_HW[8] = {
  0x65656565, 0x65656565, 0x65656565, 0x65656565, 0x76767676, 0x76767676, 0x87878787, 0xb9a99898, // 0x0 
};
__place_k0_data__ unsigned int DCT_B15_8_HW[128] = {
  0x00000000, 0x00000000, 0x41004100, 0x41004100, 0x08170817, 0x09170917, 0x07170717, 0x03270327, // 0x0 
  0x01760176, 0x01760176, 0x01660166, 0x01660166, 0x05160516, 0x05160516, 0x06160616, 0x06160616, // 0x1 
  0x0c180258, 0x01a801b8, 0x0d180e18, 0x02480428, 0x03150315, 0x03150315, 0x03150315, 0x03150315, // 0x2 
  0x02250225, 0x02250225, 0x02250225, 0x02250225, 0x04150415, 0x04150415, 0x04150415, 0x04150415, // 0x3 
  0x02130213, 0x02130213, 0x02130213, 0x02130213, 0x02130213, 0x02130213, 0x02130213, 0x02130213, // 0x4 
  0x02130213, 0x02130213, 0x02130213, 0x02130213, 0x02130213, 0x02130213, 0x02130213, 0x02130213, // 0x5 
  0x81048104, 0x81048104, 0x81048104, 0x81048104, 0x81048104, 0x81048104, 0x81048104, 0x81048104, // 0x6 
  0x01340134, 0x01340134, 0x01340134, 0x01340134, 0x01340134, 0x01340134, 0x01340134, 0x01340134, // 0x7 
  0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, // 0x8 
  0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, // 0x9 
  0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, // 0xa 
  0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, 0x01120112, // 0xb 
  0x01230123, 0x01230123, 0x01230123, 0x01230123, 0x01230123, 0x01230123, 0x01230123, 0x01230123, // 0xc 
  0x01230123, 0x01230123, 0x01230123, 0x01230123, 0x01230123, 0x01230123, 0x01230123, 0x01230123, // 0xd 
  0x01450145, 0x01450145, 0x01450145, 0x01450145, 0x01550155, 0x01550155, 0x01550155, 0x01550155, // 0xe 
  0x0a170a17, 0x02370237, 0x0b170b17, 0x01870187, 0x01970197, 0x01d801c8, 0x05280338, 0x01f801e8, // 0xf 
};
__place_k0_data__ unsigned int DCT_B15_10_HW[8] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x06290629, 0x0f190f19, 0x111a034a, 0x10191019, // 0x0 
};
__place_k0_data__ unsigned int DCT_13_HW[32] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 0x0 
  0x0a2d0b2d, 0x044d063d, 0x027d035d, 0x01fd026d, 0x01dd01ed, 0x1b1d01cd, 0x191d1a1d, 0x171d181d, // 0x1 
  0x01bc01bc, 0x092c092c, 0x053c053c, 0x01ac01ac, 0x034c034c, 0x082c082c, 0x161c161c, 0x151c151c, // 0x2 
  0x019c019c, 0x141c141c, 0x131c131c, 0x025c025c, 0x043c043c, 0x018c018c, 0x072c072c, 0x121c121c, // 0x3 
};
__place_k0_data__ unsigned int DCT_15_HW[32] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 0x0 
  0x127f128f, 0x125f126f, 0x123f124f, 0x121f122f, 0x20ef120f, 0x20cf20df, 0x20af20bf, 0x208f209f, // 0x1 
  0x11fe11fe, 0x11ee11ee, 0x11de11de, 0x11ce11ce, 0x11be11be, 0x11ae11ae, 0x119e119e, 0x118e118e, // 0x2 
  0x117e117e, 0x116e116e, 0x115e115e, 0x114e114e, 0x113e113e, 0x112e112e, 0x111e111e, 0x110e110e, // 0x3 
};
__place_k0_data__ unsigned int DCT_16_HW[16] = {
  0x81008100, 0x81008100, 0x81008100, 0x81008100, 0x81008100, 0x81008100, 0x81008100, 0x81008100, // 0x0 
  0x02110212, 0x020f0210, 0x11020703, 0x0f021002, 0x0d020e02, 0x20010c02, 0x1e011f01, 0x1c011d01, // 0x1 
};
__place_k0_data__ unsigned int DCT_B14AC_5_HW[16] = {
  0x00000000, 0x00000000, 0x01350000, 0x04150515, 0x01240124, 0x03140314, 0x02130213, 0x02130213, // 0x0 
  0x81028102, 0x81028102, 0x81028102, 0x81028102, 0x01120112, 0x01120112, 0x01120112, 0x01120112, // 0x1 
};
__place_k0_data__ unsigned int DCT_B14DC_5_HW[16] = {
  0x00000000, 0x00000000, 0x01350000, 0x04150515, 0x01240124, 0x03140314, 0x02130213, 0x02130213, // 0x0 
  0x01110111, 0x01110111, 0x01110111, 0x01110111, 0x01110111, 0x01110111, 0x01110111, 0x01110111, // 0x1 
};
__place_k0_data__ unsigned int DCT_B14_8_HW[20] = {
  0x00000000, 0x00000000, 0x41004100, 0x41004100, 0x03270327, 0x0a170a17, 0x01470147, 0x09170917, // 0x0 
  0x08160816, 0x08160816, 0x07160716, 0x07160716, 0x02260226, 0x02260226, 0x06160616, 0x06160616, // 0x1 
  0x01680e18, 0x0c180d18, 0x02380428, 0x0b180158, };
__place_k0_data__ unsigned int DCT_B14_10_HW[8] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x062a111a, 0x033a017a, 0x101a024a, 0x052a0f1a, // 0x0 
};
__place_k0_data__ unsigned int MV_4_HW[2] = {
  0x13132436, 0x02020202};
__place_k0_data__ unsigned int MV_10_HW[12] = {
  0x0a0a0a0a, 0x0a0a0a0a, 0x0a0a0a0a, 0xcadaeafa, 0x9999aaba, 0x79798989, 0x67676767, 0x67676767, // 0x0 
  0x57575757, 0x57575757, 0x47474747, 0x47474747, };
__place_k0_data__ unsigned int MB_I_HW[1] = {
  //0x01020101,
  0x00000546,
};
__place_k0_data__ int DMV_2_HW[1] = {
  0x0000e611,
};

/* ------------------ get slice info ----------------------------- */
#define CODING_TYPE_MSK       7
#define CODING_TYPE_SFT       0
#define FR_PRED_FR_DCT_MSK    1
#define FR_PRED_FR_DCT_SFT    3
#define PIC_TYPE_MSK          3
#define PIC_TYPE_SFT          4
#define CONCEAL_MV_MSK        1
#define CONCEAL_MV_SFT        6
#define INTRA_DC_PRE_MSK      7
#define INTRA_DC_PRE_SFT      7
#define INTRA_VLC_FORMAT_MSK  1
#define INTRA_VLC_FORMAT_SFT  10
#define MPEG1_MSK             1
#define MPEG1_SFT             11
#define TOP_FI_FIRST_MSK      1
#define TOP_FI_FIRST_SFT      12
#define QS_TYPE_MSK           1               
#define QS_TYPE_SFT           13
#define SEC_FLD_MSK           1
#define SEC_FLD_SFT           14
#define F_CODE_F0_MSK         0xf
#define F_CODE_F0_SFT         16
#define F_CODE_F1_MSK         0xf
#define F_CODE_F1_SFT         20
#define F_CODE_B0_MSK         0xf
#define F_CODE_B0_SFT         24
#define F_CODE_B1_MSK         0xf
#define F_CODE_B1_SFT         28

#define GET_SL_INFO(coding_type, fr_pred_fr_dct, pic_type, conceal_mv, intra_dc_pre, intra_vlc_format, mpeg1, \
		    top_fi_first, q_scale_type, sec_fld, f_code_f0, f_code_f1, f_code_b0, f_code_b1) \
  ({									\
	      ((coding_type & CODING_TYPE_MSK) << CODING_TYPE_SFT |	\
	       (fr_pred_fr_dct& FR_PRED_FR_DCT_MSK) << FR_PRED_FR_DCT_SFT | \
	       (pic_type& PIC_TYPE_MSK) << PIC_TYPE_SFT |		\
	       (conceal_mv& CONCEAL_MV_MSK) << CONCEAL_MV_SFT |		\
	       (intra_dc_pre& INTRA_DC_PRE_MSK) << INTRA_DC_PRE_SFT |	\
	       (intra_vlc_format& INTRA_VLC_FORMAT_MSK) << INTRA_VLC_FORMAT_SFT | \
	       (mpeg1& MPEG1_MSK) << MPEG1_SFT |			\
	       (top_fi_first& TOP_FI_FIRST_MSK) << TOP_FI_FIRST_SFT |	\
	       ((q_scale_type !=0)& QS_TYPE_MSK) << QS_TYPE_SFT |	\
	       (sec_fld& SEC_FLD_MSK) << SEC_FLD_SFT |			\
	       (f_code_f0& F_CODE_F0_MSK) << F_CODE_F0_SFT |		\
	       (f_code_f1& F_CODE_F1_MSK) << F_CODE_F1_SFT |		\
	       (f_code_b0& F_CODE_B0_MSK) << F_CODE_B0_SFT |		\
	       (f_code_b1& F_CODE_B1_MSK) << F_CODE_B1_SFT);		\
  })									

#define SCH1_DSA  (VPU_BASE | 0x00070)
#define SCH2_DSA  (VPU_BASE | 0x00074)
#define SCH3_DSA  (VPU_BASE | 0x00078)
#define SCH4_DSA  (VPU_BASE | 0x0007C)

#define I_TYPE 1
#define P_TYPE 2
#define B_TYPE 3
#define D_TYPE 4

#endif
