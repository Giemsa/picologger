/*
 * picologger
 * Copyright (C) 2015 Giemsa/MithrilWorks <mithrilworks@gmail.com>
 *
 * this software is distributed under the zlib/libpng license.
 */

package jp.mithrilworks.picologger.formatters;

import java.text.SimpleDateFormat;
import java.util.Date;

import jp.mithrilworks.picologger.Formatter;
import jp.mithrilworks.picologger.LogLevel;

public class DefaultFormatter extends Formatter {
    private static SimpleDateFormat formatter_ = new SimpleDateFormat("HH:mm:ss.SSS");

    @Override
    public String format(LogLevel level, String str) {
        return String.format("%s [%-5s] %s", formatter_.format(new Date()), getName(level), str);
    }
}
