// Constraints für alle Properties, die unique sein sollen
CREATE CONSTRAINT FOR (n:User) REQUIRE n.userName IS UNIQUE;
CREATE CONSTRAINT FOR (n:Recipe) REQUIRE n.recipeName IS UNIQUE;
CREATE CONSTRAINT FOR (n:Ingredient) REQUIRE n.ingredientName IS UNIQUE;
CREATE CONSTRAINT FOR (n:Difficulty) REQUIRE n.difficultyName IS UNIQUE;
CREATE CONSTRAINT FOR (n:MealType) REQUIRE n.mealTypeName IS UNIQUE;

// Import Users
LOAD CSV WITH HEADERS FROM "file:///users.csv" AS row FIELDTERMINATOR ";"
  MERGE (:User {
    userName: row.userName,
    userEmail: row.userEmail,
    userPassword: row.userPassword,
    enabled: toBoolean(row.enabled)
  });

// Import Recipes
LOAD CSV WITH HEADERS FROM "file:///recipes.csv" AS row FIELDTERMINATOR ";"
  MERGE (:Recipe {
    recipeName: row.recipeName,
    prepTimeInMinutes: toInteger(row.prepTimeInMinutes),
    prepText: row.prepText,
    people: toInteger(row.people),
    restTimeInMinutes: toInteger(row.restTimeInMinutes),
    viewCount: toInteger(row.restTimeInMinutes)
  });

// Import Ingredients
LOAD CSV WITH HEADERS FROM "file:///ingredients.csv" AS row FIELDTERMINATOR ";"
  MERGE(:Ingredient { ingredientName: row.ingredientName });

// Import Relationship ARE_FRIENDS
LOAD CSV WITH HEADERS FROM "file:///users_are_friends.csv" AS row FIELDTERMINATOR ";"
  MATCH (n:User { userName: row.userNameOne })
  MATCH (m:User { userName: row.userNameTwo })
  MERGE (n)-[:ARE_FRIENDS]-(m);

// Import Relationship CREATED_BY
LOAD CSV WITH HEADERS FROM "file:///recipes.csv" AS row FIELDTERMINATOR ";"
  MATCH (u:User { userName: row.createdByUser })
  MATCH (r:Recipe { recipeName: row.recipeName })
  MERGE (u)-[:CREATED_BY]->(r);

// Import Relationship IS_FAVOURITE
LOAD CSV WITH HEADERS FROM "file:///user_has_favourite.csv" AS row FIELDTERMINATOR ";"
  MATCH (u:User { userName: row.userName })
  MATCH (r:Recipe { recipeName: row.favouriteRecipe })
  MERGE (u)-[:IS_FAVOURITE]->(r);

// Import Relationship RATED
LOAD CSV WITH HEADERS FROM "file:///user_rated_recipe.csv" AS row FIELDTERMINATOR ";"
  MATCH (u:User { userName: row.userName })
  MATCH (r:Recipe { recipeName: row.recipeName })
  MERGE (u)-[rs:RATED]->(r) SET rs.rating = row.rating;

// Import Relationship RECIPE_REQUIRES_INGREDIENT
LOAD CSV WITH HEADERS FROM "file:///ingredient_to_recipe.csv" AS row FIELDTERMINATOR ";"
  MATCH (r:Recipe { recipeName: row.recipeName })
  MATCH (i:Ingredient { ingredientName: row.ingredientName })
  MERGE (r)-[:RECIPE_REQUIRES_INGREDIENT {
    amount: toInteger(row.amount),
    unitName: row.unitName,
    unitAbbreviation: row.unitAbbreviation
  }]->(i);

// Import Relationship RECIPE_HAS_DIFFICULTY
LOAD CSV WITH HEADERS FROM "file:///recipes.csv" AS row FIELDTERMINATOR ";"
  MATCH (r:Recipe { recipeName: row.recipeName })
  // Dadurch wird eine neue Difficulty erstellt, wenn es sie noch nicht gibt, ansonsten wird die vorhandene genommen
  MERGE (d:Difficulty { difficultyName: row.difficultyName })
  MERGE (r)-[:RECIPE_HAS_DIFFICULTY]->(d);

// Import Relationship RECIPE_OF_TYPE
LOAD CSV WITH HEADERS FROM "file:///recipes.csv" AS row FIELDTERMINATOR ";"
  MATCH (r:Recipe { recipeName: row.recipeName })
  MERGE (t:MealType { mealTypeName: row.mealTypeName })
  MERGE (r)-[:RECIPE_OF_TYPE]->(t);

// Import Relationship USER_HAS_MEALPLAN
LOAD CSV WITH HEADERS FROM "file:///user_has_mealplan.csv" AS row FIELDTERMINATOR ";"
  MATCH (u:User { userName: row.userName })
  CREATE (m:MealPlan { mealPlanId: toInteger(row.mealPlanId) })
  MERGE (u)-[:USER_HAS_MEALPLAN]->(m);

// Import Relationship INCLUDES_RECIPE
LOAD CSV WITH HEADERS FROM "file:///user_has_mealplan_includes_recipe.csv" AS row FIELDTERMINATOR ";"
  // Parse das deutsche Datumsformat: https://neo4j.com/developer/kb/neo4j-string-to-date/
  // Das *, ist dafür da, dass Variablen, die vorher definiert wurden (speziell row),
  // nicht durch das WITH de-scoped werden und weiter unten noch verfügbar sind
  WITH *, [item IN split(row.date, ".") | toInteger(item)] AS dateParts
  WITH *, date({ day: dateParts[0], month: dateParts[1], year: dateParts[2] }) AS date
  MATCH (u:User { userName: row.userName })-[:USER_HAS_MEALPLAN]->(m:MealPlan { mealPlanId: toInteger(row.mealPlanId) })
  MATCH (r:Recipe { recipeName: row.recipeName })
  MERGE (m)-[rs:INCLUDES_RECIPE]->(r) SET rs.date = date;
