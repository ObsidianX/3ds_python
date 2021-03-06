#include <string.h>

#include <3ds.h>

#include "py/runtime.h"

#define METHOD_OBJ_N(__args, __n) \
    STATIC MP_DEFINE_CONST_FUN_OBJ_##__args(mod_citrus_os_##__n##_obj, mod_citrus_os_##__n)

#define LOCAL_METHOD(__n) \
    {MP_OBJ_NEW_QSTR(MP_QSTR_##__n), (mp_obj_t) &mod_citrus_os_##__n##_obj}

STATIC mp_obj_t mod_citrus_os_get_firm_version(void) {
    return mp_obj_new_int_from_uint(osGetFirmVersion());
}

STATIC mp_obj_t mod_citrus_os_get_kernel_version(void) {
    return mp_obj_new_int_from_uint(osGetKernelVersion());
}

STATIC mp_obj_t mod_citrus_os_get_time(void) {
    return mp_obj_new_int_from_ull(osGetTime());
}

STATIC mp_obj_t mod_citrus_os_get_wifi_strength(void) {
    return mp_obj_new_int_from_uint(osGetWifiStrength());
}

STATIC mp_obj_t mod_citrus_os_get_3d_slider_state(void) {
    return mp_obj_new_float(osGet3DSliderState());
}

STATIC mp_obj_t mod_citrus_os_set_speedup_enable(mp_obj_t enable) {
    osSetSpeedupEnable(mp_obj_is_true(enable));

    return mp_const_none;
}

STATIC mp_obj_t mod_citrus_os_get_system_version_data(void) {
    OS_VersionBin nver, cver;

    osGetSystemVersionData(&nver, &cver);

    mp_obj_tuple_t *ret = mp_obj_new_tuple(5, NULL);

    ret->items[0] = mp_obj_new_int(cver.mainver);
    ret->items[1] = mp_obj_new_int(cver.minor);
    ret->items[2] = mp_obj_new_int(cver.build);
    ret->items[3] = mp_obj_new_int(nver.mainver);
    ret->items[4] = mp_obj_new_str(&nver.region, 1, true);

    return ret;
}

STATIC mp_obj_t mod_citrus_os_get_system_version_data_string(void) {
    char buffer[64];
    osGetSystemVersionDataString(NULL, NULL, buffer, sizeof(buffer));

    return mp_obj_new_str(buffer, strlen(buffer), true);
}

METHOD_OBJ_N(0, get_firm_version);
METHOD_OBJ_N(0, get_kernel_version);
METHOD_OBJ_N(0, get_time);
METHOD_OBJ_N(0, get_wifi_strength);
METHOD_OBJ_N(0, get_3d_slider_state);
METHOD_OBJ_N(1, set_speedup_enable);
METHOD_OBJ_N(0, get_system_version_data);
METHOD_OBJ_N(0, get_system_version_data_string);

STATIC const mp_rom_map_elem_t mp_module_citrus_os_globals_table[] = {
        // Package Info
        {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_os)},

        // Functions
        LOCAL_METHOD(get_firm_version),
        LOCAL_METHOD(get_kernel_version),
        LOCAL_METHOD(get_time),
        LOCAL_METHOD(get_wifi_strength),
        LOCAL_METHOD(get_3d_slider_state),
        LOCAL_METHOD(set_speedup_enable),
        LOCAL_METHOD(get_system_version_data),
        LOCAL_METHOD(get_system_version_data_string),
};

STATIC MP_DEFINE_CONST_DICT(mp_module_citrus_os_globals, mp_module_citrus_os_globals_table);

const mp_obj_module_t mp_module_citrus_os = {
        .base = {&mp_type_module},
        .name = MP_QSTR_os,
        .globals = (mp_obj_dict_t *) &mp_module_citrus_os_globals,
};