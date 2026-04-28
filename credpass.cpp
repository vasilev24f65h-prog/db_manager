#include <windows.h>
#include <wincred.h>
#include <string>
bool writeCredential(const std::wstring& target, const std::wstring& password)
{
    CREDENTIALW cred{};
    cred.Type = CRED_TYPE_GENERIC;
    cred.TargetName = (LPWSTR)target.c_str();

    cred.CredentialBlobSize = password.size() * sizeof(wchar_t);
    cred.CredentialBlob = (LPBYTE)password.c_str();

    cred.Persist = CRED_PERSIST_LOCAL_MACHINE;

    return CredWriteW(&cred, 0);
}
bool readCredential(const std::wstring& target, std::wstring& password)
{
    PCREDENTIALW pcred;

    if (CredReadW(target.c_str(), CRED_TYPE_GENERIC, 0, &pcred))
    {
        password.assign((wchar_t*)pcred->CredentialBlob,
                        pcred->CredentialBlobSize / sizeof(wchar_t));

        CredFree(pcred);
        return true;
    }
    return false;
}
bool deleteCredential(const std::wstring& target)
{
    return CredDeleteW(target.c_str(), CRED_TYPE_GENERIC, 0);
}
