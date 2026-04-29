#ifndef CREDPASS_H
#define CREDPASS_H

#include <string>
bool writeCredential(const std::wstring& target,
                     const std::wstring& password);
bool deleteCredential(const std::wstring& target);
bool readCredential(const std::wstring& target, std::wstring& password);

#endif // CREDPASS_H
