// This file is a part of "Candle" application.
// Copyright 2015-2026 Hayrullin Denis Ravilevich

#include "tables/programsource.h"

#include <QTextCodec>
#include <climits>

namespace {

// Number of BOM bytes at the head of the buffer and the codec they imply.
// Returns 0 (and an unchanged codec) when no BOM is present.
int bomLength(const char *data, int size, const char **codecName)
{
    if (size >= 3 &&
            static_cast<unsigned char>(data[0]) == 0xEF &&
            static_cast<unsigned char>(data[1]) == 0xBB &&
            static_cast<unsigned char>(data[2]) == 0xBF) {
        *codecName = "UTF-8";
        return 3;
    }

    return 0;
}

}

ProgramSource::ProgramSource() :
    m_codec(nullptr),
    m_startOffset(0)
{
}

ProgramSource::~ProgramSource()
{
}

bool ProgramSource::open(const QString &fileName, QString *error)
{
    close();

    if (!m_map.open(fileName)) {
        if (error) *error = m_map.errorString();
        return false;
    }

    const char *codecName = nullptr;
    m_startOffset = bomLength(m_map.data(), static_cast<int>(qMin<qint64>(m_map.size(), 3)), &codecName);

    // UTF-16 sources have a multi-byte line structure that the byte-scan
    // line index cannot represent; refuse so the caller can fall back.
    unsigned char b0 = static_cast<unsigned char>(m_map.data()[0]);
    unsigned char b1 = m_map.size() > 1 ? static_cast<unsigned char>(m_map.data()[1]) : 0;

    if ((b0 == 0xFF && b1 == 0xFE) || (b0 == 0xFE && b1 == 0xFF)) {
        if (error) *error = QStringLiteral("UTF-16 source not supported for lazy load");
        close();
        return false;
    }

    if (codecName) {
        m_codec = QTextCodec::codecForName(codecName);
    }

    if (!m_codec) m_codec = QTextCodec::codecForLocale();

    return true;
}

void ProgramSource::close()
{
    m_map.close();
    m_codec = nullptr;
    m_startOffset = 0;
}

QByteArray ProgramSource::rawLine(int offset, int length) const
{
    return QByteArray::fromRawData(m_map.data() + offset, length);
}

QString ProgramSource::lineText(int offset, int length) const
{
    // Match QTextStream::readLine(): drop a trailing carriage return.
    while (length > 0 && m_map.data()[offset + length - 1] == '\r')
        length--;

    return m_codec->toUnicode(m_map.data() + offset, length);
}

bool ProgramSource::scanLines(const QString &fileName, QVector<int> &offsets, QVector<int> &lengths, QString *error)
{
    offsets.clear();
    lengths.clear();

    FileMap map;

    if (!map.open(fileName)) {
        if (error) *error = map.errorString();
        return false;
    }

    if (map.size() > INT_MAX) {
        if (error) *error = QStringLiteral("file too large for lazy load");
        return false;
    }

    const char *data = map.data();
    int size = static_cast<int>(map.size());

    const char *codecName = nullptr;
    int offset = bomLength(data, qMin(size, 3), &codecName);

    if (offset == 0 && size >= 2) {
        unsigned char b0 = static_cast<unsigned char>(data[0]);
        unsigned char b1 = static_cast<unsigned char>(data[1]);

        if ((b0 == 0xFF && b1 == 0xFE) || (b0 == 0xFE && b1 == 0xFF)) {
            if (error) *error = QStringLiteral("UTF-16 source not supported for lazy load");
            return false;
        }
    }

    offsets.reserve(size / 16 + 16);
    lengths.reserve(size / 16 + 16);

    int lineStart = offset;

    for (int i = offset; i < size; i++) {
        if (data[i] == '\n') {
            offsets.append(lineStart);
            lengths.append(i - lineStart);
            lineStart = i + 1;
        }
    }

    // Final line without a trailing newline.
    if (lineStart < size) {
        offsets.append(lineStart);
        lengths.append(size - lineStart);
    }

    return true;
}
