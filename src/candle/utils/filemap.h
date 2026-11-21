// This file is a part of "Candle" application.
// Copyright 2015-2026 Hayrullin Denis Ravilevich

#ifndef FILEMAP_H
#define FILEMAP_H

#include <QString>
#include <QByteArray>

/**
 * Read-only memory mapping of a file. Pages are supplied by the OS and can
 * be evicted under memory pressure, so mapped contents do not count against
 * the process private working set the way a materialized copy would.
 */
class FileMap
{
public:
    FileMap();
    ~FileMap();

    FileMap(const FileMap &) = delete;
    FileMap &operator=(const FileMap &) = delete;

    bool open(const QString &fileName);
    void close();

    bool isOpen() const { return m_address != nullptr; }
    const char *data() const { return static_cast<const char *>(m_address); }
    qint64 size() const { return m_size; }
    QString errorString() const { return m_error; }

private:
    void *m_address;
    void *m_fileHandle;
    void *m_mapHandle;
    qint64 m_size;
    QString m_error;
};

#endif // FILEMAP_H
