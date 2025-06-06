// Seraphine Software 2025

#include "common/config.h"

#include "wrap_Debugger.h"

namespace love
{
namespace debugger
{

#define instance() (Module::getInstance<DebugModule>(Module::M_DEBUGGER))

int w_Log(lua_State *L)
{
	DebugModule* instance = instance();
	instance->Log(L, 1);
	return 0;
}

int w_Break(lua_State *L)
{
	DebugModule* instance = instance();
	instance->Break(L);
	return 0;
}

static const luaL_Reg functions[] = 
{
	{ "log", w_Log },
	{ "breakpoint", w_Break },
	{ 0, 0 }
};

extern "C" int luaopen_love_debugger(lua_State * L)
{
	DebugModule* instance = instance();

	if (instance == nullptr)
	{
		luax_catchexcept(L, [&](){ instance = new DebugModule(); });
	}
	else
	{
		instance->retain();
	}

	WrappedModule w;
	w.module = instance;
	w.name = "debugger";
	w.type = &Module::type;
	w.functions = functions;
	w.types = 0;

	return luax_register_module(L, w);
}

}
}
