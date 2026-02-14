-- save/save-settings.lua
local file = assert(io.open("src/save/settings.racc", "w"))

-- Formatting
local function write(label, value)
  file:write(label .. ":\n\t" .. value .. "\n")
end

-- Driver mapping
local driver_str = (driver == 0) and "EVENT_DRIVEN"
                or (driver == 1) and "REAL_TIME"
                or "UNKNOWN"

-- Settings values
write("name", name)
write("version", version)
write("fullscreen", fullscreen and "true" or "false")
write("driver", driver_str)

file:close()
