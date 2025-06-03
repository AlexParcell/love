// Seraphine Software 2025

#include "common/config.h"

#include "wrap_Camera.h"

namespace love
{
namespace camera
{

#define instance() (Module::getInstance<CameraModule>(Module::M_CAMERA))

int w_getCameraLocation(lua_State *L)
{
	lua_pushnumber(L, instance()->m_CameraLocation.x);
	lua_pushnumber(L, instance()->m_CameraLocation.y);

	return 2;
}

int w_setCameraLocation(lua_State *L)
{
	double X = luaL_checknumber(L, 1);
	double Y = luaL_checknumber(L, 2);
	instance()->m_CameraLocation = Vector2(X, Y);
	return 0;
}

int w_offsetCameraLocation(lua_State *L)
{
	double X = luaL_checknumber(L, 1);
	double Y = luaL_checknumber(L, 2);
	instance()->m_CameraLocation += Vector2(X, Y);
	return 0;
}

int w_setCameraRenderingActive(lua_State *L)
{
	bool active = luax_checkboolean(L, 1);
	instance()->m_bOffsetRenderingByCamera = active;
	return 0;
}

int w_getCameraRenderingActive(lua_State *L)
{
	luax_pushboolean(L, instance()->m_bOffsetRenderingByCamera);
	return 1;
}

static const luaL_Reg functions[] = 
{
	{ "getCameraLocation", w_getCameraLocation },
	{ "setCameraLocation", w_setCameraLocation },
	{ "offsetCameraLocation", w_offsetCameraLocation },
	{ "setCameraRenderingActive", w_setCameraRenderingActive },
	{ "getCameraRenderingActive", w_getCameraRenderingActive },
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
