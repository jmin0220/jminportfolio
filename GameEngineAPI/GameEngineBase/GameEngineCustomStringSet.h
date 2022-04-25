#pragma once
// 액터
#define ACTOR_PLAYER "Player"

#define ACTOR_UI_CLOCK "Clock"
#define ACTOR_UI_ENERGYBAR "EnergyBar"
#define ACTOR_UI_INVENTORY "Inventory"

#define ACTOR_TITLE_BACKGROUND "TitleBackGround"
#define ACTOR_TITLE_BUTTON_NEW "TitleButtonNewGame"
#define ACTOR_TITLE_BUTTON_LOAD "TitleButtonLoadGame"
#define ACTOR_TITLE_BUTTON_EXIT "TitleButtonExitGame"
#define ACTOR_TITLE_LOGO "TitleLogo"

// 플레이어 수치
#define PLAYER_COL_SIZE 30
#define PLAYER_ACTION_COL_SIZE 15
#define PLAYER_ACTION_COL_LENG 24.0f

// 디렉토리
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
#define DIR_FONT "Font"

// 이미지
#define IMAGE_CLOCK_POS_H 129
#define IMAGE_CLOCK_POS_W 1125
#define IMAGE_CLOCK_SIZE_H 236
#define IMAGE_CLOCK_SIZE_W 288
#define IMAGE_CLOCK "Clock.bmp"
#define IMAGE_ENERGYBAR_POS_H 591
#define IMAGE_ENERGYBAR_POS_W 1249
#define IMAGE_FARM_BUILDING "FarmBuildings.bmp"
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
#define IMAGE_TOOL_ICON "ToolIcon.bmp"
#define IMAGE_FULL_SIZE_H 720
#define IMAGE_FULL_SIZE_W 1280
#define IMAGE_FONT "Font.bmp"
#define IMAGE_FONT_NUMBER "FontNumber.bmp"
#define IMAGE_SIZE_EMPTY 64

#define IMAGE_FISHING_MAX "FishingMax.bmp"
#define IMAGE_FISHING_HIT "FishingHit.bmp"
#define IMAGE_FISHING_FISHINGBAR "Fishingbar.bmp"
#define IMAGE_FISHING_POWERBAR "FishingPowerbar.bmp"
#define IMAGE_FISHING_PROGRESS "FishingProgress.bmp"
#define IMAGE_FISHING_FISH_HITBOX "FishinghitBox.bmp"
#define IMAGE_FISHING_CATCH_HITBOX "Fishinghitbox.bmp"
#define IMAGE_FISHING_LURE "lure.bmp"

#define IMAGE_ENVIRONMENT_SEED "Seed.bmp"
#define IMAGE_ENVIRONMENT_CROPS "Crops.bmp"
#define IMAGE_ENVIRONMENT_FISHING "Fishing.bmp"
#define IMAGE_ENVIRONMENT_FORAGE "Forage.bmp"
#define IMAGE_ENVIRONMENT_FRUIT "Fruit.bmp"
#define IMAGE_ENVIRONMENT_MAPLETREE "MapleTree.bmp"
#define IMAGE_ENVIRONMENT_OAKTREE "OakTree.bmp"
#define IMAGE_ENVIRONMENT_PINETREE "PineTree.bmp"

#define IMAGE_ITEM_FORAGE "Forage.bmp"

#define IMAGE_TILESET_DIRT "Dirt.bmp"
#define IMAGE_TILESET_DIRTWATERED "DirtWatered.bmp"

// 키 입력
#define KEY_MOVE_LEFT "MoveLeft"
#define KEY_MOVE_RIGHT "MoveRight"
#define KEY_MOVE_UP "MoveUp"
#define KEY_MOVE_DOWN "MoveDown"
#define KEY_INTERACT "Interact"
#define KEY_INVEN_EXTEND "InventoryExtend"

// 인벤토리 선택 단축키
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


// 맵
// 농장
#define MAP_FARM_BACKGORUND "FarmBack.bmp"
#define MAP_FARM_BUILDING "FarmBuilding.bmp"
#define MAP_FARM_FRONT "FarmFront.bmp"
#define MAP_FARM_ALWAYSFRONT "FarmAlwaysfront.bmp"
#define MAP_FARM_COLLISION "FarmBuildingCollision.bmp"
#define MAP_FARM_RENDER_ORDER_COLLISION "FarmFrontCollision.bmp"
#define MAP_FARM_SIZE_H 3120.0f
#define MAP_FARM_SIZE_W 3840.0f
// 타운
#define MAP_TOWN_BACKGORUND "TownBack.bmp"
#define MAP_TOWN_BUILDING "TownBuilding.bmp"
#define MAP_TOWN_FRONT "TownFront.bmp"
#define MAP_TOWN_ALWAYSFRONT "TownAlwaysfront.bmp"
#define MAP_TOWN_COLLISION "TownBuildingCollision.bmp"
#define MAP_TOWN_RENDER_ORDER_COLLISION "TownFrontCollision.bmp"
#define MAP_TOWN_SIZE_H 5280.0f
#define MAP_TOWN_SIZE_W 5760.0f

// 해변
#define MAP_BEACH_BACKGORUND "BeachBack.bmp"
#define MAP_BEACH_BUILDING "BeachBuilding.bmp"
#define MAP_BEACH_FRONT "BeachFront.bmp"
#define MAP_BEACH_ALWAYSFRONT "BeachAlwaysfront.bmp"
#define MAP_BEACH_COLLISION "BeachBuildingCollision.bmp"
#define MAP_BEACH_RENDER_ORDER_COLLISION "BeachFrontCollision.bmp"
#define MAP_BEACH_SIZE_H 2397.0f
#define MAP_BEACH_SIZE_W 4992.0f

// 컬리전
#define COL_GROUP_PLAYER "PlayerCollision"
#define COL_GROUP_PLAYER_ACTION "PlayerActionCollision"
#define COL_GROUP_MOUSE "Mouse"
#define COL_GROUP_INVENTORY_BAR "InventoryBar"
#define COL_GROUP_INVENTORY_EXTEND_BAR "InventoryExtendBar"
#define COL_GROUP_INVENTORY_BOX "InventoryBox"
#define COL_GROUP_INVENTORY_EXTEND_BOX "InventoryExtendBox"
#define COL_GROUP_CROPS "CropsCol"
#define COL_GROUP_TREES "TreeCol"
#define COL_GROUP_FISH_HITBOX "FishHitBox"
#define COL_GROUP_CATCH_HITBOX "CatchHitBox"

// 타일맵
#define TILEMAP_SIZE 48

// 레벨
#define LEVEL_CHANGE_FARM "LevelChangeFarm"
#define LEVEL_CHANGE_TOWN "LevelChangeTown"
#define LEVEL_TITLE "TitleLevel"
#define LEVEL_TOWN "TownLevel"
#define LEVEL_FARM "FarmLevel"
#define LEVEL_BEACH "BeachLevel"
#define LEVEL_PLAY "PlayLevel"
#define LEVEL_ENDING "EndingLevel"

// 윈도우
#define WINDOW_BACKBUFFER "BackBuffer"
#define WINDOW_GAMEWINDOW "GameWindow"
#define WINDOW_MAINDC "WindowMain"

#define WINDOW_SIZE_H 720
#define WINDOW_SIZE_W 1280


// 애니메이션
#define ANIM_KEYWARD_IDLE "Idle"
#define ANIM_KEYWARD_WALK "Walk"
#define ANIM_KEYWARD_HIT_HORIZON "HitHorizon"
#define ANIM_KEYWARD_HIT_VERTICAL "HitVertical"
#define ANIM_KEYWARD_WATERING "Watering"
#define ANIM_KEYWARD_DIR_RIGHT "Right"
#define ANIM_KEYWARD_DIR_LEFT "Left"
#define ANIM_KEYWARD_DIR_UP "Up"
#define ANIM_KEYWARD_DIR_DOWN "Down"

#define ANIM_IDLE_DOWN "IdleDown"
#define ANIM_IDLE_RIGHT "IdleRight"
#define ANIM_IDLE_LEFT "IdleLeft"
#define ANIM_IDLE_UP "IdleUp"

#define ANIM_WALK_DOWN "WalkDown"
#define ANIM_WALK_RIGHT "WalkRight"
#define ANIM_WALK_LEFT "WalkLeft"
#define ANIM_WALK_UP "WalkUp"
// 세로로 휘두르기
#define ANIM_HIT_HORIZON_DOWN "HitHorizonDown"
#define ANIM_HIT_HORIZON_RIGHT "HitHorizonRight"
#define ANIM_HIT_HORIZON_LEFT "HitHorizonLeft"
#define ANIM_HIT_HORIZON_UP "HitHorizonUp"
// 가로로 휘두르기
#define ANIM_HIT_VERTICAL_DOWN "HitVerticalDown"
#define ANIM_HIT_VERTICAL_RIGHT "HitVerticalRight"
#define ANIM_HIT_VERTICAL_LEFT "HitVerticalLeft"
#define ANIM_HIT_VERTICAL_UP "HitVerticalUp"
// 물주기
#define ANIM_WATERING_DOWN "WateringDown"
#define ANIM_WATERING_RIGHT "WateringRight"
#define ANIM_WATERING_LEFT "WateringLeft"
#define ANIM_WATERING_UP "WateringUp"


// 아이템
#define ITEM_NAME_EMPTY "Empty"
// 장비
#define ITEM_NAME_HOE "Hoe"
#define ITEM_NAME_AXE "Axe"
#define ITEM_NAME_WATERINGCAN "WateringCan"
#define ITEM_NAME_FISHINGROD "FishingRod"
// 나무
#define ITEM_NAME_OAKTREE "OakTree"
#define ITEM_NAME_MAPLETREE "MapleTree"
#define ITEM_NAME_PINETREE "PineTree"
// 농작물
#define ITEM_NAME_PARSNIP "Parsnip"
#define ITEM_NAME_COULIFLOWER "CaouliFlower"
#define ITEM_NAME_GARLIC "Garlic"
#define ITEM_NAME_RHUBARB "Rhubarb"
#define ITEM_NAME_TOMATO "Tomato"
#define ITEM_NAME_HOTPEPPER "Hotpepper"
#define ITEM_NAME_RADISH "Radish"
#define ITEM_NAME_STARFRUIT "Star"
#define ITEM_NAME_EGGPLANT "Eggplant"
#define ITEM_NAME_PUMPKIN "Pumpkin"
#define ITEM_NAME_YAM "Yam"
#define ITEM_NAME_BEET "Beet"
#define ITEM_NAME_SUNFLOWER "SunFlower"
#define ITEM_NAME_GREENBEAN "Greenbean"
#define ITEM_NAME_POTATO "Potato"
#define ITEM_NAME_KALE "Kale"
#define ITEM_NAME_MELON "Melon"
#define ITEM_NAME_BLUEBERRY "Blueberry"
#define ITEM_NAME_REDCABBAGE "RedCabbage"
#define ITEM_NAME_CORN "Corn"
// 생선
#define ITEM_NAME_PUFFERFISH "PufferFish"
#define ITEM_NAME_ANCHOVY "Anchovy"
#define ITEM_NAME_TUNA "Tuna"
// 필드 아이템
#define ITEM_NAME_MINITREE "MiniTree"
#define ITEM_NAME_PARSNIP_FRUIT "ParsnipFruit"
#define ITEM_NAME_COULIFLOWER_FRUIT "CaouliFlowerFruit"
#define ITEM_NAME_GARLIC_FRUIT "GarlicFruit"
#define ITEM_NAME_RHUBARB_FRUIT "RhubarbFruit"
#define ITEM_NAME_TOMATO_FRUIT "TomatoFruit"
#define ITEM_NAME_HOTPEPPER_FRUIT "HotpepperFruit"
#define ITEM_NAME_RADISH_FRUIT "RadishFruit"
#define ITEM_NAME_STARFRUIT_FRUIT "StarFruitFruit"
#define ITEM_NAME_EGGPLANT_FRUIT "EggplantFruit"
#define ITEM_NAME_PUMPKIN_FRUIT "PumpkinFruit"
#define ITEM_NAME_YAM_FRUIT "YamFruit"
#define ITEM_NAME_BEET_FRUIT "BeetFruit"
#define ITEM_NAME_SUNFLOWER_FRUIT "SunFlowerFruit"
#define ITEM_NAME_GREENBEAN_FRUIT "GreenbeanFruit"
#define ITEM_NAME_POTATO_FRUIT "PotatoFruit"
#define ITEM_NAME_KALE_FRUIT "KaleFruit"
#define ITEM_NAME_MELON_FRUIT "MelonFruit"
#define ITEM_NAME_BLUEBERRY_FRUIT "BlueberryFruit"
#define ITEM_NAME_REDCABBAGE_FRUIT "RedCabbageFruit"
#define ITEM_NAME_CORN_FRUIT "CornFruit"