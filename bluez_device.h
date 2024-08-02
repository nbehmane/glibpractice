#ifndef BLUEZ_DEVICE_H
#define BLUEZ_DEVICE_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "dbushelper.h"

#define MAX_CONNECTIONS 2

/*
 * UNUSED
 */
extern GDBusProxy **bluez_device_get_proxies();

/*
 *  @brief Connects to a device that has been scanned with DBus object path.
 *
 *  @param object_path Device object path
 */
extern void bluez_device_connect(const gchar *object_path);

extern void bluez_device_disconnect(const gchar *object_path);


#endif
