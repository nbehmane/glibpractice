#include "bluez_lemgr.h"

/* Forward Declarations */
static void on_properties_changed(GDBusProxy *proxy, GVariant *changed_properties, const gchar* const *invalidated_properties, gpointer user_data);
static void on_signal(GDBusProxy *proxy, gchar *sender_name, gchar *signal_name, GVariant *parameters, gpointer user_data);
static gboolean on_handle_release(LEAdvertisement1 *interface, GDBusMethodInvocation *invocation, gpointer user_data);

/* Static variables and arrays */
static GDBusProxy *bluez_lemgr_proxy = NULL;

// TODO: This should be a list because there could be multiple advertisments.
static LEAdvertisement1 *adv_interface = NULL;

static gchar *adv_path = NULL;

static GDBusProxy *adv_proxy = NULL;

/*
 *  ======== bluez_lemgr_create_adv ========
 *  TODO: Make it so this function takes in the properties.
 *  That way it doesn't hardcode them
 */
extern void bluez_lemgr_create_adv(GDBusConnection *connection, const gchar *object_path, gsize path_size)
{
	if (object_path == NULL)
		return;

	/* copy the path to be used when registering the advertisement */
	adv_path = g_memdup2(object_path, path_size);

	adv_interface = leadvertisement1_skeleton_new();

	// Advertisement Object
	g_signal_connect(adv_interface,
			"handle-release",
			G_CALLBACK (on_handle_release),
			NULL);

	// Set properties
	leadvertisement1_set_type_(adv_interface, "peripheral");

	g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON (adv_interface), 
			connection, 
			object_path,
			NULL);

	/* At this point we actualy need to get the advertisment object */

	GError *error = NULL;

	// This will allow us to call methods via the proxy.
	adv_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,
			G_DBUS_PROXY_FLAGS_NONE,
			NULL,
			"ti.example",
			adv_path, 
			"org.bluez.LEAdvertisement1",
			NULL,
			&error);	

	print_error(error);
}

/*
 *  ======== bluez_lemgr_register_adv ========
 */
extern void bluez_lemgr_register_adv(const gchar *object_path)
{	
	GError *error = NULL;


	g_dbus_proxy_call_sync( bluez_lemgr_proxy,
			"RegisterAdvertisement",
			g_variant_new("(oa{sv})", g_dbus_proxy_get_object_path(adv_proxy), NULL),
			G_DBUS_CALL_FLAGS_NONE,
			-1,
			NULL,
			&error);

	print_error(error);

	return;
}

/*
 *  ======== bluez_lemgr_proxy_init ========
 */
extern void bluez_lemgr_proxy_init(GDBusConnection *connection)
{
	GError *error = NULL;
	// Adapter interface proxy.
	// This will allow us to call methods via the proxy.
	bluez_lemgr_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
			G_DBUS_PROXY_FLAGS_NONE,
			NULL,
			"org.bluez",
			"/org/bluez/hci0", 
			"org.bluez.LEAdvertisingManager1",
			NULL,
			&error);	
	
	if (bluez_lemgr_proxy == NULL)
	{
		print_error(error);
		goto out;
	}

	g_signal_connect(bluez_lemgr_proxy,
			"g-properties-changed",
			G_CALLBACK (on_properties_changed),
			NULL);

	g_signal_connect(bluez_lemgr_proxy,
			"g-signal",
			G_CALLBACK(on_signal),
			NULL);

#ifdef DEBUG
	// Print the owner ID of the proxy object.
	print_proxy(bluez_lemgr_proxy);
#endif

	return;

out:
	if (bluez_lemgr_proxy != NULL)
		g_object_unref(bluez_lemgr_proxy);
}



/*
 *  ======== on_device_signal ========
 */
static void on_signal(GDBusProxy *proxy,
		gchar *sender_name,
		gchar *signal_name,
		GVariant *parameters,
		gpointer user_data)
{
#if DEBUG
	g_print("LEMgr: Signal\n");
#endif
}

/*
 *  ======== on_device_properties_changed ========
 */
static void on_properties_changed(GDBusProxy *proxy,
				GVariant *changed_properties,
				const gchar* const *invalidated_properties,
				gpointer user_data)
{
#if DEBUG 
	g_print("LEMgr: Properties Changed\n");
#endif
}

/*
 *  ======== on_handle_release ========
 */
static gboolean on_handle_release(LEAdvertisement1 *interface,
		GDBusMethodInvocation *invocation,
		gpointer user_data)
{
	// TODO: Free any data that was allocated by this advertisement.
	leadvertisement1_complete_release(interface, invocation);
	return TRUE;
}

