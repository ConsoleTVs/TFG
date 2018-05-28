import terminal, strformat, strutils

proc displayMsg(f: File, color: ForegroundColor, helpText, text: string) =
    f.styledWriteLine(color, &"[{helpText}] ", resetStyle, text, resetStyle)

proc success*(text, helpText: string = "Success") =
    stdout.displayMsg(fgGreen, helpText, text)

proc error*(text, helpText: string = "Error") =
    stderr.displayMsg(fgRed, helpText, text)

proc info*(text, helpText: string = "Information") =
    stdout.displayMsg(fgCyan, helpText, text)

proc warning*(text, helpText: string = "Warning") =
    stdout.displayMsg(fgYellow, helpText, text)

proc printQuestion(
        f: File,
        color: ForegroundColor,
        text, helptext: string,
        default: bool,
        badAnswer: string = "",
        showOptions: bool = true
    ) =
    f.setForegroundColor(color)
    f.write &"[{helpText}] "
    f.resetAttributes
    f.write text
    if showOptions:
        f.write &" ("
        if default:
            f.setForegroundColor(fgGreen)
            f.write "Yes"
            f.resetAttributes
            f.write "/No) "
        else:
            f.write "Yes/"
            f.setForegroundColor(fgRed)
            f.write "No"
            f.resetAttributes
            f.write ") "
    if badAnswer != "":
        f.setForegroundColor(fgRed)
        f.write &"[{badAnswer} is not a valid answer] "
        f.resetAttributes

proc confirm*(text: string = "Are you sure?", helpText: string = "Question", default: bool = true): bool =
    stdout.printQuestion(fgMagenta, text, helpText, default)
    while true:
        var res: string = stdin.readLine
        if res == "":
            res = "n"
            if default:
                res = "y"
        case res
        of "y", "Y", "yes", "Yes", "YES":
            stdout.cursorUp
            stdout.eraseLine
            stdout.printQuestion(fgGreen, text, "Confirmed", default, showOptions = false)
            stdout.write '\n'
            return true
        of "n", "N", "no", "No", "NO":
            stdout.cursorUp
            stdout.eraseLine
            stdout.printQuestion(fgRed, text, "Declined", default, showOptions = false)
            stdout.write '\n'
            return false
        else:
            stdout.cursorUp
            stdout.eraseLine
            stdout.printQuestion(fgMagenta, text, helpText, default, res)
            continue

proc ask*(text: string, items: seq[string], helpText: string = "Question") : int =
    stdout.styledWriteLine(fgMagenta, &"[{helpText}] ", resetStyle, text, resetStyle)
    for i,e in items:
        stdout.styledWriteLine(fgCyan, &"    [{i}]\t", resetStyle, e, resetStyle)
    var res: string
    stdout.write "Answer: "
    res = stdin.readLine()
    while not res.isDigit or (res.parseInt > items.len or res.parseInt < 0):
        stdout.cursorUp
        stdout.eraseLine
        stdout.write "Answer: "
        stdout.setForegroundColor(fgRed)
        stdout.write &" [{res} is not a valid answer] "
        stdout.resetAttributes
        res = stdin.readLine
    # Remove the answer
    stdout.cursorUp
    stdout.eraseLine
    # Remove the items
    for i in items:
        stdout.cursorUp
        stdout.eraseLine
    # Remove the initial question and replace it
    stdout.cursorUp
    stdout.eraseLine
    stdout.styledWriteLine(fgGreen, &"[{items[res.parseInt]}] ", resetStyle, text, resetStyle)
    return res.parseInt