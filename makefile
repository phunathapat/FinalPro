DEPS = mmabelzz

compile : main.cpp
	clear 
	g++ main.cpp -o $(DEPS)
    
run : $(DEPS)
	./$(DEPS)

clean : $(DEPS)
	rm $(DEPS)