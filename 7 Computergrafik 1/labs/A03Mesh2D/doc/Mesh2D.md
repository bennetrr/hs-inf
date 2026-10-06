---
# Build Command
# pandoc --pdf-engine xelatex -s Mesh2D.md --template ../../eisvogel.latex -o Mesh2D.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: "Praktikum: Mesh 2D Zeichnen"
titlepage: true
author: [Prof. Dr.-Ing. Quirin Meyer]
date: "2025-10-09"
keywords: [CG1 Praktikum, Dreiecke, Rasterung]
papersize: A4
fontfamily: roboto
mainfont: "Roboto-Regular"
lang: "de"
header-left: "\\theauthor"
header-center: " "
header-right: "Computer Grafik 1"
footer-left: "Hochschule Coburg"
footer-center: "\\thepage"
footer-right: "FEIF"
...

In dieser Aufgabe erstellen und animieren wir ein 2D-Mesh eines kleinen Löwen. Dabei durchlaufen wir mehrere Schritte von der Matrix-Arithmetik bis zur finalen Darstellung.


# Matrix-Arithmetik 

Implementieren Sie die Funktionen gemäß den Kommentaren in `cgclib/math/Mat4.h`.

**Datei:** `cgclib/math/Mat4.h`

**Ziel:** Alle Tests in `T08TestMat4` sollen erfolgreich durchlaufen.


# Transformationen

Implementieren Sie die folgenden Funktionen aus dem Header `cgclib/math/Transforms.h`:

- `NDCToWindow`
- `Projection2D`

**Hinweis:** Die Kommentare im Code geben Ihnen genaue Hinweise zur Umsetzung.

**Datei:** `cgclib/math/Transforms.h`

**Ziel:** Alle Tests in `T09Test2DTrafo` sollen erfolgreich durchlaufen.


# 2D-Mesh rendern

Vervollständigen Sie die Funktion `Render2DMesh` aus dem Header `Render2DMesh.h`, um das `SimpleMesh mesh` mit `DrawTriangleFlat` zu zeichnen.
Machen Sie sich auch mit der Struktur `SimpleMesh` vertraut -- sie ist zentral für das Rendering.

**Datei:** `Render2DMesh.h`

**Ziel:** Wenn Sie `A03Mesh2D` ausführen, soll ein kleiner Löwe sichtbar sein.

# Animationen 
Der Löwe soll sich drehen und gleichzeitig verschoben werden. Die zugehörigen Tests finden Sie in `T10Mesh2DTransforms`.

Vervollständigen Sie dazu `Mesh2DTransforms.h`.

**Schritt 1: Objekt in den Camera-Space transformieren**

Implementieren Sie `ObjectToCamera`:

1. Rotation um den Winkel  
  $$\alpha = \frac{t}{1000}$$
2. Verschiebung um den Vektor  
  $$
  \vec{t} = \frac{1}{2} \begin{bmatrix} \cos\left(\frac{\alpha}{10}\right) \\ \sin\left(\frac{\alpha}{10}\right) \end{bmatrix}
  $$

**Wichtig:** Achten Sie auf die korrekte Reihenfolge der Matrix-Multiplikationen!


**Schritt 2: Transformation in Window Coordinates**

Implementieren Sie `ModelToWindow`:

1. Berechnen Sie die Model-Transform mit `ObjectToCamera` (siehe oben)
2. Transformieren Sie in den Clip-Space mit `Projection2D`
3. Transformieren Sie in Window Coordinates mit `NDCToWindow`
4. Multiplizieren Sie die Matrizen in der richtigen Reihenfolge und geben Sie das Ergebnis zurück

**Datei:** `Mesh2DTransforms.h`

**Ziel:**  Die Tests in `T10Mesh2DTransforms` laufen durch.

# Finale Animation

Betrachten Sie die Funktion `RenderScene` im Header `Render2DMesh.h`.
Ersetzen Sie die hartkodierte `modelToWindow`-Matrix durch die berechnete aus `ModelToWindow`.
Die Zeit $t$ seit dem Programmstart bekommen Sie über ```Pixelbuffer p``` mit ```p.time```. 

**Datei:** `Render2DMesh.h`

**Ziele:**  

1. Wenn alles korrekt ist, zeigt die Anwendung `A03Mesh2D` eine schöne, flüssige Animation des Löwen.
1. Die Tests in `T11Render2DMesh` erzeugen Vergleichsbilder und prüfen diese gegen die Referenz.

