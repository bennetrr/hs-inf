use sea_orm::DbErr;

#[allow(dead_code)]
#[derive(Debug)]
pub(crate) enum Error {
    Validation(String),
    Duplicate(String),
    Authorization(),
    NotFound(),
    Db(DbErr),
    Unexpected(String),
}
