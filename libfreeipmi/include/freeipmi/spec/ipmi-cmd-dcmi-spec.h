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
/*****************************************************************************\
 *  Copyright (C) 2009-2010 Lawrence Livermore National Security, LLC.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  LLNL-CODE-413270
 *
 *  This file is part of Ipmi-Dcmi, tools and libraries to support the
 *  data center manageability interface (DCMI).  For details, see
 *  http://www.llnl.gov/linux/.
 *
 *  Ipmi-Dcmi is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmi-Dcmi is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmi-Dcmi.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#ifndef _IPMI_CMD_DCMI_SPEC_H
#define _IPMI_CMD_DCMI_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_CMD_DCMI_GET_DCMI_CAPABILITIY_INFO        0x01
#define IPMI_CMD_DCMI_GET_POWER_READING                0x02
#define IPMI_CMD_DCMI_GET_POWER_LIMIT                  0x03
#define IPMI_CMD_DCMI_SET_POWER_LIMIT                  0x04
#define IPMI_CMD_DCMI_ACTIVATE_DEACTIVATE_POWER_LIMIT  0x05
#define IPMI_CMD_DCMI_GET_ASSET_TAG                    0x06
#define IPMI_CMD_DCMI_GET_DCMI_SENSOR_INFO             0x07

#ifdef __cplusplus
}
#endif

#endif /* ipmi-cmd-dcmi-spec.h */
