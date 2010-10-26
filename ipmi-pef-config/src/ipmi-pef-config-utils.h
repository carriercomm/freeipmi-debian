/*
  Copyright (C) 2007-2010 FreeIPMI Core Team

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA
*/

#ifndef _IPMI_PEF_CONFIG_UTILS_H
#define _IPMI_PEF_CONFIG_UTILS_H

#include <stdint.h>

#include "ipmi-pef-config.h"

config_err_t get_lan_channel_number (struct ipmi_pef_config_state_data *state_data,
                                     uint8_t *channel_num);

config_err_t get_number_of_lan_alert_destinations (struct ipmi_pef_config_state_data *state_data,
                                                   uint8_t *number_of_lan_alert_destinations);

config_err_t get_number_of_alert_strings (struct ipmi_pef_config_state_data *state_data,
                                          uint8_t *number_of_alert_strings);

config_err_t get_number_of_alert_policy_entries (struct ipmi_pef_config_state_data *state_data,
                                                 uint8_t *number_of_alert_policy_entries);

config_err_t get_number_of_event_filters (struct ipmi_pef_config_state_data *state_data,
                                          uint8_t *number_of_event_filters);

#endif
