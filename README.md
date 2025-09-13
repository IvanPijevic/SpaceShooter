# Game:
Kontrole: W - gore, S - dole, A - lijevo, D - desno, RAZMAK - pucanje, Q - 1. laser, E - 2. laser

Projekt se može buildati u svim konfiguracijama: 32-bit i 64-bit. Sve konfiguracije su testirane i build rade bez grešaka.

Podržani operacijski sustav: Projekt je podržan samo na Windows operacijskim sustavima.

# Struktura projekta:

├── **SpaceShooter/**                   *# Game folder*

│   ├── **Levels/**                       *# Level folder*

│   │   ├── **Level.txt**              *# Level data file*

├── **SpaceShooter.sln**                 


# Pokretanje:  
Projekt je dovoljno klonirati i buildati — nema dodatnih zahtjeva niti vanjskih biblioteka.

# Editor
Level.txt u direktoriju SpaceShooter/Levels/ definira valove neprijatelja u igri. Svaki val neprijatelja opisan je s tri reda koji specificiraju broj neprijateljskih brodova, njihov tip i putanju kretanja.  
Format vala
***************************************************************************************
Prvi red: NumberOfEnemyShips: <broj> - Broj neprijateljskih brodova u valu (cijeli broj, npr. 4).  
Drugi red: TypeOfEnemyShips: <tip> - Tip broda DRONE 
Treći red: EnemyTrajectory: <putanja> - Putanja kretanja LINE
***************************************************************************************
Svaka tri reda čine jedan val. Valovi se nižu jedan za drugim u datoteci.  
Na kraj datoteke dodajte tri nova reda za svaki novi val.  
Primjer dodavanja vala:
***************************************************************************************
NumberOfEnemyShips: 5  
TypeOfEnemyShips: DRONE  
EnemyTrajectory: LINE 
***************************************************************************************
Uređivanje postojećeg vala:  
Pronađite tri reda koji odgovaraju valu koji želite promijeniti.  
Zamijenite vrijednosti:  
***************************************************************************************
# Napomena o level editoru  
U trenutnoj verziji projekta postavljen je samo jedan tip neprijatelja i jedna putanja kretanja. U editoru se može mijenjati samo broj neprijatelja koji dolaze.  
***************************************************************************************
# Uvjeti prekida igre
Igra se prekida u sljedećim situacijama:  
Uništenje zadnjeg neprijatelja u zadnjem valu  
Zadnji val izađe van ekrana  
Igrač izgubi treći život
