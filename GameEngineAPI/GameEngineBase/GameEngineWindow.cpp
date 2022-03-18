#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

// HWND hWnd       ��� �������� �ڵ�
// UINT message    �� �޼����� ����
// WPARAM wParam   
// LPARAM lParam   

LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // ������ ����, ���� ����
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);
    // ������ ȭ�鿡 �����ΰ� �׷��� ���
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

// ������ Ŭ���� ����
void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    // ������ Ŭ���� ���
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
    // ������ ������ �ߺ� ����Ǿ�����츦 ���. �̹� �����Ǿ��ִ� ��� �Լ� ����.
    if (nullptr != hInst_)
    {
        MsgBoxAssert("�����츦 �ߺ��Ͽ� ���� �߽��ϴ�.");
        return;
    }

    Title_ = _Title;
    hInst_ = _hInst;
    RegClass(_hInst);

    // ������ �ڵ�
    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    // ȭ�鿡 ���𰡸� �׸��� �ڵ�
    // �׷����ϴ� �����츦 ����
    HDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
}


void GameEngineWindow::ShowGameWindow()
{
    // �����찡 �������� �ʾ������ �Լ� ����
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("���� �����찡 ��������� �ʾҽ��ϴ�. ȭ�鿡 ����� �� �����ϴ�.");
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

    // �⺻ �޽��� �����Դϴ�:
    while (WindowOn_)
    {
        // GetMessage�� �޼����� ������ ���� ������ ��ٸ�. ���ӿ��� ������.
        // PM_NOREMOVE �޼��� ������ ���ÿ��� �޼����� �������� ����.
        // PM_REMONVE  �޼��� ������ ���ÿ��� �޼����� ������.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // Ű������ �Է��� �����ϰ�� WM_KEYDOWN�κ��� WM_CHAR(�Էµ� ����)�� ��ȯ�ϴ� �Լ�.
            TranslateMessage(&msg);

            // WM_CHAR�� WndProc�� ����
            DispatchMessage(&msg);
        }

        // ���ӽ����

        if (nullptr == _LoopFunction)
        {
            continue;
        }

        _LoopFunction();
    }
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale)
{
    // �������� �޴���, â�� �����ӻ����� ���� ����� �������� ũ�⸦ ����
    RECT Rc = { 0, 0, _Scale.ix(), _Scale.iy() };
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    Scale_ = _Scale;

    SetWindowPos(hWnd_, nullptr, _Pos.ix(), _Pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);

}