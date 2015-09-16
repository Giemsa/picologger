/*
 * picologger
 * Copyright (C) 2015 Giemsa/MithrilWorks <mithrilworks@gmail.com>
 *
 * this software is distributed under the zlib/libpng license.
 */

package jp.mithrilworks.picologger;

public enum LogLevel {
    Fatal(0),
    Error(1),
    Warn(2),
    Info(3),
    Debug(4),
    Trace(5);

    private int value_;

    private LogLevel(int v) {
        value_ = v;
    }

    public int getLevel() {
        return value_;
    }
}
