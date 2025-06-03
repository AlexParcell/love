#include "Animation.h"
#include "graphics/Texture.h"

namespace love
{
animation::AnimationModule::AnimationModule()
	: Module(M_ANIMATION, "love.animation")
{

}

animation::Animation* animation::AnimationModule::NewAnimation(
	graphics::Texture *InTexture,
	int InStartX,
	int InStartY,
	int InFrameCount,
	int InSpritesheetDirX,
	int InSpritesheetDirY,
	int InFrameWidth,
	int InFrameHeight,
	float InFrameInterval
)
{
	return new animation::Animation(
		InTexture,
		InStartX, InStartY,
		InFrameCount,
		InSpritesheetDirX, InSpritesheetDirY,
		InFrameHeight, InFrameWidth,
		InFrameInterval
	);
}

animation::Animation::Animation(
	graphics::Texture *InTexture,
	int InStartX,
	int InStartY,
	int InFrameCount,
	int InSpritesheetDirX,
	int InSpritesheetDirY,
	int InFrameWidth,
	int InFrameHeight,
	float InFrameInterval
)
	: m_SpritesheetTexture(InTexture)
	, m_StartX(InStartX)
	, m_StartY(InStartY)
	, m_FrameCount(InFrameCount)
	, m_SpritesheetDirectionX(InSpritesheetDirX)
	, m_SpritesheetDirectionY(InSpritesheetDirY)
	, m_FrameHeight(InFrameHeight)
	, m_FrameWidth(InFrameWidth)
	, m_FrameInterval(InFrameInterval)
	, m_CurrentFrame(0)
	, m_ElapsedTime(0.0f)
	, m_OffsetX(0)
	, m_OffsetY(0)
{

}

void animation::Animation::Update(float DeltaTime)
{
	m_ElapsedTime += DeltaTime;
	if (m_ElapsedTime >= m_FrameInterval)
	{
		m_CurrentFrame++;
		m_CurrentFrame %= m_FrameCount;
		m_ElapsedTime = 0;
	}
}
}
