// Seraphine Software 2025

#include "common/config.h"

#include "wrap_Camera.h"

namespace love
{
namespace camera
{

#define instance() (Module::getInstance<CameraModule>(Module::M_CAMERA))

static const luaL_Reg functions[] = 
{
	{ 0, 0 }
};

extern "C" int luaopen_love_camera(lua_State * L)
{
	CameraModule* instance = instance();

	if (instance == nullptr)
	{
		luax_catchexcept(L, [&](){ instance = new CameraModule(); });
	}
	else
	{
		instance->retain();
	}

	WrappedModule w;
	w.module = instance;
	w.name = "camera";
	w.type = &Module::type;
	w.functions = functions;
	w.types = 0;

	return luax_register_module(L, w);
}

}
}
