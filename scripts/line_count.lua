local lfs = require"lfs"

function trim(str)
   return (str:gsub("^%s*(.-)%s*$", "%1"))
end

function calculateLinesOfCode(path, includeComments)
  local attr = lfs.attributes(path)
  
  if attr == nil then
    print(srcPath .. " could not be opened")
    return 1
  end
  
  local totalLineCount = 0
  for file in lfs.dir(path) do
    if file ~= "."   and file ~= ".." then
      local path = path .. "\\" .. file
      local attr = lfs.attributes(path)
      if attr ~= nil then       
        if attr.mode == "directory" then  
          totalLineCount = totalLineCount + calculateLinesOfCode(path, includeComments)
        else   
          local lineCount = 0
          for line in io.lines(path) do  
            line = trim(line)
            if includeComments then
              lineCount = lineCount + 1
            else     
              if string.len(line) ~= 0 and 
                 not string.match(line, "^/.*") and
                 not string.match(line, "^\*") then
                lineCount = lineCount + 1
              end          
            end
          end
          outString = path .. ": " .. lineCount .. " lines."
          print(outString)
          totalLineCount = totalLineCount + lineCount
        end
      end 
    end
  end
  
  return totalLineCount
end

function main()  
  srcPath = "X:\\workspace\\GameDev\\Trem\\src\\trem"
  --if script was called with --i option, include comments and empty lines
  includeCommentsAndEmptyLines = false
  outputText = "comments and empty lines are not included"
  if arg[1] == "--i" then
    includeCommentsAndEmptyLines = true
    outputText = "comments and empty lines are included"
  end
  totalLineCount = calculateLinesOfCode(srcPath, includeCommentsAndEmptyLines)
  print("\n" .. outputText)
  print("total lines of code: " .. totalLineCount)
    
  --keep console open
  os.execute 'pause'
end

main()
