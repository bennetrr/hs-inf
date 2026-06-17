use actix_web::error::ErrorServiceUnavailable;
use actix_web::{HttpResponse, Responder, get, web};
use sea_orm::DatabaseConnection;

#[get("/healthz")]
async fn healthz(db: web::Data<DatabaseConnection>) -> actix_web::Result<impl Responder> {
    db.ping().await.map_err(|err| {
        log::warn!("GET /healthz failed: Failed to ping database: {}", err); // Task 1.1
        // log::warn!(err: err; "GET /healthz failed: Failed to ping database"); // Task 4.2
        ErrorServiceUnavailable(err)
    })?;

    Ok(HttpResponse::Ok().body("Healthy"))
}
