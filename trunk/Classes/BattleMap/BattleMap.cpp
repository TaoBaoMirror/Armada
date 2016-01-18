#include "BattleMap.h"
#include "BattleMapManager.h"
#include "MapCollision.h"

//Sprites Layer
#define EffectLayer "EffectLayer"			//��ʾ����Ч��
#define ItemLayer "ItemLayer"				//��ʾ����Ʒ��
#define BulletLayer "BulletLayer"			//��ʾ���ӵ���
#define ShipLayer "ShipLayer"				//������
#define BuildLayer "BuildLayer"				//�������
#define LandLayer "LandLayer"				//����½�ز�
#define LandBaseLayer "LandBaseLayer"		//����½�صײ�(�ٻ���)

//Object
#define StartPointLayer "StartPoint"		//����½�ز�

#define ShipLayerTag 0xa1		//���������ݲ�
#define BulletLayerTag 0xa2		//��Ʒ��
#define ItemLayerTag 0xa3		//��Ʒ��
#define EffectLayerTag 0xa4		//��Ч��




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
			pLandLayer->getTiles();
			//this->_states->setVisible(false);//���ֱ����editor������invisible, getLayer�᷵��nullptr
			// find
			auto layerSize = pLandLayer->getLayerSize();
			cocos2d::Size tsize = pLandLayer->getMapTileSize();

			int x_Tiles = (int)layerSize.width;
			int y_Tiles = (int)layerSize.height;

			cocos2d::Vec2 curTilePos = cocos2d::Vec2(layerSize.width*0.5f, layerSize.height*0.5f);

			for (int ly = 0; ly < y_Tiles; ++ly)
			{
				for (int lx = 0; lx < x_Tiles; ++lx)
				{
					//curTilePos = cocos2d::Vec2(layerSize.width*0.5f + j*layerSize.width, layerSize.height*0.5f + i*layerSize.height);

					auto gid = pLandLayer->getTileGIDAt(cocos2d::Vec2(lx, ly));
					cocos2d::Sprite* pTimeSprite = pLandLayer->getTileAt(cocos2d::Vec2(lx, ly));

					if (pTimeSprite != nullptr)
					{
						int i = 100;
					}

					auto properties = this->getPropertiesForGID(gid);

					if (properties.isNull() == false)
					{
						auto properties_Map = properties.asValueMap();
						if (!properties_Map.empty())
						{
							if (properties_Map["collision_type"].asString() == "1")
							{
								if (pTimeSprite != nullptr)
								{
									//can not break
									MapCollision* mc = new MapCollision(pTimeSprite);
									mc->SetRect(pTimeSprite->getBoundingBox());
									BattleMapManager::getInstance()->AddMapCollision(mc);
									break;
								}
							}
							else if (properties_Map["collision_type"].asString() == "2")
							{
								//can break
								if (pTimeSprite != nullptr)
								{
									//can not break
									MapCollision* mc = new MapCollision(pTimeSprite);
									mc->SetCanBreak();
									mc->SetRect(pTimeSprite->getBoundingBox());
									BattleMapManager::getInstance()->AddMapCollision(mc);
									break;
								}
							}

							if (properties_Map["is_anim"].asString() == "1")
							{

							}
						}
					}
				}
			}

			//��ˮ��ɳ̲����ЧҲ����� ��������tiled�е������ж�������

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
