#pragma once
// ����
#define ACTOR_PLAYER "Player"

#define ACTOR_UI_CLOCK "Clock"
#define ACTOR_UI_ENERGYBAR "EnergyBar"
#define ACTOR_UI_INVENTORY "Inventory"

#define ACTOR_TITLE_BACKGROUND "TitleBackGround"
#define ACTOR_TITLE_BUTTON_NEW "TitleButtonNewGame"
#define ACTOR_TITLE_BUTTON_LOAD "TitleButtonLoadGame"
#define ACTOR_TITLE_BUTTON_EXIT "TitleButtonExitGame"
#define ACTOR_TITLE_LOGO "TitleLogo"

// ���丮
#define DIR_PARENT "GameEngineAPI"
#define DIR_PLAYER "Player"
#define DIR_RESOURCES "Resources"
#define DIR_IMAGE "Image"
#define DIR_SOUND "Sound"
#define DIR_INTERFACE "Interface"
#define DIR_TOOL "Tool"
#define DIR_ENVIRONMENT "Environment"
#define DIR_TILESET "Tileset"
#define DIR_MAP "Map"
#define DIR_BUILDING "Building"

// �̹���
#define IMAGE_CLOCK_POS_H 129
#define IMAGE_CLOCK_POS_W 1125
#define IMAGE_CLOCK_SIZE_H 236
#define IMAGE_CLOCK_SIZE_W 288
#define IMAGE_ENERGYBAR_POS_H 591
#define IMAGE_ENERGYBAR_POS_W 1249
#define IMAGE_FARM_BUILDING "FarmBuildings.bmp"
#define IMAGE_PLAYER_CLOTH "PlayerCloth.bmp"
#define IMAGE_PLAYER_HAIR "PlayerHair.bmp"
#define IMAGE_PLAYER_HAT "PlayerHat.bmp"
#define IMAGE_PLAYER_MASK "PlayerMask.bmp"
#define IMAGE_PLAYER_MAN_BODY "PlayerManBody.bmp"
#define IMAGE_PLAYER_WOMAN_BODY "PlayerWomanBody.bmp"
#define IMAGE_PLAYER_MAN_TOTAL "PlayerManBodyTotal.bmp"
#define IMAGE_INVENTORY_BAR "InventoryBar.bmp"
#define IMAGE_INVENTORY_EXTEND "InventoryExtend.bmp"
#define IMAGE_INVENTORY_SELECT "InventorySelectBox.bmp"
#define IMAGE_INVENTORY_EMPTY "Empty.bmp"
#define IMAGE_INVENTORYBAR_POS_UP_X 640
#define IMAGE_INVENTORYBAR_POS_UP_Y 55
#define IMAGE_INVENTORYBAR_POS_DOWN_X 640
#define IMAGE_INVENTORYBAR_POS_DOWN_Y 663
#define IMAGE_INVENTORY_EXT_POS_X 640
#define IMAGE_INVENTORY_EXT_POS_Y 563
#define IMAGE_MOUSE_CURSOR "MouseCursor.bmp"
#define IMAGE_TITLE_BUTTON_H 174
#define IMAGE_TITLE_BUTTON_W 222
#define IMAGE_TITLE_BACKGOUND "MainBackground.bmp"
#define IMAGE_TITLE_LOGO_H 374
#define IMAGE_TITLE_LOGO_W 796
#define IMAGE_TOOL_SET1 "Tools_set1.bmp"
#define IMAGE_TOOL_SET2 "Tools_set2.bmp"
#define IMAGE_FULL_SIZE_H 720
#define IMAGE_FULL_SIZE_W 1280

#define IMAGE_ENVIRONMENT_CROPS "Crops.bmp"
#define IMAGE_ENVIRONMENT_FISHING "Fishing.bmp"
#define IMAGE_ENVIRONMENT_FORAGE "Forage.bmp"
#define IMAGE_ENVIRONMENT_MAPLETREE "MapleTree.bmp"
#define IMAGE_ENVIRONMENT_OAKTREE "OakTree.bmp"
#define IMAGE_ENVIRONMENT_PINETREE "PineTree.bmp"

#define IMAGE_TILESET_DIRT "Dirt.bmp"
#define IMAGE_TILESET_DIRTWATERED "DirtWatered.bmp"

// Ű �Է�
#define KEY_MOVE_LEFT "MoveLeft"
#define KEY_MOVE_RIGHT "MoveRight"
#define KEY_MOVE_UP "MoveUp"
#define KEY_MOVE_DOWN "MoveDown"
#define KEY_INTERACT "Interact"
#define KEY_INVEN_EXTEND "InventoryExtend"

// �κ��丮 ���� ����Ű
#define KEY_INVEN_SELECT_1 "INVEN_SEL_1"
#define KEY_INVEN_SELECT_2 "INVEN_SEL_2"
#define KEY_INVEN_SELECT_3 "INVEN_SEL_3"
#define KEY_INVEN_SELECT_4 "INVEN_SEL_4"
#define KEY_INVEN_SELECT_5 "INVEN_SEL_5"
#define KEY_INVEN_SELECT_6 "INVEN_SEL_6"
#define KEY_INVEN_SELECT_7 "INVEN_SEL_7"
#define KEY_INVEN_SELECT_8 "INVEN_SEL_8"
#define KEY_INVEN_SELECT_9 "INVEN_SEL_9"
#define KEY_INVEN_SELECT_0 "INVEN_SEL_0"
#define KEY_INVEN_SELECT_11 "INVEN_SEL_11"
#define KEY_INVEN_SELECT_12 "INVEN_SEL_12"


// ��
// ����
#define MAP_FARM_BACKGORUND "FarmBack.bmp"
#define MAP_FARM_BUILDING "FarmBuilding.bmp"
#define MAP_FARM_FRONT "FarmFront.bmp"
#define MAP_FARM_ALWAYSFRONT "FarmAlwaysfront.bmp"
#define MAP_FARM_COLLISION "FarmBuildingCollision.bmp"
#define MAP_FARM_RENDER_ORDER_COLLISION "FarmFrontCollision.bmp"
#define MAP_FARM_SIZE_H 3120.0f
#define MAP_FARM_SIZE_W 3840.0f
// Ÿ��
#define MAP_TOWN_BACKGORUND "TownBack.bmp"
#define MAP_TOWN_BUILDING "TownBuilding.bmp"
#define MAP_TOWN_FRONT "TownFront.bmp"
#define MAP_TOWN_ALWAYSFRONT "TownAlwaysfront.bmp"
#define MAP_TOWN_COLLISION "TownBuildingCollision.bmp"
#define MAP_TOWN_RENDER_ORDER_COLLISION "TownFrontCollision.bmp"
#define MAP_TOWN_SIZE_H 5280.0f
#define MAP_TOWN_SIZE_W 5760.0f
// ���� ���θ�
#define MAP_FARMBUILDING_BACKGROUND "FarmBuildingBack.bmp"
#define MAP_FARMBUILDING_BUILDING "FarmBuildingBuilding.bmp"
#define MAP_FARMBUILDING_FRONT "FarmBuildingFront.bmp"
#define MAP_FARMBUILDING_COLLISION "FarmBuildingBuildingCollision.bmp"
#define MAP_FARMBUILDING_SIZE_H 414.0f
#define MAP_FARMBUILDING_SIZE_W 414.0f
// �غ�
#define MAP_BEACH_BACKGORUND "BeachBack.bmp"
#define MAP_BEACH_BUILDING "BeachBuilding.bmp"
#define MAP_BEACH_FRONT "BeachFront.bmp"
#define MAP_BEACH_ALWAYSFRONT "BeachAlwaysfront.bmp"
#define MAP_BEACH_COLLISION "BeachBuildingCollision.bmp"
#define MAP_BEACH_RENDER_ORDER_COLLISION "BeachFrontCollision.bmp"
#define MAP_BEACH_SIZE_H 2397.0f
#define MAP_BEACH_SIZE_W 4992.0f

// �ø���
#define COL_GROUP_MOUSE "Mouse"
#define COL_GROUP_INVENTORY_BAR "InventoryBar"
#define COL_GROUP_INVENTORY_EXTEND_BAR "InventoryExtendBar"
#define COL_GROUP_INVENTORY_BOX "InventoryBox"
#define COL_GROUP_INVENTORY_EXTEND_BOX "InventoryExtendBox"

// Ÿ�ϸ�
#define TILEMAP_SIZE 48

// ����
#define LEVEL_CHANGE_FARM "LevelChangeFarm"
#define LEVEL_CHANGE_TOWN "LevelChangeTown"
#define LEVEL_TITLE "TitleLevel"
#define LEVEL_TOWN "TownLevel"
#define LEVEL_FARM "FarmLevel"
#define LEVEL_BEACH "BeachLevel"
#define LEVEL_FARMBUILDING "FarmBuildingLevel"
#define LEVEL_PLAY "PlayLevel"
#define LEVEL_ENDING "EndingLevel"

// ������
#define WINDOW_BACKBUFFER "BackBuffer"
#define WINDOW_GAMEWINDOW "GameWindow"
#define WINDOW_MAINDC "WindowMain"

#define WINDOW_SIZE_H 720
#define WINDOW_SIZE_W 1280


// �ִϸ��̼�
#define ANIM_IDLE_DOWN "IdleDown"
#define ANIM_IDLE_RIGHT "IdleRight"
#define ANIM_IDLE_LEFT "IdleLeft"
#define ANIM_IDLE_UP "IdleUp"

#define ANIM_WALK_DOWN "WalkDown"
#define ANIM_WALK_RIGHT "WalkRight"
#define ANIM_WALK_LEFT "WalkLeft"
#define ANIM_WALK_UP "WalkUp"
// ���η� �ֵθ���
#define ANIM_HIT_HORIZON_DOWN "HitHorizonDown"
#define ANIM_HIT_HORIZON_RIGHT "HitHorizonRight"
#define ANIM_HIT_HORIZON_LEFT "HitHorizonLeft"
#define ANIM_HIT_HORIZON_UP "HitHorizonUp"
// ���η� �ֵθ���
#define ANIM_HIT_VERTICAL_DOWN "HitVerticalDown"
#define ANIM_HIT_VERTICAL_RIGHT "HitVerticalRight"
#define ANIM_HIT_VERTICAL_LEFT "HitVerticalLeft"
#define ANIM_HIT_VERTICAL_UP "HitVerticalUp"


// ������
#define ITEM_NAME_EMPTY "Empty"
#define ITEM_NAME_HOE "Hoe"
#define ITEM_NAME_AXE "Axe"
#define ITEM_NAME_WATERINGCAN "WateringCan"