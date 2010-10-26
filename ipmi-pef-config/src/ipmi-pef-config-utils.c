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

#if HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#if STDC_HEADERS
#include <string.h>
#endif /* STDC_HEADERS */
#include <errno.h>
#include <assert.h>

#include "ipmi-pef-config.h"
#include "ipmi-pef-config-utils.h"

#include "freeipmi-portability.h"
#include "pstdout.h"

config_err_t
get_lan_channel_number (struct ipmi_pef_config_state_data *state_data, uint8_t *channel_num)
{
  uint8_t channel_number;

  assert (state_data);
  assert (channel_num);

  if (state_data->lan_channel_number_initialized)
    {
      *channel_num = state_data->lan_channel_number;
      return (0);
    }

  if (ipmi_get_channel_number (state_data->ipmi_ctx,
                               IPMI_CHANNEL_MEDIUM_TYPE_LAN_802_3,
                               &channel_number) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_get_channel_number: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));
      return (CONFIG_ERR_NON_FATAL_ERROR);
    }

  state_data->lan_channel_number_initialized = 1;
  state_data->lan_channel_number = channel_number;
  *channel_num = state_data->lan_channel_number;
  return (CONFIG_ERR_SUCCESS);
}

config_err_t
get_number_of_lan_alert_destinations (struct ipmi_pef_config_state_data *state_data, uint8_t *number_of_lan_alert_destinations)
{
  fiid_obj_t obj_cmd_rs = NULL;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t rc;
  uint64_t val;
  uint8_t channel_number;

  assert (state_data);
  assert (number_of_lan_alert_destinations);

  if (state_data->number_of_lan_alert_destinations_initialized)
    {
      *number_of_lan_alert_destinations = state_data->number_of_lan_alert_destinations;
      return (CONFIG_ERR_SUCCESS);
    }

  if ((rc = get_lan_channel_number (state_data, &channel_number)) != CONFIG_ERR_SUCCESS)
    {
      rv = rc;
      goto cleanup;
    }

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_get_lan_configuration_parameters_number_of_destinations_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if (ipmi_cmd_get_lan_configuration_parameters_number_of_destinations (state_data->ipmi_ctx,
                                                                        channel_number,
                                                                        IPMI_GET_LAN_PARAMETER,
                                                                        CONFIG_SET_SELECTOR,
                                                                        CONFIG_BLOCK_SELECTOR,
                                                                        obj_cmd_rs) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_get_lan_configuration_parameters_number_of_destinations: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));

      if (config_is_non_fatal_error (state_data->ipmi_ctx,
                                     obj_cmd_rs,
                                     &rc))
        rv = rc;

      goto cleanup;
    }

  if (FIID_OBJ_GET (obj_cmd_rs,
                    "number_of_lan_destinations",
                    &val) < 0)
    {
      rv = CONFIG_ERR_NON_FATAL_ERROR;
      goto cleanup;
    }

  state_data->number_of_lan_alert_destinations_initialized = 1;
  state_data->number_of_lan_alert_destinations = val;

  *number_of_lan_alert_destinations = state_data->number_of_lan_alert_destinations;
  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}

config_err_t
get_number_of_alert_strings (struct ipmi_pef_config_state_data *state_data, uint8_t *number_of_alert_strings)
{
  fiid_obj_t obj_cmd_rs = NULL;
  uint64_t val;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t rc;

  assert (state_data);
  assert (number_of_alert_strings);

  if (state_data->number_of_alert_strings_initialized)
    {
      *number_of_alert_strings = state_data->number_of_alert_strings;
      return (CONFIG_ERR_SUCCESS);
    }

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_get_pef_configuration_parameters_number_of_alert_strings_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if (ipmi_cmd_get_pef_configuration_parameters_number_of_alert_strings (state_data->ipmi_ctx,
                                                                         IPMI_GET_PEF_PARAMETER,
                                                                         CONFIG_SET_SELECTOR,
                                                                         CONFIG_BLOCK_SELECTOR,
                                                                         obj_cmd_rs) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_get_pef_configuration_parameters_number_of_alert_strings: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));

      if (config_is_non_fatal_error (state_data->ipmi_ctx,
                                     obj_cmd_rs,
                                     &rc))
        rv = rc;

      goto cleanup;
    }

  if (FIID_OBJ_GET (obj_cmd_rs,
                    "number_of_alert_strings",
                    &val) < 0)
    {
      rv = CONFIG_ERR_NON_FATAL_ERROR;
      goto cleanup;
    }

  state_data->number_of_alert_strings_initialized = 1;
  state_data->number_of_alert_strings = val;

  *number_of_alert_strings = state_data->number_of_alert_strings;
  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}

config_err_t
get_number_of_alert_policy_entries (struct ipmi_pef_config_state_data *state_data, uint8_t *number_of_alert_policy_entries)
{
  fiid_obj_t obj_cmd_rs = NULL;
  uint64_t val;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t rc;

  assert (state_data);
  assert (number_of_alert_policy_entries);

  if (state_data->number_of_alert_policy_entries_initialized)
    {
      *number_of_alert_policy_entries = state_data->number_of_alert_policy_entries;
      return (CONFIG_ERR_SUCCESS);
    }

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_get_pef_configuration_parameters_number_of_alert_policy_entries_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if (ipmi_cmd_get_pef_configuration_parameters_number_of_alert_policy_entries (state_data->ipmi_ctx,
                                                                                IPMI_GET_PEF_PARAMETER,
                                                                                CONFIG_SET_SELECTOR,
                                                                                CONFIG_BLOCK_SELECTOR,
                                                                                obj_cmd_rs) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_get_pef_configuration_parameters_number_of_alert_policy_entries: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));

      if (config_is_non_fatal_error (state_data->ipmi_ctx,
                                     obj_cmd_rs,
                                     &rc))
        rv = rc;

      goto cleanup;
    }

  if (FIID_OBJ_GET (obj_cmd_rs,
                    "number_of_alert_policy_entries",
                    &val) < 0)
    {
      rv = CONFIG_ERR_NON_FATAL_ERROR;
      goto cleanup;
    }

  state_data->number_of_alert_policy_entries_initialized = 1;
  state_data->number_of_alert_policy_entries = val;

  *number_of_alert_policy_entries = state_data->number_of_alert_policy_entries;
  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}

config_err_t
get_number_of_event_filters (struct ipmi_pef_config_state_data *state_data, uint8_t *number_of_event_filters)
{
  fiid_obj_t obj_cmd_rs = NULL;
  uint64_t val;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t rc;

  assert (state_data);
  assert (number_of_event_filters);

  if (state_data->number_of_event_filters_initialized)
    {
      *number_of_event_filters = state_data->number_of_event_filters;
      return (CONFIG_ERR_SUCCESS);
    }

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_get_pef_configuration_parameters_number_of_event_filters_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if (ipmi_cmd_get_pef_configuration_parameters_number_of_event_filters (state_data->ipmi_ctx,
                                                                         IPMI_GET_PEF_PARAMETER,
                                                                         CONFIG_SET_SELECTOR,
                                                                         CONFIG_BLOCK_SELECTOR,
                                                                         obj_cmd_rs) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_get_pef_configuration_parameters_number_of_event_filters: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));

      if (config_is_non_fatal_error (state_data->ipmi_ctx,
                                     obj_cmd_rs,
                                     &rc))
        rv = rc;

      goto cleanup;
    }

  if (FIID_OBJ_GET (obj_cmd_rs,
                    "number_of_event_filters",
                    &val) < 0)
    {
      rv = CONFIG_ERR_NON_FATAL_ERROR;
      goto cleanup;
    }

  state_data->number_of_event_filters_initialized = 1;
  state_data->number_of_event_filters = val;

  *number_of_event_filters = state_data->number_of_event_filters;
  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}


