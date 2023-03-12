
set(PRIV_INCLUDE_DIRS_LIST
  "${APP_GEN_DIR}"
  "${CHIP_ROOT}/examples/providers"
  "${CHIP_ROOT}/examples/platform/esp32"
)

set(SRC_DIRS_LIST
  "${CMAKE_CURRENT_LIST_DIR}"

  "${CHIP_ROOT}/examples/platform/esp32/common"

  "${CHIP_ROOT}/examples/providers"
  "${CHIP_ROOT}/src/app/server"
  "${CHIP_ROOT}/src/app/util"

  "${CHIP_ROOT}/zzz_generated/app-common/app-common/zap-generated/attributes"

  # endpoint 0 clusters
  "${CHIP_ROOT}/src/app/clusters/groups-server"
  "${CHIP_ROOT}/src/app/clusters/descriptor"
  "${CHIP_ROOT}/src/app/clusters/access-control-server"
  "${CHIP_ROOT}/src/app/clusters/localization-configuration-server"
  "${CHIP_ROOT}/src/app/clusters/time-format-localization-server"
  "${CHIP_ROOT}/src/app/clusters/general-commissioning-server"
  "${CHIP_ROOT}/src/app/clusters/administrator-commissioning-server"
  "${CHIP_ROOT}/src/app/clusters/operational-credentials-server"
  "${CHIP_ROOT}/src/app/clusters/group-key-mgmt-server"
  "${CHIP_ROOT}/src/app/clusters/fixed-label-server"
  "${CHIP_ROOT}/src/app/clusters/user-label-server"
  "${CHIP_ROOT}/src/app/clusters/basic-information"
  "${CHIP_ROOT}/src/app/clusters/network-commissioning"

  # endpoint 1 clusters (groups & descriptor are already added)
  "${CHIP_ROOT}/src/app/clusters/identify-server"
  "${CHIP_ROOT}/src/app/clusters/scenes"
  "${CHIP_ROOT}/src/app/clusters/on-off-server"
)

set(PRIV_REQUIRES_LIST chip bt app_update nvs_flash)

idf_component_register(
  PRIV_INCLUDE_DIRS ${PRIV_INCLUDE_DIRS_LIST}
  SRC_DIRS ${SRC_DIRS_LIST}
  PRIV_REQUIRES ${PRIV_REQUIRES_LIST}
)

include("${CHIP_ROOT}/build/chip/esp32/esp32_codegen.cmake")
chip_app_component_codegen("${CMAKE_CURRENT_LIST_DIR}/zap/app.matter")
chip_app_component_zapgen("${CMAKE_CURRENT_LIST_DIR}/zap/app.zap")

target_compile_options(${COMPONENT_LIB} PUBLIC
           "-DCHIP_ADDRESS_RESOLVE_IMPL_INCLUDE_HEADER=<lib/address_resolve/AddressResolve_DefaultImpl.h>"
)

# -Wmaybe-uninitialized has too many false positives, including on std::optional
# and chip::Optional.  Make it nonfatal.
#
# See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80635
idf_build_set_property(COMPILE_OPTIONS "-Wno-error=maybe-uninitialized" APPEND)