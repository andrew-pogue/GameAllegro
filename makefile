OS := windows
IDIR := ./include D:/Libraries/MinGW/Allegro/include
LDIR := ./lib D:/Libraries/MinGW/Allegro/lib
SDIR := ./src
BDIR := ./build
TARGET := hello_allegro

CC := gcc
CXX := g++

CFLAGS := -Wall
CXXFLAGS := -Wall
IFLAGS := $(addprefix -I,$(IDIR))
DFLAGS = -MMD -MF $(@:.o=.d)

LFLAGS := $(addprefix -L,$(LDIR)) -lmingw32 -lallegro -lallegro_main -lallegro_font -lallegro_image
LFLAGS += -lallegro_primitives -lallegro_audio -lallegro_video -lallegro_color
ifeq ($(OS), windows)
	LFLAGS += -mconsole -mwindows
endif

SRCS := $(wildcard $(SDIR)/*.c)
SRCS += $(wildcard $(SDIR)/*.cpp)

OBJS := $(SRCS:$(SDIR)%=$(BDIR)%.o)

DEPS := $(OBJS:.o=.d)

-include $(DEPS)

all : init $(TARGET)

init :
ifeq ($(OS), windows)
	@-mkdir "$(BDIR)"
else
	@mkdir -p $(BDIR)
endif

$(TARGET) : $(OBJS)
	@$(CXX) $^ $(CXXFLAGS) $(LFLAGS) -o $@

$(BDIR)/%.c.o : $(SDIR)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS) $(IFLAGS) -o $@

$(BDIR)/%.cpp.o : $(SDIR)/%.cpp
	@$(CXX) -c $< $(CXXFLAGS) $(DFLAGS) $(IFLAGS) -o $@

.PHONY : clean
clean:
ifeq ($(OS), windows)
	@rmdir /s /q "$(BDIR)" & del $(TARGET).exe
else
	@rm -r $(BDIR) & rm $(TARGET)
endif