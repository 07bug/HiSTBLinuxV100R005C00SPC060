/***********************************************************************************/
/*  Copyright (c) 2002-2006, Silicon Image, Inc.  All rights reserved.             */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1060 East Arques Avenue, Sunnyvale, California 94085                           */
/***********************************************************************************/
typedef enum tagTCLK_SEL
{ 
    x0_5 = 0x00, 
    x1 = 0x20, 
    x2 = 0x40, 
    x4 = 0x60 
} TCLK_SEL; // Move this into SiITXAPIDefs.h when TCLK_SEL is part of the API.

typedef enum tagRANGE 
{ 
    blue, 
    yellow, 
    orange 
}RANGE;

#define TMDS_SETUP_FAILED		1
#define TMDS_SETUP_PASSED		0

#define CLR_BITS_7_6_5			0x3F
#define CLR_BITS_5_4_3			0xC7
#define BIT_DITHER_EN			0x20

HI_U8 ConfigTXVideoMode(HI_U8 , HI_U8 );

void siiSetVideoPath ( HI_U8, HI_U8 * );
void siiGetVideoPath ( HI_U8 * );

