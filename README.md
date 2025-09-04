# SpaceShooter

Upute za korištenje:

w, a, s, d - kretanje

space - pucanje

q, e - odabir oružja


Nivo se učitava iz SpaceShooter/Levels/level.txt  u kojem se mogu mijenjati/dodavati valovi nadolazećih "brodova", broj neprijatelja(NumberOfEnemyShips), tip neprijatelja te putanje po kojima dolaze. 
U trenutnoj verziji igre implementirana je po jedna varijanta tipa neprijatelja(DRONE) i putanje(LINE). 
Kod dodavanja valova u .txt nije potrebno paziti na prazne redove, "#" označava komentare.

U Enemy.cpp u konstruktoru za promjenu brzine kretanja valova mjenja se m_speed koji je trenutno postavit na 15.0f

U Player.cpp m_verticalSpeed i m_horizontalSpeed za promjenu brzine kretanja igrača

Kad val bude uništen ili izađe van ekrana, započima sljedeći val...   U .txt fajlu se nalazi 5 valova, kad 5. val završi igra završava.

Dronovi imaju 30hp-a, osnovni mod, brži(def), pucanja (tipka: Q) radi (10dmga), sekundarni, sporiji mod (tipka: E) radi 30dmg-a. Igrač je postavit na 3 života koje gubi u sudaru, igra završava kad se izgube životi.
