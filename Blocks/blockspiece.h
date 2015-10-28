#ifndef BLOCKSPIECE_H
#define BLOCKSPIECE_H

//shapw enum maps name to digits 1 - 7
enum BlockShape {NoShape, ZShape, SShape, LineShape, TShape, SquareShape, LShape, RShape};

class BlocksPiece
{
public:
    BlocksPiece() {setShape (NoShape);}

    void setRandomShape();
    void setShape(BlockShape shape);

    BlockShape shape() const ;

    int x(int index) const;
    int y(int index) const;

    int minX() const;
    int minY() const;
    int maxX() const;
    int maxY() const;

    BlocksPiece rotatedLeft() const;
    BlocksPiece rotatedRight() const;

private:
    void setX(int index, int x);
    void setY(int index, int y);

    BlockShape pieceShape;
    int coords[4][2];


};

#endif // BLOCKSPIECE_H
