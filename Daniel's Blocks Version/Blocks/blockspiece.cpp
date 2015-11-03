#include "blockspiece.h"
#include <stdlib.h>
#include <QtCore>


/*******************************************************************************
 *  select a random piece shape (BlocksShape Enum value 1-7), and sets it as the
 * current shape
 ******************************************************************************/
void BlocksPiece::setRandomShape()
{
    setShape(BlockShape(qrand() % 7 +1));
}

/*******************************************************************************
* @returns piece shape (Enum value 0-7)
*******************************************************************************/
BlockShape BlocksPiece::shape() const {
    return pieceShape;
}

/*******************************************************************************
 * get block segment's x coordinate for the given segment index
 * @return horizontal coordinate for BlocksPiece segment
 ******************************************************************************/
int BlocksPiece::x(int index) const
{
    return coords[index][0];
}

/*******************************************************************************
 * get block segment's y coordinate for the given segment index
 * @return vertical coordinate for BlocksPiece segment
 ******************************************************************************/
int BlocksPiece::y(int index) const
{
    return coords[index][1];
}

/*******************************************************************************
 * Set block segment's x coordinate for the given segment index
 * @param segment index
 * @param horizontal coordinate
 ******************************************************************************/
void BlocksPiece::setX(int index, int x)
{
    coords[index][0] = x;
}

/*******************************************************************************
 * Set block segment's 7 coordinate for the given segment index
 * @param segment index
 * @param vertical coordinate
 ******************************************************************************/
void BlocksPiece::setY(int index, int y)
{
    coords[index][1] = y;
}


/*******************************************************************************
 * Setshape function uses a lookup table to associate the relative location for
 * each BlocksPiece segment
*******************************************************************************/
void BlocksPiece::setShape(BlockShape shape){
    //tridementionial array holds the relative position for each block segment
    //coordsTable[BlockShape][BlockSegment][RelativeXYPosition]
    static const int coordsTable[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },//[0]NoShape
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },//[1]ZShape
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },//[2]SShape
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },//[3]LineShape
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },//[4]TShape
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },//[5]SquareShape
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },//[6]LShape
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }//[7]RShape
    };


    for (int i = 0; i < 4; i++){//for each segment
        for (int j = 0; j < 2; j++){//for x and y
            coords[i][j] = coordsTable[shape][i][j];
        }

    }
    pieceShape = shape;
}



/*******************************************************************************
 * @return minimum horizontal coordinate occupied by piece segments
 ******************************************************************************/
int BlocksPiece::minX() const
{
    //capture first segment x value
    int min = coords[0][0];

    for (int i = 0; i < 4; ++i){//for each segment
        min = qMin(min, coords[i][0]);//capture the min value
    }

    return min;//return min
}

/*******************************************************************************
 * @return maximum horizontal coordinate occupied by piece segments
 ******************************************************************************/
int BlocksPiece::maxX() const
{
    int max = coords[0][0];

    for(int i = 1; i < 4; ++i){
        max = qMax(max, coords[i][0]);
    }
    return max;
}

/*******************************************************************************
 * @return minimum vertical coordinate occupied by piece segments
 ******************************************************************************/
int BlocksPiece::minY() const
{
    int min = coords [0][1];

    for(int i = 0; i< 4; ++i){
        min = qMin(min, coords[i][1]);
    }

    return min;
}


/*******************************************************************************
 * @return maximum vertical coordinate occupied by piece segments
 ******************************************************************************/
int BlocksPiece::maxY() const
{
    int max = coords[0][1];

    for(int i = 1; i < 4; ++i){
        max = qMax(max, coords[i][1]);
    }
    return max;
}


/*******************************************************************************
 * Rotate left method. Creates a new peice with the same shape, but rotated to
 * the left
 * @return BlocksPiece with coordinates rotated to the left
 ******************************************************************************/
BlocksPiece BlocksPiece::rotatedLeft() const
{
    //a rotated square block is the same as the original so return this object
    if (pieceShape == SquareShape){
        return *this;
    }

    //create new peice
    BlocksPiece result;

    //set new piece shape
    result.pieceShape = pieceShape;

    //for each piece segment, translate the coords to the left
    for (int i = 0; i< 4; ++i){
        result.setX(i, y(i));
        result.setY(i,-x(i));
    }

    //return new shape
    return result;

}

/*******************************************************************************
 * Rotate right method. Creates a new peice with the same shape, but rotated to
 * the right
 * @return BlocksPiece with coordinates rotated to the right
 ******************************************************************************/
BlocksPiece BlocksPiece::rotatedRight() const
{
    if (pieceShape == SquareShape){
        return *this;
    }

    BlocksPiece result;

    result.pieceShape = pieceShape;
    for(int i= 0; i< 4; ++i){
        result.setX(i, -y(i));
        result.setY(i,x(i));
    }

    return result;

}
