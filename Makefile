CXX = clang++
CXXFLAGS += -g -Wall -std=c++20 -pedantic

-include config.mk
CXXFLAGS += -I$(EIGEN_PATH)

BUILD_DIR = bin

ALL_OBJ = main.o VolSlice/VolSlice.o VolSlice/FlatSlice.o VolSlice/SabrSlice.o DataContainer/Table.o Utils/Utils.o Utils/Optimization.o

main: $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/main $(ALL_OBJ)

main.o: main.cpp
VolSlice/VolSlice.o: VolSlice/VolSlice.cpp VolSlice/VolSlice.h
VolSlice/FlatSlice.o: VolSlice/FlatSlice.cpp VolSlice/FlatSlice.h Utils/Optimization.h
VolSlice/SabrSlice.o: VolSlice/SabrSlice.cpp VolSlice/SabrSlice.h Utils/Optimization.h
DataContainer/Table.o: DataContainer/Table.cpp DataContainer/Table.h Utils/Utils.h
Utils/Utils.o: Utils/Utils.cpp Utils/Utils.h
Utils/Optimization.o: Utils/Optimization.cpp Utils/Optimization.h

clean:
	find . -name "*.o" -type f -delete
	rm -rf $(BUILD_DIR)/*