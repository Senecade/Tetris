#define BLOCKS_PER_LEVEL 10
#define SHOW_CHANGE_TIME 200

#define UP_INT 0
#define RIGHT_INT 1
#define DOWN_INT 2
#define LEFT_INT 3
#define FALL_INT 4
#define ROTATION_RIGHT_INT 5
#define ROTATION_LEFT_INT 6

#define X 0
#define Y 1
#define TRUE 1
#define FALSE 0

#define CHANGE_INT 0
#define RESULT_INT 1

#define MOVE_BLOCK_RIGHT ActiveBlox.x++
#define MOVE_BLOCK_DOWN while (possible(FALL_INT)) FALL
#define MOVE_BLOCK_LEFT ActiveBlox.x--
#define MOVE_BLOCK_FALL ActiveBlox.y++
#define ROTATE_BLOCK_RIGHT rotate(ROTATION_RIGHT_INT)
#define ROTATE_BLOCK_LEFT rotate(ROTATION_LEFT_INT)

#define RIGHT try_move(RIGHT_INT)
#define DOWN try_move(DOWN_INT)
#define LEFT try_move(LEFT_INT)
#define FALL try_move(FALL_INT)
#define ROTATE_RIGHT try_move(ROTATION_RIGHT_INT)
#define ROTATE_LEFT try_move(ROTATION_LEFT_INT)

#define MARK_ROWS destroy_rows(CHANGE_INT)
#define DEL_ROWS destroy_rows(RESULT_INT)

#define INIT init()

#define BLOX_RGB(R, G, B) block_to_rgb(ActiveBlox.Blox.rgb, &(R), &(G), &(B))
#define FIELD_RGB(X, Y, R, G, B) block_to_rgb(field[(X)][(Y)], &(R), &(G), &(B))
