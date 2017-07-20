#include "cMyGame.h"

Engine::cMyGame::~cMyGame()
{

}

bool Engine::cMyGame::Initialize()
{
	Engine::Network::NetworkManager::CreateNetworkManager();
	
	const char* const path = "data/Meshes/Car.bin";
	const char* const path2 = "data/Meshes/Platform.bin";
	const char* const path3 = "data/Meshes/Cylinder.bin";

	const char* const matpath1 = "data/Materials/mat1.bin";
	const char* const matpath2 = "data/Materials/mat2.bin";
	const char* const matpath3 = "data/Materials/mat3.bin";
	const char* const matpath4 = "data/Materials/mat4.bin";
	
	m1.s_mesh = new Engine::Mesh::Mesh;
	m2.s_mesh = new Engine::Mesh::Mesh;
	m3.s_mesh = new Engine::Mesh::Mesh;
	m4.s_mesh = new Engine::Mesh::Mesh;
	m5.s_mesh = new Engine::Mesh::Mesh;
	m6.s_mesh = new Engine::Mesh::Mesh;
	m7.s_mesh = new Engine::Mesh::Mesh;
	m8.s_mesh = new Engine::Mesh::Mesh;
	m9.s_mesh = new Engine::Mesh::Mesh;
	mat1 = new Engine::Graphics::Materials::Material;
	mat2 = new Engine::Graphics::Materials::Material;
	mat3 = new Engine::Graphics::Materials::Material;
	mat4 = new Engine::Graphics::Materials::Material;

	s_camPos = new Engine::Math::cVector(0.0f, 5.0f, 20.0f);
	s_Camera = new Engine::Camera::Camera(*s_camPos, s_camOri, Engine::Math::ConvertDegreesToRadians(60.0f), 0.1f, 100.0f);
	spr1 = new Engine::Graphics::cSprite(-0.3f, 0.3f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f);
	spr1->Initialize();
	bool wereThereErrors = false;

	if (!m1.s_mesh->LoadFile(path))
	{
		wereThereErrors = true;
	}
	if (!m2.s_mesh->LoadFile(path2))
	{
		wereThereErrors = true;
	}
	if (!m3.s_mesh->LoadFile(path2))
	{
		wereThereErrors = true;
	}
	if (!m4.s_mesh->LoadFile(path3))
	{
		wereThereErrors = true;
	}
	if (!m5.s_mesh->LoadFile(path3))
	{
		wereThereErrors = true;
	}
	if (!m6.s_mesh->LoadFile(path3))
	{
		wereThereErrors = true;
	}
	if (!m7.s_mesh->LoadFile(path2))
	{
		wereThereErrors = true;
	}
	if (!m8.s_mesh->LoadFile(path2))
	{
		wereThereErrors = true;
	}
	if (!m9.s_mesh->LoadFile(path))
	{
		wereThereErrors = true;
	}
	if (!mat1->Load(matpath1))
	{
		wereThereErrors = true;
	}
	if (!mat2->Load(matpath2))
	{
		wereThereErrors = true;
	}
	if (!mat3->Load(matpath3))
	{
		wereThereErrors = true;
	}
	if (!mat4->Load(matpath4))
	{
		wereThereErrors = true;
	}
	m1.s_mat = mat1;
	m2.s_mat = mat2;
	m3.s_mat = mat2;
	m4.s_mat = mat3;
	m5.s_mat = mat3;
	m6.s_mat = mat3;
	m7.s_mat = mat2;
	m8.s_mat = mat2;
	m9.s_mat = mat1;
	Engine::Graphics::SetCamera(*s_Camera);
	m3.s_pos.z(m3.s_pos.z() - 24.0f);
	m7.s_pos.z(m7.s_pos.z() - 48.0f);
	m8.s_pos.z(m8.s_pos.z() - 72.0f);
	Engine::Graphics::SetMesh(m3);
	m4.s_pos.z(m4.s_pos.z() - 20.0f);
	m4.s_pos.x(m4.s_pos.x() + 5.0f);
	Engine::Graphics::SetMesh(m4);
	m5.s_pos.z(m5.s_pos.z() - 35.0f);
	m5.s_pos.x(m5.s_pos.x() - 5.0f);
	Engine::Graphics::SetMesh(m5);
	m6.s_pos.z(m6.s_pos.z() - 43.0f);
	m6.s_pos.x(m6.s_pos.x() + 5.0f);
	Engine::Graphics::SetMesh(m6);
	return !wereThereErrors;
}

void Engine::cMyGame::DrawMesh()
{
	float offset[2] = { 0.0f, 0.0f };
	{
		if (UserInput::IsKeyPressed('A'))
			offset[0] -= 4.0f;
		if (UserInput::IsKeyPressed('D'))
			offset[0] += 4.0f;
		offset[1] -= 60.0f;
	}
	{
		const float speed_unitsPerSecond = 0.2f;
		const float offsetModifier = speed_unitsPerSecond * Time::GetElapsedSecondCount_duringPreviousFrame();
		
		offset[0] *= offsetModifier;
		offset[1] *= offsetModifier;
	}
	Engine::Math::cVector tempVec(0.0f, 0.0f, offset[1]);
	s_Camera->Move(tempVec);

	Engine::Math::cVector tempx(1.0f, 0.0f, 0.0f);
	Engine::Math::cVector tempy(0.0f, 1.0f, 0.0f);

	m1.s_pos.z(m1.s_pos.z() + offset[1]);
	m1.s_pos.x(m1.s_pos.x() + offset[0]);
	m9.s_pos.z(m9.s_pos.z() + offset[1]);
	m9.s_pos.x(m9.s_pos.x() + offset[0]);

	Engine::Network::NetworkManager::Update();

	bool multiplePeers = false;

	Engine::Network::Transform myTransform(m1.s_pos, m1.s_rot);

	if (!Engine::Network::NetworkManager::IsServer())
	{
		Engine::Network::Client* client = Engine::Network::NetworkManager::GetClient();
		if (client->IsServerConnected())
		{
			multiplePeers = true;
			client->SendTransform(myTransform);
			Engine::Network::Transform otherTransform(client->GetTransform());

			m9.s_pos.x(otherTransform.posx);
			m9.s_pos.y(otherTransform.posy);
			m9.s_pos.z(otherTransform.posz);

			m9.s_rot.x(otherTransform.rotx);
			m9.s_rot.y(otherTransform.roty);
			m9.s_rot.z(otherTransform.rotz);
		}
	}
	else
	{
		Engine::Network::Server* server = Engine::Network::NetworkManager::GetServer();
		if (server->IsClientConnected())
		{
			multiplePeers = true;
			server->SendTransform(myTransform);
			Engine::Network::Transform otherTransform(server->GetTransform());

			m9.s_pos.x(otherTransform.posx);
			m9.s_pos.y(otherTransform.posy);
			m9.s_pos.z(otherTransform.posz);

			m9.s_rot.x(otherTransform.rotx);
			m9.s_rot.y(otherTransform.roty);
			m9.s_rot.z(otherTransform.rotz);
		}
	}

	Engine::Graphics::SetMesh(m1);
	Engine::Graphics::SetMesh(m2);
	Engine::Graphics::SetMesh(m3);
	Engine::Graphics::SetMesh(m4);
	Engine::Graphics::SetMesh(m5);
	Engine::Graphics::SetMesh(m6);
	Engine::Graphics::SetMesh(m7);
	Engine::Graphics::SetMesh(m8);

	if (multiplePeers == true)
	{
		Engine::Graphics::SetMesh(m9);
	}

	Engine::Graphics::SetSprite(spr1, mat4);
	Engine::Graphics::SetCamera(*s_Camera);
}

bool Engine::cMyGame::CleanUp()
{
	bool wereThereErrors = false;
	if (m1.s_mesh && !m1.s_mesh->CleanUp())
	{
		return false;
	}
	if (m1.s_mesh)
	{
		delete m1.s_mesh;
	}
	if (m2.s_mesh && !m2.s_mesh->CleanUp())
	{
		return false;
	}
	if (m2.s_mesh)
	{
		delete m2.s_mesh;
	}
	if (m3.s_mesh && !m3.s_mesh->CleanUp())
	{
		return false;
	}
	if (m3.s_mesh)
	{
		delete m3.s_mesh;
	}
	if (m4.s_mesh && !m4.s_mesh->CleanUp())
	{
		return false;
	}
	if (m4.s_mesh)
	{
		delete m4.s_mesh;
	}
	if (m5.s_mesh && !m5.s_mesh->CleanUp())
	{
		return false;
	}
	if (m5.s_mesh)
	{
		delete m5.s_mesh;
	}
	if (m6.s_mesh && !m6.s_mesh->CleanUp())
	{
		return false;
	}
	if (m6.s_mesh)
	{
		delete m6.s_mesh;
	}
	if (m7.s_mesh)
	{
		delete m7.s_mesh;
	}
	if (m8.s_mesh)
	{
		delete m8.s_mesh;
	}
	if (m9.s_mesh)
	{
		delete m9.s_mesh;
	}
	if (mat1)
	{
		mat1->CleanUp();
		delete mat1;
	}
	if (mat2)
	{
		mat2->CleanUp();
		delete mat2;
	}
	if (mat3)
	{
		mat3->CleanUp();
		delete mat3;
	}
	if (mat4)
	{
		mat4->CleanUp();
		delete mat4;
	}
	if (s_camPos)
	{
		delete s_camPos;
	}
	if (s_Camera)
	{
		delete s_Camera;
	}
	if (spr1)
	{
		spr1->CleanUp();
		delete spr1;
	}

	Engine::Network::NetworkManager::DestroyNetworkManager();

	return !wereThereErrors;
}
