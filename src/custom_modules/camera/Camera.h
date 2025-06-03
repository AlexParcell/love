// Seraphine Software 2025

#ifndef LOVE_CAMERA_H
#define LOVE_CAMERA_H

#include "common/Module.h"
#include "graphics/Texture.h"
#include "graphics/Quad.h"

namespace love
{
namespace camera
{
class CameraModule : public love::Module
{
public:
	CameraModule();
	virtual ~CameraModule() = default;
};

}
}

#endif
