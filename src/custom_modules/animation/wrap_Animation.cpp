// Seraphine Software 2025

#include "common/config.h"

#include "wrap_Animation.h"

namespace love
{
namespace animation
{

#define instance() (Module::getInstance<AnimationModule>(Module::M_ANIMATION))


int w_NewAnimation(lua_State *L)
{
	graphics::Texture* tex = luax_checktype<graphics::Texture>(L, 1);
	int startX = luaL_checkinteger(L, 2);
	int startY = luaL_checkinteger(L, 3);
	int frameCount = luaL_checkinteger(L, 4);
	int dirX = luaL_checkinteger(L, 5);
	int dirY = luaL_checkinteger(L, 6);
	int width = luaL_checkinteger(L, 7);
	int height = luaL_checkinteger(L, 8);
	float interval = luaL_checknumber(L, 9);

	Animation* newAnim = instance()->NewAnimation(tex, startX, startY, frameCount, dirX, dirY, width, height, interval);
	luax_pushtype(L, newAnim);
	return 1;
}

int w_animation_update(lua_State *L)
{
	Animation* anim = luax_checktype<Animation>(L, 1);
	float deltaTime = (float)luaL_checknumber(L, 2);
	anim->Update(deltaTime);
	return 0;
}

int w_animation_getdrawdata(lua_State *L)
{
	Animation *anim = luax_checktype<Animation>(L, 1);

	double FrameStartX = anim->m_FrameWidth * anim->m_CurrentFrame * anim->m_SpritesheetDirectionX;
	double FrameStartY = anim->m_FrameHeight * anim->m_CurrentFrame * anim->m_SpritesheetDirectionY;

	graphics::Quad* NewQuad = new graphics::Quad(
		{FrameStartX, FrameStartY, (double)anim->m_FrameWidth, (double)anim->m_FrameHeight},
		anim->m_SpritesheetTexture->getWidth(), anim->m_SpritesheetTexture->getHeight()
	);

	luax_pushtype(L, NewQuad);
	luax_pushtype(L, anim->m_SpritesheetTexture);

	return 2;
}

static const luaL_Reg functions[] = 
{
	{ "newAnimation", w_NewAnimation },
	{ "update", w_animation_update },
	{ "getDrawData", w_animation_getdrawdata },
	{ 0, 0 }
};

extern "C" int love::animation::luaopen_love_animation(lua_State * L)
{
	AnimationModule *instance = instance();

	if (instance == nullptr)
	{
		luax_catchexcept(L, [&](){ instance = new love::animation::AnimationModule(); });
	}
	else
	{
		instance->retain();
	}

	WrappedModule w;
	w.module = instance;
	w.name = "animation";
	w.type = &Module::type;
	w.functions = functions;
	w.types = 0;

	return luax_register_module(L, w);
}

}
}
