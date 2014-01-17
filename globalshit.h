#define WINDOW_HEIGHT 650
#define WINDOW_WIDTH 550
#define GAME_WINDOW_HEIGHT 600
#define GAME_WINDOW_WIDTH 300
#define OFFSET_X 25
#define OFFSET_Y 25

#define BLOCKS_PER_LEVEL 5

#define UP_INT 0
#define RIGHT_INT 1
#define DOWN_INT 2
#define LEFT_INT 3
#define FALL_INT 4
#define ROTATION_RIGHT_INT 5
#define ROTATION_LEFT_INT 6
#define SHADOW_FALL_INT 7

#define FIELD_INT 0
#define SHADOW_INT 1
#define BLOX_INT 2

#define MARK_ROWS_INT 0
#define DEL_ROWS_INT 1

#define X 0
#define Y 1
#define TRUE 1
#define FALSE 0

#define MOVE_BLOCK_RIGHT ActiveBlox.x++
#define MOVE_BLOCK_DOWN while (FALL)
#define MOVE_BLOCK_LEFT ActiveBlox.x--
#define MOVE_BLOCK_FALL ActiveBlox.y++
#define ROTATE_BLOCK_RIGHT rotate(ROTATION_RIGHT_INT)
#define ROTATE_BLOCK_LEFT rotate(ROTATION_LEFT_INT)
#define MOVE_SHADOW_FALL ActiveBlox.shadow_offset++

#define RIGHT try_move(RIGHT_INT)
#define DOWN try_move(DOWN_INT)
#define LEFT try_move(LEFT_INT)
#define FALL try_move(FALL_INT)
#define ROTATE_RIGHT try_move(ROTATION_RIGHT_INT)
#define ROTATE_LEFT try_move(ROTATION_LEFT_INT)
#define SHADOW gen_shadow()

#define INIT init(NULL)

#define BLOX_RGB(R, G, B) block_to_rgb(ActiveBlox.Blox.rgb, &(R), &(G), &(B))
#define FIELD_RGB(X, Y, R, G, B) block_to_rgb(field[(X)][(Y)], &(R), &(G), &(B))
#define RGB_INT(R, G, B) (((R) << 17) | ((G) <<9) | ((B) <<1) | 1)
