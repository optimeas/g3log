#include "g3log/log.hpp"
#include "g3log/g3log.hpp"
#include "g3log/logworker.hpp"
#include "g3log/rotatingfilesink.hpp"

#include <QString>

namespace g3
{

std::string copyStringIfNotNullPtr(const char * data)
{
    if(data == nullptr)
        return "nullptr";

    return std::string(data);
}

void myQtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString& txt)
{
    std::string message  = txt.toStdString();
    std::string fileName = copyStringIfNotNullPtr(context.file);
    std::string function = copyStringIfNotNullPtr(context.function);
    std::string category = copyStringIfNotNullPtr(context.category);

    if((!category.empty() && (category != "default")))
        message = category + ": " + message;

    switch (type) {
    case QtDebugMsg:
        LogCapture(fileName.data(), context.line, function.data(), G3LOG_DEBUG).stream() << message;
        break;
    case QtInfoMsg:
        LogCapture(fileName.data(), context.line, function.data(), INFO).stream() << message;
        break;
    case QtWarningMsg:
        LogCapture(fileName.data(), context.line, function.data(), WARNING).stream() << message;
        break;
    case QtCriticalMsg:
    case QtFatalMsg:
        LogCapture(fileName.data(), context.line, function.data(), ERR).stream() << message;
        break;

    default:
        LogCapture(fileName.data(), context.line, function.data(), ERR).stream() << message;
        break;
    }
}

void initializeLoggingFramework(const std::string &filenamePrefix, const std::string &path, const bool logToConsole)
{
    static std::unique_ptr<g3::LogWorker> logger = g3::LogWorker::createLogWorker();

    auto sinkHandle = logger->addSink(std::make_unique<g3::RotatingFileSink>(), &g3::RotatingFileSink::writeMessage);
    sinkHandle->call(&g3::RotatingFileSink::setPath,            path);
    sinkHandle->call(&g3::RotatingFileSink::setFilenamePrefix,  filenamePrefix);

    if(logToConsole)
        sinkHandle->call(&g3::RotatingFileSink::setMirrorToConsole, true);

    initializeLogging(logger.get());

    qInstallMessageHandler(myQtMessageHandler);
}

}
