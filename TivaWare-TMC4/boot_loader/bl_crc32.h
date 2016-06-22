//*****************************************************************************
//
// bl_crc32.h - Public header for the boot loader CRC32 functions.
//
// Copyright (c) 2013-2015 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.2.111 of the Tiva Firmware Development Package.
//
//*****************************************************************************

#ifndef __BL_CRC32_H__
#define __BL_CRC32_H__

//*****************************************************************************
//
// Return codes generated by CheckImageCRC32().
//
//*****************************************************************************
#define CHECK_CRC_OK            0
#define CHECK_CRC_NO_HEADER     1
#define CHECK_CRC_NO_LENGTH     2
#define CHECK_CRC_BAD_LENGTH    3
#define CHECK_CRC_BAD_CRC       4

//*****************************************************************************
//
// Exported function prototypes.
//
//*****************************************************************************
extern void InitCRC32Table(void);
extern uint32_t CheckImageCRC32(uint32_t *pui32Image);
extern uint32_t CalculateCRC32(uint8_t *pui8Data, uint32_t ui32Length,
                               uint32_t ui32CRC);

#endif
