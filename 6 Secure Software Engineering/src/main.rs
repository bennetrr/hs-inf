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
    let db = Database::connect("sqlite:../db.sqlite?mode=rwc")
        .await
        .expect("Failed to connect to the database");

    // Migrate database schemas
    db.get_schema_registry("craftmine-authentication-service::entities::*")
        .sync(&db)
        .await
        .expect("Failed to migrate the database");

    let db_state = db.clone();

    // Start the HTTP server
    let default_port: u16 = 65432;
    let port = var("PORT")
        .unwrap_or(default_port.to_string())
        .parse::<u16>()
        .unwrap_or(default_port);

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
    db.close()
        .await
        .expect("Failed to close database connection");

    Ok(())
}
