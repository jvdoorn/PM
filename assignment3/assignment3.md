# Life
Het is de bedoeling om een C++-programma te maken dat de gebruiker in staat stelt Life te spelen via een menu-systeem. Dat betekent dat de gebruiker van het programma kan kiezen uit een aantal mogelijkheden, de zogeheten opties. Er is één submenu, waarin ook weer enkele opties zijn. De bedoeling is dat het hele menu op één regel staat, onder de wereld (zie verderop). 
De opties worden gekozen door de eerste letter van de betreffende optie in te toetsen (gevolgd door Enter), bijvoorbeeld een s of S om te stoppen. Uiteraard wordt een en ander duidelijk en ondubbelzinnig aan de gebruiker meegedeeld. Gebruik geen recursie!
Van Wiki Alle door de gebruiker ingetoetste symbolen moeten gecontroleerd worden, dat wil zeggen dat er binnen redelijke grenzen geen foute invoer geaccepteerd wordt. Zo zal het intoetsen van bijvoorbeeld q of & in het hoofdmenu genegeerd worden. Verder moet bij getalleninvoer karakter voor karakter ingelezen worden (met cin.get ( ); als je elders ook nog cin >> ... gebruikt krijg je overigens soms problemen met "hangende Enter's"; gebruik dus overal cin.get ( )). Er moet ook op gelet worden dat er geen te grote getallen worden ingevoerd. Schrijf dus een geschikte functie leesgetal die de gelezen karakters (cijfers) omzet in een getal (tip: negeer alle "voorloop-Enter's"; verwerk alles tot en met de eerstvolgende enter, en maak hiervan zo goed mogelijk een getal, van een maximale grootte; zo kan abc123defg999h, als je een getal kleiner dan 10000 wilt, bijvoorbeeld verwerkt worden tot 1239), en een functie leesoptie die netjes één karakter inleest en Enter's afhandelt! Aan de gebruiker mogen "redelijke" beperkingen worden gevraagd, bijvoorbeeld dat de in te voeren getallen maximaal vier cijfers hebben. Het programma moet dan echter wel bestand zijn tegen pogingen meer dan vier cijfers in te voeren. Ook het invoeren van letters in plaats van cijfers moet geen problemen opleveren. Houd het simpel!

Life is een cellulaire automaat, in 1970 bedacht door John Horton Conway. Zie verder het college, Wikipedia of hier, en Johan Bontes' implementatie, met voorbeeldpatronen [en de nieuwste GitHub-versie]. In een 2-dimensionaal (zeg) 1000 bij 1000 rooster, de wereld, beginnen we met een eindig aantal levende vakjes oftewel cellen. Een levend vakje met minder dan 2 of meer dan 3 buren van de 8 (horizontaal, verticaal en diagonaal) gaat dood (uit eenzaamheid of juist overbevolking), met precies 2 of 3 levende buren overleeft het. In een dood vakje met precies 3 levende buren ontstaat leven. Dit leidt tot de volgende generatie. Let erop dat dit voor alle vakjes tegelijk gebeurt! 
Eigenlijk moet het geheel zich afspelen op een oneindig rooster, maar we kiezen voor de eindige variant. Om moeilijkheden te voorkomen, spreken we af dat de rand van onze wereld altijd uit dode cellen blijft bestaan. 
De gebruiker ziet altijd een klein gedeelte van de wereld, de view geheten. Steeds staan de coordinaten van het punt linksboven genoemd. De hoogte en breedte van de view zijn member-variabelen (zie verderop), zeg 25 en 80. Liefhebbers mogen ze eventueel wijzigen in het parameter-submenu.

In het hoofdmenu zijn de volgende opties aanwezig:

**Stoppen**

**Heelschoon** Maak de wereld leeg (alle cellen gaan dood).

**Schoon** Maak de view leeg (alle cellen in de view gaan dood).

**Verschuif** Verschuif de view naar links, boven, rechts, of onder.

**Parameters** Dit leidt tot een submenu om de parameters in te stellen, zie onder.

**Random** Vul de view met random dode en levende cellen. De rest van de wereld blijft onveranderd.

**Toggle** Klapt levend en dood om voor de cel op de "cursorpositie"; deze laatste kan met vier toetsen omhoog/omlaag/naar links/rechts (bijvoorbeeld W/A/S/Z) gewijzigd worden, waarbij de coordinaten steeds getoond worden.

**Glidergun** Vul de view met een glidergun. Lees de configuratie in uit een file. (Als dit "hard-coded" wordt gedaan kost dat een halve punt.)

**Een** Er wordt één generatie gedaan.

**Gaan** Er worden een hele serie generaties gedaan — en allemaal getoond (zonder Enter's).

Steeds wordt de view getoond, in het begin ruwweg het midden van de wereld. Voor de optie Random moet een zelfgemaakte random-generator (nou ja, random) gebruikt worden, zie Hoofdstuk 3.9.3 uit het dictaat, gedeelte "aantekeningen bij de hoorcolleges".
Er zijn verschillende parameters, in te stellen via het gelijknamige submenu:

De verschuivings-stapgrootte van de view. Deze parameter wordt gebruikt als de view in één van de vier richtingen verschuift. Beeld de echte rand van de wereld ook duidelijk af, zodra deze in beeld is.
Het percentage cellen dat levend moet zijn bij de optie Random (bij benadering).
De twee verschillende karakters die op het scherm gebruikt worden voor levende en dode cellen.
Kies zelf redelijke grenswaarden voor deze parameters. En denk natuurlijk aan de optie "Terug naar het hoofdmenu".
De bedoeling is een klasse (class) life te maken, met daarin onder meer functies die ieder voor zich een menuoptie afhandelen. De parameters zijn typisch membervariabelen. Gebruik nog geen eigen headerfiles, alles moet deze keer in één file staan.

## Opmerkingen
Gebruik geschikte (member)functies. Bij deze opgave mogen bij elke functie (zelfs main) tussen begin-{ en eind-} hooguit circa 30 niet al te volle regels staan! Elke functie dient van commentaar voorzien te zijn, bij voorkeur één regel boven de functie. Let op goed parametergebruik: alle parameters, met uitzondering van membervariabelen, in de heading doorgeven, en de variabele-declaraties zowel bij main als bij de andere functies aan het begin. De enige te gebruiken headerfiles zijn in principe iostream, fstream, cstdlib en string. Zeer ruwe indicatie voor de lengte van het C++-programma: 500 regels. Denk aan het infoblokje.