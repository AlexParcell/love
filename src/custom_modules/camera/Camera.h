// Seraphine Software 2025

#ifndef LOVE_CAMERA_H
#define LOVE_CAMERA_H

#include "common/Module.h"
#include "graphics/Texture.h"
#include "graphics/Quad.h"
#include "common/Vector.h"

namespace love
{
namespace camera
{
class CameraModule : public love::Module
{
public:
	CameraModule();
	virtual ~CameraModule() = default;

	bool m_bOffsetRenderingByCamera;
	Vector2 m_CameraLocation;
};

}
}

#endif
