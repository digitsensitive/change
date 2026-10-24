CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -lEGL -lGLESv2 -lgbm -ldrm -lrt -lm -lpthread -ldl -levdev
RAYLIB = ./lib/libraylib.a

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
TITLE = change

# Find all source and header files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Object files go into build/
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
TARGET := $(BUILD_DIR)/${TITLE}

all: $(TARGET)

# Link executable
$(TARGET): $(OBJS) $(RAYLIB)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) $(RAYLIB) -o $@ $(LDFLAGS)

# Compile .c -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Format with clang
format:
	@echo "Formatting source and header files ..."
	@find $(SRC_DIR) -type f -name "*.c" -exec clang-format -i {} \;
	@find $(INC_DIR) -type f -name "*.h" -exec clang-format -i {} \;
	@echo "Formatting complete!"

# Create tmux session
tmux:
	@if ! tmux has-session -t $(TITLE) 2>/dev/null; then \
		tmux new-session -d -s $(TITLE) -n "editor"; \
		tmux split-window -h -t "$(TITLE):editor.0"; \
		tmux split-window -v -t "$(TITLE):editor.0"; \
		tmux split-window -v -t "$(TITLE):editor.2"; \
		tmux split-window -h -t "$(TITLE):editor.3"; \
		\
		tmux send-keys -t "$(TITLE):editor.0" "nano ./src/*.h" C-m; \
		tmux send-keys -t "$(TITLE):editor.1" "nano ./src/*.c CHANGELOG.md" C-m; \
		tmux send-keys -t "$(TITLE):editor.2" "grep -A 1 "RLAPI" ./include/raylib.h | fzf" C-m; \
		tmux send-keys -t "$(TITLE):editor.3" "clear" C-m; \
		tmux clock-mode -t "$(TITLE):editor.4"; \
		\
		tmux resize-pane -t "$(TITLE):editor.0" -L 23; \
		\
		tmux select-pane -t "$(TITLE):editor.0"; \
	fi
	tmux attach-session -t $(TITLE)

# Kill tmux session
tmux-kill:
	tmux kill-session -t $(TITLE)

# Cleanup
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
