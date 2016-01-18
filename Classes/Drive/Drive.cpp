#include "Drive.h"

void Drive::SetHeading(const cocos2d::Vec2& new_heading)
{
	mHeading = new_heading;
	//side����Ҫ��ֱ��ͷ��
	mSide = mHeading.getRPerp();
}

bool Drive::RotateHeadingToFacePosition(const cocos2d::Vec2& target)
{
	cocos2d::Vec2 toTarget = (target - mPos).getNormalized();

	//���ȣ����ͷ������ָ��Ŀ�������ĽǶ�
	double angle = acos(mHeading.dot(toTarget));

	//����泯Ŀ�ĵأ��򷵻�
	if (angle < 0.00001f) return true;

	//��ȡ�Ƕ�Ϊ���ת��Ƕ�
	if (angle > mMaxTurnRate) angle = mMaxTurnRate;

	cocos2d::Mat4 RotationMatrix;
	RotationMatrix.rotateZ(angle * Drive::Sign(mHeading, toTarget));
	cocos2d::Vec3	mHeadingV3(mHeading.x, mHeading.y,0);
	cocos2d::Vec3	mVelocityV3(mVelocity.x, mVelocity.y, 0);
	RotationMatrix.transformVector(&mHeadingV3);
	RotationMatrix.transformVector(&mVelocityV3);
	mHeading.set(mHeadingV3.x, mHeadingV3.y);
	mVelocity.set(mVelocityV3.x, mVelocityV3.y);

	//�����������side����
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
