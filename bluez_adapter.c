#include "bluez_adapter.h"
#include "dbushelper.h"

// Signal Callbacks
static void on_adapter_properties_changed(GDBusProxy *proxy, GVariant *changed_properties, const gchar* const *invalidated_properties, gpointer user_data);
static void on_adapter_signal(GDBusProxy *proxy, gchar *sender_name, gchar *signal_name, GVariant *parameters, gpointer user_data);

// Method Calls
extern void bluez_adapter_scan(guint time);

// Proxy handle
static GDBusProxy *bluez_adapter_proxy = NULL;


/**
 * @brief Initiates scanning, populating the bluez.org namespace with device objects.
 *
 * @param s Set 1 to start scanning and 0 to stop scanning.
 */
extern void bluez_adapter_scan(guint s)
{
	GError *error = NULL;

	const gchar* discov = s ? "StartDiscovery" : "StopDiscovery";
	g_dbus_proxy_call_sync( bluez_adapter_proxy,
			discov,
			g_variant_new("()", NULL),
			G_DBUS_CALL_FLAGS_NONE,
			-1,
			NULL,
			&error);


	print_error(error);
}



/**
 * @brief Initializes the GDBusProxy object to get access to the org.bluez.Adapter1 methods.
 * 	Connects to two signals: g-properties-changed and g-signal. Currently, neither of 
 * 	these signals are used. 
 *
 * 	TODO: Make the selection of the controller dynamic.
 *
 * @param connection Not used.
 */
extern void bluez_adapter_proxy_init(GDBusConnection *connection)
{
	GError *error = NULL;
	// Adapter interface proxy.
	// This will allow us to call methods via the proxy.
	bluez_adapter_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
			G_DBUS_PROXY_FLAGS_NONE,
			NULL,
			"org.bluez",
			"/org/bluez/hci0", 
			"org.bluez.Adapter1",
			NULL,
			&error);	
	
	if (bluez_adapter_proxy == NULL)
	{
		print_error(error);
		goto out;
	}

	g_signal_connect(bluez_adapter_proxy,
			"g-properties-changed",
			G_CALLBACK (on_adapter_properties_changed),
			NULL);

	g_signal_connect(bluez_adapter_proxy,
			"g-signal",
			G_CALLBACK(on_adapter_signal),
			NULL);

#ifdef DEBUG
	// Print the owner ID of the proxy object.
	print_proxy(bluez_adapter_proxy);
#endif

	return;

out:
	if (bluez_adapter_proxy != NULL)
		g_object_unref(bluez_adapter_proxy);
}



/**** SIGNAL HANDLERS START ****/
static void on_adapter_signal(GDBusProxy *proxy,
		gchar *sender_name,
		gchar *signal_name,
		GVariant *parameters,
		gpointer user_data)
{
#ifdef DEBUG
	g_print("Adapter: Signal\n");
#endif
}


static void on_adapter_properties_changed(GDBusProxy *proxy,
				GVariant *changed_properties,
				const gchar* const *invalidated_properties,
				gpointer user_data)
{
#ifdef DEBUG
	g_print("Adapter: Properties Changed\n");
#endif
}
/**** SIGNAL HANDLERS END ****/
