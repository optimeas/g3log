#pragma once

#include "logmessage.hpp"
#include <fstream>

namespace g3 {

class RotatingFileSink
{
public:
    RotatingFileSink();
    void writeMessage(LogMessageMover message);

    void openFirstFile(void);
    void switchToNextFile(void);

    const std::string& generateFilename(void);


    const std::string& path() const;
    void setPath(const std::string &path);

    const std::string& filenamePrefix() const;
    void setFilenamePrefix(const std::string &filenamePrefix);

    const uint8_t& maxFileCount() const;
    void setMaxFileCount(const uint8_t &maxFileCount);

    const uint32_t& maxFileSize() const;
    void setMaxFileSize(const uint32_t &maxFileSize);

    bool mirrorToConsole() const;
    void setMirrorToConsole(bool mirrorToConsole);

    bool showThreadId() const;
    void setShowThreadId(bool showThreadId);

private:
    std::string   m_path            = "";
    std::string   m_filenamePrefix  = "app_name";
    uint8_t       m_maxFileCount    = 10;
    uint32_t      m_maxFileSize     = 512000;
    std::fstream  m_file;
    int           m_fileIndex       = -1;
    std::string   m_filename        = "";
    bool          m_mirrorToConsole = false;
    bool          m_showThreadId    = false;

};

} // g3
