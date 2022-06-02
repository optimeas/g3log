#include "g3log/rotatingfilesink.hpp"

#include <iostream>
#include <iomanip>
#include <cstdio>

namespace g3 {

RotatingFileSink::RotatingFileSink()
{
}

void RotatingFileSink::writeMessage(g3::LogMessageMover message)
{
    using namespace std;
    LogMessage &msg = message.get();

    if(!m_file.is_open())
        openFirstFile();

    stringstream ss(msg.file()); // "main.cpp" => "main"
    string cppfile;
    getline(ss, cppfile, '.');
    cppfile += ":" + msg.line();

    stringstream line;
    line << left     << msg.timestamp("%d.%m.%y|%H:%M:%S.%f3") << "|";

    if(m_showThreadId)
        line << right    << setw(8) << setfill('0') << msg.threadID()                              << "|";

    line << left     << setw(30) << setfill(' ') << cppfile                                        << "|"
         << setw(7)  << msg.level()                                                                << "|"
         <<             msg.message();

    m_file << line.str() << endl;

    if(m_mirrorToConsole)
        cout << line.str() << endl;

    if(m_file.tellg() >= m_maxFileSize)
        switchToNextFile();
}

void RotatingFileSink::openFirstFile()
{
    for(int i=0; i<m_maxFileCount; ++i)
    {
        m_fileIndex = i;

        m_file.open(generateFilename(), std::fstream::out | std::fstream::app);

        if(m_file.tellg() < m_maxFileSize)
            return; // first not complete filled file found

        m_file.close();
    }

    // when all files are filled we start at index 0
    m_fileIndex = 0;
    ::remove(generateFilename().c_str());
    m_file.open(m_filename, std::fstream::out | std::fstream::app);
}

void RotatingFileSink::switchToNextFile()
{
    m_file.close();

    m_fileIndex++;
    if(m_fileIndex >= m_maxFileCount)
        m_fileIndex = 0;

    ::remove(generateFilename().c_str());
    m_file.open(m_filename, std::fstream::out | std::fstream::app);
}

const std::string &RotatingFileSink::generateFilename()
{
    m_filename = m_path + m_filenamePrefix + "_" + std::to_string(m_fileIndex) + ".log";
    return m_filename;
}

const std::string& RotatingFileSink::path() const
{
    return m_path;
}

void RotatingFileSink::setPath(const std::string &path)
{
    m_path = path;
}

const std::string& RotatingFileSink::filenamePrefix() const
{
    return m_filenamePrefix;
}

void RotatingFileSink::setFilenamePrefix(const std::string &filenamePrefix)
{
    m_filenamePrefix = filenamePrefix;
}

const uint8_t& RotatingFileSink::maxFileCount() const
{
    return m_maxFileCount;
}

void RotatingFileSink::setMaxFileCount(const uint8_t &maxFileCount)
{
    m_maxFileCount = maxFileCount;
}

const uint32_t& RotatingFileSink::maxFileSize() const
{
    return m_maxFileSize;
}

void RotatingFileSink::setMaxFileSize(const uint32_t &maxFileSize)
{
    m_maxFileSize = maxFileSize;
}
bool RotatingFileSink::mirrorToConsole() const
{
    return m_mirrorToConsole;
}

void RotatingFileSink::setMirrorToConsole(bool mirrorToConsole)
{
    m_mirrorToConsole = mirrorToConsole;
}
bool RotatingFileSink::showThreadId() const
{
    return m_showThreadId;
}

void RotatingFileSink::setShowThreadId(bool showThreadId)
{
    m_showThreadId = showThreadId;
}



} // g3
