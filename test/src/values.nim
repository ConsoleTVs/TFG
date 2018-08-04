import tables

type
    ValueKind* = enum
        NUMBERVALUE = "NUMBER"
        STRINGVALUE = "STRING"
        BOOLEANVALUE = "BOOLEAN"
        LISTVALUE = "LIST"
        FUNCTIONVALUE = "FUNCTION"
        NONEVALUE = "NONE"

    Frame* = ref tuple
        heap: Table[string, Value]
        return_address: int

    Value* = ref object
        kind*: ValueKind
        numberValue*: float
        stringValue*: string
        booleanValue*: bool
        listValues*: seq[Value]
        functionArguments*: int # Number of arguments
        functionFrame*: Frame
        functionLabel*: string # Label of the function

proc newNumberValue*(v: float): Value =
    new result
    result.kind = NUMBERVALUE
    result.numberValue = v
proc newStringValue*(v: string): Value =
    new result
    result.kind = STRINGVALUE
    result.stringValue = v
proc newBooleanValue*(v: bool): Value =
    new result
    result.kind = BOOLEANVALUE
    result.booleanValue = v
proc newListValue*(v: seq[Value]): Value =
    new result
    result.kind = LISTVALUE
    result.listValues = v
proc newFunctionValue*(label: string, frame: Frame, arguments: int): Value =
    new result
    result.kind = FUNCTIONVALUE
    result.functionLabel = label
    result.functionFrame = frame
    result.functionArguments = arguments
proc newNoneValue*(): Value =
    new result
    result.kind = NONEVALUE

proc newFrame*(return_address: int, heap = initTable[string, Value]()): Frame =
    new result
    result.heap = heap
    result.return_address = return_address

proc `$`*(value: Value): string =
    case value.kind:
        of NUMBERVALUE: return $value.numberValue
        of STRINGVALUE: return value.stringValue
        of BOOLEANVALUE: return $value.booleanValue
        of LISTVALUE:
            result = "["
            for i,e in value.listValues:
                result &= $e
                if i != value.listValues.len - 1:
                    result &= ", "
            result &= "]"
        of FUNCTIONVALUE: return "<function " & value.functionLabel & ">"
        of NONEVALUE: return ""
        else: echo "Error creating value"; quit()