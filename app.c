
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

extern void app_register_application()
{
	g_bus_own_name(G_BUS_TYPE_SESSION,
			"ti.example",
			G_BUS_NAME_OWNER_FLAGS_NONE,
			NULL,
			on_name_acquired,
			NULL,
			NULL,
			NULL);
}




