##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

all: zappy_server zappy_gui zappy_ai

zappy_server:
	make -C server/
	mv server/zappy_server .

# zappy_gui rule needs to make symbolic link to the assets folder
zappy_gui:
	cd gui && git submodule init && git pull origin feat/gui --recurse-submodules
	cd gui && ./build.sh
	cp gui/imgui.ini .
	mv gui/zappy_gui .

zappy_ai:
	cp ia/zappy_ai.py zappy_ai
	cp -t . ia/sucide.py ia/evolver.py ia/collector.py ia/debug_lib.py

clean:
	make clean -C server/

fclean: clean
	make fclean -C server/
	rm -fr gui/build
	rm -f sucide.py
	rm -f evolver.py
	rm -f collector.py
	rm -f debug_lib.py
	rm -f imgui.ini
	rm -f zappy_server
	rm -f zappy_gui
	rm -f zappy_ai

re: fclean all
