ifndef SETTINGS_MK
SETTINGS_MK = 1

NAME	= FSM.a	

CFLAGS	= -Wall -Wextra -Werror -O3 -std=c++23 -pedantic
IFLAGS	= $(addprefix -I, $(IDIR))

SDIR	= src
ODIR	= .obj
IDIR	= includes 

DEPENDENCIES := $(patsubst %.cpp,.obj/%.d,$(SRC))

TEST_DIR = tests
UNIT_DIR = $(TEST_DIR)/unit_tests

UNIT_TESTS = $(wildcard $(UNIT_DIR)/*.cpp)
UNIT_BIN = $(patsubst $(UNIT_DIR)/%.cpp, $(UNIT_DIR)/bin/%, $(UNIT_TESTS))

ifdef DEBUG
	CFLAGS += -g -D DEBUG
endif

ifdef LEAKS
	CFLAGS += -D LEAKS
endif

ifdef FSANITIZE
	CFLAGS += -D FSANITIZE
	CFLAGS += -g -fsanitize=address
endif

include ./make_settings/src.mk
OBJ := $(addprefix $(ODIR)/, $(SRC:.cpp=.o))
UNIT_OBJ := $(filter-out $(ODIR)/main.o,$(OBJ))

endif
