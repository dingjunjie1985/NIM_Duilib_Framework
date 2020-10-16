// chart.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "main.h"
#include "main_form.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
#ifdef _DEBUG
	AllocConsole();
	FILE* fp = NULL;
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
	wprintf_s(L"Command:\n%s\n\n", L"");
#endif
	MainThread().RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

	return 0;
}

void MiscThread::Init()
{
	nbase::ThreadManager::RegisterThread(thread_id_);
}

void MiscThread::Cleanup()
{
	nbase::ThreadManager::UnregisterThread();
}

void MainThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadUI);

	// �������´����߳�
	misc_thread_.reset(new MiscThread(kThreadGlobalMisc, "Global Misc Thread"));
	misc_thread_->Start();

	// ��ȡ��Դ·������ʼ��ȫ�ֲ���
	std::wstring app_dir = nbase::win32::GetCurrentModuleDirectory();
	ui::GlobalManager::Startup(app_dir + L"resources\\", ui::CreateControlCallback(), false);

	// ����һ��Ĭ�ϴ�����Ӱ�ľ��д���
	MainForm* window = new MainForm();
	window->Create(NULL, MainForm::kClassName.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowWindow();
}

void MainThread::Cleanup()
{
	ui::GlobalManager::Shutdown();

	misc_thread_->Stop();
	misc_thread_.reset(nullptr);

	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}
