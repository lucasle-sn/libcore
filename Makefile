BUILD_DIR_PARENT=./build
BUILD_TYPE=debug
C_COMPILER=gcc
CXX_COMPILER=g++
BUILD_DIR=${BUILD_DIR_PARENT}/${BUILD_TYPE}/${C_COMPILER}

.PHONY: build all clean do-all-unit-tests gen-doxygen do-clang-format-check do-clang-format-run

build:
	@cmake -S . -B ${BUILD_DIR} \
			-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
			-DCMAKE_C_COMPILER=${C_COMPILER} \
			-DCMAKE_CXX_COMPILER=${CXX_COMPILER}
	@cmake --build ${BUILD_DIR} -j8 -- --no-print-directory

# Use default compiler gcc
build-debug:
	make build BUILD_TYPE=debug

# Use default compiler gcc
build-release:
	make build BUILD_TYPE=release

build-gcc:
	make build-debug C_COMPILER=gcc CXX_COMPILER=g++
	make build-release C_COMPILER=gcc CXX_COMPILER=g++

build-clang:
	make build-debug C_COMPILER=clang CXX_COMPILER=clang++
	make build-release C_COMPILER=clang CXX_COMPILER=clang++

all:
	make build-gcc
	make build-clang

do-all-unit-tests:
	@cmake -S . -B ${BUILD_DIR} \
			-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
			-DCMAKE_C_COMPILER=${C_COMPILER} \
			-DCMAKE_CXX_COMPILER=${CXX_COMPILER} \
			-Dlibcore_TESTING_ENABLED=ON
	@cmake --build ${BUILD_DIR} -j8 -- --no-print-directory
	cd ${BUILD_DIR} && ctest -j8 -T test --no-compress-output

gen-doxygen:
	@$(eval buildDir=build/doxygen)
	@cmake -S . -B ${buildDir} \
			-DCMAKE_BUILD_TYPE=debug \
			-DCMAKE_C_COMPILER="clang" \
			-DCMAKE_CXX_COMPILER="clang++" \
			-Dlibcore_DOXYGEN_BUILD_ENABLED=ON
	@cmake --build ${buildDir} --target doxygen -- --no-print-directory
	doxygen ${buildDir}/doxygen/Doxyfile

do-clang-format-check:
	@sh tools/check_clangformat.sh

do-clang-format-run:
	@sh tools/run_clangformat.sh

clean:
	@rm -rf ${BUILD_DIR_PARENT}
