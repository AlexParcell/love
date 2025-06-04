// Seraphine Software 2025

#ifndef LOVE_DEBUGGER_H
#define LOVE_DEBUGGER_H

#include "common/Module.h"
#include "graphics/Texture.h"
#include "graphics/Quad.h"
#include "common/Vector.h"

namespace love
{
namespace debugger
{
class DebugModule : public love::Module
{
public:
	DebugModule();
	virtual ~DebugModule() = default;
};

}
}

#endif
