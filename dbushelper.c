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


void print_error(GError *error)
{

	if (error == NULL)
		return;
	g_printerr("Error: %s\n", error->message);
	g_error_free(error);
}	

void print_is_floating(GVariant *variant)
{
	if (g_variant_is_floating(variant))
	{
		g_print("Floating.\n");
		return;
	}
	g_print("Not floating.\n");
}

// Example: /org/bluez/dev_xx_xx_xx_xx_xx_xx

GVariant *object_tokenizer(const gchar *object_path, int max_tokens)
{
	gchar **tokens = NULL;
	GVariant *result = NULL;

	tokens = g_strsplit(object_path, "/", max_tokens);


	for (int i = 0; tokens[i] != NULL; i++)
	{
		if (i == max_tokens - 1)
		{
			result = g_variant_new("s", tokens[i]);
			break;
		}
		result = NULL;

	}
	g_strfreev(tokens);
	return result;
}


