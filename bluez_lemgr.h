#ifndef BLUEZ_LEMGR_H
#define BLUEZ_LEMGR_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "dbushelper.h"
#include "./gen/leadvertisement.h"

extern void bluez_lemgr_register_adv(const gchar *object_path);
extern void bluez_lemgr_proxy_init(GDBusConnection *connection);
extern void bluez_lemgr_create_adv(GDBusConnection *connection, const gchar *object_path);


#endif
