#ifndef NETWORKMANAGER_H
#define	NETWORKMANAGER_H

#include "Client.h"
#include "Server.h"

namespace Engine
{
	namespace Network
	{
		class NetworkManager
		{
		public:
			static void CreateNetworkManager();
			static void DestroyNetworkManager();
			static void Update();
			static bool IsServer();
			static Client* GetClient();
			static Server* GetServer();

		private:
			NetworkManager();
			~NetworkManager();

			static NetworkManager* m_instance;

			const unsigned int m_maxClient;
			const unsigned int m_serverPort;
			Server* m_server;
			Client* m_client;
			bool m_isServer;
		};
	}
}

#endif