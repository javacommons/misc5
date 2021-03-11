import os
import osproc
import strutils,pegs,unicode
import osproc,streams,times

#proc `$`(t:TimeInfo) : string = format(t, "yyyy/MM/dd HH:mm:ss ")

proc call_with_busybox(args: openArray[string] = []): int =
  let busybox = "$#\\busybox32.exe" % [os.getAppDir()]
  #let cmdline = "\"$#\" $#" % [busybox, cmd]
  #echo cmdline
  #return execCmd(cmdline)
  #return execShellCmd(cmdline)
  #return global.run_cmd(cmdline)
  let p = startProcess(busybox, "", args, nil, {poEchoCmd, poUsePath, poParentStreams})
  defer:
    p.close
  #echo p.processID
  let exit_status = p.waitForExit()
  return exit_status

import nimline
defineCppType(MyClass, "MyClass", "MyClass.hpp")
defineCppType(MyClass2, "MyClass2", "MyClass.hpp")
cppfiles("MyClass.cpp")

var
  myx2 = MyClass2.new()
  myx = MyClass.new(555)
myx.test3().to(void)
myx.num = 99
var x = myx2.test20(1234).to(cint)
echo x
#echo myx2.num.to(cint)
#let n = myx2.num().to(cint)
echo global.globalNumber.to(cint)
let msg: StdString = "HelloWorld"
myx.say(msg).to(void)
let gr = myx.greeting(msg).to(StdString)
echo gr.c_str().to(cstring)
echo myx.z().to(cint)
myx.z(222).to(void)
echo myx.z().to(cint)
#echo myx2.class1.z().to(cint)


block:
  echo "$1 eats $2." % ["The cat", "fish"]
  echo "$# eats $#." % ["The cat", "fish"]
  echo "$animal eats $food." % ["animal", "The cat", "food", "fish"]

#echo os.getAppDir()
#var busybox = "$#\\busybox32.exe" % [os.getAppDir()]
#echo busybox
#var curl = "$#\\curl32.exe" % [os.getAppDir()]
#var cmd1 = "\"$#\" ls -l" % [busybox]
#echo cmd1
#var xc1 = execCmd(cmd1)
#echo xc1

#var cmd01 = 
#  "\"$#\" --etag-compare test.etag --etag-save test.etag -o msys2-x86_64-latest.tar.xz https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz" % [curl]
#echo execCmd(cmd01)
#echo call_with_busybox("rm -rf my-msys2.tmp")
#echo call_with_busybox(@["rm", "-rf", "my-msys2.tmp"])
#echo call_with_busybox("mkdir -p my-msys2.tmp")
#echo call_with_busybox(@["mkdir", "-p", "my-msys2.tmp"])
#echo call_with_busybox("tar -xvf msys2-x86_64-latest.tar.xz -C my-msys2.tmp --strip-components 1")
#echo call_with_busybox(@[
#  "tar", "-xvf", "msys2-x86_64-latest.tar.xz", "-C", "my-msys2.tmp", "--strip-components", "1"])

let inst01 = "$#\\inst01.exe" % [os.getAppDir()]
#var xc1 = execCmd(inst01)
#echo xc1
#discard startProcess(inst01)
global.launch_cmd(inst01).to(void)
