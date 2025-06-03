// Seraphine Software 2025

#ifndef LOVE_ANIMATION_H
#define LOVE_ANIMATION_H

#include "common/Module.h"
#include "graphics/Texture.h"
#include "graphics/Quad.h"

namespace love
{
namespace animation
{
class Animation : public Object
{
public:
	Animation(
		graphics::Texture *InTexture,
		int InStartX,
		int InStartY,
		int InFrameCount,
		int InSpritesheetDirX,
		int InSpritesheetDirY,
		int InFrameWidth,
		int InFrameHeight,
		float InFrameInterval
	);

	void Update(float DeltaTime);

	int m_FrameCount;
	int m_StartX;
	int m_StartY;
	int m_SpritesheetDirectionX;
	int m_SpritesheetDirectionY;
	int m_FrameWidth;
	int m_FrameHeight;
	float m_FrameInterval;
	graphics::Texture *m_SpritesheetTexture;

	float m_ElapsedTime;
	int m_CurrentFrame;
	int m_OffsetX;
	int m_OffsetY;
};

class AnimationModule : public love::Module
{
public:
	AnimationModule();
	virtual ~AnimationModule() = default;

	Animation* NewAnimation(
		graphics::Texture* InTexture, 
		int InStartX,
		int InStartY,
		int InFrameCount,
		int InSpritesheetDirX,
		int InSpritesheetDirY,
		int InFrameWidth,
		int InFrameHeight,
		float InFrameInterval
	);
};

}
}

#endif
