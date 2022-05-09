#pragma once
// 액터
#define ACTOR_PLAYER "Player"
#define ACTOR_MOUSE "Mouse"
#define ACTOR_INVENTORY "Inventory"

#define ACTOR_UI_CLOCK "Clock"
#define ACTOR_UI_ENERGYBAR "EnergyBar"
#define ACTOR_UI_INVENTORY "Inventory"

#define ACTOR_TITLE_BACKGROUND "TitleBackGround"
#define ACTOR_TITLE_BUTTON_NEW "TitleButtonNewGame"
#define ACTOR_TITLE_BUTTON_LOAD "TitleButtonLoadGame"
#define ACTOR_TITLE_BUTTON_EXIT "TitleButtonExitGame"
#define ACTOR_TITLE_LOGO "TitleLogo"

// 수치
#define PLAYER_COL_SIZE 30

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
#define DIR_SEEDSHOP "SeedShop"
#define DIR_MINES "Mines"

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
#define IMAGE_TOOL_ANIM "ToolAnim.bmp"
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
#define IMAGE_FISHING_CATCH_HITBOX "Catchhitbox.bmp"
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
#define IMAGE_ITEM_MINES "Mines.bmp"
#define IMAGE_ITEM_MINERAL "Mineral.bmp"

#define IMAGE_SEEDSHOP_INTERFACE "ShopInterface.bmp"
#define IMAGE_SEEDSHOP_STOCK_PARSNIP "ParsnipStock.bmp"
#define IMAGE_SEEDSHOP_STOCK_POTATO "PotatoStock.bmp"
#define IMAGE_SEEDSHOP_STOCK_KALE "KaleStock.bmp"
#define IMAGE_SEEDSHOP_STOCK_GREENBEAN "GreenBeanStock.bmp"
#define IMAGE_SEEDSHOP_STOCK_CAULIFLOWER "CauliflowerStock.bmp"

#define IMAGE_TILESET_DIRT "Dirt.bmp"
#define IMAGE_TILESET_DIRTWATERED "DirtWatered.bmp"

// 키 입력
#define KEY_MOVE_LEFT "MoveLeft"
#define KEY_MOVE_RIGHT "MoveRight"
#define KEY_MOVE_UP "MoveUp"
#define KEY_MOVE_DOWN "MoveDown"
#define KEY_INTERACT "Interact"
#define KEY_INVEN_EXTEND "InventoryExtend"
#define KEY_CLOSE "CloseShop"
#define KEY_DEBUG "DebugSwitch"

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

// 씨앗상점
#define MAP_SEEDSHOP_BACKGROUND "SeedShopBack.bmp"
#define MAP_SEEDSHOP_BUILDING "SeedShopBuilding.bmp"
#define MAP_SEEDSHOP_FRONT "SeedShopFront.bmp"
#define MAP_SEEDSHOP_COLLISION "SeedShopBuildingCollision.bmp"
#define MAP_SEEDSHOP_RENDER_ORDER_COLLISION "SeedShopFrontCollision.bmp"
#define MAP_SEEDSHOP_SIZE_H 1537.0f
#define MAP_SEEDSHOP_SIZE_W 2016.0f

// 광산
#define MAP_MINES_BACKGROUND "MineBack.bmp"
#define MAP_MINES_BUILDING "MineBuilding.bmp"
#define MAP_MINES_FRONT "MineFront.bmp"
#define MAP_MINES_COLLISION "MineBuildingCollision.bmp"
#define MAP_MINES_RENDER_ORDER_COLLISION "MineFrontCollision.bmp"
#define MAP_MINES_SIZE_H 961.0f
#define MAP_MINES_SIZE_W 2600.0f

#define MAP_CAVE1_BACKGROUND "Cave1Back.bmp"
#define MAP_CAVE1_BUILDING "Cave1Building.bmp"
#define MAP_CAVE1_FRONT "Cave1Front.bmp"
#define MAP_CAVE1_COLLISION "Cave1BuildingCollision.bmp"
#define MAP_CAVE1_RENDER_ORDER_COLLISION "Cave1FrontCollision.bmp"
#define MAP_CAVE1_SIZE_H 960.0f
#define MAP_CAVE1_SIZE_W 1280.0f

#define MAP_CAVE2_BACKGROUND "Cave2Back.bmp"
#define MAP_CAVE2_BUILDING "Cave2Building.bmp"
#define MAP_CAVE2_FRONT "Cave2Front.bmp"
#define MAP_CAVE2_COLLISION "Cave2BuildingCollision.bmp"
#define MAP_CAVE2_RENDER_ORDER_COLLISION "Cave2FrontCollision.bmp"
#define MAP_CAVE2_SIZE_H 1680.0f
#define MAP_CAVE2_SIZE_W 1680.0f

// 컬리전
#define COL_GROUP_PLAYER "PlayerCollision"
#define COL_GROUP_PLAYER_ACTION "PlayerActionCollision"
#define COL_GROUP_MOUSE "Mouse"
#define COL_GROUP_STOCK "Stock"
#define COL_GROUP_INVENTORY_BAR "InventoryBar"
#define COL_GROUP_INVENTORY_EXTEND_BAR "InventoryExtendBar"
#define COL_GROUP_INVENTORY_BOX "InventoryBox"
#define COL_GROUP_INVENTORY_EXTEND_BOX "InventoryExtendBox"
#define COL_GROUP_CROPS "CropsCol"
#define COL_GROUP_MINES "MinesCol"
#define COL_GROUP_TREES "TreeCol"
#define COL_GROUP_FISH_HITBOX "FishHitBox"
#define COL_GROUP_CATCH_HITBOX "CatchHitBox"

// 타일맵
#define TILEMAP_SIZE 48.0f

// 레벨
#define LEVEL_CHANGE_FARM "LevelChangeFarm"
#define LEVEL_CHANGE_TOWN "LevelChangeTown"
#define LEVEL_TITLE "TitleLevel"
#define LEVEL_TOWN "TownLevel"
#define LEVEL_FARM "FarmLevel"
#define LEVEL_BEACH "BeachLevel"
#define LEVEL_PLAY "PlayLevel"
#define LEVEL_SEEDSHOP "SeedShopLevel"
#define LEVEL_MINES "MinesLevel"
#define LEVEL_CAVE1 "Cave1Level"
#define LEVEL_CAVE2 "Cave2Level"
#define LEVEL_ENDING "EndingLevel"

// 윈도우
#define WINDOW_BACKBUFFER "BackBuffer"
#define WINDOW_GAMEWINDOW "GameWindow"
#define WINDOW_MAINDC "WindowMain"

#define WINDOW_SIZE_H 720
#define WINDOW_SIZE_W 1280


// 애니메이션
#define ANIM_KEYWORD_IDLE "Idle"
#define ANIM_KEYWORD_WALK "Walk"
#define ANIM_KEYWORD_HIT_HORIZON "HitHorizon"
#define ANIM_KEYWORD_HIT_VERTICAL "HitVertical"
#define ANIM_KEYWORD_WATERING "Watering"
#define ANIM_KEYWORD_FISHING "Fishing"
#define ANIM_KEYWORD_FISHING_WAIT "FishingWait"
#define ANIM_KEYWORD_HIT_HORIZON "HitHorizon"
#define ANIM_KEYWORD_HIT_VERTICAL "HitVertical"

#define ANIM_KEYWORD_TOOL_IDLE "ToolIdle"
#define ANIM_KEYWORD_TOOL_HOE "Hoe"
#define ANIM_KEYWORD_TOOL_AXE "Axe"
#define ANIM_KEYWORD_TOOL_PICKAXE "Pickaxe"
#define ANIM_KEYWORD_TOOL_WATERING "ToolWatering"
#define ANIM_KEYWORD_TOOL_FISHING "ToolFishing"
#define ANIM_KEYWORD_TOOL_FISHING_WAIT "ToolFishingWait"

#define ANIM_KEYWORD_DIR_RIGHT "Right"
#define ANIM_KEYWORD_DIR_LEFT "Left"
#define ANIM_KEYWORD_DIR_UP "Up"
#define ANIM_KEYWORD_DIR_DOWN "Down"

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
// 물주기
#define ANIM_WATERING_DOWN "WateringDown"
#define ANIM_WATERING_RIGHT "WateringRight"
#define ANIM_WATERING_LEFT "WateringLeft"
#define ANIM_WATERING_UP "WateringUp"
// 낚시
#define ANIM_FISHING_DOWN "FishingDown"
#define ANIM_FISHING_RIGHT "FishingRight"
#define ANIM_FISHING_LEFT "FishingLeft"
#define ANIM_FISHING_UP "FishingUp"

#define ANIM_FISHING_DOWN_WAIT "FishingWaitDown"
#define ANIM_FISHING_RIGHT_WAIT "FishingWaitRight"
#define ANIM_FISHING_LEFT_WAIT "FishingWaitLeft"
#define ANIM_FISHING_UP_WAIT "FishingWaitUp"

#define TOOL_ANIM_IDLE "ToolIdle"
#define TOOL_ANIM_HOE_RIGHT "HoeRight"
#define TOOL_ANIM_HOE_LEFT "HoeLeft"
#define TOOL_ANIM_HOE_DOWN "HoeDown"
#define TOOL_ANIM_HOE_UP "HoeUp"

#define TOOL_ANIM_AXE_RIGHT "AxeRight"
#define TOOL_ANIM_AXE_LEFT "AxeLeft"
#define TOOL_ANIM_AXE_DOWN "AxeDown"
#define TOOL_ANIM_AXE_UP "AxeUp"

#define TOOL_ANIM_PICKAXE_RIGHT "PickaxeRight"
#define TOOL_ANIM_PICKAXE_LEFT "PickaxeLeft"
#define TOOL_ANIM_PICKAXE_DOWN "PickaxeDown"
#define TOOL_ANIM_PICKAXE_UP "PickaxeUp"

#define TOOL_ANIM_WATERINGCAN_RIGHT "ToolWateringRight"
#define TOOL_ANIM_WATERINGCAN_LEFT "ToolWateringLeft"
#define TOOL_ANIM_WATERINGCAN_DOWN "ToolWateringDown"
#define TOOL_ANIM_WATERINGCAN_UP "ToolWateringUp"

#define TOOL_ANIM_FISHING_RIGHT "ToolFishingRight"
#define TOOL_ANIM_FISHING_LEFT "ToolFishingLeft"
#define TOOL_ANIM_FISHING_DOWN "ToolFishingDown"
#define TOOL_ANIM_FISHING_UP "ToolFishingUp"
#define TOOL_ANIM_FISHING_WAIT_RIGHT "ToolFishingWaitRight"
#define TOOL_ANIM_FISHING_WAIT_LEFT "ToolFishingWaitLeft"
#define TOOL_ANIM_FISHING_WAIT_DOWN "ToolFishingWaitDown"
#define TOOL_ANIM_FISHING_WAIT_UP "ToolFishingWaitUp"


// 아이템
#define ITEM_NAME_EMPTY "Empty"
// 장비
#define ITEM_NAME_HOE "Hoe"
#define ITEM_NAME_AXE "Axe"
#define ITEM_NAME_WATERINGCAN "WateringCan"
#define ITEM_NAME_FISHINGROD "FishingRod"
#define ITEM_NAME_PICKAXE "Pickaxe"
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

#define ITEM_NAME_DIAMOND "Diamond"
#define ITEM_NAME_RUBY "Ruby"
#define ITEM_NAME_JADE "Jade"
#define ITEM_NAME_AMETHYST "Amethyst"
#define ITEM_NAME_TOPAZ "Topaz"



// 사운드
#define SOUND_AXE "axe.wav"
#define SOUND_BRICK "brick1.wav"
#define SOUND_COINS "coins.wav"
#define SOUND_REEL "slowReel.wav"
#define SOUND_FISHBITE "fishBite.wav"
#define SOUND_FISHESCAPE "fishEscape.wav"
#define SOUND_FISHHIT "FishHit.wav"
#define SOUND_FISHSLAP "fishSlap.wav"
#define SOUND_HOE "hoe.wav"
#define SOUND_HOEHIT "hoeHit.wav"
#define SOUND_MOUSECLICK "mouseClick.wav"
#define SOUND_PICKUPITEM "pickUpItem.wav"
#define SOUND_SMALLSELCET "smallSelect.wav"
#define SOUND_SPRINGDAY "spring_day.wav"
#define SOUND_STUMPCRACK "stumpCrack.wav"
#define SOUND_WATER "water_step1.wav"
#define SOUND_WOODDYHIT "woodyHit.wav"