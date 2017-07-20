#include "NetworkMessageTypes.h"

namespace Engine
{
	namespace Network
	{
		Transform::Transform() :
			posx(0.0f), posy(0.0f), posz(0.0f), rotx(0.0f), roty(0.0f), rotz(0.0f)
		{

		}
		
		Transform::Transform(const Engine::Math::cVector& i_pos, const Engine::Math::cVector& i_rot) :
			posx(i_pos.x()), posy(i_pos.y()), posz(i_pos.z()), rotx(i_rot.x()), roty(i_rot.y()), rotz(i_rot.z())
		{

		}

		Transform::Transform(const Transform& i_transform) :
			posx(i_transform.posx), posy(i_transform.posy), posz(i_transform.posz), rotx(i_transform.rotx), roty(i_transform.roty), rotz(i_transform.rotz)
		{

		}

		Transform& Transform::operator=(const Transform& i_transform)
		{
			if (this != &i_transform)
			{
				posx = i_transform.posx;
				posy = i_transform.posy;
				posz = i_transform.posz;

				rotx = i_transform.rotx;
				roty = i_transform.roty;
				rotz = i_transform.rotz;
			}

			return *this;
		}
	}
}