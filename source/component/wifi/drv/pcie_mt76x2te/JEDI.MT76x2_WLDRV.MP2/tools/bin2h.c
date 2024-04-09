/*
  * Copyright (c) 2016 MediaTek Inc.  All rights reserved.
  *
  * This software is available to you under a choice of one of two
  * licenses.  You may choose to be licensed under the terms of the GNU
  * General Public License (GPL) Version 2, available from the file
  * COPYING in the main directory of this source tree, or the
  * BSD license below:
  *
  *     Redistribution and use in source and binary forms, with or
  *     without modification, are permitted provided that the following
  *     conditions are met:
  *
  *      - Redistributions of source code must retain the above
  *        copyright notice, this list of conditions and the following
  *        disclaimer.
  *
  *      - Redistributions in binary form must reproduce the above
  *        copyright notice, this list of conditions and the following
  *        disclaimer in the documentation and/or other materials
  *        provided with the distribution.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
  * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FIRMWARE_NAME_BUFFER_LENGTH 128
#define MAX_NAME_BUFFER_LENGTH 512
#define MAX_CHIPSETS_BUFFER_LENGTH 1024

int bin2h(char *infname, char *outfname, char *fw_name)
{
	int ret = 0;
    FILE *infile, *outfile;
	int c;
    int i=0;

    infile = fopen(infname,"r");

    if (infile == (FILE *) NULL) {
		printf("Can't read file %s \n",infname);
		return -1;
    }

    outfile = fopen(outfname,"w");

    if (outfile == (FILE *) NULL) {
		printf("Can't open write file %s \n",outfname);
		fclose(infile);
       	return -1;
    }

    fputs("/* AUTO GEN PLEASE DO NOT MODIFY IT */ \n",outfile);
    fputs("/* AUTO GEN PLEASE DO NOT MODIFY IT */ \n",outfile);
    fputs("\n",outfile);
    fputs("\n",outfile);

	fprintf(outfile, "UCHAR %s[] = {\n", fw_name);

    while(1) {
		char cc[3];

		c = getc(infile);

		if (feof(infile))
	   		break;

		memset(cc,0,2);

		if (i >= 16) {
	   		fputs("\n", outfile);
	   		i = 0;
		}

		fputs("0x", outfile);
		snprintf(cc, sizeof(cc), "%02x", c);
		fputs(cc, outfile);
		fputs(", ", outfile);
		i++;
    }

    fputs("} ;\n", outfile);
    fclose(infile);
    fclose(outfile);
	return 0;
}

int main(int argc ,char *argv[])
{
	char infname[MAX_NAME_BUFFER_LENGTH];
	char ine2pname[MAX_NAME_BUFFER_LENGTH];
	char in_rom_patch[MAX_NAME_BUFFER_LENGTH];
	char outfname[MAX_NAME_BUFFER_LENGTH];
	char oute2pname[MAX_NAME_BUFFER_LENGTH];
	char out_rom_patch[MAX_NAME_BUFFER_LENGTH];
	char chipsets[MAX_CHIPSETS_BUFFER_LENGTH];
	char fw_name[MAX_FIRMWARE_NAME_BUFFER_LENGTH];
	char e2p_name[MAX_FIRMWARE_NAME_BUFFER_LENGTH];
	char rom_patch_name[MAX_FIRMWARE_NAME_BUFFER_LENGTH];
    char *rt28xxdir;
    char *chipset, *token;
	char *wow, *rt28xx_mode;
	int is_bin2h_fw = 0, is_bin2h_rom_patch = 0, is_bin2h_e2p=0;

    rt28xxdir = (char *)getenv("RT28xx_DIR");
    chipset = (char *)getenv("CHIPSET");
	wow = (char *)getenv("HAS_WOW_SUPPORT");
	rt28xx_mode = (char *)getenv("RT28xx_MODE");

    if(!rt28xxdir) {
		printf("Environment value \"RT28xx_DIR\" not export \n");
	 	return -1;
    }

    if(!chipset) {
		printf("Environment value \"CHIPSET\" not export \n");
		return -1;
    }
	memcpy(chipsets, chipset, strlen(chipset));

	if (strlen(rt28xxdir) > (sizeof(infname)-100)) {
		printf("Environment value \"RT28xx_DIR\" is too long!\n");
		return -1;
	}

	chipset = strtok(chipsets, " ");

	while (chipset != NULL) {
		printf("chipset = %s\n", chipset);
		memset(infname, 0, MAX_NAME_BUFFER_LENGTH);
		memset(ine2pname, 0, MAX_NAME_BUFFER_LENGTH);
		memset(outfname, 0, MAX_NAME_BUFFER_LENGTH);
		memset(oute2pname, 0, MAX_NAME_BUFFER_LENGTH);
		memset(fw_name, 0, MAX_FIRMWARE_NAME_BUFFER_LENGTH);
		memset(e2p_name, 0, MAX_FIRMWARE_NAME_BUFFER_LENGTH);
		memset(in_rom_patch, 0, MAX_NAME_BUFFER_LENGTH);
		memset(out_rom_patch, 0, MAX_NAME_BUFFER_LENGTH);
		memset(rom_patch_name, 0, MAX_FIRMWARE_NAME_BUFFER_LENGTH);
		strncat(infname, rt28xxdir, MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
		strncat(ine2pname, rt28xxdir,
			MAX_NAME_BUFFER_LENGTH - strlen(ine2pname) - 1);
		strncat(in_rom_patch, rt28xxdir,
			MAX_NAME_BUFFER_LENGTH - strlen(in_rom_patch) - 1);
		strncat(outfname, rt28xxdir,
			MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
		strncat(oute2pname, rt28xxdir,
			MAX_NAME_BUFFER_LENGTH - strlen(oute2pname) - 1);
		strncat(out_rom_patch, rt28xxdir,
			MAX_NAME_BUFFER_LENGTH - strlen(out_rom_patch) - 1);
		is_bin2h_fw = 0;
		is_bin2h_rom_patch = 0;
		is_bin2h_e2p = 0;
		if (strncmp(chipset, "2860",4) == 0) {
			strncat(infname, "/mcu/bin/rt2860.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
			strncat(outfname, "/include/mcu/rt2860_firmware.h",
				MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
			strncat(fw_name, "RT2860_FirmwareImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			is_bin2h_fw = 1;
		} else if (strncmp(chipset, "2870",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
				strncat(infname, "/mcu/bin/rt2870_wow.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_wow_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_WOW_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			} else {
				strncat(infname, "/mcu/bin/rt2870.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			}
		} else if (strncmp(chipset, "3090",4) == 0) {
			strncat(infname, "/mcu/bin/rt2860.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
			strncat(outfname, "/include/mcu/rt2860_firmware.h",
				MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
			strncat(fw_name, "RT2860_FirmwareImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			is_bin2h_fw = 1;
		} else if (strncmp(chipset, "2070",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
				strncat(infname, "/mcu/bin/rt2870_wow.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_wow_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_WOW_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			} else {
				strncat(infname, "/mcu/bin/rt2870.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			}
		} else if (strncmp(chipset, "3070",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
				strncat(infname, "/mcu/bin/rt2870_wow.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_wow_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_WOW_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			} else {
				strncat(infname, "/mcu/bin/rt2870.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			}
		} else if (strncmp(chipset, "3572",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
				strncat(infname, "/mcu/bin/rt2870_wow.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_wow_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_WOW_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			} else {
				strncat(infname, "/mcu/bin/rt2870.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			}
		} else if (strncmp(chipset, "3573",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
				strncat(infname, "/mcu/bin/rt2870_wow.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_wow_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_WOW_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			} else {
				strncat(infname, "/mcu/bin/rt2870.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			}
		} else if (strncmp(chipset, "3370",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
				strncat(infname, "/mcu/bin/rt2870_wow.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_wow_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_WOW_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			} else {
				strncat(infname, "/mcu/bin/rt2870.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			}
		} else if (strncmp(chipset, "5370",4) == 0) {
			if ((strncmp(wow, "y", 1) == 0) && (strncmp(rt28xx_mode, "STA", 3) == 0)) {
				strncat(infname, "/mcu/bin/rt2870_wow.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_wow_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_WOW_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			} else {
				strncat(infname, "/mcu/bin/rt2870.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/rt2870_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "RT2870_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
				is_bin2h_fw = 1;
			}
		} else if (strncmp(chipset, "5572",4) == 0) {
			strncat(infname, "/mcu/bin/rt2870.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
			strncat(outfname, "/include/mcu/rt2870_firmware.h",
				MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
			strncat(fw_name, "RT2870_FirmwareImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			is_bin2h_fw = 1;
		} else if (strncmp(chipset, "5592",4) == 0) {
			strncat(infname, "/mcu/bin/rt2860.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
			strncat(outfname, "/include/mcu/rt2860_firmware.h",
				MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
			strncat(fw_name, "RT2860_FirmwareImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			is_bin2h_fw = 1;
		} else if ((strncmp(chipset, "mt7601e", 7) == 0)
				|| (strncmp(chipset, "mt7601u", 7) == 0)) {
			strncat(infname, "/mcu/bin/MT7601_formal_1.6.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
			/* strcat(infname,"/mcu/bin/MT7601_formal_1.7.bin"); // from CE */
			strncat(outfname, "/include/mcu/mt7601_firmware.h",
			MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
			strncat(fw_name, "MT7601_FirmwareImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			is_bin2h_fw = 1;
			strncat(ine2pname, "/eeprom/MT7601_USB_V0_D-20130416.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(ine2pname) - 1);
			strncat(oute2pname, "/include/eeprom/mt7601_e2p.h",
				MAX_NAME_BUFFER_LENGTH - strlen(oute2pname) - 1);
			strncat(e2p_name, "MT7601_E2PImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(e2p_name) - 1);
			is_bin2h_e2p = 1;
		} else if ((strncmp(chipset, "mt7650e", 7) == 0)
				|| (strncmp(chipset, "mt7650u", 7) == 0)
				|| (strncmp(chipset, "mt7630e", 7) == 0)
				|| (strncmp(chipset, "mt7630u", 7) == 0)) {
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.20121031.modify.USB.flow.bin"); // pmu
			strncat(infname, "/mcu/bin/MT7650.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1); /* pmu */
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210302000.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_10292045.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.for.PMU.print.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_20121029.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210231140.bin"); // atomic bw
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210181030.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210180939.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210151438.bin"); // led
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210171346.bin");
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210151547.bin");
			//strcat(infname, "/mcu/bin/MT7650_1012.bin");
			//strcat(infname,"/mcu/bin/MT7610.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_201210031435.bin");
			//strcat(infname,"/mcu/bin/MT7610_201210021430.bin"); // turn on debug log same as 10020138.bin
			//strcat(infname,"/mcu/bin/MT7610_201210020138.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_10021442.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_1002.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_shang_1001.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_Lv5.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_Lv4.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_20120919.bin"); // wifi
			//strcat(infname,"/mcu/bin/MT7650E2_V01007870_20120921.bin"); // bt
			//strcat(infname,"/mcu/bin/MT7650.bin");
			strncat(outfname, "/include/mcu/mt7650_firmware.h",
				MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
			strncat(fw_name, "MT7650_FirmwareImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			is_bin2h_fw = 1;
		} else if ((strncmp(chipset, "mt7610e", 7) == 0)
				|| (strncmp(chipset, "mt7610u", 7) == 0)) {
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.20121031.modify.USB.flow.bin"); // pmu
			strncat(infname, "/mcu/bin/MT7650.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1); /* pmu */
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.20121031.modify.USB.flow.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650E2_3_4V01008449_20121207.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210302000.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_10292045.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr.for.PMU.print.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_20121029.bin"); // pmu
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210231140.bin"); // atomic bw
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210181030.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210181030.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210180939.bin"); // PMU
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210151438.bin"); // led
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210171346.bin");
			//strcat(infname, "/mcu/bin/MT7650_E2_hdr_201210151547.bin");
			//strcat(infname, "/mcu/bin/MT7650_1012.bin");
			//strcat(infname,"/mcu/bin/MT7610.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_201210031435.bin");
			//strcat(infname,"/mcu/bin/MT7610_201210021430.bin"); // turn on debug log same as 10020138.bin
			//strcat(infname,"/mcu/bin/MT7610_201210031425.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_10021442.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_shang_1001.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_1002.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_Lv5.bin");
			//strcat(infname,"/mcu/bin/MT7610_201210020138.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_Lv4.bin");
			//strcat(infname,"/mcu/bin/MT7650_E2_hdr_20120919.bin");
			strncat(outfname, "/include/mcu/mt7610_firmware.h",
				MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
			strncat(fw_name, "MT7610_FirmwareImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			is_bin2h_fw = 1;

			if ((strncmp(chipset, "mt7610e", 7) == 0)) {
				strncat(ine2pname, "/eeprom/MT7610U_FEM_V1_1.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(ine2pname) - 1);
				strncat(oute2pname, "/include/eeprom/mt7610e_e2p.h",
					MAX_NAME_BUFFER_LENGTH - strlen(oute2pname) - 1);
				strncat(e2p_name, "MT7610E_E2PImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(e2p_name) - 1);
			} else if ((strncmp(chipset, "mt7610u", 7) == 0)) {
				strncat(ine2pname, "/eeprom/MT7610U_FEM_V1_1.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(ine2pname) - 1);
				strncat(oute2pname, "/include/eeprom/mt7610u_e2p.h",
					MAX_NAME_BUFFER_LENGTH - strlen(oute2pname) - 1);
				strncat(e2p_name, "MT7610U_E2PImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(e2p_name) - 1);
			}
		} else if ((strncmp(chipset, "mt7662e", 7) == 0)
				|| (strncmp(chipset, "mt7662u", 7) == 0)
				|| (strncmp(chipset, "mt7632e", 7) == 0)
				|| (strncmp(chipset, "mt7632u", 7) == 0)
				|| (strncmp(chipset, "mt7612e", 7) == 0)
				|| (strncmp(chipset, "mt7612u", 7) == 0)) {
			strncat(infname, "/mcu/bin/mt7662_firmware_e3_tvbox.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
			//strcat(infname, "/mcu/bin/mt7662_firmware_e3_20140718.bin"); // from CE
			strncat(outfname, "/include/mcu/mt7662_firmware.h",
				MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
			strncat(fw_name, "MT7662_FirmwareImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			strncat(in_rom_patch, "/mcu/bin/mt7662_patch_e3_hdr.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(in_rom_patch) - 1);
			//strcat(in_rom_patch, "/mcu/bin/mt7662_patch_e3_hdr_v0.0.2_P51_20140515.bin"); // from CE
			strncat(out_rom_patch, "/include/mcu/mt7662_rom_patch.h",
				MAX_NAME_BUFFER_LENGTH - strlen(out_rom_patch) - 1);
			strncat(rom_patch_name, "mt7662_rom_patch",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(rom_patch_name) - 1);
			strncat(ine2pname,
				"/eeprom/MT7612E_EEPROM_layout_20131121_2G5G_ePAeLNA_TXTC_off.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(ine2pname) - 1);
			//strcat(ine2pname, "/eeprom/MT7662E2_EEPROM_20130527.bin"); // from CE
			strncat(oute2pname, "/include/eeprom/mt76x2_e2p.h",
				MAX_NAME_BUFFER_LENGTH - strlen(oute2pname) - 1);
			strncat(e2p_name, "MT76x2_E2PImage",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(e2p_name) - 1);
			is_bin2h_fw = 1;
			is_bin2h_rom_patch = 1;
			is_bin2h_e2p = 1;
		} else if ((strncmp(chipset, "mt7662tu", 8) == 0)
				|| (strncmp(chipset, "mt7632tu", 8) == 0)
				|| (strncmp(chipset, "mt7612tu", 8) == 0)
				|| (strncmp(chipset, "mt7662te", 8) == 0)
				|| (strncmp(chipset, "mt7632te", 8) == 0)
				|| (strncmp(chipset, "mt7612te", 8) == 0)) {
			if ((strncmp(chipset, "mt7662te", 8) == 0)
				|| (strncmp(chipset, "mt7632te", 8) == 0)
				|| (strncmp(chipset, "mt7612te", 8) == 0)) {
				strncat(infname, "/mcu/bin/mt7662te_firmware_e1.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/mt7662te_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "MT7662TE_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			} else {
				strncat(infname, "/mcu/bin/mt7662t_firmware_e1.bin",
					MAX_NAME_BUFFER_LENGTH - strlen(infname) - 1);
				strncat(outfname, "/include/mcu/mt7662t_firmware.h",
					MAX_NAME_BUFFER_LENGTH - strlen(outfname) - 1);
				strncat(fw_name, "MT7662T_FirmwareImage",
					MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(fw_name) - 1);
			}

			strncat(in_rom_patch, "/mcu/bin/mt7662t_patch_e1_hdr.bin",
				MAX_NAME_BUFFER_LENGTH - strlen(in_rom_patch) - 1);
			strncat(out_rom_patch, "/include/mcu/mt7662t_rom_patch.h",
				MAX_NAME_BUFFER_LENGTH - strlen(out_rom_patch) - 1);
			strncat(rom_patch_name, "mt7662t_rom_patch",
				MAX_FIRMWARE_NAME_BUFFER_LENGTH - strlen(rom_patch_name) - 1);
			is_bin2h_fw = 1;
			is_bin2h_rom_patch = 1;
		} else {
			printf("unknown chipset = %s\n", chipset);
		}

		if (is_bin2h_fw)
     		bin2h(infname, outfname, fw_name);

		if (is_bin2h_rom_patch)
			bin2h(in_rom_patch, out_rom_patch, rom_patch_name);

		if (is_bin2h_e2p)
			bin2h(ine2pname, oute2pname, e2p_name);

		chipset = strtok(NULL, " ");
	}

    exit(0);
}
