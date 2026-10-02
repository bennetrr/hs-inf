1) Finden sie alle Rezept-Knoten.

MATCH (n: Recipe) 
RETURN n;

2) Finden sie alle Rezepte und zeigen sie nur die Spalten Name, Preparationszeit, Ruhezeit
und ordnen sie diese nach aufsteigender Preparationszeit.

MATCH (n: Recipe) 
RETURN n.recipeName, n.prepTimeInMinutes AS prep, n.restTimeInMinutes AS rest 
ORDER BY prep ASC;

3) Finden sie alle Rezepte und zeigen sie den Rezeptnamen und die wirkliche Kochzeit
(Preparationszeit und Ruhezeit) absteigend geordnet nach wirklicher Kochzeit an.

MATCH (n: Recipe) 
RETURN n.recipeName, n.prepTimeInMinutes + n.restTimeInMinutes AS real 
ORDER BY real DESC;

4) Finden sie alle Rezepte, die vom Typen "Hauptspeise" sind, als auch den
Schwierigkeitsgrad "normal" besitzen und zusätzlich die Ersteller dieser Rezepte. Zeigen
sie nur Nutzername und Rezeptname an.

MATCH (d: Difficulty {difficultyName: "normal"})
<-[:RECIPE_HAS_DIFFICULTY]-(r: Recipe)-[:RECIPE_OF_TYPE]->
(t: MealType {mealTypeName: "Hauptspeise"}) 
RETURN r;

5) Finden sie alle Nutzer, die ein Rezept erstellt haben und geben sie diese in einer Spalte
wieder. Jeder Nutzer soll maximal einmal aufgeführt werden.

MATCH (u:User)-[:CREATED_BY]->(r:Recipe) RETURN DISTINCT u;

6) Updaten sie für alle Rezept-braucht-Zutat Relationen in denen die Einheit "nach Bedarf"
ist die Eigenschaft Menge zu "etwas" (Vorsicht mit Update Befehlen, nichts falsches
Updaten! Ansonsten muss neu importiert werden).

MATCH (:Recipe)-[rel:RECIPE_REQUIRES_INGREDIENT]->(:Ingredient)
WHERE rel.unitName = "nach Bedarf"
SET rel.amount = "etwas" 

7) Entfernen sie die Abkürzung für alle Rezept-braucht-Zutat Relationen, in denen die die
Abkürzung gleich dem Einheitsnamen ist (Vorsicht mit Update Befehlen, nichts falsches
Entfernen! Ansonsten muss neu importiert werden).

MATCH (:Recipe)-[rel:RECIPE_REQUIRES_INGREDIENT]->(:Ingredient)
WHERE rel.unitName = rel.unitAbbreviation
REMOVE rel.unitAbbreviation

8) Führen sie ein Update auf alle Rezepte aus, welches den Rezepten die Eigenschaft
durchschnittliche Bewertung (Integer), berechnet durch die jeweiligen Bewertungen,
hinzufügt.

MATCH(:User)-[rel:RATED]->(r:Recipe)
WITH r, round(avg(toInteger(rel.rating)), 1) AS avgRating
SET r.averageRating = avgRating

9) Finden sie das Rezept mit der höchsten durchschnittlichen Bewertung und zeigen sie nur
den Namen und die durchschnittliche Bewertung an.

MATCH(r:Recipe)
WHERE exists(r.averageRating)
RETURN r.name, r.averageRating
ORDER BY r.averageRating DESC
LIMIT 1

10) Finden sie alle Zutaten, welche für die Rezepte des Essensplans bzw. der Essenspläne
des Nutzers "CooperKilvington" benötigt werden und zeigen sie diese in einer Liste an.
Jede Zutat darf nur einmal in der Liste vorhanden sein.

MATCH (:User {userName: "CooperKilvington"})-[:USER_HAS_MEALPLAN]->(plan:MealPlan)
MATCH (plan)-[:INCLUDES_RECIPE]->(r:Recipe)-[:RECIPE_REQUIRES_INGREDIENT]->(ingredient:Ingredient)
RETURN collect(DISTINCT ingredient.ingredientName)

11) Finden sie für alle Rezepte, wie oft diese jeweils favorisiert wurden und geben sie die
Rezeptnamen sowie die Anzahl der Favorisierungen nach absteigender
Favorisierungsanzahl aus.

MATCH (:User)-[rel:IS_FAVOURITE]->(r:Recipe)
RETURN r.recipeName, count(rel) AS favCount
ORDER BY favCount DESC

12) Erweitern sie das System um Freundschaften zwischen Usern. Für den Import der
Freundverbindungen steht die CSV-Datei „users_are_friends.csv“ bereit. (Tipp: PERIODIC
COMMIT)

----------- (in der Load Datei) 

13) Finden sie alle Nutzer mit denen "KaliSavile" befreundet ist.

MATCH (u:User)-[:ARE_FRIENDS]->(:User {userName: "KaliSavile"}) RETURN u;

14) Finden Sie alle Rezepte, die in einem Essensplan von einem Nutzer enthalten sind, mit
welchem der Nutzer "KaliSavile" über drei Kanten befreundet ist. Außerdem soll der über
drei Kanten befreundete Nutzer das Rezept auf dem Essensplan mit einer Wertung von 5
bewertet haben. Geben sie nur den Namen des Rezeptes bzw. der Rezepte aus.

MATCH (k:User {userName: "KaliSavile"})-[:ARE_FRIENDS*3]->(friend:User)-[:USER_HAS_MEALPLAN]->(plan:MealPlan)-[:INCLUDES_RECIPE]->(r:Recipe)<-[rel:RATED {rating: 5}]-(friend)
RETURN DISTINCT r.recipeName

15) Finden Sie alle Rezepte, die in einem Essensplan von einem Nutzer enthalten sind, mit
welchem der Nutzer "KaliSavile" über drei Kanten befreundet ist (Freunde von Freunden
von Freunden). Außerdem soll der über drei Kanten befreundete Nutzer das Rezept auf
dem Essensplan mit einer Wertung von 5 bewertet haben. Diese Gerichte sollen dem
Nutzer "KaliSavile" empfohlen werden und dürfen deshalb nicht in einem Essensplan von 
"KaliSavile" enthalten sein. Geben sie nur den/die Namen des/der Rezepte in einer Liste
aus.

MATCH (k:User {userName: "KaliSavile"})-[:ARE_FRIENDS*3]->(friend:User)
MATCH (friend)-[:USER_HAS_MEALPLAN]->(plan:MealPlan)-[:INCLUDES_RECIPE]->(r:Recipe)
MATCH (friend)-[rel:RATED]->(r)
WHERE rel.rating = "5" 
AND NOT EXISTS {
  MATCH (k)-[:USER_HAS_MEALPLAN]->(:MealPlan)-[:INCLUDES_RECIPE]->(r)
}
RETURN DISTINCT collect(r.recipeName)
