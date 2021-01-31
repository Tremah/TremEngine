local lfs = require"lfs"

function createBackupDir(path)
  local backupRootDir=lfs.attributes(path)
  if backupRootDir == nil then
    assert(lfs.mkdir(path), "could not create " .. path)
  end
  --create new backup directory
  local dateTime = os.time()
  local year, month, day, hour, min, sec =
  os.date("%Y", dateTime),
  os.date("%m", dateTime),
  os.date("%d", dateTime),
  os.date("%H", dateTime),
  os.date("%M", dateTime),
  os.date("%S", dateTime)        
  local newDir = year .. month .. day .. '_' .. hour .. min .. sec
  backupDir = path .. "\\" .. newDir
  
  print("creating backupdir " .. backupDir .. "...")
  assert(lfs.mkdir(backupDir), "could not create " .. backupDir)
  print("created " .. backupDir)
  return backupDir
end

function copyFiles(srcPath, tarPath)
  for file in lfs.dir(srcPath) do
    if file ~= "."   and file ~= ".."  and file ~= ".vs"       and
       file ~= "x64" and not string.match(file, "bin*")        and
       file ~= "doc" and not string.match(file, ".*vcxproj.*") and 
       not string.match(file, ".*\.sln.*") and not string.match(file, "_ReSharper\.Caches") and 
       not string.match(file, ".*vendor*") and not string.match(file, "editorconfig") then
      local filePath = srcPath .. "\\" .. file
      local attr = lfs.attributes(filePath)
      if attr ~= nil then       
        if attr.mode == "directory" then
          local targetFile = tarPath .. "\\" .. file
          --print(targetFile)
          lfs.mkdir(targetFile)
          copyFiles(filePath, targetFile)  
        else
          print(filePath)
          local input = assert(io.open(filePath, "rb"))
          local targetFile = tarPath .. "\\" .. file
          local output = assert(io.open(targetFile, "wb"))
          local content = input:read("*all")
          output:write(content)
          input:close()
          output:close()
        end
      else
        print(file .. " could not be opened")
      end 
    end
  end
end

function main()
  --GameDev directory (parent dir of scripts/)
  sourceDir = ".."
  --backup root directory
  targetDir = createBackupDir("..\\..\\backup\\TremEngine")
  print("copying " .. sourceDir .. " to " .. targetDir .. "\n\n")
  copyFiles(sourceDir, targetDir)
  
  os.execute 'pause'
end

main()
