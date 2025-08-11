/**
 ******************************************************************************
 * @file           : usbd_custom_hid_if.c
 * @version        : v1.0_Cube
 * @brief          : USB Device Custom HID interface file.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
 * @brief Usb device.
 * @{
 */

/** @addtogroup USBD_CUSTOM_HID
 * @{
 */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
 * @brief Private types.
 * @{
 */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
 * @brief Private defines.
 * @{
 */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
 * @brief Private macros.
 * @{
 */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
 * @brief Private variables.
 * @{
 */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[] __ALIGN_END =
{
        0x06, 0x00, 0xFF, // USAGE_PAGE (Vendor Defined 0xFF00)
        0x09, 0x01,       // USAGE (1) <-- REQUIRED before COLLECTION
        0xA1, 0x01,       // COLLECTION (Application)

        // Optional: Nested Physical Collection
        0xA1, 0x00, // COLLECTION (Physical)

        // Input Report (Report ID 1)
        0x85, 0x01,       //   REPORT_ID (1)
        0x95, 0x3F,       //   REPORT_COUNT (63)
        0x75, 0x08,       //   REPORT_SIZE (8)
        0x15, 0x00,       //   LOGICAL_MINIMUM (0)
        0x26, 0xFF, 0x00, //   LOGICAL_MAXIMUM (255)
        0x09, 0x01,       //   USAGE (1)
        0x81, 0x02,       //   INPUT (Data,Var,Abs)

        // Output Report (Report ID 2)
        0x85, 0x02,       //   REPORT_ID (2)
        0x95, 0x3F,       //   REPORT_COUNT (63)
        0x75, 0x08,       //   REPORT_SIZE (8)
        0x15, 0x00,       //   LOGICAL_MINIMUM (0)
        0x26, 0xFF, 0x00, //   LOGICAL_MAXIMUM (255)
        0x09, 0x02,       //   USAGE (2)
        0x91, 0x02,       //   OUTPUT (Data,Var,Abs)

        // Feature Report (Report ID 3)
        0x85, 0x03,       //   REPORT_ID (3)
        0x95, 0x3F,       //   REPORT_COUNT (63)
        0x75, 0x08,       //   REPORT_SIZE (8)
        0x15, 0x00,       //   LOGICAL_MINIMUM (0)
        0x26, 0xFF, 0x00, //   LOGICAL_MAXIMUM (255)
        0x09, 0x03,       //   USAGE (3)
        0xB1, 0x02,       //   FEATURE (Data,Var,Abs)

        0xC0, // END_COLLECTION (Physical)
        0xC0  // END_COLLECTION (Application)
};

const uint32_t CUSTOM_HID_ReportDesc_FS_size = sizeof(CUSTOM_HID_ReportDesc_FS);

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
 * @brief Public variables.
 * @{
 */
extern USBD_HandleTypeDef hUsbDeviceFS;

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
 * @brief Private functions declaration.
 * @{
 */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t* report_buffer);
int8_t CUSTOM_HID_CtrlReqComplete_FS(uint8_t request, uint16_t wLength);
uint8_t* CUSTOM_HID_GetReport_FS(uint16_t *ReportLength);


USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS,
  CUSTOM_HID_CtrlReqComplete_FS,
  CUSTOM_HID_GetReport_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
 * @brief Private functions.
 * @{
 */

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Initializes the CUSTOM HID media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_Init_FS(void)
{
  return (USBD_OK);
}

/**
 * @brief  DeInitializes the CUSTOM HID media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  return (USBD_OK);
}

/**
 * @brief  Manage the CUSTOM HID class events
 * @param  event_idx: Event index
 * @param  state: Event state
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t* report_buffer)
{
  UNUSED(report_buffer);

  /* Start next USB packet transfer once data processing is completed */
  if (USBD_CUSTOM_HID_ReceivePacket(&hUsbDeviceFS) != (uint8_t)USBD_OK)
  {
    return -1;
  }

  return (USBD_OK);
}

/**
 * @brief  Send the report to the Host
 * @param  report: The report to be sent
 * @param  len: The report length
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}

int8_t CUSTOM_HID_CtrlReqComplete_FS(uint8_t request, uint16_t wLength) {
	// The return value isn't used and doesn't matter
	return 0;
}

uint8_t* CUSTOM_HID_GetReport_FS(uint16_t *ReportLength) {
	*ReportLength = 64;
	// Just for testing
	static uint8_t data[64] = {3, 1, 2, 3, 4, 5, 6, 7};
	return data;
}
