import jp.mithrilworks.picologger.Logger;
import jp.mithrilworks.picologger.LogLevel;
import jp.mithrilworks.picologger.formatters.DefaultFormatter;
import jp.mithrilworks.picologger.writers.DefaultWriter;

public class Main {
    private static final String TAG = Main.class.getSimpleName();

    // custom formatter
    private static class CustomFormatter extends DefaultFormatter {
        @Override
        public String format(LogLevel level, String str) {
            return TAG + " | " + super.format(level, str);
        }
    }

    private static class Logger extends jp.mithrilworks.picologger.Logger {
        private static class LazyHolder {
            static final Logger INSTANCE = new Logger();
        }

        public static Logger getInstance() {
            return LazyHolder.INSTANCE;
        }

        public Logger() {
            super(
                new CustomFormatter(), // use custom formatter
                new DefaultWriter(System.out)
            );
        }
    }

    public static void main(String args[]) {
        Logger.getInstance().info("info level log");
        Logger.getInstance().warn("warn level log");

        // default log level is "LogLevel::Info", so following message is not logged.
        Logger.getInstance().debug("debug level log 1");

        // switch log level
        Logger.getInstance().setLogLevel(LogLevel.Debug);
        Logger.getInstance().debug("debug level log 2");
    }
}
