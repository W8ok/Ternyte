// utilities.c
#include "raylib.h"
#include <math.h>

#include "core.h"


Vector2 SnapToGrid(Vector2 point, Rectangle workspace, int grid_size)
{
    // Adjust point relative to workspace
    float relative_x = point.x - workspace.x;
    float relative_y = point.y - workspace.y;
    
    // Find the nearest grid multiple
    float snapped_x = roundf(relative_x / grid_size) * grid_size;
    float snapped_y = roundf(relative_y / grid_size) * grid_size;
    
    // Add workspace offset back
    snapped_x += workspace.x;
    snapped_y += workspace.y;
    
    return (Vector2){snapped_x, snapped_y};
}
