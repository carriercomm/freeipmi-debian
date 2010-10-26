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
 *  $Id: ipmi-dcmi-util.c,v 1.1.2.2 2010-05-17 17:42:55 chu11 Exp $
 *****************************************************************************
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#ifdef STDC_HEADERS
#include <string.h>
#endif /* STDC_HEADERS */
#include <errno.h>

#include "freeipmi/util/ipmi-dcmi-util.h"
#include "freeipmi/fiid/fiid.h"
#include "freeipmi/spec/ipmi-cmd-dcmi-spec.h"

#include "libcommon/ipmi-fiid-util.h"
#include "libcommon/ipmi-trace.h"

#include "freeipmi-portability.h"

const char *
ipmi_cmd_dcmi_str (uint8_t cmd)
{
  switch (cmd)
    {
    case IPMI_CMD_DCMI_GET_DCMI_CAPABILITIY_INFO:
      return "Get DCMI Capability Info";
    case IPMI_CMD_DCMI_GET_POWER_READING:
      return "Get Power Reading";
    case IPMI_CMD_DCMI_GET_POWER_LIMIT:
      return "Get Power Limit";
    case IPMI_CMD_DCMI_SET_POWER_LIMIT:
      return "Set Power LIMIT";
    case IPMI_CMD_DCMI_ACTIVATE_DEACTIVATE_POWER_LIMIT:
      return "Activate/Deactivate Power Limit";
    case IPMI_CMD_DCMI_GET_ASSET_TAG:
      return "Get Asset Tag";
    case IPMI_CMD_DCMI_GET_DCMI_SENSOR_INFO:
      return "Get DCMI Sensor Info";
    default:
      return "Unknown";
    }
}
