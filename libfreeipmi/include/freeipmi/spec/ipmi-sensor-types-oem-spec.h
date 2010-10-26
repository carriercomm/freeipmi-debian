/*
   Copyright (C) 2003-2010 FreeIPMI Core Team

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 */

#ifndef _IPMI_SENSOR_TYPES_OEM_SPEC_H
#define _IPMI_SENSOR_TYPES_OEM_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
 * Dell                                    *
 *******************************************/

/*
 * Dell Poweredge R610
 * Dell Poweredge R710
 */

/* achu: names taken from code, are correct names? */
#define IPMI_SENSOR_TYPE_OEM_DELL_SYSTEM_PERFORMANCE_DEGRADATION_STATUS 0xC0
#define IPMI_SENSOR_TYPE_OEM_DELL_LINK_TUNING                           0xC1
#define IPMI_SENSOR_TYPE_OEM_DELL_NON_FATAL_ERROR                       0xC2
#define IPMI_SENSOR_TYPE_OEM_DELL_FATAL_IO_ERROR                        0xC3
#define IPMI_SENSOR_TYPE_OEM_DELL_UPGRADE                               0xC4

/*******************************************
 * Intel                                   *
 *******************************************/

/*
 * Intel Node Manager
 *
 * http://download.intel.com/support/motherboards/server/s5500wb/sb/s5500wb_tps_1_0.pdf
 *
 * For Intel Chips, not just Intel Motherboards.  Confirmed for:
 *
 * Intel S5500WB/Penguin Computing Relion 700
 * Inventec 5441/Dell Xanadu II
 * Inventec 5442/Dell Xanadu III
 * Quanta S99Q/Dell FS12-TY
 */

#define IPMI_SENSOR_TYPE_OEM_INTEL_NODE_MANAGER 0xDC

/*******************************************
 * Inventec                                *
 *******************************************/

/*
 * Inventec 5441/Dell Xanadu II
 * Inventec 5442/Dell Xanadu III
 */
/* achu: not official names, named based on use context */
#define IPMI_SENSOR_TYPE_OEM_INVENTEC_BIOS 0xC1

/*******************************************
 * Supermicro                              *
 *******************************************/

/*
 * Supermicro X8DTH
 */
/* achu: not official names, named based on use context */
#define IPMI_SENSOR_TYPE_OEM_SUPERMICRO_CPU_TEMP 0xC0 

#ifdef __cplusplus
}
#endif

#endif
