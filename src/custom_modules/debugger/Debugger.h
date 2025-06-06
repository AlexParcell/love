// Seraphine Software 2025

#ifndef LOVE_DEBUGGER_H
#define LOVE_DEBUGGER_H

#include "common/Module.h"
#include "graphics/Texture.h"
#include "graphics/Quad.h"
#include "common/Vector.h"
#include "common/runtime.h"
#include <string>
#include <unordered_set>

namespace love
{
namespace debugger
{
class DebugModule : public love::Module
{
public:
	DebugModule();
	virtual ~DebugModule() = default;

	void Log(lua_State *L, int index, int indentLevel = 0, std::unordered_set<const void *> *visited = nullptr);
	void LogCallStack(lua_State* L);
	void LogValueStack(lua_State *L);
	void Break(lua_State *L /*= nullptr*/);

private:
	static std::string Indent(int level)
	{
		return std::string(level*2, ' ');
	}

	void PrintValueInLine(lua_State* L, int index);
};

}
}

#endif
