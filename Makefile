.PHONY: clean All

All:
	@echo "----------Building project:[ Swift2 - Debug ]----------"
	@$(MAKE) -f  "Swift2.mk"
clean:
	@echo "----------Cleaning project:[ Swift2 - Debug ]----------"
	@$(MAKE) -f  "Swift2.mk" clean
