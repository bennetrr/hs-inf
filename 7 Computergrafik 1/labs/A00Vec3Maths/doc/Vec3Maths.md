---
# Build Command
# pandoc --pdf-engine xelatex -s CG1P00.md --template ../../eisvogel.latex -o CG1P06.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: 'Praktikum 0: Mathematische Funktionen'
titlepage: true
author: [Prof. Dr.-Ing. Quirin Meyer]
date: '2025-10-05'
keywords: [CG1 Praktikum, Mathematische Funktionen]
papersize: A4
fontfamily: roboto
mainfont: 'Roboto-Regular'
lang: 'de'
header-left: "\\theauthor"
header-center: ' '
header-right: 'Computer Grafik 1'
footer-left: 'Hochschule Coburg'
footer-center: "\\thepage"
footer-right: 'FEIF'
...

# Warm-Up: Vec3-Mathematik implementieren

Implementieren Sie alle Methoden in der Datei `cgclib/include/cgclib/math/Vec3.h`, die mit dem Kommentar `// TODO Implement me!` versehen sind. Die
Beschreibung der jeweiligen Funktion finden Sie direkt im zugehörigen Kommentar im Header.

Führen Sie anschließend das Testprojekt `TestVec3` aus, um Ihre Implementierung zu überprüfen. Achten Sie darauf, dass sämtliche Tests erfolgreich
durchlaufen und keine Fehler auftreten.

Ziel dieser Aufgabe ist eine vollständige und korrekte Implementierung der Vektor-Mathematik für `Vec3`, die alle vorgesehenen Tests besteht.
