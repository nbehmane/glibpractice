#include "bluez_device.h"

static GDBusProxy *device_proxies[MAX_CONNECTIONS] = { NULL };




static GDBusProxy *bluez_device_setup_proxy(const gchar *object_path)
{
	//1. Create the proxy object from the path and connect it to the right interface org.bluez.Device1
	//2. setup the signal handlers for this particular proxy.
	//3. return the proxy if it was successfull otherwise return null.
	return NULL;
}

extern void bluez_device_connect(const gchar *object_path)
{
	//1. Create the proxy object for the object path and store it somewhere. 
	//2. Setup the signal handlers for the proxy object so we can manage the connection
	//3. return
	return;
}

extern void bluez_device_disconnect(const gchar *object_path)
{
	//1. grab the correct proxy object.
	//2. disconnect
	//3. remove it from the list of device proxies.
	return;
}
