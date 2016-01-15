#include "BattleMap.h"

//Sprites Layer
#define EffectLayer "EffectLayer"			//显示的特效层
#define ItemLayer "ItemLayer"				//显示的物品层
#define BulletLayer "BulletLayer"			//显示的子弹层
#define ShipLayer "ShipLayer"				//船舶层
#define BuildLayer "BuildLayer"				//建筑物层
#define LandLayer "LandLayer"				//岛屿陆地层
#define LandBaseLayer "LandBaseLayer"		//岛屿陆地底层(毁坏后)

//Object
#define StartPointLayer "StartPoint"		//岛屿陆地层

#define ShipLayerTag 0xa1		//生物体数据层
#define BulletLayerTag 0xa2		//物品层
#define ItemLayerTag 0xa3		//物品层
#define EffectLayerTag 0xa4		//特效层




BattleMap::BattleMap()
{
}


BattleMap::~BattleMap()
{
}

void BattleMap::update(float delta)
{

}

void BattleMap::onEnter()
{

}

void BattleMap::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{

}

void BattleMap::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{

}

bool BattleMap::InitBattleMap(std::string tmxFile)
{
	if (initWithTMXFile(tmxFile))
	{
		//Objects
		auto pObjectsLayer = this->getObjectGroup(StartPointLayer);
		if (pObjectsLayer != nullptr)
		{
			auto& objects = pObjectsLayer->getObjects();

			for (auto& obj : objects)
			{
				cocos2d::ValueMap& dict = obj.asValueMap();

				float x = dict["x"].asFloat();
				float y = dict["y"].asFloat();

				std::string name = dict["name"].asString();

				if (name == "StartPoint_Left")
				{
					cocos2d::Vec2 leftpos = cocos2d::Vec2(x, y);

					m_LeftBornPoint = leftpos;
				}
				else if (name == "StartPoint_Right")
				{
					cocos2d::Vec2 rightpos = cocos2d::Vec2(x, y);

					m_RightBornPoint = rightpos;
				}
			}
		}


		//Layers
		int curZOrder = 0;
		auto pLandBaseLayer = getLayer(LandBaseLayer);
		if (pLandBaseLayer != nullptr)
		{
			curZOrder = pLandBaseLayer->getZOrder();
		}

		auto pLandLayer = getLayer(LandLayer);
		if (pLandLayer != nullptr)
		{
			//海水冲沙滩的特效也在这层 在这里让tiled中的序列中动画播放

			// order
			curZOrder = pLandLayer->getZOrder();
		}
		
		auto pBuildLayer = getLayer(BuildLayer);

		if (pBuildLayer != nullptr)
		{
			//1 build logic

			//2 order
			curZOrder = pBuildLayer->getZOrder();
		}

		cocos2d::Layer* pRenderShipLayer = cocos2d::Layer::create();
		this->addChild(pRenderShipLayer, curZOrder + 1, ShipLayerTag);

		cocos2d::Layer* pRenderBulletLayer = cocos2d::Layer::create();
		this->addChild(pRenderBulletLayer, curZOrder + 2, BulletLayerTag);

		cocos2d::Layer* pRenderItemLayer = cocos2d::Layer::create();
		this->addChild(pRenderItemLayer, curZOrder + 3, ItemLayerTag);

		cocos2d::Layer* pRenderEffectLayer = cocos2d::Layer::create();
		this->addChild(pRenderEffectLayer, curZOrder + 4, EffectLayerTag);



		//auto sLayerSize = pShipLayer->getLayerSize();
		//auto sTileSize = pShipLayer->getMapTileSize();
		

		return true;
	}


	return false;
}
//--------------------------------------------------------------
cocos2d::TMXLayer* BattleMap::GetCreatureTMXLayer()
{
	return nullptr;
}

cocos2d::Layer* BattleMap::GetShipLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(ShipLayerTag));
}

cocos2d::Layer* BattleMap::GetEffectLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(EffectLayerTag));
}

cocos2d::Layer* BattleMap::GetItemLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(ItemLayerTag));
}

cocos2d::Layer* BattleMap::GetBulletLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(BulletLayerTag));
}

cocos2d::TMXLayer* BattleMap::GetBuildLayer()
{
	auto pBuildLayer = getLayer(BuildLayer);

	return pBuildLayer;
}

cocos2d::TMXLayer* BattleMap::GetLandLayer()
{
	auto pLandLayer = getLayer(LandLayer);

	return pLandLayer;
}
//---------------------------------------------------------------------------
cocos2d::Vec2 BattleMap::GetLeftBornPoint()
{
	return m_LeftBornPoint;
}

cocos2d::Vec2 BattleMap::GetRightBornPoint()
{
	return m_RightBornPoint;
}
