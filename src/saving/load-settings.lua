local f = assert(io.open("src/saving/settings.racc", "r"))

-- Helper to read label + value
local function read_label_value()
  local label = f:read("*line")
  local value = f:read("*line")
  if value then
    value = value:gsub("^%s+", "") -- remove leading tab/space
  end
  return label, value
end

-- name
local _, value = read_label_value()
app_name = value

-- version
_, value = read_label_value()
app_version = value

-- fullscreen
_, value = read_label_value()
app_fullscreen = (value == "true")

-- driver
_, value = read_label_value()
if value == "REAL_TIME" then
  app_driver = 1
elseif value == "EVENT_DRIVEN" then
  app_driver = 0
else
  app_driver = -1 -- unknown
end

f:close()

