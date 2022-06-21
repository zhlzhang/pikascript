from PikaObj import *


class List(TinyObj):
    def __init__(self): ...
    # add an arg after the end of list
    def append(self, arg: any): ...
    # get an arg by the index
    def get(self, i: int) -> any: ...
    # set an arg by the index
    def set(self, i: int, arg: any): ...
    # get the length of list
    def len(self) -> int: ...
    # support for loop
    def __iter__(self) -> any: ...
    # support for loop
    def __next__(self) -> any: ...
    # support list[]  = val
    def __set__(self, __key: any, __val: any): ...
    # support val = list[]
    def __get__(self, __key: any) -> any: ...
    def __del__(self): ...


class Dict(TinyObj):
    def __init__(self): ...
    # get an arg by the key
    def get(self, key: str) -> any: ...
    # set an arg by the key
    def set(self, key: str, arg: any): ...
    # remove an arg by the key
    def remove(self, key: str): ...
    def __iter__(self) -> any: ...
    def __next__(self) -> any: ...
    # support dict[]  = val
    def __set__(self, __key: any, __val: any): ...
    # support val = dict[]
    def __get__(self, __key: any) -> any: ...
    def __del__(self): ...


class String(TinyObj):
    def __init__(self, s: str): ...
    def set(self, s: str): ...
    def get(self) -> str: ...
    def __iter__(self) -> any: ...
    def __next__(self) -> any: ...
    # support string[]  = val
    def __set__(self, __key: any, __val: any): ...
    # support val = string[]
    def __get__(self, __key: any) -> any: ...
    # support str()
    def __str__(self) -> str: ...

    def startwith(self, prefix: str) -> int: ...
    def endwith(self, suffix: str) -> int: ...
    def isdigit(self) -> int: ...
    def islower(self) -> int: ...
    def isalnum(self) -> int: ...
    def isalpha(self) -> int: ...
    def isspace(self) -> int: ...
    def split(self, s: str) -> any: ...


class ByteArray(List):
    # convert a string to ByteArray
    def fromString(self, s: str): ...


class Utils(TinyObj):
    # convert a int to bytes
    def int_to_bytes(self, val: int) -> bytes: ...
