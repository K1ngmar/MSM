SETTINGS_DIR := make_settings

include $(SETTINGS_DIR)/src.mk
include $(SETTINGS_DIR)/settings.mk
include $(SETTINGS_DIR)/colors.mk

all: $(NAME)

# Compilation

$(NAME): $(OBJ)
	@echo "$(COLOR_GREEN)Creating $(NAME) Library...$(COLOR_RESET)"
	@ar rcs $(NAME) $(OBJ)

-include $(DEPENDENCIES)

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(@D)
	@echo "$(COLOR_LBLUE)Compiling...	$(COLOR_BLUE)$<$(COLOR_RESET)"
	@$(CXX) -c -o $@ $< $(CFLAGS) -MMD -MP $(IFLAGS)

# Clean up

clean:
	@echo "$(COLOR_YELLOW)clean $(NAME)... $(COLOR_RESET)"
	@printf "$(COLOR_RED)"
	$(RM) -r $(ODIR)
	@printf "$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_YELLOW)force clean $(NAME)... $(COLOR_RESET)"
	@printf "$(COLOR_RED)"
	$(RM) $(NAME)
	$(RM) -rf $(UNIT_BIN)
	@printf "$(COLOR_RESET)"

re: fclean
	@$(MAKE) all

# Unit tests

$(UNIT_DIR)/bin/%: $(UNIT_DIR)/%.c
	@mkdir -p $(UNIT_DIR)/bin
	@echo "$(COLOR_LBLUE)Compiling tests... $(COLOR_BLUE)$<$(COLOR_RESET)"
	@$(CXX) $(CFLAGS) $(IFLAGS) $< $(UNIT_OBJ) -o $@ -lcriterion $(LIBKM_LIB)

unit_test_build: $(NAME) $(UNIT_DIR) $(UNIT_BIN)

unit_test: unit_test_build
	@sh $(UNIT_DIR)/run_tests.sh

# Debugging
debug: fclean
	@echo "$(COLOR_YELLOW)Building $(NAME) debug... $(COLOR_RESET)"
	@$(MAKE) DEBUG=1

leaks: fclean
	@echo "$(COLOR_YELLOW)Building $(NAME) leaks... $(COLOR_RESET)"
	@$(MAKE) LEAKS=1

fsanitize: fclean
	@echo "$(COLOR_YELLOW)Building $(NAME) fsanitize... $(COLOR_RESET)"
	@$(MAKE) FSANITIZE=1

# Phony
.PHONY: debug fsanitize test clean fclean re
