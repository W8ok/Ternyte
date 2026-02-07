// utilities.c
#include "raylib.h"
#include <math.h>

#include "src.h"


Vector2 SnapToGrid(Vector2 point, Rectangle rec, int grid_size)
{
    // Adjust point relative to the rectangle
    float relative_x = point.x - rec.x;
    float relative_y = point.y - rec.y;
    
    // Find the nearest grid multiple
    float snapped_x = roundf(relative_x / grid_size) * grid_size;
    float snapped_y = roundf(relative_y / grid_size) * grid_size;
    
    // Add workspace offset back
    snapped_x += rec.x;
    snapped_y += rec.y;
    
    return (Vector2){snapped_x, snapped_y};
}
