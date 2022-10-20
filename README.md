# Anteckningar-2022-10-20
Implementering av interruptstyrda tillståndsmaskiner i C.

Filen Tillståndsmaskin för en dörr.zip innehåller en demonstration av en enkel tillståndsmaskin för en dörr, 
som kan hållas öppen, stängd, låst eller försättas i ett feltillstånd (som kräver återställning av tillståndsmaskinen för att avbrytas).
Detta program genomfördes som en första demonstration av tillståndsmaskiner. 
Interrupts används för att direkt uppdatera dörrens tillstånd via tryckknappar.

Övriga filer används för implementering av en tillståndsmaskin för multipla lysdioder, som kan blinka, tändas och släckas. 
Interrupts används för att direkt uppdatera lysdiodernas tillstånd via tryckknappar. 
Pekare används i samband med blinkhastighet för att direkt kunna avbryta eventuell blinkning vid byte av tillstånd (blinkhastighetem som refereras
till av pekaren nollställs när tillståndet övergår från blinkande till något annat).

I filen header.h implementeras deklarationer, enumerationer och definitioner för implementering av tillståndsmaskinen.
I filen main.c åstadkommes initiering av mikrodatorn, följt av att tillståndsmaskinen utsignaler uppdateras kontinuerligt.
I filen setup.c sker initiering av mikrodatorn (I/O-portarna konfigureras och avbrott aktiveras på tryckknapparnas pinnar).
I filen interrupts.c placeras avbrottsrutiner för att uppdatera tillståndsmaskinens tillstånd vid nedtryckning av någon av tryckknapparna.
I filen fsm.c definieras funktioner för att realisera tillståndsmaskinen.
