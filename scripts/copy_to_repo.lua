local lfs = require"lfs"

function trim(str)
   return (str:gsub("^%s*(.-)%s*$", "%1"))
end

function readConfig(path)
  local readValues = false
  local configTable = {}
  for line in io.lines(path) do  
    line = trim(line)     
    if string.len(line) ~= 0 and not string.match(line, "^//") then
      if string.match(line, "^\#copy_to_repo") then
        readValues = true
      else      
        if readValues then 
          for k, v in string.gmatch(line, "(.+)=(.+)") do
            k = trim(k)
            v = trim(v)
            configTable[k] = v
          end
        end
      end
    end          
  end
  return configTable
end

function createDir(path)
  local attr = lfs.attributes(path)
  if attr == nil then   
    assert(lfs.mkdir(path), "could not create " .. path)
  end
end

function copyFiles(srcPath, tarPath)
  createDir(tarPath)
  for file in lfs.dir(srcPath) do
    if file ~= "."   and file ~= ".." then
      local filePath = srcPath .. "\\" .. file
      local attr = lfs.attributes(filePath)
      if attr ~= nil then       
        if attr.mode == "directory" then
          local targetFile = tarPath .. "\\" .. file
          --print(targetFile)
          lfs.mkdir(targetFile)
          copyFiles(filePath, targetFile)  
        else
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
  local configTable = readConfig("scripts_config.conf")
  local sourceRootPath = configTable["src_root_path"]
  local targetRootPath = configTable["tar_root_path"]
  
  --print("source path: " .. sourceRootPath)
  --print("target path: " .. targetRootPath)
  
  for srcFile in string.gmatch(configTable["src_paths"], '([^,]+)') do
    srcFile = trim(srcFile)
    local sourceFile = sourceRootPath .. "\\" .. srcFile
    local targetFile = targetRootPath .. "\\" .. srcFile  

  print("source path: " .. sourceFile)
  print("target path: " .. targetFile)    
        
    copyFiles(sourceFile, targetFile)
  end
  
  
end

main()