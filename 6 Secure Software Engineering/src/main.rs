use crate::utils::jwt::authenticated;
use actix_web::middleware::from_fn;
use actix_web::{App, HttpServer, web};
use sea_orm::Database;
use std::env::var;

pub mod endpoints;
pub(crate) mod entities;
pub(crate) mod utils;

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    // Set up logging

    // Set up database connection
    let db_uri = "sqlite:../db.sqlite?mode=rwc";
    log::info!("Connecting to database on {db_uri}"); // Task 1.1
    // log::info!(db_uri; "Connecting to database"); // Task 4.2

    let db = Database::connect(db_uri)
        .await
        .expect("Failed to connect to the database");

    // Migrate database schemas
    log::info!("Migrating database schemas"); // Task 1.1 & 4.2
    db.get_schema_registry("craftmine-authentication-service::entities::*")
        .sync(&db)
        .await
        .expect("Failed to migrate the database");
    log::info!("Database schema migration complete"); // Task 1.1 & 4.2

    let db_state = db.clone();

    // Start the HTTP server
    let default_port: u16 = 65432;
    let port = var("PORT")
        .unwrap_or(default_port.to_string())
        .parse::<u16>()
        .unwrap_or(default_port);

    log::info!("Starting HTTP server on port {port}"); // Task 1.1
    // log::info!(port; "Starting HTTP server"); // Task 4.2
    HttpServer::new(move || {
        App::new()
            .app_data(web::Data::new(db_state.clone()))
            .service(endpoints::healthz::healthz)
            .service(endpoints::player::create)
            .service(endpoints::player::auth)
            .service(
                web::scope("")
                    .wrap(from_fn(authenticated))
                    .service(endpoints::player::change_name)
                    .service(endpoints::player::change_password)
                    .service(endpoints::player::get_me)
                    .service(endpoints::player::get_player),
            )
    })
    .bind(("0.0.0.0", port))?
    .run()
    .await?;

    // Cleanup resources
    log::info!("Shutting down, closing database connection"); // Task 1.1 & 4.2
    db.close()
        .await
        .expect("Failed to close database connection");

    Ok(())
}
