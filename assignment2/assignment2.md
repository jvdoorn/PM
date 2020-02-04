# Keurig
Er moet een programma worden geschreven dat een foutloos te compileren C++-programma (bijvoorbeeld een uitwerking van de eerste programmeeropgave) een klein beetje probeert te begrijpen, oftewel een paar zaken doet die een compiler ook moet doen. Het programma moet de invoerfile netjes ingesprongen naar een uitvoerfile kopiëren, en daarbij alle //-commentaar weglaten. Verder moet het programma getallen opsporen, en kijken of deze een speciale eigenschap hebben. 
Stel allereerst enkele eenvoudige vragen om gegevens van de gebruiker te weten te komen. Gevraagd wordt hoe de originele invoerfile en de "doelfile" heten (als de invoerfile niet bestaat stopt het programma direct), en hoe groot de parameter tab (zie straks) moet worden. Het programma leest dan eenmalig de opgegeven invoerfile, en schrijft deze symbool voor symbool op de juiste wijze aangepast weg naar de uitvoerfile; na afloop wordt een rapportje op het scherm afgedrukt.

De volgende drie punten moeten worden geadresseerd:

## Commentaar moet verwijderd worden. 
Elk commentaar dat begint met // moet niet naar de uitvoerfile worden weggeschreven, maar weggelaten worden. Alleen de regelovergang wordt weer naar de uitvoerfile gekopieerd. 
Voor het gemak mag aangenomen worden dat er geen /* ... */ commentaar voorkomt. Als er binnen //-commentaar opnieuw // voorkomt, wordt die volgende // ook gewoon verwijderd. We vatten zelfs // binnen een string op als het begin van commentaar.

## Inspringen moet netjes geregeld worden.
De bedoeling is dat iedere regel op diepte d even ver inspringt, en wel tab maal d spaties. Hierbij is tab een door de gebruiker te kiezen getal, bijvoorbeeld 3. De diepte d van een regel wordt als volgt bepaald. De eerste regel van het programma is op diepte 0, iedere openingsaccolade { verhoogt de diepte met 1 (één) en iedere sluitaccolade } verlaagt de diepte met 1 (één). Een veranderde diepte merk je pas op de volgende regel (zie verderop hoe we accolades zelf afhandelen). 
We nemen aan dat er geen accolades binnen strings (of als karakter '{') voorkomen. Accolades die binnen commentaar staan tellen niet mee voor de berekening van de diepte. De oude regelstructuur van het programma blijft behouden; voor iedere regel geldt dat het eerste karakter ongelijk spatie en TAB ('\t') op positie tab maal d +1 moet komen. Dit karakter kan een regelovergang zijn; zo wordt een oorspronkelijk "lege" regel op diepte d nu een regel met tab maal d spaties, en een regelovergang. 
Wellicht ten overvloede, een regel met een stel spaties en TAB's, en dan verder alleen //-commentaar, komt als tab maal d spaties in de uitvoerfile. 
We nemen aan dat de accolades netjes gepaard zijn. 
En op welke positie staat een accolade, als dit het eerste symbool is dat op een regel wordt afgedrukt? We spreken af dat als dit een openings-accolade is hiervoor nog de "oude" diepte wordt gebruikt, en voor een sluit-accolade de "nieuwe". We krijgen dus (waarbij een punt (.) een spatie voorstelt; tab = 3, d = 2):
......if ( x == y )
......{
.........z = 0;
......}

## Lychrel-getallen moeten worden opgespoord. 
Voor elk geheel getal > 0 uit de invoerfile wordt gekeken of het een Lychrel-getal is. Op het scherm wordt afgedrukt wat het aantal iteraties is om tot een palindroom te komen (voor 545 is dit 0, voor 113 is dit 1), of het nummer van de iteratie waarvan het resultaat boven INT_MAX (gebruik include <climits>) uitkomt (voor 196 is dit (waarschijnlijk) 18). Als dit laatste gebeurt, wordt dit erbij vermeld. 
Elke directe opeenvolging van cijfers in de invoerfile wordt als een geheel getal opgevat. Neem aan dat ze alle kleiner dan of gelijk aan INT_MAX zijn. Zo bevat 123abcd-"qqq 5"+++uvw-77.88ddd//vb5656 de gehele getallen 123, 5, 77 en 88. Het maakt verder ook niet uit of een getal al dan niet binnen een string staat, het telt gewoon mee. Getallen binnen commentaar worden niet gedaan.
Na afloop moeten op het scherm enkele "statistieken" afgedrukt worden, namelijk het totaal aantal ingelezen karakters (inclusief regelovergangen, spaties en dergelijke), het aantal in de uitvoerfile afgedrukte karakters en het maximale aantal iteraties voor Lychrel-berekeningen met een bijbehorend getal.

## Opmerkingen
We nemen aan dat de gebruiker zo vriendelijk is verder geen fouten te maken bij het invoeren van gegevens. Als een getal gevraagd wordt, geeft hij/zij een getal.
Gebruik de regelstructuur: elke regelovergang in een bestand bestaat uit een LineFeed (\n) (in UNIX) of een CarriageReturn gevolgd door een LineFeed (\r\n) (in Windows). Normaal gesproken gaat dit "vanzelf" goed. We nemen aan dat er voor het EndOfFile-symbool (wat dat ook moge zijn) een regelovergang staat.
Alleen voor de namen van de files mag een array (of string) gebruikt worden; voor het lezen en verwerken van de tekst is slechts het huidige karakter en enige kennis over de voorgaande karakters nodig — zie boven. Alleen de headerfiles iostream en fstream mogen gebruikt worden (en string voor de filenamen; denk in dat geval aan het gebruik van c_str; en climits voor INT_MAX). Uit een file mag alleen met invoer.get (...) gelezen worden, vergelijk Hoofdstuk 3.7 uit het dictaat, gedeelte "aantekeningen bij de hoorcolleges". Binnen de hoofdloop van het programma staat bij voorkeur maar één keer een get-opdracht, vergelijk het voorbeeldprogramma uit dit hoofdstuk (daar staat twee keer get, één maal vóór de loop, uiteraard). Karakters mogen niet worden teruggezet in de oorspronkelijke file. 
Schrijf zelf functies die testen of een karakter een cijfer is, etcetera. Er mogen geen andere functies dan die uit fstream gebruikt worden, en c_str.
Denk aan het infoblokje dat aan begin op het scherm verschijnt. Gebruik enkele geschikte functies, bijvoorbeeld voor infoblokje, inlezen gegevens van de gebruiker, omkeren van het getal, en coderen en decoderen van een file (zie de tips bij het vijfde werkcollege). Globale variabelen zijn streng verboden. Ruwe indicatie voor de lengte van het C++-programma: circa 250 regels.