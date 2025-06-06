#include "Debugger.h"
#include <iostream>

namespace love
{
namespace debugger
{

DebugModule::DebugModule()
	: Module(M_DEBUGGER, "love.debugger")
{

}

void DebugModule::Log(lua_State *L, int index, int indentLevel, std::unordered_set<const void*>* visited) 
{
	int type = lua_type(L, index);

	if (type == LUA_TTABLE)
	{
		const void *ptr = lua_topointer(L, index);
		if (!visited)
		{
			visited = new std::unordered_set<const void *>();
		}

		if (visited->count(ptr))
		{
			std::cout << Indent(indentLevel) << "{...}  -- already visited" << std::endl;
			return;
		}

		visited->insert(ptr);
		std::cout << "{" << std::endl;

		// Make sure index is absolute
		if (index < 0)
		{
			index = lua_gettop(L) + index + 1;
		}

		lua_pushnil(L); // first key
		while (lua_next(L, index))
		{
			std::cout << Indent(indentLevel + 1) << "[";

			// Print key
			PrintValueInLine(L, -2);
			std::cout << "] = ";

			// Print value
			Log(L, -1, indentLevel + 1, visited);

			lua_pop(L, 1); // pop value
		}

		std::cout << Indent(indentLevel) << "}" << std::endl;
	}
	else
	{
		PrintValueInLine(L, index);
		std::cout << std::endl;
	}
}

void DebugModule::LogCallStack(lua_State *L)
{
	lua_Debug ar;
	int depth = 0;

	std::cout << "Lua Call Stack Trace: " << std::endl;
	while (lua_getstack(L, depth, &ar))
	{
		lua_getinfo(L, "nSl", &ar);
		std::cout << "#" << depth << " ";
		if (ar.name)
		{
			std::cout << ar.name << " ";
		}
		else
		{
			std::cout << "?" << " ";
		}
		std::cout << "(" << ar.short_src << ":" << ar.currentline << ")" << std::endl;
		++depth;
	}

	if (depth == 0)
	{
		std::cout << "(Call stack is empty)" << std::endl;
	}
}

void DebugModule::LogValueStack(lua_State *L)
{
	int top = lua_gettop(L);
	std::cout << "[Lua Value Stack] Top = " << top << std::endl;

	for (int i = 1; i <= top; ++i)
	{
		Log(L, i);
	}

	if (top == 0)
	{
		std::cout << "(stack is empty)" << std::endl;
	}
}

void DebugModule::Break(lua_State *L /*= nullptr*/)
{
	std::cout << "[DEBUG BREAKPOINT]" << std::endl;
	
	std::cout << "[CALL STACK]:" << std::endl;
	if (L)
	{
		LogCallStack(L);
	}
	std::cout << std::endl;

	std::cout << "[VALUE STACK]:" << std::endl;
	if (L)
	{
		LogValueStack(L);
	}
	std::cout << std::endl;

	std::cout << "[LOCALS]:" << std::endl;
	if (L)
	{
		LogLocals(L);
	}
	std::cout << std::endl;

	std::cout << "Press enter to continue." << std::endl;
	std::cin.ignore();
}

void DebugModule::LogLocals(lua_State *L, int stackLevel)
{
	lua_Debug ar;
	if (lua_getstack(L, stackLevel, &ar))
	{
		int i = 1;
		const char *name;
		while ((name = lua_getlocal(L, &ar, i)) != nullptr)
		{
			std::cout << name << " = ";

			Log(L, -1);
			lua_pop(L, 1);  // remove value from stack
			i++;
		}
	}
	else
	{
		std::cout << "No stack frame at level " << stackLevel << std::endl;
	}
}

void DebugModule::PrintValueInLine(lua_State *L, int index)
{
	int type = lua_type(L, index);
	switch (type)
	{
	case LUA_TNIL:
		std::cout << "nil";
		break;
	case LUA_TBOOLEAN:
		std::cout << (lua_toboolean(L, index) ? "true" : "false");
		break;
	case LUA_TNUMBER:
		std::cout << lua_tonumber(L, index);
		break;
	case LUA_TSTRING:
		std::cout << "\"" << lua_tostring(L, index) << "\"";
		break;
	case LUA_TTABLE:
	case LUA_TFUNCTION:
	case LUA_TUSERDATA:
	case LUA_TTHREAD:
	case LUA_TLIGHTUSERDATA:
		std::cout << lua_typename(L, type) << ":" << lua_topointer(L, index);
		break;
	default:
		std::cout << lua_typename(L, type);
	}
}

}
}
