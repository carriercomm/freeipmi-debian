/*
  Copyright (C) 2003-2010 FreeIPMI Core Team

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

#ifndef _TOOL_SDR_CACHE_COMMON_H
#define _TOOL_SDR_CACHE_COMMON_H

#include <stdio.h>
#include <stdint.h>

#include <freeipmi/freeipmi.h>

#include "pstdout.h"

#define IPMI_SDR_CACHE_MAX_ID_STRING         16
#define IPMI_SDR_CACHE_MAX_DEVICE_ID_STRING  16

/* For sdr_cache_get_cache_directory: pstate can be NULL if we aren't
 * yet threaded
 */
int sdr_cache_get_cache_directory (pstdout_state_t pstate,
                                   const char *cache_dir,
                                   char *buf,
                                   unsigned int buflen);

int sdr_cache_get_cache_filename (pstdout_state_t pstate,
                                  const char *hostname,
                                  const char *cache_dir,
                                  char *buf,
                                  unsigned int buflen);

int sdr_cache_create_directory (pstdout_state_t pstate,
                                const char *cache_dir);

int sdr_cache_create (ipmi_sdr_cache_ctx_t ctx,
                      pstdout_state_t pstate,
                      ipmi_ctx_t ipmi_ctx,
                      int quiet_cache,
                      int sdr_cache_recreate,
                      const char *hostname,
                      const char *cache_dir);

int sdr_cache_create_and_load (ipmi_sdr_cache_ctx_t ctx,
                               pstdout_state_t pstate,
                               ipmi_ctx_t ipmi_ctx,
                               int quiet_cache,
                               int sdr_cache_recreate,
                               const char *hostname,
                               const char *cache_dir);

int sdr_cache_flush_cache (ipmi_sdr_cache_ctx_t ctx,
                           pstdout_state_t pstate,
                           int quiet_cache,
                           const char *hostname,
                           const char *cache_dir);

#endif
