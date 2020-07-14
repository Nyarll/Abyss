#pragma once

#include "../../../../../../Framework/Camera/Camera.h"

class Transform;
class GameContext;

class DebugCamera
{
private:
	DirectX::SimpleMath::Matrix	m_view;
	DirectX::SimpleMath::Matrix m_proj;

public:
	void Update(GameContext& context, Transform* self);

	DirectX::SimpleMath::Matrix& GetViewMatrix();
	DirectX::SimpleMath::Matrix& GetProjectionMatrix();
};