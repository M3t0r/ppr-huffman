ppr-huffman
===========

Dieses Projekt realisiert eine einfache Komprimierung von Dateien mit Hilfe 
des Huffmann-Algorithmus.

Benutzung
=========
    SYNTAX:
      ppr-huffman (-c | -d) inputFile [outputFile]

      Optionen:
         -c  Komprimiert die Datei inputFile.
         -d  Behandelt inputFile als komprimierte Datei und
             dekomprimiert diese.
         -h  Zeigt diese Hilfe an.

    Dieses Programm komprimiert Dateien mit Hilfe des Huffmann-Algorithmus.

    Wird das Programm mit dem Parameter -c oder -d aufgerufen,
    so muss zwingend auch ein inputFile angegeben werden.
    Wird kein OutputFile angegeben, so wird an den Namen der
    Eingabedatei eine Standardendung angehangen. Diese lautet im
    Modus Komprimierung .hc bzw. .hd im Modus Dekomprimierung.

    BEISPIELE:
      > ppr-huffman -h              ... Zeigt diese Hilfe an.
      > ppr-huffman -c datei.exe    ... Komprimiert die Datei datei.exe,
                                        dabei wird die Ausgabedatei
                                        datei.exe.hc erzeugt.
      > ppr-huffman -d datei.exe.hc ... Dekomprimiert die Datei datei.exe.hc
                                        und speichert das dekomprimierte
                                        Ergebnis in der datei.exe.hd.
      > ppr-huffman -c d.txt d.comp ... Komprimiert die Datei d.txt und
                                        speichert das Ergebnis in d.comp.

Entwicklung
===========

Baue pp-huffman

    make || make ppr-huffman

Baue ppr-huffman mit DEBUG Flags

    make debug

Baue und führe Tests aus

    make test

Linte den Quellcode (Benötigt `splint` in $PATH)

    make splint

Baue Dokumentation (Benötigt `doxygen` in $PATH)

    make doxygen

Authoren
========
Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
