import os
import io

InFile = open("Input.txt", "r")
OutFile = open("Output.txt", "w")

Line = InFile.readline()

OutFile.write("switch(Var)\n{\n")

while(Line != ''):
    Line.find('=')
    Value = Line[0 : Line.find('=')-1]
    Out = "case %s: return \"%s\";\n" % (Value, Value)
    OutFile.write(Out)
    Line = InFile.readline()

OutFile.write("}\n")
