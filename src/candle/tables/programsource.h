// This file is a part of "Candle" application.
// Copyright 2015-2026 Hayrullin Denis Ravilevich

#ifndef PROGRAMSOURCE_H
#define PROGRAMSOURCE_H

#include <QByteArray>
#include <QString>
#include <QVector>

#include "utils/filemap.h"

class QTextCodec;

/**
 * Backing store for lazily loaded G-code programs: the program text stays in
 * the (memory-mapped) source file and single lines are materialized on demand.
 *
 * The codec is pinned at open() time to the same one QTextStream would have
 * used while reading the file, so line text decoded here is byte-identical to
 * what an eager readLine()-based load would have produced.
 */
class ProgramSource
{
public:
    ProgramSource();
    ~ProgramSource();

    ProgramSource(const ProgramSource &) = delete;
    ProgramSource &operator=(const ProgramSource &) = delete;

    bool open(const QString &fileName, QString *error = nullptr);
    void close();

    bool isOpen() const { return m_map.isOpen(); }
    qint64 size() const { return m_map.size(); }
    QTextCodec *codec() const { return m_codec; }

    // Non-owning view of raw line bytes; valid while the source stays open.
    QByteArray rawLine(int offset, int length) const;

    // Line text decoded with the load-time codec, terminated like
    // QTextStream::readLine() (line feed removed, carriage return kept).
    QString lineText(int offset, int length) const;

    /**
     * Byte-scan the file recording start offset and length of every line
     * ('\n' terminated; the terminator is not part of the recorded length).
     * Refuses files that cannot back a lazy load (empty, UTF-16, size beyond
     * addressable int range).
     */
    static bool scanLines(const QString &fileName, QVector<int> &offsets, QVector<int> &lengths, QString *error = nullptr);

private:
    FileMap m_map;
    QTextCodec *m_codec;
    int m_startOffset; // First line offset after a skipped BOM.
};

#endif // PROGRAMSOURCE_H
