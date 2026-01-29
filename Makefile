# Détection de l'OS
ifeq ($(OS),Windows_NT)
    # Configuration Windows
    RM = del /Q
    EXT = .exe
    FIX_PATH = $(subst /,\,$1)
else
    # Configuration Linux / Mac
    RM = rm -f
    EXT =
    FIX_PATH = $1
endif

TARGET = main$(EXT)

all:
	g++ -o $(TARGET) source/*.cpp -Isources

clean:
	$(RM) $(TARGET)