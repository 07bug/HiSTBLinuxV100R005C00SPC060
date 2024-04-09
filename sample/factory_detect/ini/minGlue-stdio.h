/*  Glue functions for the minIni library, based on the C/C++ stdio library
 *
 *  Or better said: this file contains macros that maps the function interface
 *  used by minIni to the standard C/C++ file I/O functions.
 *
 *  Copyright (c) CompuPhase, 2008-2012
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy
 *  of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  License for the specific language governing permissions and limitations
 *  under the License.
 */

/* map required file I/O types and functions to the standard C library */
#include <stdio.h>

#define INI_FILETYPE                  FILE*
#define ini_openread(filename,file)   ((*(file) = fopen((filename),"rb")) != NULL)
#define ini_openwrite(filename,file)  ((*(file) = fopen((filename),"wb")) != NULL)
#define ini_close(file)               (fclose(*(file)) == 0)
#define ini_read(buffer,size,file)    (fgets((buffer),(size),*(file)) != NULL)
#define ini_write(buffer,file)        (fputs((buffer),*(file)) >= 0)
#define ini_rename(source,dest)       (rename((source), (dest)) == 0)
#define ini_remove(filename)          (remove(filename) == 0)

#define INI_FILEPOS                   fpos_t
#define ini_tell(file,pos)            (fgetpos(*(file), (pos)) == 0)
#define ini_seek(file,pos)            (fsetpos(*(file), (pos)) == 0)

/* for floating-point support, define additional types and functions */
#define INI_REAL                      float
#define ini_ftoa(string,value)        sprintf((string),"%f",(value))
#define ini_atof(string)              (INI_REAL)strtod((string),NULL)
