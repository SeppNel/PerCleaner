#include "Folder.h"

std::string Folder::getPath() {
	return path_;
}

bool Folder::isLog() {
	return is_log_;
}

bool Folder::isFromUser() {
	return is_from_user_;
}

static Folder::getUserPath() {
    PWSTR userFolderPath;
    HRESULT result = SHGetKnownFolderPath(FOLDERID_Profile, 0, NULL, &userFolderPath);

    if (result == S_OK)
    {
        CString str1(userFolderPath);
        const wchar_t* str2 = str1;
        std::wstring str3(str2);
        wprintf(str3.c_str());
    }
    else
    {
        wprintf(L"Error\n");
    }

    CoTaskMemFree(static_cast<LPVOID>(userFolderPath));
}