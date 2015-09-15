/*
 * picologger
 * Copyright (C) 2015 Giemsa/MithrilWorks <mithrilworks@gmail.com>
 *
 * this software is distributed under the zlib/libpng license.
 */

#ifndef MW_PICOLOGGER_H
#define MW_PICOLOGGER_H

#include <vector>
#include <sstream>
#include <cstdarg>
#ifdef _MSC_VER
#   include <Windows.h>
#else
#   include <sys/time.h>
#endif

namespace picologger
{
    namespace LogLevel
    {
        enum Type
        {
            Fatal,
            Error,
            Warn,
            Info,
            Debug,
            Trace
        };
    }

    class Writer
    {
    public:
        virtual ~Writer() { }
        virtual void write(const std::string &text) = 0;
    };

    class Formatter
    {
    public:
        static std::string getName(const LogLevel::Type level)
        {
            switch(level)
            {
                case LogLevel::Fatal: return "Fatal";
                case LogLevel::Error: return "Error";
                case LogLevel::Warn:  return "Warn";
                case LogLevel::Info:  return "Info";
                case LogLevel::Debug: return "Debug";
                case LogLevel::Trace: return "Trace";
            }

            return "Unknown";
        }

        virtual ~Formatter() { }
        virtual void format(std::ostream &os, const LogLevel::Type level, const std::string &str) = 0;
    };

    // defaults
    namespace writers
    {
        class DefaultWriter : public picologger::Writer
        {
        private:
            std::ostream &os_;
        public:
            DefaultWriter(std::ostream &os)
            : os_(os)
            { }
            virtual ~DefaultWriter() { }

            virtual void write(const std::string &text) { os_ << text << "\n"; }
        };
    }

    namespace formetters
    {
        struct DefaultFormatter : public picologger::Formatter
        {
            virtual ~DefaultFormatter() { }
            virtual void format(std::ostream &os, const LogLevel::Type level, const std::string &str)
            {
                static const char *format = "%02d:%02d:%02d.%03d [%-5s] %s";

                const std::size_t len = snprintf(NULL, 0, format, 0, 0, 0, 0, "", str.c_str()) + 1;
                char *buf = static_cast<char *>(alloca(len * sizeof(char)));
#ifdef _MSC_VER
                SYSTEMTIME t;
                GetLocalTime(&t);
                snprintf(buf, len, format, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, getName(level).c_str(), str.c_str());
#else
                timeval t;
                gettimeofday(&t, NULL);
                tm *lt = localtime(&t.tv_sec);
                snprintf(buf, len, format, lt->tm_hour, lt->tm_min, lt->tm_sec, t.tv_usec / 1000, getName(level).c_str(), str.c_str());
#endif
                os << buf;
            }
        };
    }

    class Logger
    {
        typedef std::vector<Writer *> WriterList;
    private:
        WriterList writerList_;
        Formatter *formatter_;
        bool enabled_;
        LogLevel::Type logLevel_;

        void clearWriters()
        {
            for(WriterList::const_iterator it = writerList_.begin(); it != writerList_.end(); ++it)
            {
                delete *it;
            }
        }

        void output(const LogLevel::Type level, const char *format, va_list args)
        {
            if(!enabled_ || static_cast<int>(level) > static_cast<int>(logLevel_))
            {
                return;
            }

            std::va_list tmp;
            va_copy(tmp, args);
            const std::size_t len = vsnprintf(NULL, 0, format, tmp) + 1;
            va_end(tmp);

            char *buf = static_cast<char *>(alloca(len * sizeof(char)));
            vsnprintf(buf, len, format, args);

            if(!formatter_)
            {
                formatter_ = new formetters::DefaultFormatter();
            }

            std::ostringstream oss;
            formatter_->format(oss, level, buf);
            const std::string &str = oss.str();
            for(WriterList::iterator it = writerList_.begin(); it != writerList_.end(); ++it)
            {
                (*it)->write(str);
            }
        }

        Logger(const Logger &);
        Logger &operator=(const Logger &);
    public:
        Logger()
        : formatter_(NULL), enabled_(true), logLevel_(LogLevel::Info)
        { }

        Logger(const LogLevel::Type level)
        : formatter_(NULL), enabled_(true), logLevel_(level)
        { }

        Logger(Formatter *formatter, Writer *writer)
        : formatter_(formatter), enabled_(true), logLevel_(LogLevel::Info)
        {
            writerList_.push_back(writer);
        }

        Logger(const LogLevel::Type level, Formatter *formatter, Writer *writer)
        : formatter_(formatter), enabled_(true), logLevel_(level)
        {
            writerList_.push_back(writer);
        }

        virtual ~Logger()
        {
            clearWriters();
            delete formatter_;
        }

        Logger &addWriter(Writer *writer)
        {
            writerList_.push_back(writer);
            return *this;
        }

        Logger &setFormatter(Formatter *formatter)
        {
            if(formatter_)
            {
                delete formatter_;
            }

            formatter_ = formatter;
            return *this;
        }

        Logger &setLogLevel(const LogLevel::Type level)
        {
            logLevel_ = level;
            return *this;
        }

#define MW_PICOLOGGER_OUTPUT_(level) \
    std::va_list args;          \
    va_start(args, format);     \
    output(level, format, args);   \
    va_end(args);
        void log(const LogLevel::Type level, const char *format, ...) { MW_PICOLOGGER_OUTPUT_(level) }
        void fatal(const char *format, ...) { MW_PICOLOGGER_OUTPUT_(LogLevel::Fatal) }
        void error(const char *format, ...) { MW_PICOLOGGER_OUTPUT_(LogLevel::Error) }
        void warn(const char *format, ...) { MW_PICOLOGGER_OUTPUT_(LogLevel::Warn) }
        void info(const char *format, ...) { MW_PICOLOGGER_OUTPUT_(LogLevel::Info) }
        void debug(const char *format, ...) { MW_PICOLOGGER_OUTPUT_(LogLevel::Debug) }
        void trace(const char *format, ...) { MW_PICOLOGGER_OUTPUT_(LogLevel::Trace) }
#undef MW_PICOLOGGER_OUTPUT_

        void setEnabled(const bool enabled) { enabled_ = enabled; }
    };
}

#endif
