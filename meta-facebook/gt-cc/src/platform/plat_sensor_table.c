#include "plat_sensor_table.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sensor.h"
#include "ast_adc.h"
#include "intel_peci.h"
#include "hal_gpio.h"
#include "plat_class.h"
#include "plat_gpio.h"
#include "plat_hook.h"
#include "plat_i2c.h"
#include "power_status.h"
#include "pmbus.h"
#include "tmp431.h"
#include "libutil.h"
#include "i2c-mux-tca9548.h"
#include "isl28022.h"
#include "pex89000.h"

sensor_cfg plat_sensor_config[] = {
	/* number,                  type,       port,      address,      offset,
	   access check arg0, arg1, cache, cache_status, mux_ADDRess, mux_offset,
	   pre_sensor_read_fn, pre_sensor_read_args, post_sensor_read_fn, post_sensor_read_fn  */
	/* NIC 0 */
	{ SENSOR_NUM_TEMP_NIC_0, sensor_dev_tmp75, I2C_BUS1, NIC_ADDR, NIC_TEMP_OFFSET, stby_access,
	  0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOLT_NIC_0, sensor_dev_isl28022, I2C_BUS6, NIC_0_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[0] },
	{ SENSOR_NUM_IOUT_NIC_0, sensor_dev_isl28022, I2C_BUS6, NIC_0_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[0] },
	{ SENSOR_NUM_POUT_NIC_0, sensor_dev_isl28022, I2C_BUS6, NIC_0_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[0] },
	/* NIC 1 */
	{ SENSOR_NUM_TEMP_NIC_1, sensor_dev_tmp75, I2C_BUS2, NIC_ADDR, NIC_TEMP_OFFSET, stby_access,
	  0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOLT_NIC_1, sensor_dev_isl28022, I2C_BUS6, NIC_1_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[1] },
	{ SENSOR_NUM_IOUT_NIC_1, sensor_dev_isl28022, I2C_BUS6, NIC_1_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[1] },
	{ SENSOR_NUM_POUT_NIC_1, sensor_dev_isl28022, I2C_BUS6, NIC_1_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[1] },
	/* NIC 2 */
	{ SENSOR_NUM_TEMP_NIC_2, sensor_dev_tmp75, I2C_BUS3, NIC_ADDR, NIC_TEMP_OFFSET, stby_access,
	  0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOLT_NIC_2, sensor_dev_isl28022, I2C_BUS6, NIC_2_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[2] },
	{ SENSOR_NUM_IOUT_NIC_2, sensor_dev_isl28022, I2C_BUS6, NIC_2_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[2] },
	{ SENSOR_NUM_POUT_NIC_2, sensor_dev_isl28022, I2C_BUS6, NIC_2_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[2] },
	/* NIC 3 */
	{ SENSOR_NUM_TEMP_NIC_3, sensor_dev_tmp75, I2C_BUS4, NIC_ADDR, NIC_TEMP_OFFSET, stby_access,
	  0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL, NULL },
	{ SENSOR_NUM_VOLT_NIC_3, sensor_dev_isl28022, I2C_BUS6, NIC_3_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[3] },
	{ SENSOR_NUM_IOUT_NIC_3, sensor_dev_isl28022, I2C_BUS6, NIC_3_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[3] },
	{ SENSOR_NUM_POUT_NIC_3, sensor_dev_isl28022, I2C_BUS6, NIC_3_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[3] },
	/* NIC 4 */
	{ SENSOR_NUM_TEMP_NIC_4, sensor_dev_tmp75, I2C_BUS11, NIC_ADDR, NIC_TEMP_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_VOLT_NIC_4, sensor_dev_isl28022, I2C_BUS6, NIC_4_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[4] },
	{ SENSOR_NUM_IOUT_NIC_4, sensor_dev_isl28022, I2C_BUS6, NIC_4_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[4] },
	{ SENSOR_NUM_POUT_NIC_4, sensor_dev_isl28022, I2C_BUS6, NIC_4_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[4] },
	/* NIC 5 */
	{ SENSOR_NUM_TEMP_NIC_5, sensor_dev_tmp75, I2C_BUS12, NIC_ADDR, NIC_TEMP_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_VOLT_NIC_5, sensor_dev_isl28022, I2C_BUS6, NIC_5_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[5] },
	{ SENSOR_NUM_IOUT_NIC_5, sensor_dev_isl28022, I2C_BUS6, NIC_5_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[5] },
	{ SENSOR_NUM_POUT_NIC_5, sensor_dev_isl28022, I2C_BUS6, NIC_5_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[5] },
	/* NIC 6 */
	{ SENSOR_NUM_TEMP_NIC_6, sensor_dev_tmp75, I2C_BUS13, NIC_ADDR, NIC_TEMP_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_VOLT_NIC_6, sensor_dev_isl28022, I2C_BUS6, NIC_6_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[6] },
	{ SENSOR_NUM_IOUT_NIC_6, sensor_dev_isl28022, I2C_BUS6, NIC_6_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[6] },
	{ SENSOR_NUM_POUT_NIC_6, sensor_dev_isl28022, I2C_BUS6, NIC_6_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[6] },
	/* NIC 7 */
	{ SENSOR_NUM_TEMP_NIC_7, sensor_dev_tmp75, I2C_BUS14, NIC_ADDR, NIC_TEMP_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  NULL },
	{ SENSOR_NUM_VOLT_NIC_7, sensor_dev_isl28022, I2C_BUS6, NIC_7_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[7] },
	{ SENSOR_NUM_IOUT_NIC_7, sensor_dev_isl28022, I2C_BUS6, NIC_7_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[7] },
	{ SENSOR_NUM_POUT_NIC_7, sensor_dev_isl28022, I2C_BUS6, NIC_7_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL,
	  &nic_sensor_init_args[7] },
	/* HSC */
	{ SENSOR_NUM_TEMP_PDB_HSC, sensor_dev_mp5990, I2C_BUS6, HSC_MP5990_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[6], post_i2c_bus_read, NULL, &mp5990_init_args[0] },
	{ SENSOR_NUM_VOUT_PDB_HSC, sensor_dev_mp5990, I2C_BUS6, HSC_MP5990_ADDR, PMBUS_READ_VOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[6], post_i2c_bus_read, NULL, &mp5990_init_args[0] },
	{ SENSOR_NUM_IOUT_PDB_HSC, sensor_dev_mp5990, I2C_BUS6, HSC_MP5990_ADDR, PMBUS_READ_IOUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[6], post_i2c_bus_read, NULL, &mp5990_init_args[0] },
	{ SENSOR_NUM_POUT_PDB_HSC, sensor_dev_mp5990, I2C_BUS6, HSC_MP5990_ADDR, PMBUS_READ_POUT,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[6], post_i2c_bus_read, NULL, &mp5990_init_args[0] },
	/* ADC voltage */
	{ SENSOR_NUM_BB_P12V_AUX, sensor_dev_ast_adc, ADC_PORT0, NONE, NONE, stby_access, 1780, 200,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adc_asd_init_args[0] },
	{ SENSOR_NUM_BB_P5V_AUX, sensor_dev_ast_adc, ADC_PORT1, NONE, NONE, stby_access, 736, 200,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adc_asd_init_args[0] },
	{ SENSOR_NUM_BB_P3V3_AUX, sensor_dev_ast_adc, ADC_PORT2, NONE, NONE, stby_access, 487, 200,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adc_asd_init_args[0] },
	{ SENSOR_NUM_BB_P1V2_AUX, sensor_dev_ast_adc, ADC_PORT3, NONE, NONE, stby_access, 1, 1,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adc_asd_init_args[0] },
	{ SENSOR_NUM_BB_P3V3, sensor_dev_ast_adc, ADC_PORT4, NONE, NONE, stby_access, 487, 200,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adc_asd_init_args[0] },
	{ SENSOR_NUM_BB_P1V8_PEX0, sensor_dev_ast_adc, ADC_PORT5, NONE, NONE, stby_access, 4, 3,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adc_asd_init_args[0] },
	{ SENSOR_NUM_BB_P1V8_PEX1, sensor_dev_ast_adc, ADC_PORT6, NONE, NONE, stby_access, 4, 3,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adc_asd_init_args[0] },
	{ SENSOR_NUM_BB_P1V8_PEX2, sensor_dev_ast_adc, ADC_PORT15, NONE, NONE, stby_access, 4, 3,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adc_asd_init_args[0] },
	{ SENSOR_NUM_BB_P1V8_PEX3, sensor_dev_ast_adc, ADC_PORT14, NONE, NONE, stby_access, 4, 3,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL, NULL, NULL, NULL,
	  &adc_asd_init_args[0] },
	/* PEX 0 */
	{ SENSOR_NUM_TEMP_PEX_0, sensor_dev_isl69259, I2C_BUS6, PEX_0_1_P0V8_VR_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[0], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_VOLT_PEX_0, sensor_dev_isl69259, I2C_BUS6, PEX_0_1_P0V8_VR_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[0], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_IOUT_PEX_0, sensor_dev_isl69259, I2C_BUS6, PEX_0_1_P0V8_VR_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[0], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_POUT_PEX_0, sensor_dev_isl69259, I2C_BUS6, PEX_0_1_P0V8_VR_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[0], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P1V25_VOLT_PEX_0, sensor_dev_isl28022, I2C_BUS6,
	  PEX_0_P1V25_POWER_MONITOR_ADDR, ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[0] },
	{ SENSOR_NUM_P1V25_IOUT_PEX_0, sensor_dev_isl28022, I2C_BUS6,
	  PEX_0_P1V25_POWER_MONITOR_ADDR, ISL28022_CURRENT_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[0] },
	{ SENSOR_NUM_P1V25_POUT_PEX_0, sensor_dev_isl28022, I2C_BUS6,
	  PEX_0_P1V25_POWER_MONITOR_ADDR, ISL28022_POWER_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[0] },
	/* PEX 1 */
	{ SENSOR_NUM_TEMP_PEX_1, sensor_dev_isl69259, I2C_BUS6, PEX_0_1_P0V8_VR_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[1], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_VOLT_PEX_1, sensor_dev_isl69259, I2C_BUS6, PEX_0_1_P0V8_VR_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[1], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_IOUT_PEX_1, sensor_dev_isl69259, I2C_BUS6, PEX_0_1_P0V8_VR_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[1], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_POUT_PEX_1, sensor_dev_isl69259, I2C_BUS6, PEX_0_1_P0V8_VR_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[1], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P1V25_VOLT_PEX_1, sensor_dev_isl28022, I2C_BUS6,
	  PEX_1_P1V25_POWER_MONITOR_ADDR, ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[1] },
	{ SENSOR_NUM_P1V25_IOUT_PEX_1, sensor_dev_isl28022, I2C_BUS6,
	  PEX_1_P1V25_POWER_MONITOR_ADDR, ISL28022_CURRENT_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[1] },
	{ SENSOR_NUM_P1V25_POUT_PEX_1, sensor_dev_isl28022, I2C_BUS6,
	  PEX_1_P1V25_POWER_MONITOR_ADDR, ISL28022_POWER_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[1] },
	/* PEX 2 */
	{ SENSOR_NUM_TEMP_PEX_2, sensor_dev_isl69259, I2C_BUS6, PEX_2_3_P0V8_VR_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[2], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_VOLT_PEX_2, sensor_dev_isl69259, I2C_BUS6, PEX_2_3_P0V8_VR_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[2], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_IOUT_PEX_2, sensor_dev_isl69259, I2C_BUS6, PEX_2_3_P0V8_VR_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[2], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_POUT_PEX_2, sensor_dev_isl69259, I2C_BUS6, PEX_2_3_P0V8_VR_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[2], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P1V25_VOLT_PEX_2, sensor_dev_isl28022, I2C_BUS6,
	  PEX_2_P1V25_POWER_MONITOR_ADDR, ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[2] },
	{ SENSOR_NUM_P1V25_IOUT_PEX_2, sensor_dev_isl28022, I2C_BUS6,
	  PEX_2_P1V25_POWER_MONITOR_ADDR, ISL28022_CURRENT_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[2] },
	{ SENSOR_NUM_P1V25_POUT_PEX_2, sensor_dev_isl28022, I2C_BUS6,
	  PEX_2_P1V25_POWER_MONITOR_ADDR, ISL28022_POWER_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[2] },
	/* PEX 3 */
	{ SENSOR_NUM_TEMP_PEX_3, sensor_dev_isl69259, I2C_BUS6, PEX_2_3_P0V8_VR_ADDR,
	  PMBUS_READ_TEMPERATURE_1, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[3], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_VOLT_PEX_3, sensor_dev_isl69259, I2C_BUS6, PEX_2_3_P0V8_VR_ADDR,
	  PMBUS_READ_VOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[3], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_IOUT_PEX_3, sensor_dev_isl69259, I2C_BUS6, PEX_2_3_P0V8_VR_ADDR,
	  PMBUS_READ_IOUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[3], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P0V8_POUT_PEX_3, sensor_dev_isl69259, I2C_BUS6, PEX_2_3_P0V8_VR_ADDR,
	  PMBUS_READ_POUT, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_isl69259_read, &isl69259_pre_read_args[3], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_P1V25_VOLT_PEX_3, sensor_dev_isl28022, I2C_BUS6,
	  PEX_3_P1V25_POWER_MONITOR_ADDR, ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[3] },
	{ SENSOR_NUM_P1V25_IOUT_PEX_3, sensor_dev_isl28022, I2C_BUS6,
	  PEX_3_P1V25_POWER_MONITOR_ADDR, ISL28022_CURRENT_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[3] },
	{ SENSOR_NUM_P1V25_POUT_PEX_3, sensor_dev_isl28022, I2C_BUS6,
	  PEX_3_P1V25_POWER_MONITOR_ADDR, ISL28022_POWER_REG, stby_access, 0, 0,
	  SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read, &mux_conf_addr_0xe0[1],
	  post_i2c_bus_read, NULL, &pex_p1v25_sensor_init_args[3] },
	/* PEX P1V8 */
	{ SENSOR_NUM_P1V8_VOLT_PEX, sensor_dev_isl28022, I2C_BUS6, PEX_P1V8_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[1], post_i2c_bus_read, NULL,
	  &pex_p1v8_sensor_init_args[0] },
	{ SENSOR_NUM_P1V8_IOUT_PEX, sensor_dev_isl28022, I2C_BUS6, PEX_P1V8_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[1], post_i2c_bus_read, NULL,
	  &pex_p1v8_sensor_init_args[0] },
	{ SENSOR_NUM_P1V8_POUT_PEX, sensor_dev_isl28022, I2C_BUS6, PEX_P1V8_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[1], post_i2c_bus_read, NULL,
	  &pex_p1v8_sensor_init_args[0] },

	{ SENSOR_NUM_BB_TEMP_PEX_0, sensor_dev_pex89000, I2C_BUS10, PEX_SWITCH_I2C_ADDR, PEX_TEMP,
	  dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_pex89000_read,
	  &pex89000_pre_read_args[0], post_i2c_bus_read, NULL, &pex_sensor_init_args[0] },
	{ SENSOR_NUM_BB_TEMP_PEX_1, sensor_dev_pex89000, I2C_BUS10, PEX_SWITCH_I2C_ADDR, PEX_TEMP,
	  dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_pex89000_read,
	  &pex89000_pre_read_args[1], post_i2c_bus_read, NULL, &pex_sensor_init_args[1] },
	{ SENSOR_NUM_BB_TEMP_PEX_2, sensor_dev_pex89000, I2C_BUS10, PEX_SWITCH_I2C_ADDR, PEX_TEMP,
	  dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_pex89000_read,
	  &pex89000_pre_read_args[2], post_i2c_bus_read, NULL, &pex_sensor_init_args[2] },
	{ SENSOR_NUM_BB_TEMP_PEX_3, sensor_dev_pex89000, I2C_BUS10, PEX_SWITCH_I2C_ADDR, PEX_TEMP,
	  dc_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_pex89000_read,
	  &pex89000_pre_read_args[3], post_i2c_bus_read, NULL, &pex_sensor_init_args[3] },

	/* SYSTEM INLET TEMP */
	{ SENSOR_NUM_SYSTEM_INLET_TEMP, sensor_dev_tmp75, I2C_BUS5, SYSTEM_INLET_TEMP_ADDR,
	  TMP75_TEMP_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, NULL,
	  NULL, NULL, NULL, NULL },
	/* SYSTEM OUTLET TEMP LEFT */
	{ SENSOR_NUM_OUTLET_TEMP_L1, sensor_dev_tmp75, I2C_BUS6, SYSTEM_OUTLET_TEMP_L1_ADDR,
	  TMP75_TEMP_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[2], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_OUTLET_TEMP_L2, sensor_dev_tmp75, I2C_BUS6, SYSTEM_OUTLET_TEMP_L2_ADDR,
	  TMP75_TEMP_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[2], post_i2c_bus_read, NULL, NULL },
	/* SYSTEM OUTLET TEMP RIGHT */
	{ SENSOR_NUM_OUTLET_TEMP_R1, sensor_dev_tmp75, I2C_BUS6, SYSTEM_OUTLET_TEMP_R1_ADDR,
	  TMP75_TEMP_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[2], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_OUTLET_TEMP_R2, sensor_dev_tmp75, I2C_BUS6, SYSTEM_OUTLET_TEMP_R2_ADDR,
	  TMP75_TEMP_OFFSET, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[2], post_i2c_bus_read, NULL, NULL },

	/* SSD0 */
	{ SENSOR_NUM_TEMP_E1S_0, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[0], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_0, sensor_dev_isl28022, I2C_BUS6, SSD_0_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[0] },
	{ SENSOR_NUM_CURR_E1S_0, sensor_dev_isl28022, I2C_BUS6, SSD_0_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[0] },
	{ SENSOR_NUM_POUT_E1S_0, sensor_dev_isl28022, I2C_BUS6, SSD_0_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[0] },
	/* SSD1 */
	{ SENSOR_NUM_TEMP_E1S_1, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[1], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_1, sensor_dev_isl28022, I2C_BUS6, SSD_1_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[1] },
	{ SENSOR_NUM_CURR_E1S_1, sensor_dev_isl28022, I2C_BUS6, SSD_1_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[1] },
	{ SENSOR_NUM_POUT_E1S_1, sensor_dev_isl28022, I2C_BUS6, SSD_1_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[1] },
	/* SSD2 */
	{ SENSOR_NUM_TEMP_E1S_2, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[2], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_2, sensor_dev_isl28022, I2C_BUS6, SSD_2_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[2] },
	{ SENSOR_NUM_CURR_E1S_2, sensor_dev_isl28022, I2C_BUS6, SSD_2_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[2] },
	{ SENSOR_NUM_POUT_E1S_2, sensor_dev_isl28022, I2C_BUS6, SSD_2_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[2] },
	/* SSD3 */
	{ SENSOR_NUM_TEMP_E1S_3, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_3, sensor_dev_isl28022, I2C_BUS6, SSD_3_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[3] },
	{ SENSOR_NUM_CURR_E1S_3, sensor_dev_isl28022, I2C_BUS6, SSD_3_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[3] },
	{ SENSOR_NUM_POUT_E1S_3, sensor_dev_isl28022, I2C_BUS6, SSD_3_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[3] },
	/* SSD4 */
	{ SENSOR_NUM_TEMP_E1S_4, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_4, sensor_dev_isl28022, I2C_BUS6, SSD_4_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[4] },
	{ SENSOR_NUM_CURR_E1S_4, sensor_dev_isl28022, I2C_BUS6, SSD_4_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[4] },
	{ SENSOR_NUM_POUT_E1S_4, sensor_dev_isl28022, I2C_BUS6, SSD_4_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[4] },
	/* SSD5 */
	{ SENSOR_NUM_TEMP_E1S_5, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[5], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_5, sensor_dev_isl28022, I2C_BUS6, SSD_5_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[5] },
	{ SENSOR_NUM_CURR_E1S_5, sensor_dev_isl28022, I2C_BUS6, SSD_5_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[5] },
	{ SENSOR_NUM_POUT_E1S_5, sensor_dev_isl28022, I2C_BUS6, SSD_5_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[5] },
	/* SSD6 */
	{ SENSOR_NUM_TEMP_E1S_6, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[6], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_6, sensor_dev_isl28022, I2C_BUS6, SSD_6_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[6] },
	{ SENSOR_NUM_CURR_E1S_6, sensor_dev_isl28022, I2C_BUS6, SSD_6_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[6] },
	{ SENSOR_NUM_POUT_E1S_6, sensor_dev_isl28022, I2C_BUS6, SSD_6_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[6] },
	/* SSD7 */
	{ SENSOR_NUM_TEMP_E1S_7, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe0[7], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_7, sensor_dev_isl28022, I2C_BUS6, SSD_7_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[7] },
	{ SENSOR_NUM_CURR_E1S_7, sensor_dev_isl28022, I2C_BUS6, SSD_7_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[7] },
	{ SENSOR_NUM_POUT_E1S_7, sensor_dev_isl28022, I2C_BUS6, SSD_7_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[3], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[7] },
	/* SSD8 */
	{ SENSOR_NUM_TEMP_E1S_8, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe2[0], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_8, sensor_dev_isl28022, I2C_BUS6, SSD_8_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[8] },
	{ SENSOR_NUM_CURR_E1S_8, sensor_dev_isl28022, I2C_BUS6, SSD_8_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[8] },
	{ SENSOR_NUM_POUT_E1S_8, sensor_dev_isl28022, I2C_BUS6, SSD_8_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[8] },
	/* SSD9 */
	{ SENSOR_NUM_TEMP_E1S_9, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe2[1], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_9, sensor_dev_isl28022, I2C_BUS6, SSD_9_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[9] },
	{ SENSOR_NUM_CURR_E1S_9, sensor_dev_isl28022, I2C_BUS6, SSD_9_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[9] },
	{ SENSOR_NUM_POUT_E1S_9, sensor_dev_isl28022, I2C_BUS6, SSD_9_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[9] },
	/* SSD10 */
	{ SENSOR_NUM_TEMP_E1S_10, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe2[2], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_10, sensor_dev_isl28022, I2C_BUS6, SSD_10_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[10] },
	{ SENSOR_NUM_CURR_E1S_10, sensor_dev_isl28022, I2C_BUS6, SSD_10_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[10] },
	{ SENSOR_NUM_POUT_E1S_10, sensor_dev_isl28022, I2C_BUS6, SSD_10_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[10] },
	/* SSD11 */
	{ SENSOR_NUM_TEMP_E1S_11, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe2[3], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_11, sensor_dev_isl28022, I2C_BUS6, SSD_11_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[11] },
	{ SENSOR_NUM_CURR_E1S_11, sensor_dev_isl28022, I2C_BUS6, SSD_11_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[11] },
	{ SENSOR_NUM_POUT_E1S_11, sensor_dev_isl28022, I2C_BUS6, SSD_11_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[11] },
	/* SSD12 */
	{ SENSOR_NUM_TEMP_E1S_12, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe2[4], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_12, sensor_dev_isl28022, I2C_BUS6, SSD_12_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[11] },
	{ SENSOR_NUM_CURR_E1S_12, sensor_dev_isl28022, I2C_BUS6, SSD_12_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[12] },
	{ SENSOR_NUM_POUT_E1S_12, sensor_dev_isl28022, I2C_BUS6, SSD_12_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[12] },
	/* SSD13 */
	{ SENSOR_NUM_TEMP_E1S_13, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe2[5], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_13, sensor_dev_isl28022, I2C_BUS6, SSD_13_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[13] },
	{ SENSOR_NUM_CURR_E1S_13, sensor_dev_isl28022, I2C_BUS6, SSD_13_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[13] },
	{ SENSOR_NUM_POUT_E1S_13, sensor_dev_isl28022, I2C_BUS6, SSD_13_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[13] },
	/* SSD14 */
	{ SENSOR_NUM_TEMP_E1S_14, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe2[6], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_14, sensor_dev_isl28022, I2C_BUS6, SSD_14_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[14] },
	{ SENSOR_NUM_CURR_E1S_14, sensor_dev_isl28022, I2C_BUS6, SSD_14_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[14] },
	{ SENSOR_NUM_POUT_E1S_14, sensor_dev_isl28022, I2C_BUS6, SSD_14_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[14] },
	/* SSD15 */
	{ SENSOR_NUM_TEMP_E1S_15, sensor_dev_nvme, I2C_BUS9, SSD_COMMON_ADDR, SSD_OFFSET,
	  stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS, pre_i2c_bus_read,
	  &mux_conf_addr_0xe2[7], post_i2c_bus_read, NULL, NULL },
	{ SENSOR_NUM_VOLT_E1S_15, sensor_dev_isl28022, I2C_BUS6, SSD_15_POWER_MONITOR_ADDR,
	  ISL28022_BUS_VOLTAGE_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[15] },
	{ SENSOR_NUM_CURR_E1S_15, sensor_dev_isl28022, I2C_BUS6, SSD_15_POWER_MONITOR_ADDR,
	  ISL28022_CURRENT_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[15] },
	{ SENSOR_NUM_POUT_E1S_15, sensor_dev_isl28022, I2C_BUS6, SSD_15_POWER_MONITOR_ADDR,
	  ISL28022_POWER_REG, stby_access, 0, 0, SAMPLE_COUNT_DEFAULT, 0, SENSOR_INIT_STATUS,
	  pre_i2c_bus_read, &mux_conf_addr_0xe0[4], post_i2c_bus_read, NULL,
	  &ssd_sensor_init_args[15] },
};

uint8_t plat_get_config_size()
{
	return ARRAY_SIZE(plat_sensor_config);
}

void load_sensor_config(void)
{
	memcpy(sensor_config, plat_sensor_config, sizeof(plat_sensor_config));
	sensor_config_count = ARRAY_SIZE(plat_sensor_config);
}
