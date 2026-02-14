-- save/load-settings.lua
local file = assert(io.open("src/save/settings.racc", "r"))

-- Formatting
local function read(label)
  local _ = file:read("*line")          -- discard label line
  local value = file:read("*line")      -- read value line
  if value then value = value:gsub("^%s+", "") end
  return value
end

-- Settings values
app_name = read("name")
app_version = read("version")
app_fullscreen = read("fullscreen") == "true"

-- Driver mapping
local driver_str = read("driver")
if driver_str == "REAL_TIME" then
  app_driver = 1
elseif driver_str == "EVENT_DRIVEN" then
  app_driver = 0
else
  app_driver = -1 -- unknown
end

file:close()
