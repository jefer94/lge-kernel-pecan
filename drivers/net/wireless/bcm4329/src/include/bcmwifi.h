/*
 * Misc utility routines for WL and Apps
 * This header file housing the define and function prototype use by
 * both the wl driver, tools & Apps.
 *
 * Copyright (C) 1999-2010, Broadcom Corporation
 * 
 *         Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2 (the "GPL"),
 * available at http://www.broadcom.com/licenses/GPLv2.php, with the
 * following added to such license:
 * 
 *      As a special exception, the copyright holders of this software give you
 * permission to link this software with independent modules, and to copy and
 * distribute the resulting executable under terms of your choice, provided that
 * you also meet, for each linked independent module, the terms and conditions of
 * the license of that module.  An independent module is a module which is not
 * derived from this software.  The special exception does not apply to any
 * modifications of the software.
 * 
 *      Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a license
 * other than the GPL, without Broadcom's express prior written consent.
 * $Id: bcmwifi.h,v 1.15.132.4.16.2 2010/06/07 21:32:42 Exp $
 */


#ifndef	_bcmwifi_h_
#define	_bcmwifi_h_



typedef uint16 chanspec_t;


#define CH_UPPER_SB			0x01
#define CH_LOWER_SB			0x02
#define CH_EWA_VALID			0x04
#define CH_20MHZ_APART			4
#define CH_10MHZ_APART			2
#define CH_5MHZ_APART			1
#define CH_MAX_2G_CHANNEL		14	
#define WLC_MAX_2G_CHANNEL		CH_MAX_2G_CHANNEL 
#define	MAXCHANNEL		224	

#define WL_CHANSPEC_CHAN_MASK		0x00ff
#define WL_CHANSPEC_CHAN_SHIFT		0

#define WL_CHANSPEC_CTL_SB_MASK		0x0300
#define WL_CHANSPEC_CTL_SB_SHIFT	     8
#define WL_CHANSPEC_CTL_SB_LOWER	0x0100
#define WL_CHANSPEC_CTL_SB_UPPER	0x0200
#define WL_CHANSPEC_CTL_SB_NONE		0x0300

#define WL_CHANSPEC_BW_MASK		0x0C00
#define WL_CHANSPEC_BW_SHIFT		    10
#define WL_CHANSPEC_BW_10		0x0400
#define WL_CHANSPEC_BW_20		0x0800
#define WL_CHANSPEC_BW_40		0x0C00

#define WL_CHANSPEC_BAND_MASK		0xf000
#define WL_CHANSPEC_BAND_SHIFT		12
#define WL_CHANSPEC_BAND_5G		0x1000
#define WL_CHANSPEC_BAND_2G		0x2000
#define INVCHANSPEC			255


#define WF_CHAN_FACTOR_2_4_G		4814	
#define WF_CHAN_FACTOR_5_G		10000	
#define WF_CHAN_FACTOR_4_G		8000	


#define LOWER_20_SB(channel)	((channel > CH_10MHZ_APART) ? (channel - CH_10MHZ_APART) : 0)
#define UPPER_20_SB(channel)	((channel < (MAXCHANNEL - CH_10MHZ_APART)) ? \
				(channel + CH_10MHZ_APART) : 0)
#define CHSPEC_WLCBANDUNIT(chspec)	(CHSPEC_IS5G(chspec) ? BAND_5G_INDEX : BAND_2G_INDEX)
#define CH20MHZ_CHSPEC(channel)	(chanspec_t)((chanspec_t)(channel) | WL_CHANSPEC_BW_20 | \
				WL_CHANSPEC_CTL_SB_NONE | (((channel) <= CH_MAX_2G_CHANNEL) ? \
				WL_CHANSPEC_BAND_2G : WL_CHANSPEC_BAND_5G))
#define NEXT_20MHZ_CHAN(channel)	((channel < (MAXCHANNEL - CH_20MHZ_APART)) ? \
					(channel + CH_20MHZ_APART) : 0)
#define CH40MHZ_CHSPEC(channel, ctlsb)	(chanspec_t) \
					((channel) | (ctlsb) | WL_CHANSPEC_BW_40 | \
					((channel) <= CH_MAX_2G_CHANNEL ? WL_CHANSPEC_BAND_2G : \
					WL_CHANSPEC_BAND_5G))
#define CHSPEC_CHANNEL(chspec)	((uint8)((chspec) & WL_CHANSPEC_CHAN_MASK))
#define CHSPEC_BAND(chspec)	((chspec) & WL_CHANSPEC_BAND_MASK)

#define CHSPEC_CTL_SB(chspec) (chspec & WL_CHANSPEC_CTL_SB_MASK)
#define CHSPEC_BW(chspec)     (chspec & WL_CHANSPEC_BW_MASK)

#ifdef WL20MHZ_ONLY

#define CHSPEC_IS10(chspec)	0
#define CHSPEC_IS20(chspec)	1
#ifndef CHSPEC_IS40
#define CHSPEC_IS40(chspec)	0
#endif

#else 

#define CHSPEC_IS10(chspec)	((chspec & WL_CHANSPEC_BW_MASK) == WL_CHANSPEC_BW_10)
#define CHSPEC_IS20(chspec)	((chspec & WL_CHANSPEC_BW_MASK) == WL_CHANSPEC_BW_20)
#ifndef CHSPEC_IS40
#define CHSPEC_IS40(chspec)	(((chspec) & WL_CHANSPEC_BW_MASK) == WL_CHANSPEC_BW_40)
#endif

#endif 


#if defined(BAND5G)
#if defined(BAND2G)
#define CHSPEC_IS5G(chspec)	((chspec & WL_CHANSPEC_BAND_MASK) == WL_CHANSPEC_BAND_5G)
#define CHSPEC_IS2G(chspec)	((chspec & WL_CHANSPEC_BAND_MASK) == WL_CHANSPEC_BAND_2G)
#else
#define CHSPEC_IS5G(chspec)	1
#define CHSPEC_IS2G(chspec)	0
#endif 
#else
#define CHSPEC_IS5G(chspec)	0
#define CHSPEC_IS2G(chspec)	1
#endif 


#define CHSPEC_SB_NONE(chspec)	((chspec & WL_CHANSPEC_CTL_SB_MASK) == WL_CHANSPEC_CTL_SB_NONE)
#define CHSPEC_SB_UPPER(chspec)	((chspec & WL_CHANSPEC_CTL_SB_MASK) == WL_CHANSPEC_CTL_SB_UPPER)
#define CHSPEC_SB_LOWER(chspec)	((chspec & WL_CHANSPEC_CTL_SB_MASK) == WL_CHANSPEC_CTL_SB_LOWER)
#define CHSPEC_CTL_CHAN(chspec)  ((CHSPEC_SB_LOWER(chspec)) ? \
				  (LOWER_20_SB(((chspec) & WL_CHANSPEC_CHAN_MASK))) : \
				  (UPPER_20_SB(((chspec) & WL_CHANSPEC_CHAN_MASK))))
#define CHSPEC2WLC_BAND(chspec) (CHSPEC_IS5G((chspec))? WLC_BAND_5G: WLC_BAND_2G)

#define CHANSPEC_STR_LEN    8


#define WLC_MAXRATE	108	
#define WLC_RATE_1M	2	
#define WLC_RATE_2M	4	
#define WLC_RATE_5M5	11	
#define WLC_RATE_11M	22	
#define WLC_RATE_6M	12	
#define WLC_RATE_9M	18	
#define WLC_RATE_12M	24	
#define WLC_RATE_18M	36	
#define WLC_RATE_24M	48	
#define WLC_RATE_36M	72	
#define WLC_RATE_48M	96	
#define WLC_RATE_54M	108	

#define WLC_2G_25MHZ_OFFSET		5	


extern char * wf_chspec_ntoa(chanspec_t chspec, char *buf);


extern chanspec_t wf_chspec_aton(char *a);


extern chanspec_t wf_chspec_ctlchspec(chanspec_t chspec);


extern int wf_mhz2channel(uint freq, uint start_factor);


extern int wf_channel2mhz(uint channel, uint start_factor);

#endif	
