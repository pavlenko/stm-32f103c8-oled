/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PWM_DRIVER_H
#define __PWM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/** Instructions **************************************************************/

// Register read
#define PWM_DRIVER_CMD_R_CODE            0x00U
#define PWM_DRIVER_CMD_R_MASK            0x3FU
#define PWM_DRIVER_CMD_R_REGISTER(_reg_) ((PWM_DRIVER_CMD_R_CODE) | ((PWM_DRIVER_CMD_R_MASK) & (_reg_)))

// Register write
#define PWM_DRIVER_CMD_W_CODE            0x40U
#define PWM_DRIVER_CMD_W_MASK            0x3FU
#define PWM_DRIVER_CMD_W_REGISTER(_reg_) ((PWM_DRIVER_CMD_W_CODE) | ((PWM_DRIVER_CMD_W_MASK) & (_reg_)))

/** Registers *****************************************************************/

#define PWM_DRIVER_CH0_PULSE 0x00U
#define PWM_DRIVER_CH1_PULSE 0x01U
#define PWM_DRIVER_CH2_PULSE 0x02U
#define PWM_DRIVER_CH3_PULSE 0x03U
#define PWM_DRIVER_CH4_PULSE 0x04U
#define PWM_DRIVER_CH5_PULSE 0x05U
#define PWM_DRIVER_CH6_PULSE 0x06U
#define PWM_DRIVER_CH7_PULSE 0x07U

/** CH bits *******************************************************************/
#define PWM_DRIVER_CH0_Pos (0U)
#define PWM_DRIVER_CH0_Msk (1U << PWM_DRIVER_CH0_Pos)
#define PWM_DRIVER_CH0     PWM_DRIVER_CH0_Msk

#define PWM_DRIVER_CH1_Pos (1U)
#define PWM_DRIVER_CH1_Msk (1U << PWM_DRIVER_CH1_Pos)
#define PWM_DRIVER_CH1     PWM_DRIVER_CH1_Msk

#define PWM_DRIVER_CH2_Pos (2U)
#define PWM_DRIVER_CH2_Msk (1U << PWM_DRIVER_CH2_Pos)
#define PWM_DRIVER_CH2     PWM_DRIVER_CH2_Msk

#define PWM_DRIVER_CH3_Pos (3U)
#define PWM_DRIVER_CH3_Msk (1U << PWM_DRIVER_CH3_Pos)
#define PWM_DRIVER_CH3     PWM_DRIVER_CH3_Msk

#define PWM_DRIVER_CH4_Pos (4U)
#define PWM_DRIVER_CH4_Msk (1U << PWM_DRIVER_CH4_Pos)
#define PWM_DRIVER_CH4     PWM_DRIVER_CH4_Msk

#define PWM_DRIVER_CH5_Pos (5U)
#define PWM_DRIVER_CH5_Msk (1U << PWM_DRIVER_CH5_Pos)
#define PWM_DRIVER_CH5     PWM_DRIVER_CH5_Msk

#define PWM_DRIVER_CH6_Pos (6U)
#define PWM_DRIVER_CH6_Msk (1U << PWM_DRIVER_CH6_Pos)
#define PWM_DRIVER_CH6     PWM_DRIVER_CH6_Msk

#define PWM_DRIVER_CH7_Pos (7U)
#define PWM_DRIVER_CH7_Msk (1U << PWM_DRIVER_CH7_Pos)
#define PWM_DRIVER_CH7     PWM_DRIVER_CH7_Msk

#define PWM_DRIVER_ALL     0xFFu

/* Exported function prototypes --------------------------------------------- */
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif //__PWM_DRIVER_H
