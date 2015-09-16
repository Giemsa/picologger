# picologger
picologger is a compact logger library for C++ and Java. 

C++:

    using namespace picologger;
    Logger *logger = new Logger(
        new formatters::DefaultFormatter(),
        new writers::DefaultWriter(std::cout));

    logger->error("error! %d", 0); // 01:59:20.128 [Error] error! 0

Java:

    Logger logger = new Logger(
        new DefaultFormatter(),
        new DefaultWriter(System.out));

    logger.error("error! %d", 0); // 01:59:20.128 [Error] error! 0

See main.cpp if you want more example.

## set log level
You can set log level using `setLogLevel`. The default level is `Info`. The following log levels are defined in `LogLevel` namespace:

- Fatal
- Error
- Warn
- Info
- Debug
- Trace

Logs that have level you specified or over are output.

## formatter and writer
picologger has formatter and writer. Formatter class formats log messages and Writer class output the messages. picologger has default formatter `DefaultFormatter` in `formatters` namespace and default writer `DefaultWriter` in `writers` namespace. These classes provide simple prosesses for formatting and output.
If you want to custom message format or change output, you can use custom formatter and writer. 
You can create custom formatter by inheriting Formatter class and override `format` method. You can also create custom writer in the same way as creating custom formatter. 

Formatter's method you should override:

	void format(std::ostream &os, const LogLevel::Type level, const std::string &str)

And Writer's method you should override:

	void write(const std::string &text)	

See main.cpp for more information.

## disabling logging
If you want to disable logging, you call `setEnabled`.  


# License
Copyright (C) 2015 Giemsa/MithrilWorks(mithrilworks@gmail.com)  
this software is distributed under the zlib/libpng license.