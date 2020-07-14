#include "DebugCamera.h"
#include "../../../../../../Framework/Framework.h"

void DebugCamera::Update(GameContext& context, Transform* self)
{
	DirectX::SimpleMath::Vector3 eye = self->localPosition;

	if(InputManager::GetKey(DirectX::Keyboard::Keys::W))
	{
		eye.z += 0.1f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::S))
	{
		eye.z -= 0.1f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::A))
	{
		eye.x += 0.1f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::D))
	{
		eye.x -= 0.1f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::Space))
	{
		eye.y += 0.1f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::LeftShift))
	{
		eye.y -= 0.1f;
	}
	self->localPosition = eye;

	DirectX::SimpleMath::Vector3 target = eye - DirectX::SimpleMath::Vector3(0.f, 5.f, -10.f);

	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, DirectX::SimpleMath::Vector3::Up);

	RECT size = context.Get<DX::DeviceResources>().GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);
	float fovAngleY = DirectX::XMConvertToRadians(45.0f);
	m_proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY, aspectRatio,
		0.01f, 10000.0f
	);
}

DirectX::SimpleMath::Matrix& DebugCamera::GetViewMatrix()
{
	return m_view;
}

DirectX::SimpleMath::Matrix& DebugCamera::GetProjectionMatrix()
{
	return m_proj;
}
