#ifndef SERVER_H
#define	SERVER_H

#include "NetworkMessageTypes.h"

#include "RakNet\RakPeerInterface.h"
#include "RakNet\RakNetTypes.h"

namespace Engine
{
	namespace Network
	{
		class NetworkManager;

		class Server
		{
			public :
				void Update();
				Transform GetTransform();
				void SendTransform(Transform i_transform);
				bool IsClientConnected();
				void makeDejaVu();
				bool didDeJaVuHappen();

			private:
				Server(RakNet::RakPeerInterface* i_peer);
				~Server();

				friend class NetworkManager;

				RakNet::SystemAddress m_clientSystemAddress;
				Transform m_clientTransform;
				RakNet::RakPeerInterface* m_peer;
				bool m_isClientConnected;

				bool _dejaVu;
		};
	}
}

#endif	