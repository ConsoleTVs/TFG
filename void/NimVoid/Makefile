COMPILER = nim
ENTRY = src/void
FLAGS = -d:release

.PHONY
debug:
	$(COMPILER) c $(ENTRY)

.PHONY
try:
	$(COMPILER) c --run $(ENTRY)

.PHONY
release:
	$(COMPILER) c $(ENTRY) $(FLAGS)