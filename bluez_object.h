#ifndef BLUEZ_OBJECT_H
#define BLUEZ_OBJECT_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "dbushelper.h"

#define DEV_ARR_SIZE 25

/**
 * @brief Returns the devices from scanning. 
 *
 * @return A GVariant* array of type 'as'. Note that the device strings are
 * 	in the form of object paths, not Bluetooth addresses. It's recommended
 * 	to tokenize these when needed.
 *
 */
extern GVariant *bluez_object_get_devices();

extern void bluez_object_proxy_init(GDBusConnection *connection);


#endif
