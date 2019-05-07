.PHONY: clean All

All:
	@echo "----------Building project:[ ProjetCppGraph - Debug ]----------"
	@"$(MAKE)" -f  "ProjetCppGraph.mk"
clean:
	@echo "----------Cleaning project:[ ProjetCppGraph - Debug ]----------"
	@"$(MAKE)" -f  "ProjetCppGraph.mk" clean
