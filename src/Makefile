CXX = g++
CXXFLAGS = -std=c++17 -Wall -I../include

CORE_OBJS = core/matrix.o
LOSS_OBJS = losses/mse.o losses/mae.o
OPT_OBJS = optimizers/sgd.o optimizers/adam.o
MODEL_OBJS = models/supervised/linear_regression.o

ALL_OBJS = $(CORE_OBJS) $(LOSS_OBJS) $(OPT_OBJS) $(MODEL_OBJS) main.o

all: ml_train

ml_train: $(ALL_OBJS)
	$(CXX) $(CXXFLAGS) -o ml_train $(ALL_OBJS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

core/matrix.o: core/matrix.cpp
	$(CXX) $(CXXFLAGS) -c core/matrix.cpp -o core/matrix.o

losses/mse.o: losses/mse.cpp
	$(CXX) $(CXXFLAGS) -c losses/mse.cpp -o losses/mse.o

losses/mae.o: losses/mae.cpp
	$(CXX) $(CXXFLAGS) -c losses/mae.cpp -o losses/mae.o

optimizers/sgd.o: optimizers/sgd.cpp
	$(CXX) $(CXXFLAGS) -c optimizers/sgd.cpp -o optimizers/sgd.o

optimizers/adam.o: optimizers/adam.cpp
	$(CXX) $(CXXFLAGS) -c optimizers/adam.cpp -o optimizers/adam.o

models/supervised/linear_regression.o: models/supervised/linear_regression.cpp
	$(CXX) $(CXXFLAGS) -c models/supervised/linear_regression.cpp -o models/supervised/linear_regression.o

clean:
	rm -f $(ALL_OBJS) ml_train

run: ml_train
	./ml_train

.PHONY: all clean run
