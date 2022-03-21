#include "GameEngineWindow.h"

// HWND hWnd       대상 윈도우의 핸들
// UINT message    그 메세지의 종류
// WPARAM wParam   
// LPARAM lParam   

LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // 윈도우 종료, 루프 종료
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);
    // 윈도우 화면에 무엇인가 그려질 경우
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

GameEngineWindow::GameEngineWindow()
    : hInst_(nullptr)
    , hWnd_(nullptr)
    , WindowOn_(true)
    , HDC_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow() 
{
    if (nullptr != HDC_)
    {
        ReleaseDC(hWnd_, HDC_);
        HDC_ = nullptr;
    }

    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}

void GameEngineWindow::Off()
{
    WindowOn_ = false;
}

// 윈도우 클래스 생성
void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    // 윈도우 클래스 등록
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageProcess;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    // 윈도우 생성이 중복 실행되었을경우를 대비. 이미 생성되어있는 경우 함수 종료.
    if (nullptr != hInst_)
    {
        MsgBoxAssert("윈도우를 중복하여 띄우려 했습니다.");
        return;
    }

    Title_ = _Title;
    hInst_ = _hInst;
    RegClass(_hInst);

    // 윈도우 핸들
    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    // 화면에 무언가를 그리는 핸들
    // 그려야하는 윈도우를 전달
    HDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
}


void GameEngineWindow::ShowGameWindow()
{
    // 윈도우가 생성되지 않았을경우 함수 종료
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다. 화면에 출력할 수 없습니다.");
        return;
    }

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}

void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{
    if (nullptr != _InitFunction)
    {
        _InitFunction();
    }

    MSG msg;

    // 기본 메시지 루프입니다:
    while (WindowOn_)
    {
        // GetMessage는 메세지가 없으면 다음 실행을 기다림. 게임에는 부적합.
        // PM_NOREMOVE 메세지 실행후 스택에서 메세지를 제거하지 않음.
        // PM_REMONVE  메세지 실행후 스택에서 메세지를 제거함.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 키보드의 입력이 문자일경우 WM_KEYDOWN로부터 WM_CHAR(입력된 문자)를 반환하는 함수.
            TranslateMessage(&msg);

            // WM_CHAR를 WndProc에 전달
            DispatchMessage(&msg);
        }

        // 게임실행부

        if (nullptr == _LoopFunction)
        {
            continue;
        }

        _LoopFunction();
    }
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale)
{
    // 윈도우의 메뉴바, 창의 프레임사이즈 등을 고려한 윈도우의 크기를 생성
    RECT Rc = { 0, 0, _Scale.ix(), _Scale.iy() };
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    Scale_ = _Scale;

    SetWindowPos(hWnd_, nullptr, _Pos.ix(), _Pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);

}