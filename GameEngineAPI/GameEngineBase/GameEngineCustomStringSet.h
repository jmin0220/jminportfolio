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
#define DIR_INTERFACE "Interface"
#define DIR_TOOL "Tool"
#define DIR_MAP "Map"

// �̹���
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
#define IMAGE_INVENTORY_BAR "InventoryBar.bmp"
#define IMAGE_INVENTORY_EXTEND "InventoryExtend.bmp"
#define IMAGE_INVENTORY_SELECT "InventorySelectBox.bmp"
#define IMAGE_INVENTORYBAR_POS_UP_X 640
#define IMAGE_INVENTORYBAR_POS_UP_Y 55
#define IMAGE_INVENTORYBAR_POS_DOWN_X 640
#define IMAGE_INVENTORYBAR_POS_DOWN_Y 663
#define IMAGE_INVENTORY_EXT_POS_X 640
#define IMAGE_INVENTORY_EXT_POS_Y 563
#define IMAGE_TITLE_BUTTON_H 174
#define IMAGE_TITLE_BUTTON_W 222
#define IMAGE_TITLE_BACKGOUND "MainBackground.bmp"
#define IMAGE_TITLE_LOGO_H 374
#define IMAGE_TITLE_LOGO_W 796
#define IMAGE_TOOL_SET1 "Tools_set1.bmp"
#define IMAGE_FULL_SIZE_H 720
#define IMAGE_FULL_SIZE_W 1280

// Ű �Է�
#define KEY_MOVE_LEFT "MoveLeft"
#define KEY_MOVE_RIGHT "MoveRight"
#define KEY_MOVE_UP "MoveUp"
#define KEY_MOVE_DOWN "MoveDown"
#define KEY_INTERACT "Interact"

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
#define KEY_INVEN_EXTEND "INVEN_EXTEND"


// ����
#define MATH_VERTICAL_SPD 1.0f
#define MATH_HORIZON_SPD 1.0f


// ��
#define MAP_FARM_SIZE_H 3120.0f
#define MAP_FARM_SIZE_W 3840.0f

// ���ڿ�
#define STRING_DOT "."

// ����
#define LEVEL_CHANGE "LevelChange"
#define LEVEL_TITLE "TitleLevel"
#define LEVEL_FARM "FarmLevel"
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




// ����� �޼���
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
