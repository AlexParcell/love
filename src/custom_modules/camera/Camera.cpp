#include "Camera.h"
#include "graphics/Texture.h"

namespace love
{
namespace camera
{

CameraModule::CameraModule()
	: Module(M_CAMERA, "love.camera")
	, m_CameraLocation(Vector2(500.0f, 500.0f))
	, m_bOffsetRenderingByCamera(true)
{

}

}
}
