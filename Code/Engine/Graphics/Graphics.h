#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Configuration.h"
#include "Mesh.h"
#include "cSprite.h"
#include "Effect.h"
#include "Material.h"
#include "ConstantBuffer.h"
#include "Camera.h"
#include "../Math/cQuaternion.h"
#include "../Math/cVector.h"
#include "../Math/cMatrix_transformation.h"
#include "../Math/Functions.h"
#include "../Platform/Platform.h"
#include "Effect.h"

#if defined( PLATFORM_WINDOWS )
	#include "../Windows/Includes.h"
#endif

namespace Engine
{
	namespace Graphics
	{
		struct MeshData
		{
			Mesh::Mesh* s_mesh;
			Math::cVector s_pos;
			Math::cVector s_rot;
			Materials::Material* s_mat;
		};

		struct DrawCallData
		{
			Mesh::Mesh* s_mesh;
			Materials::Material* s_mat;
			ConstantBuffer::sDrawCall s_drawCall;
		};

		struct SpriteCallData
		{
			cSprite* s_sprite;
			Materials::Material* s_mat;
		};

		void SetMesh(MeshData i_mesh);
		void SetSprite(cSprite* i_spr, Materials::Material* i_mat);
		void SetCamera(Camera::Camera i_cam);
		void ClearScreen();
		void RenderFrame();

		struct sInitializationParameters
		{
#if defined( PLATFORM_WINDOWS )
			HWND mainWindow;
	#if defined( PLATFORM_D3D )
			unsigned int resolutionWidth, resolutionHeight;
	#elif defined( PLATFORM_GL )
			HINSTANCE thisInstanceOfTheApplication;
	#endif
#endif
		};

		bool Initialize( const sInitializationParameters& i_initializationParameters );
		bool CleanUp();
	}
}

#endif	