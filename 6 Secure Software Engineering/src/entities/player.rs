use crate::utils::error::Error;
use crate::utils::jwt::create_jwt;
use crate::utils::password::{hash_password, verify_password};
use sea_orm::IntoActiveValue;
use sea_orm::entity::prelude::*;
use serde::{Deserialize, Serialize};

#[sea_orm::model]
#[derive(Clone, Debug, PartialEq, Eq, DeriveEntityModel)]
#[sea_orm(table_name = "players")]
pub struct Model {
    #[sea_orm(primary_key)]
    pub id: String,
    #[sea_orm(unique)]
    pub name: String,
    pub password_hash: String,
}

impl ActiveModelBehavior for ActiveModel {}

#[derive(Debug, Serialize, Deserialize)]
pub struct Dto {
    pub id: String,
    pub name: String,
}

impl From<Model> for Dto {
    fn from(model: Model) -> Self {
        Self {
            id: model.id,
            name: model.name,
        }
    }
}

fn validate_name(name: String) -> Result<(), Error> {
    if name.trim().is_empty() {
        return Err(Error::Validation("name must not be empty".to_string()));
    }

    if name.len() > 30 {
        return Err(Error::Validation(
            "name must not be longer than 30 characters".to_string(),
        ));
    }

    Ok(())
}

fn validate_password(password: String) -> Result<(), Error> {
    if password.trim().is_empty() {
        return Err(Error::Validation("password must not be empty".to_string()));
    }

    if password.len() < 12 {
        return Err(Error::Validation(
            "password must be longer than 12 chars".to_string(),
        ));
    }

    Ok(())
}

pub(crate) async fn create(
    db: &DatabaseConnection,
    name: String,
    password: String,
) -> Result<Model, Error> {
    validate_name(name.clone())?;
    validate_password(password.clone())?;

    let player = ActiveModel {
        id: Uuid::new_v4().to_string().into_active_value(),
        name: name.into_active_value(),
        password_hash: hash_password(password)?.into_active_value(),
    };

    player.insert(db).await.map_err(|e| match e.sql_err() {
        Some(SqlErr::UniqueConstraintViolation(_)) => {
            Error::Duplicate("A user with the same name is already registered".to_string())
        }
        _ => Error::Db(e),
    })
}

pub(crate) async fn get(db: &DatabaseConnection, id: String) -> Result<Model, Error> {
    Entity::find_by_id(id)
        .one(db)
        .await
        .map_err(Error::Db)?
        .ok_or_else(Error::NotFound)
}

pub(crate) async fn authenticate(
    db: &DatabaseConnection,
    name: String,
    password: String,
) -> Result<String, Error> {
    let player = Entity::find()
        .filter(Column::Name.eq(name))
        .one(db)
        .await
        .map_err(Error::Db)?
        .ok_or_else(Error::Authorization)?;
    let id = player.id;

    if !verify_password(password, player.password_hash) {
        log::warn!("Player {id} tried to authenticate with wrong password"); // Task 1.1
        // log::warn!(id; "Player {id} tried to authenticate with wrong password"); // Task 4.2
        return Err(Error::Authorization());
    }

    log::debug!("Player {id} signed in successfully"); // Task 1.1
    // log::warn!(id; "Player {id} signed in successfully"); // Task 4.2
    create_jwt(id, player.name)
}

pub(crate) async fn change_name(
    _db: &DatabaseConnection,
    _id: String,
    _name: String,
) -> Result<Model, Error> {
    Err(Error::Unexpected("Intentional error for testing".to_string()))
}

pub(crate) async fn change_password(
    db: &DatabaseConnection,
    id: String,
    old_password: String,
    new_password: String,
) -> Result<Model, Error> {
    validate_password(new_password.clone())?;

    let mut player: ActiveModel = get(db, id.clone()).await?.into();

    if !verify_password(old_password, player.password_hash.unwrap()) {
        log::warn!("Player {id} tried to authenticate with wrong password"); // Task 1.1
        // log::warn!(id; "Player {id} tried to authenticate with wrong password"); // Task 4.2
        return Err(Error::Validation("old_password is not correct".to_string()));
    }

    player.password_hash = hash_password(new_password)?.into_active_value();

    player.update(db).await.map_err(Error::Db)
}
