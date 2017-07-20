#ifndef CLIENT_H
#define	CLIENT_H

#include "NetworkMessageTypes.h"

#include "RakNet\RakPeerInterface.h"
#include "RakNet\RakNetTypes.h"

namespace Engine
{
	namespace Network
	{
		class NetworkManager;

		class Client
		{
			public:
				void Update();
				Transform GetTransform();
				void SendTransform(Transform i_transform);
				bool IsServerConnected();
				void makeDejaVu();
				bool didDeJaVuHappen();

			private:
				Client(RakNet::RakPeerInterface* i_peer);
				~Client();

				friend class NetworkManager;

				RakNet::RakPeerInterface* m_peer;
				bool m_isConnectedToServer;
				Transform m_serverTransform;
				RakNet::SystemAddress m_serverSystemAddress;

				bool _dejaVu;
		};
	}
}

#endif