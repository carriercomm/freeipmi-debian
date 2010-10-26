/*****************************************************************************\
 *  $Id: ipmi-dcmi.h,v 1.1.4.3 2010-05-17 17:42:55 chu11 Exp $
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

/* double underscore, libfreeipmi ipmi-dcmi.h also exists */
#ifndef __IPMI_DCMI_H
#define __IPMI_DCMI_H

#include <freeipmi/freeipmi.h>

#include "tool-cmdline-common.h"
#include "tool-oem-common.h"
#include "pstdout.h"

enum ipmi_dcmi_argp_option_keys
  {
    GET_DCMI_CAPABILITY_INFO = 160,
    GET_SYSTEM_POWER_STATISTICS = 161,
    GET_ENHANCED_SYSTEM_POWER_STATISTICS = 162,
    GET_POWER_LIMIT = 163,
    SET_POWER_LIMIT = 164,
    EXCEPTION_ACTIONS = 165,
    POWER_LIMIT_REQUESTED = 166,
    CORRECTION_TIME_LIMIT = 167,
    STATISTICS_SAMPLING_PERIOD = 168,
    ACTIVATE_DEACTIVATE_POWER_LIMIT = 169,
    GET_ASSET_TAG = 170,
    GET_DCMI_SENSOR_INFO = 171,
    INTERPRET_OEM_DATA_KEY = 172,
  };

struct ipmi_dcmi_arguments
{
  struct common_cmd_args common;
  struct hostrange_cmd_args hostrange;
  int get_dcmi_capability_info;
  int get_system_power_statistics;
  int get_enhanced_system_power_statistics;
  int get_power_limit;
  int set_power_limit;
  int exception_actions;
  uint8_t exception_actions_arg;
  int power_limit_requested;
  uint16_t power_limit_requested_arg;
  int correction_time_limit;
  uint32_t correction_time_limit_arg;
  int statistics_sampling_period;
  uint16_t statistics_sampling_period_arg;
  int activate_deactivate_power_limit;
  uint8_t activate_deactivate_power_limit_arg;
  int get_asset_tag;
  int get_dcmi_sensor_info;
  int interpret_oem_data;
};

typedef struct ipmi_dcmi_prog_data
{
  char *progname;
  struct ipmi_dcmi_arguments *args;
} ipmi_dcmi_prog_data_t;

typedef struct ipmi_dcmi_state_data
{
  ipmi_dcmi_prog_data_t *prog_data;
  ipmi_ctx_t ipmi_ctx;
  pstdout_state_t pstate;
  struct ipmi_oem_data oem_data;
} ipmi_dcmi_state_data_t;

#endif
