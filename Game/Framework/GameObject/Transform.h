#pragma once

// <class name		: Transform>
// <update date		: 2020 / 05 / 25>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef TRANSFORM_DEFINED
#define TRANSFORM_DEFINED

// <Transform>
class Transform
{
public:
	DirectX::SimpleMath::Vector3 localPosition;		// <ローカル位置>
	DirectX::SimpleMath::Quaternion localRotation;	// <ローカル回転>
	DirectX::SimpleMath::Vector3 localScale;		// <ローカルスケール>

	Transform()
	{
		localPosition = DirectX::SimpleMath::Vector3::Zero;
		localRotation = DirectX::SimpleMath::Quaternion::Identity;
		localScale = DirectX::SimpleMath::Vector3(1.f, 1.f, 1.f);
	}

	DirectX::SimpleMath::Matrix GetMatrix()const
	{
		DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::CreateScale(localScale) *
			DirectX::SimpleMath::Matrix::CreateFromQuaternion(localRotation) *
			DirectX::SimpleMath::Matrix::CreateTranslation(localPosition);

		return matrix;
	}
};

#endif