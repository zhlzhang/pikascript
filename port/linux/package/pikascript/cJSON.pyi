import imp
from PikaObj import *
import json


class cJSON(TinyObj):
    def __init__(self): ...
    def print(self) -> str: ...

class Utils(TinyObj):
    def parse(self) -> cJSON: ...
    def createObject(self) -> cJSON: ...
