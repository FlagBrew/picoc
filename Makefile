rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
.SECONDEXPANSION:

# Use $ xxd -i ./LICENSE > include/LICENSE.h
# to create the license info file. Should be signed char, add a
# null character to the end of the array.

CC	:=	gcc
CXX	:=	g++

SOURCES				:=	source
INCLUDES			:=	include

CFILES		:=	$(patsubst ./%,%,$(foreach dir,$(SOURCES),$(call rwildcard,$(dir),*.c)))
CPPFILES	:=	$(patsubst ./%,%,$(foreach dir,$(SOURCES),$(call rwildcard,$(dir),*.cpp)))
EXEC_NAME	:=	picoc
BUILD		:=	build

ifeq ($(OS),Windows_NT)
EXEC_NAME	:=	$(EXEC_NAME).exe
CFILES		+=	platform/library_msvc.c platform/platform_msvc.c
else
CFILES		+=	platform/library_unix.c platform/platform_unix.c
endif

DEBUG_FLAGS	:=

CFLAGS=-Wall -g -std=gnu11 -pedantic -DUNIX_HOST -DVER=\"`git show-ref --abbrev=8 --head --hash head`\" -DTAG=\"`git describe --abbrev=0 --tags`\" $(foreach dir, $(INCLUDES), -I$(CURDIR)/$(dir)) $(DEBUG_FLAGS)
LIBS=-lm -lreadline

OFILES			:=	$(CFILES:.c=.c.o) $(CPPFILES:.cpp=.cpp.o)
BUILD_OFILES	:=	$(subst //,/,$(subst /../,/__PrEvDiR/,$(subst /,//, $(OFILES))))
BUILD_OFILES	:=	$(patsubst ../%,__PrEvDiR/%,$(BUILD_OFILES))
BUILD_OFILES	:=	$(addprefix $(BUILD)/, $(BUILD_OFILES))
DEPSFILES		:=	$(BUILD_OFILES:.o=.d)

LD		:=	$(if $(CPPFILES),$(CXX),$(CC))
LDFLAGS	:=	-lm -lreadline

.PHONY: all clean

all: $(EXEC_NAME)

test:	all
	@(cd tests; make -s test)
	@(cd tests; make -s csmith)
	@(cd tests; make -s jpoirier)

format:
	clang-format -i $(CFILES) $(CPPFILES) $(foreach dir, $(INCLUDES), $(wildcard $(dir)/*.h)) $(foreach dir, $(INCLUDES), $(wildcard $(dir)/*.hpp))

count:
	@echo "Core:"
	@cat include/picoc.h include/interpreter.h source/picoc.c source/table.c source/lex.c source/parse.c source/expression.c source/platform.c source/heap.c source/type.c source/variable.c source/include.c source/debug.c | grep -v '^[ 	]*/\*' | grep -v '^[ 	]*$$' | wc
	@echo ""
	@echo "Everything:"
	@cat $(CFILES) $(CPPFILES) $(foreach dir, $(INCLUDES), $(wildcard $(dir)/*.h)) $(foreach dir, $(INCLUDES), $(wildcard $(dir)/*.hpp)) | wc

clean:
	@rm -rf $(BUILD)
	@rm -f $(EXEC_NAME)

$(EXEC_NAME): $(BUILD_OFILES)
	$(LD) $(BUILD_OFILES) $(LDFLAGS) -o $@

$(BUILD)/%.c.o: $$(subst __PrEvDiR,..,$$*.c)
	@mkdir -p $(dir $@)
	$(CC) -MMD -MP -MF $(@:.o=.d) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.cpp.o: $$(subst __PrEvDiR,..,$$*.cpp)
	@mkdir -p $(dir $@)
	$(CXX) -MMD -MP -MF $(@:.o=.d) $(CXXFLAGS) -c -o $@ $<

include $(wildcard $(DEPSFILES))
