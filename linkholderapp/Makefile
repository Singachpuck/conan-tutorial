include config.mk

all: clean c-install generate b

# examples: clean c-install generate-ex b

# roll-dice: clean c-install generate-roll b

c-install:
	$(CONAN) install -of=$(BUILD_DIR) . 

generate:
	$(CMAKE_GENERATE_COMMAND)

# generate-ex:
# 	$(CMAKE_GENERATE_COMMAND) -DWITH_EXAMPLES=On -DWITH_ROLL_DICE=Off

# generate-roll:
# 	$(CMAKE_GENERATE_COMMAND) -DWITH_EXAMPLES=Off -DWITH_ROLL_DICE=On

b:
	$(CMAKE_HOME) --build ./$(BUILD_DIR)

clean:
	powershell -Command "Remove-Item -Path ./build -Recurse -Force"
	mkdir build

run-app:
	./build/bin/linkholderapp.exe