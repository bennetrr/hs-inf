---
# Build Command
# pandoc --pdf-engine xelatex -s CG1P00.md --template ../../eisvogel.latex -o CG1P06.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: 'Praktikum 1: Rasterung'
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

# Rechteck zeichnen

**Implementieren Sie** die Funktion in der Datei `cgclib/src/raster/Rectangle.c` an der markierten Stelle `// TODO Implement me!`, gemäß der
Beschreibung im zugehörigen Header. **Testen Sie** Ihre Implementierung mit dem Projekt `T01DrawRectangle`. Die **Referenzbilder** befinden sich im
Verzeichnis `/tests/T01DrawRectangle`. Während der Tests werden die von Ihnen erzeugten Bilder mit den Referenzbildern verglichen. Alle relevanten
Bilder (Test-, Referenz- und Differenzbilder) werden im Ordner `build/tests/T01DrawRectangle` abgelegt.

# Kreis zeichnen

**Implementieren Sie** die Funktion in der Datei `cgclib/src/raster/Circle.c` entsprechend der Beschreibung im Header. Verwenden Sie das Testprojekt
`T02DrawCircle`, das analog zum Rechteck-Test funktioniert. Auch hier finden Sie Referenz-, Test- und Differenzbilder im entsprechenden Verzeichnis.

# Interaktive Anwendung

Das Projekt `A01BasicRaster` stellt eine interaktive Anwendung bereit, die Ihre Rechteck- und Kreisfunktionen verwendet. Nutzen Sie diese Anwendung,
um Ihre Implementierung visuell zu überprüfen und zu testen.
