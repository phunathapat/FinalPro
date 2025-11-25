DEPS = mmabelzz

mabelz : main.cpp
	clear 
	g++ main.cpp -o $(DEPS)
    
narak : $(DEPS)
	./$(DEPS)

clean : $(DEPS)
	rm $(DEPS)