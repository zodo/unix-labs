INC=./includes
SRC=./src
OUT=./bin

$(OUT)/lab: $(OUT)/main.o
	gcc -o $(OUT)/lab $(OUT)/main.o
$(OUT)/main.o: $(SRC)/main.c $(INC)/first.h
	gcc -I$(INC) -o $(OUT)/main.o -c $(SRC)/main.c
# $(OUT)/args.o: $(SRC)/args.c $(INC)/first.h
# 	gcc -I$(INC) -o $(OUT)/args.o -c $(SRC)/args.c
# $(OUT)/stdMode.o: $(SRC)/stdMode.c $(INC)/first.h
# 	gcc -I$(INC) -o $(OUT)/stdMode.o -c $(SRC)/stdMode.c
# $(OUT)/childMode.o: $(SRC)/childMode.c $(INC)/first.h
# 	gcc -I$(INC) -o $(OUT)/childMode.o -c $(SRC)/childMode.c
# $(OUT)/posixMode.o: $(SRC)/posixMode.c $(INC)/first.h
# 	gcc -I$(INC) -o $(OUT)/posixMode.o -c $(SRC)/posixMode.c
# $(OUT)/pipeMode.o: $(SRC)/pipeMode.c $(INC)/first.h
# 	gcc -I$(INC) -o $(OUT)/pipeMode.o -c $(SRC)/pipeMode.c
clean:
	rm $(OUT)/*.o $(OUT)/lab