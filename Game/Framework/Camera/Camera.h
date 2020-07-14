#pragma once

// <class name		: Camera>
// <update date		: 2020 / 06 / 02>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef CAMERA_DEFINED
#define CAMERA_DEFINED

class Transform;
class GameContext;

class Camera
{
private:
	DirectX::SimpleMath::Matrix	m_view;
	DirectX::SimpleMath::Matrix m_proj;

	const Transform* m_target;

public:
	void Update(GameContext& context, Transform* self, Transform* target = nullptr);

	DirectX::SimpleMath::Matrix& GetViewMatrix();
	DirectX::SimpleMath::Matrix& GetProjectionMatrix();
};

#endif