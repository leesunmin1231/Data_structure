NAME = program
CAL_SRC = calculator.c stack.c
TRAIN_SRC = train.c stack.c

all: $(NAME)

$(NAME):
	gcc $(CAL_SRC) -o $(NAME)
train:
	gcc $(TRAIN_SRC) -o $(NAME)
clean:
	rm -f $(NAME)
re: clean all

retrain: clean train
