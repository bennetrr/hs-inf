use crate::entities::player;
use crate::utils::error::Error;
use crate::utils::jwt::Claims;
use actix_web::error::ErrorInternalServerError;
use actix_web::{HttpResponse, Responder, get, patch, post, web};
use sea_orm::DatabaseConnection;
use serde::{Deserialize, Serialize};

#[derive(Debug, Deserialize)]
struct CreateRequest {
    name: String,
    password: String,
}

#[post("/players")]
async fn create(
    db: web::Data<DatabaseConnection>,
    request: web::Json<CreateRequest>,
) -> actix_web::Result<impl Responder> {
    let res = player::create(&db, request.0.name, request.0.password).await;

    match res {
        Ok(entity) => Ok(HttpResponse::Created().json(player::Dto::from(entity))),
        Err(Error::Validation(msg)) => Ok(HttpResponse::BadRequest().body(msg)),
        Err(Error::Duplicate(msg)) => Ok(HttpResponse::Conflict().body(msg)),
        Err(_) => {
            Err(ErrorInternalServerError("An unexpected error occurred"))
        }
    }
}

#[get("/players/me")]
async fn get_me(
    db: web::Data<DatabaseConnection>,
    claims: Claims,
) -> actix_web::Result<impl Responder> {
    let res = player::get(&db, claims.sub).await;

    match res {
        Ok(entity) => Ok(HttpResponse::Ok().json(player::Dto::from(entity))),
        Err(Error::NotFound()) => Ok(HttpResponse::NotFound().finish()),
        Err(_) => {
            Err(ErrorInternalServerError("An unexpected error occurred"))
        }
    }
}

#[get("/players/{id}")]
async fn get_player(
    db: web::Data<DatabaseConnection>,
    path: web::Path<String>,
) -> actix_web::Result<impl Responder> {
    let res = player::get(&db, path.into_inner()).await;

    match res {
        Ok(entity) => Ok(HttpResponse::Ok().json(player::Dto::from(entity))),
        Err(Error::NotFound()) => Ok(HttpResponse::NotFound().finish()),
        Err(_) => {
            Err(ErrorInternalServerError("An unexpected error occurred"))
        }
    }
}

#[derive(Debug, Deserialize)]
struct AuthRequest {
    name: String,
    password: String,
}

#[derive(Debug, Serialize)]
struct AuthResponse {
    access_token: String,
}

#[post("/players/me/auth")]
async fn auth(
    db: web::Data<DatabaseConnection>,
    request: web::Json<AuthRequest>,
) -> actix_web::Result<impl Responder> {
    let res = player::authenticate(&db, request.0.name, request.0.password).await;

    match res {
        Ok(jwt) => Ok(HttpResponse::Ok().json(AuthResponse { access_token: jwt })),
        Err(Error::Authorization()) => Ok(HttpResponse::Unauthorized().finish()),
        Err(_) => {
            Err(ErrorInternalServerError("An unexpected error occurred"))
        }
    }
}

#[derive(Debug, Deserialize)]
struct ChangeNameRequest {
    name: String,
}

#[patch("/players/me/name")]
async fn change_name(
    db: web::Data<DatabaseConnection>,
    claims: Claims,
    request: web::Json<ChangeNameRequest>,
) -> actix_web::Result<impl Responder> {
    let res = player::change_name(&db, claims.sub, request.0.name).await;

    match res {
        Ok(entity) => Ok(HttpResponse::Ok().json(player::Dto::from(entity))),
        Err(Error::NotFound()) => Ok(HttpResponse::NotFound().finish()),
        Err(Error::Validation(msg)) => Ok(HttpResponse::BadRequest().body(msg)),
        Err(Error::Duplicate(msg)) => Ok(HttpResponse::Conflict().body(msg)),
        Err(_) => {
            Err(ErrorInternalServerError("An unexpected error occurred"))
        }
    }
}

#[derive(Debug, Deserialize)]
struct ChangePasswordRequest {
    old_password: String,
    new_password: String,
}

#[patch("/players/me/password")]
async fn change_password(
    db: web::Data<DatabaseConnection>,
    claims: Claims,
    request: web::Json<ChangePasswordRequest>,
) -> actix_web::Result<impl Responder> {
    let res = player::change_password(
        &db,
        claims.sub,
        request.0.old_password,
        request.0.new_password,
    )
    .await;

    match res {
        Ok(entity) => Ok(HttpResponse::Ok().json(player::Dto::from(entity))),
        Err(Error::NotFound()) => Ok(HttpResponse::NotFound().finish()),
        Err(Error::Validation(msg)) => Ok(HttpResponse::BadRequest().body(msg)),
        Err(_) => {
            Err(ErrorInternalServerError("An unexpected error occurred"))
        }
    }
}
