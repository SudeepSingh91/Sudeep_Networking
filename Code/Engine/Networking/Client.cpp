#include "Client.h"

#include "RakNet\BitStream.h"

namespace Engine
{
	namespace Network
	{
		void Client::Update()
		{
			RakNet::Packet *packet;

			for (packet = m_peer->Receive(); packet; m_peer->DeallocatePacket(packet), packet = m_peer->Receive())
			{
				switch (packet->data[0])
				{
					case ID_CONNECTION_REQUEST_ACCEPTED:
					{
						m_serverSystemAddress = packet->systemAddress;
						m_isConnectedToServer = true;
					}
					break;

					case ID_FACTORY_RESET:
					{
						_dejaVu = true;
					}
					break;

					case ID_SERVER_TRANSFORM:
					{
						RakNet::RakString message;
						RakNet::BitStream bsIn(packet->data, packet->length, false);
						bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

						{
							bsIn.Read(m_serverTransform.posx);
							bsIn.Read(m_serverTransform.posy);
							bsIn.Read(m_serverTransform.posz);

							bsIn.Read(m_serverTransform.rotx);
							bsIn.Read(m_serverTransform.roty);
							bsIn.Read(m_serverTransform.rotz);
						}

						bsIn.Read(message);
					}
					break;
				}
			}
		}

		Transform Client::GetTransform()
		{
			return m_serverTransform;
		}

		void Client::SendTransform(Transform i_transform)
		{
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)ID_CLIENT_TRANSFORM);

			{
				bsOut.Write(i_transform.posx);
				bsOut.Write(i_transform.posy);
				bsOut.Write(i_transform.posz);
				bsOut.Write(i_transform.rotx);
				bsOut.Write(i_transform.roty);
				bsOut.Write(i_transform.rotz);
			}

			bsOut.Write("Client to Server");

			m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_serverSystemAddress, false);
		}

		bool Client::IsServerConnected()
		{
			return m_isConnectedToServer;
		}

		void Client::makeDejaVu()
		{
			_dejaVu = true;
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)ID_FACTORY_RESET);
			m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_serverSystemAddress, false);
		}

		Client::~Client()
		{
			RakNet::RakPeerInterface::DestroyInstance(m_peer);
		}

		bool Client::didDeJaVuHappen()
		{
			if (_dejaVu)
			{
				_dejaVu = false;
				return true;
			}

			return false;
		}

		Client::Client(RakNet::RakPeerInterface* i_peer)
		{
			m_peer = i_peer;
			m_isConnectedToServer = false;
			_dejaVu = false;
		}
	}
}