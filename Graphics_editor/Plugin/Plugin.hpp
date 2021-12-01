#ifndef PLUGIN_SUPPORT_HPP
#define PLUGIN_SUPPORT_HPP

#include <dlfcn.h>

class Plugin
{
protected:
	void *handle;

public:
	Plugin(const char *dll_name)
	{
		handle = dlopen(dll_name, RTLD_LAZY);
		// Не забудь вызвать init
	}

	~Plugin()
	{
		// Не забудь вызвать deinit
		dlclose(handle);
	}
};

#endif // PLUGIN_SUPPORT_HPP
