#include "Camera.h"
#include "graphics/Texture.h"
#include "window/Window.h"

namespace love
{
namespace camera
{

CameraModule::CameraModule()
	: Module(M_CAMERA, "love.camera")
	, m_CameraLocation(Vector2(0.0f, 0.0f))
	, m_bOffsetRenderingByCamera(false)
{

}

love::Matrix4 CameraModule::GetTransformMatrix() const
{
	float OutX = -m_CameraLocation.x;
	float OutY = -m_CameraLocation.y;

	window::Window *winModule = Module::getInstance<window::Window>(Module::M_WINDOW);
	if (winModule)
	{
		OutX += (winModule->getWidth() / 2);
		OutY += (winModule->getHeight() / 2);
	}

	Vector2 OutVector = love::Vector2(OutX, OutY);
	Matrix4 CameraMatrix = Matrix4(OutVector.x, OutVector.y, 0, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	return CameraMatrix;
}

love::Matrix4 CameraModule::TransformByCameraLocation(const Matrix4 &InMatrix)
{
	return GetTransformMatrix() * InMatrix;
}

}
}
