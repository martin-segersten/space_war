CC = g++
CFLAGS = -c
LFLAGS = -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf
OBJECTS = main.o Objects.o Player.o timer.o Gamestates.o GamestateGameplay.o general.o

space_war : $(OBJECTS)
			$(CC) $(LFLAGS) $(OBJECTS) -o space_war
			
main.o : main.cpp Gamestates.h general.h
			$(CC) $(LFLAGS) $(CFLAGS) main.cpp -o main.o
			
GamestateGameplay.o : GamestateGameplay.cpp Gamestates.h timer.h Objects.h	
			$(CC) $(LFLAGS) $(CFLAGS) GamestateGameplay.cpp -o GamestateGameplay.o	
			
Gamestates.o : Gamestates.cpp Gamestates.h timer.h Objects.h
			$(CC) $(LFLAGS) $(CFLAGS) Gamestates.cpp -o Gamestates.o

Player.o : Player.cpp Objects.h general.h
			$(CC) $(LFLAGS) $(CFLAGS) Player.cpp -o Player.o

Objects.o : Objects.cpp Objects.h general.h
			$(CC) $(LFLAGS) $(CFLAGS) Objects.cpp -o Objects.o
			
ParticleEngine.o : ParticleEngine.cpp ParticleEngine.h Particle.h
			$(CC) $(LFLAGS) $(CLFLAGS) ParticleEngine.cpp -o ParticleEngine.o
			
Particle.o : Particle.cpp Particle.h
			$(CC) $(LFLAGS) $(CLFLAGS) Particle.cpp -o Particle.o

general.o : general.cpp general.h
			$(CC) $(LFLAGS) $(CFLAGS) general.cpp -o general.o

timer.o : timer.cpp timer.h
			$(CC) $(LFLAGS) $(CFLAGS) timer.cpp -o timer.o
			

Gamestates.h : Objects.h timer.h

Objects.h : general.h

clean:
	\rm *.o *~ space_war
	
tar:
	tar cfv space_war.tar *.h *.cpp files/
