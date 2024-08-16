#include <windows.h>
#include <winhttp.h>
#include <iostream>
#include <fstream>

int main() {
    // Download the file
    HINTERNET hSession = WinHttpOpen(L"My Agent/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        std::cerr << "Error opening session" << std::endl;
        return 1;
    }

    // URL to download from (replace with the actual URL if needed)
    const wchar_t* url = L"https://raw.githubusercontent.com/MatixAndr09/Kozlowski/main/main.cpp";

    HINTERNET hConnect = WinHttpConnect(hSession, url, INTERNET_DEFAULT_HTTP_PORT, 0);
    if (!hConnect) {
        std::cerr << "Error connecting" << std::endl;
        WinHttpCloseHandle(hSession);
        return 1;
    }

    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    if (!hRequest) {
        std::cerr << "Error creating request" << std::endl;
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    if (!WinHttpSendRequest(hRequest, WINHTTP_NO_REQUEST_DATA, 0, WINHTTP_NO_ADDITIONAL_HEADERS, 0)) {
        std::cerr << "Error sending request" << std::endl;
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    if (!WinHttpReceiveResponse(hRequest, NULL, NULL)) {
        std::cerr << "Error receiving response" << std::endl;
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Download the file
    std::ofstream outputFile("downloaded_main.cpp", std::ios::binary); // Name it downloaded_main.cpp
    if (!outputFile) {
        std::cerr << "Error opening output file" << std::endl;
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    DWORD dwSize = 0;
    char buffer[1024];
    while (WinHttpReadData(hRequest, buffer, sizeof(buffer), &dwSize) && dwSize > 0) {
        outputFile.write(buffer, dwSize);
    }
    outputFile.close();

    // Compile the downloaded file
    int compileResult = system("g++ downloaded_main.cpp -o Build");

    if (compileResult == 0) {
        std::cout << "Compilation successful!" << std::endl;
        // You can optionally execute the program here using system("./downloaded_program");
    } else {
        std::cerr << "Compilation failed!" << std::endl;
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    return 0;
}