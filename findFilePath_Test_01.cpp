#include <shlobj.h>
#include <tchar.h>

void PrintTCHAR(const _TCHAR* strToPrint) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// 写入控制台，自动选择正确的函数版本
	WriteConsole(hOut, strToPrint, _tcslen(strToPrint), NULL, NULL);
}

int main()
{
	SetConsoleOutputCP(65001);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);

	TCHAR szPath[MAX_PATH];
	TCHAR buffer[512];
	// 這裏已分配好一個TCHAR array的空間, 大小為MAX_PATH, 即260個bytes
	// 分配好空間, 在function SHGetFolderPath中以pointer寫入路徑
	HRESULT result = SHGetFolderPath
	(
		NULL, //HWND hwndOwner 
		// 窗口句柄, 通常為NULL
		CSIDL_MYMUSIC, //int nFolder
		// CSIDL_DESKTOP 桌面 //CSIDL_MYMUSIC 音樂 //CSIDL_MYPICTURES 圖片 //CSIDL_MYVIDEO 影片 //CSIDL_PERSONAL 文件 //CSIDL_WINDOWS Windows目錄
		NULL, //HANDLE hToken 
		// 訪問令牌, 可以指定用戶環境 通常設為 NULL, 表示使用當前用戶
		SHGFP_TYPE_CURRENT, //DWORD dwFlags
		// 控制選項, 例如 SHGFP_TYPE_CURRENT 返回當前用戶自定義的路徑, SHGFP_TYPE_DEFAULT 返回默認路徑
		szPath //LPTSTR pszPath
		// 指向接收路徑的緩衝區的指標, 該緩衝區應至少為 MAX_PATH 字符長
	);
	if (S_OK == result)
	{
		_stprintf(buffer, _T("我的文件夾: %s\n"), szPath);
		PrintTCHAR(buffer);
		//成功則輸出string路徑
	}
	else
	{
		_stprintf(buffer, _T("無法取得我的文件夾路徑, 錯誤碼: %ld\n"), result);
		PrintTCHAR(buffer);
		//不成功則輸出long int錯誤碼
	}
	return 0;
}
