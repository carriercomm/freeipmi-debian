/*****************************************************************************\
 *  $Id: ipmimonitoring-argp.c,v 1.64.4.2 2009-12-23 21:24:11 chu11 Exp $
 *****************************************************************************
 *  Copyright (C) 2007-2010 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2006-2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  UCRL-CODE-222073
 *
 *  This file is part of Ipmimonitoring, an IPMI sensor monitoring
 *  library.  For details, see http://www.llnl.gov/linux/.
 *
 *  Ipmimonitoring is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmimonitoring is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmimonitoring.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#if HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#if STDC_HEADERS
#include <string.h>
#endif /* STDC_HEADERS */
#if HAVE_ARGP_H
#include <argp.h>
#else /* !HAVE_ARGP_H */
#include "freeipmi-argp.h"
#endif /* !HAVE_ARGP_H */
#if HAVE_UNISTD_H
#include <unistd.h>
#endif /* HAVE_UNISTD_H */
#include <assert.h>
#include <errno.h>

#include "ipmimonitoring.h"
#include "ipmimonitoring-argp.h"

#include "freeipmi-portability.h"
#include "tool-cmdline-common.h"
#include "tool-config-file-common.h"

const char *argp_program_version =
  "ipmimonitoring - " PACKAGE_VERSION "\n"
  "Copyright (C) 2007-2010 Lawrence Livermore National Security, LLC.\n"
  "Copyright (C) 2006-2007 The Regents of the University of California.\n"
  "This program is free software; you may redistribute it under the terms of\n"
  "the GNU General Public License.  This program has absolutely no warranty.";

const char *argp_program_bug_address =
  "<" PACKAGE_BUGREPORT ">";

static char cmdline_doc[] =
  "ipmimonitoring - IPMI monitoring utility";

static char cmdline_args_doc[] = "";

static struct argp_option cmdline_options[] =
  {
    ARGP_COMMON_OPTIONS_DRIVER,
    ARGP_COMMON_OPTIONS_INBAND,
    ARGP_COMMON_OPTIONS_OUTOFBAND_HOSTRANGED,
    ARGP_COMMON_OPTIONS_AUTHENTICATION_TYPE,
    ARGP_COMMON_OPTIONS_CIPHER_SUITE_ID,
    ARGP_COMMON_OPTIONS_PRIVILEGE_LEVEL,
    ARGP_COMMON_OPTIONS_CONFIG_FILE,
    ARGP_COMMON_OPTIONS_WORKAROUND_FLAGS,
    ARGP_COMMON_SDR_OPTIONS,
    ARGP_COMMON_HOSTRANGED_OPTIONS,
    ARGP_COMMON_OPTIONS_DEBUG,
    { "verbose", VERBOSE_KEY, 0, 0,
      "Increase verbosity in output.", 30},
    /* maintain "cache-dir" for backwards compatability */
    { "cache-dir", CACHE_DIR_KEY, "DIRECTORY", OPTION_HIDDEN,
      "Specify an alternate directory to read and write SDR caches.", 31},
    { "quiet-readings", QUIET_READINGS_KEY,  0, 0,
      "Do not output sensor readings, only states.", 32},
    /* for backwards compatability */
    { "sensors",        SENSORS_KEY, "SENSORS-LIST", OPTION_HIDDEN,
      "Show sensors by record id.  Accepts space or comma separated lists", 33},
    { "record-ids",     RECORD_IDS_KEY, "RECORD-IDS-LIST", 0,
      "Show specific sensors by record id.  Accepts space or comma separated lists", 34},
    { "exclude-record-ids", EXCLUDE_RECORD_IDS_KEY, "RECORD-IDS-LIST", 0,
      "Do not show specific sensors by record id.  Accepts space or comma separated lists", 35},
    /* maintain "group" options for backwards compatability */
    { "groups",         GROUPS_KEY,       "GROUP-LIST", 0,
      "Show sensors belonging to a specific group.", 36},
    /* maintain "group" options for backwards compatability */
    { "exclude-groups", EXCLUDE_GROUPS_KEY, "GROUP-LIST", 0,
      "Do not show sensors belonging to a specific group.", 37},
    /* maintain "group" options for backwards compatability */
    { "list-groups",    LIST_GROUPS_KEY,    0, 0,
      "List sensor groups.", 38},
    { "sensor-types",   SENSOR_TYPES_KEY,  "SENSOR-TYPE-LIST", 0,
      "Show sensors of a specific type.", 39},
    { "exclude-sensor-types", EXCLUDE_SENSOR_TYPES_KEY, "SENSOR-TYPE-LIST", 0,
      "Do not show sensors of a specific type.", 40},
    { "list-sensor-types",    LIST_SENSOR_TYPES_KEY, 0, 0,
      "List sensor types.", 41},
    { "bridge-sensors", BRIDGE_SENSORS_KEY, NULL, 0,
      "Bridge addresses to read non-BMC owned sensors.", 42},
    { "shared-sensors", SHARED_SENSORS_KEY, NULL, 0,
      "Iterate over shared sensors in a single record.", 43},
    { "interpret-oem-data", INTERPRET_OEM_DATA_KEY, NULL, 0,
      "Attempt to interpret OEM data.", 44},
    { "ignore-non-interpretable-sensors", IGNORE_NON_INTERPRETABLE_SENSORS_KEY, NULL, 0,
      "Ignore non-interpretable sensors in output.", 45},
    { "entity-sensor-names", ENTITY_SENSOR_NAMES_KEY, NULL, 0,
      "Output sensor names with entity ids and instances.", 46},
    { "no-sensor-type-output", NO_SENSOR_TYPE_OUTPUT_KEY, 0, 0,
      "Do not show sensor type output.", 47},
    { "comma-separated-output", COMMA_SEPARATED_OUTPUT_KEY, 0, 0,
      "Output fields in comma separated format.", 48},
    { "no-header-output", NO_HEADER_OUTPUT_KEY, 0, 0,
      "Do not output column headers.", 49},
    { "non-abbreviated-units", NON_ABBREVIATED_UNITS_KEY, 0, 0,
      "Output non-abbreviated units (e.g. 'Amps' instead of 'A').", 50},
    { "legacy-output", LEGACY_OUTPUT_KEY, 0, 0,
      "Output in legacy format.", 51},
    { "sensor-config-file", SENSOR_CONFIG_FILE_KEY, "FILE", 0,
      "Specify an alternate sensor configuration file.", 52},
    { NULL, 0, NULL, 0, NULL, 0}
  };

static error_t cmdline_parse (int key, char *arg, struct argp_state *state);

static struct argp cmdline_argp = { cmdline_options,
                                    cmdline_parse,
                                    cmdline_args_doc,
                                    cmdline_doc };

static struct argp cmdline_config_file_argp = { cmdline_options,
                                                cmdline_config_file_parse,
                                                cmdline_args_doc,
                                                cmdline_doc };

static error_t
cmdline_parse (int key, char *arg, struct argp_state *state)
{
  struct ipmimonitoring_arguments *cmd_args = state->input;
  char *ptr;
  char *tok;
  int value;
  error_t ret;

  switch (key)
    {
    case VERBOSE_KEY:
      cmd_args->verbose_count++;
      break;
      /* legacy option */
    case CACHE_DIR_KEY:
      return (sdr_parse_opt (ARGP_SDR_CACHE_DIRECTORY_KEY,
                             arg,
                             &(cmd_args->sdr)));
      break;
    case QUIET_READINGS_KEY:
      cmd_args->quiet_readings = 1;
      break;
    /* for backwards compatability */
    case SENSORS_KEY:
    case RECORD_IDS_KEY:
      tok = strtok (arg, " ,");
      while (tok && cmd_args->record_ids_length < MAX_SENSOR_RECORD_IDS)
        {
          value = 0;
          ptr = NULL;
          errno = 0;

          if (!strcasecmp (tok, SENSOR_PARSE_ALL_STRING))
            {
              cmd_args->record_ids_length = 0;
              break;
            }

          value = strtol (tok, &ptr, 10);

          if (errno
              || ptr[0] != '\0'
              || value < 0
              || value < IPMI_SDR_RECORD_ID_FIRST
              || value > IPMI_SDR_RECORD_ID_LAST)
            {
              fprintf (stderr, "invalid sensor record id: %d\n", value);
              exit (1);
            }

          cmd_args->record_ids[cmd_args->record_ids_length] = value;
          cmd_args->record_ids_length++;
          tok = strtok (NULL, " ,");
        }
      break;
    case EXCLUDE_RECORD_IDS_KEY:
      tok = strtok (arg, " ,");
      while (tok && cmd_args->exclude_record_ids_length < MAX_SENSOR_RECORD_IDS)
        {
          value = 0;
          ptr = NULL;
          errno = 0;

          if (!strcasecmp (tok, SENSOR_PARSE_NONE_STRING))
            {
              cmd_args->exclude_record_ids_length = 0;
              break;
            }

          value = strtol (tok, &ptr, 10);

          if (errno
              || ptr[0] != '\0'
              || value < 0
              || value < IPMI_SDR_RECORD_ID_FIRST
              || value > IPMI_SDR_RECORD_ID_LAST)
            {
              fprintf (stderr, "invalid sensor record id: %d\n", value);
              exit (1);
            }

          cmd_args->exclude_record_ids[cmd_args->exclude_record_ids_length] = value;
          cmd_args->exclude_record_ids_length++;
          tok = strtok (NULL, " ,");
        }
      break;
    case GROUPS_KEY:            /* legacy */
    case SENSOR_TYPES_KEY:
      tok = strtok (arg, " ,");
      while (tok && cmd_args->sensor_types_length < MAX_SENSOR_TYPES)
        {
          if (!strcasecmp (tok, SENSOR_PARSE_ALL_STRING))
            {
              cmd_args->sensor_types_length = 0;
              break;
            }
          strncpy (cmd_args->sensor_types[cmd_args->sensor_types_length],
                   tok,
                   MAX_SENSOR_TYPES_STRING_LENGTH);
          cmd_args->sensor_types_length++;
          tok = strtok (NULL, " ,");
        }
      break;
    case EXCLUDE_GROUPS_KEY:    /* legacy */
    case EXCLUDE_SENSOR_TYPES_KEY:
      tok = strtok (arg, " ,");
      while (tok && cmd_args->exclude_sensor_types_length < MAX_SENSOR_TYPES)
        {
          if (!strcasecmp (tok, SENSOR_PARSE_NONE_STRING))
            {
              cmd_args->exclude_sensor_types_length = 0;
              break;
            }
          strncpy (cmd_args->exclude_sensor_types[cmd_args->exclude_sensor_types_length],
                   tok,
                   MAX_SENSOR_TYPES_STRING_LENGTH);
          cmd_args->exclude_sensor_types_length++;
          tok = strtok (NULL, " ,");
        }
      break;
    case LIST_GROUPS_KEY:       /* legacy */
    case LIST_SENSOR_TYPES_KEY:
      cmd_args->list_sensor_types = 1;
      break;
    case BRIDGE_SENSORS_KEY:
      cmd_args->bridge_sensors = 1;
      break;
    case SHARED_SENSORS_KEY:
      cmd_args->shared_sensors = 1;
      break;
    case INTERPRET_OEM_DATA_KEY:
      cmd_args->interpret_oem_data = 1;
      break;
    case IGNORE_NON_INTERPRETABLE_SENSORS_KEY:
      cmd_args->ignore_non_interpretable_sensors = 1;
      break;
    case ENTITY_SENSOR_NAMES_KEY:
      cmd_args->entity_sensor_names = 1;
      break;
    case NO_SENSOR_TYPE_OUTPUT_KEY:
      cmd_args->no_sensor_type_output = 1;
      break;
    case COMMA_SEPARATED_OUTPUT_KEY:
      cmd_args->comma_separated_output = 1;
      break;
    case NO_HEADER_OUTPUT_KEY:
      cmd_args->no_header_output = 1;
      break;
    case NON_ABBREVIATED_UNITS_KEY:
      cmd_args->non_abbreviated_units = 1;
      break;
    case LEGACY_OUTPUT_KEY:
      cmd_args->legacy_output = 1;
      break;
    case SENSOR_CONFIG_FILE_KEY:
      if (cmd_args->sensor_config_file)
        free (cmd_args->sensor_config_file);
      if (!(cmd_args->sensor_config_file = strdup (arg)))
        {
          perror ("strdup");
          exit (1);
        }
      break;
    case ARGP_KEY_ARG:
      /* Too many arguments. */
      argp_usage (state);
      break;
    case ARGP_KEY_END:
      break;
    default:
      ret = common_parse_opt (key, arg, &(cmd_args->common));
      if (ret == ARGP_ERR_UNKNOWN)
        ret = sdr_parse_opt (key, arg, &(cmd_args->sdr));
      if (ret == ARGP_ERR_UNKNOWN)
        ret = hostrange_parse_opt (key, arg, &(cmd_args->hostrange));
      return (ret);
    }

  return (0);
}

static void
_ipmimonitoring_config_file_parse (struct ipmimonitoring_arguments *cmd_args)
{
  struct config_file_data_ipmimonitoring config_file_data;

  memset (&config_file_data,
          '\0',
          sizeof (struct config_file_data_ipmimonitoring));

  if (config_file_parse (cmd_args->common.config_file,
                         0,
                         &(cmd_args->common),
                         &(cmd_args->sdr),
                         &(cmd_args->hostrange),
                         CONFIG_FILE_INBAND | CONFIG_FILE_OUTOFBAND | CONFIG_FILE_SDR | CONFIG_FILE_HOSTRANGE,
                         CONFIG_FILE_TOOL_IPMIMONITORING,
                         &config_file_data) < 0)
    {
      fprintf (stderr, "config_file_parse: %s\n", strerror (errno));
      exit (1);
    }

  if (config_file_data.verbose_count_count)
    cmd_args->verbose_count = config_file_data.verbose_count;
  if (config_file_data.quiet_readings_count)
    cmd_args->quiet_readings = config_file_data.quiet_readings;
  if (config_file_data.record_ids_count && config_file_data.record_ids_length)
    {
      unsigned int i;

      assert (MAX_SENSOR_RECORD_IDS == CONFIG_FILE_MAX_SENSOR_RECORD_IDS);

      for (i = 0; i < config_file_data.record_ids_length; i++)
        cmd_args->record_ids[i] = config_file_data.record_ids[i];
      cmd_args->record_ids_length = config_file_data.record_ids_length;
    }
  if (config_file_data.exclude_record_ids_count && config_file_data.exclude_record_ids_length)
    {
      unsigned int i;

      assert (MAX_SENSOR_RECORD_IDS == CONFIG_FILE_MAX_SENSOR_RECORD_IDS);

      for (i = 0; i < config_file_data.exclude_record_ids_length; i++)
        cmd_args->exclude_record_ids[i] = config_file_data.exclude_record_ids[i];
      cmd_args->exclude_record_ids_length = config_file_data.exclude_record_ids_length;
    }
  if (config_file_data.sensor_types_count && config_file_data.sensor_types_length)
    {
      unsigned int i;

      assert(MAX_SENSOR_TYPES == CONFIG_FILE_MAX_SENSOR_TYPES);
      assert(MAX_SENSOR_TYPES_STRING_LENGTH == CONFIG_FILE_MAX_SENSOR_TYPES_STRING_LENGTH);

      for (i = 0; i < config_file_data.sensor_types_length; i++)
        strncpy (cmd_args->sensor_types[i],
                 config_file_data.sensor_types[i],
                 MAX_SENSOR_TYPES_STRING_LENGTH);
      cmd_args->sensor_types_length = config_file_data.sensor_types_length;
    }
  if (config_file_data.exclude_sensor_types_count && config_file_data.exclude_sensor_types_length)
    {
      unsigned int i;

      assert(MAX_SENSOR_TYPES == CONFIG_FILE_MAX_SENSOR_TYPES);
      assert(MAX_SENSOR_TYPES_STRING_LENGTH == CONFIG_FILE_MAX_SENSOR_TYPES_STRING_LENGTH);

      for (i = 0; i < config_file_data.exclude_sensor_types_length; i++)
        strncpy (cmd_args->exclude_sensor_types[i],
                 config_file_data.exclude_sensor_types[i],
                 MAX_SENSOR_TYPES_STRING_LENGTH);
      cmd_args->exclude_sensor_types_length = config_file_data.exclude_sensor_types_length;
    }
  if (config_file_data.bridge_sensors_count)
    cmd_args->bridge_sensors = config_file_data.bridge_sensors;
  if (config_file_data.shared_sensors_count)
    cmd_args->shared_sensors = config_file_data.shared_sensors;
  if (config_file_data.interpret_oem_data_count)
    cmd_args->interpret_oem_data = config_file_data.interpret_oem_data;
  if (config_file_data.ignore_non_interpretable_sensors_count)
    cmd_args->ignore_non_interpretable_sensors = config_file_data.ignore_non_interpretable_sensors;
  if (config_file_data.entity_sensor_names_count)
    cmd_args->entity_sensor_names = config_file_data.entity_sensor_names;
  if (config_file_data.no_sensor_type_output_count)
    cmd_args->no_sensor_type_output = config_file_data.no_sensor_type_output;
  if (config_file_data.comma_separated_output_count)
    cmd_args->comma_separated_output = config_file_data.comma_separated_output;
  if (config_file_data.no_header_output_count)
    cmd_args->no_header_output = config_file_data.no_header_output;
  if (config_file_data.non_abbreviated_units_count)
    cmd_args->non_abbreviated_units = config_file_data.non_abbreviated_units;
  if (config_file_data.legacy_output_count)
    cmd_args->legacy_output = config_file_data.legacy_output;
  if (config_file_data.sensor_config_file_count)
    cmd_args->sensor_config_file = config_file_data.sensor_config_file;
}

void
ipmimonitoring_argp_parse (int argc, char **argv, struct ipmimonitoring_arguments *cmd_args)
{
  unsigned int i;

  init_common_cmd_args_operator (&(cmd_args->common));
  init_sdr_cmd_args (&(cmd_args->sdr));
  init_hostrange_cmd_args (&(cmd_args->hostrange));
  cmd_args->verbose_count = 0;
  cmd_args->quiet_readings = 0;

  memset (cmd_args->record_ids,
          '\0',
          sizeof (unsigned int) * MAX_SENSOR_RECORD_IDS);
  cmd_args->record_ids_length = 0;

  memset (cmd_args->exclude_record_ids,
          '\0',
          sizeof (unsigned int) * MAX_SENSOR_RECORD_IDS);
  cmd_args->exclude_record_ids_length = 0;

  for (i = 0; i < MAX_SENSOR_TYPES; i++)
    memset (cmd_args->sensor_types[i],
            '\0',
            MAX_SENSOR_TYPES_STRING_LENGTH+1);
  cmd_args->sensor_types_length = 0;

  for (i = 0; i < MAX_SENSOR_TYPES; i++)
    memset (cmd_args->exclude_sensor_types[i],
            '\0',
            MAX_SENSOR_TYPES_STRING_LENGTH+1);
  cmd_args->exclude_sensor_types_length = 0;

  cmd_args->list_sensor_types = 0;

  cmd_args->bridge_sensors = 0;
  cmd_args->shared_sensors = 0;
  cmd_args->interpret_oem_data = 0;
  cmd_args->ignore_non_interpretable_sensors = 0;
  cmd_args->entity_sensor_names = 0;
  cmd_args->no_sensor_type_output = 0;
  cmd_args->comma_separated_output = 0;
  cmd_args->no_header_output = 0;
  cmd_args->non_abbreviated_units = 0;
  cmd_args->legacy_output = 0;
  cmd_args->sensor_config_file = NULL;

  memset (&(cmd_args->conf), '\0', sizeof (struct ipmi_monitoring_ipmi_config));
  cmd_args->ipmimonitoring_flags = 0;

  memset (cmd_args->ipmimonitoring_sensor_types,
          '\0',
          sizeof (unsigned int) * MAX_SENSOR_TYPES);
  cmd_args->ipmimonitoring_sensor_types_length = 0;

  argp_parse (&cmdline_config_file_argp,
              argc,
              argv,
              ARGP_IN_ORDER,
              NULL,
              &(cmd_args->common));

  _ipmimonitoring_config_file_parse (cmd_args);

  argp_parse (&cmdline_argp,
              argc,
              argv,
              ARGP_IN_ORDER,
              NULL,
              cmd_args);

  verify_common_cmd_args (&(cmd_args->common));
  verify_sdr_cmd_args (&(cmd_args->sdr));
  verify_hostrange_cmd_args (&(cmd_args->hostrange));
}


