
#include "esp_log.h"
#include "nvs_flash.h"

#include "DeviceCallbacks.h"

#include <common/CHIPDeviceManager.h>
#include <common/Esp32AppServer.h>

#include <DeviceInfoProviderImpl.h>
#include <app/server/OnboardingCodesUtil.h>

#include <credentials/examples/DeviceAttestationCredsExample.h>

using namespace ::chip;
using namespace ::chip::Credentials;
using namespace ::chip::DeviceManager;
using namespace ::chip::DeviceLayer;

static const char *TAG = "esp32-matter-app";

static AppDeviceCallbacks EchoCallbacks;

static void InitServer(intptr_t context)
{
  // Print QR Code URL
  PrintOnboardingCodes(chip::RendezvousInformationFlags(CONFIG_RENDEZVOUS_MODE));
  Esp32AppServer::Init(); // Init ZCL Data Model and CHIP App Server AND Initialize device attestation config
}

extern "C" void app_main()
{
  // Initialize the ESP NVS layer.
  esp_err_t err = nvs_flash_init();
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "nvs_flash_init() failed: %s", esp_err_to_name(err));
    return;
  }
  ESP_LOGI(TAG, "### esp32-matter-app starting ###");

  CHIPDeviceManager &deviceMgr = CHIPDeviceManager::GetInstance();
  CHIP_ERROR         error = deviceMgr.Init(&EchoCallbacks);
  if (error != CHIP_NO_ERROR) {
    ESP_LOGE(TAG, "device.Init() failed: %s", ErrorStr(error));
    return;
  }

  SetDeviceAttestationCredentialsProvider(Examples::GetExampleDACProvider());
  DeviceLayer::PlatformMgr().ScheduleWork(InitServer, reinterpret_cast<intptr_t>(nullptr));
}
