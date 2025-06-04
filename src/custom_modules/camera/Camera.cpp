#include "Camera.h"
#include "graphics/Texture.h"
#include "window/Window.h"

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

void CameraModule::TransformLocationByCameraLocation(float &OutX, float &OutY)
{
	OutX -= m_CameraLocation.x;
	OutY -= m_CameraLocation.y;

	window::Window *winModule = Module::getInstance<window::Window>(Module::M_WINDOW);
	if (winModule)
	{
		OutX += (winModule->getWidth() / 2);
		OutY += (winModule->getHeight() / 2);
	}
}

}
}
