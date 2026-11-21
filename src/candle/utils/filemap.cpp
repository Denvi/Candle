// This file is a part of "Candle" application.
// Copyright 2015-2026 Hayrullin Denis Ravilevich

#include "utils/filemap.h"
#include <QFile>
#ifdef Q_OS_WIN
#include <windows.h>
#else
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#endif

FileMap::FileMap() :
    m_address(nullptr),
    m_fileHandle(nullptr),
    m_mapHandle(nullptr),
    m_size(0)
{
}

FileMap::~FileMap()
{
    close();
}

bool FileMap::open(const QString &fileName)
{
    close();

#ifdef Q_OS_WIN
    HANDLE file = CreateFileW(reinterpret_cast<const wchar_t *>(fileName.utf16()),
        GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (file == INVALID_HANDLE_VALUE) {
        m_error = QStringLiteral("CreateFile failed (%1)").arg(GetLastError());
        return false;
    }

    LARGE_INTEGER size;
    if (!GetFileSizeEx(file, &size)) {
        m_error = QStringLiteral("GetFileSizeEx failed (%1)").arg(GetLastError());
        CloseHandle(file);
        return false;
    }

    if (size.QuadPart == 0) {
        m_error = QStringLiteral("file is empty");
        CloseHandle(file);
        return false;
    }

    HANDLE mapping = CreateFileMappingW(file, nullptr, PAGE_READONLY,
        static_cast<DWORD>(size.QuadPart >> 32), static_cast<DWORD>(size.QuadPart & 0xFFFFFFFF), nullptr);

    if (!mapping) {
        m_error = QStringLiteral("CreateFileMapping failed (%1)").arg(GetLastError());
        CloseHandle(file);
        return false;
    }

    void *address = MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0);

    if (!address) {
        m_error = QStringLiteral("MapViewOfFile failed (%1)").arg(GetLastError());
        CloseHandle(mapping);
        CloseHandle(file);
        return false;
    }

    m_address = address;
    m_fileHandle = file;
    m_mapHandle = mapping;
    m_size = size.QuadPart;
    m_error.clear();
    return true;
#else
    int fd = ::open(QFile::encodeName(fileName).constData(), O_RDONLY);

    if (fd < 0) {
        m_error = QStringLiteral("open failed (%1)").arg(strerror(errno));
        return false;
    }

    struct stat st;

    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode) || st.st_size == 0) {
        m_error = QStringLiteral("fstat failed or not a regular file");
        ::close(fd);
        return false;
    }

    void *address = ::mmap(nullptr, st.st_size, PROT_READ, MAP_FILE | MAP_SHARED, fd, 0);

    if (address == MAP_FAILED) {
        m_error = QStringLiteral("mmap failed (%1)").arg(strerror(errno));
        ::close(fd);
        return false;
    }

    m_address = address;
    m_fileHandle = reinterpret_cast<void *>(static_cast<intptr_t>(fd));
    m_mapHandle = nullptr;
    m_size = st.st_size;
    m_error.clear();
    return true;
#endif
}

void FileMap::close()
{
#ifdef Q_OS_WIN
    if (m_address) UnmapViewOfFile(m_address);
    if (m_mapHandle) CloseHandle(static_cast<HANDLE>(m_mapHandle));
    if (m_fileHandle) CloseHandle(static_cast<HANDLE>(m_fileHandle));
#else
    if (m_address) ::munmap(m_address, m_size);
    if (m_fileHandle) ::close(static_cast<int>(reinterpret_cast<intptr_t>(m_fileHandle)));
#endif

    m_address = nullptr;
    m_fileHandle = nullptr;
    m_mapHandle = nullptr;
    m_size = 0;
}
