
/**
 * @brief All application specific functions (signal handlers, interface definitions, etc.)
 * 	should go into a .c file. These functions should not be called directly (hence they're static).
 * 	The only exposed function to main.c should be <object>_register_<object>. In this case
 * 	it's app_register_application.
 *
 *
 */


#include "app.h"


#define VERSION "1.0.0"


/*
 * @brief XML defintion for function
 *
 * <method name="Version">
 * 	<arg name="response" direction="out" type="s"/>
 * </method>
 */
static gboolean on_handle_version(AppInfo *interface, 
		GDBusMethodInvocation *invocation,
		const char *version,
		const char *description,
		gpointer user_data)
{
	version = VERSION;
	description = "Skeleton App - Architecture example for creating new applications.";

	g_print("%s\n", version);
	g_print("%s\n", description);




	
	app_info_complete_version(interface, invocation, version, description);
	return TRUE;
}


static void on_name_acquired(GDBusConnection *connection, 
		const gchar *name, 
		gpointer user_data)
{
	AppInfo *interface = NULL;
	GError *error = NULL;

	interface = app_info_skeleton_new();
	g_signal_connect(interface,
			"handle-version",
			G_CALLBACK (on_handle_version),
			NULL);

	g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON (interface), 
			connection, 
			"/ti/example/AppInfo",
			&error);
}


/*TEMP FUNC*/

static void on_signal(GDBusProxy *proxy,
		gchar *sender_name,
		gchar *signal_name,
		GVariant *parameters,
		gpointer user_data)
{
	g_print("Adapter: Signal\n");
}


static void on_properties_changed(GDBusProxy *proxy,
				GVariant *changed_properties,
				const gchar* const *invalidated_properties,
				gpointer user_data)
{
	g_print("Adapter: Properties Changed\n");
}


static void print_proxy(GDBusProxy *proxy)
{
	gchar *name_owner;
	name_owner = g_dbus_proxy_get_name_owner(proxy);
	g_print("Owner: %s\n", name_owner);
}

static void on_name_owner_notify(GObject *object,
		GParamSpec *pspec,
		gpointer user_data)
{
	GDBusProxy *proxy = G_DBUS_PROXY(object);
	print_proxy(proxy);
}

extern void app_register_application(GDBusProxy *bluez_adapter_proxy)
{
	GError *error = NULL;

	// This is the MAIN application session.
	g_bus_own_name(G_BUS_TYPE_SESSION,
			"ti.example",
			G_BUS_NAME_OWNER_FLAGS_NONE,
			NULL,
			on_name_acquired,
			NULL,
			NULL,
			NULL);

	/* BLUEZ */
	// This is the BlueZ object we can call methods on
	// Notice that this for the adapter object.
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
		g_printerr("Error in creating proxy: %s\n", error->message);
		g_error_free(error);
		goto out;
	}

	g_signal_connect(bluez_adapter_proxy,
			"notify::g-name-owner",
			G_CALLBACK (on_name_owner_notify),
			NULL);

	g_signal_connect(bluez_adapter_proxy,
			"g-properties-changed",
			G_CALLBACK (on_properties_changed),
			NULL);
	g_signal_connect(bluez_adapter_proxy,
			"g-signal",
			G_CALLBACK(on_signal),
			NULL);


	print_proxy(bluez_adapter_proxy);

	return;

out:
	if (bluez_adapter_proxy != NULL)
		g_object_unref(bluez_adapter_proxy);
}

