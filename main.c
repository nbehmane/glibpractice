#include <stdlib.h>
#include <gio/gio.h>
#include "Object.h"

static gboolean emit_object_cb(gpointer skeleton)
{
	object_emit_beep(OBJECT(skeleton));
	object_set_activated(OBJECT(skeleton), FALSE);
	return FALSE;
}

static gboolean on_handle_configure(Object *skeleton,
		GDBusMethodInvocation *invocation,
		guint seconds,
		gpointer user_data)
{
	if (object_get_activated(skeleton)) 
	{
		g_dbus_method_invocation_return_error_literal(
				invocation, G_IO_ERROR, G_IO_ERROR_EXISTS, "Exists");
		return TRUE;
	}

	object_set_activated(skeleton, TRUE);
	g_timeout_add_seconds(seconds, emit_object_cb, skeleton);
}

static void on_name_acquired(GDBusConnection *connection,
		const gchar *name,
		gpointer user_data)
{
	Object *skeleton;
	skeleton = object_skeleton_new();

	g_signal_connect(skeleton,
			"handle-configure",
			G_CALLBACK (on_handle_configure),
			NULL);

	g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(skeleton),
			connection,
			"/ti/example/Object",
			NULL);
}


int main(void)
{
	g_print("---- Example Application ----\n");

	GMainLoop *loop;
	loop = g_main_loop_new(NULL, FALSE);
	g_bus_own_name(G_BUS_TYPE_SESSION,
			"ti.example.Object",
			G_BUS_NAME_OWNER_FLAGS_NONE,
			NULL,
			on_name_acquired,
			NULL,
			NULL,
			NULL);

	g_main_loop_run(loop);
	return 0;
}
