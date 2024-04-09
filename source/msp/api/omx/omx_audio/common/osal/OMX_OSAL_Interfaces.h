/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
/*
 * Copyright (c) 2005 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef OMX_OSAL_Interfaces_h
#define OMX_OSAL_Interfaces_h

#include <OMX_Types.h>
#include <OMX_Core.h>

/** OMX_OSAL_Interfaces.h
 *  Interface definitions of the OpenMax IL OS abstraction layer including memory, threading,
 *  mutex, event, time query and tracing functionality.
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    /**********************************************************************
     * MEMORY
     **********************************************************************/
    OMX_PTR OMX_OSAL_Malloc(OMX_IN OMX_U32 size);
    void OMX_OSAL_Free(OMX_IN OMX_PTR pData);
    OMX_PTR OMX_OSAL_Memset(OMX_IN OMX_PTR pDest, OMX_IN OMX_U32 cChar, OMX_IN OMX_U32 nCount);
    OMX_PTR OMX_OSAL_Memcpy(OMX_IN OMX_PTR pDest, OMX_IN OMX_PTR pSrc, OMX_IN OMX_U32 nCount);


    /**********************************************************************
     * EVENTS
     **********************************************************************/

#define INFINITE_WAIT 0xffffffff

    OMX_ERRORTYPE OMX_OSAL_EventCreate(OMX_OUT OMX_HANDLETYPE *phEvent); /** Create an event */
    OMX_ERRORTYPE OMX_OSAL_EventDestroy(OMX_IN OMX_HANDLETYPE hEvent);/** Destroy an event */
    OMX_ERRORTYPE OMX_OSAL_EventReset(OMX_IN OMX_HANDLETYPE hEvent);/** Reset an event */
    OMX_ERRORTYPE OMX_OSAL_EventSet(OMX_IN OMX_HANDLETYPE hEvent);/** Set an event */
    /** Wait at most mSec milliseconds for the specified event to be set.
     *  If mSec==INFINITE_WAIT wait indefinitely. If bTimedout is set the wait timed out before
     *  the event was signaled. */
    OMX_ERRORTYPE OMX_OSAL_EventWait(OMX_IN OMX_HANDLETYPE hEvent, OMX_IN OMX_U32 mSec, OMX_OUT OMX_BOOL *pbTimedOut);

    /***********************************************************************
     * TRACE
     *
     * Examples:
     *   OMX_OSAL_Trace(OMX_OSAL_TracePASSFAIL, "StateTransitionTest FAILED!\n");
     *   OMX_OSAL_Trace(OMX_OSAL_TraceCALLSEQUENCE, "FreeBuffer(");
     *   OMX_OSAL_Trace(OMX_OSAL_TracePARAMETERS, "\n\thComponent = 0x%08x", hComponent);
     *   OMX_OSAL_Trace(OMX_OSAL_TracePARAMETERS, "\n\tnPortIndex = 0x%08x", nPortIndex);
     *   OMX_OSAL_Trace(OMX_OSAL_TracePARAMETERS, "\n\tpBufer = 0x%08x", pBuffer);
     *   OMX_OSAL_Trace(OMX_OSAL_TraceCALLSEQUENCE, ")\n");
     *
     ***********************************************************************/

    extern OMX_HANDLETYPE g_OMX_CONF_hTraceMutex;

    /** Trace flags. */
#define OMX_OSAL_TRACE_INFO           0x0001
#define OMX_OSAL_TRACE_DEBUG          0x0002
#define OMX_OSAL_TRACE_WARNING        0x0004
#define OMX_OSAL_TRACE_ERROR          0x0006
#define OMX_OSAL_TRACE_FATAL          0x0008

    /** Output a trace message */
    OMX_ERRORTYPE OMX_OSAL_Trace(OMX_IN OMX_U32 nTraceFlags, OMX_IN char *format, ...);

    OMX_ERRORTYPE OMX_OSAL_ProcessCommandsFromFile(OMX_STRING sFileName);
    OMX_ERRORTYPE OMX_OSAL_ProcessCommandsFromPrompt();

    /** Open logfile. All enabled tracing will be sent to the file (in addition
     *  to the display). */
    OMX_ERRORTYPE OMX_OSAL_OpenLogfile(OMX_IN OMX_STRING sFilename);
    /** Close logfile.*/
    OMX_ERRORTYPE OMX_OSAL_CloseLogfile();

    /**********************************************************************
     * INPUT FILE MAPPING
     **********************************************************************/

    /** Open the input file associated with the given port index.*/
    OMX_ERRORTYPE OMX_OSAL_OpenInputFile(OMX_IN OMX_U32 nPortIndex);

    /** Read the given number bytes from the input file associated with the given port index.
     *  Return the actual number of bytes read. */
    OMX_U32 OMX_OSAL_ReadFromInputFile(OMX_OUT OMX_PTR pData, OMX_IN OMX_U32 nBytes, OMX_IN OMX_U32 nPortIndex);

    /** Close the input file associated with the given port index.*/
    OMX_ERRORTYPE OMX_OSAL_CloseInputFile(OMX_IN OMX_U32 nPortIndex);

    /**********************************************************************
     * OUTPUT FILE MAPPING
     **********************************************************************/

    /** Open the output file associated with the given port index.*/
    OMX_ERRORTYPE OMX_OSAL_OpenOutputFile(OMX_IN OMX_U32 nPortIndex);

    /** Write the given bytes to the output file associated with the given port index.
     *  Return the actual number of bytes written. */
    OMX_U32 OMX_OSAL_WriteToOutputFile(OMX_OUT OMX_PTR pData, OMX_IN OMX_U32 nBytes, OMX_IN OMX_U32 nPortIndex);

    /** Close the output file associated with the given port index.*/
    OMX_ERRORTYPE OMX_OSAL_CloseOutputFile(OMX_IN OMX_U32 nPortIndex);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/* File EOF */
