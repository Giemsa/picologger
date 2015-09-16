/*
 * picologger
 * Copyright (C) 2015 Giemsa/MithrilWorks <mithrilworks@gmail.com>
 *
 * this software is distributed under the zlib/libpng license.
 */

package jp.mithrilworks.picologger.writers;

import java.io.OutputStream;
import java.io.PrintStream;
import jp.mithrilworks.picologger.Writer;

public class DefaultWriter extends Writer {
    private PrintStream out_ = null;
    public DefaultWriter(OutputStream out) {
        out_ = new PrintStream(out);
    }

    @Override
    public void write(String text) {
        out_.println(text);
    }
}
