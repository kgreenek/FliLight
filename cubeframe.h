#ifndef CUBEDEFINES_H
#define CUBEDEFINES_H

#define CUBE_NUM_LEDS_PER_ROW   8
#define CUBE_NUM_BYTES_PER_ROW  1
#define CUBE_NUM_ROWS_PER_LEVEL 8
#define CUBE_NUM_LEVELS         8

typedef uint8_t CubeRow[CUBE_NUM_BYTES_PER_ROW];
typedef CubeRow CubeLevel[CUBE_NUM_ROWS_PER_LEVEL];
typedef CubeLevel CubeFrame[CUBE_NUM_LEVELS];

#endif // CUBEDEFINES_H
