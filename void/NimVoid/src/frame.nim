import tables, values

type
    Frame* = ref tuple
        heap: Table[string, Value]
        return_address: int

proc newFrame*(return_address: int, heap = initTable[string, Value]()): Frame =
    new result
    result.heap = heap
    result.return_address = return_address

# proc `$`*(frame: Frame): string = "Frame -> " & $frame.return_address & " " & $frame.heap