/*
 * picologger
 * Copyright (C) 2015 Giemsa/MithrilWorks <mithrilworks@gmail.com>
 *
 * this software is distributed under the zlib/libpng license.
 */

package jp.mithrilworks.picologger;

import jp.mithrilworks.picologger.LogLevel;

public abstract class Formatter {
    public abstract String format(LogLevel level, String str);

    public static String getName(LogLevel level) {
        switch(level)
        {
            case Fatal: return "Fatal";
            case Error: return "Error";
            case Warn:  return "Warn";
            case Info:  return "Info";
            case Debug: return "Debug";
            case Trace: return "Trace";
        }

        return "Unknown";
    }
}
