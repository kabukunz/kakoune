#WATCH_FILES= find . -type f -not -path '*/\.*' | grep -i '.*[.]cc,hh$$' 2> /dev/null
WATCH_FILES=find . -type f -not -path '*/\.*' -and -not -path '*/build/*' | grep -i '.*[.]\(cc\|hh\)$$' 2> /dev/null


test:
	./test/run

mkdir_build:
	[[ -d ./build ]] || mkdir -p build

entr_warn:
	@echo "----------------------------------------------------------"
	@echo "     ! File watching functionality non-operational !      "
	@echo ""
	@echo "Install entr(1) to automatically run tasks on file change."
	@echo "See http://entrproject.org/"
	@echo "----------------------------------------------------------"


watch_debug:
	if command -v entr > /dev/null; then ${WATCH_FILES} | entr -c $(MAKE) debug; else $(MAKE) debug entr_warn; fi

format:
	clang-format -style=Chromium src/* -i || clang-format37 -style=Chromium src/* -i

run:
	./build/kak


build: mkdir_build
	cd build; cmake -GNinja ..
	ninja -C build


debug: mkdir_build
	cd build; cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..
	ninja -C build