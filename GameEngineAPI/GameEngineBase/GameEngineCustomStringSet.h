#pragma once
// 액터
#define ACTOR_PLAYER "Player"

#define ACTOR_UI_CLOCK "Clock"
#define ACTOR_UI_ENERGYBAR "EnergyBar"
#define ACTOR_UI_INVENTORY_BAR "InventoryBar"

#define ACTOR_TITLE_BACKGROUND "TitleBackGround"
#define ACTOR_TITLE_BUTTON_NEW "TitleButtonNewGame"
#define ACTOR_TITLE_BUTTON_LOAD "TitleButtonLoadGame"
#define ACTOR_TITLE_BUTTON_EXIT "TitleButtonExitGame"
#define ACTOR_TITLE_LOGO "TitleLogo"

// 디렉토리
#define DIR_PARENT "GameEngineAPI"
#define DIR_PLAYER "Player"
#define DIR_RESOURCES "Resources"
#define DIR_IMAGE "Image"
#define DIR_INTERFACE "Interface"
#define DIR_TOOL "Tool"
#define DIR_MAP "Map"

// 이미지
#define IMAGE_CLOCK_POS_H 129
#define IMAGE_CLOCK_POS_W 1125
#define IMAGE_CLOCK_SIZE_H 236
#define IMAGE_CLOCK_SIZE_W 288
#define IMAGE_ENERGYBAR_POS_H 591
#define IMAGE_ENERGYBAR_POS_W 1249
#define IMAGE_PLAYER_CLOTH "PlayerCloth.bmp"
#define IMAGE_PLAYER_HAIR "PlayerHair.bmp"
#define IMAGE_PLAYER_HAT "PlayerHat.bmp"
#define IMAGE_PLAYER_MASK "PlayerMask.bmp"
#define IMAGE_PLAYER_MAN_BODY "PlayerManBody.bmp"
#define IMAGE_PLAYER_WOMAN_BODY "PlayerWomanBody.bmp"
#define IMAGE_INVENTORYBAR_POS_UP_X 640
#define IMAGE_INVENTORYBAR_POS_UP_Y 55
#define IMAGE_INVENTORYBAR_POS_DOWN_X 640
#define IMAGE_INVENTORYBAR_POS_DOWN_Y 663
#define IMAGE_TITLE_BUTTON_H 174
#define IMAGE_TITLE_BUTTON_W 222
#define IMAGE_TITLE_BACKGOUND "MainBackground.bmp"
#define IMAGE_TITLE_LOGO_H 374
#define IMAGE_TITLE_LOGO_W 796
#define IMAGE_TOOL_SET1 "Tools_set1.bmp"
#define IMAGE_EXT_BMP "Bmp"
#define IMAGE_FULL_SIZE_H 720
#define IMAGE_FULL_SIZE_W 1280

// 키 입력
#define KEY_MOVE_LEFT "MoveLeft"
#define KEY_MOVE_RIGHT "MoveRight"
#define KEY_MOVE_UP "MoveUp"
#define KEY_MOVE_DOWN "MoveDown"
#define KEY_INTERACT "Interact"


// 수학
#define MATH_VERTICAL_SPD 1.0f
#define MATH_HORIZON_SPD 1.0f


// 맵
#define MAP_FARM_SIZE_H 3120.0f
#define MAP_FARM_SIZE_W 3840.0f

// 문자열
#define STRING_DOT "."

// 레벨
#define LEVEL_CHANGE "LevelChange"
#define LEVEL_TITLE "TitleLevel"
#define LEVEL_FARM "FarmLevel"
#define LEVEL_PLAY "PlayLevel"
#define LEVEL_ENDING "EndingLevel"

// 윈도우
#define WINDOW_BACKBUFFER "BackBuffer"
#define WINDOW_GAMEWINDOW "GameWindow"
#define WINDOW_MAINDC "WindowMain"

#define WINDOW_SIZE_H 720
#define WINDOW_SIZE_W 1280


// 애니메이션
#define ANIM_IDLE_DOWN "IdleDown"
#define ANIM_IDLE_RIGHT "IdleRight"
#define ANIM_IDLE_LEFT "IdleLeft"
#define ANIM_IDLE_UP "IdleUp"

#define ANIM_WALK_DOWN "WalkDown"
#define ANIM_WALK_RIGHT "WalkRight"
#define ANIM_WALK_LEFT "WalkLeft"
#define ANIM_WALK_UP "WalkUp"




// 디버그 메세지
#define DEBUG_MSG_DC_CREATE_FAILURE "Create ImageDC failure"

#define DEBUG_MSG_GENGINE_NOT_START "GEngine ERROR Engine is NOT Start"

#define DEBUG_MSG_IMAGE_ALREADY_EXIST "You tried Create Image that is Already Created"
#define DEBUG_MSG_IMAGE_CREATE_FAILURE " Create Image failure"
#define DEBUG_MSG_IMAGE_CREATE_ZEROSIZE "You tried Create 0 Size Image"
#define DEBUG_MSG_IMAGE_LOAD_FAILURE " Image Load Failure"
#define DEBUG_MSG_IMAGE_NOT_DIVISIBLE_SCALE "Scale is Not Divisible Number"
#define DEBUG_MSG_IMAGE_NOT_SET_RENDERER "This Image is not setting in Renderer"
#define DEBUG_MSG_IMAGE_NOT_EXIST "This Image is not Exist"
#define DEBUG_MSG_IMAGE_NOT_EXIST_SET_RENDERER " Tried to Set a Non-Existent Image on the Renderer"

#define DEBUG_MSG_KEY_EXIST "This Key is Already exist"
#define DEBUG_MSG_KEY_NOT_EXIST "This Key is not Exist" 

#define DEBUG_MSG_LEVEL_CURRENT_NULL "Current Level is NULL => GameEngine Loop Error"
#define DEBUG_MSG_LEVEL_FIND_FAILURE "Level Find Error"

#define DEBUG_MSG_WINDOW_DUPLICATE "Create a duplicate window"
#define DEBUG_MSG_WINDOW_NOT_CREATE "Main Window is not Created"

#define DEBUG_ERROR "Error"
