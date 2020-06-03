
#include "Camera.h"
#include "../GameObject/Transform.h"
#include "../Context/GameContext.h"

void Camera::Update(GameContext& context, Transform* _self, Transform* _target)
{
	DirectX::SimpleMath::Vector3 eye = _self->localPosition;
	DirectX::SimpleMath::Vector3 target = eye - DirectX::SimpleMath::Vector3(0.f, 5.f, -10.f);
	if (_target)
	{
		target = _target->localPosition;
	}
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, DirectX::SimpleMath::Vector3::Up);

	RECT size = context.Get<DX::DeviceResources>().GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);
	float fovAngleY = DirectX::XMConvertToRadians(45.0f);
	m_proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY, aspectRatio,
		0.01f, 10000.0f
	);
}

DirectX::SimpleMath::Matrix& Camera::GetViewMatrix()
{
	return m_view;
}

DirectX::SimpleMath::Matrix& Camera::GetProjectionMatrix()
{
	return m_proj;
}
