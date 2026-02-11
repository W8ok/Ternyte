local f = assert(io.open("src/saving/settings.racc", "w"))

-- name and version are strings
f:write("name:\n\t" .. name .. "\n")
f:write("version:\n\t" .. version .. "\n")

-- fullscreen -> "true" / "false"
local fs_str = fullscreen and "true" or "false"
f:write("fullscreen:\n\t" .. fs_str .. "\n")

-- driver -> human-readable string
local driver_str = (driver == 0) and "EVENT_DRIVEN"
                 or (driver == 1) and "REAL_TIME"
                 or "UNKNOWN"
f:write("driver:\n\t" .. driver_str .. "\n")

f:close()

