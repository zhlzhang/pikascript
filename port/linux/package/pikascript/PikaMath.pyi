from PikaObj import *


class Operator(TinyObj):
    def plusInt(self, num1: int, num2: int) -> int: ...
    def plusFloat(self, num1: float, num2: float) -> float: ...
    def minusInt(self, num1: int, num2: int) -> int: ...
    def minusFloat(self, num1: float, num2: float) -> float: ...
    def equalInt(self, num1: int, num2: int) -> int: ...
    def equalFloat(self, num1: float, num2: float) -> int: ...
    def graterThanInt(self, num1: int, num2: int) -> int: ...
    def graterThanFloat(self, num1: float, num2: float) -> int: ...
    def lessThanInt(self, num1: int, num2: int) -> int: ...
    def lessThanFloat(self, num1: float, num2: float) -> int: ...
    def AND(self, flag1: int, flag2: int) -> int: ...
    def OR(self, flag1: int, flag2: int) -> int: ...
    def NOT(self, flag: int) -> int: ...
    def __str__(self) -> str: ...
    def __del__(self): ...
