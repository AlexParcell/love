// Seraphine Software 2025.

#ifndef LOVE_CAMERA_WRAP_CAMERA_H
#define LOVE_CAMERA_WRAP_CAMERA_H

#include "common/runtime.h"
#include "Camera.h"

namespace love
{
namespace camera
{

extern "C" LOVE_EXPORT int luaopen_love_camera(lua_State* L);

}
}

#endif
