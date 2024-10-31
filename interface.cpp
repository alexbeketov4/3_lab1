//WindowsProject1.cpp : Определяет точку входа для приложения.

#include "framework.h"
#include "framework.h"
#include "WindowsProject1.h"
#include "LinkedListSequence.h"
#include "tests.h"
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#define MAX_LOADSTRING 100
#define IDC_MAIN_EDIT 101
#define IDC_MAIN_BUTTON 102
#define IDC_OPERATION_BUTTON 103
#define IDC_DISPLAY_SEQUENCE 104
#define IDC_APPEND_BUTTON 105
#define IDC_PREPEND_BUTTON 106
#define IDC_INSERT_BUTTON 107
#define IDC_INDEX_EDIT 108
#define IDC_INPUT_VALUE_EDIT 109
#define IDC_GET_BUTTON 110
#define IDC_START_INDEX_EDIT 111
#define IDC_END_INDEX_EDIT 112
#define IDC_GET_SUBSEQUENCE_BUTTON 113
#define IDC_SECOND_SEQUENCE_EDIT 114
#define IDC_CREATE_SECOND_SEQUENCE_BUTTON 115
#define IDC_CONCAT_BUTTON 116

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

UnqPtr<LinkedListSequence<int>> sequence;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

std::vector<int> ParseInput(const std::wstring& input) {
    std::wstringstream stream(input);
    std::vector<int> result;
    int num;
    while (stream >> num) {
        result.push_back(num);
    }
    return result;
}

void DisplaySequence(HWND hWnd) {
    std::wstring sequenceStr;
    for (int i = 0; i < sequence->GetLength(); i++) {
        sequenceStr += std::to_wstring(sequence->Get(i)) + L" ";
    }
    SetWindowText(GetDlgItem(hWnd, IDC_DISPLAY_SEQUENCE), sequenceStr.c_str());
}

void DisplaySubSequence(HWND hWnd, const Sequence<int>* subSeq) {
    std::wstring result = L"";
    for (int i = 0; i < subSeq->GetLength(); i++) {
        result += std::to_wstring(subSeq->Get(i)) + L" ";
    }
    SetWindowText(GetDlgItem(hWnd, IDC_DISPLAY_SEQUENCE), result.c_str());
}

void RunTests()
{
    Test_of_GetLastLinkedListSmart();
    Test_of_GetFirst_LinkedListSmart();
    Test_of_GetLength_LinkedListSmart();
    Test_of_Get_LinkedListSmart();
    Test_of_GetSubList_LinkedListSmart();
    Test_of_Append_LinkedListSmart();
    Test_of_Prepend_LinkedListSmart();
    Test_of_InsertAt_LinkedListSmart();
    Test_of_Concat_LinkedListSmart();

    Test_of_GetLastLinkedListSequence();
    Test_of_GetFirst_LinkedListSequence();
    Test_of_GetLength_LinkedListSequence();
    Test_of_Get_LinkedListSequence();
    Test_of_GetSubList_LinkedListSequence();
    Test_of_Append_LinkedListSequence();
    Test_of_Prepend_LinkedListSequence();
    Test_of_InsertAt_LinkedListSequence();
    Test_of_ConcatLinkedListSequence();

    Test_of_ShrdPtrCreation();
    Test_of_ShrdPtrCopy();
    Test_of_ShrdPtrAssignment();
    Test_of_ShrdPtrNullAssignment();
    Test_of_ShrdPtrReset();
    Test_of_ShrdPtrRefCount();

    Test_of_UnqPtr_Creation();
    Test_of_UnqPtr_Nullptr();
    Test_of_UnqPtr_Reset();
    Test_of_UnqPtr_Release();
    Test_of_UnqPtr_MoveAssignment();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    try
    {
        RunTests();
    }
    catch (const std::out_of_range& e)
    {
        MessageBox(NULL, L"Something wrong with tests", L"Test Notification", MB_OK);
        PostQuitMessage(0);
    }

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1000, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) {
        return FALSE;
    }


    CreateWindowEx(0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        20, 20, 300, 25, hWnd, (HMENU)IDC_MAIN_EDIT, hInstance, nullptr);

    CreateWindowEx(0, L"BUTTON", L"Create a sequence",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        330, 20, 300, 25, hWnd, (HMENU)IDC_MAIN_BUTTON, hInstance, nullptr);

    CreateWindowEx(0, L"STATIC", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        200, 70, 360, 25, hWnd, (HMENU)IDC_DISPLAY_SEQUENCE, hInstance, nullptr);

    CreateWindowEx(0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        20, 150, 75, 25, hWnd, (HMENU)IDC_INPUT_VALUE_EDIT, hInstance, nullptr);

    CreateWindowEx(0, L"BUTTON", L"Add to end",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        130, 110, 160, 25, hWnd, (HMENU)IDC_APPEND_BUTTON, hInstance, nullptr);

    CreateWindowEx(0, L"BUTTON", L"Add to start",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        130, 150, 160, 25, hWnd, (HMENU)IDC_PREPEND_BUTTON, hInstance, nullptr);

    CreateWindowEx(0, L"EDIT", L"", 
        WS_CHILD | WS_VISIBLE | WS_BORDER, 
        20, 215, 75, 25, hWnd, (HMENU)IDC_INDEX_EDIT, hInstance, nullptr);

    CreateWindowEx(0, L"BUTTON", L"Insert at", 
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
        130, 190, 160, 25, hWnd, (HMENU)IDC_INSERT_BUTTON, hInstance, nullptr);

    CreateWindowEx(0, L"BUTTON", L"Get an item by index",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        130, 240, 220, 25, hWnd, (HMENU)IDC_GET_BUTTON, hInstance, nullptr);

    CreateWindowEx(0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        20, 290, 75, 25, hWnd, (HMENU)IDC_START_INDEX_EDIT, hInstance, nullptr);

    CreateWindowEx(0, L"EDIT", L"", 
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        110, 290, 75, 25, hWnd, (HMENU)IDC_END_INDEX_EDIT, hInstance, nullptr);

    CreateWindowEx(0, L"BUTTON", L"Get a subsequence",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        200, 290, 300, 25, hWnd, (HMENU)IDC_GET_SUBSEQUENCE_BUTTON, hInstance, nullptr);

    CreateWindowEx(0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        20, 340, 300, 25, hWnd, (HMENU)IDC_SECOND_SEQUENCE_EDIT, hInstance, nullptr);

    CreateWindowEx(0, L"BUTTON", L"Create second sequence",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        330, 340, 300, 25, hWnd, (HMENU)IDC_CREATE_SECOND_SEQUENCE_BUTTON, hInstance, nullptr);

    CreateWindowEx(0, L"BUTTON", L"Concatenation",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 380, 250, 25, hWnd, (HMENU)IDC_CONCAT_BUTTON, hInstance, nullptr);

    CreateWindow(L"STATIC", L"Elem:", WS_VISIBLE | WS_CHILD,
        20, 130, 50, 20, hWnd, NULL, hInst, NULL);

    CreateWindow(L"STATIC", L"Index:", WS_VISIBLE | WS_CHILD,
        20, 195, 50, 20, hWnd, NULL, hInst, NULL);

    CreateWindow(L"STATIC", L"Start:", WS_VISIBLE | WS_CHILD,
        20, 270, 50, 20, hWnd, NULL, hInst, NULL);

    CreateWindow(L"STATIC", L"End:", WS_VISIBLE | WS_CHILD,
        110, 270, 50, 20, hWnd, NULL, hInst, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static WCHAR inputText[256], indexText[256], startIndexText[256], endIndexText[256], secondInputText[256];
    static UnqPtr<LinkedListSequence<int>> otherSequence;

    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);

        if (wmId == IDC_MAIN_BUTTON) {
            HWND hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
            GetWindowText(hEdit, inputText, 256);

            auto values = ParseInput(inputText);
            if (values.empty()) {
                MessageBox(hWnd, L"Enter a sequence", L"Error", MB_OK);
                return 0;
            }

            sequence.reset(new LinkedListSequence<int>());
            for (const int& value : values) {
                sequence->Append(value);
            }

            MessageBox(hWnd, L"The sequence has been created", L"", MB_OK);
            DisplaySequence(hWnd);
        }

        else if (wmId == IDC_APPEND_BUTTON) {
            GetWindowText(GetDlgItem(hWnd, IDC_INPUT_VALUE_EDIT), inputText, 256);
            int value = _wtoi(inputText);

            if (sequence) {
                sequence->Append(value);
                DisplaySequence(hWnd);
            }
            else {
                MessageBox(hWnd, L"First, create a sequence", L"Error", MB_OK);
            }
        }

        else if (wmId == IDC_PREPEND_BUTTON) {
            GetWindowText(GetDlgItem(hWnd, IDC_INPUT_VALUE_EDIT), inputText, 256);
            int value = _wtoi(inputText);

            if (sequence) {
                sequence->Prepend(value);
                DisplaySequence(hWnd);
            }
            else {
                MessageBox(hWnd, L"First, create a sequence", L"Error", MB_OK);
            }
        }

        else if (wmId == IDC_INSERT_BUTTON) {
            GetWindowText(GetDlgItem(hWnd, IDC_INDEX_EDIT), indexText, 256);
            GetWindowText(GetDlgItem(hWnd, IDC_INPUT_VALUE_EDIT), inputText, 256);
            int index = _wtoi(indexText);
            int value = _wtoi(inputText);
            try
            {
                if (sequence) {
                    sequence->InsertAt(value, index);
                    DisplaySequence(hWnd);
                }
                else {
                    MessageBox(hWnd, L"First, create a sequence", L"Error", MB_OK);
                }
            }
            catch (const char* error_message)
            {
                MessageBoxA(NULL, error_message, "Error", MB_OK | MB_ICONERROR);
            }
        }

        else if (wmId == IDC_GET_BUTTON) { 
            try {
                GetWindowText(GetDlgItem(hWnd, IDC_INDEX_EDIT), indexText, 256);
                int index = _wtoi(indexText);

                if (sequence) {
                    int value = sequence->Get(index);
                    wchar_t output[256];
                    swprintf_s(output, L"The element on the index %d: %d", index, value);
                    MessageBox(hWnd, output, L"Result of Get", MB_OK);
                }
                else {
                    MessageBox(hWnd, L"First, create a sequence", L"Error", MB_OK);
                }
            }
            catch (const char* error_message) {
                MessageBoxA(NULL, error_message, "Error", MB_OK | MB_ICONERROR);
            }
        }

        else if (wmId == IDC_GET_SUBSEQUENCE_BUTTON) {
            try {
                GetWindowText(GetDlgItem(hWnd, IDC_START_INDEX_EDIT), startIndexText, 256);
                GetWindowText(GetDlgItem(hWnd, IDC_END_INDEX_EDIT), endIndexText, 256);
                int startIndex = _wtoi(startIndexText);
                int endIndex = _wtoi(endIndexText);

                if (sequence) {
                    auto subSeq = sequence->GetSubsequence(startIndex, endIndex);
                    DisplaySubSequence(hWnd, subSeq.get());
                }
                else {
                    MessageBox(hWnd, L"First, create a sequence", L"Error", MB_OK);
                }
            }
            catch (const char* error_message) {
                MessageBoxA(NULL, error_message, "Error", MB_OK | MB_ICONERROR);
            }
        }

        else if (wmId == IDC_CREATE_SECOND_SEQUENCE_BUTTON) {
            HWND hEdit = GetDlgItem(hWnd, IDC_SECOND_SEQUENCE_EDIT);
            GetWindowText(hEdit, secondInputText, 256);

            auto values = ParseInput(secondInputText);
            if (values.empty()) {
                MessageBox(hWnd, L"Enter the second sequence ", L"Error", MB_OK);
                return 0;
            }

            otherSequence.reset(new LinkedListSequence<int>());
            for (const int& value : values) {
                otherSequence->Append(value);
            }

            MessageBox(hWnd, L"The second sequence is created", L"", MB_OK);
        }

        else if (wmId == IDC_CONCAT_BUTTON) {
                if (sequence && otherSequence) {
                    try {
                        auto concatenatedSequence = sequence->Concat(otherSequence.get());
                        DisplaySubSequence(hWnd, concatenatedSequence.get());
                    }
                    catch (const char* error_message) {
                        MessageBoxA(NULL, error_message, "Concatenation error", MB_OK | MB_ICONERROR);
                    }
                }
                else {
                    MessageBox(hWnd, L"Create both sequences", L"Error", MB_OK);
                }
        }
        break;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
    }
                 break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
