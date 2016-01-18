#include "Drive.h"

void Drive::SetHeading(const cocos2d::Vec2& new_heading)
{
	mHeading = new_heading;
	//side向量要垂直于头部
	mSide = mHeading.getRPerp();
}

bool Drive::RotateHeadingToFacePosition(const cocos2d::Vec2& target)
{
	cocos2d::Vec2 toTarget = (target - mPos).getNormalized();

	//首先，算出头向量和指向目的向量的角度
	double angle = acos(mHeading.dot(toTarget));

	//如果面朝目的地，则返回
	if (angle < 0.00001f) return true;

	//截取角度为最大转向角度
	if (angle > mMaxTurnRate) angle = mMaxTurnRate;

	cocos2d::Mat4 RotationMatrix;
	RotationMatrix.rotateZ(angle * Drive::Sign(mHeading, toTarget));
	cocos2d::Vec3	mHeadingV3(mHeading.x, mHeading.y,0);
	cocos2d::Vec3	mVelocityV3(mVelocity.x, mVelocity.y, 0);
	RotationMatrix.transformVector(&mHeadingV3);
	RotationMatrix.transformVector(&mVelocityV3);
	mHeading.set(mHeadingV3.x, mHeadingV3.y);
	mVelocity.set(mVelocityV3.x, mVelocityV3.y);

	//最后重新生成side向量
	mSide = mHeading.getRPerp();

	return false;
}

Drive::Drive()
{

}

Drive::~Drive()
{

}

int Drive::Sign(cocos2d::Vec2& v1,cocos2d::Vec2& v2)
{
	if (v1.y*v2.x > v1.x*v2.y)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
