#pragma once

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define CHECKSUM_CONSTANT 44111

typedef enum
{
	BalancingIn_ENABLE,
	BalancingOut_ENABLE,
	Balancing_DISABLE
}MA_BalanceState;

/******************  Bit definition for Event register  *******************/
#define MA_Event_BufferEnable_Pos                (0U)                               
#define MA_Event_BufferEnable_Msk                (0x1U << MA_Event_BufferEnable_Pos)           /*!< 0x0001 */
#define MA_Event_BufferEnable                    MA_Event_BufferEnable_Msk                     /*!< BUFF_PWR Normal */
#define MA_Event_Transformer_Out_Pos             (1U)                               
#define MA_Event_Transformer_Out_Msk             (0x1U << MA_Event_Transformer_Out_Pos)        /*!< 0x0002 */
#define MA_Event_Transformer_Out                 MA_Event_Transformer_Out_Msk                  /*!< Transformer Out */
#define MA_Event_Balancing_In_Pos                (2U)                               
#define MA_Event_Balancing_In_Msk                (0x1U << MA_Event_Balancing_In_Pos)           /*!< 0x0004 */
#define MA_Event_Balancing_In                    MA_Event_Balancing_In_Msk                     /*!< Balancing_In Enable */
#define MA_Event_Balancing_Out_Pos               (3U)                               
#define MA_Event_Balancing_Out_Msk               (0x1U << MA_Event_Balancing_Out_Pos)          /*!< 0x0008 */
#define MA_Event_Balancing_Out                   MA_Event_Balancing_Out_Msk                    /*!< Balancing_Out Enable */
#define MA_Event_Safety_Status_COV_Pos           (4U)                               
#define MA_Event_Safety_Status_COV_Msk           (0x1U << MA_Event_Safety_Status_COV_Pos)      /*!< 0x0010 */
#define MA_Event_Safety_Status_COV               MA_Event_Safety_Status_COV_Msk                /*!< Cell Overvoltage */
#define MA_Event_Safety_Status_CUV_Pos           (5U)                               
#define MA_Event_Safety_Status_CUV_Msk           (0x1U << MA_Event_Safety_Status_CUV_Pos)      /*!< 0x0020 */
#define MA_Event_Safety_Status_CUV               MA_Event_Safety_Status_CUV_Msk                /*!< Cell Undervoltage */
#define MA_Event_Safety_Status_COT_Pos           (6U)                               
#define MA_Event_Safety_Status_COT_Msk           (0x1U << MA_Event_Safety_Status_COT_Pos)      /*!< 0x0040 */
#define MA_Event_Safety_Status_COT               MA_Event_Safety_Status_COT_Msk                /*!< Cell Overtemperature */
#define MA_Event_Safety_Status_CUT_Pos           (7U)                               
#define MA_Event_Safety_Status_CUT_Msk           (0x1U << MA_Event_Safety_Status_CUT_Pos)      /*!< 0x0080 */
#define MA_Event_Safety_Status_CUT               MA_Event_Safety_Status_CUT_Msk                /*!< Cell Undertemperature */
#define MA_Event_Safety_Status_OTT_Pos           (8U)                               
#define MA_Event_Safety_Status_OTT_Msk           (0x1U << MA_Event_Safety_Status_OTT_Pos)      /*!< 0x0100 */
#define MA_Event_Safety_Status_OTT               MA_Event_Safety_Status_OTT_Msk                /*!< Tansistor Overtemperature */
#define MA_Event_Safety_Status_MA_Fail_Pos       (9U)                               
#define MA_Event_Safety_Status_MA_Fail_Msk       (0x1U << MA_Event_Safety_Status_MA_Fail_Pos)  /*!< 0x0200 */
#define MA_Event_Safety_Status_MA_Fail           MA_Event_Safety_Status_MA_Fail_Msk            /*!< MA circuit error */

/** 
  * @brief MA measurements Structure definition
  */
typedef volatile  struct
{
	uint16_t U_cell;              /*!< Cell voltage, mV */
	int16_t  I_balance;           /*!< Balancing current, mA */
	int8_t   TemperatureAnode;    /*!< Anode cell temperature (-), 'C */
	int8_t   TemperatureCathode;  /*!< Cathode cell temperature (+), 'C */
	int8_t   TemperatureVT1;      /*!< VT1 transistor temperature, 'C */
	uint16_t MA_Event_Register;   /*!< MA Event Register */
}MA_MeasurementsTypeDef;

/** 
  * @brief MA settings Structure definition
  */
typedef volatile struct
{
	uint16_t COV_Threshold;   /*!< Cell Over Voltage Threshold, mV */
	uint16_t COV_Recovery;    /*!< Cell Over Voltage Recovery, mV */
	uint16_t COV_Time;        /*!< Cell Over Voltage Time, ms */
	uint16_t CUV_Threshold;   /*!< Cell Under Voltage Threshold, mV */
	uint16_t CUV_Recovery;    /*!< Cell Under Voltage Recovery, mV */
	uint16_t CUV_Time;        /*!< Cell Under Voltage Time, ms */
	int8_t   COT_Threshold;   /*!< Cell Over Temperature Threshold, 'C */
	int8_t   COT_Recovery;    /*!< Cell Over Temperature Recovery, 'C */
	uint16_t COT_Time;        /*!< Cell Over Temperature Time, ms */
	int8_t   CUT_Threshold;   /*!< Cell Under Temperature Threshold, 'C */
	int8_t   CUT_Recovery;    /*!< Cell Under Temperature Recovery, 'C */
	uint16_t CUT_Time;        /*!< Cell Under Temperature Time, ms */
	int8_t   OTT_Threshold;   /*!< Over Temperature Tansistor Threshold, 'C */
	int8_t   OTT_Recovery;    /*!< Over Temperature Tansistor Recovery, 'C */
	uint16_t OTT_Time;        /*!< Over Temperature Tansistor Time, ms */
}MA_SettingsTypeDef;

extern MA_MeasurementsTypeDef measurements;
extern MA_SettingsTypeDef settings;

bool writeDataToSettingsArray(uint8_t *data, const uint8_t size, const uint8_t address);
void setBalanceState(const MA_BalanceState state);
void sendMeasurements();
void sendSettingsChecksum();
void updateSettings();
void updateMeasurements();