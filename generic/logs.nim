import console

type
    Logger* = ref object
        debug*: bool

var logger* = new Logger

proc error*(logger: Logger, message: string, help: string = "Error", halt: bool = true, debug = false) =
    if (debug and logger.debug) or not debug:
        message.error(help)
        if halt:
            quit()

proc success*(logger: Logger, message: string, help: string = "Success", debug = false) =
    if (debug and logger.debug) or not debug:
        message.success(help)

proc warning*(logger: Logger, message: string, help: string = "Warning", debug = false) =
    if (debug and logger.debug) or not debug:
        message.warning(help)

proc info*(logger: Logger, message: string, help: string = "Info", debug = false) =
    if (debug and logger.debug) or not debug:
        message.info(help)
