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

#ifndef _IPMI_DCMI_CMDS_TEMPLATES_H
#define _IPMI_DCMI_CMDS_TEMPLATES_H

#ifdef __cplusplus
extern "C" {
#endif

/* This header file is for documentation only */

#if 0

Format = { bits, "field name", field flags }

FIID_FIELD_REQUIRED - field is required for the payload
FIID_FIELD_OPTIONAL - field is optional for the payload

FIID_FIELD_LENGTH_FIXED - field length is fixed at the number of bits listed
FIID_FIELD_LENGTH_VARIABLE - field length is variable for the number of bits listed

FIID_FIELD_MAKES_PACKET_SUFFICIENT - indicates field or fields are "sufficient" to make a valid packet

DCMI Rolling Average Time Period
--------------------------------

fiid_template_t tmpl_dcmi_rolling_average_time_period =
  {
    { 6, "time_duration", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 2, "time_duration_units", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
  };

DCMI Get DCMI Capability Info Request
-------------------------------------

fiid_template_t tmpl_cmd_dcmi_get_dcmi_capability_info_rq =
  {
    { 8, "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "parameter_selector", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get DCMI Capability Info Response
--------------------------------------

fiid_template_t tmpl_cmd_dcmi_get_dcmi_capability_info_rs =
  {
    { 8,    "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,    "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,    "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,    "dcmi_specification_conformance.major_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,    "dcmi_specification_conformance.minor_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,    "parameter_revision", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1024, "parameter_data", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_VARIABLE},
    { 0, "", 0}
  };

DCMI Get DCMI Capability Info (Supported DCMI Capabilities) Response
--------------------------------------------------------------------

/* achu: assume typo "Out-Of-B" means "Out-Of-Band" */
fiid_template_t tmpl_cmd_dcmi_get_dcmi_capability_info_supported_dcmi_capabilities_rs =
  {
    { 8, "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "dcmi_specification_conformance.major_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "dcmi_specification_conformance.minor_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "parameter_revision", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1, "mandatory_platform_capabilities.identification_support", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1, "mandatory_platform_capabilities.sel_logging", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1, "mandatory_platform_capabilities.chassis_power", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1, "mandatory_platform_capabilities.temperature_monitor", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 4, "mandatory_platform_capabilities.reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1, "optional_platform_capabilities.power_management", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 7, "optional_platform_capabilities.reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1, "manageability_access_capabilities.in_band_kcs_channel_available", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1, "manageability_access_capabilities.out_of_band_serial_tmode_available", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1, "manageability_access_capabilities.out_of_band_secondary_lan_channel_available", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1, "manageability_access_capabilities.out_of_band_primary_lan_channel_available", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1, "manageability_access_capabilities.sol_supported", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1, "manageability_access_capabilities.vlan_capable", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 2, "manageability_access_capabilities.reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };


DCMI Get DCMI Capability Info (Mandatory Platform Attributes) Response
----------------------------------------------------------------------

fiid_template_t tmpl_cmd_dcmi_get_dcmi_capability_info_mandatory_platform_attributes_rs =
  {
    { 8,  "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,  "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,  "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "dcmi_specification_conformance.major_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "dcmi_specification_conformance.minor_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "parameter_revision", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 12, "sel_attributes.number_of_sel_entries", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 3,  "sel_attributes.reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1,  "sel_attributes.sel_automatic_rollover_enabled", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1,  "identification_attributes.guid_support", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1,  "identification_attributes.dhcp_host_name_support", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1,  "identification_attributes.asset_tag_support", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 5,  "identification_attributes.reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1,  "temperature_monitoring.inlet_temperature", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1,  "temperature_monitoring.processors_temperature", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    /* in parameter revision >= 02h, reserved */
    { 1,  "temperature_monitoring.baseboard_temperature", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 5,  "temperature_monitoring.reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get DCMI Capability Info (Optional Platform Attributes) Response
---------------------------------------------------------------------

fiid_template_t tmpl_cmd_dcmi_get_dcmi_capability_info_optional_platform_attributes_rs =
  {
    { 8, "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "dcmi_specification_conformance.major_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "dcmi_specification_conformance.minor_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "parameter_revision", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1, "power_management_device_slave_address.reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 7, "power_management_device_slave_address.slave_address", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 4, "power_management_controller_channel_number.device_revision", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 4, "power_management_controller_channel_number.channel_number", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get DCMI Capability Info (Manageability Access Attributes) Response
------------------------------------------------------------------------

/* achu: for consistency, renamed "oob" to "out_of_band" */
fiid_template_t tmpl_cmd_dcmi_get_dcmi_capability_info_manageability_access_attributes_rs =
  {
    { 8, "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "dcmi_specification_conformance.major_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "dcmi_specification_conformance.minor_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "parameter_revision", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "mandatory_primary_lan_out_of_band_support_channel_number", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "optional_secondary_lan_out_of_band_support_channel_number", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "optional_serial_out_of_band_tmode_capability_channel_number", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get DCMI Capability Info (Enhanced System Power Statistics Attributes) Response
------------------------------------------------------------------------------------

/* 256 * 8 = 2048 */
fiid_template_t tmpl_cmd_dcmi_get_dcmi_capability_info_enhanced_system_power_statistics_attributes_rs =
{
  { 8,    "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
  { 8,    "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
  { 8,    "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
  { 8,    "dcmi_specification_conformance.major_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
  { 8,    "dcmi_specification_conformance.minor_version", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
  { 8,    "parameter_revision", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
  { 8,    "number_of_supported_rolling_average_time_periods", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
  { 2048, "rolling_average_time_periods", FIID_FIELD_OPTIONAL | FIID_FIELD_LENGTH_VARIABLE},
  { 0, "", 0}
};

DCMI Get Power Reading Request
------------------------------

fiid_template_t tmpl_cmd_dcmi_get_power_reading_rq =
  {
    { 8,  "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "mode", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get Power Reading Response
-------------------------------

fiid_template_t tmpl_cmd_dcmi_get_power_reading_rs =
  {
    { 8,  "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,  "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,  "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "current_power", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "minimum_power_over_sampling_duration", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "maximum_power_over_sampling_duration", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "average_power_over_sampling_duration", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 32, "time_stamp", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 32, "statistics_reporting_time_period", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 6,  "power_reading_state.reserved1", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1,  "power_reading_state.power_measurement", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 1,  "power_reading_state.reserved2", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get Power Limit Request
----------------------------

fiid_template_t tmpl_cmd_dcmi_get_power_limit_rq =
  {
    { 8,  "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get Power Limit Response
-----------------------------

fiid_template_t tmpl_cmd_dcmi_get_power_limit_rs =
  {
    { 8,  "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,  "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,  "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "reserved1", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "exception_actions", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "power_limit_requested", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 32, "correction_time_limit", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "reserved2", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "management_application_statistics_sampling_period", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Set Power Limit Request
----------------------------

fiid_template_t tmpl_cmd_dcmi_set_power_limit_rq =
  {
    { 8,  "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 24, "reserved1", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "exception_actions", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "power_limit_requested", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 32, "correction_time_limit", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "reserved2", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "management_application_statistics_sampling_period", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Set Power Limit Response
-----------------------------

fiid_template_t tmpl_cmd_dcmi_set_power_limit_rs =
  {
    { 8, "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Activate/Deactivate Power Limit Request
--------------------------------------------

fiid_template_t tmpl_cmd_dcmi_activate_deactivate_power_limit_rq =
  {
    { 8,  "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,  "power_limit_activation", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 16, "reserved", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Activate/Deactivate Power Limit Response
---------------------------------------------

fiid_template_t tmpl_cmd_dcmi_activate_deactivate_power_limit_rs =
  {
    { 8, "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8, "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get Asset Tag Request
--------------------------

fiid_template_t tmpl_cmd_dcmi_get_asset_tag_rq =
  {
    { 8, "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "offset_to_read", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "number_of_bytes_to_read", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get Asset Tag Response
---------------------------

/* achu: number_of_bytes_to_read is max 16, so presumably data can only be max 16, but
 * asset tag max is 64 bytes.  We'll use 64 bytes (512 bits) as the max then.
 */
fiid_template_t tmpl_cmd_dcmi_get_asset_tag_rs =
  {
    { 8,   "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,   "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,   "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,   "total_asset_tag_length", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 512, "data", FIID_FIELD_OPTIONAL | FIID_FIELD_LENGTH_VARIABLE},
    { 0, "", 0}
  };

DCMI Get DCMI Sensor Info Request
---------------------------------

fiid_template_t tmpl_cmd_dcmi_get_dcmi_sensor_info_rq =
  {
    { 8, "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "entity_id", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "entity_instance", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8, "entity_instance_start", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 0, "", 0}
  };

DCMI Get DCMI Sensor Info Response
----------------------------------

/* presumably a max of 256 entity_instances (b/c 1 byte field), so 
 * assume max record ids of 256.  record_id = 16 bits, so 256 * 16 = 4096
 */
fiid_template_t tmpl_cmd_dcmi_get_dcmi_sensor_info_rs =
  {
    { 8,    "cmd", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,    "comp_code", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED | FIID_FIELD_MAKES_PACKET_SUFFICIENT},
    { 8,    "group_extension_identification", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,    "total_number_of_available_instances", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 8,    "number_of_record_ids_in_this_response", FIID_FIELD_REQUIRED | FIID_FIELD_LENGTH_FIXED},
    { 4096, "sdr_record_ids", FIID_FIELD_OPTIONAL | FIID_FIELD_LENGTH_VARIABLE}, /* 16 bit fields of record ids, LS byte first */
    { 0, "", 0}
  };

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif  /* _IPMI_DCMI_CMDS_TEMPLATES_H */
