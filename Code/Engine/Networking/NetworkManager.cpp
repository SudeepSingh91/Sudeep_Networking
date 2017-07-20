#include "NetworkManager.h"

#include "RakNet\RakPeerInterface.h"
#include "../Asserts/Asserts.h"

namespace Engine
{
	namespace Network
	{
		NetworkManager* NetworkManager::m_instance = nullptr;

		void NetworkManager::CreateNetworkManager()
		{
			if (m_instance == nullptr)
			{
				m_instance = new NetworkManager();
			}
			else
			{
				ASSERTF(false, "Networking is a singleton class.\n");
			}
		}

		void NetworkManager::DestroyNetworkManager()
		{
			ASSERTF(m_instance != nullptr, "Networking is nullptr");
			delete m_instance;
		}

		void NetworkManager::Update()
		{
			if (m_instance->m_isServer)
			{
				m_instance->m_server->Update();
			}
			else
			{
				m_instance->m_client->Update();
			}
		}

		bool NetworkManager::IsServer()
		{
			return m_instance->m_isServer;;
		}

		Client * NetworkManager::GetClient()
		{
			return m_instance->m_client;
		}

		Server * NetworkManager::GetServer()
		{
			return m_instance->m_server;
		}

		NetworkManager::NetworkManager() : m_maxClient(2), m_serverPort(60000), m_server(nullptr), m_client(nullptr), m_isServer(false)
		{
			RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
			RakNet::SocketDescriptor sd(m_serverPort, 0);
			RakNet::SocketDescriptor clientSocketDesc;
			RakNet::StartupResult result = peer->Startup(m_maxClient, &sd, 1);

			if (result == RakNet::StartupResult::RAKNET_STARTED)
			{
				m_isServer = true;
				peer->SetMaximumIncomingConnections(m_maxClient);
				m_server = new Server(peer);
			}
			else
			{
				peer->Startup(1, &clientSocketDesc, 1);
				peer->Connect("127.0.0.1", m_serverPort, 0, 0);
				m_client = new Client(peer);
			}
		}

		NetworkManager::~NetworkManager()
		{
			delete m_server;
			delete m_client;
		}
	}
}