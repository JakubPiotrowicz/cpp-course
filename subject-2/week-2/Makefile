CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0

SINGLE := $(wildcard [0-9][0-9]-*.cpp)
DIRS := $(patsubst %/,%,$(wildcard [0-9][0-9]-*/))
PROGRAMS := $(SINGLE:%.cpp=build/%) $(DIRS:%=build/%)
BROKEN := $(patsubst %/,%,$(wildcard broken/*/))

.PHONY: all run broken clean
all: $(PROGRAMS)

# Przykład z jednego pliku: jedna reguła kompiluje i łączy.
build/%: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

# Przykład z katalogu: każdy plik .cpp kompiluje się osobno do pliku obiektowego (-c),
# a potem wszystkie obiekty łączy sterownik C++. Opcje -MMD -MP zapisują zależności od nagłówków
# w plikach .d, dzięki czemu po zmianie nagłówka make kompiluje ponownie tylko zależne pliki.
build/obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

define DIR_PROGRAM
OBJECTS_$(1) := $$(patsubst %.cpp,build/obj/%.o,$$(wildcard $(1)/*.cpp))
build/$(1): $$(OBJECTS_$(1))
	$$(CXX) $$(LDFLAGS) $$^ $$(LDLIBS) -o $$@
-include $$(OBJECTS_$(1):.o=.d)
endef
$(foreach dir,$(DIRS),$(eval $(call DIR_PROGRAM,$(dir))))

run: all
	@set -e; for program in $(PROGRAMS); do \
	    printf '\n>>> %s\n' "$$program"; "./$$program"; \
	done

# Celowo błędne warianty. Każdy podkatalog broken/ to osobny program. Błędy kompilacji i łączenia
# są tu oczekiwane, więc pętla nie przerywa pracy po pierwszym z nich.
broken:
	@mkdir -p build/broken
	@for dir in $(BROKEN); do \
	    printf '\n>>> %s\n' "$$dir"; \
	    $(CXX) $(CXXFLAGS) $$dir/*.cpp -o build/$$dir || true; \
	done

clean:
	$(RM) -r build
