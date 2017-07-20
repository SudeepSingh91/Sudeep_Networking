#include "Server.h"

#include "RakNet\BitStream.h"

namespace Engine
{
	namespace Network
	{
		void Server::Update()
		{
			RakNet::Packet *packet;

			for (packet = m_peer->Receive(); packet; m_peer->DeallocatePacket(packet), packet = m_peer->Receive())
			{
				switch (packet->data[0])
				{
					case ID_NEW_INCOMING_CONNECTION:
					{
						m_clientSystemAddress = packet->systemAddress;
						m_isClientConnected = true;
					}
					break;

					case ID_FACTORY_RESET:
					{
						_dejaVu = true;
					}
					break;

					case ID_CLIENT_TRANSFORM:
					{
						RakNet::RakString message;
						RakNet::BitStream bsIn(packet->data, packet->length, false);
						bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

						{
							bsIn.Read(m_clientTransform.posx);
							bsIn.Read(m_clientTransform.posy);
							bsIn.Read(m_clientTransform.posz);

							bsIn.Read(m_clientTransform.rotx);
							bsIn.Read(m_clientTransform.roty);
							bsIn.Read(m_clientTransform.rotz);
						}

						bsIn.Read(message);
					}
					break;
				}
			}
		}

		Transform Server::GetTransform()
		{
			return m_clientTransform;
		}

		void Server::SendTransform(Transform i_transform)
		{
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)ID_SERVER_TRANSFORM);

			{
				bsOut.Write(i_transform.posx);
				bsOut.Write(i_transform.posy);
				bsOut.Write(i_transform.posz);
				bsOut.Write(i_transform.rotx);
				bsOut.Write(i_transform.roty);
				bsOut.Write(i_transform.rotz);
			}

			bsOut.Write("Server to Client");

			m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_clientSystemAddress, false);
		}

		bool Server::IsClientConnected()
		{
			return m_isClientConnected;
		}

		void Server::makeDejaVu()
		{
			_dejaVu = true;
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)ID_FACTORY_RESET);
			m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_clientSystemAddress, false);
		}

		Server::~Server()
		{
			RakNet::RakPeerInterface::DestroyInstance(m_peer);
		}

		bool Server::didDeJaVuHappen()
		{
			if (_dejaVu)
			{
				_dejaVu = false;
				return true;
			}

			return false;
		}

		Server::Server(RakNet::RakPeerInterface* i_peer)
		{
			m_peer = i_peer;
			m_isClientConnected = false;
			_dejaVu = false;
		}
	}
}