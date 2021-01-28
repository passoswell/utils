/**
 * @file  custom_types.h
 * @date  22-December-2020
 * @brief Useful data type definitions.
 *
 * @author
 * @author
 */

#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H


#include <stdint.h>
#include "stdstatus.h"


/***** FIRMWARE VERSION ***************************************************** */
#define COMMON_CUSTOM_TYPES_VER_MAJOR                                       2020
#define COMMON_CUSTOM_TYPES_VER_MINOR                                         12
#define COMMON_CUSTOM_TYPES_VER_PATCH                                          5


/******************************************************************************/
/**                         Util                                             **/
/******************************************************************************/

/**
 * @brief Common communication interfaces for devices in general.
 */
typedef enum
{
  COMMOPT_SPI,
  COMMOPT_I2C,
  COMMOPT_PARALLEL,
  COMMOPT_NUMBER_OF_COMMOPT,
}CommOpt_t;


/**
 * @brief Common sensor types (from Adafruit's Unified Sensor Driver).
 */
typedef enum
{
  SENSOR_TYPE_INVALID               = 0x0000,
  SENSOR_TYPE_ACCELEROMETER         = (1 << 0),
  SENSOR_TYPE_GYROSCOPE             = (1 << 1),
  SENSOR_TYPE_MAGNETIC_FIELD        = (1 << 2),
  SENSOR_TYPE_GRAVITY               = (1 << 3),
  SENSOR_TYPE_PRESSURE              = (1 << 4),
  SENSOR_TYPE_ORIENTATION           = (1 << 5),
  SENSOR_TYPE_ROTATION_VECTOR       = (1 << 6),

  SENSOR_TYPE_LIGHT                 = (1 << 7),
  SENSOR_TYPE_PROXIMITY             = (1 << 8),
  SENSOR_TYPE_COLOR                 = (1 << 9),

  SENSOR_TYPE_RELATIVE_HUMIDITY     = (1 << 10),
  SENSOR_TYPE_AMBIENT_TEMPERATURE   = (1 << 11),
  SENSOR_TYPE_CHIP_TEMPERATURE      = (1 << 12),

  SENSOR_TYPE_VOLTAGE               = (1 << 13),
  SENSOR_TYPE_CURRENT               = (1 << 14),
} SensorsType_t;


/**
 * @brief Vector of three dimensions.
 */
typedef struct
{
  float x;
  float y;
  float z;
} Vector_t;


/******************************************************************************/
/**                         Displays                                         **/
/******************************************************************************/

/**
 * @brief Common color options for displays.
 */
typedef enum
{
  DISPLAY_MONOCHROMATIC = 0,
  DISPLAY_8BITS,
  DISPLAY_24BITS,
  DISPLAY_RGB,
  DISPLAY_NUMBER_OF_COLORCONFIG,
}Display_ColorConfig_t;


/**
 * @brief Common communication interfaces for displays. Kept for backwards
 *        compatibility.
 */
typedef enum
{
  DISPLAY_SPI,
  DISPLAY_I2C,
  DISPLAY_PARALLEL,
  DISPLAY_NUMBER_OF_COMMOPT,
}Display_CommOpt_t;


/**
 * @brief Useful characteristics for displays.
 */
typedef struct
{
  uint8_t               Name[10];
  uint32_t              HorizontalPixels;
  uint32_t              VerticalPixels;
  uint32_t              HorizontalBitsPerWrite;
  uint32_t              VerticalBitsPerWrite;
  uint32_t              CharInRows;
  uint16_t              CharInCollumns;
  Display_CommOpt_t     CommOpt;
  Display_ColorConfig_t ColorScheme;
}Display_specs_t;


/**
 * @brief List of display functions for access through function pointers.
 */
typedef struct
{
  EStatus_t (*IntHwInit)(uint8_t ID, void *Parameter,
      Display_CommOpt_t CommOpt);

  EStatus_t (*ExtDevConfig)(uint8_t ID);

  EStatus_t (*SetCursor)(uint8_t ID, uint8_t Row, uint8_t Column);

  EStatus_t (*PutChar)(uint8_t ID, uint8_t Row, uint8_t Col,
      uint8_t Character, uint8_t Color );

  EStatus_t (*PutString)( uint8_t ID, uint8_t *Buffer, uint32_t Length,
      uint8_t Row, uint8_t Col, uint8_t Color );

  EStatus_t (*ClearScreen)(uint8_t ID, uint8_t Color);

  EStatus_t (*ReadSpecs)(Display_specs_t *Specs);
}Display_Functions_t;


/******************************************************************************/
/**                         IMUs and AHRS                                    **/
/******************************************************************************/

/**
 * @brief IMU measurement data.
 */
typedef struct
{
  Vector_t LinAccel;    /*!< Linear acceleration */
  Vector_t AngVel;      /*!< Angular velocity */
  Vector_t MagField;    /*!< Magnetic field */
  Vector_t Pressure;    /*!< Triaxial pressure */
  float    Temperature; /*!< Sensor's temperature */
}IMU_Data_t;


/**
 * @brief AHRS computed or measured data.
 */
typedef struct
{
  Vector_t LinPos;
  Vector_t AngPos;   /*!< Roll (x), Pitch (y) and Yaw (z) */
  Vector_t LinVel;
  Vector_t AngVel;
  Vector_t LinAccel;
  Vector_t AngAccel;
  float    Tilt;
}AHRS_t;


/**
 * @brief Useful characteristics for IMUs.
 */
typedef struct
{
  uint8_t       Name[10];
  SensorsType_t Type;       /*!< Any combination of SensorsType_t values */
  float         MinValue;
  float         MaxValue;
  float         Resolution; /*!< Smallest difference possible between
                                 two values */
  int32_t       MinDelay;   /*!< Time between data readings in microseconds*/
}IMU_specs_t;


/**
 * @brief List of IMU functions for access through function pointers.
 */
typedef struct
{
  EStatus_t (*IntHwInit)(uint8_t ID, void *Parameter, CommOpt_t CommOpt);

  EStatus_t (*ExtDevConfig)(uint8_t ID);

  EStatus_t (*Read)(uint8_t ID, IMU_Data_t *Data);

  EStatus_t (*ReadSpecs)(IMU_specs_t *Specs);
}IMU_Functions_t;

#endif /* CUSTOM_TYPES_H */
