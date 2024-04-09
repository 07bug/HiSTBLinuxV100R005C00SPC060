/*************************************************************************************************************/
/*                                  Silicon Laboratories                                                     */
/*                                  Broadcast Video Group                                                    */
/*                     Layer 0      Communication Functions                                                  */
/*-----------------------------------------------------------------------------------------------------------*/
/*   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF                           */
/*     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING                                */
/*     TO THIS SOURCE FILE.                                                                                  */
/*  IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,                             */
/*    PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all i2c functions to communicate with i2c components                          */
/*     All functions are declared in Silabs_L0_API.h                                                         */
/*************************************************************************************************************/
/* Change log:

 As from V5.0.5:
  Changing some char* to const char* to avoid compilation warnings on some compilers
  In traceToBuffer:   using strncat instead of strcat
  In SiTraceFunction: using strncpy instead of strcpy, using vsnprintf instead of vsprintf

 As from V5.0.4:
  <correction>[multiple/memory] Removing ucBuffer from global scope. This may create issues for setups with multiple frontends.
    ucBuffer is now locally declared in L0_WriteBytes and L0_WriteString (with a size reduced to 100 bytes instead of the previous 1000).

 As from V5.0.3:
  <new_feature>[TS/slave] Update to CypressUSB.dll to V15.49 to enable 'TS SLAVE' feature (using the TS output as with a SoC)

 As from V5.0.2:
  <compatibility>[Linux/adapter_nr] In L0_SetAddress: setting adapter_nr as add[15:8] (only if LINUX_I2C_Capability)
    When using adapter_nr, provide it from L3 together with the i2c address:
      adapter_nr  = add[15:8]
      i2c address = add[ 7:0]

 As from V5.0.1:
  <compatibility>[Linux/Time] In system_time: now compatible with standard Linux with USB support (using FX2LP)
    as well as with ST_SDK2 in kernelspace.

 As from V5.0.0:
  <compatibility>[Linux/ST_SDK2] Code compatible with ST SDK2-20.2 and above.
    This requires declaring LINUX_ST_SDK2_I2C

 As from V4.0.2:
  <compatibility>[Linux/gettimeofday] Code compiling under Linux with Cypress EZUSB compatibility.
   (requires NO_WIN32 / LINUX / USB_Capability flags and compiling with libCypressUSB.so)
    When connected in LINUX_USB mode, L0 traces will show 'LUSB'.

 As from V4.0.0:
  Adding L0_Cypress_VendorCmd and L0_Cypress_VendorRead (for Cypress chip only, when USB_Capability is defined)
  <compatibility>[Tizen/int] explicitly declaring all function parameters are 'signed int' instead fo 'int'.
    This is because Tizen interpret 'int' as 'unsigned int'
    All other compilers   interpret 'int' as 'signed   int', so this change doesn't affect other compilers.

 As from V3.5.1:
  <improvement> [Code checker/warnings] In L0_WriteString: removing unused pucBuffer

 As from V3.5.0:
  <improvement>In L0_ReadRawBytes/L0_WriteRawBytes: adding semaphoreName and COM_ownership in rawI2C struct to avoid an issue
    when the interface is claimed a second time
  <improvement>In L0_ReadRegister/L0_WriteRegister: checking input parameter to avoid having iNbBytes = 0.
   NB: This would only occur if improper parameters are sent to the functions.
   An error message is now generated to inform the user that the input parameters are incorrect.

 As from V3.4.9:
  <correction/system_wait> In system_wait: really waiting for the expected amount of time (regression introduced in V3.4.6).

 As from V3.4.8:
  <new_feature>[SiTRACES/<porting>] In Silabs_L0_API.h: defining SiLOGS to SiTRACE when traces are defined and printf otherwise.
   This is to be able to get minimal traces even with release versions (i.e. compiled without SITRACES)
  <improvement>[tag] Consistency in tagging between memory/stdout/file (the tag was duplicated in file)
  <improvement>[Compatibility/traces] In L0_StoreTag: returning directly when SiTRACES is not defined.

 As from V3.4.7:
  <porting>[Windows] In system_time: replacing 1000/CLOCKS_PER_SEC by 1/1 on Windows, since this provides a much longer
    time before the returned value folds and returns a negative value.

 As from V3.4.6:
  <improvement>[Compatibility/Strings] Using STRING_APPEND_SAFE when filling SiTRACE strings
  <new feature> [tag/level] In traceToFile: Adding support for tags and levels

 As from 3.4.5:
  <improvement>[Compatibility/Strings] Adding STRING_APPEND_SAFE in header to replace snprintf

 As from 3.4.4:
  <new feature> [tag/level] Adding support for tag and level
    This allows adding a tag at the beginning of trace lines to identify the frontend and DTV/TER/SAT, what is very
     useful to use traces generated by multiple frontend applications.
    In addition to this, it is now possible to display the 'level' as well, as well as select which level is
     visible in traces (level is from 0 to 32, commonly 0 to 3 in our console code).
     Adding SiTraceLevelEnabled    (int level): to check whether a given trace level is enabled
     Adding SiTraceLevel           (int level, unsigned char on_off): to set the 'enable' flag for the trace level
    Redefinition of SiTraceFunction to have it take the level and tag as well.
     Thanks to new macros, the changes in the other layers are minimal.
     Use SiTRACE_X to use the 'same' traces as before (defaulting to level 32, tag "")
  <improvement> [SiTRACE config] In SiTraceConfiguration: adding check on number of arguments for configuration strings

 As from 3.4.3:
  <new_feature> [SPI] Adding SPI control functions (initially only implemented for the Cypress Fx2lp chip):
     L0_EnableSPI:  enabling SPI port selected pins
     L0_LoadSPI:    loading bytes over SPI
     L0_DisableSPI: disabling SPI pins

 As from 3.4.2:
  <improvement>In L0_WriteString: removed one dead code line

 As from 3.4.1:
  Moving buffer allocation inside functions using them, to be thread-safe.
  NB: There is one remaining area which is not thread-safe in the functions used by the SiERROR and CHECK_FOR_ERRORS macros.
      If this is an issue, redefine the SiERROR and CHECK_FOR_ERRORS macros inside Silabs_L0_API.h to empty strings

 As from 3.3.9:
  In strcmp_nocase_n: using "%s" in sprintf (greater Linux compatibility)

 As from 3.3.8:
  Declaring parameter strings as 'const char*' instead of 'char*' to limit -Wwrite-strings warnings

  As from 3.3.7:
  Adding L0_SlowI2C and L0_FastI2C for easier control of the i2c speed from the above layers

 As from 3.3.6:
  Improved porting comments in L0_ReadBytes

 As from 3.3.5:
  casting calls to strlen as (int) for greater compatibility with VisualStudio

 As from 3.3.4:
  Added help for 'resume' / "suspend'

 As from 3.3.3:
  Adding 'suspend' / 'resume' in traces to keep control of the traces destination at application level.
  This is required to avoid having the traces routed to file after each FW download with 'command mode' parts.

 As from 3.3.2:
 Correction on last character when changing traces file name
 Correction in traces file name management
 *************************************************************************************************************/
 /* TAG V5.0.4 */

#include <linux/delay.h>
#include <linux/semaphore.h>

#include "linux/kernel.h"

#include <hi_debug.h>
#include "hi_type.h"
#include "drv_i2c_ext.h"

#include "drv_tuner_ext.h"
#include "drv_demod.h"
#include "drv_tuner_ioctl.h"
#include "hi_drv_mem.h"
#include "hi_drv_i2c.h"
#include "hi_drv_gpioi2c.h"

#include "Silabs_L0_API.h"
#include "hi3137.h"

#define   SiLEVEL          0
#include "Silabs_L0_API.h"

#ifdef    NO_WIN32
  /* NO_WIN32: includes for non-Windows platform */
  #ifdef    LINUX_USB_Capability
    #include "CyAPIUser.h"
    typedef enum NN6_RET {
      RET_OK = 0,
      RET_KO = 2
    } NN6_RET;
    unsigned char  cypress_checks_done    = 0;
  #endif /* LINUX_USB_Capability */
#endif /* End of includes for non-Windows platform */
#ifndef   NO_WIN32
  /* includes for Windows */
  #ifdef    USB_Capability
    #include "CyAPIUser.h"
    typedef enum NN6_RET {
      RET_OK = 0,
      RET_KO = 2
    } NN6_RET;
    unsigned char  cypress_checks_done    = 0;
    double mydval;
  #endif /* USB_Capability */
#endif /* End of includes for Windows */

L0_Context  rawI2C_context;
L0_Context *rawI2C;

#define  SIMULATOR_SCOPE 0xffff
int      Byte[SIMULATOR_SCOPE];
char           L0_error_buffer_0[ERROR_MESSAGE_MAX_LENGH];
char           L0_error_buffer_1[ERROR_MESSAGE_MAX_LENGH];

char          *stored_error_message;
char          *L0_error_message;

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef    SiTRACES
#define   SiTRACES_BUFFER_LENGTH  100000
#define   SiTRACES_NAMESIZE           30
#define   SiTRACES_FUNCTION_NAMESIZE  30
#if       SiTRACES_FEATURES == SiTRACES_FULL
    #define SiTRACES_DEFAULT_FILE "SiLabs_Traces.txt"
#endif /* SiTRACES_FEATURES */

typedef enum TYPE_OF_OUTPUT {
    TRACE_NONE = 0,
    TRACE_STDOUT,
    TRACE_EXTERN_FILE,
    TRACE_MEMORY
}TYPE_OF_OUTPUT;

TYPE_OF_OUTPUT trace_output_type;

unsigned char trace_init_done        = 0;
unsigned char trace_suspend          = 0;
unsigned char trace_skip_info        = 0;
unsigned char trace_config_lines     = 0;
unsigned char trace_config_files     = 0;
unsigned char trace_config_functions = 0;
unsigned char trace_config_rename    = 0;
unsigned char trace_config_time      = 0;
unsigned char trace_config_tags      = 1;
unsigned char trace_config_level     = 1;
unsigned char trace_lost_traces      = 0;
unsigned char trace_config_verbose   = 0;
int           trace_linenumber       = 0;
int           trace_current_index    = 0;
int           trace_count            = 0;
int           carriage_return        = 1;
int           trace_levels           = 0xffffffff;

char trace_buffer[SiTRACES_BUFFER_LENGTH];
char trace_stockInt[25];
char trace_timer[50];
char trace_elapsed_time[20];
char trace_source_file[100];
char trace_file_name[SiTRACES_NAMESIZE+1];
char trace_source_function[SiTRACES_FUNCTION_NAMESIZE+1];
char trace_tag[SILABS_TAG_SIZE];
char trace_level_text[SILABS_TAG_SIZE];
char trace_message[1000];
char trace_L0_message[1000];

/************************************************************************************************************************
  SiTraceLevelEnabled function
  Use:        SiTRACES level trace activation/de-activation check function.
              It is used to know if tracing is enabled/disabled for the selected level.
  Parameters:  level, the selected level
  Returns:    the flag for the selected level
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
int   SiTraceLevelEnabled    (int level) {
  return (trace_levels>>level)&0x1;
}
/************************************************************************************************************************
  SiTraceLevel function
  Use:        SiTRACES level trace activation/de-activation function.
              It is used to enable/disable traces for the selected level.
  Parameters:  level, the selected level to activate/de-activate
               on_off: a flag indicating if the selected level traces are visible (1) or hidden (0)
  Returns:    the bitfield representing the currently active levels
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
int   SiTraceLevel           (int level, unsigned char on_off) {
  if (on_off) {
    if (SiTraceLevelEnabled(level)==0) {
    SiTRACE_X("Enabling  traces for level %2d\n",level);
    trace_levels = trace_levels + (1<<level);
    }
  } else {
    if (SiTraceLevelEnabled(level)==1) {
      SiTRACE_X("Disabling traces for level %2d\n",level);
      trace_levels = trace_levels - (1<<level);
    }
  }
  return trace_levels;
}
/************************************************************************************************************************
  SiTraceDefaultConfiguration function
  Use:        SiTRACES initialization function.
              It is called on the first call to L0_Init (only once).
              It defines the default output and inserts date and time in the default file.
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
void  SiTraceDefaultConfiguration(void) {
#if       SiTRACES_FEATURES == SiTRACES_FULL
    FILE *file;
    time_t rawtime;
    struct tm * timeinfo;
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */

    if (trace_init_done) return;
    trace_output_type=TRACE_STDOUT;
    trace_init_done=1;
#if       SiTRACES_FEATURES == SiTRACES_FULL
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime (trace_timer,50,"%A %B %d   %I:%M%p   %Y",timeinfo);
    sprintf(trace_tag      , "%s", "tag");
    sprintf(trace_file_name, "%s", SiTRACES_DEFAULT_FILE);
    file = fopen(trace_file_name,"w");
    if (file != NULL) {
      fprintf(file,"            SiTraceFunction log created on %s\n",trace_timer);
      fclose(file);
    } else {
      printf("%s file access not possible.\n",trace_file_name);
    }
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */
}
/************************************************************************************************************************
  traceHelp function
  Use:        SiTRACES configuration help function.
  Returns:    the help menu text
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
char* traceHelp              (void) {
  return (char *)"\
-------------------------------------------------------------------------------------------\n\
 Possible traces commands:\n\
-------------------------------------------------------------------------------------------\n\
traces  -output   <memory/stdout/file/none>. select the trace destination (don't use 'stdout' in wish)\n\
traces  -file     <on/off> . . . . . . . . . select file name   mode (adding C source file name)\n\
traces  -line     <on/off> . . . . . . . . . select line number mode (adding C source file line number)\n\
traces  -function <on/off> . . . . . . . . . select function    mode (adding C source file function name)\n\
traces  -time     <on/off> . . . . . . . . . select time tag    mode (adding elapsed time as hh:mm:ss.ms)\n\
traces  -tag      <on/off> . . . . . . . . . select tag         mode (adding user-defined tag, often with frontend index)\n\
traces  -level    <on/off> . . . . . . . . . select level       mode (adding trace level indication)s\n\
traces  -name     <file_name>. . . . . . . . select traces file name (default 'SiLabs_traces.txt' and '' gives the current file used)\n\
traces  -verbose  <on/off> . . . . . . . . . select verbose mode (traces in console even if '-output' not 'stdout')\n\
traces  show . . . . . . . . . . . . . . . . display buffered traces in console (not visible in wish)\n\
traces  get. . . . . . . . . . . . . . . . . display buffered traces (visible in wish)\n\
traces  count. . . . . . . . . . . . . . . . display number of traces since start\n\
traces  suspend. . . . . . . . . . . . . . . suspend tracing until 'resume'\n\
traces  resume . . . . . . . . . . . . . . . resume  tracing after 'suspend'\n\
traces  lost . . . . . . . . . . . . . . . . display number of traces lost since start\n\
traces  save . . . . . . . . . . . . . . . . save    buffered traces to file\n\
traces  flush. . . . . . . . . . . . . . . . erase   buffered traces\n\
traces  erase. . . . . . . . . . . . . . . . erase   file content\n\
traces  status . . . . . . . . . . . . . . . display the current traces flags\n\
traces  help . . . . . . . . . . . . . . . . display this help\n\
";
}
/************************************************************************************************************************
  traceFlushBuffer function
  Use:        SiTRACES buffer erasing function.
              It is called to empty the buffer.
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
  Parameter:  buffer  the trace buffer content.
  Returns:    void
************************************************************************************************************************/
void  traceFlushBuffer       (char *buffer) {
  trace_current_index=0;
  trace_lost_traces=0;
  buffer[0]=0;
}
/************************************************************************************************************************
  traceElapsedTime function
  Use:        SiTRACES time formatting function.
              It allows the user to know when the trace has been treated.
              It is used to insert the time before the trace when -time 'on'.
  Returns:    text containing the execution time in HH:MM:SS.ms format.
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
char *traceElapsedTime       (void) {
    int timeElapsed, ms, sec, min, hours;
    timeElapsed = system_time();
    ms=timeElapsed%1000;
    timeElapsed=timeElapsed/1000;
    sec=timeElapsed%60;
    timeElapsed=timeElapsed/60;
    min=timeElapsed%60;
    timeElapsed=timeElapsed/60;
    hours=timeElapsed%60;
    sprintf(trace_elapsed_time,"%02d:%02d:%02d.%03d ",hours,min,sec,ms);
    return trace_elapsed_time;
}
/************************************************************************************************************************
  traceToStdout function
  Use:        SiTRACES stdout display function.
              It displays the current trace in the command window.
              It adds file name, line number,function name and time if selected.
  Parameter:  trace
  Returns:    void
************************************************************************************************************************/
void  traceToStdout          (char* trace) {
  char stdout_string[1000];
  sprintf(stdout_string, "%s", "");
    if (!trace_skip_info) {
        if (trace_config_files    ) { STRING_APPEND_SAFE(stdout_string, 1000, "%-40s ", trace_source_file    ); }
        if (trace_config_lines    ) { STRING_APPEND_SAFE(stdout_string, 1000, "%5d "  , trace_linenumber     ); }
        if (trace_config_functions) { STRING_APPEND_SAFE(stdout_string, 1000, "%-30s ", trace_source_function); }
    }
        if (trace_config_time     ) { STRING_APPEND_SAFE(stdout_string, 1000, "%s ",    traceElapsedTime()   ); }
    if (carriage_return)      {
        if (trace_config_tags     ) { STRING_APPEND_SAFE(stdout_string, 1000, "%s ",     trace_tag           ); }
        if (trace_config_level    ) { STRING_APPEND_SAFE(stdout_string, 1000, "%s  ",    trace_level_text    ); }
    }
        if (trace[strlen(trace)-1]== '\n') {carriage_return = 1;} else {carriage_return = 0;}
                                      STRING_APPEND_SAFE(stdout_string, 1000, "%s",     trace);
                                      CUSTOM_PRINTF("%s",stdout_string);
}
#if       SiTRACES_FEATURES == SiTRACES_FULL
/************************************************************************************************************************
  traceToFile function
  Use:        SiTRACES file saving function.
              It writes the current trace in an extern file.
              It adds file name, line number,function name and time if selected.
  Parameter:  trace
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
void  traceToFile            (char* trace) {
    FILE *file;
    file = fopen(trace_file_name,"a+");

    if (file != NULL) {
      if (!trace_skip_info) {
          if (trace_config_files    ) { fprintf(file,"%-40s " , trace_source_file    ); }
          if (trace_config_lines    ) { fprintf(file,"%5d "   , trace_linenumber     ); }
          if (trace_config_functions) { fprintf(file, "%-30s ", trace_source_function); }
      }
          if (trace_config_time     ) { fprintf(file,"%s "    , traceElapsedTime()   ); }
      if (carriage_return)      {
          if (trace_config_tags     ) { fprintf(file, "%s "   , trace_tag           ); }
          if (trace_config_level    ) { fprintf(file, "%s  "  , trace_level_text    ); }
      }
      if (trace[strlen(trace)-1]== '\n') {carriage_return = 1;} else {carriage_return = 0;}
      fprintf(file,"%s", trace);
      fclose(file);
    } else {
      trace_output_type=TRACE_MEMORY;
      printf("writing in %s failed, routing traces to memory.", trace_file_name);
    }
}
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */
/************************************************************************************************************************
  traceToBuffer function
  Use:        SiTRACES buffer saving function.
              It adds file name, line number,function name and time if selected.
  Comment:    The trace buffer length is limited (it is set by SiTRACES_BUFFER_LENGTH).
              If the buffer is full, the oldest traces will be lost to write the new trace.
  Parameter:  trace
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
void  traceToBuffer          (char* trace) {
    char tmp[1000];
    int new_string_length, lenTmp, lenTrace;

    new_string_length=0;

    sprintf(tmp,"%s","");
    if (((trace_config_files || trace_config_lines) && (!trace_skip_info)) ||  trace_config_time) {
        if(trace_buffer[strlen(trace_buffer)-1] != '\n') {strncat(tmp, "\n", 1000-strlen(tmp));}
    }
    if (!trace_skip_info) {
        if (trace_config_files    ) { STRING_APPEND_SAFE(tmp, 1000, "%-40s ", trace_source_file    ); }
        if (trace_config_lines    ) { STRING_APPEND_SAFE(tmp, 1000, "%5d "  , trace_linenumber     ); }
        if (trace_config_functions) { STRING_APPEND_SAFE(tmp, 1000, "%-30s ", trace_source_function); }
        }
    if (  trace_config_time       ) { STRING_APPEND_SAFE(tmp, 1000, "%s "    , traceElapsedTime()  ); }
    if (carriage_return)      {
      if (  trace_config_tags     ) { STRING_APPEND_SAFE(tmp, 1000, "%s "    , trace_tag           ); }
      if (  trace_config_level    ) { STRING_APPEND_SAFE(tmp, 1000, "%s "    , trace_level_text    ); }
    }
      if (trace[strlen(trace)-1]== '\n') {carriage_return = 1;} else {carriage_return = 0;}

    lenTmp   = (int)strlen(tmp);
    lenTrace = (int)strlen(trace);
    new_string_length = lenTmp + lenTrace;

    if( (trace_current_index+new_string_length) > SiTRACES_BUFFER_LENGTH) {
        if( (trace_current_index+lenTmp) > SiTRACES_BUFFER_LENGTH) { /* tmp is cut */
            /* Copy the beginning of the TMP string at the end of the buffer */
            strncat(trace_buffer+trace_current_index ,tmp, SiTRACES_BUFFER_LENGTH-trace_current_index);

            /* Copy the end of the TMP string at the beginning of the buffer */
            sprintf(trace_buffer, "%s",               tmp+SiTRACES_BUFFER_LENGTH-trace_current_index);
            trace_current_index = lenTmp-(SiTRACES_BUFFER_LENGTH-trace_current_index);

            /* Copy the whole TRACE string after TMP*/
            strncat(trace_buffer+trace_current_index, trace , SiTRACES_BUFFER_LENGTH-trace_current_index);
            trace_current_index += lenTrace;
        }
        else { /* trace is cut */
            /* Copy the whole TRACE string at the end of the buffer*/
            strncat(trace_buffer+trace_current_index,tmp , SiTRACES_BUFFER_LENGTH-trace_current_index);
            trace_current_index += lenTmp;

            /* Copy the beginning of the TRACE string after TMP */
            strncat(trace_buffer+trace_current_index ,trace, SiTRACES_BUFFER_LENGTH-trace_current_index);

            /* Copy the end of the TRACE string at the beginning of the buffer */
            sprintf(trace_buffer, "%s",               trace+SiTRACES_BUFFER_LENGTH-trace_current_index);
            trace_current_index = lenTrace-(SiTRACES_BUFFER_LENGTH-trace_current_index);
        }
        trace_lost_traces++;
    }
    else {
        strncat(trace_buffer+trace_current_index, tmp, SiTRACES_BUFFER_LENGTH-trace_current_index);
        trace_current_index += lenTmp;
        strncat(trace_buffer+trace_current_index, trace, SiTRACES_BUFFER_LENGTH-trace_current_index);
        trace_current_index += lenTrace;
        if (trace_lost_traces) trace_lost_traces++;
    }
}
/************************************************************************************************************************
  traceToDestination function
  Use:        switch the trace in the selected output mode.
  Comment:    In verbose mode, the trace is always displayed in stdout.
  Parameter:  trace, the trace string
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
void  traceToDestination     (char* trace) {
    int last;
    if (trace_suspend) {return;}
    /* If trace is a single CrLf, do not print the file/line/function info           */
    if (strcmp(trace,"\n")==0) {trace_skip_info = 1;}
    /* If file/line/function info printed, make sure there is a CrLf after each line */
    if (trace_config_files + trace_config_lines + trace_config_functions + trace_config_time) {
      last = (int)strlen(trace)-1;
      if (trace[last] != 0x0a) {sprintf(trace, "%s\n", trace);}
    }
    switch(trace_output_type) {
        case TRACE_MEMORY      : traceToBuffer(trace); break;
        case TRACE_STDOUT      : traceToStdout(trace); break;
#if       SiTRACES_FEATURES == SiTRACES_FULL
        case TRACE_EXTERN_FILE : traceToFile  (trace); break;
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */
        case TRACE_NONE        : return;               break;
        default :                                      break;
    }
    if ((trace_config_verbose) & (trace_output_type!=TRACE_STDOUT))  {traceToStdout(trace);}
    if (strcmp(trace,"\n")==0) {trace_skip_info = 0;}
    trace_count++;
}
/************************************************************************************************************************
  SiTraceConfiguration function
  Use:        SiTRACES configuration function.
              It is used to configure the traces or trace a custom string..
  Comments:   If the trace entered starts by 'traces', analyze the configuration string trace
              and define which type of arguments there are.
              (Each argument refers to a particular treatment).
              The trace message may include several series of (-<param> <value>) pairs.
  Parameter:  config, the configuration string or trace to add (if not a configuration string)
  Returns:    The help if 'traces help' or 'traces'
              The configuration  status if 'traces -<param> <value>'
              The traces buffer content if 'traces get'
              The number of      traces if 'traces count'
              The number of lost traces if 'traces lost'
              Nothing otherwise.
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
const char *SiTraceConfiguration   (const char *config) {
#if       SiTRACES_FEATURES == SiTRACES_FULL
    FILE *file;
    time_t rawtime;
    struct tm * timeinfo;
    char c;
    unsigned int i;
    char *pArray;
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */
    char saved;
    int loop, nbArgs, trace_configuration_message, lenTraceBuffer, destination, start, origine;
    char *array[50];
    char *pBuffer;
#ifdef    LINUX_ST_SDK2_I2C
    char *config_string;
#endif /* LINUX_ST_SDK2_I2C */

    loop                        = 0;
    trace_configuration_message = 0;
    trace_stockInt[0]           = 0;
    lenTraceBuffer              = (int)strlen(trace_buffer);
    destination                 = lenTraceBuffer%SiTRACES_BUFFER_LENGTH;
    start                       = lenTraceBuffer;
    saved                       = trace_buffer[start];
    pBuffer                     = trace_buffer;

    sprintf(trace_message, "%s", config);
    if (!strncmp(trace_message,"traces",6)) {
        /* strtok splitting input and storing all items, returning first item */
#ifdef    LINUX_ST_SDK2_I2C
        config_string = trace_message +7;
        array[0] = strsep(&config_string," ");
#else  /* LINUX_ST_SDK2_I2C */
        array[0] = strtok(trace_message+7," ");
#endif /* LINUX_ST_SDK2_I2C */
        if(array[0]==NULL) {return traceHelp();}

        /* retrieving all remaining items */
        for(loop=1;loop<50;loop++) {
#ifdef    LINUX_ST_SDK2_I2C
            array[loop] = strsep(&config_string," ");
#else  /* LINUX_ST_SDK2_I2C */
            array[loop] = strtok(NULL," ");
#endif /* LINUX_ST_SDK2_I2C */
            if(array[loop]==NULL) break;
        }
        nbArgs=loop;
        /*treatment of the buffer according to the output*/
        for(loop=0;loop<nbArgs;loop++) {
            if(!strcmp_nocase_n(array[loop],"help",4)) {
                /*print the help menu*/
                trace_configuration_message=1;
              /* display the trace help on stdout */
                return traceHelp();
            }
#if       SiTRACES_FEATURES == SiTRACES_FULL
            else if(!strcmp_nocase_n(array[loop],"erase"   ,5) ) {
                file = fopen(trace_file_name,"w");
                if(!file) {
                  trace_output_type=TRACE_MEMORY;
                  sprintf(trace_message,"traces can not be written to file %s, routing traces to memory.\n", trace_file_name);
                } else {
                sprintf(trace_message,"traces in %s erased.\n", trace_file_name);
                fclose(file);
              }
              return trace_message;
            }
            else if(!strcmp_nocase_n(array[loop],"save"    ,4) ) {
                /*save the trace buffer content in an extern file */
                file = fopen(trace_file_name,"a+");
              if(!file) {
                trace_output_type=TRACE_MEMORY;
                sprintf(trace_message,"traces can not be written to file %s, routing traces to memory.\n", trace_file_name);
              } else {
                if(trace_lost_traces) {fprintf(file,"\n[...lost traces : %4d...]\n",trace_lost_traces);}
                fprintf(file,"%s\n",trace_buffer);
                fclose(file);
              }
              return trace_message;
            }
            else if(!strcmp_nocase_n(array[loop],"show"    ,4) ) {
                /*print the buffer content on stdout*/
                if(trace_lost_traces) {
                    CUSTOM_PRINTF("[...lost traces : %4d...]\n",trace_lost_traces);
                    c=trace_buffer[SiTRACES_BUFFER_LENGTH-1];
                    trace_buffer[SiTRACES_BUFFER_LENGTH-1]='\0';
                    pBuffer+=strlen(trace_buffer)+1;
                    CUSTOM_PRINTF("%s",pBuffer);
                    if(c) {CUSTOM_PRINTF("%c",c);}
                    trace_buffer[SiTRACES_BUFFER_LENGTH-1]=c;
                 }
                CUSTOM_PRINTF("%s\n",trace_buffer);
                return (char *)"";
            }
            else if(!strcmp_nocase_n(array[loop],"-name"   ,5) ) {
                trace_configuration_message=1;
                if(!array[loop+1]) {
                  sprintf(trace_message,"%s\n", trace_file_name);
                  return trace_message;
                }
                else if(strlen(array[loop+1]) < 40) {
                    pArray = array[loop+1];
                    for (i=0;i<strlen(array[loop+1]);i++) {
                        trace_file_name[i] = *pArray;
                        pArray++;
                    }
                    trace_file_name[i] = 0x00;
                    trace_config_rename=1;
                    file = fopen(trace_file_name,"a+");
                    if(!file) CUSTOM_PRINTF("rename file operation failed");
                    else {
                        /*print the actual date and time */
                        time ( &rawtime );
                        timeinfo = localtime ( &rawtime );
                        strftime (trace_timer,50,"%A %B %d   %I:%M%p   %Y",timeinfo);
                        fprintf(file,"            SiTraceFunction log created on %s\n",trace_timer);
                        fclose(file);
                    }
                }
                else {CUSTOM_PRINTF("rename file operation failed");}
            }
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */
            else if(!strcmp_nocase_n(array[loop],"-verbose",8) ) {
                if (nbArgs <= loop+1) return "missing argument after '-verbose'";
                trace_configuration_message=1;
                if((!strcmp_nocase_n(array[loop+1],"on" ,2)) || (!strncmp(array[loop+1],"1",1))) trace_config_verbose=1;
                if((!strcmp_nocase_n(array[loop+1],"off",3)) || (!strncmp(array[loop+1],"0",1))) trace_config_verbose=0;
            }
            else if(!strcmp_nocase_n(array[loop],"count"   ,5) ) {
                sprintf(trace_stockInt,"%d\n",trace_count);
                trace_count=0;
                return trace_stockInt;
            }
            else if(!strcmp_nocase_n(array[loop],"suspend" ,7) ) {
                trace_suspend = 1;
                sprintf(trace_stockInt,"%d\n",trace_suspend);
                return trace_stockInt;
            }
            else if(!strcmp_nocase_n(array[loop],"resume"  ,6) ) {
                trace_suspend=0;
                sprintf(trace_stockInt,"%d\n",trace_suspend);
                return trace_stockInt;
            }
            else if(!strcmp_nocase_n(array[loop],"lost"    ,4) ) {
                sprintf(trace_stockInt,"%d\n",trace_lost_traces);
                return trace_stockInt;
            }
            else if(!strcmp_nocase_n(array[loop],"flush"   ,5) ) {
                trace_configuration_message=1;
              /* empty the trace buffer */
                if(strlen(trace_buffer)) {traceFlushBuffer(trace_buffer);}
                return (char *)"traces memory flushed\n";
              }
            else if(!strcmp_nocase_n(array[loop],"get"     ,3) ) {
                /*reorder the trace buffer content and return a pointer on the trace buffer address*/
                if(trace_lost_traces) {
                     for (loop=0;loop<SiTRACES_BUFFER_LENGTH;loop++) {
                        origine = (destination - (SiTRACES_BUFFER_LENGTH - 1 - lenTraceBuffer) ) % SiTRACES_BUFFER_LENGTH;
                        if (destination < 0) {destination += SiTRACES_BUFFER_LENGTH;}
                        if (origine < 0) {origine += SiTRACES_BUFFER_LENGTH;}
                        if (origine == start) {
                            trace_buffer[destination] = saved;
                            destination = origine+1;
                            start = destination;
                            saved = trace_buffer[start];
            }
                        else {
                            trace_buffer[destination] = trace_buffer[origine];
                            destination = origine;
            }
            }
            }
                return trace_buffer;
            }
            else if(!strcmp_nocase_n(array[loop],"status"  ,6) ) {
                switch(trace_output_type) {
                    case TRACE_MEMORY      : sprintf(trace_message," -output memory " ); break;
                    case TRACE_STDOUT      : sprintf(trace_message," -output stdout " ); break;
#if       SiTRACES_FEATURES == SiTRACES_FULL
                    case TRACE_EXTERN_FILE : sprintf(trace_message," -output file "   ); break;
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */
                    case TRACE_NONE        : sprintf(trace_message," -output none "   ); break;
                    default                : sprintf(trace_message," -output unknown "); break;
                 }
#if       SiTRACES_FEATURES == SiTRACES_FULL
                                             sprintf(trace_message,"%s -name %s "        , trace_message, trace_file_name);
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */
                                             sprintf(trace_message,"%s-file "            , trace_message);
                if (trace_config_files    ) {sprintf(trace_message,"%s on "              , trace_message);}
                else {                       sprintf(trace_message,"%soff "              , trace_message);}
                                             sprintf(trace_message,"%s-line "            , trace_message);
                if (trace_config_lines    ) {sprintf(trace_message,"%s on "              , trace_message);}
                else {                       sprintf(trace_message,"%soff "              , trace_message);}
                                             sprintf(trace_message,"%s-function "        , trace_message);
                if (trace_config_functions) {sprintf(trace_message,"%s on "              , trace_message);}
                else {                       sprintf(trace_message,"%soff "              , trace_message);}
                                             sprintf(trace_message,"%s-time "            , trace_message);
                if (trace_config_time     ) {sprintf(trace_message,"%s on "              , trace_message);}
                else {                       sprintf(trace_message,"%soff "              , trace_message);}
                                             sprintf(trace_message,"%s-tags "            , trace_message);
                if (trace_config_tags     ) {sprintf(trace_message,"%s on "              , trace_message);}
                else {                       sprintf(trace_message,"%soff "              , trace_message);}
                                             sprintf(trace_message,"%s-level "           , trace_message);
                if (trace_config_level    ) {sprintf(trace_message,"%s on "              , trace_message);}
                else {                       sprintf(trace_message,"%soff "              , trace_message);}
                                             sprintf(trace_message,"%slevels 0x%02x "    , trace_message, trace_levels);
                                             sprintf(trace_message,"%s-verbose "         , trace_message);
                if (trace_config_verbose  ) {sprintf(trace_message,"%s on "              , trace_message);}
                else {                       sprintf(trace_message,"%soff "              , trace_message);}
                sprintf(trace_message,"%s\n", trace_message);
                return trace_message;
            }
            else if(!strcmp_nocase_n(array[loop],"-output"  ,7) ) {
                if (nbArgs <= loop+1) return "missing argument after '-output'";
                trace_configuration_message=1;
                if (!strcmp_nocase_n(array[loop+1],"none"  ,4)) trace_output_type=TRACE_NONE;
                if (!strcmp_nocase_n(array[loop+1],"memory",6)) trace_output_type=TRACE_MEMORY;
                if (!strcmp_nocase_n(array[loop+1],"stdout",6)) trace_output_type=TRACE_STDOUT;
#if       SiTRACES_FEATURES == SiTRACES_FULL
                if (!strcmp_nocase_n(array[loop+1],"file"  ,4)) trace_output_type=TRACE_EXTERN_FILE;
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */
            }
            else if(!strcmp_nocase_n(array[loop],"-file"    ,5) ) {
                if (nbArgs <= loop+1) return "missing argument after '-file'";
                trace_configuration_message=1;
                if((!strcmp_nocase_n(array[loop+1],"on" ,2)) || (!strncmp(array[loop+1],"1",1))) trace_config_files=1;
                if((!strcmp_nocase_n(array[loop+1],"off",3)) || (!strncmp(array[loop+1],"0",1))) trace_config_files=0;
            }
            else if(!strcmp_nocase_n(array[loop],"-line"    ,5) ) {
                if (nbArgs <= loop+1) return "missing argument after '-line'";
                trace_configuration_message=1;
                if((!strcmp_nocase_n(array[loop+1],"on" ,2)) || (!strncmp(array[loop+1],"1",1))) trace_config_lines=1;
                if((!strcmp_nocase_n(array[loop+1],"off",3)) || (!strncmp(array[loop+1],"0",1))) trace_config_lines=0;
            }
            else if(!strcmp_nocase_n(array[loop],"-function",9) ) {
                if (nbArgs <= loop+1) return "missing argument after '-function'";
                trace_configuration_message=1;
                if((!strcmp_nocase_n(array[loop+1],"on" ,2)) || (!strncmp(array[loop+1],"1",1))) trace_config_functions=1;
                if((!strcmp_nocase_n(array[loop+1],"off",3)) || (!strncmp(array[loop+1],"0",1))) trace_config_functions=0;
            }
            else if(!strcmp_nocase_n(array[loop],"-time"    ,5) ) {
                if (nbArgs <= loop+1) return "missing argument after '-time'";
                trace_configuration_message=1;
                if((!strcmp_nocase_n(array[loop+1],"on" ,2)) || (!strncmp(array[loop+1],"1",1))) trace_config_time=1;
                if((!strcmp_nocase_n(array[loop+1],"off",3)) || (!strncmp(array[loop+1],"0",1))) trace_config_time=0;
            }
            else if(!strcmp_nocase_n(array[loop],"-tag"     ,5) ) {
                if (nbArgs <= loop+1) return "missing argument after '-tag'";
                trace_configuration_message=1;
                if((!strcmp_nocase_n(array[loop+1],"on" ,2)) || (!strncmp(array[loop+1],"1",1))) trace_config_tags=1;
                if((!strcmp_nocase_n(array[loop+1],"off",3)) || (!strncmp(array[loop+1],"0",1))) trace_config_tags=0;
            }
            else if(!strcmp_nocase_n(array[loop],"-level"   ,6) ) {
                if (nbArgs <= loop+1) return "missing argument after '-level'";
                trace_configuration_message=1;
                if((!strcmp_nocase_n(array[loop+1],"on" ,2)) || (!strncmp(array[loop+1],"1",1))) trace_config_level=1;
                if((!strcmp_nocase_n(array[loop+1],"off",3)) || (!strncmp(array[loop+1],"0",1))) trace_config_level=0;
            }
#if      SiTRACES_FEATURES == SiTRACES_FULL
            else if(!strcmp_nocase_n(array[loop],"level"    ,5) ) {
                if (nbArgs <= loop+1) return "missing level_index argument after 'level'";
                if (nbArgs <= loop+2) return "missing level_index and on/off arguments after 'level'";
                sscanf(array[loop+1],"%d",&i);
                trace_configuration_message=1;
                if((!strcmp_nocase_n(array[loop+2],"on" ,2)) || (!strncmp(array[loop+2],"1",1))) SiTraceLevel(i, 1);
                if((!strcmp_nocase_n(array[loop+2],"off",3)) || (!strncmp(array[loop+2],"0",1))) SiTraceLevel(i, 0);
            }
#endif /* SiTRACES_FEATURES == SiTRACES_FULL */
        }
    }
    if (!trace_configuration_message) {
      trace_skip_info = 1;
      traceToDestination((char*)(config+7));
      trace_skip_info = 0;
      return (char *)"";
    }
    return SiTraceConfiguration("traces status");
}
/************************************************************************************************************************
  SiTraceFunction function
  Use:        SiTRACES trace formatting function.
              It formats the trace message with file name and line number and time if selected
              then saves it to the trace output.
  Parameter:  name    the file name where the trace is written.
  Parameter:  number  the line number where the trace is written.
  Parameter:  fmt     string content of trace message. Others arguments are sent thanks to the ellipse.
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h.
************************************************************************************************************************/
void  SiTraceFunction        (unsigned char level, const char *tag, const char *name, int linenumber, const char *func, const char *fmt, ...) {
    char        message[1000];
    const char *pname;
    const char *pfunc;
    va_list     ap;
    if (trace_output_type == TRACE_NONE) return;
    if (SiTraceLevelEnabled(level)==0)   return;
    /* print the line line number in trace_linenumber */
    trace_linenumber = linenumber;
    pname=name;

    /* print the file name in trace_source_file */
    if(strlen(pname)>SiTRACES_NAMESIZE) {
      pname+=strlen(pname)-SiTRACES_NAMESIZE;
    }
    strncpy(trace_source_file,pname,SiTRACES_NAMESIZE);

    /* print the tag in trace_tag          */
    /* print the level in trace_level_text */
    if (level != 32) {
      snprintf(trace_tag, SILABS_TAG_SIZE ,"%s",tag);
      snprintf(trace_level_text, SILABS_TAG_SIZE ,"L%-3d",level);
    } else {
      snprintf(trace_tag, SILABS_TAG_SIZE ,"%9s","");
      snprintf(trace_level_text, SILABS_TAG_SIZE ," %3s","");
    }
    /*print the function name in trace_source_function */
    pfunc=func;
    sprintf(trace_source_function,"%s","");
    if(strlen(pfunc)>SiTRACES_FUNCTION_NAMESIZE) {
      pfunc+=(strlen(pfunc)-SiTRACES_FUNCTION_NAMESIZE)+2;
      strncpy(trace_source_function,"..",SiTRACES_FUNCTION_NAMESIZE);
    }
    strncat(trace_source_function,pfunc,SiTRACES_FUNCTION_NAMESIZE-2);

    va_start(ap, fmt);
    vsnprintf(message,1000,fmt,ap);
    traceToDestination(message);
    va_end(ap);
    return;
}
#endif /* SiTRACES */
/************************************************************************************************************************
  strcmp_nocase function
  Use:        case-insensitive string comparison function
              Used to compare 2 strings without case sensitivity
  Comments:   As long as this function is only used for SiTRACES, it can be left in the TRACES code
  Returns:    0 if identical
************************************************************************************************************************/
int  strcmp_nocase   (const char* str1, const char* str2) {
    size_t       l;
    unsigned int i;
    int       diff;
    l = strlen(str1);
    if (l != strlen(str2)) return 1;
    for (i=0;i<l;i++) {
        if (str1[i] != str2[i]) {
            diff = str1[i]-str2[i];
            if (diff < 0) {diff = - diff;}
            if (diff !=32) {
                return 2;
            } else {
                if ((((str1[i]+str2[i])/2) < 81) || (((str1[i]+str2[i])/2)>106))  return 3;
            }
        }
    }
    return 0;
}
/************************************************************************************************************************
  strcmp_nocase_n function
  Use:        case-insensitive string comparison function with size limit
              Used to compare 2 strings without case sensitivity, with a limit on the number of characters
  Comments:   As long as this function is only used for SiTRACES, it can be left in the TRACES code
  Returns:    0 if identical
************************************************************************************************************************/
int  strcmp_nocase_n (const char* str1, const char* str2, unsigned int n) {
    size_t       l;
    size_t       l1;
    size_t       l2;
    unsigned int i;
    int       diff;
    l1 = strlen(str1);
    l2 = strlen(str2);
    if (l1 < l2) {l = l1;} else {l = l2;};
    if (l  > n ) {l = n;}
    for (i=0;i<l;i++) {
        if (str1[i] != str2[i]) {
            diff = str1[i]-str2[i];
            if (diff < 0) {diff = - diff;}
            if (diff !=32) {
                return 2;
            } else {
                if ((((str1[i]+str2[i])/2) < 81) || (((str1[i]+str2[i])/2)>106))  return 3;
            }
        }
    }
    return 0;
}
int  L0_StoreTag     (const char *tag) {
#ifdef SiTRACES
  return snprintf(trace_tag, SILABS_TAG_SIZE ,"%s", tag);
#else  /* SiTRACES */
  return strlen(tag);
#endif /* SiTRACES */
}
int  L0_StoreError   (const char *message) {
  int length;
  int length_new_msg;
  length         = (int)strlen(stored_error_message);
  length_new_msg = (int)strlen(message);
  if ( (length + length_new_msg) >= ERROR_MESSAGE_MAX_LENGH ) {
    stored_error_message[ERROR_MESSAGE_MAX_LENGH-40] = 0x00;
    length = sprintf(stored_error_message, "%s%s", stored_error_message, "...There are lost errors...\n");
  } else {
    length = sprintf(stored_error_message, "%s%s", stored_error_message, message);
  }
  return length;
}
int  L0_ErrorMessage (void) {
  int length;
  length = sprintf(L0_error_message, "%s", stored_error_message);
  sprintf(stored_error_message, "%s", "");
  return length;
}
/************************************************************************************************************************
  system_wait function
  Use:        current system wait function
              Used to wait for time_ms milliseconds while doing nothing
  Parameter:  time_ms the wait duration in milliseconds
  Returns:    The current system time in milliseconds
  Porting:    Needs to use the final system call for time retrieval
************************************************************************************************************************/
int     system_wait          (int time_ms) {
  unsigned long ticks1, ticks2;
  ticks1=system_time() + time_ms;
  ticks2=ticks1;
  while (ticks2<=ticks1) {ticks2=system_time();}
  return (int)ticks2;
}
/************************************************************************************************************************
  system_time function
  Use:        current system time retrieval function
              Used to retrieve the current system time in milliseconds
  Returns:    The current system time in milliseconds
  Porting:    Needs to use the final system call
************************************************************************************************************************/
int     system_time          (void)        {
    /* <porting> Replace 'clock' by whatever is necessary to return the system time in milliseconds */
    //return (int)clock()*1000/CLOCKS_PER_SEC;
    struct timeval stSilabsTime;
    HI_U32  u32SystemTimeInMs = 0;

    do_gettimeofday(&stSilabsTime);
    u32SystemTimeInMs = stSilabsTime.tv_sec*1000 + stSilabsTime.tv_usec/1000;
    return u32SystemTimeInMs;
}
int     L0_SimulatorRead     (int AdrSize, unsigned char * Adr, int ReadSize, unsigned char *Buffer) {
  int I2cIndex, relativeAdd, i;
  I2cIndex =0;
  for (i = 0; i < AdrSize; i++) {
    I2cIndex = (I2cIndex << 8) + Adr[i];
  }
  if (I2cIndex + ReadSize >= SIMULATOR_SCOPE) {
    CUSTOM_PRINTF("trying to access an address out of the simulator's scope !!");
    return 0;
  }
  for (relativeAdd = 0; relativeAdd < ReadSize; relativeAdd ++) {
    Buffer[relativeAdd]=Byte[I2cIndex + relativeAdd];
  }
  return ReadSize;
}
int     L0_SimulatorWrite    (int AdrSize, int BufSize, unsigned char * Buffer){
  int I2cIndex, relativeAdd, i;
  I2cIndex =0;
  for (i = 0; i < AdrSize; i++) {
    I2cIndex = (I2cIndex <<8) + Buffer[i];
  }
  if (I2cIndex + BufSize >= SIMULATOR_SCOPE) {
    CUSTOM_PRINTF("trying to access an address out of the simulator's scope !!");
    return 0;
  }
  for (relativeAdd = AdrSize; relativeAdd < BufSize; relativeAdd ++) {
     Byte[I2cIndex + relativeAdd -AdrSize] = Buffer[relativeAdd];
  }
  return BufSize;
}

/* Re-definition of SiTRACE for L0_Context */
#ifdef    SiTRACES
  #undef  SiTRACE
  #define SiTRACE(...)        SiTraceFunction(SiLEVEL, i2c->tag, __FILE__, __LINE__, __func__     ,__VA_ARGS__)
#endif /* SiTRACES */
#ifdef    LINUX_ST_SDK2_I2C
#ifndef HISILICON_I2C
STCHIP_Error_t SDK2_I2cRead (STCHIP_Handle_t hChip, u_int8_t ChipAddress, unsigned char *Data, int NbData)
{
  fe_i2c_msg msg[1];
  int ret;
  uint32_t MsgIndex    = 0;
  uint32_t retry_count = 0;
  uint32_t msg_cnt;

  msg[MsgIndex].addr   = hChip->I2cAddr;
  msg[MsgIndex].flags  = READING;
#ifdef CONFIG_ARCH_STI
  msg[MsgIndex].flags |= STMFE_I2C_USE_STOP;
#else
  msg[MsgIndex].flags |= I2C_M_NOREPSTART;
#endif
  msg[MsgIndex].buf    = Data;
  msg[MsgIndex].len    = NbData;
  (MsgIndex)++;

  do {
    ret = i2c_transfer(hChip->dev_i2c, &msg[0], MsgIndex);
    if (ret != MsgIndex && retry_count == 2) {
      for (msg_cnt = 0; msg_cnt < MsgIndex; msg_cnt++)
        pr_err(
          "%s:WR msg[%d] addr = 0x%x len = %d Err= %d\n"
          , __func__, msg_cnt, msg[msg_cnt].addr,
          msg[msg_cnt].len, ret);
      hChip->Error = CHIPERR_I2C_NO_ACK;
    }
    retry_count++;
  } while ((ret != MsgIndex) && (retry_count <= 2));

	return hChip->Error;
}
STCHIP_Error_t SDK2_I2cWrite(STCHIP_Handle_t hChip, u_int8_t ChipAddress, unsigned char *Data, int NbData)
{
  fe_i2c_msg msg[1];
  int ret;
  uint32_t MsgIndex    = 0;
  uint32_t retry_count = 0;
  uint32_t msg_cnt;

    hChip->Error = CHIPERR_NO_ERROR;

  msg[MsgIndex].addr   = hChip->I2cAddr;
  msg[MsgIndex].flags  = WRITING;
#ifdef CONFIG_ARCH_STI
  msg[MsgIndex].flags |= STMFE_I2C_USE_STOP;
#else
  msg[MsgIndex].flags |= I2C_M_NOREPSTART;
#endif
  msg[MsgIndex].buf    = Data;
  msg[MsgIndex].len    = NbData;
  (MsgIndex)++;

  do {
    ret = i2c_transfer(hChip->dev_i2c, &msg[0], MsgIndex);
      if (ret != MsgIndex && retry_count == 2) {
        for (msg_cnt = 0; msg_cnt < MsgIndex; msg_cnt++)
          pr_err(
            "%s:WR msg[%d] addr = 0x%x len = %d Err= %d\n"
            , __func__, msg_cnt, msg[msg_cnt].addr,
            msg[msg_cnt].len, ret);
          hChip->Error = CHIPERR_I2C_NO_ACK;
        }
        retry_count++;
    } while ((ret != MsgIndex) && (retry_count <= 2));

  return hChip->Error;
}
#endif /* HISILICON_I2C */
#endif /* LINUX_ST_SDK2_I2C */
/************************************************************************************************************************
  L0_Init function
  Use:        layer 0 initialization function
              Used to set the layer 0 context parameters to startup values.
              It must be called first and once per Layer 1 instance (i.e. once for the tuner and once for the demodulator).
              It is automatically called by the Layer 1 init function.
  Parameters: mustReadWithoutStop has been added to manage the case when some components do not allow a stop in a 'read'.
              i2c usually allows 'write 0xc8 0x01 0x02' followed by 'read 0xc9 1' to read the byte at index 0x0102.
              This should return the same data as 'read 0xc8 0x01 0x02 1'.
              If this is not allowed, set mustReadWithoutStop at 1.
              NB: at the date of writing, this behavior has only been detected in the RDA5812 satellite tuner.
  Returns:    void
  Porting:    If some members of the L0_Context structure are removed, they need to be removed from here too
************************************************************************************************************************/
void    L0_Init  (unsigned int u32TunerId,L0_Context* i2c,unsigned int u32I2cChannel) {
  int i;
  #ifdef    USB_Capability
  char rettxtBuffer[200];
  char *rettxt;
  double dval;
  rettxt = rettxtBuffer;
  #endif /* USB_Capability */

  i2c->address             = 0;
  i2c->indexSize           = 0;
  i2c->connectionType      = SIMU;
  i2c->trackWrite          = 0;
  i2c->trackRead           = 0;
  i2c->mustReadWithoutStop = 0;
  i2c->u32I2cChannel = u32I2cChannel;
  i2c->u32TunerId = u32TunerId;
  i2c->tag_index           = 0;
  for (i=0; i<SIMULATOR_SCOPE; i++) {Byte[i]=0x00;}
  rawI2C = &rawI2C_context;
  rawI2C->indexSize = 0;
  stored_error_message = L0_error_buffer_0;
  L0_error_message     = L0_error_buffer_1;
  sprintf(stored_error_message, "%s", "");
  #ifdef    USB_Capability
  if (!cypress_checks_done) {
    L0_Connect (i2c, USB);
    L0_Cypress_Process((char*)"dll_version", (char*)"", 0, &dval, &rettxt);
    SiTRACE("dll_version %s (recommended minimal version 10.23)\n", rettxt);
    L0_Cypress_Process((char*)"fw_version" , (char*)"", 0, &dval, &rettxt);
    SiTRACE("fw_version  %s (recommended minimal version 10.20)\n", rettxt);
    cypress_checks_done = 1;
  }
  #endif /* USB_Capability */
#ifdef    LINUX_ST_SDK2_I2C
  #ifdef    HISILICON_I2C
    i2c->channel = i2c->channel;
  #else
    i2c->SDK2_i2c_Chip = NULL;
  #endif
#endif /* LINUX_ST_SDK2_I2C */
#ifdef    SiTRACES
  if (!trace_init_done) {
    CUSTOM_PRINTF("\n********** SiTRACES activated *********\nComment the '#define SiTRACES' line\nin Silabs_L0_API.h to de-activate all traces.\n\n");
    SiTraceDefaultConfiguration();
  }
  snprintf(i2c->tag, SILABS_TAG_SIZE, "%s", "");
#endif /* SiTRACES */

}
/************************************************************************************************************************
  L0_InterfaceType function
  Use:        function to return the communication mode string
              Used to display a clear text related to the communication mode.
  Returns:    the string correspopnding to the current connection mode
************************************************************************************************************************/
const char*   L0_InterfaceType     (L0_Context* i2c) {
  switch (i2c->connectionType) {
  #ifdef USB_Capability
    case USB:
      return (char *)"USB";
      break;
  #endif /* USB_Capability */
    case SIMU:
      return (char *)"SIMU";
      break;
    case CUSTOMER:
      return (char *)"CUST";
      break;
    case LINUX_I2C:
      return (char *)"I2C";
      break;
    case LINUX_USB:
      return (char *) "LUSB";
      break;
#ifdef    LINUX_ST_SDK2_I2C
    case LINUX_KERNEL_I2C:
      return (char *) "STK";
      break;
#endif /* LINUX_ST_SDK2_I2C */
    default:
      return (char *)"?";
      break;
   };
}
/************************************************************************************************************************
  L0_SetAddress function
  Use:        function to set the device address
              Used to set the I2C address of the component.
              It must be called only once at startup per Layer 1 instance, as the addresses are not expected to change over time.
  Returns:    1 if OK, 0 otherwise
************************************************************************************************************************/
int     L0_SetAddress        (L0_Context* i2c, unsigned int add, int addSize) {
  i2c->address   =  add     & 0xff;
#ifdef    LINUX_I2C_Capability
  i2c->adapter_nr= (add>>8) & 0xff;
#endif /* LINUX_I2C_Capability */
  i2c->indexSize = addSize;
  switch (i2c->connectionType) {
  #ifdef USB_Capability
    case USB:
      L0_Connect (i2c, i2c->connectionType);
      return 1;
      break;
  #endif /* USB_Capability */
    case SIMU:
      return 1;
      break;
    case CUSTOMER:
      return 1;
      break;
    default:
      break;
   };
  return 0;
}
/************************************************************************************************************************
  L0_Connect function
  Use:        Core layer 0 connection function
              Used to switch between various connection modes
              If a single connection  mode is used, this function can be removed, and the corresponding calls from the Layer 1 code can be removed as well.
              It can be useful during SW development, to easily switch between the simulator and the actual HW.
  Returns:    1 if connected to actual hw
  Porting:    Depending on the i2c layer, this function could be removed if a single connection mode is allowed
************************************************************************************************************************/
int     L0_Connect           (L0_Context* i2c, CONNECTION_TYPE connType) {
  #ifdef    USB_Capability
  if (i2c->connectionType == USB) {
    Cypress_USB_Close();
  }
  #endif /* USB_Capability */
  #ifdef    LINUX_USB_Capability
  if (i2c->connectionType == LINUX_USB) {
    Cypress_USB_Close();
  }
  #endif /* LINUX_USB_Capability */
  switch (connType) {
    #ifdef    USB_Capability
    case USB:
      Cypress_USB_Open();
      i2c->connectionType =  USB;
      return 1;
      break;
    #endif /* USB_Capability */
    case CUSTOMER:
      i2c->connectionType =  CUSTOMER;
      return 1;
      break;
  #ifdef    LINUX_I2C_Capability
    case LINUX_I2C:
      i2c->connectionType =  LINUX_I2C;
      return 1;
      break;
  #endif /* LINUX_I2C_Capability */
  #ifdef    LINUX_USB_Capability
    case LINUX_USB:
      Cypress_USB_Open();
      i2c->connectionType =  LINUX_USB;
      return 1;
      break;
  #endif /* LINUX_USB_Capability */
  #ifdef    LINUX_ST_SDK2_I2C
    case LINUX_KERNEL_I2C:
      i2c->connectionType =  LINUX_KERNEL_I2C;
      return 1;
      break;
  #endif /* LINUX_ST_SDK2_I2C */
    default:
      i2c->connectionType =  SIMU;
      return 0;
    break;
  };
  return 0;
}
/************************************************************************************************************************
  L0_TrackRead function
  Use:        layer 0 initialization function
              Used to toggle the read traces for the related Layer 1 instance.
              It is useful for debug purpose, mostly to control that data is properly transmitted to the above layers.
  Returns:    void
************************************************************************************************************************/
void    L0_TrackRead         (L0_Context* i2c, unsigned int track) {
  i2c->trackRead  = track;
}
/************************************************************************************************************************
  L0_TrackWrite function
  Use:        layer 0 initialization function
              Used to toggle the write traces for the related Layer 1 instance.
              It is useful for debug purpose, mostly to control that data is properly written to the desired Layer 1 instance.
  Returns:    void
************************************************************************************************************************/
void    L0_TrackWrite        (L0_Context* i2c, unsigned int track) {
  i2c->trackWrite = track;
}


HI_U32  si2144_tda_read(HI_U8 uAddress,HI_U32 uNbData, HI_U8 * pDataBuff)
{
    HI_S32 i;
    HI_S32 s32Ret;
    TUNER_I2C_DATA_S stI2cDataStr = { 0 };
    HI_U8 au8RcvData[256] = { 0 };
    HI_U8 uSubAddress = 0x00;

    memset ((void *) au8RcvData, 0, sizeof (au8RcvData));
    stI2cDataStr.pu8ReceiveBuf = au8RcvData;
    stI2cDataStr.pu8SendBuf = &uSubAddress;
    stI2cDataStr.u32ReceiveLength = uNbData;
    stI2cDataStr.u32SendLength = 0;

    s32Ret = tuner_i2c_receive_data_si(g_stTunerOps[0].enI2cChannel, uAddress /*|0x01 */ ,&stI2cDataStr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("[si2144 error]%s %d IIC read err! status:0x%x\n", __FUNCTION__, __LINE__, s32Ret);
        return HI_FAILURE;
    }
    for (i = 0; i < uNbData; i++)
    {
        pDataBuff[i] = au8RcvData[i];
    }
    return HI_SUCCESS;
}

/************************************************************************************************************************
  L0_ReadBytes function
  Use:        lowest layer read function
              Used to read a given number of bytes from the Layer 1 instance.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to read.
              iNbBytes, the number of bytes to read.
              *pbtDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final i2c read function
************************************************************************************************************************/
int     L0_ReadBytes         (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pucDataBuffer) {
    HI_S32 s32Ret = HI_SUCCESS;
  int r,i,nbReadBytes;
  unsigned char  ucAddressBuffer[4];
  unsigned char *pucAddressBuffer;
#ifdef    USB_Capability
  char rettxtBuffer[256];
  char *rettxt;
  rettxt = rettxtBuffer;
#endif /* USB_Capability */
  pucAddressBuffer = (unsigned char *)&ucAddressBuffer;

  nbReadBytes = 0;
  for (i=0;i<i2c->indexSize;i++) {
      r = 8*(i2c->indexSize -1 -i);
    pucAddressBuffer[i] = (unsigned char)((iI2CIndex & (0xff<<r) ) >> r);
  }
  for (i=i2c->indexSize; i<4;i++) {
    pucAddressBuffer[i] = 0x00;
  }
  switch (i2c->connectionType) {
#ifdef    USB_Capability
    case USB:
      if (i2c->mustReadWithoutStop==0) {
        L0_Cypress_Configure((char*)"-i2cread", (char*)"normal" , 0, &mydval, &rettxt);
      } else {
        L0_Cypress_Configure((char*)"-i2cread", (char*)"no_stop", 0, &mydval, &rettxt);
      }
      if (RET_OK == Cypress_USB_ReadI2C(i2c->address>>1, i2c->indexSize, pucAddressBuffer, iNbBytes, pucDataBuffer)) {
        nbReadBytes = iNbBytes;
      }
      break;
#endif /* USB_Capability */
    case LINUX_I2C:
      #ifdef    LINUX_I2C_Capability
        if(RET_OK == Linux_I2C_readByte (i2c->adapter_nr, i2c->address>>1, i2c->indexSize, pucAddressBuffer, iNbBytes, pucDataBuffer)){
          nbReadBytes = iNbBytes;
        }
      #endif /* LINUX_I2C_Capability */
      break;
#ifdef    LINUX_USB_Capability
    case LINUX_USB:
      if (RET_OK == Cypress_USB_ReadI2C(i2c->address>>1, i2c->indexSize, pucAddressBuffer, iNbBytes, pucDataBuffer)) {
        nbReadBytes = iNbBytes;
      }
      break;
#endif /* USB_Capability */
#ifdef    LINUX_ST_SDK2_I2C
    case LINUX_KERNEL_I2C:
    #ifdef    HISILICON_I2C

    #else
      nbWrittenBytes = 0;
        i2c->SDK2_i2c_Chip->I2cAddr = i2c->address>>1;
        if ( SDK2_I2cWrite(i2c->SDK2_i2c_Chip, 0x00, pucBuffer , iNbBytes + i2c->indexSize) != 0 ) {
          write_error++;
        } else {
          nbWrittenBytes = iNbBytes + i2c->indexSize;
        }
     #endif
#endif /* LINUX_ST_SDK2_I2C */
    case CUSTOMER:
      /* <porting> Insert here whatever is needed to
      read iNbBytes bytes
      from the chip whose i2c address is i2c->address,
      starting at index iI2CIndex,
      with an index on i2c->indexSize bytes
      the index bytes being stored in pucAddressBuffer.

      Make it such that on success nbReadBytes = iNbBytes
      and on failure nbReadBytes = 0.
      data bytes will be stored in pucDataBuffer.
      */      
        nbReadBytes = iNbBytes; 

        if (HI_UNF_DEMOD_DEV_TYPE_3130E == g_stTunerOps[i2c->u32TunerId].enDemodDevType ||
        HI_UNF_DEMOD_DEV_TYPE_3130I == g_stTunerOps[i2c->u32TunerId].enDemodDevType)
        {
            qam_config_i2c_out (i2c->u32TunerId, 1);
            s32Ret = si2144_tda_read ((HI_U8)g_stTunerOps[i2c->u32TunerId].u32TunerAddress, iNbBytes, pucDataBuffer);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("si2144_tda_read err.\n");
            }
        }
#if defined (DEMOD_DEV_TYPE_HI3137)
        else  if (HI_UNF_DEMOD_DEV_TYPE_3137 == g_stTunerOps[i2c->u32TunerId].enDemodDevType)
        {
            hi3137_config_i2c_out(i2c->u32TunerId);
            if(i2c->u32I2cChannel < HI_STD_I2C_NUM)
            {
                s32Ret = HI_DRV_I2C_Read(i2c->u32I2cChannel, i2c->address, 0xFE, 1, pucDataBuffer, iNbBytes);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_TUNER("HI_DRV_I2C_Read err:0x%x.\n",s32Ret);
                }
            }
            else
            {
                s32Ret = HI_DRV_GPIOI2C_ReadExt(i2c->u32I2cChannel, i2c->address, 0xFE, 1, pucDataBuffer, iNbBytes);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_TUNER("HI_DRV_GPIOI2C_ReadExt err:0x%x.\n",s32Ret);
                }
            }
        }
#endif
        else
        {
            if(i2c->channel < HI_STD_I2C_NUM)
            {
                s32Ret = HI_DRV_I2C_Read_SiLabs(i2c->channel, i2c->address, 0xFE, 1, pucDataBuffer, iNbBytes);            
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_TUNER("HI_DRV_I2C_Read err:0x%x.\n",s32Ret);
                }
            }
            else
            {
                s32Ret = HI_DRV_GPIOI2C_ReadExt(i2c->channel, i2c->address, 0xFE, 1, pucDataBuffer, iNbBytes);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_TUNER("HI_DRV_GPIOI2C_ReadExt err:0x%x.\n",s32Ret);
                }
            }
        }
      break;
    case SIMU:
      nbReadBytes = L0_SimulatorRead (i2c->indexSize, pucAddressBuffer, iNbBytes, pucDataBuffer);
      break;
    default:
      break;
  }
#ifdef    SiTRACES
  trace_skip_info = 1;
    if (i2c->trackRead==1) {
    sprintf(trace_L0_message, "reading 0x%02x ",i2c->address + 1);
    if (i2c->indexSize) {
      sprintf(trace_L0_message, "%sat", trace_L0_message);
      for (i=0;i<i2c->indexSize;i++) {
        r = 8*(i2c->indexSize -1 -i);
        sprintf(trace_L0_message, "%s 0x%02x", trace_L0_message, ((iI2CIndex & (0xff<<r))>> r)&0xff );
      }
    }
    sprintf(trace_L0_message, "%s <%s", trace_L0_message, L0_InterfaceType(i2c));
    if (nbReadBytes != iNbBytes) {sprintf(trace_L0_message, "%s READ  ERROR!", trace_L0_message);}
    for ( i=0 ; i < nbReadBytes ; i++ ) {  sprintf(trace_L0_message, "%s 0x%02x" ,trace_L0_message , (pucDataBuffer)[i]); }
    SiTRACE("%s\n", trace_L0_message);
    }
    trace_skip_info = 0;
#endif /* SiTRACES */
    return nbReadBytes;
}
/************************************************************************************************************************
  L0_WriteBytes function
  Use:        lowest layer write function
              Used to write a given number of bytes from the Layer 1 instance.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to write.
              iNbBytes, the number of bytes to write.
              *pbtDataBuffer, a pointer to a buffer containing the bytes to write.
  Returns:    the number of bytes read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final i2c write function
************************************************************************************************************************/
int     L0_WriteBytes        (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pucDataBuffer) {
    HI_S32 s32Ret = HI_SUCCESS;
  int r, i, nbWrittenBytes, write_error;
  unsigned char  ucBuffer[100];
  unsigned char  ucAddressBuffer[4];
  unsigned char *pucAddressBuffer;
  unsigned char *pucBuffer;
  HI_U8 pArray[256];

  pucBuffer        = (unsigned char *)&ucBuffer;
  pucAddressBuffer = (unsigned char *)&ucAddressBuffer;

  nbWrittenBytes = 0;
  write_error    = 0;
  for (i=0; i <i2c->indexSize;i++) {
    r = 8*(i2c->indexSize -1 -i);
    pucBuffer[i] = (unsigned char)((iI2CIndex & (0xff<<r) ) >> r);
    pucAddressBuffer[i] = pucBuffer[i];
  }
  for (i=0; i < iNbBytes ;    i++) {
    pucBuffer[i+i2c->indexSize] = pucDataBuffer[i];
	pArray[i] = pucDataBuffer[i];
  }
  switch (i2c->connectionType) {
#ifdef    USB_Capability
    case USB:
      pucDataBuffer = &pucBuffer[i2c->indexSize];
      if (RET_OK == Cypress_USB_WriteI2C (i2c->address>>1, i2c->indexSize, pucAddressBuffer, iNbBytes, pucDataBuffer)) {
        nbWrittenBytes = iNbBytes + i2c->indexSize;
      } else {
        write_error++;
      }
      break;
#endif /* USB_Capability */
#ifdef    LINUX_USB_Capability
    case LINUX_USB:
      pucDataBuffer = &pucBuffer[i2c->indexSize];
      if (RET_OK == Cypress_USB_WriteI2C (i2c->address>>1, i2c->indexSize, pucAddressBuffer, iNbBytes, pucDataBuffer)) {
        nbWrittenBytes = iNbBytes + i2c->indexSize;
      } else {
        write_error++;
      }
      break;
#endif /* LINUX_USB_Capability */
#ifdef    LINUX_ST_SDK2_I2C
    case LINUX_KERNEL_I2C:
    #ifdef    HISILICON_I2C

    #else
      nbWrittenBytes = 0;
        i2c->SDK2_i2c_Chip->I2cAddr = i2c->address>>1;
        if ( SDK2_I2cWrite(i2c->SDK2_i2c_Chip, 0x00, pucBuffer , iNbBytes + i2c->indexSize) != 0 ) {
          write_error++;
        } else {
          nbWrittenBytes = iNbBytes + i2c->indexSize;
        }
     #endif
        break;        
#endif /* LINUX_ST_SDK2_I2C */
    case CUSTOMER:
      nbWrittenBytes = 0;
        /* <porting> Insert here whatever is needed to
        (option 1)
        write iNbBytes bytes
        to the chip whose i2c address is i2c->address,
        starting at index iI2CIndex,
        with an index on i2c->indexSize bytes
        the data bytes being stored in pucDataBuffer.

        (option 2)
        Another option is to
        write iNbBytes + i2c->indexSize bytes
        to the chip whose i2c address is i2c->address,
        the index bytes and data bytes all being stored in pucBuffer.

        Make it such that on success nbWrittenBytes = iNbBytes + i2c->indexSize
        and on failure write_error is incremented.
        */        
        nbWrittenBytes = iNbBytes;

        if (HI_UNF_DEMOD_DEV_TYPE_3130E == g_stTunerOps[i2c->u32TunerId].enDemodDevType ||
        HI_UNF_DEMOD_DEV_TYPE_3130I == g_stTunerOps[i2c->u32TunerId].enDemodDevType)
        {
            qam_config_i2c_out (i2c->u32TunerId, 1);
            if (i2c->u32I2cChannel < HI_STD_I2C_NUM)
            {
                s32Ret = HI_DRV_I2C_Write(i2c->u32I2cChannel, i2c->address, pArray[0], 0, pArray, iNbBytes);
            }
            else
            {
                s32Ret = HI_DRV_GPIOI2C_WriteExt(i2c->u32I2cChannel, i2c->address, pArray[0], 0, pArray, iNbBytes);
                if (HI_SUCCESS == s32Ret)
                {
                    break;
                }
            }
        }
#if defined (DEMOD_DEV_TYPE_HI3137)
        else  if (HI_UNF_DEMOD_DEV_TYPE_3137 == g_stTunerOps[i2c->u32TunerId].enDemodDevType)
        {
            hi3137_config_i2c_out(i2c->u32TunerId);
            if (i2c->u32I2cChannel < HI_STD_I2C_NUM)
            {
            s32Ret = HI_DRV_I2C_Write(i2c->u32I2cChannel, i2c->address, pArray[0], 0, pArray, iNbBytes);
            }
            else
            {
            s32Ret = HI_DRV_GPIOI2C_WriteExt(i2c->u32I2cChannel, i2c->address, pArray[0], 0, pArray, iNbBytes);
            if (HI_SUCCESS == s32Ret)
            {
            break;
            }
            }
            hi3137_config_i2c_close(i2c->u32TunerId);
        }
#endif
        else
        {
            if (i2c->channel < HI_STD_I2C_NUM)
            {
                s32Ret = HI_DRV_I2C_Write(i2c->channel, i2c->address, iI2CIndex, i2c->indexSize, pucDataBuffer, iNbBytes);
                if (HI_SUCCESS != s32Ret)
                {
                    //HI_ERR_TUNER("HI_DRV_I2C_Write err:0x%x.\n",s32Ret);
                }            
            }
            else
            {
                s32Ret = HI_DRV_GPIOI2C_WriteExt(i2c->channel, i2c->address, iI2CIndex, i2c->indexSize, pucDataBuffer, iNbBytes);
                if (HI_SUCCESS != s32Ret)
                {
                    //HI_ERR_TUNER("HI_DRV_GPIOI2C_WriteExt err:0x%x.\n",s32Ret);
                }
            }
     	}
        break;
    case LINUX_I2C:
        #ifdef    LINUX_I2C_Capability
          if ((iNbBytes + i2c->indexSize) == Linux_I2C_writeByte (i2c->adapter_nr, i2c->address>>1, iNbBytes + i2c->indexSize, pucBuffer))
          {
            nbWrittenBytes = iNbBytes + i2c->indexSize;
          }
          else
          {
            write_error++;
          }
        #endif /* LINUX_I2C_Capability */
        break;
    case SIMU:
      nbWrittenBytes = L0_SimulatorWrite(i2c->indexSize, (iNbBytes + i2c->indexSize), pucBuffer);
      break;
    default:
      break;
  }
#ifdef    SiTRACES
  trace_skip_info = 1;
  if (i2c->trackWrite     == 1) {
    sprintf(trace_L0_message, "writing 0x%02x ",i2c->address);
    if (i2c->indexSize) {
      sprintf(trace_L0_message, "%sat", trace_L0_message);
      for (i=0;i<i2c->indexSize;i++) {
        r = 8*(i2c->indexSize -1 -i);
        if (i2c->indexSize) sprintf(trace_L0_message, "%s 0x%02x", trace_L0_message, ((iI2CIndex & (0xff<<r))>> r)&0xff );
      }
    }
    sprintf(trace_L0_message, "%s %s>", trace_L0_message, L0_InterfaceType(i2c));
    if (write_error) { sprintf(trace_L0_message, "%s WRITE ERROR! (", trace_L0_message); }
      for ( i=0 ; i < iNbBytes ; i++ ) {
      sprintf(trace_L0_message, "%s 0x%02x", trace_L0_message, pucDataBuffer[i]);
      }
    if (write_error) { sprintf(trace_L0_message, "%s )", trace_L0_message); }
    SiTRACE("%s\n", trace_L0_message);
  }
  trace_skip_info = 0;
#endif /* SiTRACES */
  if (write_error) return 0;
  return nbWrittenBytes - i2c->indexSize;
}
/************************************************************************************************************************
  L0_ReadCommandBytes function
  Use:        'command mode' bytes reading function
              Used to read a given number of bytes from the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the indexSize is always 0 and the index is always 0x00
  Parameters: i2c, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to read.
              *pucDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
************************************************************************************************************************/
int     L0_ReadCommandBytes  (L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer) {
  int res;
  res = L0_ReadBytes (i2c, 0x00, iNbBytes, pucDataBuffer);
  return res;
}
/************************************************************************************************************************
  L0_WriteCommandBytes function
  Use:        'command mode' bytes writing function
              Used to write a given number of bytes to the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the indexSize is always 0 and the index is always 0x00
  Parameters: i2c, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to write.
              *pucDataBuffer, a pointer to a buffer containing the bytes.
  Returns:    the number of bytes written.
************************************************************************************************************************/
int     L0_WriteCommandBytes (L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer) {
  int res;
  res = L0_WriteBytes(i2c, 0x00, iNbBytes, pucDataBuffer);
  return res;
}
/************************************************************************************************************************
  L0_ReadRawBytes function
  Use:        raw i2c read function
              Used to read a given number of bytes from the Layer 1 instance while managing the indexSize at this level.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to read.
              iNbBytes, the number of bytes to read.
              *pbtDataBuffer, a pointer to a buffer used to store the bytes.
  Comment:    This function splits a 'read' operation in
              1- 'writing' the chip's i2c adress plus the index bytes
              2- 'reading' iNbBytes bytes from the chip
  Porting:    Can be used to manage the 16 bit case at this level
  Returns:    the number of bytes read.
************************************************************************************************************************/
int     L0_ReadRawBytes      (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pbtDataBuffer) {
  int i,r,ret;
  unsigned char pbtIndexBuffer [2];
  rawI2C->address        = i2c->address;
  rawI2C->trackRead      = i2c->trackRead;
  rawI2C->trackWrite     = i2c->trackWrite;
  rawI2C->connectionType = i2c->connectionType;
  if (i2c->indexSize >0) {
    for (i=0;i<i2c->indexSize;i++) {
      r = 8*(i2c->indexSize -1 -i);
      pbtIndexBuffer[i] = (unsigned char)((iI2CIndex & (0xff<<r) ) >> r);
    }
    /* First write the index bytes (if any) */
    ret = L0_WriteBytes(rawI2C, 0, i2c->indexSize, pbtIndexBuffer);
    if (ret == 0) return 0; /* There has been a communication error, do not attempt to read */
  }
  /* Now read the data bytes */
  ret = L0_ReadBytes (rawI2C, 0, iNbBytes, pbtDataBuffer);
  return ret;
}
/************************************************************************************************************************
  L0_WriteRawBytes function
  Use:        raw i2c write function
              Used to write a given number of bytes from the Layer 1 instance while managing the indexSize at this level.
  Parameters: i2c, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first byte to write.
              iNbBytes, the number of bytes to write.
              *pbtDataBuffer, a pointer to a buffer containing the bytes.
  Porting:    Can be used to manage the 16 bit case at this level
  Returns:    the number of bytes written.
************************************************************************************************************************/
int     L0_WriteRawBytes     (L0_Context* i2c, unsigned int iI2CIndex, int iNbBytes, unsigned char *pbtDataBuffer) {
  int i,r,ret;
  unsigned char *pbtBuffer;
  unsigned char myBufferBytes[iNbBytes + i2c->indexSize];
  rawI2C->address        = i2c->address;
  rawI2C->trackRead      = i2c->trackRead;
  rawI2C->trackWrite     = i2c->trackWrite;
  rawI2C->connectionType = i2c->connectionType;
  pbtBuffer = &myBufferBytes[0];
  /* Store the index bytes in the first bytes of the write buffer */
  for (i=0;i<i2c->indexSize;i++) {
      r = 8*(i2c->indexSize -1 -i);
      pbtBuffer [i] = (unsigned char)((iI2CIndex & (0xff<<r) ) >> r);
  }
  /* Store the data bytes following the index bytes */
  for (i=i2c->indexSize; i< i2c->indexSize+iNbBytes;i++) {
      pbtBuffer[i] = pbtDataBuffer[i - i2c->indexSize];
  }
  /* Write all bytes as a single buffer */
  ret = L0_WriteBytes (rawI2C, 0, iNbBytes + i2c->indexSize, pbtBuffer) - i2c->indexSize;
  return ret;
}
/************************************************************************************************************************
  L0_ReadRegister function
  Use:        register read function
              Used to read a register based on its address, size, offset
  Parameter:  add              register address
  Parameter:  offset           register offset
  Parameter:  nbbit            register size in bits
  Parameter:  isSigned         register sign info
  Behavior:          This function uses the characteristics of the register to read its value from hardware
                       it reads the minimum number of bytes required to retrieve the register based on the number of bits and the offset
                       it masks all bits not belonging to the register before returning
                       it handles the sign-bit propagation for signed registers
  Returns: the value read. O if error during the read
************************************************************************************************************************/
long    L0_ReadRegister      (L0_Context *i2c, unsigned int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned int isSigned) {
  int iNbBytes, i, nbReadBytes, iNbPrefixBitsToCancel;
  long iVal;
  unsigned char  prefixByte, postfixByte;
  unsigned char  registerDataBuffer[8];
  iNbBytes = (nbbit + offset + 7)/8;
  if ( iNbBytes < 1 ) {SiERROR("iNbBytes < 1 ! Check your input parameters to L0_ReadRegister!\n"); return 0;} /* fool proofing against call with wrong parameters */
  if (i2c->mustReadWithoutStop==0) {
    nbReadBytes = L0_ReadRawBytes(i2c    , iI2CIndex, iNbBytes, registerDataBuffer);
  } else {
    nbReadBytes = L0_ReadBytes   (i2c    , iI2CIndex, iNbBytes, registerDataBuffer);
  }
  if (nbReadBytes != iNbBytes) {
    return 0;
  }
  iVal = 0;
  for (i = 0; i < iNbBytes; i++) {iVal = iVal + ( registerDataBuffer[i] << (8*(i)));}

  prefixByte  = registerDataBuffer[iNbBytes - 1];
  iNbPrefixBitsToCancel = 8*(iNbBytes) - nbbit - offset;
  prefixByte  = prefixByte  >> (8 - iNbPrefixBitsToCancel);
  prefixByte  = prefixByte  << (8 - iNbPrefixBitsToCancel);
  postfixByte = registerDataBuffer[0];
  postfixByte = postfixByte << (8 - offset);
  postfixByte = postfixByte >> (8 - offset);

  iVal = -( prefixByte << (8*(iNbBytes - 1))) + ( iVal ) - postfixByte ;

  /* sign bit propagation, if required */
  if (isSigned) {
    iVal = (long)iVal >> offset;
    iVal = (long)iVal << (32-nbbit);
    iVal = (long)iVal >> (32-nbbit);
  } else {
    iVal = (unsigned long)iVal >> offset;
  }

  return iVal;
}
/************************************************************************************************************************
  L0_WriteRegister function
  Use:        register write function
              Used to write a register based on its address, size, offset
  Parameter:  add              register address
  Parameter:  offset           register offset
  Parameter:  nbbit            register size in bits
  Parameter:  alone            register loneliness info (1 if all other bits can be overwritten without checking)
  Parameter:  Value            the required value for the register
  Behavior:          This function uses all characteristics of the register to write its value in the hardware
                       if the required value is out of range, no operation is performed and an error code is returned
                       before writing, the current register value is retrieved (if required because of adjacent registers),
                          in order to preserve the contain of adjacent registers
                       it reads the minimum number of bytes required to retrieve the register based on:
                          the number of bits and the offset
                       it keeps all bits not belonging to the register intact
                       it handles the sign-bit propagation for signed registers
  Returns: the value written. O if error during the write
************************************************************************************************************************/
long    L0_WriteRegister     (L0_Context *i2c, unsigned int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned char alone, long Value) {
  unsigned int  iNbBytes, i,nbWrittenBytes, iNbPrefixBitsToCancel, nbReadBytes;
  unsigned long iVal;
  unsigned char prefixByte, postfixByte;
  unsigned char registerDataBuffer[8];
  iNbBytes = (nbbit + offset + 7)/8;
  if ( iNbBytes < 1 ) {SiERROR("iNbBytes < 1 ! Check your input parameters to L0_WriteRegister!\n"); return 0;} /* fool proofing against call with wrong parameters */
  iNbPrefixBitsToCancel = 8*(iNbBytes) - nbbit - offset;
  /* removing sign-propagation bits for negative values of signed registers */
  Value = (unsigned long)Value << iNbPrefixBitsToCancel;
  Value = (unsigned long)Value >> iNbPrefixBitsToCancel;
  if (((iNbBytes*8 == nbbit) && (offset == 0)) || ((alone == 1))) {
    /*  If the register is the only one using the related bytes, do not read it before setting bits */
    iVal = (unsigned long)Value << offset;
  } else {
    /*  If the bytes are used by other registers, read them before setting register-specific bits */
    if (i2c->mustReadWithoutStop==0) {
      nbReadBytes = L0_ReadRawBytes(i2c    , iI2CIndex, iNbBytes, registerDataBuffer);
    } else {
      nbReadBytes = L0_ReadBytes   (i2c    , iI2CIndex, iNbBytes, registerDataBuffer);
    }

    if (nbReadBytes != iNbBytes) { return 0; }

    prefixByte  = registerDataBuffer[iNbBytes-1];
    prefixByte  = prefixByte  >> (8 - iNbPrefixBitsToCancel);
    prefixByte  = prefixByte  << (8 - iNbPrefixBitsToCancel);

    postfixByte = registerDataBuffer[0];
    postfixByte = postfixByte << (8 - offset);
    postfixByte = postfixByte >> (8 - offset);

    iVal = ( prefixByte << (8*(iNbBytes - 1))) + ( (unsigned long)Value << offset ) + postfixByte ;
  }

  for (i = 0 ; i < iNbBytes; i++ ) {registerDataBuffer[i] = (unsigned char)(iVal >> 8*(i));}

  nbWrittenBytes = L0_WriteBytes(i2c, iI2CIndex, iNbBytes, registerDataBuffer);
  if (nbWrittenBytes != iNbBytes) {SiTRACE("nbWrittenBytes != iNbBytes\n"); return 0;}
  return Value;
}
/************************************************************************************************************************
  L0_ReadRegisterTrace function
  Use:         trace and read function
               Used to read a register based on its address, size, offset, with traces
  Parameter:    add              register address
  Parameter:    offset           register offset
  Parameter:    nbbit            register size in bits
  Behavior:          This function traces the register information, then calls L1_ReadRegister with all the register parameters
                     It is used only when tracing register reads is required
  Comments: generally activated by changing the definition of the CONTEXT_READ function in the proper header file
  Returns: the value written. O if error during the write
************************************************************************************************************************/
long    L0_ReadRegisterTrace (L0_Context *i2c, char* name, unsigned int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned int isSigned) {
  long res = L0_ReadRegister (i2c, iI2CIndex, offset, nbbit, isSigned);
#ifdef    SiTRACES
  unsigned int iNbBytes;
  trace_skip_info = 1;
  iNbBytes = (nbbit + offset + 7)/8;
  sprintf(trace_L0_message, " << READ  %-30s       : %4ld (0x%04lx)", name, res, res);
  sprintf(trace_L0_message, "%s  @[0x%0x:%d", trace_L0_message, iI2CIndex+iNbBytes-1, (offset+nbbit-1)%8);
    if (iNbBytes == 1) {
     if (nbbit ==1) { sprintf(trace_L0_message, "%s]\n", trace_L0_message);
     } else         { sprintf(trace_L0_message, "%s-%d]\n", trace_L0_message, offset);
       }
  } else            { sprintf(trace_L0_message, "%s]-[0x%0x:%d]\n", trace_L0_message, iI2CIndex, offset);}
  SiTRACE("%s",trace_L0_message);
  trace_skip_info = 0;
#else
  name = name; /*to avoid compiler warning */
#endif /* SiTRACES */
  return res;
}
/************************************************************************************************************************
  L0_WriteRegisterTrace function
  Use:        register write and trace function
              Used to write a register based on its address, size, offset, with traces
  Parameter:  add              register address
  Parameter:  offset           register offset
  Parameter:  nbbit            register size in bits
  Parameter:  alone            register loneliness info (1 if all other bits can be overwritten without checking)
  Parameter:  Value            the required value for the register
  Behavior:          This function traces the register information, then calls L1_WriteRegister with all the register parameters
                     It is used only when tracing register writes is required
  Comments: generally activated by changing the definition of the CONTEXT_WRITE function in the proper header file
  Returns: the value written. O if error during the write
************************************************************************************************************************/
long    L0_WriteRegisterTrace(L0_Context *i2c, char* name, char* valtxt, unsigned int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned char alone, long Value) {
  long res;
#ifdef    SiTRACES
  unsigned int iNbBytes;
  iNbBytes = (nbbit + offset + 7)/8;
  trace_skip_info = 1;
  sprintf(trace_L0_message, " >> WRITE %-20s %-25s : %ld (0x%04x)", name, valtxt, Value, (int)Value);
  sprintf(trace_L0_message, "%s  @[0x%0x:%d", trace_L0_message, iI2CIndex+iNbBytes-1, (offset+nbbit-1)%8);
  if (iNbBytes == 1) {
      if (nbbit ==1) { sprintf(trace_L0_message, "%s]\n", trace_L0_message);
      } else         { sprintf(trace_L0_message, "%s-%d]\n", trace_L0_message, offset);
      }
  } else             { sprintf(trace_L0_message, "%s]-[0x%0x:%d]\n", trace_L0_message, iI2CIndex, offset); }
  SiTRACE("%s",trace_L0_message);
  trace_skip_info = 0;
#else
  name   = name;   /*to avoid compiler warning */
  valtxt = valtxt; /*to avoid compiler warning */
#endif /* SiTRACES */
  res = L0_WriteRegister (i2c, iI2CIndex, offset, nbbit, alone, Value);
  return res;
}
/************************************************************************************************************************
  L0_ReadString function
  Use:        L0 generic read function
              Used to read bytes based on a string input
  Behavior:   Split the input string in tokens (separated by 'space') and read the corresponding bytes
              The chip address is the first byte
              The number of bytes to read is equal to the last token
              The index size if the number of tokens - 2
  Example:    'L0_ReadString (i2c, "0xC8 0x12 0x34 5", pbtDataBuffer);' will read 5 bytes from the chip at address 0xc8 starting from index 0x1234
               0xC8 0x12 0x34  5
                |   ---------  |
                |       |      ----> 5 bytes to read
                |       -----------> index 0x1234 (on 2 bytes)
                -------------------> address = 0xc8
  Example:    'L0_ReadString (i2c, "0xA0 0x00 5"     , pbtDataBuffer);' will read 5 bytes from the chip at address 0xA0 starting from index 0x00 (This will return the content of the Cypress eeprom)
  Example:    'L0_ReadString (i2c, "0xC0 1"          , pbtDataBuffer);' will read 1 byte  from the chip at address 0xC0 (This will return the status byte for a command-mode chip)
  Returns:    The number of bytes written
************************************************************************************************************************/
int     L0_ReadString        (L0_Context* i2c, char *readString, unsigned char *pbtDataBuffer) {
    int i;
    int readBytes;
    int loop;
    int nbArgs;
    int indexSize;
    unsigned int address;
    unsigned int uintval;
    unsigned int hexval;
    char *input;
    char *array[50];
    int   bytes[50];
    unsigned int   iI2CIndex;
    int            iNbBytes;

    if (pbtDataBuffer == NULL) {
     SiTRACE("L0_ReadString can not store bytes in NULL buffer!\n");
     return 0;
    }

    input = readString;

    /* strtok splitting input and storing all items, returning first item */
#ifdef    LINUX_ST_SDK2_I2C
    array[0] = strsep(&input," ");
#else  /* LINUX_ST_SDK2_I2C */
    array[0] = strtok(input," ");
#endif /* LINUX_ST_SDK2_I2C */
    if(array[0]==NULL) {return 0;}
    /* retrieving all remaining items */
    for(loop=1;loop<50;loop++) {
#ifdef    LINUX_ST_SDK2_I2C
        array[loop] = strsep(&input," ");
#else  /* LINUX_ST_SDK2_I2C */
        array[loop] = strtok(NULL," ");
#endif /* LINUX_ST_SDK2_I2C */
        if(array[loop]==NULL) break;
    }
    nbArgs = loop;
    /* scanning arguments, allowing decimal or hexadecimal input */
    for(loop=0;loop<nbArgs;loop++) {
        hexval=0;
        sscanf(array[loop],"%u", &uintval);
        if (!uintval) sscanf(array[loop],"%x", &hexval);
        bytes[loop] = hexval + uintval;
    }

    address   = bytes[0];
    indexSize = nbArgs - 2;
    if (indexSize <0) return 0;
    iI2CIndex = 0;
    for (i=1; i<= indexSize; i++) {
      iI2CIndex = (iI2CIndex<<8) + bytes[i];
    }
    iNbBytes  = bytes[loop-1];

    L0_SetAddress   (i2c, address, indexSize);

/*    SiTRACE("L0_ReadString address 0x%02x, index 0x%02x (on %d bytes), %d bytes\n", address, iI2CIndex, indexSize, iNbBytes); */

    readBytes = L0_ReadBytes (i2c, iI2CIndex, iNbBytes, pbtDataBuffer);

    return readBytes;
}
/************************************************************************************************************************
  L0_WriteString function
  Use:        L0 generic write function
              Used to write bytes based on a string input
  Behavior:   Split the input string in tokens (separated by 'space') and write the corresponding bytes
              The chip address is the first byte
              The number of bytes to write is equal to the number of tokens -1
  Example:    'L0_WriteString (i2c, "0xC8 0x12 0x34 0x37");' will write '0x37' at index 0x1234 in the chip at address 0xc8
  Returns:    The number of bytes written
************************************************************************************************************************/
int     L0_WriteString       (L0_Context* i2c, char *writeString) {
#ifndef    LINUX_ST_SDK2_I2C
    int i;
#endif /* LINUX_ST_SDK2_I2C */
    int writeBytes;
    int loop;
    int nbArgs;
    int indexSize;
    unsigned int address;
    unsigned int uintval;
    unsigned int hexval;
    char *input;
    unsigned char  ucBuffer[100];
    char *array[50];
    int  bytes[50];
    unsigned int iI2CIndex;
    int iNbBytes;
    unsigned char *pbtDataBuffer;

    pbtDataBuffer = (unsigned char*)&ucBuffer;

    input = writeString;

    /* strtok splitting input and storing all items, returning first item */
#ifdef    LINUX_ST_SDK2_I2C
    array[0] = strsep(&input," ");
#else  /* LINUX_ST_SDK2_I2C */
    array[0] = strtok(input," ");
#endif /* LINUX_ST_SDK2_I2C */
    if(array[0]==NULL) {return 0;}
    /* retrieving all remaining items */
    for(loop=1;loop<50;loop++) {
#ifdef    LINUX_ST_SDK2_I2C
        array[loop] = strsep(&input," ");
#else  /* LINUX_ST_SDK2_I2C */
        array[loop] = strtok(NULL," ");
#endif /* LINUX_ST_SDK2_I2C */
        if(array[loop]==NULL) break;
    }
    nbArgs = loop;
    /* scanning arguments, allowing decimal or hexadecimal input */
    for(loop=0;loop<nbArgs;loop++) {
        hexval=0;
        sscanf(array[loop],"%u", &uintval);
        if (!uintval) sscanf(array[loop],"%x", &hexval);
        bytes[loop] = hexval + uintval;
    }

    address   = bytes[0];
    indexSize = 0;
    iI2CIndex = 0;
    iNbBytes  = nbArgs-1;
#ifndef   LINUX_ST_SDK2_I2C
    pbtDataBuffer = (unsigned char*)malloc(sizeof(unsigned char)*iNbBytes);
    for (i=0; i<iNbBytes; i++) { pbtDataBuffer[i] = bytes[i+1]; }
    L0_SetAddress   (i2c, address, indexSize);
    writeBytes = L0_WriteBytes (i2c, iI2CIndex, iNbBytes, pbtDataBuffer);
#endif /* LINUX_ST_SDK2_I2C */
    return writeBytes;
}
const char*   Si_I2C_TAG_TEXT      (void) { return (char *)"V5.0.4"; }
/************************************************************************************************************************
  L0_FastI2C  function
  Use:        function to set the i2c speed
              Used to set the speed of the i2c interface to 'fast'
              The initial version only manages the Cypress Interface chip, which has only 2 possible speeds
  Returns:    1
************************************************************************************************************************/
int     L0_FastI2C           (void) {
#ifdef    USB_Capability
  double        retdval;
  char rettxtBuffer[256];
  char *rettxt;
  rettxt = rettxtBuffer;
  Cypress_Configure((char*)"-i2c" ,(char*)"400khz", 0 , &retdval, &rettxt);
#endif /* USB_Capability */
  return 1;
}
/************************************************************************************************************************
  L0_SlowI2C  function
  Use:        function to set the i2c speed
              Used to set the speed of the i2c interface to 'slow'
              The initial version only manages the Cypress Interface chip, which has only 2 possible speeds
  Returns:    1
************************************************************************************************************************/
int     L0_SlowI2C           (void) {
#ifdef    USB_Capability
  double        retdval;
  char rettxtBuffer[256];
  char *rettxt;
  rettxt = rettxtBuffer;
  Cypress_Configure((char*)"-i2c" ,(char*)"100khz", 0 , &retdval, &rettxt);
#endif /* USB_Capability */
  return 1;
}
/************************************************************************************************************************
  L0_EnableSPI function
  Use:        SPI enable function
              Used to allow sending a series of bytes over SPI

  Porting:Needs to be completed to match the SPI HW. Initially suppoting only the Cypress chip.

  Parameters: SPI_config. One byte used to select with the cypress chip the initial port A (OEA) enable configuration

  Returns:    1 if OK, 0 if SPI is not available
************************************************************************************************************************/
int     L0_EnableSPI         (unsigned char SPI_config) {
  int res;
#ifdef   USB_Capability
  #ifdef   CYPRESS_SPI_Capability
    return 1;
  #endif /* CYPRESS_SPI_Capability */
#endif /* USB_Capability */
  SPI_config = SPI_config;
  res = 0;
  /* <porting> Insert here whatever is needed to
  enable SPI transfer between the host and the part,
  such as host pins enable, etc.
  */
  return res;
}
/************************************************************************************************************************
  L0_LoadSPIoverPortA function
  Use:        SPI download function
              Used to send a series of bytes as in SPI over Port A

  Porting:Needs to be completed to match the SPI HW. Initially supporting only the Cypress chip.

  Parameters:   SPI_data, the buffer containing the SPI bytes to send.
                length, the number of bytes to send
                index, a byte used with the Cypress Chip to select the pins used for spi_clk and spi_data in the Cypress:
                    0x01 : SPI Data on PA_0, SPI clock on PA_1
                    0x10 : SPI Data on PA_1, SPI clock on PA_0
                    0x02 : SPI Data on PA_0, SPI clock on PA_2
                    0x20 : SPI Data on PA_2, SPI clock on PA_0
                    0x12 : SPI Data on PA_1, SPI clock on PA_2
                    0x21 : SPI Data on PA_2, SPI clock on PA_1

  Returns:    0 if OK, otherwise an error code
************************************************************************************************************************/
int     L0_LoadSPIoverPortA  (unsigned char *SPI_data, unsigned char  length, unsigned short index) {
  int res;
  SPI_data = SPI_data;
  length   = length;
  index    = index;
  res = 0;
#ifdef   USB_Capability
  #ifdef   CYPRESS_SPI_Capability
  if ( Cypress_USB_LoadSPIoverPortA (SPI_data, length, index) != 1 ) {res = 0;}
  #endif /* CYPRESS_SPI_Capability */
#endif /* USB_Capability */
  return res;
}
/* Re-definition of SiTRACE for L0_LoadSPIoverGPIF */
#ifdef    SiTRACES
  #undef  SiTRACE
  #define SiTRACE(...)        SiTraceFunction(SiLEVEL, "GPIF  SPI", __FILE__, __LINE__, __func__     ,__VA_ARGS__)
#endif /* SiTRACES */
/************************************************************************************************************************
  L0_LoadSPIoverGPIF function
  Use:        SPI download function using Cypress GPIF pins
              Used to send a series of bytes over SPI on the GPIF pins

  Porting:Needs to be completed to match the SPI HW. Initially supporting only the Cypress chip.

  Parameters:   SPI_data, the buffer containing the SPI bytes to send.
                length, the number of bytes to send

  Returns:    0 if OK, otherwise an error code
************************************************************************************************************************/
int     L0_LoadSPIoverGPIF   (unsigned char *SPI_data, int  length) {
  int res;
  SiTRACE("L0_LoadSPIoverGPIF length %d\n", length);
  if (length <= 16) {
    for (res = 0;        res < length; res++) {SiTRACE("0x%02x ", SPI_data[res]);}
  } else {
    for (res = 0;        res <      8; res++) {SiTRACE("0x%02x ", SPI_data[res]);}
    SiTRACE("...%6d bytes ... ", length);
    for (res = length-8; res < length; res++) {SiTRACE("0x%02x ", SPI_data[res]);}
  }
  SiTRACE("\n");
  SPI_data = SPI_data;
  res = 1;
#ifdef   USB_Capability
  #ifdef   CYPRESS_SPI_Capability
    res  =   Cypress_USB_LoadSPIoverGPIF  (SPI_data, length);
             Cypress_USB_LoadSPIwaitDONE(10000);
  #endif /* CYPRESS_SPI_Capability */
#endif /* USB_Capability */
  return res;
}
/* Re-definition of SiTRACE for L0_Context */
#ifdef    SiTRACES
  #undef  SiTRACE
  #define SiTRACE(...)        SiTraceFunction(SiLEVEL, i2c->tag, __FILE__, __LINE__, __func__     ,__VA_ARGS__)
#endif /* SiTRACES */

/************************************************************************************************************************
  L0_DisableSPI function
  Use:        SPI disable function
              Used to disable sending bytes over SPI

  Porting:Needs to be completed to match the SPI HW. Initially suppoting only the Cypress chip.

  Returns:    1 if OK, 0 if SPI is not available
************************************************************************************************************************/
int     L0_DisableSPI        (void) {
  int res;
  res = 0;
  return res;
}

#ifdef    USB_Capability
/************************************************************************************************************************
  L0_Cypress_Process function
  Use:        Cypress chip command channel function
              Used to send a generic command to the Cypress chip via the CypressUSB dll.
  Comment:    The cypress chip commands are defined in the underlying Cypress USB dll, and are not relevant to non-Windows cases or when the i2c layer is not using the Cypress chip (after porting).
  Returns:    1 if the command is unknow
  Porting:    If not using the Cypress Fx2LP USB interface, comment the USB_Capability flag to avoid compiling this function
************************************************************************************************************************/
int     L0_Cypress_Process   (const char *cmd, const char *text, double dval, double *retdval, char **rettxt) {
  sprintf(*rettxt, "returning from the '%s' command",cmd);
  return Cypress_USB_Command ((char*)cmd, (char*)text, dval, retdval, rettxt);
}
/************************************************************************************************************************
  L0_Cypress_VendorCmd function
  Use:        Cypress chip vendor command generic 'write' function
              Used to send a vendor 'write' command to the Cypress chip.
  Comment:    The cypress chip commands are defined in the underlying Cypress USB dll, and are not relevant to non-Windows cases or when the i2c layer is not using the Cypress chip (after porting).
  Returns:    1 if the command is unknow
  Porting:    If not using the Cypress Fx2LP USB interface, comment the USB_Capability flag to avoid compiling this function
************************************************************************************************************************/
int     L0_Cypress_VendorCmd (unsigned char  ucVendorCode, unsigned short value, unsigned short index, unsigned char * byteBuffer, int   len) {
  return Cypress_USB_VendorCmd (ucVendorCode, value, index, byteBuffer, len);
}
/************************************************************************************************************************
  L0_Cypress_VendorRead function
  Use:        Cypress chip vendor command generic 'read' function
              Used to send a vendor 'read' command to the Cypress chip.
  Comment:    The cypress chip commands are defined in the underlying Cypress USB dll, and are not relevant to non-Windows cases or when the i2c layer is not using the Cypress chip (after porting).
  Returns:    1 if the command is unknow
  Porting:    If not using the Cypress Fx2LP USB interface, comment the USB_Capability flag to avoid compiling this function
************************************************************************************************************************/
int     L0_Cypress_VendorRead(unsigned char  ucVendorCode, unsigned short value, unsigned short index, unsigned char * byteBuffer, int *plen) {
  return Cypress_USB_VendorRead (ucVendorCode, value, index, byteBuffer, plen);
}
/************************************************************************************************************************
  L0_Cypress_Configure function
  Use:        Cypress chip configuration function
              Used to send a configuration command to the Cypress chip.
  Comment:    The cypress chip commands are defined in the underlying Cypress USB dll, and are not relevant to non-Windows cases or when the i2c layer is not using the Cypress chip (after porting).
  Returns:    1 if the command is unknown
  Porting:    If not using the Cypress Fx2LP USB interface, comment the USB_Capability flag to avoid compiling this function
************************************************************************************************************************/
int     L0_Cypress_Configure (const char *cmd, const char *text, double dval, double *retdval, char **rettxt) {
  sprintf(*rettxt, "returning from the '%s' command",cmd);
  Cypress_Configure ((char*)cmd, (char*)text, dval, retdval,rettxt);
  return 1;
}
/************************************************************************************************************************
  L0_Cypress_Cget function
  Use:        Cypress chip configuration retrieval function
              Used to send a configuration info request to the Cypress chip.
  Comment:    The cypress chip commands are defined in the underlying Cypress USB dll, and are not relevant to non-Windows cases or when the i2c layer is not using the Cypress chip (after porting).
  Returns:    1 if the command is unknow
  Porting:    If not using the Cypress Fx2LP USB interface, comment the USB_Capability flag to avoid compiling this function
************************************************************************************************************************/
int     L0_Cypress_Cget      (const char *cmd, const char *text, double dval, double *retdval, char **rettxt) {
  sprintf(*rettxt, "returning from the '%s' command",cmd);
  Cypress_Cget ((char*)cmd, (char*)text, dval, retdval, rettxt);
  return 1;
}
#endif /* USB_Capability */
#ifdef    __cplusplus
}
#endif /* __cplusplus */
