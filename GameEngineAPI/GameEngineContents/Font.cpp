#include "Font.h"
#include "ContentsEnums.h"

Font::Font() 
{
}

Font::~Font() 
{
}

void Font::Start()
{
	RendererFont_ = CreateRenderer(IMAGE_FONT, (int)ORDER::UIFONT);
	RendererFont_->CameraEffectOff();
	RendererNumber_ = CreateRenderer(IMAGE_FONT_NUMBER, (int)ORDER::UIFONT);
	RendererNumber_->CameraEffectOff();

	RendererFontOff();
	RendererNumberOff();
}

GameEngineRenderer* Font::GetNumberFont(int _Index)
{
	RendererNumber_->SetIndex(_Index);

	return RendererNumber_;
}

GameEngineRenderer* Font::GetFont(char _Char)
{
	int Index = 0;

	// 입력받은 글자에 맞춘 인덱스 설정
	switch (_Char)
	{
	case 'A':
		Index = 0;
		break;
	case 'B':
		Index = 1;
		break;
	case 'C':
		Index = 2;
		break;
	case 'D':
		Index = 3;
		break;
	case 'E':
		Index = 4;
		break;
	case 'F':
		Index = 5;
		break;
	case 'G':
		Index = 6;
		break;
	case 'H':
		Index = 7;
		break;
	case 'I':
		Index = 8;
		break;
	case 'J':
		Index = 9;
		break;
	case 'K':
		Index = 10;
		break;
	case 'L':
		Index = 11;
		break;
	case 'M':
		Index = 12;
		break;
	case 'N':
		Index = 13;
		break;
	case 'O':
		Index = 14;
		break;
	case 'P':
		Index = 15;
		break;
	case 'Q':
		Index = 16;
		break;
	case 'R':
		Index = 17;
		break;
	case 'S':
		Index = 18;
		break;
	case 'T':
		Index = 19;
		break;
	case 'U':
		Index = 20;
		break;
	case 'V':
		Index = 21;
		break;
	case 'W':
		Index = 22;
		break;
	case 'X':
		Index = 23;
		break;
	case 'Y':
		Index = 24;
		break;
	case 'Z':
		Index = 25;
		break;
	case 'a':
		Index = 26;
		break;
	case 'b':
		Index = 27;
		break;
	case 'c':
		Index = 28;
		break;
	case 'd':
		Index = 29;
		break;
	case 'e':
		Index = 30;
		break;
	case 'f':
		Index = 31;
		break;
	case 'g':
		Index = 32;
		break;
	case 'h':
		Index = 33;
		break;
	case 'i':
		Index = 34;
		break;
	case 'j':
		Index = 35;
		break;
	case 'k':
		Index = 36;
		break;
	case 'l':
		Index = 37;
		break;
	case 'm':
		Index = 38;
		break;
	case 'n':
		Index = 39;
		break;
	case 'o':
		Index = 40;
		break;
	case 'p':
		Index = 41;
		break;
	case 'q':
		Index = 42;
		break;
	case 'r':
		Index = 43;
		break;
	case 's':
		Index = 44;
		break;
	case 't':
		Index = 45;
		break;
	case 'u':
		Index = 46;
		break;
	case 'v':
		Index = 47;
		break;
	case 'w':
		Index = 48;
		break;
	case 'x':
		Index = 49;
		break;
	case 'y':
		Index = 50;
		break;
	case 'z':
		Index = 51;
		break;
	case '0':
		Index = 52;
		break;
	case '1':
		Index = 53;
		break;
	case '2':
		Index = 54;
		break;
	case '3':
		Index = 55;
		break;
	case '4':
		Index = 56;
		break;
	case '5':
		Index = 57;
		break;
	case '6':
		Index = 58;
		break;
	case '7':
		Index = 59;
		break;
	case '8':
		Index = 60;
		break;
	case '9':
		Index = 61;
		break;
	case '?':
		Index = 62;
		break;
	case '!':
		Index = 63;
		break;
	default:
		// 공백
		Index = 64;
		break;
	}

	RendererFont_->SetIndex(Index);

	return RendererFont_;
}