#ifndef DBUS_HELPER_H
#define DBUS_HELPER_H
#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>

/* print_proxy
 *
 * @brief Prints the application ID on bus.
 *
 */
void print_proxy(GDBusProxy *proxy);
void print_error(GError *error);
void print_is_floating(GVariant *variant);
GVariant *object_tokenizer(const gchar *object_path, int max_tokens);


#endif
