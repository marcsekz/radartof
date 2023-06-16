#include "app_camera.h"
#include "ov5640.h"
#include "custom_errno.h"
#include "stm32h747i_discovery_camera.h"

I2C_HandleTypeDef* camera_i2c_handle;
DCMI_HandleTypeDef* camera_dcmi_handle;

// void                *Camera_CompObj = NULL;
extern CAMERA_Ctx_t        Camera_Ctx[CAMERA_INSTANCES_NBR];

static CAMERA_Drv_t *Camera_Drv = NULL;
static CAMERA_Capabilities_t Camera_Cap;
static uint32_t HSPolarity = DCMI_HSPOLARITY_LOW;
static uint32_t CameraId;

static HAL_StatusTypeDef OV5640_Probe(uint32_t Resolution, uint32_t PixelFormat);

void Camera_Init(I2C_HandleTypeDef* hi2c, DCMI_HandleTypeDef* hdcmi, uint32_t resolution, uint32_t pixformat)
{
  camera_i2c_handle = hi2c;
  camera_dcmi_handle = hdcmi;

  BSP_CAMERA_Init(0, resolution, pixformat);

  BSP_CAMERA_Start(0, (uint8_t*) CAMERA_FRAMEBUFFER, CAMERA_MODE_CONTINUOUS);
}