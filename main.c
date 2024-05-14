#include <stdlib.h>
#include <stdint.h>
#include <gio/gio.h>
#include "app.h"


int main(void)
{
	g_print("---- Example Application ----\n");
	GDBusProxy *bluez_adapter_proxy = NULL;
	GMainLoop *loop;

	loop = g_main_loop_new(NULL, FALSE);

	app_register_application(bluez_adapter_proxy);

	g_main_loop_run(loop);

	return 0;
}
