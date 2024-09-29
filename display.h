#ifndef _DISPLAY_H_
#define _DISPLAY_H_

class Board;

// prints the board/game to stdout
class Display {
    Board *b; // Display class will "have" a board pointer
  public:
    Display(Board *b);
    ~Display();

    void render_board() const; // prints board to stdout
    void render_hand(int pnum) const;
    void render_minion(int pnum, int index) const;
};

#endif
