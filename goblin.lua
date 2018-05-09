#!/bin/lua

-- Goblin : A C++ Small Project Builder for Unix plaforms v1.0
-- https://gist.github.com/Yannissss/24f1f6bc9176380cfc6d537c0e052289

local args = {...}

-- Build constants
local CXX      = "gcc"
local CXXFLAGS = "-Wall -g"
local LDFLAGS  = "-lSDL2 -lGL -lm"
local SRCDIR   = "src/"
local OBJDIR   = "obj/"
local BINDIR   = "./"
local TARGET   = "flora"

-- Compile function using os interface return compile log
function compile(sourceFile)
  local output = io.popen(CXX.." "..LDFLAGS.." -c "..SRCDIR.."/"
    ..sourceFile..".c -o "..OBJDIR.."/"..sourceFile..".o "
    ..CXXFLAGS, "r")
  local i,_ = sourceFile:reverse():find("/") or #sourceFile,_
  local dir = sourceFile:sub(1,(#sourceFile-i))
  if (dir ~= "")
  then
    os.execute("mkdir -p "..OBJDIR.."/"..dir)
  end
  local compileLog = output:read("*a")
  output:close()
  return compileLog
end

-- Find all C++ Sources file in the SRCDIR and return them as an array
function getSourcesFiles()
  local sourcesFiles = {}
  local output = io.popen("find "..SRCDIR..' -name "*.c"', "r")
  for path in output:lines()
  do
    path,_ = path:gsub("%.c", "")
    path,_ = path:gsub(SRCDIR, "")
    table.insert(sourcesFiles, path)
  end
  output:close()
  return sourcesFiles
end

-- Check whether the source file has been changed since last compile
-- and return true if the source file need to be compiled again
function isUpToDate(sourceFile)
  local output = io.popen("date +%s -r "..
    SRCDIR.."/"..sourceFile..".c", "r")
  local editDate = tonumber(output:read("*a")) or 0
    io.popen("date +%s -r "..SRCDIR.."/"..sourceFile..".c", "r")
  output:close()
  output = io.popen("date +%s -r "..
    OBJDIR.."/"..sourceFile..".o", "r")
  local compileDate = tonumber(output:read("*a")) or 0
  output:close()
  return (not (editDate>compileDate))
end

-- Try to build necessary dirs in case they don't exist
os.execute("mkdir -p "..BINDIR)
os.execute("mkdir -p "..SRCDIR)
os.execute("mkdir -p "..OBJDIR)

-- Compile all necessary sources into their object
local sourcesFiles = getSourcesFiles()
local compileQueue = {}
for _,sourceFile in ipairs(sourcesFiles)
do
  if (not isUpToDate(sourceFile))
  then
    table.insert(compileQueue, sourceFile)
  end
end
local N = #compileQueue
if (N == 0 and args[1] ~= "-f")
then
  print(" -- \27[32mNothing to do\27[37m")
  os.exit()
else
  print(" -- \27[32mStarting to compile necessary objects \27[37m")
  for i,sourceFile in ipairs(compileQueue)
  do
    local progress = math.floor(100*(i-1)/N)
    io.write("[CXX ")
    if (progress < 10)
    then
      io.write("0"..progress.."%] ")
    else
      io.write(progress.."%] ")
    end
    print("\27[32mBuilding "..sourceFile..".o \27[37m") 
    local compileLog = compile(sourceFile)
  end
end

-- Linking all objects into targetted binary
local objectsList = ""
for _,sourceFile in ipairs(sourcesFiles)
do
  objectsList = objectsList..OBJDIR.."/"..sourceFile..".o "
end
print(" -- \27[32mStarting to link objects in binary \27[37m")
os.execute(CXX.." "..LDFLAGS.." "..objectsList
    .." -o "..BINDIR.."/"..TARGET.." "..CXXFLAGS)
print(" -- \27[32mTarget built : "..TARGET.."\27[37m")
os.execute("chmod +x "..BINDIR.."/"..TARGET)
