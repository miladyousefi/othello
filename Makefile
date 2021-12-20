REVERSI_BIN = othello
REVERSI_OBJ = AIPlayer.cpp Gameboard.cpp Othello.cpp

CXX = g++
CXX_OPTS = -g -O0 -Wall

all: $(REVERSI_BIN)

clean:
	@rm -rf *.o $(REVERSI_BIN)

$(REVERSI_BIN): $(SQUARE_MAZE_OBJS)
	$(CXX) $(CXX_OPTS) $(REVERSI_OBJ) -o $(REVERSI_BIN)
