
#include "Camera.h"

void Camera::Update(const Transform * self, const Transform * target)
{
}

DirectX::SimpleMath::Matrix& Camera::GetViewMatrix()
{
	return m_view;
}

DirectX::SimpleMath::Matrix& Camera::GetProjectionMatrix()
{
	return m_proj;
}
