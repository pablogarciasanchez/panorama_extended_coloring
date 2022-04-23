SRC = src/
OBJ = obj/
INC = include/
OPENCV4 = /usr/include/opencv4
LOPENCV = -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
COMPILER = g++ -fopenmp -O3 $(LOPENCV)
FLAGS = -I$(INC) -I$(OPENCV4)
exe = bin/panorama_extended
units_cpp := $(wildcard $(addprefix $(SRC), *.cpp))
units_o := $(addprefix $(OBJ), $(addsuffix .o, $(notdir $(basename $(units_cpp)))))
headers := $(wildcard $(addprefix $(INC), *.h*))

# all: $(OBJ)/malla3d.o
# 	$(COMPILER) -o $(EXE) $(SRC)/main.cpp -I$(INC) -I$(OPENCV)

# $(OBJ)/malla3d.o:
# 	$(COMPILER) -c $(SRC)/malla3d.cpp -I$(INC)

x: $(exe)
	@echo Compilando $(exe)
	$(exe)

test: $(exe)
	@echo Compilando $(exe)

$(exe): $(units_o) makefile
	$(COMPILER) -o $(exe) $(units_o)

$(OBJ)%.o : $(SRC)%.cpp
	$(COMPILER) -o $@ -c $(FLAGS) $<

$(units_cpp) : $(headers)
	touch $(units_cpp)

clean:
	rm -rf obj/*.o bin/*_exe
