H_REP=./include
C_REP=./src
O_REP=./obj
B_REP=./bin
$(B_REP)/main: $(O_REP)/main.o $(O_REP)/grille.o $(O_REP)/jeu.o $(O_REP)/io.o
	gcc -o $@ -Wall $^
$(O_REP)/%.o : $(C_REP)/%.c
	gcc -o $@ -c $< -I $(H_REP)
run:
	./bin/main ./grilles/$(GRILLE)
clean:
	rm $(O_REP)/*.o
	rm $(B_REP)/main
archive:
	tar -cvz $(H_REP)/*.h $(C_REP)/*.c makefile grilles ./doc/Doxyfile -f jeu_de_la_vie.tar.gz
