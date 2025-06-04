// Seraphine Software 2025.

#ifndef LOVE_DEBUGGER_WRAP_DEBUGGER_H
#define LOVE_DEBUGGER_WRAP_DEBUGGER_H

#include "common/runtime.h"
#include "Debugger.h"

namespace love
{
namespace debugger
{

extern "C" LOVE_EXPORT int luaopen_love_debugger(lua_State* L);

}
}

#endif
