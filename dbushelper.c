#include "dbushelper.h"


/* print_proxy
 *
 * @brief Prints the application ID on bus.
 *
 */
void print_proxy(GDBusProxy *proxy)
{
	gchar *name_owner; name_owner = g_dbus_proxy_get_name_owner(proxy);
	g_print("Owner: %s\n", name_owner);
}

