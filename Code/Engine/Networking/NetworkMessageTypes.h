#ifndef NETWORK_MESSAGE_TYPES_H
#define	NETWORK_MESSAGE_TYPES_H

#include "RakNet\MessageIdentifiers.h"
#include "../Engine/Math/cVector.h"

namespace Engine
{
	namespace Network
	{
		enum NetworkMessageTypes
		{
			ID_SERVER_TRANSFORM = ID_USER_PACKET_ENUM + 1,
			ID_CLIENT_TRANSFORM = ID_USER_PACKET_ENUM + 2,
			ID_FACTORY_RESET = ID_USER_PACKET_ENUM + 3
		};

		struct Transform
		{
			float posx, posy, posz, rotx, roty, rotz;

			Transform();
			Transform(const Engine::Math::cVector& i_pos, const Engine::Math::cVector& i_rot);
			Transform(const Transform& i_transform);
			Transform& operator=(const Transform& i_transform);
		};
	}
}

#endif
