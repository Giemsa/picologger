/*
 * picologger
 * Copyright (C) 2015 Giemsa/MithrilWorks <mithrilworks@gmail.com>
 *
 * this software is distributed under the zlib/libpng license.
 */

package jp.mithrilworks.picologger;

import java.util.List;
import java.util.ArrayList;

import jp.mithrilworks.picologger.Formatter;
import jp.mithrilworks.picologger.Writer;
import jp.mithrilworks.picologger.LogLevel;

public class Logger {
    private Formatter formatter_ = null;
    private List<Writer> writerList_ = new ArrayList<Writer>();
    private LogLevel logLevel_ = LogLevel.Info;
    private boolean enabled_ = true;

    public Logger() { }

    public Logger(LogLevel level) {
        logLevel_ = level;
    }

    public Logger(Formatter formatter, Writer writer) {
        formatter_ = formatter;
        writerList_.add(writer);
    }

    public Logger(LogLevel level, Formatter formatter, Writer writer) {
        logLevel_ = level;
        formatter_ = formatter;
        writerList_.add(writer);
    }

    public Logger addWriter(Writer writer) {
        writerList_.add(writer);
        return this;
    }

    public Logger setFormatter(Formatter formatter) {
        formatter_ = formatter;
        return this;
    }

    public Logger setEnabled(boolean enabled) {
        enabled_ = enabled;
        return this;
    }

    public Logger setLogLevel(LogLevel level) {
        logLevel_ = level;
        return this;
    }

    protected void output(LogLevel level, String format, Object... args) {
        if(formatter_ == null || !enabled_ || level.getLevel() > logLevel_.getLevel()) {
            return;
        }

        String str = formatter_.format(level, String.format(format, args));
        for(Writer writer : writerList_) {
            writer.write(str);
        }
    }

    public void log(LogLevel level, String format, Object... args) {
        output(level, format, args);
    }

    public void fatal(String format, Object... args) {
        output(LogLevel.Fatal, format, args);
    }

    public void error(String format, Object... args) {
        output(LogLevel.Error, format, args);
    }

    public void warn(String format, Object... args) {
        output(LogLevel.Warn, format, args);
    }

    public void info(String format, Object... args) {
        output(LogLevel.Info, format, args);
    }

    public void debug(String format, Object... args) {
        output(LogLevel.Debug, format, args);
    }

    public void trace(String format, Object... args) {
        output(LogLevel.Trace, format, args);
    }
}
