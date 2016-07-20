This was one my first ever projects, thus the code for it questionable but I keep it here for memories.

It requies SFML (audio) as a third-party library.

It is an simple RPG where you walk around a field, encounter monsters and have a chance of leveling up.

Roaming:

![alt tag](http://puu.sh/nVAYR/fa528f5d53.png "Roaming.")

Encounter:

![alt tag](http://puu.sh/nVB2q/1007408c37.png "Encounter.")

![alt tag](http://puu.sh/nVB4e/f78be41bf1.png "Encounter.")

Every encounter is based in the main.cpp inside a function.

All monsters inherit from a base "monster" class.

The maps are named "Map X Y". This allows for simple transition between maps. Eg, when the player walks over a '>' tile, the X position of the map increases by one. Then I can just load up "Map Player::MapX Player::MapY" eg "Map 1 0"
