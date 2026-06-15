use actix_web::error::ErrorServiceUnavailable;
use actix_web::{HttpResponse, Responder, get, web};
use sea_orm::DatabaseConnection;

#[get("/healthz")]
async fn healthz(db: web::Data<DatabaseConnection>) -> actix_web::Result<impl Responder> {
    db.ping().await.map_err(ErrorServiceUnavailable)?;

    Ok(HttpResponse::Ok().body("Healthy"))
}
