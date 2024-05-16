#include "bluez_object.h"

#define DEV_ARR_SIZE 25

static GDBusProxy *bluez_object_proxy = NULL;

static GVariant *device_array[DEV_ARR_SIZE] = { NULL };
static int device_arr_i = 0; 

/**
 * Returns GVariant of type 'as'.
 *
 */
extern GVariant *bluez_object_get_devices()
{
	return g_variant_new_array(G_VARIANT_TYPE_STRING, device_array, device_arr_i);
}


/**
 * @brief When an interface is added (a device) this callback occurs.
 * 	@param parameters We own this pointer. so we must unreference it when we don't want it anymore
 *
 */
static void on_signal_interfaces_added(GDBusProxy* self, gchar* sender_name, gchar* signal_name, GVariant* parameters, gpointer user_data)
{
	const gchar *temp_object_path = NULL;
	const gchar *interface_name = NULL;
	GVariantIter *interfaces = NULL;
	GVariant *properties = NULL;

	//! We are extracting the object string (the device address).
	//! We don't need this to return anything except the object_path because
	//! We won't be calling any interfaces yet.
	g_variant_get(parameters, "(&oa{sa{sv}})", &temp_object_path, &interfaces);
	while(g_variant_iter_next(interfaces, "{&s*}", &interface_name, &properties))
	{
		g_variant_take_ref(properties);
		// If it's what we're looking for, save it to the list.
		if(g_strstr_len(g_ascii_strdown(interface_name, -1), -1, "device"))
		{
			if (device_arr_i < DEV_ARR_SIZE )
			{
				device_array[device_arr_i] = g_variant_new("s", temp_object_path); 
				device_arr_i++;
			}

			break;
		}
		g_variant_unref(properties);
	}

	// Free the iterator.
	g_variant_iter_free(interfaces);
}




extern void bluez_object_proxy_init(GDBusConnection *connection)
{
	GError *error = NULL;
	// Adapter interface proxy.
	// This will allow us to call methods via the proxy.
	bluez_object_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
			G_DBUS_PROXY_FLAGS_NONE,
			NULL,
			"org.bluez",
			"/", 
			"org.freedesktop.DBus.ObjectManager",
			NULL,
			&error);	
	
	if (bluez_object_proxy == NULL)
	{
		print_error(error);
		goto out;
	}

	g_signal_connect(bluez_object_proxy,
			"g-signal::InterfacesAdded",
			G_CALLBACK (on_signal_interfaces_added),
			NULL);

#ifdef DEBUG
	// Print the owner ID of the proxy object.
	print_proxy(bluez_object_proxy);
#endif

	return;

out:
	if (bluez_object_proxy != NULL)
		g_object_unref(bluez_object_proxy);

}
