// Seraphine Software 2025

#include "common/config.h"

#include "wrap_Debugger.h"

namespace love
{
namespace debugger
{

#define instance() (Module::getInstance<DebugModule>(Module::M_DEBUGGER))

static const luaL_Reg functions[] = 
{
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
