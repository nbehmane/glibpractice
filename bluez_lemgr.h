#ifndef BLUEZ_LEMGR_H
#define BLUEZ_LEMGR_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "dbushelper.h"
#include "./gen/leadvertisement.h"

/*  
 *  @brief Initializes a proxy object to the LEAdvertisingManager1 interface.
 *
 *  @param connection		A GDBusConnection to the bus to create the proxy on.
 */
extern void bluez_lemgr_proxy_init(GDBusConnection *connection);

/*
 *  @brief Registers an advertisment object using it's object path.
 *
 *  @param object_path		The object path to the advertisment. 
 */
extern void bluez_lemgr_register_adv(const gchar *object_path);

/*
 *  @brief Registers an advertisment object using it's object path.
 *
 *  @param connection		The bus to create the advertisment object on (i.e name). 
 *  @param object_path		Object path for the advertisement. 
 */
extern void bluez_lemgr_create_adv(GDBusConnection *connection, const gchar *object_path, gsize path_size);


#endif
