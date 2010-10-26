/*****************************************************************************\
 *  $Id: ipmi_monitoring_defs.h,v 1.31.4.3 2010-06-04 21:35:35 chu11 Exp $
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

#ifndef _IPMI_MONITORING_DEFS_H
#define _IPMI_MONITORING_DEFS_H

#if HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdint.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <limits.h>             /* MAXHOSTNAMELEN */
#ifdef HAVE_NETDB_H
#include <netdb.h>              /* MAXHOSTNAMELEN Solaris */
#endif /* HAVE_NETDB_H */
#include <freeipmi/freeipmi.h>

#include "list.h"

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 64
#endif /* MAXHOSTNAMELEN */

#ifndef MAXPATHLEN
#define MAXPATHLEN 4096
#endif /* MAXPATHLEN */

/* +1 to avoid gcc warnings */
#define IPMI_MONITORING_SENSOR_TYPE_VALID(__val)                      \
  ((((__val) + 1) >= (IPMI_MONITORING_SENSOR_TYPE_TEMPERATURE + 1)    \
    && (__val) <= IPMI_MONITORING_SENSOR_TYPE_UNKNOWN) ? 1 : 0)

#define IPMI_MONITORING_SENSOR_STATE_VALID(__val)                  \
  (((__val) == IPMI_MONITORING_SENSOR_STATE_NOMINAL                \
    || (__val) == IPMI_MONITORING_SENSOR_STATE_WARNING             \
    || (__val) == IPMI_MONITORING_SENSOR_STATE_CRITICAL            \
    || (__val) == IPMI_MONITORING_SENSOR_STATE_UNKNOWN) ? 1 : 0)

/* +1 to avoid gcc warnings */
#define IPMI_MONITORING_SENSOR_UNITS_VALID(__val)                   \
  ((((__val) + 1) >= (IPMI_MONITORING_SENSOR_UNITS_NONE + 1)        \
    && (__val) <= IPMI_MONITORING_SENSOR_UNITS_UNKNOWN) ? 1 : 0)

#define IPMI_MONITORING_SENSOR_READING_TYPE_VALID(__val)                  \
  (((__val) == IPMI_MONITORING_SENSOR_READING_TYPE_UNSIGNED_INTEGER8_BOOL \
    || (__val) == IPMI_MONITORING_SENSOR_READING_TYPE_UNSIGNED_INTEGER32  \
    || (__val) == IPMI_MONITORING_SENSOR_READING_TYPE_DOUBLE              \
    || (__val) == IPMI_MONITORING_SENSOR_READING_TYPE_UNKNOWN) ? 1 : 0)

/* +1 to avoid gcc warnings */
#define IPMI_MONITORING_SENSOR_BITMASK_TYPE_VALID(__val)                 \
  ((((__val) + 1) >= (IPMI_MONITORING_SENSOR_BITMASK_TYPE_THRESHOLD + 1) \
    && (__val) <= IPMI_MONITORING_SENSOR_BITMASK_TYPE_UNKNOWN) ? 1 : 0)

#define IPMI_MONITORING_MAX_USER_NAME_LENGTH IPMI_MAX_USER_NAME_LENGTH

#define IPMI_MONITORING_MAX_PASSWORD_LENGTH  IPMI_MAX_1_5_PASSWORD_LENGTH

#define IPMI_MONITORING_PRIVILEGE_LEVEL_VALID(__val)              \
  (((__val) == IPMI_MONITORING_PRIVILEGE_LEVEL_USER               \
    || (__val) == IPMI_MONITORING_PRIVILEGE_LEVEL_OPERATOR        \
    || (__val) == IPMI_MONITORING_PRIVILEGE_LEVEL_ADMIN) ? 1 : 0)

#define IPMI_MONITORING_AUTHENTICATION_TYPE_VALID(__val)                    \
  (((__val) == IPMI_MONITORING_AUTHENTICATION_TYPE_NONE                     \
    || (__val) == IPMI_MONITORING_AUTHENTICATION_TYPE_STRAIGHT_PASSWORD_KEY \
    || (__val) == IPMI_MONITORING_AUTHENTICATION_TYPE_MD2                   \
    || (__val) == IPMI_MONITORING_AUTHENTICATION_TYPE_MD5) ? 1 : 0)

#define IPMI_MONITORING_FLAGS_MASK               \
  (IPMI_MONITORING_FLAGS_NONE                    \
   | IPMI_MONITORING_FLAGS_DEBUG                 \
   | IPMI_MONITORING_FLAGS_DEBUG_IPMI_PACKETS    \
   | IPMI_MONITORING_FLAGS_LOCK_MEMORY)

#define IPMI_MONITORING_WORKAROUND_FLAGS_MASK                         \
  (IPMI_MONITORING_WORKAROUND_FLAGS_ACCEPT_SESSION_ID_ZERO            \
   | IPMI_MONITORING_WORKAROUND_FLAGS_FORCE_PERMSG_AUTHENTICATION     \
   | IPMI_MONITORING_WORKAROUND_FLAGS_CHECK_UNEXPECTED_AUTHCODE       \
   | IPMI_MONITORING_WORKAROUND_FLAGS_BIG_ENDIAN_SEQUENCE_NUMBER      \
   | IPMI_MONITORING_WORKAROUND_FLAGS_AUTHENTICATION_CAPABILITIES     \
   | IPMI_MONITORING_WORKAROUND_FLAGS_INTEL_2_0_SESSION               \
   | IPMI_MONITORING_WORKAROUND_FLAGS_SUPERMICRO_2_0_SESSION          \
   | IPMI_MONITORING_WORKAROUND_FLAGS_SUN_2_0_SESSION                 \
   | IPMI_MONITORING_WORKAROUND_FLAGS_OPEN_SESSION_PRIVILEGE          \
   | IPMI_MONITORING_WORKAROUND_FLAGS_NON_EMPTY_INTEGRITY_CHECK_VALUE \
   | IPMI_MONITORING_WORKAROUND_FLAGS_ASSUME_IO_BASE_ADDRESS)

#define IPMI_MONITORING_SENSOR_READING_FLAGS_MASK                          \
  (IPMI_MONITORING_SENSOR_READING_FLAGS_REREAD_SDR_CACHE                   \
   | IPMI_MONITORING_SENSOR_READING_FLAGS_IGNORE_NON_INTERPRETABLE_SENSORS \
   | IPMI_MONITORING_SENSOR_READING_FLAGS_BRIDGE_SENSORS                   \
   | IPMI_MONITORING_SENSOR_READING_FLAGS_INTERPRET_OEM_DATA               \
   | IPMI_MONITORING_SENSOR_READING_FLAGS_SHARED_SENSORS)

#define IPMI_MONITORING_AUTHENTICATION_TYPE_DEFAULT           IPMI_AUTHENTICATION_TYPE_MD5
#define IPMI_MONITORING_PRIVILEGE_LEVEL_DEFAULT               IPMI_PRIVILEGE_LEVEL_USER
#define IPMI_MONITORING_SESSION_TIMEOUT_LENGTH_DEFAULT        20000
#define IPMI_MONITORING_RETRANSMISSION_TIMEOUT_LENGTH_DEFAULT 500

#define IPMI_MONITORING_MAX_SENSOR_NAME_LENGTH      32
#define IPMI_MONITORING_MAX_SDR_RECORD_LENGTH       1024

#define IPMI_MONITORING_MAGIC         0xABCD9876

#define IPMI_MONITORING_PACKET_BUFLEN 1024

struct ipmi_sensor_config {
  char *option_str;
  int sensor_state;
};

struct ipmi_monitoring_sensor_reading {
  int record_id;
  int sensor_number;
  int sensor_type;
  char sensor_name[IPMI_MONITORING_MAX_SENSOR_NAME_LENGTH];
  int sensor_state;
  int sensor_units;
  int sensor_reading_type;
  int sensor_bitmask_type;
  int sensor_bitmask;
  union {
    uint8_t bool_val;
    uint32_t integer_val;
    double double_val;
  } sensor_reading;
};

struct ipmi_monitoring_ctx {
  uint32_t magic;
  int errnum;

  ipmi_sdr_cache_ctx_t sdr_cache_ctx;

  ipmi_ctx_t ipmi_ctx;
  ipmi_sensor_read_ctx_t sensor_read_ctx;
  ipmi_sdr_parse_ctx_t sdr_parse_ctx;

  List sensor_readings;
  ListIterator sensor_readings_itr;
  struct ipmi_monitoring_sensor_reading *current_sensor_reading;

  Ipmi_Monitoring_Sensor_Readings_Callback callback;
  void *callback_data;
  struct ipmi_monitoring_sensor_reading *callback_sensor_reading;

  uint32_t manufacturer_id;
  uint16_t product_id;
};

#endif /* _IPMI_MONITORING_DEFS_H */
